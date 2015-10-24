#include "types.h"
#include "npc.h"
#include "util.h"

#define LEDGE_FRAMES_MULTIPLIER 2

extern void (**stepspeeds[5])(struct object *, u8);
extern const u16 stepspeed_seq_length[5];

void ledge_fun(struct npc_state *npc, struct object *obj, u16 *ledge_frames_table) {
	struct npc_state *follower = follower_npc_state();
	u8 speed;

	if (follower == npc) {
		speed = walkrun_state.running2 ? 3 : 1;
	} else {
		speed = 0;	
	}

	/* Calculate the frames for the jump */
	u16 frame_count = (u16) stepspeed_seq_length[speed] * LEDGE_FRAMES_MULTIPLIER;
	ledge_frames_table[obj->private[4]] = frame_count;

	/* Call the step shifter */
	u8 current_frame = obj->private[6] / LEDGE_FRAMES_MULTIPLIER;
	stepspeeds[speed][current_frame](obj, obj->private[3]);
}
