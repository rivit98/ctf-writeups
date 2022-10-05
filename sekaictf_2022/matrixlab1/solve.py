from z3 import *
import itertools

length = 2 ** 3 - 2

def transform(arr):
    m = [[0 for x in range(length)] for y in range(length)]
    for i in range(0, length * length):
        m[i // length][i % length] = arr[i]

    return m


def getArray(var0, var1, var2):
    var3 = [None for i in range(length * 2)]
    var4 = 0
    for var5 in range(length):
        var3[var4] = var0[var1][var5]
        var4 += 1

    for var5 in range(length):
        var3[var4] = var0[var2][length - 1 - var5]
        var4 += 1

    return var3


def encrypt(var0, var1):
    var2 = [None for i in range(length * 2)]
    var3 = length - 1
    var4 = length
    for var5 in range(0, length * 2, 2):
        var2[var5] = var0[var3]
        var3 -= 1
        var2[var5 + 1] = var0[var4]
        var4 += 1

    for var5 in range(length * 2):
        var2[var5] ^= var1

    return var2

input = [BitVec(f'x{i}', 8) for i in range(length * length)]
var1 = transform(input)
for var2 in range(length // 2 + 1):
    for var3 in range(length - 2 * var2 - 1):
        var4 = var1[var2][var2 + var3]
        var1[var2][var2 + var3] = var1[length - 1 - var2 - var3][var2]
        var1[length - 1 - var2 - var3][var2] = var1[length - 1 - var2][length - 1 - var2 - var3]
        var1[length - 1 - var2][length - 1 - var2 - var3] = var1[var2 + var3][length - 1 - var2]
        var1[var2 + var3][length - 1 - var2] = var4

enc1 = encrypt(getArray(var1, 0, 5), 2)
enc2 = encrypt(getArray(var1, 1, 4), 1)
enc3 = encrypt(getArray(var1, 2, 3), 0)

s = Solver()
target = "oz]{R]3l]]B#50es6O4tL23Etr3c10_F4TD2"
for v, t in itertools.chain.from_iterable([zip(enc1, target[:12]), zip(enc2, target[12:24]), zip(enc3, target[24:])]):
    s.add(v == ord(t))

print(s.check())
if s.check() == sat:
    flag = ''.join(map(chr, [s.model()[i].as_long() for i in input]))
    print(f'SEKAI{{{flag}}}')
