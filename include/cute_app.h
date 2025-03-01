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

#ifndef CUTE_APP_H
#define CUTE_APP_H

#include "cute_defines.h"
#include "cute_result.h"
#include "cute_graphics.h"
#include "cute_time.h"

//--------------------------------------------------------------------------------------------------
// C API

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct ImGuiContext ImGuiContext;
typedef struct sg_imgui_t sg_imgui_t;
typedef struct sg_image sg_image;

/**
 * @enum     App Options
 * @category app
 * @brief    Various options to control how the application starts up, such as fullscreen, or selecting a graphics backend.
 * @example > Creating a basic window and immediately destroying it.
 *     #include <cute.h>
 *     using namespace cute;
 *     
 *     int main(int argc, const char** argv)
 *     {
 *         uint32_t options = APP_OPTIONS_D3D11_CONTEXT | APP_OPTIONS_WINDOW_POS_CENTERED;
 *         app_make("Fancy Window Title", 0, 0, 640, 480, options, argv[0]);
 *         app_destroy();
 *         return 0;
 *     }
 * @remarks  The `app_options` parameter of `cf_make_app` is a bitmask flag. Simply take the `APP_OPTIONS_*` flags listed above and OR them together.
 * @related  cf_make_app cf_destroy_app
 */
#define CF_APP_OPTION_DEFS \
	/* @entry Starts the app with an OpenGL 3.3 context. */     \
	CF_ENUM(APP_OPTIONS_OPENGL_CONTEXT,                 1 << 0) \
	/* @entry Starts the app with an OpenGL ES 3.3 context. */  \
	CF_ENUM(APP_OPTIONS_OPENGLES_CONTEXT,               1 << 1) \
	/* @entry Starts the app with a DirectX 11 context. */      \
	CF_ENUM(APP_OPTIONS_D3D11_CONTEXT,                  1 << 2) \
	/* @entry Picks a good default graphics context for the given platform. */ \
	CF_ENUM(APP_OPTIONS_DEFAULT_GFX_CONTEXT,            1 << 3) \
	/* @entry Starts the application in borderless full-screen mode. */ \
	CF_ENUM(APP_OPTIONS_FULLSCREEN,                     1 << 4) \
	/* @entry Allows the window to be resized. */               \
	CF_ENUM(APP_OPTIONS_RESIZABLE,                      1 << 5) \
	/* @entry Starts the application with the window hidden. */ \
	CF_ENUM(APP_OPTIONS_HIDDEN,                         1 << 6) \
	/* @entry Starts the application with the window centered on the screen. */ \
	CF_ENUM(APP_OPTIONS_WINDOW_POS_CENTERED,            1 << 7) \
	/* @entry Disables automatically mounting the folder the executable runs from to "/". See `cf_fs_mount` for more details. */ \
	CF_ENUM(APP_OPTIONS_FILE_SYSTEM_DONT_DEFAULT_MOUNT, 1 << 8) \
	/* @entry Starts the application with no audio. */          \
	CF_ENUM(APP_OPTIONS_NO_AUDIO,                       1 << 9) \
	/* @entry Starts the application without vertical sync. */  \
	CF_ENUM(APP_OPTIONS_VSYNC,                          1 << 10) \
	/* @end */

enum
{
	#define CF_ENUM(K, V) CF_##K = V,
	CF_APP_OPTION_DEFS
	#undef CF_ENUM
};

