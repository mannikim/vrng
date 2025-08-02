// SPDX identifier: GPL-3.0-or-later
// copyright 2025 mannikim mannikim[at]proton[dot]me
// this file is part of vrng.h

// vrng.h - simple single-header seeded random number generator library

#include <float.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef VRNG_H
#define VRNG_H

// if your project uses a single translation unit, you can use `#define
// VRNGAPI static inline` so the compiler can remove unused functions
#ifndef VRNGAPI
#define VRNGAPI
#endif

#define VRNG_STATIC_ASSERT(cond, msg) \
	typedef char static_assertion_##msg[(cond) ? 1 : -1]

#ifdef VRNG_DEBUG

#ifndef VRNG_ASSERT
#include <assert.h>
#define VRNG_ASSERT assert
#endif

#else // VRNG_DEBUG

// ignore all asserts in the code
#define VRNG_ASSERT(...)

#endif // VRNG_DEBUG

// VRNG DEF

// seed: uint32_t
#define tof32(seed) ((float)seed / UINT32_MAX)
#define tof32max(seed) ((float)seed / UINT32_MAX * FLT_MAX)

// seed: uint64_t
#define tof64(seed) ((double)seed / UINT64_MAX)
#define tof64max(seed) ((double)seed / UINT64_MAX * DBL_MAX)

VRNGAPI uint32_t
xorshiftu32(uint32_t seed);

VRNGAPI uint64_t
xorshiftu64(uint64_t seed);

VRNGAPI uint64_t
xorshiftu64(uint64_t seed);

VRNGAPI size_t
weightu64(uint64_t seed, uint64_t *weights, size_t weight_count);

VRNGAPI size_t
weightu32(uint32_t seed, uint32_t *weights, size_t weight_count);

VRNGAPI uint32_t
randu32(uint64_t seed, uint32_t min, uint32_t max);

VRNGAPI uint64_t
randu64(uint64_t seed, uint64_t min, uint64_t max);

#ifdef VRNG_IMPL

// https://en.wikipedia.org/wiki/Xorshift
VRNGAPI uint32_t
xorshiftu32(uint32_t seed)
{
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

VRNGAPI uint64_t
xorshiftu64(uint64_t seed)
{
	seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

VRNGAPI size_t
weightu64(uint64_t seed, uint64_t *weights, size_t weight_count)
{
	// remember to also apply changes to `weight32` funtion

	VRNG_ASSERT(weights && "Null pointer passed to weight64");

	uint64_t total_weight = 0;
	for (size_t i = 0; i < weight_count; i++)
	{
		total_weight += weights[i];
	}

	uint64_t weight = seed % total_weight;

	// find the closest weight in `weights`, but smaller then `weight`
	size_t last = 0;
	uint64_t closest_weight = 0;
	uint64_t offset = 0;
	for (size_t i = 0; i < weight_count; i++)
	{
		if (offset + weights[i] > weight)
		{
			offset += weights[i];
			continue;
		}

		if (offset + closest_weight < weight)
		{
			closest_weight = weight;
			last = i;
		}

		offset += weights[i];
	}

	return last;
}

VRNGAPI size_t
weightu32(uint32_t seed, uint32_t *weights, size_t weight_count)
{
	// remember to also apply changes to `weight64` funtion
	
	VRNG_ASSERT(weights && "Null pointer passed to weight32");

	uint32_t total_weight = 0;
	for (size_t i = 0; i < weight_count; i++)
	{
		total_weight += weights[i];
	}

	uint32_t weight = seed % total_weight;

	// find the closest weight in `weights`, but smaller then `weight`
	size_t last = 0;
	uint32_t closest_weight = 0;
	uint32_t offset = 0;
	for (size_t i = 0; i < weight_count; i++)
	{
		if (offset + weights[i] > weight)
		{
			offset += weights[i];
			continue;
		}

		if (offset + closest_weight < weight)
		{
			closest_weight = weight;
			last = i;
		}

		offset += weights[i];
	}

	return last;
}

VRNGAPI uint32_t
randu32(uint64_t seed, uint32_t min, uint32_t max)
{
	return seed % (max - min) + min;
}

VRNGAPI uint64_t
randu64(uint64_t seed, uint64_t min, uint64_t max)
{
	return seed % (max - min) + min;
}

#endif // VRNG_IMPL

#endif // VRNG_H (guard)
