from Crypto.Util.number import bytes_to_long, getStrongPrime
from random import randrange
from pwn import *

LIMIT = 64

flag = b"corctf{ABCDEFGHIJKLMN12345689034568}"


def main():
	# cap =  10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	cap =  5207851285831991069018664616693415824195562260751582516097806772363284738507980478829791747964096025668757404599258689372930479386523996733325103074152943
	# cap2 = 5000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
	cap2 = 5207851285831991069018664616693415824195562260751582516097806772363284738507980478829791747964096025668757404599258689372930479386523996447358933572901247
	l, r = cap2, cap

	p = remote("crypto.be.ax", 6000)
	p.recvuntil('g:')
	g = int(p.recvline().strip().decode())
	print(f'g: {g}')

	p.recvuntil('p:')
	pp = int(p.recvline().strip().decode())
	print(f'p: {pp}')

	p.recvuntil('encrypted flag:')
	enc = int(p.recvline().strip().decode())
	print(f'enc: {enc}')

	def gimme(div):
		p.recvuntil("give me a number> ")
		p.sendline(str(div).encode())
		v = int(p.recvline().strip().decode())
		return v

	while abs(l-r) != 1:
		mid = (l+r) // 2
		print(r)
		print(l)
		print()
		ret = gimme(mid)
		if ret == 1:
			r = mid
		elif ret == g:
			l = mid
		else:
			print("sth went wrong")
			raise SystemExit()

	print(l)
	print(r)



	def dec(x):
		from binascii import unhexlify
		try:
			print(unhexlify(hex(x)[2:]))
		except:
			pass

	dec(l)
	dec(r)


main()