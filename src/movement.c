#include "movement.h"

u8 determine_follower_state(struct npc_state *follower, u8 state, enum direction direction) {
	u8 new_state;
	
	switch (state) {
	case 0x10:
	case 0x11:
	case 0x12:
	case 0x13:
		new_state = 0x10 + direction;
		break;
	case 0x14:
	case 0x15:
	case 0x16:
	case 0x17:
		follower_state.delayed_state = 0x14;
		/* Don't allow delayed_state to be overwritten */
		return 0x10 + direction;
	case 0x3d:
	case 0x3E:
	case 0x3F:
	case 0x40:
		new_state = 0x3d + direction;
		break;
	default:
		return 0xFE;
	}

	if (follower_state.delayed_state) {
		new_state = follower_state.delayed_state;
		follower_state.delayed_state = 0;
	}
	
	return new_state;
}
