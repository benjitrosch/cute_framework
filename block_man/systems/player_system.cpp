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

#include <systems/player_system.h>

#include <components/transform.h>
#include <components/animator.h>
#include <components/board_piece.h>
#include <components/player.h>

void set_player_animation_based_on_facing_direction(Player* player, Animator* animator)
{
	const char* animation = NULL;
	if (player->holding) {
		if (player->xdir) {
			animation = "hold_side";
		} else {
			if (player->ydir > 0) {
				animation = "hold_up";
			} else {
				animation = "hold_down";
			}
		}
	} else {
		if (player->xdir) {
			animation = "side";
		} else if (player->ydir) {
			if (player->ydir > 0) {
				animation = "up";
			} else {
				animation = "idle";
			}
		}
	}
	CUTE_ASSERT(animation);
	animator->sprite.play(animation);
}

void player_system_update(app_t* app, float dt, void* udata, Transform* transforms, Animator* animators, BoardPiece* board_pieces, Player* players, int entity_count)
{
	for (int i = 0; i < entity_count; ++i) {
		Transform* transform = transforms + i;
		Animator* animator = animators + i;
		BoardPiece* board_piece = board_pieces + i;
		Player* player = players + i;

		set_player_animation_based_on_facing_direction(player, animator);
	}
}
