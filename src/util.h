#ifndef PKMN_UTIL_H_
#define PKMN_UTIL_H_

#include "npc.h"

void gf_memcpy(void *dst, void *src, u32 size);

struct npc_state *player_npc_state(void);
struct npc_state *follower_npc_state(void);

#endif /* PKMN_UTIL_H_ */
