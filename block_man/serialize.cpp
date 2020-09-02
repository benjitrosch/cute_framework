/*
	Cute Framework
	Copyright (C) 2020 Randy Gaul https://randygaul.net

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

#include <serialize.h>
#include <world.h>

error_t serialize_transform(kv_t* kv, const char* key, transform_t* transform)
{
	kv_object_begin(kv, key);
		kv_key(kv, "x"); kv_val(kv, &transform->p.x);
		kv_key(kv, "y"); kv_val(kv, &transform->p.y);
		kv_key(kv, "s"); kv_val(kv, &transform->r.s);
		kv_key(kv, "c"); kv_val(kv, &transform->r.c);
	kv_object_end(kv);

	return kv_error_state(kv);
}

error_t kv_val(kv_t* kv, const char** string)
{
	size_t len = *string ? CUTE_STRLEN(*string) : 0;
	kv_val_string(kv, string, &len);
	strpool_t* strpool = aseprite_cache_get_strpool_ptr(cache);
	STRPOOL_U64 id = strpool_inject(strpool, *string, (int)len);
	*string = strpool_cstr(strpool, id);
	return kv_error_state(kv);
}
