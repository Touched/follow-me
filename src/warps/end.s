	.thumb
	.align 2

warp_end_hook:
	cmp r4, #0xF
	bls loop
	bl warp_set_end
	pop {r4, r5, pc}

loop:
	ldr r0, =(0x08068A62 + 1)
	bx r0
