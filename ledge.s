	.align 2
	.thumb

main:
	mov r3, r6 		@ npc_state pointer from parent function
	mov r6, #0
	mov r1, #0x36
	ldrsh r0, [r4, r1]
	cmp r0, #0
	beq dont_move_oam

	@@ Load follower NPC state
	ldr r2, follower_config
	ldrb r2, [r2]
	lsl r0, r2, #3
	add r0, r2
	lsl r0, #2
	ldr r1, npc_states
	add r0, r1

	mov r2, #0
	cmp r3, r0
	bne calculate_frames

	ldr r1, walkrun_state
	ldrb r1, [r1, #2]
	cmp r1, #2
	beq running
	mov r2, #1
	b calculate_frames

running:	
	mov r2, #2

calculate_frames:
	@@ Work out which table to use
	adr r0, step_table
	lsl r2, #3
	add r2, r0
	
	@@ Change frame duration
	mov r0, sp
	ldr r1, [r2]
	strh r1, [r0, #4]

	@@ Call big step
	ldrh r1, [r4, #0x34]
	mov r0, r4
	ldr r2, [r2, #4]
	bl call_via_r2

dont_move_oam:
	ldr r2, =(0x08068D6E + 1)
	bx r2

call_via_r2:
	bx r2
	
	.align 2
npc_states: .word 0x02036E38
follower_config: .word 0x08063962 @ TODO: Change to dynamic location
walkrun_state: .word 0x02037078	
step_table:
	.long 0x20, 0x08068D62 + 1 @ normal
	.long 0x10, 0x08068AAC + 1 @ follower (player walking)
	.long 0x8, 0x08068AF8 + 1  @ follower (player running)
