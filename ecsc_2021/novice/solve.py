

def random_thingy(v):
	return (0xDEAD * v + 0xBEEF) % 0x80


def random_thingy2(v, how_many):
	for _ in range(ord(how_many)):
		v = random_thingy(v)
	
	return v

v5 = ['\x15','f','\x10','p','m','9','r','a','3','u','}','b','\x1A','\x02',':','1','\t','\x1C','p','l','q','3','\b','E','#',':',':','\f','b','[','%','Q','O','8','\x19', '+', '|', '\\', '\\']

out = []
v2 = random_thingy(61767)
for i in v5:
	v2 = random_thingy2(v2, i)
	out.append(chr(v2))

print(''.join(out))
