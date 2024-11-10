from base64 import b64decode
from pwn import unhex

based = "cQoFRQErX1YAVw1zVQdFUSxfAQNRBXUNAxBSe15QCVRVJ1pQEwd/WFBUAlElCFBFUnlaB1ULByRdBEFdfVtWVA=="
expected = b64decode(based)
print(expected)

# .rdata:00000000004C8030                 db '2bf16FlareOn2024bad verb ',27h,'%0123456789_/dev/stdout/dev/stder'

recovered = []
for i, c in enumerate(expected):
    v17 = i - 0xB * ((((i * 0x5D1745D1745D1746) >> 64) & ((2**64)-1)) >> 2)
    k = "FlareOn2024"[v17]
    recovered.append(c ^ ord(k))

print(recovered)
print(''.join(map(chr, recovered)))