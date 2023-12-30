# d = open("flag.enc", "rb").read()
# d = list(d)
# rb = ''.join(bin(dd)[2:].zfill(8) for dd in d)

# for i in range(0x20, 0x40):
#     for j in range(0, 8):
#         if len(rb[j:]) % i != 0: continue
#         print(i, j)

#         for idx, c in enumerate(rb[j:]):
#             if idx % 2 == 1: continue

#             if idx % i == 0:
#                 print()
#             print(c, end='')
#         print()
#         print()


# 42 is the size of QR, 6 zeros to skip 

def re_map_row(masked_row, mask_row):
    out_row = []
    out_char = None

    for masked_char, mask_char in zip(masked_row, mask_row):
        out_char = mask_char
        if out_char == '0':
            out_char = masked_char
        elif out_char == '1':
            out_char = '0' if masked_char == '1' else '1'
        
        out_row.append(out_char)

    return out_row

# 1 in mask means - flip
# 0 means - rewrite
# just xor?

d = open("flag.enc.orig", "rb").read()
d = list(d)
rb = ''.join(bin(dd)[2:].zfill(8) for dd in d)

masked = []
chunk = ''
for idx, c in enumerate(rb[6:]):
    if idx and idx % 74 == 0:
        print()
        masked.append(chunk)
        chunk = ''
    print(c, end='')
    chunk += c
masked.append(chunk)

print()
print()
mask = open("./target_pattern.txt", "rt").read().strip()
mask_rows = mask.splitlines()
for i in range(len(mask_rows)):
    mapped = re_map_row(masked[i], mask_rows[i])
    print(''.join(mapped[::2]))

# paste output to: https://bahamas10.github.io/binary-to-qrcode/
# decode qr
