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

#ifndef CUTE_TIMER_H
#define CUTE_TIMER_H

#include "cute_defines.h"

//--------------------------------------------------------------------------------------------------
// C API

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @struct   CF_DELTA_TIME
 * @category time
 * @brief    The `dt` or elapsed time from the previous two frames. Use this as an estimate to advance your current frame.
 * @related  CF_DELTA_TIME cf_update_time CF_OnUpdateFn
 */
CUTE_API extern float CF_DELTA_TIME;
// @end

/**
 * @struct   CF_DELTA_TIME_FIXED
 * @category time
 * @brief    The time elapsed between two frames in fixed-timestep mode.
 * @remarks  To turn on fixed-timestep use `cf_set_fixed_timestep`. Fixed timestep is useful when games need determinism. Determinism
 *           means given the same inputs, the exact same outputs are produced. This is especially important for networked games, or
 *           games that require extreme precision and fine-tuning (such as certain fighting games or platformers).
 * @related  CF_DELTA_TIME cf_update_time CF_OnUpdateFn CF_DELTA_TIME_INTERPOLANT cf_set_fixed_timestep cf_set_fixed_timestep_max_updates
 */
CUTE_API extern float CF_DELTA_TIME_FIXED;
// @end

/**
 * @struct   CF_DELTA_TIME_INTERPOLANT
 * @category time
 * @brief    The remaining interpolant between two fixed timestep updates, used for rendering.
 * @remarks  When fixed-timestepping is used (turned on by `cf_set_fixed_timestep`) usually rendering happens at a different frequency
 *           than the fixed updates. To produce smooth visuals, the current time is mod'd producing an interpolant value from [0,1].
 *           Typically games will store two transforms, the previous and current transform, each representing a position at a fixed timestep
 *           interval. This interpolant value is to interpolate between these two states to produce a smooth rendering transition.
 * @related  CF_DELTA_TIME cf_update_time CF_OnUpdateFn CF_DELTA_TIME_INTERPOLANT cf_set_fixed_timestep cf_set_fixed_timestep_max_updates
 */
CUTE_API extern float CF_DELTA_TIME_INTERPOLANT;
// @end

/**
 * @struct   CF_TICKS
 * @category time
 * @brief    The number of machine ticks since program start.
 * @remarks  The frequency of these ticks is platform dependent. If you want to convert these ticks to relative to one second of actual time
 *           call `cf_get_tick_frequency` and use it as a divisor.
 * @related  CF_TICKS CF_PREV_TICKS cf_get_ticks cf_get_tick_frequency cf_make_stopwatch CF_SECONDS
 */
CUTE_API extern uint64_t CF_TICKS;
// @end

/**
 * @struct   CF_PREV_TICKS
 * @category time
 * @brief    The number of machine ticks since program start for the last frame.
 * @remarks  The frequency of these ticks is platform dependent. If you want to convert these ticks to relative to one second of actual time
 *           call `cf_get_tick_frequency` and use it as a divisor.
 * @related  CF_TICKS CF_PREV_TICKS cf_get_ticks cf_get_tick_frequency cf_make_stopwatch CF_SECONDS
 */
CUTE_API extern uint64_t CF_PREV_TICKS;
// @end

/**
 * @struct   CF_SECONDS
 * @category time
 * @brief    The number of seconds elapsed since program start.
 * @related  CF_TICKS CF_PREV_TICKS cf_get_ticks cf_get_tick_frequency cf_make_stopwatch CF_SECONDS CF_PREV_SECONDS
 */
CUTE_API extern double CF_SECONDS;
// @end

/**
 * @struct   CF_PREV_SECONDS
 * @category time
 * @brief    The number of seconds elapsed since program start for the last frame.
 * @related  CF_TICKS CF_PREV_TICKS cf_get_ticks cf_get_tick_frequency cf_make_stopwatch CF_SECONDS CF_PREV_SECONDS
 */
CUTE_API extern double CF_PREV_SECONDS;
// @end

/**
 * @struct   CF_PAUSE_TIME_LEFT
 * @category time
 * @brief    The number of seconds left for the global pause control.
 * @remarks  The entire application can be paused with `cf_pause_for` or `cf_pause_for_ticks`, which pause updates that will
 *           happen when `cf_update_time` is called.
 * @related  CF_PAUSE_TIME_LEFT cf_update_time cf_pause_for cf_pause_for_ticks cf_is_paused
 */
