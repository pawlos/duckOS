/*
    This file is part of duckOS.

    duckOS is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    duckOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with duckOS.  If not, see <https://www.gnu.org/licenses/>.

    Copyright (c) Byteduck 2016-2020. All rights reserved.
*/

#ifndef DUCKOS_PTYMUXDEVICE_H
#define DUCKOS_PTYMUXDEVICE_H

#include <kernel/device/CharacterDevice.h>
#include <kernel/tasking/SpinLock.h>

class PTYControllerDevice;
class PTYMuxDevice: public CharacterDevice {
public:
	PTYMuxDevice();

	//File
	bool is_pty_mux() override;

	kstd::shared_ptr<PTYControllerDevice> create_new();

private:
	unsigned int current_pty = 0;
	SpinLock lock;
};


#endif //DUCKOS_PTYMUXDEVICE_H
