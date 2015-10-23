	.align 2
	.thumb
	.include "constants.s"
	.include "config.s"
	.global set_state_hook

set_state_hook:
	mov r0, r4
	mov r1, r5
	bl follow_me
	b return 
	
	push {r0, r6-r7}

	ldr r1, walkrun_state
	ldrb r1, [r1, #5]
	lsl r2, r1, #3
	add r2, r1
	lsl r2, #2
	ldr r1, npc_states
	add r2, r1
	cmp r2, r4
	bne exit

test:
	ldr r2, =follower_config @ NPC State index
	ldrb r2, [r2]
	lsl r0, r2, #3
	add r0, r2
	lsl r0, #2
	add r6, r0, r1
	@@ mov r1, r5

load_movement_table:	
	@@ Look movement up in table
	adr r0, movement_list
	lsl r1, r5, #3
	add r7, r0, r1

	@@ Skip the direction check if we don't have this flag set
	ldr r1, [r7]
	cmp r1, #FOLLOWER_MOVE
	bne copy_state

	mov r0, r5 		@ current npc state
	bl filter_follower_movement
	cmp r0, #0xFE
	beq calculate_direction
	mov r5, r0
	adr r0, movement_list
	lsl r1, r5, #3
	add r7, r0, r1

calculate_direction:
	mov r0, r6
	mov r1, r4
	bl show_if_player_in_control

	mov r0, r6		@ follower state
	mov r1, r4		@ player state
	bl determine_follower_move_direction
	cmp r0, #0xFF
	beq exit

	@@ Get state from direction table
	add r2, r7, #4
	ldrb r1, [r2, r0]	@ state index
	mov r0, r6 		@ player state
	b apply_state

copy_state:
	ldr r1, [r7]
	cmp r1, #FOLLOWER_COPY
	bne exit
	mov r1, r5		@ player's state index
	mov r0, r6		@ player npc state
	
apply_state:
	bl set_state
	
exit:
	@@ Conditionally reset the the follower to re-enable NPC
	@@ behaviour after moving
	mov r0, r6
	ldr r2, =(0x08063D7C + 1)
	bl call_via_r2		
	
	pop {r0, r6-r7}

return:	
	pop {r4, r5}
	pop {r1}
	bx r1

determine_follower_move_direction:
	ldrh r2, [r0, #0x10] 	@ follower to x
	ldrh r3, [r1, #0x10]	@ player from x
	sub r2, r3

	cmp r2, #0
	bgt dir_left
	cmp r2, #0
	blt dir_right

	ldrh r2, [r0, #0x12]	@ follower to y
	ldrh r3, [r1, #0x12]	@ player from y
	sub r2, r3

	cmp r2, #0
	bgt dir_up
	cmp r2, #0
	blt dir_down
	b dir_none

dir_left:
	mov r0, #2
	b dir_return	
dir_right:
	mov r0, #3
	b dir_return	
dir_up:
	mov r0, #1
	b dir_return	
dir_down:
	mov r0, #0
	b dir_return
dir_none:
	mov r0, #0xFF
dir_return:
	bx lr

set_state:
	push {r4, r5, lr}
	mov r4, r0
	mov r5, r1

	ldr r2, =(0x08063D1C +1)
	bl call_via_r2
	
	mov r0, r4		
	mov r1, r5
	ldr r2, =(0x08063CA4 + 1)
	bl call_via_r2

	pop {r4, r5, pc}

show_if_player_in_control:
	mov r2, #0x22
	ldrb r2, [r1, r2]
	cmp r2, #0
	beq show_ret
	
	@@ Show sprite
	ldrb r2, [r0, #1]
	mov r1, #0x21
	neg r1, r1
	and r2, r1
	strb r2, [r0, #1]

show_ret:	
	bx lr

filter_follower_movement:
	ldr r1, =(0x203BFFA) 	@ follower data (TODO: Proper memory block)
	ldrb r2, [r1]
	cmp r2, #0
	bne replace
	
	cmp r0, #0x14
	blo no_filter
	cmp r0, #0x17
	bhi no_filter

	mov r0, #0x14
	strb r0, [r1] 		@ save to use later

	mov r0, #0x10
	bx lr

replace:
	mov r0, r2
	mov r2, #0
	strb r2, [r1]
	bx lr

no_filter:	
	mov r0, #0xFE
	bx lr

call_via_r2:
	bx r2

	.align 2
npc_states: .word 0x02036E38
walkrun_state: .word 0x02037078

.include "move_list.s"

