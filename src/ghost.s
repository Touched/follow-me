	.align 2
	.thumb

collision_hook:
	push {r1-r3}
	mov r0, r2
	mov r1, r6
	bl collision_exempt
	pop {r1-r3}
	cmp r0, #0
	beq check_for_collision

no_collision:
	ldr r0, =(0x0806396C + 1)
	bx r0

check_for_collision:	
	mov r0, #0x10
	ldrsh r1, [r2, r0]
	lsl r0, r7, #0x10
	asr r3, r0, #0x10
	ldr r1, =(0x08063930 + 1)
	bx r1

	.align 2
walkrun_state: .word 0x02037078
