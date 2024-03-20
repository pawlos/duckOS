/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright © 2016-2024 Byteduck */

#include "IPSocket.h"
#include "UDPSocket.h"
#include "../api/in.h"
#include "../kstd/KLog.h"
#include "../tasking/PollBlocker.h"
#include "../filesystem/FileDescriptor.h"

IPSocket::IPSocket(Socket::Type type, int protocol): Socket(Domain::Inet, type, protocol) {

}

ResultRet<kstd::Arc<IPSocket>> IPSocket::make(Socket::Type type, int protocol) {
	switch (type) {
	case Type::Dgram:
		return kstd::static_pointer_cast<IPSocket>(TRY(UDPSocket::make()));
	default:
		return Result(EINVAL);
	}
}

Result IPSocket::bind(SafePointer<sockaddr> addr_ptr, socklen_t addrlen) {
	LOCK(m_lock);

	if (m_bound || addrlen != sizeof(sockaddr_in))
		return Result(set_error(EINVAL));

	auto addr = addr_ptr.as<sockaddr_in>().get();
	if (addr.sin_family != AF_INET)
		return Result(set_error(EINVAL));

	m_bound_port = from_big_endian(addr.sin_port);
	m_bound_addr = IPv4Address(from_big_endian(addr.sin_addr.s_addr));

	return do_bind();
}

ssize_t IPSocket::recvfrom(FileDescriptor& fd, SafePointer<uint8_t> buf, size_t len, int flags, SafePointer<sockaddr> src_addr, SafePointer<socklen_t> addrlen) {
	m_receive_queue_lock.acquire();

	// Verify addrlen ptr
	if (src_addr && addrlen && addrlen.get() != sizeof(sockaddr_in))
		return -set_error(EINVAL);

	// Block until we have a packet to read
	while (m_receive_queue.empty()) {
		if (fd.nonblock()) {
			m_receive_queue_lock.release();
			return -set_error(EAGAIN);
		}

		update_blocker();
		m_receive_queue_lock.release();
		TaskManager::current_thread()->block(m_receive_blocker);
		if (m_receive_blocker.was_interrupted())
			return -set_error(EINTR);
		m_receive_queue_lock.acquire();
	}

	// Read our packet
	auto* packet = m_receive_queue.pop_front();
	update_blocker();
	m_receive_queue_lock.release();
	auto res = do_recv(packet, buf, len);

	// Write out addr
	if (src_addr && addrlen) {
		src_addr.as<sockaddr_in>().set({
			AF_INET,
			as_big_endian(packet->port),
			packet->packet.source_addr.val()
		});
		addrlen.set(sizeof(sockaddr_in));
	}

	kfree(packet);
	return res;
}

ssize_t IPSocket::sendto(FileDescriptor& fd, SafePointer<uint8_t> buf, size_t len, int flags, SafePointer<sockaddr> dest_addr, socklen_t addrlen) {
	LOCK(m_lock);
	if (dest_addr) {
		if (addrlen != sizeof(sockaddr_in))
			return -set_error(EINVAL);

		auto addr = dest_addr.as<sockaddr_in>().get();
		if (addr.sin_family != AF_INET)
			return -set_error(EAFNOSUPPORT);

		if (m_type != Stream) {
			m_dest_addr = addr.sin_addr.s_addr;
			m_dest_port = from_big_endian(addr.sin_port);
		} else {
			// TODO: TCP. We want to use connect() for that
		}
	}

	if (!m_bound) {
		// If we're not bound, bind to 0.0.0.0:0
		m_bound_port = 0;
		m_bound_addr = {};
		auto res = do_bind();
		if (res.is_error())
			return -res.code();
	}

	// TODO: Adapter binding?

	auto send_res = do_send(buf, len);
	if (send_res.is_error())
		return -send_res.code();
	return (ssize_t) send_res.value();
}

Result IPSocket::recv_packet(const void* buf, size_t len) {
	LOCK(m_receive_queue_lock);

	if (m_receive_queue.size() == m_receive_queue.capacity()) {
		KLog::warn("IPSocket", "Dropping packet because receive queue is full");
		return Result(set_error(ENOSPC));
	}

	auto* src_pkt = (const IPv4Packet*) buf;
	auto* new_pkt = new RecvdPacket;
	memcpy(&new_pkt->packet, src_pkt, len);

	m_receive_queue.push_back(new_pkt);
	update_blocker();

	return Result(SUCCESS);
}

bool IPSocket::can_read(const FileDescriptor& fd) {
	return !m_receive_queue.empty();
}

void IPSocket::update_blocker() {
	m_receive_blocker.set_ready(!m_receive_queue.empty());
}