/**
 * @function cf_make_app
 * @category app
 * @brief    Use this function to construct an instance of your application window and (optionally) initialize graphics.
 * @param    window_title  The title of the window in utf8 encoding.
 * @param    x             The x position of the window.
 * @param    y             The y position of the window.
 * @param    w             The width of the window in pixels.
 * @param    h             The height of the window in pixels.
 * @param    options       0 by default; a bitmask of `app_options` flags.
 * @param    argv0         The first argument passed to your main function in the `argv` parameter.
 * @return   Returns any errors on failure as a `CF_Result`.
 * @example > Creating a basic 640x480 window for your game.
 *     #include <cute.h>
 *     using namespace cute;
 *     
 *     int main(int argc, const char** argv)
 *     {
 *         // Create a window with a resolution of 640 x 480, along with a DirectX 11 context.
 *         app_make("Fancy Window Title", 50, 50, 640, 480, CUTE_APP_OPTIONS_D3D11_CONTEXT, argv[0]);
 *         
 *         while (app_is_running())
 *         {
 *             app_update();
 *             // All your game logic and updates go here...
 *             app_draw_onto_screen();
 *         }
 *         
 *         app_destroy();
 *         
 *         return 0;
 *     }
 * @remarks  The options parameter is an enum from `app_options`. Different options can be OR'd together.
 *           Parameters `w` and `h` are ignored if the window is initialized to fullscreen mode with `APP_OPTIONS_FULLSCREEN`.
 * @related  cf_app_is_running cf_app_signal_shutdown cf_destroy_app
 */
CUTE_API CF_Result CUTE_CALL cf_make_app(const char* window_title, int x, int y, int w, int h, int options, const char* argv0);

/**
 * @function cf_destroy_app
 * @category app
 * @brief    Cleans up all resources used by the application. Call `cf_app_signal_shutdown` first.
 * @related  cf_make_app cf_app_is_running cf_app_signal_shutdown
 */
CUTE_API void CUTE_CALL cf_destroy_app();

/**
 * @function cf_app_is_running
 * @category app
 * @brief    Returns true while the app should keep running. Call this as your main loop condition.
 * @return   Returns true if the application should continue running.
 * @example > Creating a basic 640x480 window for your game.
 *     #include <cute.h>
 *     using namespace cute;
 *     
 *     int main(int argc, const char** argv)
 *     {
 *         // Create a window with a resolution of 640 x 480, along with a DirectX 11 context.
 *         app_make("Fancy Window Title", 50, 50, 640, 480, CUTE_APP_OPTIONS_D3D11_CONTEXT, argv[0]);
 *         
 *         while (app_is_running())
 *         {
 *             app_update();
 *             // All your game logic and updates go here...
 *             app_draw_onto_screen();
 *         }
 *         
 *         app_destroy();
 *         
 *         return 0;
 *     }
 * @remarks  Some OS events, like clicking the red X on the app, will signal the app should shutdown.
 *           This will cause this function to return false. You may manually call `cf_app_signal_shutdown`
 *           to signal a shutdown.
 * @related  cf_make_app cf_destroy_app cf_app_signal_shutdown
 */
CUTE_API bool CUTE_CALL cf_app_is_running();

/**
 * @function cf_app_signal_shutdown
 * @category app
 * @brief    Call this to end your main-loop; makes `cf_app_is_running` return false.
 * @example > Creating a basic 640x480 window for your game.
 *     #include <cute.h>
 *     using namespace cute;
 *     
 *     int main(int argc, const char** argv)
 *     {
 *         // Create a window with a resolution of 640 x 480, along with a DirectX 11 context.
 *         app_make("Fancy Window Title", 50, 50, 640, 480, CUTE_APP_OPTIONS_D3D11_CONTEXT, argv[0]);
 *         
 *         while (app_is_running())
 *         {
 *             app_update();
 *             // All your game logic and updates go here...
 *             if (my_game_should_quit()) {
 *                 // The next call to app_is_running() will return false.
 *                 cf_app_signal_shutdown();
 *             }
 *             app_draw_onto_screen();
 *         }
 *         
 *         app_destroy();
 *         
 *         return 0;
 *     }
 * @related  cf_make_app cf_destroy_app cf_app_is_running
 */
CUTE_API void CUTE_CALL cf_app_signal_shutdown();

/**
 * @function cf_app_update
 * @category app
 * @brief    Updates the application. Must be called once per frame.
 * @param    on_update  Called for each update tick.
 * @example > Running an app in Variable or Fixed Timestep.
 *     TODO
 * @related  cf_make_app cf_app_is_running cf_app_signal_shutdown cf_destroy_app
 */
CUTE_API void CUTE_CALL cf_app_update(CF_OnUpdateFn* on_update);