CUTE_API extern float CF_PAUSE_TIME_LEFT;
// @end

/**
 * @function CF_OnUpdateFn
 * @category time
 * @brief    An optional function pointer (callback), called whenever an update should occur, after calling `cf_update_time`.
 * @remarks  This callback can be used to implement your main-loop, and is generally used to update your gameplay/logic/physics.
 *           Usually rendering will occur outside of this callback one time per frame. This callback is only really useful when
 *           using a fixed timestep (see `cf_set_fixed_timestep`), as multiple calls can occur given a single frame's update.
 * @related  cf_set_fixed_timestep cf_set_fixed_timestep_max_updates cf_update_time CF_DELTA_TIME_FIXED CF_DELTA_TIME_INTERPOLANT
 */
typedef void (CF_OnUpdateFn)();

/**
 * @function cf_set_fixed_timestep
 * @category time
 * @brief    Sets the frequency for fixed timestep updates to occur.
 * @param    frames_per_second  The frequency for fixed-timestep updates to occur, e.g. 30 is a good default number.
 * @remarks  Often times a fixed-timestep can occur multiple times in one frame. In this case, `CF_OnUpdateFn` will be called once
 *           per update to simulate a fixed-timestep (see `CF_OnUpdateFn` and `cf_update_time`). The max number of updates possible 
 *           is clamped below `cf_set_fixed_timestep_max_updates`.
 * @related  cf_set_fixed_timestep cf_set_fixed_timestep_max_updates cf_update_time CF_DELTA_TIME_FIXED CF_DELTA_TIME_INTERPOLANT
 */
CUTE_API void CUTE_CALL cf_set_fixed_timestep(int frames_per_second);

/**
 * @function cf_set_fixed_timestep_max_updates
 * @category time
 * @brief    Sets the frequency for fixed timestep updates to occur.
 * @param    max_updates  The max number of updates. A good default number is 5.
 * @remarks  Often times a fixed-timestep can occur multiple times in one frame. In this case, `CF_OnUpdateFn` will be called once
 *           per update to simulate a fixed-timestep (see `CF_OnUpdateFn` and `cf_update_time`). The max number of updates possible 
 *           is clamped below `max_updates`.
 * @related  cf_set_fixed_timestep cf_set_fixed_timestep_max_updates cf_update_time CF_DELTA_TIME_FIXED CF_DELTA_TIME_INTERPOLANT
 */
CUTE_API void CUTE_CALL cf_set_fixed_timestep_max_updates(int max_updates);

/**
 * @function cf_update_time
 * @category time
 * @brief    Updates the application.
 * @param    on_update  Can be `NULL`. Called once per update. Mostly just useful for the fixed-timestep case (see `cf_set_fixed_timestep`).
 * @related  cf_set_fixed_timestep cf_set_fixed_timestep_max_updates cf_update_time CF_DELTA_TIME_FIXED CF_DELTA_TIME_INTERPOLANT
 */
CUTE_API void CUTE_CALL cf_update_time(CF_OnUpdateFn* on_update);

/**
 * @function cf_pause_for
 * @category time
 * @brief    Pauses the application.
 * @param    seconds    A number of seconds to pause the application for.
 * @remarks  The entire application can be paused with `cf_pause_for` or `cf_pause_for_ticks`, which pause updates that will
 *           happen when `cf_update_time` is called.
 * @related  CF_PAUSE_TIME_LEFT cf_update_time cf_pause_for cf_pause_for_ticks cf_is_paused
 */
CUTE_API void CUTE_CALL cf_pause_for(float seconds);

/**
 * @function cf_pause_for_ticks
 * @category time
 * @brief    Pauses the application.
 * @param    ticks      A number of ticks to pause the application for. See `cf_get_tick_frequency`.
 * @remarks  The entire application can be paused with `cf_pause_for` or `cf_pause_for_ticks`, which pause updates that will
 *           happen when `cf_update_time` is called.
 * @related  CF_PAUSE_TIME_LEFT cf_update_time cf_pause_for cf_pause_for_ticks cf_is_paused
 */
CUTE_API void CUTE_CALL cf_pause_for_ticks(uint64_t pause_ticks);

