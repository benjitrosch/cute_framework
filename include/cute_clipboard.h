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

#ifndef CUTE_CLIPBOARD_H
#define CUTE_CLIPBOARD_H

#include "cute_defines.h"
#include "cute_result.h"

//--------------------------------------------------------------------------------------------------
// C API

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @function cf_clipboard_get
 * @category input
 * @brief    Returns a UTF-8 string of the clipboard contents.
 * @related  cf_clipboard_get cf_clipboard_set
 */
CUTE_API char* CUTE_CALL cf_clipboard_get();

/**
 * @function cf_clipboard_set
 * @category input
 * @brief    Sets a UTF-8 string of the clipboard contents.
 * @related  cf_clipboard_get cf_clipboard_set
 */
CUTE_API CF_Result CUTE_CALL cf_clipboard_set(const char* string);

#ifdef __cplusplus
}
#endif // __cplusplus

//--------------------------------------------------------------------------------------------------
// C++ API

#ifdef CUTE_CPP

namespace Cute
{

CUTE_INLINE char* clipboard_get() { return cf_clipboard_get(); }
CUTE_INLINE CF_Result clipboard_set(const char* string) { return cf_clipboard_set(string); }

}

#endif // CUTE_CPP

#endif // CUTE_CLIPBOARD_H
