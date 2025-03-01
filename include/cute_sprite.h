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

#ifndef CUTE_SPRITE_H
#define CUTE_SPRITE_H

#include "cute_defines.h"
#include "cute_array.h"
#include "cute_hashtable.h"
#include "cute_string.h"
#include "cute_math.h"
#include "cute_time.h"

//--------------------------------------------------------------------------------------------------
// C API

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @struct   CF_Frame
 * @category sprite
 * @brief    Represents one frame of animation within a sprite.
 * @related  CF_Frame CF_Animation CF_Sprite
 */
typedef struct CF_Frame
{
	/* @member Unique identifier for this frame's image. */
	uint64_t id;

	/* @member Number of seconds to display this frame. */
	float delay;
} CF_Frame;
// @end

/**
 * @enum     CF_PlayDirection
 * @category sprite
 * @brief    The direction a sprite plays frames.
 * @related  CF_PlayDirection cf_play_direction_to_string CF_Animation
 */
#define CF_PLAY_DIRECTION_DEFS \
	/* @entry Flips through the frames of an animation forwards. */ \
	CF_ENUM(PLAY_DIRECTION_FORWARDS, 0) \
	/* @entry Flips through the frames of an animation backwards. */ \
	CF_ENUM(PLAY_DIRECTION_BACKWARDS, 1) \
	/* @entry Flips through the frames of an animation forwards, then backwards, repeating. */ \
	CF_ENUM(PLAY_DIRECTION_PINGPONG, 2) \
	/* @end */

typedef enum CF_PlayDirection
{
	#define CF_ENUM(K, V) CF_##K = V,
	CF_PLAY_DIRECTION_DEFS
	#undef CF_ENUM
} CF_PlayDirection;

/**
 * @function cf_play_direction_to_string
 * @category sprite
 * @brief    Returns a `CF_PlayDirection` converted to a C string.
 * @related  CF_PlayDirection cf_play_direction_to_string CF_Animation
 */
CUTE_INLINE const char* cf_play_direction_to_string(CF_PlayDirection dir)
{
	switch (dir) {
	#define CF_ENUM(K, V) case CF_##K: return CUTE_STRINGIZE(CF_##K);
	CF_PLAY_DIRECTION_DEFS
	#undef CF_ENUM
	default: return NULL;
	}
}

/**
 * @struct   CF_Animation
 * @category sprite
 * @brief    A named set of frames in sequence.
 * @related  CF_Frame CF_Animation CF_Sprite
 */
typedef struct CF_Animation
{
	/* The name of the animation. */
	const char* name;

	/* The direction to play the animation. See `CF_PlayDirection`. */
	CF_PlayDirection play_direction;

	/* The frames of the animation. See `dyna`. */
	dyna CF_Frame* frames;
} CF_Animation;
// @end

/**
 * @struct   CF_Sprite
 * @category sprite
 * @brief    A sprite represents a drawable entity, made of 2D animations/images.
 * @remarks  TODO
 * @related  CF_Frame CF_Animation CF_Sprite cf_make_easy_sprite cf_make_sprite
 */
typedef struct CF_Sprite
{
	/* @member The name of the sprite. */
	const char* name;

	/* @member Width of the sprite in pixels. */
	int w;

	/* @member Height of the sprite in pixels. */
	int h;

	/* @member Scale factor for the sprite when drawing. Default of `(1, 1)`. See `cf_draw_sprite`. */
	CF_V2 scale;

	/* @member A local offset/origin for the sprite when drawing. See `cf_draw_sprite`. */
	CF_V2 local_offset;

	/* @member An opacity value for the entire sprite. Default of 1.0f. See `cf_draw_sprite`. */
	float opacity;

	/* @member The current frame within `animation` to display. */
	int frame_index;

	/* @member The number of times this sprite has completed an animation. */
	int loop_count;

	/* @member A speed multiplier for updating frames. Default of 1.0f. */
	float play_speed_multiplier;

	/* @member A pointer to the current animation to display, from within the set `animations`. See `CF_Animation`. */
	const CF_Animation* animation;

	/* @member Whether or not to pause updates to the animation. */
	bool paused;

	/* @member The current elapsed time within a frame of animation. */
	float t;

	/* @member The set of named animations for this sprite. See `CF_Animation` and `htbl`. */
	htbl const CF_Animation** animations;

	/* @member An optional transform for rendering within a particular space. See `CF_Transform`. */
	CF_Transform transform;
} CF_Sprite;
// @end

