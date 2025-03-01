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

#ifndef CUTE_AUDIO_H
#define CUTE_AUDIO_H

#include "cute_defines.h"
#include "cute_multithreading.h"
#include "cute_result.h"

//--------------------------------------------------------------------------------------------------
// C API

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * @struct   CF_Audio
 * @category audio
 * @brief    An opaque pointer representing raw audio samples loaded as a resource.
 * @related  CF_Audio cf_audio_load_ogg cf_audio_load_ogg_from_memory cf_audio_load_wav cf_audio_load_wav_from_memory cf_audio_destroy cf_music_play cf_music_switch_to cf_music_crossfade cf_play_sound
 */
typedef struct CF_Audio CF_Audio;
// @end

/**
 * @function cf_audio_load_ogg
 * @category audio
 * @brief    Loads a .ogg audio file.
 * @param    path         The virtual path TODO_LINK to a .ogg file.
 * @return   Returns a pointer to `CF_Audio`. Free it up with `cf_audio_destroy` when done.
 * @related  CF_Audio cf_audio_load_ogg cf_audio_load_ogg_from_memory cf_audio_load_wav cf_audio_load_wav_from_memory cf_audio_destroy
 */
CUTE_API CF_Audio* CUTE_CALL cf_audio_load_ogg(const char* path);

/**
 * @function cf_audio_load_wav
 * @category audio
 * @brief    Loads a .wav audio file.
 * @param    path         The virtual path TODO_LINK to a .wav file.
 * @return   Returns a pointer to `CF_Audio`. Free it up with `cf_audio_destroy` when done.
 * @related  CF_Audio cf_audio_load_ogg cf_audio_load_ogg_from_memory cf_audio_load_wav cf_audio_load_wav_from_memory cf_audio_destroy
 */
CUTE_API CF_Audio* CUTE_CALL cf_audio_load_wav(const char* path);

/**
 * @function cf_audio_load_ogg_from_memory
 * @category audio
 * @brief    Loads a .ogg audio file from memory.
 * @param    memory       A buffer containing the bytes of a .ogg file.
 * @param    byte_count   The number of bytes in `memory`.
 * @return   Returns a pointer to `CF_Audio`. Free it up with `cf_audio_destroy` when done.
 * @related  CF_Audio cf_audio_load_ogg cf_audio_load_ogg_from_memory cf_audio_load_wav cf_audio_load_wav_from_memory cf_audio_destroy
 */
CUTE_API CF_Audio* CUTE_CALL cf_audio_load_ogg_from_memory(void* memory, int byte_count);

/**
 * @function cf_audio_load_wav_from_memory
 * @category audio
 * @brief    Loads a .wav audio file from memory.
 * @param    memory       A buffer containing the bytes of a .wav file.
 * @param    byte_count   The number of bytes in `memory`.
 * @return   Returns a pointer to `CF_Audio`. Free it up with `cf_audio_destroy` when done.
 * @related  CF_Audio cf_audio_load_ogg cf_audio_load_ogg_from_memory cf_audio_load_wav cf_audio_load_wav_from_memory cf_audio_destroy
 */
CUTE_API CF_Audio* CUTE_CALL cf_audio_load_wav_from_memory(void* memory, int byte_count);

/**
 * @function cf_audio_destroy
 * @category audio
 * @brief    Frees all resources used by a `CF_Audio`.
 * @param    audio        A pointer to the `CF_Audio`.
 * @related  CF_Audio cf_audio_load_ogg cf_audio_load_ogg_from_memory cf_audio_load_wav cf_audio_load_wav_from_memory cf_audio_destroy
 */
CUTE_API void CUTE_CALL cf_audio_destroy(CF_Audio* audio);

// -------------------------------------------------------------------------------------------------
// Global controls.

/**
 * @function cf_audio_set_pan
 * @category audio
 * @brief    Sets the global stereo pan for all audio.
 * @param    pan          0.5f means perfect balance for left/right speakers. 0.0f means only left speaker, 1.0f means only right speaker.
 * @related  cf_audio_set_pan cf_audio_set_global_volume cf_audio_set_sound_volume cf_audio_set_pause
 */
CUTE_API void CUTE_CALL cf_audio_set_pan(float pan);

