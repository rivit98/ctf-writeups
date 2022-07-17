from pwn import *

elf = ELF('./seed_spring')
context.arch = elf.arch
context.binary = elf

def get_conn(env=None):
	if env is None: env = {}
	
	if args.GDB:
		return gdb.debug(elf.path, '\n'.join([
			"b easy_register",
			"c"
		]), env=env)
	elif args.REMOTE:
		return remote("jupiter.challenges.picoctf.org", 35856)
	else:
		return process(elf.path, env=env)

p2 = process("gcc get_numbers.c -o get_numbers".split(' '))
print(p2.clean(1))

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


p3 = process("./get_numbers")
nums = list(map(int, p3.clean(1).decode().strip().split(' ')))
print(nums)

for n in nums:
	sl(f'{n}'.encode())

ia()
