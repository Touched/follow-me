import os.path
import subprocess
import shutil

PATH = '/opt/devkitpro/devkitARM/bin'
PREFIX = 'arm-none-eabi-'
OBJCOPY = os.path.join(PATH, PREFIX + 'objcopy')
AS = os.path.join(PATH, PREFIX + 'as')

def assemble(assembly, rom, offset, clear=True, *args):
	subprocess.check_output([AS, '-mthumb'] + list(args) + [assembly])
	subprocess.check_output([OBJCOPY, '-O', 'binary', 'a.out', 'a.bin'])
	os.remove('a.out') 
	with open(rom, 'rb+') as out, open('a.bin', 'rb') as ins:
		out.seek(offset)
		data = ins.read()
		
		out.write(data)
		if clear:
		    out.write(bytes(100))

def hook(file, rom, space, hook_at, register=0, *args):
    assemble(file, rom, space, True, *args)
    with open('test.gba', 'rb+') as rom:
        # Align 2
        if hook_at & 1:
            hook_at -= 1
            
        rom.seek(hook_at)
        
        register &= 7
        
        if hook_at % 4:
            data = bytes([0x01, 0x48 | register, 0x00 | (register << 3), 0x47, 0x0, 0x0])
        else:
            data = bytes([0x00, 0x48 | register, 0x00 | (register << 3), 0x47])
            
        space += 0x08000001
        data += (space.to_bytes(4, 'little'))
        rom.write(bytes(data))

def main():
    shutil.copyfile('BPRE0.gba', 'test.gba')
    with open('test.gba', 'rb+') as rom:
        hook('follow.s', 'test.gba', 0x800000, 0x063CF4, 1)
        hook('ghost.s', 'test.gba', 0x810000, 0x063928, 0)
        hook('warp.s', 'test.gba', 0x820000, 0x05CAF4, 0)
        hook('ledge.s', 'test.gba', 0x830000, 0x068D58, 0)

        hook('warps/stairs.s', 'test.gba', 0x840000, 0x07EB28, 1)

if __name__ == '__main__':
    main()

