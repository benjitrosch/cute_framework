/*
	Cute Framework
	Copyright (C) 2023 Randy Gaul https://randygaul.github.io/

	This software is provided 'as-is', without any express or implied
	warranty.  In no event will the authors be held liable for any damages
	arising from the use of this software.

	Permission is granted to anyone to use this software for any purpose,
	including commercial applications, and to alter it and redistribute it
	freely, subject to the following restrictions:

	1. The origin of this software must not be misrepresented; you must not
	   claim that you wrote the original software. If you use this software
	   in a product, an acknowledgment in the product documentation would be
	   appreciated but is not required.
	2. Altered source versions must be plainly marked as such, and must not be
	   misrepresented as being the original software.
	3. This notice may not be removed or altered from any source distribution.
*/

#ifndef CUTE_RND_H
#define CUTE_RND_H

#include "cute_defines.h"

//--------------------------------------------------------------------------------------------------
// C API

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @struct   CF_Rnd
 * @category random
 * @brief    A random number generator.
 * @remarks  A random number generator of the type LFSR (linear feedback shift registers). This specific
 *           implementation uses the XorShift+ variation, and returns 64-bit random numbers. More information
 *           can be found on Wikipedia.
 *           https://en.wikipedia.org/wiki/Xorshift
 *           
 *           This implementation comes from Mattias Gustavsson's single-file header collection.
 *           https://github.com/mattiasgustavsson/libs/blob/main/rnd.h
 * @related  CF_Rnd cf_rnd_seed cf_rnd_next
 */
typedef struct CF_Rnd
{
	/* @member Just two `uint64_t`'s for the internal state. Very small! These are setup by `cf_rnd_seed`. */
	uint64_t state[2];
} CF_Rnd;
// @end

/**
 * @function cf_rnd_seed
 * @category random
 * @brief    Returns an initialized `CF_Rnd` based on an initial `seed` value.
 * @param    seed         The initial seed value for the random number generator.
 * @remarks  The `seed` is used to control which set of random numbers get generated. The numbers are generated in a completely
 *           deterministic way, so it's often important for many games to control or note which seed is used.
 * @related  CF_Rnd cf_rnd_seed cf_rnd_next
 */
static CUTE_INLINE CF_Rnd   CUTE_CALL cf_rnd_seed(uint64_t seed);

/**
 * @function cf_rnd_next
 * @category random
 * @brief    Returns a random `uint64_t`.
 * @param    rnd          The random number generator state.
 * @related  CF_Rnd cf_rnd_seed cf_rnd_next cf_rnd_next_float cf_rnd_next_double cf_rnd_next_range_int cf_rnd_next_range_uint64 cf_rnd_next_range_float cf_rnd_next_range_double
 */
static CUTE_INLINE uint64_t CUTE_CALL cf_rnd_next(CF_Rnd* rnd);

/**
 * @function cf_rnd_next_float
 * @category random
 * @brief    Returns a random `float`.
 * @param    rnd          The random number generator state.
 * @related  CF_Rnd cf_rnd_seed cf_rnd_next cf_rnd_next_float cf_rnd_next_double cf_rnd_next_range_int cf_rnd_next_range_uint64 cf_rnd_next_range_float cf_rnd_next_range_double
 */
static CUTE_INLINE float    CUTE_CALL cf_rnd_next_float(CF_Rnd* rnd);

/**
 * @function cf_rnd_next_double
 * @category random
 * @brief    Returns a random `double`.
 * @param    rnd          The random number generator state.
 * @related  CF_Rnd cf_rnd_seed cf_rnd_next cf_rnd_next_float cf_rnd_next_double cf_rnd_next_range_int cf_rnd_next_range_uint64 cf_rnd_next_range_float cf_rnd_next_range_double
 */
static CUTE_INLINE double   CUTE_CALL cf_rnd_next_double(CF_Rnd* rnd);

