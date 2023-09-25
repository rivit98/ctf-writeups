from z3 import *


def char(blk, coeffs):
    assert len(coeffs) == 8
    return Sum(
        *[blk[i] * coeffs[i] for i in range(len(coeffs))]
    )


part = []

for ii in range(8):
    blk = [BitVec(f'c{i}', 64) for i in range(8)]

    s = Solver()

    for i in range(len(blk)):
        s.add(blk[i] >= 0x20)
        s.add(blk[i] <= 0x80)


    def neg(x):
        if x & 0x800000: return x - 0x1000000
        return x


    vals = [16774200, 1411, 16776275, 3646, 1532, 6451, 2510, 16777141, 16775256, 2061, 16776706, 2260, 2107, 6124, 878,
            16776140, 16775299, 1374, 16776956, 2212, 1577, 4993, 1351, 16777040, 16774665, 1498, 16776379, 3062, 1593,
            5966, 1924, 16776815, 16774318, 851, 16775763, 3663, 711, 5193, 2591, 16777069, 16774005, 1189, 16776283,
            3892, 1372, 6362, 2910, 307, 16775169, 1031, 16776798, 2426, 1171, 4570, 1728, 33, 16775201, 819, 16776898,
            2370, 1132, 4255, 1900, 347]

    a = ii * 8
    expected = vals[a:a + 8]
    expected = list(map(neg, expected))

    coeff = [
        [-7, -2, 3, -4, 4, -13, -2, -7],
        [-2, 3, 2, 5, 6, -10, 11, -3],
        [-2, -4, -3, -3, 4, -5, -2, 6],
        [9, 3, -3, 5, -6, 17, 2, 7],
        [-2, 2, -1, 3, 6, -8, 9, 4],
        [6, 7, -2, 13, 5, 1, 20, 8],
        [9, -1, -6, 1, -8, 22, -6, 13],
        [5, -5, -8, -6, -5, 15, -11, 15]
    ]

    for e, c in zip(expected, coeff):
        s.add(char(blk, c) == e)

    s.check()
    m = s.model()
    for i in range(len(blk)):
        part.append(chr(m[blk[i]].as_long()))

print(''.join(part))