/**
 * @function cf_audio_set_global_volume
 * @category audio
 * @brief    Sets the global volume for all audio.
 * @param    volume       A value from 0.0f to 1.0f, where 0.0f means no volume, and 1.0f means full volume.
 * @related  cf_audio_set_pan cf_audio_set_global_volume cf_audio_set_sound_volume cf_audio_set_pause
 */
CUTE_API void CUTE_CALL cf_audio_set_global_volume(float volume);

/**
 * @function cf_audio_set_sound_volume
 * @category audio
 * @brief    Sets the volume for all sound effects.
 * @param    volume       A value from 0.0f to 1.0f, where 0.0f means no volume, and 1.0f means full volume.
 * @remarks  Sounds come from `cf_play_sound`, as opposed to music coming from `cf_music_play`.
 * @related  cf_audio_set_pan cf_audio_set_global_volume cf_audio_set_sound_volume cf_audio_set_pause cf_play_sound
 */
CUTE_API void CUTE_CALL cf_audio_set_sound_volume(float volume);

/**
 * @function cf_audio_set_pause
 * @category audio
 * @brief    Pauses all audio.
 * @param    true_for_paused  True to pause all audio, false to unpause.
 * @related  cf_audio_set_pan cf_audio_set_global_volume cf_audio_set_sound_volume cf_audio_set_pause
 */
CUTE_API void CUTE_CALL cf_audio_set_pause(bool true_for_paused);

// -------------------------------------------------------------------------------------------------
// Music API.

/**
 * @function cf_music_play
 * @category audio
 * @brief    Plays audio as music.
 * @param    audio_source   A `CF_Audio` containing your music.
 * @param    fade_in_time   A number of seconds to fade the music in. Can be 0.0f to instantly play your music.
 * @related  cf_music_play cf_music_stop cf_music_set_volume cf_music_set_loop cf_music_pause cf_music_resume cf_music_switch_to cf_music_crossfade cf_music_get_sample_index cf_music_set_sample_index
 */
CUTE_API void CUTE_CALL cf_music_play(CF_Audio* audio_source, float fade_in_time);

/**
 * @function cf_music_stop
 * @category audio
 * @brief    Stop the music currently playing.
 * @param    fade_out_time  A number of seconds to fade the music out. Can be 0.0f to instantly stop your music.
 * @related  cf_music_play cf_music_stop cf_music_set_volume cf_music_set_loop cf_music_pause cf_music_resume cf_music_switch_to cf_music_crossfade cf_music_get_sample_index cf_music_set_sample_index
 */
CUTE_API void CUTE_CALL cf_music_stop(float fade_out_time);

/**
 * @function cf_music_set_volume
 * @category audio
 * @brief    Set the volume for music.
 * @param    volume         A value from 0.0f to 1.0f, where 0.0f means no volume, and 1.0f means full volume.
 * @related  cf_music_play cf_music_stop cf_music_set_volume cf_music_set_loop cf_music_pause cf_music_resume cf_music_switch_to cf_music_crossfade cf_music_get_sample_index cf_music_set_sample_index
 */
CUTE_API void CUTE_CALL cf_music_set_volume(float volume);

/**
 * @function cf_music_set_loop
 * @category audio
 * @brief    Turns on or off music looping.
 * @param    true_to_loop   True to loop the music.
 * @related  cf_music_play cf_music_stop cf_music_set_volume cf_music_set_loop cf_music_pause cf_music_resume cf_music_switch_to cf_music_crossfade cf_music_get_sample_index cf_music_set_sample_index
 */
CUTE_API void CUTE_CALL cf_music_set_loop(bool true_to_loop);

/**
 * @function cf_music_pause
 * @category audio
 * @brief    Pauses the music.
 * @related  cf_music_play cf_music_stop cf_music_set_volume cf_music_set_loop cf_music_pause cf_music_resume cf_music_switch_to cf_music_crossfade cf_music_get_sample_index cf_music_set_sample_index
 */
CUTE_API void CUTE_CALL cf_music_pause();

/**
 * @function cf_music_resume
 * @category audio
 * @brief    Resumes the music if the music was paused.
 * @related  cf_music_play cf_music_stop cf_music_set_volume cf_music_set_loop cf_music_pause cf_music_resume cf_music_switch_to cf_music_crossfade cf_music_get_sample_index cf_music_set_sample_index
 */
CUTE_API void CUTE_CALL cf_music_resume();