/**
 * @function cf_app_draw_onto_screen
 * @category app
 * @brief    Draws the app onto the screen.
 * @return   Returns the number of draw calls for this frame.
 * @example > Creating a basic 640x480 window for your game.
 *     #include <cute.h>
 *     using namespace cute;
 *     
 *     int main(int argc, const char** argv)
 *     {
 *         // Create a window with a resolution of 640 x 480, along with a DirectX 11 context.
 *         app_make("Fancy Window Title", 50, 50, 640, 480, CUTE_APP_OPTIONS_D3D11_CONTEXT, argv[0]);
 *         
 *         while (app_is_running())
 *         {
 *             app_update();
 *             // All your game logic and updates go here...
 *             app_draw_onto_screen();
 *         }
 *         
 *         app_destroy();
 *         
 *         return 0;
 *     }
 * @remarks  Call this at tnhe *end* of your main loop.
 * @related  cf_make_app cf_app_is_running cf_app_signal_shutdown cf_destroy_app
 */
CUTE_API int CUTE_CALL cf_app_draw_onto_screen();

/**
 * @function cf_app_get_size
 * @category app
 * @brief    Gets the size of the window in pixels.
 * @param    w          The width of the window in pixels.
 * @param    h          The height of the window in pixels.
 * @related  cf_app_set_size cf_app_get_position cf_app_set_position
 */
CUTE_API void CUTE_CALL cf_app_get_size(int* w, int* h);

/**
 * @function cf_app_set_size
 * @category app
 * @brief    Sets the size of the window in pixels.
 * @param    w          The width of the window in pixels.
 * @param    h          The height of the window in pixels.
 * @related  cf_app_get_size cf_app_get_position cf_app_set_position
 */
CUTE_API void CUTE_CALL cf_app_set_size(int w, int h);

/**
 * @function cf_app_get_position
 * @category app
 * @brief    Gets the position of the window in pixels.
 * @param    x          The x position of the window in pixels.
 * @param    y          The y position of the window in pixels.
 * @related  cf_app_get_size cf_app_set_size cf_app_set_position
 */
CUTE_API void CUTE_CALL cf_app_get_position(int* x, int* y);

/**
 * @function cf_app_set_position
 * @category app
 * @brief    Sets the position of the window in pixels.
 * @param    x          The x position of the window in pixels.
 * @param    y          The y position of the window in pixels.
 * @related  cf_app_get_size cf_app_set_size cf_app_get_position
 */
CUTE_API void CUTE_CALL cf_app_set_position(int x, int y);

/**
 * @function cf_app_was_resized
 * @category app
 * @brief    Returns true if the app was resized last frame.
 * @related  cf_app_was_moved
 */
CUTE_API bool CUTE_CALL cf_app_was_resized();

/**
 * @function cf_app_was_moved
 * @category app
 * @brief    Returns true if the app was moved (not resized) last frame.
 * @related  cf_app_was_resized
 */
CUTE_API bool CUTE_CALL cf_app_was_moved();

/**
 * @function cf_app_lost_focus
 * @category app
 * @brief    Returns true if the app lost focus last frame.
 * @remarks  The app has focus if user inputs will go to the app, such as after clicking on or selecting the app.
 * @related  cf_app_gained_focus cf_app_has_focus cf_app_was_restored
 */
CUTE_API bool CUTE_CALL cf_app_lost_focus();

/**
 * @function cf_app_gained_focus
 * @category app
 * @brief    Returns true if the app gained focus last frame.
 * @remarks  The app has focus if user inputs will go to the app, such as after clicking on or selecting the app.
 * @related  cf_app_lost_focus cf_app_has_focus cf_app_was_restored
 */
CUTE_API bool CUTE_CALL cf_app_gained_focus();

/**
 * @function cf_app_has_focus
 * @category app
 * @brief    Returns true while the app has focus currently.
 * @remarks  The app has focus if user inputs will go to the app, such as after clicking on or selecting the app.
 * @related  cf_app_lost_focus cf_app_gained_focus cf_app_was_restored
 */
CUTE_API bool CUTE_CALL cf_app_has_focus();

