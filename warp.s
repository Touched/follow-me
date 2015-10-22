	.align 2
	.thumb

main:
	sub sp, #0x18

	@@ Get ROM Npc
	mov r0, #1		@ npc id
	mov r1, #0		@ map number
	mov r2, #3		@ map bank
	ldr r4, rom_npc_by_local_id_and_map
	bl call_via_r4

	@@ Make an in-memory copy of the ROM NPC
	mov r1, r0
	mov r0, sp
	mov r2, #0x18
	ldr r4, memcpy
	bl call_via_r4

	@@ Get player state
	ldr r1, walkrun_state
	ldrb r1, [r1, #5]
	lsl r2, r1, #3
	add r2, r1
	lsl r2, #2
	ldr r1, npc_states
	add r2, r1

	@@ Copy player coordinates
	mov r0, sp
	ldrh r1, [r2, #0x10]
	sub r1, #7
	strh r1, [r0, #4]
	ldrh r1, [r2, #0x12]
	sub r1, #7	
	strh r1, [r0, #6]	
	
	bl make_npc

	@@ Hide NPC
	lsl r2, r0, #3 		@ npc id (returned)
	add r2, r0
	lsl r2, #2
	ldr r1, npc_states
	add r2, r1
	ldrb r0, [r2, #1]
	mov r1, #0x20		@ makes sprite invisible
	orr r0, r1
	strb r0, [r2, #1]

exit:
	add sp, #0x18
	mov r9, r4
	pop {r4-r6}
	pop {r0}
	bx r0

make_npc:
	push {lr}
	sub sp, #4
	mov r1, #0 		@ map number
	mov r2, #3		@ map bank
	mov r3, #0
	str r3, [sp]
	ldr r4, npc_instanciation_something
	bl call_via_r4
	add sp, #4
	pop {pc}
	
call_via_r4:
	bx r4
	
	.align 2
rom_npc_by_local_id_and_map: .word 0x0805FD5C + 1
memcpy:	.word 0x081E5E78 + 1
npc_instanciation_something: .word 0x0805E72C + 1
npc_states: .word 0x02036E38
walkrun_state: .word 0x02037078
