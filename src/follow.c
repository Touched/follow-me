#include "types.h"
#include "npc.h"
#include "follow.h"
#include "movement.h"
#include "util.h"

enum direction determine_direction(struct npc_state *player, struct npc_state *follower) {
	s8 delta_x = follower->to.x - player->to.x;
	s8 delta_y = follower->to.y - player->to.y;

	if (delta_x < 0) {
		return DIR_RIGHT;
	} else if (delta_x > 0) {
		return DIR_LEFT;
	}

	if (delta_y < 0) {
		return DIR_DOWN;
	} else if (delta_y > 0) {
		return DIR_UP;
	}

	return DIR_NONE;
}

u8 set_follower_npcid(u8 npcid) {
	follower_state.npcid = npcid;
	return npcid;
}

void follow_me(struct npc_state *npc, u8 state) {
	struct npc_state *follower = follower_npc_state(),
		*player = player_npc_state();

	if (player != npc) {
		return;
	}

	enum direction dir = determine_direction(player, follower);

	if (dir == DIR_NONE) {
		goto reset;
	}

	u8 new_state = determine_follower_state(follower, state, dir);

	if (new_state == MOVEMENT_INVALID) {
		goto reset;
	}

	npc_half_reset(follower);
	npc_set_state_2(follower, new_state);

reset:
	npc_half_reset_when_bit7_is_set(follower);
}

bool collision_exempt(struct npc_state *obstacle, struct npc_state *collider) {
	struct npc_state *follower = follower_npc_state(),
		*player = player_npc_state();

	if (follower != obstacle || player != collider) {
		return 0;
	}

	return 1;
}