/**
 * @function cf_app_was_minimized
 * @category app
 * @brief    Returns true if the app was minimized last frame.
 * @related  cf_app_was_maximized cf_app_minimized cf_app_maximized cf_app_was_restored
 */
CUTE_API bool CUTE_CALL cf_app_was_minimized();

/**
 * @function cf_app_was_maximized
 * @category app
 * @brief    Returns true if the app was maximized last frame.
 * @related  cf_app_was_minimized cf_app_minimized cf_app_maximized cf_app_was_restored
 */
CUTE_API bool CUTE_CALL cf_app_was_maximized();

/**
 * @function cf_app_minimized
 * @category app
 * @brief    Returns true while the app is currently minimized.
 * @related  cf_app_was_minimized cf_app_was_maximized cf_app_maximized cf_app_was_restored
 */
CUTE_API bool CUTE_CALL cf_app_minimized();

/**
 * @function cf_app_maximized
 * @category app
 * @brief    Returns true while the app is currently maximized.
 * @related  cf_app_was_minimized cf_app_was_maximized cf_app_minimized cf_app_was_restored
 */
CUTE_API bool CUTE_CALL cf_app_maximized();

/**
 * @function cf_app_was_restored
 * @category app
 * @brief    Returns true if the app was restored last frame.
 * @remarks  Restored means a window's size/position was restored from a minimized/maximized state.
 * @related  cf_app_was_minimized cf_app_was_maximized cf_app_minimized cf_app_maximized cf_app_was_restored
 */
CUTE_API bool CUTE_CALL cf_app_was_restored();

/**
 * @function cf_app_mouse_entered
 * @category app
 * @brief    Returns true if the mouse's coordinates began hovering over the app last frame.
 * @remarks  This function only deals with mouse coordinates, not focus (such as `cf_app_has_focus`).
 * @related  cf_app_mouse_exited cf_app_mouse_inside
 */
CUTE_API bool CUTE_CALL cf_app_mouse_entered();

/**
 * @function cf_app_mouse_exited
 * @category app
 * @brief    Returns true if the mouse's coordinates stopped hovering over the app last frame.
 * @remarks  This function only deals with mouse coordinates, not focus (such as `cf_app_has_focus`).
 * @related  cf_app_mouse_entered cf_app_mouse_inside
 */
CUTE_API bool CUTE_CALL cf_app_mouse_exited();

/**
 * @function cf_app_mouse_inside
 * @category app
 * @brief    Returns true while the mouse's coordinates are hovering the app currently.
 * @remarks  This function only deals with mouse coordinates, not focus (such as `cf_app_has_focus`).
 * @related  cf_app_mouse_entered cf_app_mouse_exited
 */
CUTE_API bool CUTE_CALL cf_app_mouse_inside();

/**
 * @function cf_app_init_imgui
 * @category app
 * @brief    Initializes Dear ImGui.
 * @param    no_default_font  Prevents Dear ImGui from loading up it's own default font to save a small bit of memory.
 *                            You must then supply your own font.
 * @remarks  [Dear ImGui](https://github.com/ocornut/imgui) is an excellent UI library for debugging, great for making tools and editors.
 *           After calling this init function you can call into Dear ImGui's functions.
 * @related  cf_app_get_sokol_imgui
 */
CUTE_API ImGuiContext* CUTE_CALL cf_app_init_imgui(bool no_default_font /*= false*/);

/**
 * @function cf_app_get_sokol_imgui
 * @category app
 * @brief    Fetches a sokol Dear ImGui debug context.
 * @remarks  Internally Cute Framework uses [sokol_gfx.h](https://github.com/floooh/sokol) for wrapping low-level graphics APIs.
 *           As an optional feature you can access `sokol_imgui_t` to use Dear ImGui to debug inspect all of sokol_gfx's primitives.
 *           You must call `cf_app_init_imgui` to use this function.
 * @related  cf_app_init_imgui
 */
CUTE_API sg_imgui_t* CUTE_CALL cf_app_get_sokol_imgui();

