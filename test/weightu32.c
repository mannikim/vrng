// SPDX-License-Identifier: GPL-3.0-or-later
// copyright 2025 mannikim <mannikim[at]proton[dot]me>
// this file is part of vrng.h
// see the bottom of the `vrng.h` file for the license text

#include <stdio.h>

#include "assert.h"

#include "test.h"
#include "vrng.h"

#define TEST_COUNT 100000000

int
main(void)
{
	assert(TEST_COUNT < UINT32_MAX);

	uint32_t weights[] = {31, 41, 59, 26, 53, 58, 97, 9};
	
	const uint32_t weight_count = sizeof(weights) / sizeof(*weights);
	
	uint32_t results[weight_count];

	uint32_t seed = (uint32_t)DEFAULT_SEED;

	uint32_t total_weight = 0;

	for (size_t i = 0; i < weight_count; i++) 
	{
		total_weight += weights[i];
		results[i] = 0;
	}
	
	for (size_t i = 0; i < TEST_COUNT; i++)
	{
		size_t result = vrng_weightu32(seed, weights, weight_count);
		results[result]++;
		seed = vrng_xorshu32(seed);
	}

	printf("Results:\n");
	int exit = 0;
	for (size_t i = 0; i < weight_count; i++) 
	{
		double out_weight = results[i] / (double)TEST_COUNT;
		double expected_weight = weights[i] / (double)total_weight;
		double diff = expected_weight > out_weight 
			? expected_weight - out_weight 
			: out_weight - expected_weight;

		printf("%d | %d | %f (expected %f diff %f)", 
				weights[i],
				results[i], 
				out_weight,
				expected_weight,
				diff);
		
		if (diff > WEIGHT_ERROR_MARGIN) 
		{
			printf(" << ERR\n");
			exit = 1;
			continue;
		}
		printf("\n");
	}

	return exit;
}
