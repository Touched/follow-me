	.align 2
	.thumb

local_id_hook:
	push {lr}
	lsl r0, #0x18
	lsr r0, #0x18
	lsl r1, #0x18
	cmp r0, #0xFE		@ hijack call with 0xFE
	beq local_id_return
	ldr r3, =(0x0805DF68 + 1)
	bx r3

local_id_return:
	bl follower_npc_id
	ldr r3, =(0x0805DF7C + 1)
	bx r3
