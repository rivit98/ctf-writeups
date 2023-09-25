k = (b'zHsqz5LbhQuqcWQmJvRW')

def decode(d):
    s = list(range(256))
    j = 0

    for i in range(256):
        j = (j+s[i]+k[i%len(k)]) % 256
        s[i],s[j] = s[j],s[i]

    i = 0
    h = 0
    def mapper(c):
        nonlocal i,h
        i += 1
        i %= 256
        h += s[i]
        h %= 256

        s[i], s[h] = s[h], s[i]
        return c ^ s[(s[i]+s[h])%256]


    return list(map(mapper, d))



raw = open("./stage2_raw", "rb").read()

open("./stage2.exe","wb").write(bytes(decode(raw)))

from base64 import b64decode
from z3 import *

expected = b64decode(b'FxxGrgbb/w==')
print(expected)

token = [BitVec(f'c{i}', 8) for i in range(len(expected))]
print(decode(token))

s = Solver()

for i in range(len(expected)):
    s.add(token[i] == expected[i])

s.check()
mdl = s.model()
res = [mdl[c].as_long() for c in token]
print(''.join(map(chr, decode(res))))

# Boz3nka