/**
 * @function cf_music_switch_to
 * @category audio
 * @brief    Switches from the currently playing music to another track.
 * @param    fade_out_time  A number of seconds to fade the currently playing track out. Can be 0.0f to instantly stop your music.
 * @param    fade_in_time   A number of seconds to fade the next track in. Can be 0.0f to instantly play your music.
 * @remarks  The currently playing track is faded out, then the second track is faded in.
 * @related  cf_music_play cf_music_stop cf_music_set_volume cf_music_set_loop cf_music_pause cf_music_resume cf_music_switch_to cf_music_crossfade cf_music_get_sample_index cf_music_set_sample_index
 */
CUTE_API void CUTE_CALL cf_music_switch_to(CF_Audio* audio_source, float fade_out_time, float fade_in_time);

/**
 * @function cf_music_crossfade
 * @category audio
 * @brief    Crossfades the currently playing track out with the next track in.
 * @param    cross_fade_time  A number of seconds to crossfade to the next track. Can be 0.0f to instantly switch to the next track.
 * @related  cf_music_play cf_music_stop cf_music_set_volume cf_music_set_loop cf_music_pause cf_music_resume cf_music_switch_to cf_music_crossfade cf_music_get_sample_index cf_music_set_sample_index
 */
CUTE_API void CUTE_CALL cf_music_crossfade(CF_Audio* audio_source, float cross_fade_time);

/**
 * @function cf_music_get_sample_index
 * @category audio
 * @brief    Returns the current sample index the music is playing at.
 * @remarks  This can be useful to sync a dynamic audio system that can turn on/off different instruments or sounds.
 * @related  cf_music_play cf_music_stop cf_music_set_volume cf_music_set_loop cf_music_pause cf_music_resume cf_music_switch_to cf_music_crossfade cf_music_get_sample_index cf_music_set_sample_index
 */
CUTE_API uint64_t CUTE_CALL cf_music_get_sample_index();

/**
 * @function cf_music_set_sample_index
 * @category audio
 * @brief    Sets the sample index to play at for the music.
 * @param    sample_index   Tells where to play music from within the `CF_Audio` for the currently playing music track.
 * @remarks  This can be useful to sync a dynamic audio system that can turn on/off different instruments or sounds.
 * @related  cf_music_play cf_music_stop cf_music_set_volume cf_music_set_loop cf_music_pause cf_music_resume cf_music_switch_to cf_music_crossfade cf_music_get_sample_index cf_music_set_sample_index
 */
CUTE_API CF_Result CUTE_CALL cf_music_set_sample_index(uint64_t sample_index);

// -------------------------------------------------------------------------------------------------
// Sound API.

/**
 * @struct   CF_SoundParams
 * @category audio
 * @brief    Parameters for the function `cf_play_sound`.
 * @remarks  You can use default settings from the `cf_sound_params_defaults` function.
 * @related  CF_SoundParams CF_Sound cf_sound_params_defaults cf_play_sound cf_sound_is_active cf_sound_get_is_paused cf_sound_get_is_looped cf_sound_get_volume cf_sound_get_sample_index cf_sound_set_sample_index cf_sound_set_is_paused cf_sound_set_is_looped cf_sound_set_volume
 */
typedef struct CF_SoundParams
{
	/* @member Default: false. True to start the sound in a paused state. False to start immediately playing the sound. */
	bool paused;

	/* @member Default: false. True to loop the sound. */
	bool looped;

	/* @member Default: 0.5f. A volume control from 0.0f to 1.0f. 0.0f meaning silent, 1.0f meaning max volume. */
	float volume;

	/* @member Default: 0.5f. A stereo pan control from 0.0f to 1.0f. 0.0f means left-speaker, 1.0f means right speaker, 0.5f means equal both. */
	float pan;

	/* @member Default: 0.0f. A number of seconds to wait before hearing the sound play. */
	float delay;
} CF_SoundParams;
// @end

/**
 * @struct   CF_Sound
 * @category audio
 * @brief    An opaque pointer representing a sound created by `cf_play_sound`.
 * @related  CF_SoundParams CF_Sound cf_sound_params_defaults cf_play_sound cf_sound_is_active cf_sound_get_is_paused cf_sound_get_is_looped cf_sound_get_volume cf_sound_get_sample_index cf_sound_set_sample_index cf_sound_set_is_paused cf_sound_set_is_looped cf_sound_set_volume
 */
