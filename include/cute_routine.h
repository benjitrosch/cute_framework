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

#ifndef CUTE_ROUTINE_H
#define CUTE_ROUTINE_H

#include <stdint.h>

//--------------------------------------------------------------------------------------------------
// C++ API

namespace Cute
{

// A portable "coroutine"-like thing for implementing FSM and behavior-cycles.
// 
// Original implementation by Noel Berry.
// See: https://gist.github.com/NoelFB/7a5fa66fc29dd7ed1c11042c30f1b00e
//
// Routine is a set of macros useful to implement Finite State Machine type of
// behaviors. It works really well for simpler behaviors with loops or cycles,
// and works especially well for anything resembling a cutscene.
// 
// The macros here are wrappers around a switch statement. All of the `rt_***`
// macros save a bookmark. On the next frame the routine is resumed at the last
// bookmark.
// 
// Each `rt_***` macro has a block { }. It contains code to run, and is attached
// to the `rt_***` macro. The exception is `rt_end` has no block. Blocks can have
// local variables but they don't persist, so be careful with them. A block will
// run for one frame.

struct CF_Routine
{
	// A "hidden feature" - Goes from 0 to 1 over X seconds during `rt_seconds`.
	// Useful for animating things.
	float elapsed = 0;

	// Used in `rt_seconds` to repeat the block for X seconds.
	float seconds = 0;

	// Used in `rt_wait` to wait for X seconds.
	float wait_elapsed = 0;

	// Bookmark for which block in the routine we are currently at.
	uint64_t at = 0;
};

// -------------------------------------------------------------------------------------------------
// Example:
// rt_begin(routine, delta_time())
// {
//     // This is the starting block. Runs once by default.
// }
// 
// rt_label("state 1")
// {
//     // Runs once.
// }
// rt_seconds(3)
// {
//     // Runs once per frame for 3 seconds.
// }
// rt_wait(1)
// {
//     // Waits 1 second, then runs this once.
// }
// rt_once()
// {
//     // Runs this one time.
//     
//     if (key_pressed(SPACE))
//         nav_goto("state 2"); // Next frame will begin on `rt_label("state 2")`.
//     else
//         nav_goto("state 1"); // Restart this state.
// }
// 
// rt_label("state 2") { } // Empty block.
// rt_wait(5.0f) { } // Empty block. This is like a long "cooldown" of 5 seconds.
// rt_once()
// {
//     nav_restart(); // Restart the whole routine back at `rt_begin`.
// }
// rt_end();

// Begins the routine.
#define rt_begin(routine, dt)                                                \
    do {                                                                     \
        CF_Routine& __rt = routine;                                          \
        bool __mn = true;                                                    \
        float __dt = dt;                                                     \
        if (__rt.wait_elapsed > 0) __rt.wait_elapsed -= __dt;                \
        else switch (__rt.at) {                                              \
        case 0: do {                                                         \

// Has a name that can be jumped to with `co_goto(name)`.
#define rt_label(name)                                                       \
        } while (0); if (__mn) __rt.at = rt_fnv1a(name); break;              \
        case rt_fnv1a(name): do {                                            \

// Runs its block once.
#define rt_once()                                                            \
        } while (0); if (__mn) __rt.at = __LINE__; break;                    \
        case __LINE__: do {                                                  \

// Runs its block for `time` seconds.
#define rt_seconds(time)                                                     \
        rt_once();                                                           \
        auto& rt = __rt;                                                     \
        if (__rt.seconds < time) {                                           \
            __rt.seconds += __dt;                                            \
            __mn = __rt.seconds >= time;                                     \
            if (__mn) {                                                      \
                __rt.elapsed = 1;                                            \
                __rt.seconds = 0;                                            \
            } else {                                                         \
                __rt.elapsed = __rt.seconds / (float)time;                   \
            }                                                                \
        }                                                                    \

// Runs its block while `condition` is true.
#define rt_while(condition)                                                  \
        } while (0); if (__mn) __rt.at = __LINE__; break;                    \
        case __LINE__: if (condition)                                        \
            do { __mn = false;                                               \

// Runs its block once when `condition` becomes true.
#define rt_upon(condition)                                                   \
        } while (0); if (__mn) {                                             \
            __rt.at = (uint64_t)((condition) ? __LINE__ : -__LINE__);        \
        } break;                                                             \
        case -__LINE__:                                                      \
            if (condition) __rt.at = __LINE__;                               \
            break;                                                           \
        case __LINE__: do {                                                  \

// Waits for `time` seconds before running its block.
#define rt_wait(time)                                                        \
        } while (0); if (__mn) {                                             \
            __rt.wait_elapsed = time;                                        \
            __rt.at = __LINE__;                                              \
        }                                                                    \
        break;                                                               \
        case __LINE__: do {                                                  \

// End of the routine. Does not have a block.
#define rt_end()                                                             \
        } while (0); if (__mn) __rt.at = -1;                                 \
        break;                                                               \
        } __rt_end:;                                                         \
    } while (0);                                                             \

// -------------------------------------------------------------------------------------------------
// The `nav_***` macros can be used anywhere in a coroutine.
// Call them like normal functions (inside if-statements, loops, etc.).

// Repeats the block of code this is placed within.
// Skips the rest of the block.
#define nav_redo()                                                           \
        do { goto __rt_end; } while (0)                                      \

// Goes to the block with the name set by `rt_label(name)`.
#define nav_goto(name)                                                       \
        do {                                                                 \
            __rt.at = rt_fnv1a(name);                                        \
            goto __rt_end;                                                   \
        } while (0)                                                          \

// Restarts the whole routine.
#define nav_restart()                                                        \
        do {                                                                 \
            __rt.at = 0;                                                     \
            __rt.elapsed = 0;                                                \
            __rt.seconds = 0;                                                \
            __rt.wait_elapsed = 0;                                           \
            goto __rt_end;                                                   \
        } while (0)                                                          \

// Goes to `name`'s block on the next frame.
// Can be called *outside* of the coroutine.
#define nav_next(routine, name)                                              \
        do { routine.at = rt_fnv1a(name); } while (0)                        \

// -------------------------------------------------------------------------------------------------
// For internal use by `rt_label(name)` and `nav_goto(name)`.

inline uint64_t constexpr rt_fnv1a(const char* name)
{
	uint64_t h = 14695981039346656037ULL;
	char c = 0;
	while ((c = *name++)) {
		h = h ^ (uint64_t)c;
		h = h * 1099511628211ULL;
	}
	return h;
}

}

#endif // CUTE_ROUTINE_H