/**
 * @function cf_sprite_defaults
 * @category sprite
 * @brief    Returns an empty sprite.
 * @remarks  Empty sprites can not be drawn. You probably don't want this function unless you know what you're doing, instead,
 *           you may be looking for `cf_make_sprite` or `cf_make_easy_sprite`.
 * @related  CF_Sprite cf_sprite_defaults cf_make_easy_sprite cf_make_sprite
 */
CUTE_INLINE CF_Sprite cf_sprite_defaults()
{
	CF_Sprite sprite = { 0 };
	sprite.scale = cf_v2(1, 1);
	sprite.opacity = 1.0f;
	sprite.play_speed_multiplier = 1.0f;
	sprite.transform = cf_make_transform();
	return sprite;
}

/**
 * @function cf_make_easy_sprite
 * @category sprite
 * @brief    Loads a single-frame sprite from a single png file.
 * @param    png_path     Virtual path to the .png file.
 * @return   Returns a `CF_Sprite` that can be drawn with `cf_sprite_draw`. The sprite is not animated,
 *           as it's only a single-frame made from a png file.
 * @remarks  The preferred way to make a sprite is `cf_make_sprite`, but this function provides a very simple way to get started
 *           by merely loading a single .png image, or for games that don't require animations. TODO - LINK_TO_VFS_TUTORIAL.
 * @related  CF_Sprite cf_make_easy_sprite cf_make_sprite
 */
CUTE_API CF_Sprite CUTE_CALL cf_make_easy_sprite(const char* png_path);

/**
 * @function cf_make_sprite
 * @category sprite
 * @brief    Loads a sprite from an aseprite file.
 * @param    aseprite_path  Virtual path to a .ase file.
 * @return   Returns a `CF_Sprite` that can be drawn with `cf_sprite_draw`.
 * @remarks  This function caches the sprite internally. Subsequent calls to load the same sprite will be very fast; you can use
 *           this function directly to fetch sprites that were already loaded. If you want to load sprites with your own custom
 *           animation data, instead of using the .ase/.aseprite format, you can try out `cf_png_cache_load` for a more low-level option.
 *           TODO - LINK_TO_VFS_TUTORIAL.
 * @related  CF_Sprite cf_make_sprite cf_sprite_unload
 */
CUTE_API CF_Sprite CUTE_CALL cf_make_sprite(const char* aseprite_path);

/**
 * @function cf_sprite_unload
 * @category sprite
 * @brief    Unloads the sprite's image resources from the internal cache.
 * @param    aseprite_path  Virtual path to a .ase file.
 * @remarks  Any live `CF_Sprite` instances for `aseprite_path` will now by "dangling". TODO - LINK_TO_VFS_TUTORIAL.
 * @related  CF_Sprite cf_make_sprite cf_sprite_unload
 */
CUTE_API void CUTE_CALL cf_sprite_unload(const char* aseprite_path);

//--------------------------------------------------------------------------------------------------
// In-line implementation of `CF_Sprite` functions.

CUTE_API void CUTE_CALL cf_draw_sprite(const CF_Sprite* sprite);

CUTE_INLINE void cf_sprite_draw(CF_Sprite* sprite)
{
	cf_draw_sprite(sprite);
}

/**
 * @function cf_sprite_update
 * @category sprite
 * @brief    Updates a sprite's animation.
 * @param    sprite     The sprite.
 * @remarks  Call this once per frame.
 * @related  CF_Sprite cf_make_sprite cf_sprite_update cf_sprite_play cf_sprite_pause
 */