typedef struct CF_Sound { uint64_t id; } CF_Sound;
// @end

/**
 * @function cf_sound_params_defaults
 * @category audio
 * @brief    Returns a `CF_SoundParams` filled with default state, to use with `cf_play_sound`.
 * @related  CF_SoundParams CF_Sound cf_sound_params_defaults cf_play_sound cf_sound_is_active cf_sound_get_is_paused cf_sound_get_is_looped cf_sound_get_volume cf_sound_get_sample_index cf_sound_set_sample_index cf_sound_set_is_paused cf_sound_set_is_looped cf_sound_set_volume
 */
CUTE_INLINE CF_SoundParams CUTE_CALL cf_sound_params_defaults()
{
	CF_SoundParams params;
	params.paused = false;
	params.looped = false;
	params.volume = 1.0f;
	params.pan = 0.5f;
	params.delay = 0;
	return params;
}

/**
 * @function cf_play_sound
 * @category audio
 * @brief    Plays a sound.
 * @param    audio_source   The `CF_Audio` samples for the sound to play.
 * @param    params         `CF_SoundParams` on how to play the sound. You can use default values by calling `cf_sound_params_defaults`.
 * @return   Returns a playing sound `CF_Sound`.
 * @related  CF_SoundParams CF_Sound cf_sound_params_defaults cf_play_sound cf_sound_is_active cf_sound_get_is_paused cf_sound_get_is_looped cf_sound_get_volume cf_sound_get_sample_index cf_sound_set_sample_index cf_sound_set_is_paused cf_sound_set_is_looped cf_sound_set_volume
 */
CUTE_API CF_Sound CUTE_CALL cf_play_sound(CF_Audio* audio_source, CF_SoundParams params);

/**
 * @function cf_sound_is_active
 * @category audio
 * @brief    Returns whether or not a sound is active.
 * @param    sound          The sound.
 * @return   Rreturns true if the sound is active, or false if it finished playing (and was not looped).
 * @related  CF_SoundParams CF_Sound cf_sound_params_defaults cf_play_sound cf_sound_is_active cf_sound_get_is_paused cf_sound_get_is_looped cf_sound_get_volume cf_sound_get_sample_index cf_sound_set_sample_index cf_sound_set_is_paused cf_sound_set_is_looped cf_sound_set_volume
 */
CUTE_API bool CUTE_CALL cf_sound_is_active(CF_Sound sound);

/**
 * @function cf_sound_get_is_paused
 * @category audio
 * @brief    Returns whether or not a sound is paused.
 * @param    sound          The sound.
 * @remarks  You can set a sound to paused with `cf_sound_set_is_paused`, or upon creation with `cf_play_sound`.
 * @related  CF_SoundParams CF_Sound cf_sound_params_defaults cf_play_sound cf_sound_is_active cf_sound_get_is_paused cf_sound_get_is_looped cf_sound_get_volume cf_sound_get_sample_index cf_sound_set_sample_index cf_sound_set_is_paused cf_sound_set_is_looped cf_sound_set_volume
 */
CUTE_API bool CUTE_CALL cf_sound_get_is_paused(CF_Sound sound);

/**
 * @function cf_sound_get_is_looped
 * @category audio
 * @brief    Returns whether or not a sound is looped.
 * @param    sound          The sound.
 * @remarks  You can set a sound to looped with `cf_sound_set_is_looped`, or upon creation with `cf_play_sound`.
 * @related  CF_SoundParams CF_Sound cf_sound_params_defaults cf_play_sound cf_sound_is_active cf_sound_get_is_paused cf_sound_get_is_looped cf_sound_get_volume cf_sound_get_sample_index cf_sound_set_sample_index cf_sound_set_is_paused cf_sound_set_is_looped cf_sound_set_volume
 */
CUTE_API bool CUTE_CALL cf_sound_get_is_looped(CF_Sound sound);

/**
 * @function cf_sound_get_volume
 * @category audio
 * @brief    Returns the volume of the sound.
 * @param    sound          The sound.
 * @remarks  You can set a sound volume with `cf_sound_set_volume`, or upon creation with `cf_play_sound`.
 * @related  CF_SoundParams CF_Sound cf_sound_params_defaults cf_play_sound cf_sound_is_active cf_sound_get_is_paused cf_sound_get_is_looped cf_sound_get_volume cf_sound_get_sample_index cf_sound_set_sample_index cf_sound_set_is_paused cf_sound_set_is_looped cf_sound_set_volume
 */
