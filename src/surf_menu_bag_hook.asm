.text
.align 2
.thumb
.thumb_func

@Surf hook, startmenu/bag access
@hook via R0, at 0x8086B00. Write 00 00 to 0x8086AFE
main:
	push {r4, r5, lr}
	ldr r0, =(follower_nomove_surf)
	bl linker
	ldr r5, =(0x2037078)
	ldrb r1, [r5, #0x5]
	lsl r0, r1, #0x3
	add r0, r0, r1
	lsl r0, r0, #0x2
	ldr r1, =(0x2036E38)
	add r4, r0, r1
	ldr r0, =(0x8120718 +1)
	
linker:
	bx r0
	
	
.align 2


