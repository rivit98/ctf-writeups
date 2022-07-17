from pwn import *

t = [
	0x6797443,
	0x2179f878,
	0x5f9aa7af,
	0x33a879d5,
	0x49e26fb3,
	0x7c56523f
]

exp = [
	0x33051c37,
	0x10ac927,
	0xeec8c1,
	0x19e04a81,
	0xe8303d5,
	0x10661e15
]

n = 0xffe000ff
p, q = 65519, 65521
tot = (p-1)*(q-1)

parts = []
for i in range(len(t)):
	d = pow(exp[i], -1, tot)
	parts.append(unhex(hex(pow(t[i], d, n))[2:]).decode()[::-1])

print(''.join(parts))

