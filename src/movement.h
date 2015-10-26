#ifndef PKMN_MOVEMENT_H_
#define PKMN_MOVEMENT_H_

#define MOVEMENT_STATE_COUNT 0xA9
#define MOVEMENT_INVALID 0xFE

#include "follow.h"
#include "types.h"
#include "npc.h"

enum direction {
	DIR_DOWN,
	DIR_UP,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_NONE
};

bool state_is_movement(u8 state);
u8 determine_follower_state(struct npc_state *follower, u8 state, enum direction direction);

#endif /* PKMN_MOVEMENT_H_ */