/**
 * @function cf_on_interval
 * @category time
 * @brief    Returns true for one frame update each time an interval of seconds elapses.
 * @param    interval   Number of seconds between each interval.
 * @param    offset     An offset of seconds used to offset within the interval of [0,interval]. This gets mathematically mod'd,
 *                      so it can be any number of seconds.
 * @remarks  This function is super useful for general purpose gameplay implementation where you want an event to fire every N seconds.
 *           Simply place this within an if-statement!
 * @related  cf_on_interval cf_between_interval cf_on_timestamp
 */
CUTE_API bool CUTE_CALL cf_on_interval(float interval, float offset);

/**
 * @function cf_between_interval
 * @category time
 * @brief    Returns true for one interval of seconds, every other interval.
 * @param    interval   Number of seconds between each interval.
 * @param    offset     An offset of seconds used to offset within the interval of [0,interval]. This gets mathematically mod'd,
 *                      so it can be any number of seconds.
 * @remarks  This function is super useful for general purpose gameplay implementation where you want an event to fire for N seconds,
 *           and then _not_ fire for N seconds, flipping back and forth periodically. Simply place this within an if-statement!
 * @related  cf_on_interval cf_between_interval cf_on_timestamp
 */
CUTE_API bool CUTE_CALL cf_between_interval(float interval, float offset);

/**
 * @function cf_on_timestamp
 * @category time
 * @brief    Returns true for one frame where a specific timestamp (relative to program start) occurs.
 * @param    timestamp  The timestamp.
 * @remarks  This function is super useful for general purpose gameplay implementation where you want an event to fire at N seconds
 *           (since program start). Simply place this within an if-statement!
 * @related  cf_on_interval cf_between_interval cf_on_timestamp
 */
CUTE_API bool CUTE_CALL cf_on_timestamp(double timestamp);

/**
 * @function cf_is_paused
 * @category time
 * @brief    Returns true if the application is currently paused.
 * @remarks  Pause means from `cf_pause_for` or `cf_pause_for_ticks`.
 * @related  CF_PAUSE_TIME_LEFT cf_is_paused cf_pause_for cf_pause_for_ticks
 */
CUTE_API bool CUTE_CALL cf_is_paused();

/**
 * @function cf_get_ticks
 * @category time
 * @brief    Returns the number of ticks elapsed _right now_ since program start.
 * @remarks  `CF_TICK` and `CF_SECONDS` are only recorded once at the beginning of an update (see `cf_update_time`). This function instead
 *           queries the application for the number of ticks _right now_. Mostly useful for performance measuring.
 * @related  cf_get_ticks cf_get_tick_frequency
 */
CUTE_API uint64_t CUTE_CALL cf_get_ticks();

/**
 * @function cf_get_tick_frequency
 * @category time
 * @brief    Returns the machine-dependent number of ticks that occur in one second.
 * @related  cf_get_ticks cf_get_tick_frequency
 */
CUTE_API uint64_t CUTE_CALL cf_get_tick_frequency();

/**
 * @function cf_sleep
 * @category time
 * @brief    Waits an estimated number of milliseconds before returning.
 * @remarks  This function actually sleeps the application. If you want to instead pause updates without locking the entire
 *           applcation (so you can e.g. continue rendering and capturing user inputs) use `cf_pause_for` instead.
 * @related  cf_get_ticks cf_get_tick_frequency cf_pause_for
 */
CUTE_API void CUTE_CALL cf_sleep(int milliseconds);

/**
 * @struct   CF_Stopwatch
 * @category time
 * @brief    A stopwatch for general purpose precise timings.
 * @remarks  Once created with `cf_make_stopwatch` the time elapsed can be fetched. To reset the stopwatch, simply call
 *           `cf_make_stopwatch` again and overwrite your old stopwatch.
 * @related  CF_Stopwatch cf_make_stopwatch cf_seconds cf_milliseconds cf_microseconds
 */
typedef struct CF_Stopwatch
{
	/* @member The starting time (in ticks) of the stopwatch. See `cf_make_stopwatch`. */
	uint64_t start_time;
} CF_Stopwatch;
// @end

