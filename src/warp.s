	.align 2
	.thumb

avatar_init_hook:
	bl follower_avatar_init
	mov r9, r4
	pop {r4-r6}
	pop {r0}
	bx r0

avatar_init_hook2:
	bl handle_sprite
	add sp, #4
	pop {r4-r5, pc}
