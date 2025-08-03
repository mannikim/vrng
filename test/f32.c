// SPDX-License-Identifier: GPL-3.0-or-later
// copyright 2025 mannikim <mannikim[at]proton[dot]me>
// this file is part of vrng.h
// see the bottom of the `vrng.h` file for the license text

#include <stdio.h>

#include "test.h"
#include "vrng.h"

int
main(void)
{
	printf("0: %f, 1: %f\n",
	       tof32(DEFAULT_SEED),
	       tof32(xorshiftu64(DEFAULT_SEED)));
	return 0;
}
