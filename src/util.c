#include "util.h"
#include "follow.h"

struct npc_state *player_npc_state(void) {
	return &npc_states[walkrun_state.npcid];
}

struct npc_state *follower_npc_state(void) {      
	return &npc_states[follower_state.npcid];
}
