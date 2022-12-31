from textwrap import wrap

def dec(encoded):
	rec = []
	const1 = 0x69B2

	orig_len = len(encoded) // 6
	parts = wrap(encoded, 6)
	pow = 0

	for p in parts:
		pow += 1
		v11 = (pow * pow) ^ 0x19

		c = int(p, 16)
		c = str(c)
		c = int(c, 8)

		r = c ^ v11 ^ const1 ^ 0x11F0B8
		rec.append(r)

	return ''.join(map(chr, rec))


data = open("flag.enc", "rt").read().strip()
encrypted = data[:-4][::-1]
rec = dec(encrypted)
print(rec)

