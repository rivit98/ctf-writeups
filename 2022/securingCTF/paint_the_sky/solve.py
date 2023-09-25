from more_itertools import windowed
from pwn import unhex

c = list(map(lambda v: v.strip(']['), open("constellations.txt").read().splitlines()))
print(unhex(''.join(map(chr, map(lambda v: c.index(''.join(v)), windowed(open("skymap.txt").read(), n=8, step=8))))).decode())

