#ifndef PKMN_UTIL_H_
#define PKMN_UTIL_H_

#include "npc.h"

void gf_memcpy(void *dst, void *src, u32 size);

struct npc_state *player_npc_state(void);
struct npc_state *follower_npc_state(void);
void npc_make_invisible(struct npc_state *npc);
void npc_make_visible(struct npc_state *npc);
void follower_set_sprite(u8 sprite_index);
u8 follower_get_sprite();

#endif /* PKMN_UTIL_H_ */
