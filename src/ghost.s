	.align 2
	.thumb
	.include "config.s"

collision_hook:
	ldr r3, =follower_config @ NPC State index
	ldrb r3, [r3]
	lsl r0, r3, #3
	add r0, r3
	lsl r0, #2
	add r3, r1, r0
	
	cmp r2, r3
	bne check

	ldr r3, walkrun_state @ NPC State index
	ldrb r3, [r3, #5]
	lsl r0, r3, #3
	add r0, r3
	lsl r0, #2
	add r1, r0

	cmp r6, r1
	bne check

continue:
	ldr r0, =(0x0806396C + 1)
	bx r0

check:	
	mov r0, #0x10
	ldrsh r1, [r2, r0]
	lsl r0, r7, #0x10
	asr r3, r0, #0x10

	ldr r1, =(0x08063930 + 1)
	bx r1

	.align 2
walkrun_state: .word 0x02037078