/**
 * @function cf_rnd_next_range_int
 * @category random
 * @brief    Returns a random `int` from the range `min` to `max` (inclusive).
 * @param    rnd          The random number generator state.
 * @related  CF_Rnd cf_rnd_seed cf_rnd_next cf_rnd_next_float cf_rnd_next_double cf_rnd_next_range_int cf_rnd_next_range_uint64 cf_rnd_next_range_float cf_rnd_next_range_double
 */
static CUTE_INLINE int      CUTE_CALL cf_rnd_next_range_int(CF_Rnd* rnd, int min, int max);

/**
 * @function cf_rnd_next_range_uint64
 * @category random
 * @brief    Returns a random `uint64_t` from the range `min` to `max` (inclusive).
 * @param    rnd          The random number generator state.
 * @related  CF_Rnd cf_rnd_seed cf_rnd_next cf_rnd_next_float cf_rnd_next_double cf_rnd_next_range_int cf_rnd_next_range_uint64 cf_rnd_next_range_float cf_rnd_next_range_double
 */
static CUTE_INLINE uint64_t CUTE_CALL cf_rnd_next_range_uint64(CF_Rnd* rnd, uint64_t min, uint64_t max);

/**
 * @function cf_rnd_next_range_float
 * @category random
 * @brief    Returns a random `float` from the range `min` to `max` (inclusive).
 * @param    rnd          The random number generator state.
 * @related  CF_Rnd cf_rnd_seed cf_rnd_next cf_rnd_next_float cf_rnd_next_double cf_rnd_next_range_int cf_rnd_next_range_uint64 cf_rnd_next_range_float cf_rnd_next_range_double
 */
static CUTE_INLINE float    CUTE_CALL cf_rnd_next_range_float(CF_Rnd* rnd, float min, float max);

/**
 * @function cf_rnd_next_range_double
 * @category random
 * @brief    Returns a random `double` from the range `min` to `max` (inclusive).
 * @param    rnd          The random number generator state.
 * @related  CF_Rnd cf_rnd_seed cf_rnd_next cf_rnd_next_float cf_rnd_next_double cf_rnd_next_range_int cf_rnd_next_range_uint64 cf_rnd_next_range_float cf_rnd_next_range_double
 */
static CUTE_INLINE double   CUTE_CALL cf_rnd_next_range_double(CF_Rnd* rnd, double min, double max);

// -------------------------------------------------------------------------------------------------

static CUTE_INLINE uint64_t cf_internal_rnd_murmur3_avalanche64(uint64_t h)
{
	h ^= h >> 33;
	h *= 0xff51afd7ed558ccd;
	h ^= h >> 33;
	h *= 0xc4ceb9fe1a85ec53;
	h ^= h >> 33;
	return h;
}

static CUTE_INLINE CF_Rnd cf_rnd_seed(uint64_t seed)
{
	CF_Rnd rnd;
	uint64_t value = cf_internal_rnd_murmur3_avalanche64((seed << 1ULL) | 1ULL);
	rnd.state[0] = value;
	rnd.state[1] = cf_internal_rnd_murmur3_avalanche64(value);
	return rnd;
}

static CUTE_INLINE uint64_t cf_rnd_next(CF_Rnd* rnd)
{
	uint64_t x = rnd->state[0];
	uint64_t y = rnd->state[1];
	rnd->state[0] = y;
	x ^= x << 23;
	x ^= x >> 17;
	x ^= y ^ (y >> 26);
	rnd->state[1] = x;
	return x + y;
}

static CUTE_INLINE float cf_rnd_next_float(CF_Rnd* rnd)
{
	uint32_t value = (uint32_t)(cf_rnd_next(rnd) >> 32);

	// Convert a randomized uint32_t value to a float value x in the range 0.0f <= x < 1.0f.
	// Contributed by Jonatan Hedborg.
	uint32_t exponent = 127;
	uint32_t mantissa = value >> 9;
	uint32_t result = (exponent << 23) | mantissa;
	return *(float*)&result - 1.0f;
}

