from pwn import *

# p = process("task.py")
p = remote("babymac.hackable.software", 1337)

target_str = 'gimme flagBBBBBB'

print(p.recvline())
m = 'A' * 32
p.sendlineafter(b'> ', b'sign')
p.sendlineafter(b'> ', m.encode())

t = p.recvline().strip()[:-len(m)].decode()
print(f'signed {m} = {t} {len(t)}')

m2 = m + '10'*16 + '0'*32 + xor(bytes.fromhex(t), target_str.encode()).hex()
p.sendlineafter(b'> ', b'sign')
p.sendlineafter(b'> ', m2.encode())

t1 = p.recvline().strip()[:-len(m2)].decode()
print(f'signed {m2} = {t1} {len(t1)}')

to_send = t1 + target_str.encode().hex()
p.sendlineafter(b'> ', b'verify')
p.sendlineafter(b'> ', to_send.encode())
print(f'verify {to_send}')

print(p.clean(1.0))
# p.interactive()
