from base64 import b64decode
from z3 import *
from pwn import *

ECSC = "NJ6WGgy3yHdkx0c`ojGW"
ECSC = xor(ECSC, 1)


def ks(n, password):
    ret = []
    num = 1337
    for i in range(n):
        for j in range(len(password)):
            num += (i * password[j]) ^ (j * password[i % len(password)])

        ret.append(num & 0xFF)

    return ret

def bop(data):
    array2 = ks(len(data), ECSC)
    return [array2[i] ^ data[i] for i in range(len(data))]


expected = b64decode('uOWIiZv8ed7f')

token = [BitVec(f'c{i}', 8) for i in range(len(expected))]

s = Solver()

enc = bop(token)

for i in range(len(token)):
    s.add(expected[i] == enc[i])

print(s)

s.check()
mdl = s.model()
res = [mdl[c].as_long() for c in token]
print(''.join(map(chr, res)))

# coZR0b1sz

