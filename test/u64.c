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
	printf("0: %lu, 1: %lu\n",
	       vrng_randu64(DEFAULT_SEED, 0, 100),
	       vrng_randu64(vrng_xorshu64(DEFAULT_SEED), 0, 100));
	return 0;
}
