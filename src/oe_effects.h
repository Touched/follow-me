struct oe_state {
	u32 effect_x;
	u32 effect_y;
	u32 npc_id;
	u32 field_c;
	u32 map_num;
	u32 map_bank;
	u32 sav1_loc;
	u32 field_1c;
};

extern struct oe_state oe;

u8 oe_exec(u8);
void bind_obj_maybe(u8 ID, u8 operation);
void sync_anim_obj_maybe(void);
u8 get_jump_animation_from_direction(u8 direction);