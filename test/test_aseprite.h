/*
	Cute Framework
	Copyright (C) 2019 Randy Gaul https://randygaul.net

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

#include <cute.h>
using namespace Cute;

#ifndef CUTE_STATIC
#	define CUTE_ASEPRITE_IMPLEMENTATION
#	include <cute/cute_aseprite.h>
#endif

#include <internal/cute_aseprite_cache_internal.h>

CUTE_TEST_CASE(test_aseprite_make_destroy, "Load an aseprite file and destroy it.");
int test_aseprite_make_destroy()
{
	ase_t* ase = cute_aseprite_load_from_file("test_data/girl.aseprite", NULL);
	cute_aseprite_free(ase);
	return 0;
}
