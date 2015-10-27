#include "npc.h"
#include "follow.h"
#include "util.h"

void handle_bike() {
	struct npc_state *follower = follower_npc_state();

	/* TODO: Read the npc state indices from somewhere! */
	if (walkrun_state.bitfield & 6) {
		/* Bike on */
		npc_change_sprite(follower, 8);
	} else {
		npc_change_sprite(follower, 7);
	}

	/* Update direction to prevent graphical glitches */
	npc_turn(follower, follower->direction);
}
