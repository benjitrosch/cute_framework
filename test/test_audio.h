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

#include <cute_audio.h>
#include <cute_app.h>
#include <cute_multithreading.h>

using namespace Cute;

CUTE_TEST_CASE(test_audio_load_synchronous, "Load and free wav/ogg files synchronously.");
int test_audio_load_synchronous()
{
	CUTE_TEST_ASSERT(!cf_is_error(cf_make_app("UNIT TEST", 0, 0, 0, 0, APP_OPTIONS_HIDDEN | APP_OPTIONS_DEFAULT_GFX_CONTEXT, NULL)));
	CF_Audio* audio = cf_audio_load_ogg("test_data/3-6-19-blue-suit-jam.ogg");
	CUTE_TEST_CHECK_POINTER(audio);
	cf_audio_destroy(audio);
	audio = cf_audio_load_wav("test_data/jump.wav");
	CUTE_TEST_CHECK_POINTER(audio);
	cf_audio_destroy(audio);
	cf_destroy_app();

	return 0;
}
