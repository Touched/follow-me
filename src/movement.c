#include "movement.h"

bool state_is_movement(u8 state) {
	return state > 3;
}

#define RETURN_STATE(state) return new_state == MOVEMENT_INVALID ? state : new_state;

/* 
 * TODO: Some of the below movements assume the action was caused by
 * certain tiles. We might need to create modes that don't have this 
 * assumption for applymovement scripts, etc.
 */

u8 determine_follower_state(struct npc_state *follower, u8 state, enum direction direction) {
	u8 new_state = MOVEMENT_INVALID;

	if ( state_is_movement(state) && follower_state.delayed_state) {
		new_state = follower_state.delayed_state + direction;
		follower_state.delayed_state = 0;
	}

	/* Clear ice tile stuff */
	follower->field1 &= 0xFB; 

	switch (state) {
	case 0x08:
	case 0x09:
	case 0x0A:
	case 0x0B:
		/* Slow walk */
		RETURN_STATE(0x8 + direction);
	case 0x0C:
	case 0x0D:
	case 0x0E:
	case 0x0F:
		/* Slow slow */
		RETURN_STATE(0xC + direction);		
	case 0x10:
	case 0x11:
	case 0x12:
	case 0x13:
		/* Normal walk */
		RETURN_STATE(0x10 + direction);
	case 0x14:
	case 0x15:
	case 0x16:
	case 0x17:
		/* Ledge jump */
		follower_state.delayed_state = 0x14;
		RETURN_STATE(0x10 + direction);
        case 0x1d:
        case 0x1e:
        case 0x1f:
        case 0x20:
		/* 
		 * Handle ice tile (some walking animation)
		 * Set a bit to freeze the follower's animation
		 * FIXME: Use a hook (at 08063E28) to set this bit
		 */
		follower->field1 |= 0x4;
		RETURN_STATE(0x1d + direction);
	case 0x3d:
	case 0x3E:
	case 0x3F:
	case 0x40:
		/* Running frames */
		RETURN_STATE(0x3d + direction);
	case 0x31:
	case 0x32:
	case 0x33:
	case 0x34:
		/* Bike speed */
		RETURN_STATE(0x31 + direction);
	case 0x41:
	case 0x42:
	case 0x43:
	case 0x44:
		/* 
		 * Stairs (slow walking)
		 * Running sideways on stairs does not use the slow
		 * frames, so split this into two. 
		 */
		if (direction < 2) {
			RETURN_STATE(0x41 + direction);
		} else {
			RETURN_STATE(0x3d + direction);
		}
	case 0x94:
	case 0x95:
	case 0x96:
	case 0x97:
		/* Warp pad spinning movement */
		RETURN_STATE(0x94 + direction);
	case 0x46:
	case 0x47:
	case 0x48:
	case 0x49:
		RETURN_STATE(0x46 + direction);
	default:
		return 0xFE;
	}

	return new_state;
}
