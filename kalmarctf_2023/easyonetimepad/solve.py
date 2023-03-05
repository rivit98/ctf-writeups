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
    port = int(args.PORT or 13338)
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
PASS_LENGTH_BYTES_TWICE = PASS_LENGTH_BYTES * 2


ru(b'pad: ')
penc = rl().strip().decode()

li(penc)
penc = list(map(lambda v: int(v, 16), wrap(penc, 2)))

perm = '63,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127'

sla(b'Permutation: ', perm.encode())
ru(b'pad: ')
permuted_penc = rl().strip().decode()
li(permuted_penc)
permuted_penc = list(map(lambda v: int(v, 16), wrap(permuted_penc, 2)))

s = Solver()
pwd= [BitVec(f'p{i}', 8) for i in range(PASS_LENGTH_BYTES_TWICE)]
pwd_shifted = [pwd[63*2], pwd[63*2+1]] + pwd[0:2*63] + pwd[2*64:2*128]
c = [BitVec(f'r{i}', 8) for i in range(PASS_LENGTH_BYTES)]
c2 = [BitVec(f'x{i}', 8) for i in range(PASS_LENGTH_BYTES)]

print(pwd_shifted)

for idx in range(0, PASS_LENGTH_BYTES_TWICE):
    s.add(pwd[idx] ^ c[idx % PASS_LENGTH_BYTES] == penc[idx])

for idx in range(0, PASS_LENGTH_BYTES_TWICE):
    s.add(pwd_shifted[idx] ^ c2[idx % PASS_LENGTH_BYTES] == permuted_penc[idx])

for idx in range(0, PASS_LENGTH_BYTES_TWICE):
    s.add(Or(And(ord('a') <= pwd[idx], pwd[idx] <= ord('f')), And(ord('0') <= pwd[idx], pwd[idx] <= ord('9'))))

print(s.check())
p = []
while s.check() == sat:
    mdl = s.model()

    for i, cc in enumerate(pwd):
        r = mdl[cc].as_long()
        p.append(r)
        s.add(Or(pwd[i] != r))

    print("pwd", bytes(p))

    k1 = bytes([(mdl[cc].as_long()) for cc in c])
    print("key1", k1.hex())

    k2 = bytes([mdl[cc].as_long() for cc in c2])
    print("key2", k2.hex())

    print()

sla(b'password: ', bytes(p))

ia()

# kalmar{guess_i_should_have_read_the_whole_article}
