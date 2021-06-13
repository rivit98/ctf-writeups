from z3 import *
from binascii import unhexlify

enc = list(map(lambda x: int(x, 16), 'EF5BFC29C7DE0F97 4ED8DA28F68A65EC C4D8A4F1B763C6A4 30850A10387421B3 EB3390DFEB1273F9'.split(" ")))
recovered = []
for e in enc:
    s = Solver()
    plain = BitVec('plain', 64)
    a = plain

    out = BitVecVal(0, 64)
    cnt = 1
    for i in range(64): # while a:
        xored = a ^ out

        v = a << cnt
        v &= 0xFFFFFFFFFFFFFFFF

        out = v + xored
        out &= 0xFFFFFFFFFFFFFFFF

        a *= 2
        a &= 0xFFFFFFFFFFFFFFFF

        cnt += 1
        cnt &= 0x7F

    s.add(out == e)

    if s.check() == sat:
        mdl = s.model()
        v = mdl[plain].as_long()
        print(hex(v))
        recovered.append(unhexlify(hex(v)[2:]).decode())

print(''.join(recovered))