/**
 * @function cf_app_get_canvas
 * @category app
 * @brief    Fetches the app's internal canvas for displaying content on the screen.
 * @remarks  This is an advanced function. If you just want to draw things on screen, try checking out `CF_Sprite`.
 *           The app's canvas can be used to implement low-level graphics features, such as multi-pass algorithms. Be careful about
 *           calling `cf_app_set_canvas_size`, as it will invalidate any references to the app's canvas.
 * @related  cf_app_set_canvas_size cf_app_get_canvas_width cf_app_get_canvas_height
 */
CUTE_API CF_Canvas CUTE_CALL cf_app_get_canvas();

/**
 * @function cf_app_set_canvas_size
 * @category app
 * @brief    Resizes the app's internal canvas to a new w/h, in pixels.
 * @param    w          The width in pixels to resize the canvas to.
 * @param    h          The height in pixels to resize the canvas to.
 * @remarks  Be careful about calling this function, as it will invalidate any old references from `cf_app_get_canvas`.
 * @related  cf_app_get_canvas cf_app_get_canvas_width cf_app_get_canvas_height
 */
CUTE_API void CUTE_CALL cf_app_set_canvas_size(int w, int h);

/**
 * @function cf_app_get_canvas_width
 * @category app
 * @brief    Gets the app's canvas width in pixels.
 * @related  cf_app_get_canvas cf_app_set_canvas_size cf_app_get_canvas_height
 */
CUTE_API int CUTE_CALL cf_app_get_canvas_width();

/**
 * @function cf_app_get_canvas_height
 * @category app
 * @brief    Gets the app's canvas height in pixels.
 * @related  cf_app_get_canvas cf_app_set_canvas_size cf_app_get_canvas_width
 */
CUTE_API int CUTE_CALL cf_app_get_canvas_height();

/**
 * @enum     CF_PowerState
 * @category app
 * @brief    The states of power for the application.
 * @related  CF_PowerInfo cf_app_power_info
 */
#define CF_POWER_STATE_DEFS \
	/* @entry Cannot determine power status. */         \
	CF_ENUM(POWER_STATE_UNKNOWN, 0)                     \
	/* @entry Not plugged in and running on battery. */ \
	CF_ENUM(POWER_STATE_ON_BATTERY, 1)                  \
	/* @entry Plugged in with no battery available. */  \
	CF_ENUM(POWER_STATE_NO_BATTERY, 2)                  \
	/* @entry Plugged in and charging battery. */       \
	CF_ENUM(POWER_STATE_CHARGING, 3)                    \
	/* @entry Plugged in and battery is charged. */     \
	CF_ENUM(POWER_STATE_CHARGED, 4)                     \
	/* @end */

typedef enum CF_PowerState
{
	#define CF_ENUM(K, V) CF_##K = V,
	CF_POWER_STATE_DEFS
	#undef CF_ENUM
} CF_PowerState;

/**
 * @function cf_power_state_to_string
 * @category app
 * @brief    Convert an enum `CF_PowerState` to a c-style string.
 * @param    state        The state to convert to a string.
 * @related  cf_app_power_info CF_PowerState CF_PowerInfo
 */
CUTE_INLINE const char* cf_power_state_to_string(CF_PowerState state) {
	switch (state) {
	#define CF_ENUM(K, V) case CF_##K: return CUTE_STRINGIZE(CF_##K);
	CF_POWER_STATE_DEFS
	#undef CF_ENUM
	default: return NULL;
	}
}

/**
 * @struct   CF_PowerInfo
 * @category app
 * @brief    Detailed information about the power level/status of the application.
 * @related  cf_app_power_info cf_power_state_to_string CF_PowerState
 */
typedef struct CF_PowerInfo
{
	/* @member Enumeration `CF_PowerState` for the power state.*/
	CF_PowerState state;

	/* @member The seconds of battery life left. -1 means not running on the battery, or unable to get a valid value. */
	int seconds_left;

	/* @member The percentage of battery life left from 0 to 100. -1 means not running on the battery, or unable to get a valid value. */
	int percentage_left;
} CF_PowerInfo;
// @end

