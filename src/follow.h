#ifndef FOLLOWME_FOLLOW_H_
#define FOLLOWME_FOLLOW_H_

#include "types.h"
#include "npc.h"

struct follower {
	u8 npcid;
	struct {
		u8 id;
		u8 number;
		u8 bank;
	} map;
	u8 locked;
	u8 delayed_state;
	struct coords16 log;
	bool warp_end;
	u8 current_sprite;
};

extern struct follower follower_state;

#endif /* FOLLOWME_FOLLOW_H_ */
