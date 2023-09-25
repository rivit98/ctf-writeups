from pwn import *
import string
from copy import copy

FLAG_LEN = 25

# p = remote("localhost", 1337)
p = remote("compresstheflag.hackable.software", 1337)

tmp = [chr(ord('a') + x) for x in range(FLAG_LEN)]
def find_seed(letter_idx):
	i = 0
	while True:
		flag = copy(tmp)
		random.seed(i)
		random.shuffle(flag)

		if flag[0] == tmp[letter_idx]:
			return i

		i += 1

found = []
print(p.clean())

for i in range(FLAG_LEN):
	seed = find_seed(i)
	print(f"Letter {i} seed: {seed}")

	d = {}
	for c in string.ascii_uppercase + 'rgn{}':
		payload = f'{seed}:{c*110}'.encode()
		p.sendline(payload)
		
		stats = p.clean(0.1).decode().split()
		zlib = int(stats[3])
		print(c, stats)
		d[c] = zlib

	m = min(d, key=d.get)
	print(m)
	found.append(m)

print(''.join(found))