/**
 * @function cf_make_stopwatch
 * @category time
 * @brief    Records a new `start_time` for a `CF_Stopwatch`.
 * @return   Returns an initialize `CF_Stopwatch` to the time of _right now_ (e.g. with `cf_get_ticks` internally).
 * @remarks  Once created with `cf_make_stopwatch` the time elapsed can be fetched. To reset the stopwatch, simply call
 *           `cf_make_stopwatch` again and overwrite your old stopwatch. To fetch the time elapsed, call `cf_stopwatch_seconds`,
 *           `cf_stopwatch_milliseconds`, or `cf_microseconds`.
 * @related  CF_Stopwatch cf_make_stopwatch cf_stopwatch_seconds cf_stopwatch_milliseconds cf_stopwatch_microseconds
 */
CUTE_API CF_Stopwatch CUTE_CALL cf_make_stopwatch();

/**
 * @function cf_stopwatch_seconds
 * @category time
 * @brief    Returns the number of seconds elapsed since the last call to `cf_make_stopwatch` was made.
 * @related  CF_Stopwatch cf_make_stopwatch cf_stopwatch_seconds cf_stopwatch_milliseconds cf_stopwatch_microseconds
 */
CUTE_API double CUTE_CALL cf_stopwatch_seconds(CF_Stopwatch stopwatch);

/**
 * @function cf_stopwatch_milliseconds
 * @category time
 * @brief    Returns the number of milliseconds elapsed since the last call to `cf_make_stopwatch` was made.
 * @related  CF_Stopwatch cf_make_stopwatch cf_stopwatch_seconds cf_stopwatch_milliseconds cf_stopwatch_microseconds
 */
CUTE_API double CUTE_CALL cf_stopwatch_milliseconds(CF_Stopwatch stopwatch);

/**
 * @function cf_stopwatch_microseconds
 * @category time
 * @brief    Returns the number of microseconds elapsed since the last call to `cf_make_stopwatch` was made.
 * @related  CF_Stopwatch cf_make_stopwatch cf_seconds cf_stopwatch_milliseconds cf_stopwatch_microseconds
 */
CUTE_API double CUTE_CALL cf_stopwatch_microseconds(CF_Stopwatch stopwatch);

#ifdef __cplusplus
}
#endif // __cplusplus

//--------------------------------------------------------------------------------------------------
// C++ API

#ifdef CUTE_CPP

namespace Cute
{

#define DELTA_TIME (CF_DELTA_TIME)
#define DELTA_TIME_FIXED (CF_DELTA_TIME_FIXED)
#define DELTA_TIME_INTERPOLANT (CF_DELTA_TIME_INTERPOLANT)
using OnUpdateFn = CF_OnUpdateFn;
using Stopwatch = CF_Stopwatch;

CUTE_INLINE void set_fixed_timestep(int frames_per_second = 60) { cf_set_fixed_timestep(frames_per_second); }
CUTE_INLINE void set_fixed_timestep_max_updates(int max_updates = 5) { cf_set_fixed_timestep_max_updates(max_updates); }
CUTE_INLINE void update_time(OnUpdateFn* on_update = NULL) { cf_update_time(on_update); }
CUTE_INLINE void pause_for(float seconds) { cf_pause_for(seconds); }
CUTE_INLINE void pause_for_ticks(uint64_t pause_ticks) { cf_pause_for_ticks(pause_ticks); }

CUTE_INLINE bool on_interval(float interval, float offset = 0) { return cf_on_interval(interval, offset); }
CUTE_INLINE bool between_interval(float interval, float offset = 0) { return cf_between_interval(interval, offset); }
CUTE_INLINE bool on_timestamp(double timestamp) { return cf_on_timestamp(timestamp); }
CUTE_INLINE bool is_paused() { return cf_is_paused(); }

CUTE_INLINE uint64_t get_ticks() { return cf_get_ticks(); }
CUTE_INLINE uint64_t get_tick_frequency() { return cf_get_tick_frequency(); }
CUTE_INLINE void sleep(int milliseconds) { cf_sleep(milliseconds); }

CUTE_INLINE CF_Stopwatch make_stopwatch() { return cf_make_stopwatch(); }
CUTE_INLINE double stopwatch_seconds(CF_Stopwatch stopwatch) { return cf_stopwatch_seconds(stopwatch); }
CUTE_INLINE double stopwatch_milliseconds(CF_Stopwatch stopwatch) { return cf_stopwatch_milliseconds(stopwatch); }
CUTE_INLINE double stopwatch_microseconds(CF_Stopwatch stopwatch) { return cf_stopwatch_microseconds(stopwatch); }

}

#endif // CUTE_CPP

#endif // CUTE_TIMER_H
