#include "types.h"
#include "npc.h"
#include "util.h"
#include "oe_effects.h"
#include "util.c"

void follower_to_water(){
	/* make the follower do the jump and spawn the surf head
	right infront of the follower's location. */
	extern void set_surf_jump(struct npc_state *npc);
	extern struct npc_state *follower_npc_state(void);
	struct npc_state *npc = follower_npc_state();
	set_surf_jump(npc);
}

void follower_nomove_surf(){
	/* spawn surfhead under follower */
	extern void set_surf(struct npc_state *npc);
	extern struct npc_state *follower_npc_state(void);
	struct npc_state *npc = follower_npc_state();
	set_surf(npc);
}

void set_surf_jump (struct npc_state *npc) {
	extern void obj_bind (u8 task_id);
	extern void setup_oe(struct npc_state *npc);
	//reset NPC movement bits
	npc_half_reset_no_checks(npc);
	
	//jump animation according to direction
	u8 direction = npc->direction / 0x10;
	u8 jump_state = get_jump_animation_from_direction(direction);
	npc_set_state_2(npc, jump_state);
	setup_oe(npc);
	
	//adjust surf head spawn location infront of npc
	switch (direction){
		case 0x1:
			oe.effect_y++;
			break;
			
		case 0x2:
			oe.effect_y--;
			break;
			
		case 0x3:
			oe.effect_x--;
			break;
			
		default:
			oe.effect_x++;
	};

	//execute, store obj ID in field1A and bind obj
	int surf_head_obj_id = oe_exec(0x8);
	npc->field1A = surf_head_obj_id;
	u8 task_id = task_add(&obj_bind, 0x1);
	tasks[task_id].arg[0] = npc->local_id;
}

void set_surf(struct npc_state *npc){
	extern void obj_bind (u8 task_id);
	extern void setup_oe(struct npc_state *npc);
	
	setup_oe(npc);
	int surf_head_obj_id = oe_exec(0x8);
	npc->field1A = surf_head_obj_id;
	u8 task_id = task_add(&obj_bind, 0x1);
	tasks[task_id].arg[0] = npc->local_id;
}

void obj_bind (u8 task_id){
	extern struct npc_state *follower_npc_state(void);
	struct npc_state *npc = follower_npc_state();
	//wait animation
	u8 anim_status = npc_half_reset_when_bit7_is_set(npc);
	if (anim_status == 0) {
		return;
	}
	
	//bind objs
	bind_obj_maybe(npc->field1A, 0x1);
	sync_anim_obj_maybe();
	task_del(task_id);
	return;
}

void setup_oe(struct npc_state *npc){
	//set up oe_state_t struct for execution
	oe.effect_x = npc->to.x;
	oe.effect_y = npc->to.y;	
	oe.npc_id = npc->local_id;
}
