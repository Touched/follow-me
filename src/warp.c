#include "npc.h"
#include "follow.h"
#include "util.h"

void player_log_coordinates(struct npc_state *player);

void follower_avatar_init() {
	struct rom_npc *npc, clone;

	npc = rom_npc_by_local_id_and_map(1, 0, 3);

	/* Create in-memory copy of constant data */
	gf_memcpy(&clone, npc, sizeof(struct rom_npc));

	struct npc_state *player = player_npc_state();
	clone.x = player->to.x - 7;
	clone.y = player->to.y - 7;

	/* Create NPC and store ID */
	u8 npcid = npc_instanciation_something(&clone, 0, 3, 0, 0);
	follower_state.npcid = npcid;

	struct npc_state *follower = follower_npc_state();
	npc_make_invisible(follower);

	player_log_coordinates(player);
}

void stairs_move_follower(struct object *obj) {
	struct object *follower = &objects[follower_npc_state()->oam_id];
	follower->pos2.x = obj->pos2.x;
	follower->pos2.y = obj->pos2.y;
}
