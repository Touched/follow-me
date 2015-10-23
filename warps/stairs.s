	.align	2
	.thumb
	.include "config.s"

main:	
	strh r0, [r7, #0x26]

	@@ Get NPC state index for follower
	ldr r2, =follower_config @ NPC State index
	ldrb r2, [r2]

	@@ Get NPC State
	ldr r1, npc_states
	lsl r0, r2, #3
	add r0, r2
	lsl r0, #2
	add r1, r0

	@@ Get object
	ldrb r2, [r1, #4]
	lsl r0, r2, #4
	add r0, r2
	lsl r0, #2
	ldr r2, objects
	add r2, r0

	@@ Copy coords
	ldrh r0, [r4]
	lsl r0, #0x10
	asr r0, #0x15
	strh r0, [r2, #0x24]

	ldrh r0, [r5]
	lsl r0, #0x10
	asr r0, #0x15
	strh r0, [r2, #0x26]

return:	
	mov r1, r8
	ldrb r0, [r1]
	lsr r0, #7	
	ldr r1, =(0x0807EB30 + 1)
	bx r1

	.align 2
walkrun_state: .word 0x02037078
objects: .word 0x0202063C
npc_states: .word 0x02036E38
