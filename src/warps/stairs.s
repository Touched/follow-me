	.align	2
	.thumb

stairs_move_hook:	
	strh r0, [r7, #0x26]
	mov r0, r7		
	bl stairs_move_follower

return:	
	mov r1, r8
	ldrb r0, [r1]
	lsr r0, #7	
	ldr r1, =(0x0807EB30 + 1)
	bx r1
