	.thumb
	.align 2

warp_door_end_hook:
	bl warp_set_end
	ldr r3, =(0x08068A5C + 1)
	bl call_via_r3
	ldr r3, =(0x0806994C + 1)
	bl call_via_r3
	ldr r0, =(0x0807E200 + 1)
	bx r0

warp_normal_end_hook:
	bl warp_set_end
	ldr r3, =(0x08068A5C + 1)
	bl call_via_r3
	ldr r3, =(0x0806994C + 1)
	bl call_via_r3
	ldr r0, =(0x0807E310 + 1)
	bx r0

call_via_r3:
	bx r3
