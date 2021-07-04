import binascii

# lol
# https://ctftime.org/writeup/18782

lines = open("task.txt", 'r').readlines()

bits = []
for line in lines:
    v = int(line[:-1])
    bits.append(str(v & 1))


bits = bits[::-1]
num = int("".join(bits), 2)
print(binascii.unhexlify(hex(num)[2:]))