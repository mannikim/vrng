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
	printf("0: %u, 1: %u\n",
	       randu32(DEFAULT_SEED, 0, 100),
	       randu32(xorshiftu32((uint32_t)DEFAULT_SEED), 0, 100));
	return 0;
}
