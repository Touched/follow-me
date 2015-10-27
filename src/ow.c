#include "npc.h"
#include "follow.h"
#include "util.h"

void handle_bike() {
	if (walkrun_state.bitfield & 6) {
		/* Bike on */
		follower_set_sprite(1);
	} else {
		follower_set_sprite(0);
	}
}
