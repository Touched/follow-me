#include "movement.h"

bool state_is_movement(u8 state) {
	return state > 3;
}

#define RETURN_STATE(state) return new_state == MOVEMENT_INVALID ? state : new_state;

u8 determine_follower_state(struct npc_state *follower, u8 state, enum direction direction) {
	u8 new_state = MOVEMENT_INVALID;

	if ( state_is_movement(state) && follower_state.delayed_state) {
		new_state = follower_state.delayed_state + direction;
		follower_state.delayed_state = 0;
	}

	switch (state) {
	case 0x10:
	case 0x11:
	case 0x12:
	case 0x13:
		RETURN_STATE(0x10 + direction);
	case 0x14:
	case 0x15:
	case 0x16:
	case 0x17:
		follower_state.delayed_state = 0x14;
		RETURN_STATE(0x10 + direction);
	case 0x3d:
	case 0x3E:
	case 0x3F:
	case 0x40:
		RETURN_STATE(0x3d + direction);
	default:
		return 0xFE;
	}

	return new_state;
}
