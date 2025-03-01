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

#include <cute_joypad.h>
#include <cute_c_runtime.h>
#include <cute_alloc.h>
#include <cute_haptics.h>

#include <internal/cute_input_internal.h>
#include <internal/cute_app_internal.h>
#include <data/cute_joypad_mapping_db.h>

#include <SDL.h>

// TODO - Lock on joypad list? Race condition with pumping input messages.

void cf_joypad_system_init()
{
	static bool init;
	if (!init) {
		init = true;
		int result = SDL_GameControllerAddMapping((const char*)joypad_mapping_db_data);
		CUTE_ASSERT(result != -1);
	}
}

CF_Result cf_joypad_add_mapping(const char* mapping)
{
	int result = SDL_GameControllerAddMapping(mapping);
	if (result == -1) return cf_result_error("Failed to add mapping.");
	else return cf_result_success();
}

int cf_joypad_count()
{
	return SDL_NumJoysticks();
}

CF_Joypad* cf_joypad_open(int index)
{
	cf_joypad_system_init();
	if (SDL_IsGameController(index)) {
		SDL_GameController* controller = SDL_GameControllerOpen(index);
		if (controller) {
			SDL_Joystick* joy = SDL_GameControllerGetJoystick(controller);
			CF_Joypad* joypad = CUTE_NEW(CF_Joypad);
			joypad->controller = controller;
			joypad->id = SDL_JoystickInstanceID(joy);
			cf_list_push_front(&app->joypads, &joypad->node);
			return joypad;
		}
	}
	return NULL;
}

void cf_joypad_close(CF_Joypad* joypad)
{
	cf_list_remove(&joypad->node);
	if (joypad->haptic) {
		cf_haptic_close(joypad->haptic);
	}
	SDL_GameControllerClose(joypad->controller);
	CUTE_FREE(joypad);
}

bool cf_joypad_is_connected(CF_Joypad* joypad)
{
	return SDL_GameControllerGetAttached(joypad->controller);
}

CF_JoypadPowerLevel cf_joypad_power_level(CF_Joypad* joypad)
{
	SDL_Joystick* joy = SDL_GameControllerGetJoystick(joypad->controller);
	SDL_JoystickPowerLevel level = SDL_JoystickCurrentPowerLevel(joy);
	switch (level) {
	case SDL_JOYSTICK_POWER_UNKNOWN: return CF_JOYPAD_POWER_LEVEL_UNKNOWN;
	case SDL_JOYSTICK_POWER_EMPTY: return CF_JOYPAD_POWER_LEVEL_EMPTY;
	case SDL_JOYSTICK_POWER_LOW: return CF_JOYPAD_POWER_LEVEL_LOW;
	case SDL_JOYSTICK_POWER_MEDIUM: return CF_JOYPAD_POWER_LEVEL_MEDIUM;
	case SDL_JOYSTICK_POWER_FULL: return CF_JOYPAD_POWER_LEVEL_FULL;
	case SDL_JOYSTICK_POWER_WIRED: return CF_JOYPAD_POWER_LEVEL_WIRED;
	case SDL_JOYSTICK_POWER_MAX: return CF_JOYPAD_POWER_LEVEL_COUNT;
	}
	return CF_JOYPAD_POWER_LEVEL_UNKNOWN;
}

const char* cf_joypad_name(CF_Joypad* joypad)
{
	return SDL_GameControllerName(joypad->controller);
}

bool cf_joypad_button_down(CF_Joypad* joypad, CF_JoypadButton button)
{
	return joypad->buttons[button];
}

bool cf_joypad_button_just_pressed(CF_Joypad* joypad, CF_JoypadButton button)
{
	return joypad->buttons[button] && !joypad->buttons_prev[button];
}

bool cf_joypad_button_just_released(CF_Joypad* joypad, CF_JoypadButton button)
{
	return !joypad->buttons[button] && joypad->buttons_prev[button];
}

int16_t cf_joypad_axis(CF_Joypad* joypad, CF_JoypadAxis axis)
{
	return joypad->axes[axis];
}
