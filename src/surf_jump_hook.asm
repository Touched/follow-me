.text
.align 2
.thumb
.thumb_func

@Surf hook, make follower jump into water as well
@hook via R0, at 0x8086B00. Write 00 00 to 0x8086AFE
main:
	ldr r0, =(follower_to_water)
	bl linker
	ldr r1, =(0x20386E0)
	mov r2, #0xA
	ldrsh r0, [r6, r2]
	str r0, [r1]
	mov r2, #0xC
	ldrsh r0,[r6, r2]
	str r0, [r1, #0x4]
	ldr r0, =(0x8086B0C +1)
	
linker:
	bx r0
	
	
.align 2


