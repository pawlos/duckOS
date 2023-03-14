/* SPDX-License-Identifier: GPL-3.0-or-later */
/* Copyright © 2016-2023 Byteduck */

#pragma once

#include "api/stdint.h"

#define BOOT_LOGO_WIDTH 16
#define BOOT_LOGO_HEIGHT 16
#define BOOT_LOGO_SCALE 6

static const uint32_t boot_logo[]  = {
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0xff000000, 0xff000000, 0xffffd800, 0xffffd800, 0xffffd800, 0xff000000, 0xff000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff000000, 0xff000000, 0xff000000,
		0x00000000, 0xff000000, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xff000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff000000, 0xffffd800, 0xff000000,
		0xff000000, 0xff000000, 0xffff6a00, 0xffff6a00, 0xffffd800, 0xff000000, 0xffffd800, 0xff000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff000000, 0xff000000, 0xffffd800, 0xff000000,
		0xff000000, 0xffff6a00, 0xffff6a00, 0xffff6a00, 0xffffd800, 0xffffd800, 0xffffd800, 0xff000000, 0x00000000, 0x00000000, 0x00000000, 0xff000000, 0xff000000, 0xffffd800, 0xffffd800, 0xff000000,
		0xff000000, 0xff000000, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xffffd800, 0xffffd800, 0xffffd800, 0xff000000,
		0x00000000, 0xff000000, 0xff000000, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xff000000,
		0x00000000, 0x00000000, 0xff000000, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffccaa00, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xff000000,
		0x00000000, 0x00000000, 0xff000000, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffccaa00, 0xffccaa00, 0xffccaa00, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xff000000,
		0x00000000, 0x00000000, 0xff000000, 0xff000000, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xff000000, 0xff000000,
		0x00000000, 0x00000000, 0x00000000, 0xff000000, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xffffd800, 0xff000000, 0xff000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0xff000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
		0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000
};