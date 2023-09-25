a = "50 5E 5E A3 4F 5B 51 5E 5E 97 A3 80 90 A3 80 90 A3 80 90 A3 80 90 A3 80 90 A3 80 90 A3 80 90 A2 A3 6B 7F 00 54 13 0D 49".split(" ")
a = list(map(lambda v: int(v, 16), a))

# see three, C3 C3 C3 C3 C3 C3 C3! XD
for b in a[:0x23]:
	print(chr(0xc3 - b), end='')