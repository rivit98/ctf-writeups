#!/usr/bin/python3

from pwn import *
from subprocess import check_output
out = check_output(f'nasm -felf64 shellcode2.asm && ld -m elf_x86_64 shellcode2.o', shell=True)
print(out)

elf = ELF('./a.out')
context.arch = elf.arch
context.binary = elf
context.terminal = ["terminator", "-u", "-e"]

def get_conn(env=None):
	if env is None: env = {}
	
	if args.GDB:
		return gdb.debug(elf.path, '\n'.join([
			"b *finish_prog",
			"c"
		]), env=env)
	elif args.REMOTE:
		# return remote("localhost", 5000)
		return remote("be.ax", 31278)
	else:
		return process(elf.path, env=env)

p = get_conn()
r = lambda x: p.recv(x)
ra = lambda: p.recvall()
rl = lambda: p.recvline(keepends=False)
ru = lambda x: p.recvuntil(x, drop=True)
s = lambda x: p.send(x)
sa = lambda x, y: p.sendafter(x, y)
sl = lambda x: p.sendline(x)
sla = lambda x, y: p.sendlineafter(x, y)
ia = lambda: p.interactive()
li = lambda s: log.info(s)
lw = lambda s: log.warn(s)
ls = lambda s: log.success(s)
cl = lambda: p.clean(timeout=1)


s(b'corctf{xor_j1t_vm_rBvBrs1ngN}')

ia()

target = [0x52, 0x5e, 0x43, 0x52, 0x49, 0x57, 0x4a, 0x4d, 0x3c, 0x36, 0x2e, 0x5b, 0x35, 0x49, 0x2e, 0x47, 0x60, 0x2e, 0x43, 0x33, 0x47, 0x33, 0x43, 0x42, 0x35, 0x5f, 0x56, 0x3f, 0x50, 0xd0, 0xa6, 0x79]

print(''.join(map(lambda v: chr(((v + 0x1e) ^ 0x13)), target)))
