#include "util.h"
#include "follow.h"

struct npc_state *player_npc_state(void) {
	return &npc_states[walkrun_state.npcid];
}

struct npc_state *follower_npc_state(void) {      
	return &npc_states[follower_state.npcid];
}

void npc_make_invisible(struct npc_state *npc) {
	npc->field1 |= 0x20u;
}

void npc_make_visible(struct npc_state *npc) {
	npc->field1 &= 0xDFu;
}

void follower_set_sprite(u8 sprite_index) {
	/* Save sprite */
	follower_state.current_sprite = sprite_index;
	
	struct npc_state *follower = follower_npc_state();
	npc_change_sprite(follower, follower_get_sprite());

	/* Update direction to prevent graphical glitches */
	npc_turn(follower, follower->direction);
}

u8 follower_get_sprite() {
	/* TODO: Make this not hardcoded and do bounds checking */
	static const u8 sprite_table[] = { 7, 8 };
	return sprite_table[follower_state.current_sprite];
}
