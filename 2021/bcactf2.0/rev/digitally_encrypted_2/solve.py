import binascii
from binascii import hexlify, unhexlify
import string

enc = list(map(lambda x: int(x, 16), '7B18824F93FB072A 2909D67381E26C31 57238C7EFEF9132D 7D24AD42B991216A 464B9173A2811D13'.split(" ")))
print(enc)

def pad(v, i):
    return bin(v)[2:].rjust(i, '0')

def get_keys(key_):
    k1 = key_ & (2**33-1)
    k2 = (key_ & 0xFFFFFFFF00) >> 8

    return k1, k2

def rev_key(k1, k2):
    rec_key = k1 | ((k2 & 0xFF000000) << 8)

    part1 = (k1 & 0xFFFFFF00) >> 8
    part2 = k2 & 0xFFFFFF

    if part2 == part1:
        return rec_key

def xor(a, b):
    return a ^ b

def neg(d):
    binary = pad(d, 32)
    return int(''.join([['1', '0'][int(v)] for v in binary]), 2)

def xnor(a, b):
    return neg(xor(a, b))

def block(plain, key):
    k1, k2 = get_keys(key)

    p_hi = (plain & 0xFFFFFFFF00000000) >> 32
    p_lo = (plain & 0xFFFFFFFF)

    a = xnor(p_lo, k1)
    b = xor(p_hi, a)
    c = xnor(k2, b)
    d = xor(p_lo, c)

    return (d << 32) | b

def deblock(plain, encrypted):
    e_hi = (encrypted & 0xFFFFFFFF00000000) >> 32
    e_lo = (encrypted & 0xFFFFFFFF)

    p_hi = (plain & 0xFFFFFFFF00000000) >> 32
    p_lo = (plain & 0xFFFFFFFF)

    from_xnor = xor(e_hi, p_lo)
    r = neg(from_xnor)
    k2 = xor(e_lo, r)

    from_xnor2 = xor(p_hi, e_lo)
    r2 = neg(from_xnor2)
    k1 = xor(p_lo, r2)

    key = rev_key(k1, k2)

    return key

def recover_plain(encrypted, k):
    e_hi = (encrypted & 0xFFFFFFFF00000000) >> 32
    e_lo = (encrypted & 0xFFFFFFFF)
    k1, k2 = get_keys(k)

    p_lo = xor(e_hi, xnor(e_lo, k2))
    p_hi = xor(e_lo, xnor(p_lo, k1))

    return unhexlify(hex(p_lo)[2:]).decode()[::-1] + unhexlify(hex(p_hi)[2:]).decode()[::-1]


# plain = 'bcactf{t'
# plain = int.from_bytes(plain.encode(), 'little')
# key = 0x1234567890
#
# e = block(plain, key)
# print(hex(e))
#
# rec_key = deblock(plain, e)
# print(rec_key == key)
#
# print(recover_plain(e, rec_key))

def decrypt_all(key):
    parts = []
    for e in enc:
        plain = recover_plain(e, key)
        print(plain)
        parts.append(plain[::-1])

    print(''.join(parts))

for e in enc:
    for c in range(0x20, 0x80):
        c = chr(c)
        possible_plain = 'bcactf{' + c
        possible_plain = int.from_bytes(possible_plain[::-1].encode(), 'little')
        k = deblock(possible_plain, e)
        if k:
            print(unhexlify(hex(k)[2:]), k, c)
            decrypt_all(k)