CUTE_INLINE void cf_sprite_update(CF_Sprite* sprite)
{
	if (sprite->paused) return;

	sprite->t += CF_DELTA_TIME * sprite->play_speed_multiplier;
	if (sprite->t >= sprite->animation->frames[sprite->frame_index].delay) {
		sprite->frame_index++;
		if (sprite->frame_index == alen(sprite->animation->frames)) {
			sprite->loop_count++;
			sprite->frame_index = 0;
		}

		sprite->t = 0;

		// TODO - Backwards and pingpong.
	}
}

/**
 * @function cf_sprite_reset
 * @category sprite
 * @brief    Resets the currently playing animation and unpauses the animation.
 * @param    sprite     The sprite.
 * @related  CF_Sprite cf_sprite_update cf_sprite_play
 */
CUTE_INLINE void cf_sprite_reset(CF_Sprite* sprite)
{
	sprite->paused = false;
	sprite->frame_index = 0;
	sprite->loop_count = 0;
	sprite->t = 0;
}

/**
 * @function cf_sprite_play
 * @category sprite
 * @brief    Switches to a new aninmation and starts playing it from the beginning.
 * @param    sprite     The sprite.
 * @param    animation  Name of the animation to switch to and start playing.
 * @related  CF_Sprite cf_sprite_update cf_sprite_play cf_sprite_is_playing
 */
CUTE_INLINE void cf_sprite_play(CF_Sprite* sprite, const char* animation)
{
	sprite->animation = hfind(sprite->animations, sintern(animation));
	CUTE_ASSERT(sprite->animation);
	cf_sprite_reset(sprite);
}

/**
 * @function cf_sprite_is_playing
 * @category sprite
 * @brief    Returns true if `animation` the is currently playing animation.
 * @param    sprite     The sprite.
 * @param    animation  Name of the animation.
 * @related  CF_Sprite cf_sprite_update cf_sprite_play cf_sprite_is_playing
 */
CUTE_INLINE bool cf_sprite_is_playing(CF_Sprite* sprite, const char* animation)
{
	return !CUTE_STRCMP(animation, sprite->animation->name);
}

/**
 * @function cf_sprite_pause
 * @category sprite
 * @brief    Pauses the sprite's animation.
 * @param    sprite     The sprite.
 * @related  CF_Sprite cf_sprite_update cf_sprite_play cf_sprite_pause cf_sprite_unpause cf_sprite_toggle_pause
 */
CUTE_INLINE void cf_sprite_pause(CF_Sprite* sprite)
{
	sprite->paused = true;
}

/**
 * @function cf_sprite_unpause
 * @category sprite
 * @brief    Unpauses the sprite's animation.
 * @param    sprite     The sprite.
 * @related  CF_Sprite cf_sprite_update cf_sprite_play cf_sprite_pause cf_sprite_unpause cf_sprite_toggle_pause
 */
CUTE_INLINE void cf_sprite_unpause(CF_Sprite* sprite)
{
	sprite->paused = false;
}

/**
 * @function cf_sprite_toggle_pause
 * @category sprite
 * @brief    Toggles the sprite's pause state.
 * @param    sprite     The sprite.
 * @related  CF_Sprite cf_sprite_update cf_sprite_play cf_sprite_pause cf_sprite_unpause cf_sprite_toggle_pause
 */
CUTE_INLINE void cf_sprite_toggle_pause(CF_Sprite* sprite)
{
	sprite->paused = !sprite->paused;
}

/**
 * @function cf_sprite_flip_x
 * @category sprite
 * @brief    Flip's the sprite on the x-axis.
 * @param    sprite     The sprite.
 * @remarks  Works by flipping the sign of the sprite's scale on the x-axis.
 * @related  CF_Sprite cf_sprite_flip_x cf_sprite_flip_y
 */
CUTE_INLINE void cf_sprite_flip_x(CF_Sprite* sprite)
{
	sprite->scale.x *= -1.0f;
}

/**
 * @function cf_sprite_flip_y
 * @category sprite
 * @brief    Flip's the sprite on the y-axis.
 * @param    sprite     The sprite.
 * @remarks  Works by flipping the sign of the sprite's scale on the y-axis.
 * @related  CF_Sprite cf_sprite_flip_x cf_sprite_flip_y
 */
