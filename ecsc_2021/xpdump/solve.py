asm = '''
[ebp+var_1C], 0C7h ; 'Ç'
[ebp+var_1B], 26h ; '&'
[ebp+var_1A], 4Eh ; 'N'
[ebp+var_19], 57h ; 'W'
[ebp+var_18], 7Dh ; '}'
[ebp+var_17], 0E6h ; 'ć'
[ebp+var_16], 31h ; '1'
[ebp+var_15], 45h ; 'E'
[ebp+var_14], 4Eh ; 'N'
[ebp+var_13], 2Dh ; '-'
[ebp+var_12], 47h ; 'G'
[ebp+var_11], 37h ; '7'
[ebp+var_10], 58h ; 'X'
[ebp+var_F], 0E3h ; 'ă'
[ebp+var_E], 8Ah ; 'Š'
[ebp+var_D], 0A2h ; '˘'
[ebp+var_C], 71h ; 'q'
[ebp+var_B], 0B8h ; '¸'
[ebp+var_A], 0EEh ; 'î'
[ebp+var_9], 13h
[ebp+var_8], 8Fh ; 'Ź'
[ebp+var_7], 0F0h ; 'đ'
[ebp+var_6], 4Eh ; 'N'
[ebp+var_5], 0FFh
[ebp+var_3C], 0A2h ; '˘'
[ebp+var_3B], 45h ; 'E'
[ebp+var_3A], 3Dh ; '='
[ebp+var_39], 34h ; '4'
[ebp+var_38], 4Fh ; 'O'
[ebp+var_37], 0D7h ; '×'
[ebp+var_36], 4Ah ; 'J'
[ebp+var_35], 3Ch ; '<'
[ebp+var_34], 21h ; '!'
[ebp+var_33], 72h ; 'r'
[ebp+var_32], 23h ; '#'
[ebp+var_31], 56h ; 'V'
[ebp+var_30], 2Fh ; '/'
[ebp+var_2F], 84h ; '„'
[ebp+var_2E], 0D5h ; 'Ő'
[ebp+var_2D], 0CEh ; 'Î'
[ebp+var_2C], 18h
[ebp+var_2B], 0CEh ; 'Î'
[ebp+var_2A], 8Bh ; '‹'
[ebp+var_29], 4Ch ; 'L'
[ebp+var_28], 0D9h ; 'Ů'
[ebp+var_27], 0BDh ; '˝'
[ebp+var_26], 34h ; '4'
[ebp+var_25], 82h ; '‚'
'''

lines = asm.split('\n')
lines = list(filter(lambda l: len(l) > 5, lines))


def mapper(l):
    address, val = l.split(',')

    ad = address.replace('[ebp+var_', '').replace(']', '')
    ad = int(ad, 16)
    val = val.split(';')[0].replace('h', '').strip()
    val = int(val, 16)

    return ad, val


lines = list(map(mapper, lines))
d = {k: v for k, v in lines}

out = []
for i, j in zip(range(0x1c, 0x1c - 0x18, -1), range(0x3c, 0x3c - 0x18, -1)):
    out.append(chr(d[i] ^ d[j]))

print(''.join(out))
