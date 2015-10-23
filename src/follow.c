#include "types.h"
#include "npc.h"

void npc_half_reset(struct npc_state *);
int npc_set_state_2(struct npc_state *, u8);

struct npc_state *player_npc_state(void) {
	return &npc_states[walkrun_state.npcid];
}

void follow_me(struct npc_state *npc, u8 state) {
	if (player_npc_state() != npc) {
		return;
	}

	npc_half_reset(&npc_states[1]);
	npc_set_state_2(&npc_states[1], state);
}