/**
 * @function cf_app_power_info
 * @category app
 * @brief    Fetches detailed power info about the application.
 * @return   Returns a `CF_PowerInfo` struct.
 * @related  CF_PowerInfo cf_power_state_to_string CF_PowerState
 */
CUTE_API CF_PowerInfo CUTE_CALL cf_app_power_info();

#ifdef __cplusplus
}
#endif // __cplusplus

//--------------------------------------------------------------------------------------------------
// C++ API

#ifdef CUTE_CPP

namespace Cute
{

enum : int
{
	#define CF_ENUM(K, V) K = V,
	CF_APP_OPTION_DEFS
	#undef CF_ENUM
};

using PowerInfo = CF_PowerInfo;

using PowerState = CF_PowerState;
#define CF_ENUM(K, V) CUTE_INLINE constexpr PowerState K = CF_##K;
CF_POWER_STATE_DEFS
#undef CF_ENUM

CUTE_INLINE const char* power_state_to_string(PowerState state) { switch (state) {
	#define CF_ENUM(K, V) case K: return #K;
	CF_POWER_STATE_DEFS
	#undef CF_ENUM
	default: return NULL;
	}
}

CUTE_INLINE Result make_app(const char* window_title, int x, int y, int w, int h, uint32_t options = 0, const char* argv0 = NULL) { return cf_make_app(window_title, x, y, w, h, options, argv0); }
CUTE_INLINE void destroy_app() { cf_destroy_app(); }
CUTE_INLINE bool app_is_running() { return cf_app_is_running(); }
CUTE_INLINE void app_signal_shutdown() { cf_app_signal_shutdown(); }
CUTE_INLINE void app_update(OnUpdateFn* on_update = NULL) { cf_app_update(on_update); }
CUTE_INLINE int app_draw_onto_screen() { return cf_app_draw_onto_screen(); }
CUTE_INLINE void app_get_size(int* w, int* h) { return cf_app_get_size(w, h); }
CUTE_INLINE void app_set_size(int w, int h) { return cf_app_set_size(w, h); }
CUTE_INLINE void app_get_position(int* x, int* y) { return cf_app_get_position(x, y); }
CUTE_INLINE void app_set_position(int x, int y) { return cf_app_set_position(x, y); }
CUTE_INLINE bool app_was_resized() { return cf_app_was_resized(); }
CUTE_INLINE bool app_was_moved() { return cf_app_was_moved(); }
CUTE_INLINE bool app_lost_focus() { return cf_app_lost_focus(); }
CUTE_INLINE bool app_gained_focus() { return cf_app_gained_focus(); }
CUTE_INLINE bool app_has_focus() { return cf_app_has_focus(); }
CUTE_INLINE bool app_was_minimized() { return cf_app_was_minimized(); }
CUTE_INLINE bool app_was_maximized() { return cf_app_was_maximized(); }
CUTE_INLINE bool app_minimized() { return cf_app_minimized(); }
CUTE_INLINE bool app_maximized() { return cf_app_maximized(); }
CUTE_INLINE bool app_was_restored() { return cf_app_was_restored(); }
CUTE_INLINE bool app_mouse_entered() { return cf_app_mouse_entered(); }
CUTE_INLINE bool app_mouse_exited() { return cf_app_mouse_exited(); }
CUTE_INLINE bool app_mouse_inside() { return cf_app_mouse_inside(); }
CUTE_INLINE int app_get_canvas_width() { return cf_app_get_canvas_width(); }
CUTE_INLINE int app_get_canvas_height() { return cf_app_get_canvas_height(); }

CUTE_INLINE ImGuiContext* app_init_imgui(bool no_default_font = false) { return cf_app_init_imgui(no_default_font); }
CUTE_INLINE sg_imgui_t* app_get_sokol_imgui() { return cf_app_get_sokol_imgui(); }
CUTE_INLINE CF_Canvas app_get_canvas() { return cf_app_get_canvas(); }
CUTE_INLINE void app_set_canvas_size(int w, int h) { cf_app_set_canvas_size(w, h); }
CUTE_INLINE PowerInfo app_power_info() { return cf_app_power_info(); }

}

#endif // CUTE_CPP

#endif // CUTE_APP_H
