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
	float f0 = vrng_tof64max(DEFAULT_SEED);
	float f1 = vrng_tof64max(vrng_xorshu64(DEFAULT_SEED));

	printf("0: %f, 1: %f\n", f0, f1);

	if (!(f0 >= DBL_MIN && f0 <= DBL_MAX && f1 >= DBL_MIN &&
	      f1 <= DBL_MAX))
	{
		fprintf(stderr, "invalid floating point number\n");
		return 1;
	}

	return 0;
}
