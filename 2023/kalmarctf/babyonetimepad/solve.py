#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from pwn import *
from textwrap import wrap
from z3 import *
import string

# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]


def get_conn(argv=[], *a, **kw):
    host = args.HOST or '3.120.132.103'
    port = int(args.PORT or 13337)
    if args.GDB:
        return gdb.debug([elf.path] + argv, gdbscript=gdbscript, env=env, *a, **kw)
    elif args.REMOTE:
        return remote(host, port)
    else:
        return process([elf.path] + argv, env=env, *a, **kw)


gdbscript = '''
# b *main+900
brva 0x1957
continue
'''
gdbscript = '\n'.join(line for line in gdbscript.splitlines()
                      if line and not line.startswith('#'))
env = {}


io = get_conn()
def r(x): return io.recv(x)
def rl(): return io.recvline(keepends=False)
def ru(x): return io.recvuntil(x, drop=True)
def cl(): return io.clean(timeout=1)
def s(x): return io.send(x)
def sa(x, y): return io.sendafter(x, y)
def sl(x): return io.sendline(x)
def sla(x, y): return io.sendlineafter(x, y)
def ia(): return io.interactive()
def li(s): return log.info(s)
def ls(s): return log.success(s)


PASS_LENGTH_BYTES = 128


ru(b'pad: ')
penc = rl().strip().decode()
li(penc)
penc = list(map(lambda v: int(v, 16), wrap(penc, 2)))

perm = list(range(PASS_LENGTH_BYTES))
perm = perm[1:] + [0]

sla(b'Permutation: ', ','.join(map(str, perm)).encode())
ru(b'pad: ')
permuted_penc = rl().strip().decode()
li(permuted_penc)
permuted_penc = list(map(lambda v: int(v, 16), wrap(permuted_penc, 2)))

s = Solver()
pwd= [BitVec(f'p{i}', 8) for i in range(PASS_LENGTH_BYTES*2)]
pwd_shifted=pwd[2:] + pwd[:2]
c = [BitVec(f'c{i}', 8) for i in range(PASS_LENGTH_BYTES)]

for idx in range(0, PASS_LENGTH_BYTES*2):
	s.add(pwd[idx] ^ c[idx % PASS_LENGTH_BYTES] == penc[idx])

for idx in range(0, PASS_LENGTH_BYTES*2):
	s.add(pwd_shifted[idx] ^ c[idx % PASS_LENGTH_BYTES] == permuted_penc[idx])

for idx in range(0, PASS_LENGTH_BYTES*2):
	s.add(pwd[idx] ^ pwd_shifted[idx] == permuted_penc[idx] ^ penc[idx])

for idx in range(0, PASS_LENGTH_BYTES*2):
	s.add(Or(And(ord('a') <= pwd[idx], pwd[idx] <= ord('f')), And(ord('0') <= pwd[idx], pwd[idx] <= ord('9'))))

p = []

if s.check() == sat:
	mdl = s.model()

	for i, cc in enumerate(pwd):
		r = mdl[cc].as_long()
		p.append(p8(r))


sla(b'password: ', b''.join(p))

ia()
