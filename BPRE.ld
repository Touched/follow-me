/*
 * Data
 */
 
objects = 0x0202063C;
walkrun_state = 0x02037078;
npc_states = 0x02036E38;
stepspeeds = 0x083A719C;
stepspeed_seq_length = 0x083A71B0;
oe = 0x020386E0;
tasks = 0x03005090;

/*
 * Functions
 */

npc_half_reset = 0x08063D1C|1;
npc_set_state_2 = 0x08063CA4|1;
npc_half_reset_when_bit7_is_set = 0x08063D7C|1;
npc_instanciation_something = 0x0805E72C|1;
gf_memcpy = 0x081E5E78|1;
rom_npc_by_local_id_and_map = 0x0805FD5C|1;
oe_exec = 0x08083444|1;
npc_half_reset_no_checks = 0x08063D34|1;
get_jump_animation_from_direction = 0x080641C0|1;
bind_obj_maybe = 0x080DC44C|1;
sync_anim_obj_maybe = 0x08068A5C|1;
task_add = 0x0807741C|1;
task_del = 0x08077508|1;

/*
 * Custom Data
 */

follower_state = 0x02031824;
