#ifndef PKMN_NPC_H_
#define PKMN_NPC_H_

#include "objects.h"

struct npc_state {
	u8 bitfield;
	u8 field1;
	u8 field2;
	u8 field3;
	u8 oam_id;
	u8 type_id;
	u8 running_behavior;
	u8 is_trainer;
	u8 local_id;
	u8 local_map_number;
	u8 local_map_bank;
	u8 height;
	struct coords16 stay_around;
	struct coords16 to;
	struct coords16 from;
	u8 direction;
	u8 movement_area;
	u8 field1A;
	u8 oamid2;
	u8 state; 		/* an_index */
	u8 sight_distance;
	u8 tile_to;
	u8 tile_from;
	u8 field20;
	u8 field21;
	u8 field22;
	u8 field23;
};

struct walkrun {
	u8 bitfield;
	u8 bike;
	u8 running2;
	u8 running1;
	u8 oamid;
	u8 npcid;
	u8 lock;
	u8 gender;
	u8 xmode;
	u8 field9;
	u8 fieldA;
	u8 fieldB;
	u32 fieldC;
	u32 field10;
	u32 field14;
	u8 field18;
	u8 field19;
	u16 field1A;
	u16 most_recent_override_tile;
};

struct rom_npc {
	u8 nr;
	u8 type_nr;
	u8 rival;
	u8 field3;
	u16 x;
	u16 y;
	u8 height;
	u8 behaviour;
	u8 movement_area;
	u8 fieldB;
	u8 trainer_or_mapnumber;
	u8 fieldD;
	u8 sight_distance_or_mapbank;
	u8 *script;
	u16 local_id;
	u16 field16;
};

extern struct walkrun walkrun_state;
extern struct npc_state npc_states[16];

void npc_half_reset(struct npc_state *);
int npc_set_state_2(struct npc_state *, u8);
void npc_half_reset_when_bit7_is_set(struct npc_state *);
struct rom_npc *rom_npc_by_local_id_and_map(u8, u8, u8);
u8 npc_instanciation_something(struct rom_npc*, u8, u8, u16, u16);
void npc_change_sprite(struct npc_state*, u8);
void npc_turn(struct npc_state*, u8);

#endif /* PKMN_NPC_H_ */
