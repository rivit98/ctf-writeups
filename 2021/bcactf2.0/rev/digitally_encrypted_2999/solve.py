from binascii import unhexlify

BIT_WIDTH = 64

def pad(v, i=BIT_WIDTH):
    return bin(v)[2:].rjust(i, '0')


plain = 0x7b18824f93fb072a

last_bit = plain & 1
res = 0
a = plain
while a:
    print(pad(a), "a")
    print(pad(res), "cur_res")
    res ^= a
    print(pad(res), "new_res")
    print()

    a <<= 1
    a &= 2**BIT_WIDTH - 1

print(hex(res))


def recover_part(cipher):
    recovered_bits = ['0'] * BIT_WIDTH
    recovered_bits[-1] = str(last_bit)
    prev_unmasked = cipher

    for t in range(1, BIT_WIDTH):
        c = prev_unmasked
        mask = int(''.join(map(str, recovered_bits)), 2) << BIT_WIDTH - t

        first = False
        for i in range(0, BIT_WIDTH - t):
            c ^= mask
            mask >>= 1

            if not first:
                first = True
                prev_unmasked = c
                print("next will be started from", pad(prev_unmasked))

            print(pad(c))

        rec_bit = pad(c)[::-1][t]
        print(f"recovered bit {t}={rec_bit}")
        recovered_bits[-t - 1] = rec_bit
        print()

    print(hex(int(''.join(recovered_bits), 2)))

    return unhexlify(hex(int(''.join(recovered_bits), 2))[2:]).decode()


parts = list(map(lambda x: int(x, 16), 'DE2120DED3DDD6EC D1EEDA2C3531EEDD EF2ECC232E2ECAEC C5DC35132C2CDDC2 3521251010CAEE2B'.split(" ")))
print(''.join(map(recover_part, parts)))
# bcactf{4r3nt_R3d1sTers_4Nd_5tufF_co01_2~
# sth is wrong with logic (or challenge) :D
# bcactf{4r3nt_R3g1sTers_4Nd_5tufF_co01_2}