CUTE_INLINE void cf_sprite_flip_y(CF_Sprite* sprite)
{
	sprite->scale.y *= -1.0f;
}

/**
 * @function cf_sprite_frame_count
 * @category sprite
 * @brief    Returns the number of frames in the sprite's currently playing animation.
 * @param    sprite     The sprite.
 * @related  CF_Sprite cf_sprite_frame_count cf_sprite_current_frame cf_sprite_frame_delay cf_sprite_animation_delay
 */
CUTE_INLINE int cf_sprite_frame_count(const CF_Sprite* sprite)
{
	return alen(sprite->animation);
}

/**
 * @function cf_sprite_current_frame
 * @category sprite
 * @brief    Returns the index of the currently playing frame.
 * @param    sprite     The sprite.
 * @related  CF_Sprite cf_sprite_frame_count cf_sprite_current_frame cf_sprite_frame_delay cf_sprite_animation_delay
 */
CUTE_INLINE int cf_sprite_current_frame(const CF_Sprite* sprite)
{
	return sprite->frame_index;
}

/**
 * @function cf_sprite_frame_delay
 * @category sprite
 * @brief    Returns the `delay` member of the currently playing frame, in milliseconds.
 * @param    sprite     The sprite.
 * @related  CF_Sprite CF_Frame cf_sprite_frame_count cf_sprite_current_frame cf_sprite_frame_delay cf_sprite_animation_delay cf_sprite_animation_interpolant
 */
CUTE_INLINE float cf_sprite_frame_delay(CF_Sprite* sprite)
{
	return sprite->animation->frames[sprite->frame_index].delay;
}

/**
 * @function cf_sprite_animation_delay
 * @category sprite
 * @brief    Sums all the delays of each frame in the animation, and returns the total, in milliseconds.
 * @param    sprite     The sprite.
 * @related  CF_Sprite CF_Frame CF_Animation cf_sprite_frame_count cf_sprite_current_frame cf_sprite_frame_delay cf_sprite_animation_delay cf_sprite_animation_interpolant
 */
CUTE_INLINE float cf_sprite_animation_delay(CF_Sprite* sprite)
{
	int count = cf_sprite_frame_count(sprite);
	float delay = 0;
	for (int i = 0; i < count; ++i) {
		delay += sprite->animation->frames[i].delay;
	}
	return delay;
}

/**
 * @function cf_sprite_animation_interpolant
 * @category sprite
 * @brief    Returns a value from 0 to 1 representing how far along the animation has played.
 * @param    sprite     The sprite.
 * @remarks  0 means just started, while 1 means finished.
 * @related  CF_Sprite CF_Frame CF_Animation cf_sprite_frame_count cf_sprite_current_frame cf_sprite_frame_delay cf_sprite_animation_delay
 */
CUTE_INLINE float cf_sprite_animation_interpolant(CF_Sprite* sprite)
{
	// TODO -- Backwards and pingpong.
	float delay = cf_sprite_animation_delay(sprite);
	float t = sprite->t + sprite->animation->frames[sprite->frame_index].delay * sprite->frame_index;
	return cf_clamp(t / delay, 0.0f, 1.0f);
}

/**
 * @function cf_sprite_will_finish
 * @category sprite
 * @brief    Returns true if the animation will loop around and finish if `cf_sprite_update` is called.
 * @param    sprite     The sprite.
 * @remarks  This is useful to see if you're currently on the last frame of animation, and will finish in this particular update.
 * @related  CF_Sprite cf_sprite_frame_count cf_sprite_current_frame cf_sprite_frame_delay cf_sprite_animation_delay cf_sprite_will_finish
 */
CUTE_INLINE bool cf_sprite_will_finish(CF_Sprite* sprite)
{
	// TODO -- Backwards and pingpong.
	if (sprite->frame_index == cf_sprite_frame_count(sprite) - 1) {
		return sprite->t + CF_DELTA_TIME * sprite->play_speed_multiplier >= sprite->animation->frames[sprite->frame_index].delay;
	} else {
		return false;
	}
}