static CUTE_INLINE double cf_rnd_next_double(CF_Rnd* rnd)
{
	uint64_t value = cf_rnd_next(rnd);
	uint64_t exponent = 1023;
	uint64_t mantissa = value >> 12;
	uint64_t result = (exponent << 52) | mantissa;
	return *(double*)&result - 1.0;
}

static CUTE_INLINE int cf_rnd_next_range_int(CF_Rnd* rnd, int min, int max)
{
	int range = (max - min) + 1;
	int value = (int)(cf_rnd_next(rnd) % range);
	return min + value;
}

static CUTE_INLINE uint64_t cf_rnd_next_range_uint64(CF_Rnd* rnd, uint64_t min, uint64_t max)
{
	uint64_t range = (max - min) + 1;
	uint64_t value = cf_rnd_next(rnd) % range;
	return min + value;
}

static CUTE_INLINE float cf_rnd_next_range_float(CF_Rnd* rnd, float min, float max)
{
	float range = max - min;
	float value = cf_rnd_next_float(rnd) * range;
	return min + value;
}

static CUTE_INLINE double cf_rnd_next_range_double(CF_Rnd* rnd, double min, double max)
{
	double range = max - min;
	double value = cf_rnd_next_float(rnd) * range;
	return min + value;
}

#ifdef __cplusplus
}
#endif // __cplusplus

//--------------------------------------------------------------------------------------------------
// C++ API

#ifdef CUTE_CPP

namespace Cute
{

using Rnd = CF_Rnd;

namespace internal
{

static CUTE_INLINE uint64_t rnd_murmur3_avalanche64(uint64_t h) { return cf_internal_rnd_murmur3_avalanche64(h); }

}

static CUTE_INLINE Rnd      rnd_seed(uint64_t seed) { return cf_rnd_seed(seed); }
static CUTE_INLINE uint64_t rnd_next(Rnd* rnd) { return cf_rnd_next(rnd); }
static CUTE_INLINE float    rnd_next_float(Rnd* rnd) { return cf_rnd_next_float(rnd); }
static CUTE_INLINE double   rnd_next_double(Rnd* rnd) { return cf_rnd_next_double(rnd); }
static CUTE_INLINE int      rnd_next_range(Rnd* rnd, int min, int max) { return cf_rnd_next_range_int(rnd, min, max); }
static CUTE_INLINE uint64_t rnd_next_range(Rnd* rnd, uint64_t min, uint64_t max) { return cf_rnd_next_range_uint64(rnd, min, max); }
static CUTE_INLINE float    rnd_next_range(Rnd* rnd, float min, float max) { return cf_rnd_next_range_float(rnd, min, max); }
static CUTE_INLINE double   rnd_next_range(Rnd* rnd, double min, double max) { return cf_rnd_next_range_double(rnd, min, max); }

static CUTE_INLINE uint64_t rnd_next(Rnd& rnd) { return cf_rnd_next(&rnd); }
static CUTE_INLINE float    rnd_next_float(Rnd& rnd) { return cf_rnd_next_float(&rnd); }
static CUTE_INLINE double   rnd_next_double(Rnd& rnd) { return cf_rnd_next_double(&rnd); }
static CUTE_INLINE int      rnd_next_range(Rnd& rnd, int min, int max) { return cf_rnd_next_range_int(&rnd, min, max); }
static CUTE_INLINE uint64_t rnd_next_range(Rnd& rnd, uint64_t min, uint64_t max) { return cf_rnd_next_range_uint64(&rnd, min, max); }
static CUTE_INLINE float    rnd_next_range(Rnd& rnd, float min, float max) { return cf_rnd_next_range_float(&rnd, min, max); }
static CUTE_INLINE double   rnd_next_range(Rnd& rnd, double min, double max) { return cf_rnd_next_range_double(&rnd, min, max); }

}

#endif // CUTE_CPP

#endif // CUTE_RND_H
