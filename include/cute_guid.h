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

#ifndef CUTE_GUID_H
#define CUTE_GUID_H

#include "cute_defines.h"
#include "cute_c_runtime.h"

//--------------------------------------------------------------------------------------------------
// C API

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @struct   CF_Guid
 * @category utility
 * @brief    A general purpose unique identifier.
 * @related  CF_Guid cf_make_guid cf_guid_equal
 */
typedef struct CF_Guid
{
	/* @member The raw bytes of the Guid. */
	uint8_t data[16];
} CF_Guid;
// @end

/**
 * @function cf_make_guid
 * @category utility
 * @brief    Returns a new `CF_Guid`.
 * @remarks  The bytes are generated in a cryptographically secure way.
 * @related  CF_Guid cf_make_guid cf_guid_equal
 */
CUTE_API CF_Guid CUTE_CALL cf_make_guid();

/**
 * @function cf_guid_equal
 * @category utility
 * @brief    Returns true if two `CF_Guid`'s are equal, false otherwise.
 * @param    a         A guid to compare.
 * @param    b         A guid to compare.
 * @related  CF_Guid cf_make_guid cf_guid_equal
 */
CUTE_INLINE bool cf_guid_equal(CF_Guid a, CF_Guid b) { return !CUTE_MEMCMP(&a, &b, sizeof(a)); }

#ifdef __cplusplus
}
#endif // __cplusplus

//--------------------------------------------------------------------------------------------------
// C++ API

#ifdef CUTE_CPP

namespace Cute
{

using Guid = CF_Guid;
CUTE_INLINE bool operator==(Guid a, Guid b) { return cf_guid_equal(a, b); }
CUTE_INLINE bool operator!=(Guid a, Guid b) { return !cf_guid_equal(a, b); }

CUTE_INLINE Guid make_guid() { return cf_make_guid(); }

}

#endif // CUTE_CPP

#endif // CUTE_GUID_H
