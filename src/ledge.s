	.align 2
	.thumb

ledge_hook:
	mov r3, r6 		@ npc_state pointer from parent function
	mov r6, #0
	mov r1, #0x36
	ldrsh r0, [r4, r1]
	cmp r0, #0
	beq dont_move_oam

	mov r0, r3		@ npc
	mov r1, r4		@ obj
	mov r2, sp 		@ ledge jump frames
	bl ledge_fun

dont_move_oam:
	ldr r2, =(0x08068D6E + 1)
	bx r2
