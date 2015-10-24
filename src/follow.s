	.align 2
	.thumb

set_state_hook:
	mov r1, r5
	mov r5, r0
	mov r0, r4
	bl follow_me
	mov r0, r5
	pop {r4, r5}
	pop {r1}
	bx r1