CUTE_API float CUTE_CALL cf_sound_get_volume(CF_Sound sound);

/**
 * @function cf_sound_get_sample_index
 * @category audio
 * @brief    Returns the index of the currently playing sample for the sound.
 * @param    sound          The sound.
 * @remarks  You can set a sound's playing index with `cf_sound_set_sample_index`. This can be useful to sync a dynamic audio system that
 *           can turn on/off different instruments or sounds.
 * @related  CF_SoundParams CF_Sound cf_sound_params_defaults cf_play_sound cf_sound_is_active cf_sound_get_is_paused cf_sound_get_is_looped cf_sound_get_volume cf_sound_get_sample_index cf_sound_set_sample_index cf_sound_set_is_paused cf_sound_set_is_looped cf_sound_set_volume
 */
CUTE_API uint64_t CUTE_CALL cf_sound_get_sample_index(CF_Sound sound);

/**
 * @function cf_sound_set_is_paused
 * @category audio
 * @brief    Sets the paused state for the sound.
 * @param    sound            The sound.
 * @param    true_for_paused  The pause state to set.
 * @remarks  You can get a sound's paused state with `cf_sound_get_is_paused`.
 * @related  CF_SoundParams CF_Sound cf_sound_params_defaults cf_play_sound cf_sound_is_active cf_sound_get_is_paused cf_sound_get_is_looped cf_sound_get_volume cf_sound_get_sample_index cf_sound_set_sample_index cf_sound_set_is_paused cf_sound_set_is_looped cf_sound_set_volume
 */
CUTE_API void CUTE_CALL cf_sound_set_is_paused(CF_Sound sound, bool true_for_paused);

/**
 * @function cf_sound_set_is_looped
 * @category audio
 * @brief    Sets the looped state for the sound.
 * @param    sound            The sound.
 * @param    true_for_looped  The loop state to set.
 * @remarks  You can get a sound's looped state with `cf_sound_get_is_looped`.
 * @related  CF_SoundParams CF_Sound cf_sound_params_defaults cf_play_sound cf_sound_is_active cf_sound_get_is_paused cf_sound_get_is_looped cf_sound_get_volume cf_sound_get_sample_index cf_sound_set_sample_index cf_sound_set_is_paused cf_sound_set_is_looped cf_sound_set_volume
 */
CUTE_API void CUTE_CALL cf_sound_set_is_looped(CF_Sound sound, bool true_for_looped);

/**
 * @function cf_sound_set_volume
 * @category audio
 * @brief    Sets the volume for the sound.
 * @param    sound      The sound.
 * @param    volume     A value from 0.0f to 1.0f. 0.0f meaning silent, 1.0f meaning max volume.
 * @remarks  You can get a sound's volume with `cf_sound_get_volume`.
 * @related  CF_SoundParams CF_Sound cf_sound_params_defaults cf_play_sound cf_sound_is_active cf_sound_get_is_paused cf_sound_get_is_looped cf_sound_get_volume cf_sound_get_sample_index cf_sound_set_sample_index cf_sound_set_is_paused cf_sound_set_is_looped cf_sound_set_volume
 */
CUTE_API void CUTE_CALL cf_sound_set_volume(CF_Sound sound, float volume);

/**
 * @function cf_sound_set_sample_index
 * @category audio
 * @brief    Sets the sample index for the sound to control which sample to play next.
 * @param    sound         The sound.
 * @param    sample_index  The index of the sample to play the sound from.
 * @remarks  You can get a sound's playing index with `cf_sound_get_sample_index`. This can be useful to sync a dynamic audio system that
 *           can turn on/off different instruments or sounds.
 * @related  CF_SoundParams CF_Sound cf_sound_params_defaults cf_play_sound cf_sound_is_active cf_sound_get_is_paused cf_sound_get_is_looped cf_sound_get_volume cf_sound_get_sample_index cf_sound_set_sample_index cf_sound_set_is_paused cf_sound_set_is_looped cf_sound_set_volume
 */
CUTE_API void CUTE_CALL cf_sound_set_sample_index(CF_Sound sound, uint64_t sample_index);

#ifdef __cplusplus
}
#endif // __cplusplus

//--------------------------------------------------------------------------------------------------
// C++ API