/**
 * @function cf_sprite_on_loop
 * @category sprite
 * @brief    Returns true whenever at the very beginning of the animation sequence.
 * @param    sprite     The sprite.
 * @remarks  This is useful for polling on when the animation restarts itself, for example, polling within an if-statement each game tick.
 * @related  CF_Sprite cf_sprite_frame_count cf_sprite_current_frame cf_sprite_frame_delay cf_sprite_animation_delay cf_sprite_will_finish
 */
CUTE_INLINE bool cf_sprite_on_loop(CF_Sprite* sprite)
{
	if (sprite->frame_index == 0 && sprite->t == 0) {
		return true;
	} else {
		return false;
	}
}

/**
 * @function cf_animation_add_frame
 * @category sprite
 * @brief    Adds a frame to an animation.
 * @param    animation   The sprite.
 * @param    frame       The frame.
 * @remarks  You can use this function to build your own animations in a custom manner. It's recommend to just use `cf_make_sprite`, which
 *           loads a full sprite out of a .ase file. But, this function provides another low-level option if desired.
 * @related  CF_Sprite CF_Animation CF_Frame dyna htbl
 */
CUTE_INLINE void cf_animation_add_frame(CF_Animation* animation, CF_Frame frame) { apush(animation->frames, frame); }

#ifdef __cplusplus
}
#endif // __cplusplus

//--------------------------------------------------------------------------------------------------
// C++ API

#ifdef CUTE_CPP

namespace Cute
{

using frame_t = CF_Frame;
using animation_t = CF_Animation;

using PlayDirection = CF_PlayDirection;
#define CF_ENUM(K, V) CUTE_INLINE constexpr PlayDirection K = CF_##K;
CF_PLAY_DIRECTION_DEFS
#undef CF_ENUM

CUTE_INLINE const char* to_string(PlayDirection dir)
{
	switch (dir) {
	#define CF_ENUM(K, V) case CF_##K: return #K;
	CF_PLAY_DIRECTION_DEFS
	#undef CF_ENUM
	default: return NULL;
	}
}

struct Sprite : public CF_Sprite
{
	Sprite() { *(CF_Sprite*)this = cf_sprite_defaults(); }
	Sprite(CF_Sprite s) { *(CF_Sprite*)this = s; }

	CUTE_INLINE void draw() { cf_sprite_draw(this); }
	CUTE_INLINE void update() { return cf_sprite_update(this); }
	CUTE_INLINE void play(const char* animation) { return cf_sprite_play(this, animation); }
	CUTE_INLINE bool is_playing(const char* animation) { return cf_sprite_is_playing(this, animation); }
	CUTE_INLINE void reset() { return cf_sprite_reset(this); }
	CUTE_INLINE void pause() { return cf_sprite_pause(this); }
	CUTE_INLINE void unpause() { return cf_sprite_unpause(this); }
	CUTE_INLINE void toggle_pause() { return cf_sprite_toggle_pause(this); }
	CUTE_INLINE void flip_x() { return cf_sprite_flip_x(this); }
	CUTE_INLINE void flip_y() { return cf_sprite_flip_y(this); }
	CUTE_INLINE int frame_count() const { return cf_sprite_frame_count(this); }
	CUTE_INLINE int current_frame() const { return cf_sprite_current_frame(this); }
	CUTE_INLINE float frame_delay() { return cf_sprite_frame_delay(this); }
	CUTE_INLINE float animation_delay() { return cf_sprite_animation_delay(this); }
	CUTE_INLINE float animation_interpolant() { return cf_sprite_animation_interpolant(this); }
	CUTE_INLINE bool will_finish() { return cf_sprite_will_finish(this); }
	CUTE_INLINE bool on_loop() { return cf_sprite_on_loop(this); }
};

CUTE_INLINE Sprite easy_make_sprite(const char* png_path) { return cf_make_easy_sprite(png_path); }
CUTE_INLINE Sprite make_sprite(const char* aseprite_path) { return cf_make_sprite(aseprite_path); }
CUTE_INLINE void sprite_unload(const char* aseprite_path) { cf_sprite_unload(aseprite_path); }

}

#endif // CUTE_CPP

#endif // CUTE_SPRITE_H
