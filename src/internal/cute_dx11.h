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

#ifndef CUTE_DX11_H
#define CUTE_DX11_H

#include "cute_defines.h"
#include "sokol/sokol_gfx.h"

void cf_dx11_init(void* hwnd, int w, int h, int sample_count);
sg_context_desc cf_dx11_get_context();
void cf_dx11_present(bool vsync);
void cf_dx11_shutdown();

#ifdef CUTE_CPP

namespace Cute
{

}

#endif // CUTE_CPP

#endif // CUTE_DX11_H