#ifdef CUTE_CPP

namespace Cute
{

using Audio = CF_Audio;

struct SoundParams : public CF_SoundParams
{
	SoundParams() { *(CF_SoundParams*)this = cf_sound_params_defaults(); }
	SoundParams(CF_SoundParams sp) { *(CF_SoundParams*)this = sp; }
};

struct Sound : public CF_Sound
{
	Sound() { id = -1; }
	Sound(CF_Sound s) { *(CF_Sound*)this = s; }
};

CUTE_INLINE Audio* audio_load_ogg(const char* path = NULL) { return cf_audio_load_ogg(path); }
CUTE_INLINE Audio* audio_load_wav(const char* path = NULL) { return cf_audio_load_wav(path); }
CUTE_INLINE Audio* audio_load_ogg_from_memory(void* memory, int byte_count) { return cf_audio_load_ogg_from_memory(memory, byte_count); }
CUTE_INLINE Audio* audio_load_wav_from_memory(void* memory, int byte_count) { return cf_audio_load_wav_from_memory(memory, byte_count); }
CUTE_INLINE void audio_destroy(Audio* audio) { cf_audio_destroy(audio); }

// -------------------------------------------------------------------------------------------------

CUTE_INLINE void audio_set_pan(float pan) { cf_audio_set_pan(pan); }
CUTE_INLINE void audio_set_global_volume(float volume) { cf_audio_set_global_volume(volume); }
CUTE_INLINE void audio_set_sound_volume(float volume) { cf_audio_set_sound_volume(volume); }
CUTE_INLINE void audio_set_pause(bool true_for_paused) { cf_audio_set_pause(true_for_paused); }

// -------------------------------------------------------------------------------------------------

CUTE_INLINE void music_play(Audio* audio_source, float fade_in_time = 0) { cf_music_play(audio_source, fade_in_time); }
CUTE_INLINE void music_stop(float fade_out_time = 0) { cf_music_stop(fade_out_time = 0); }
CUTE_INLINE void music_set_volume(float volume) { cf_music_set_volume(volume); }
CUTE_INLINE void music_set_loop(bool true_to_loop) { cf_music_set_loop(true_to_loop); }
CUTE_INLINE void music_pause() { cf_music_pause(); }
CUTE_INLINE void music_resume() { cf_music_resume(); }
CUTE_INLINE void music_switch_to(Audio* audio_source, float fade_out_time = 0, float fade_in_time = 0) { cf_music_switch_to(audio_source, fade_out_time, fade_in_time); }
CUTE_INLINE void music_crossfade(Audio* audio_source, float cross_fade_time = 0) { cf_music_crossfade(audio_source, cross_fade_time); }
CUTE_INLINE void music_set_sample_index(uint64_t sample_index) { cf_music_set_sample_index(sample_index); }
CUTE_INLINE uint64_t music_get_sample_index() { return cf_music_get_sample_index(); }

// -------------------------------------------------------------------------------------------------

CUTE_INLINE Sound sound_play(Audio* audio_source, SoundParams params = SoundParams()) { return cf_play_sound(audio_source, params); }

CUTE_INLINE bool sound_is_active(Sound sound) { return cf_sound_is_active(sound); }
CUTE_INLINE bool sound_get_is_paused(Sound sound) { return cf_sound_get_is_paused(sound); }
CUTE_INLINE bool sound_get_is_looped(Sound sound) { return cf_sound_get_is_looped(sound); }
CUTE_INLINE float sound_get_volume(Sound sound) { return cf_sound_get_volume(sound); }
CUTE_INLINE uint64_t sound_get_sample_index(Sound sound) { return cf_sound_get_sample_index(sound); }
CUTE_INLINE void sound_set_is_paused(Sound sound, bool true_for_paused) { cf_sound_set_is_paused(sound, true_for_paused); }
CUTE_INLINE void sound_set_is_looped(Sound sound, bool true_for_looped) { cf_sound_set_is_looped(sound, true_for_looped); }
CUTE_INLINE void sound_set_volume(Sound sound, float volume) { cf_sound_set_volume(sound, volume); }
CUTE_INLINE void sound_set_sample_index(Sound sound, int sample_index) { cf_sound_set_sample_index(sound, sample_index); }

}

#endif // CUTE_CPP

#endif // CUTE_AUDIO_H
