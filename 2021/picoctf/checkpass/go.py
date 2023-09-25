from binascii import unhexlify
import struct

cont = ''.join([chr(i + ord('A')) for i in range(0x20)])

scrambled_array = open("./scramble_array.bin", "rb").read()
scrambled_indexes = open("./scramble_indexes.bin", "rb").read()
target_bytes = open("./target_bytes.bin", "rb").read()
target_bytes = [int(b) for b in target_bytes]


fmt = f"<{len(scrambled_indexes) // 8}Q"
scrambled_indexes = list(struct.unpack(fmt, scrambled_indexes))


def print_array(a):
    # print(''.join(map(chr, a)))
    print(' '.join(map(hex, a)))


mapping = [
    64, 8,
    200, 25,
    216, 27,
    224, 28,
    136, 17,
    112, 14,
    96, 12,
    120, 15,
    16, 2,
    168, 21,
    128, 16,
    72, 9,
    152, 19,
    80, 10,
    104, 13,
    48, 6,
    176, 22,
    0, 0,
    240, 30,
    8, 1,
    32, 4,
    208, 26,
    232, 29,
    24, 3,
    248, 31,
    160, 20,
    192, 24,
    56, 7,
    88, 11,
    184, 23,
    40, 5,
    144, 18,
]
mapping_list = [(mapping[i], mapping[i + 1]) for i in range(0, len(mapping), 2)]
# mapping_list = sorted(mapping_list, key=lambda x: x[1])


def scramble(input_flag, offset):
    output = [0] * len(input_flag)
    offset <<= 8
    new_flag = [scrambled_array[offset + c] for c in input_flag]
    # print_array(new_flag)

    for m in mapping_list:
        scrambled_idx, out_idx = m
        v = new_flag[scrambled_indexes[(offset + scrambled_idx) // 8]]
        output[out_idx] = v

    print_array(output)
    return output


def unscramble(scrambled_data, offset):
    offset <<= 8
    new_flag = [0] * len(scrambled_data)
    for m in mapping_list:
        scrambled_idx, out_idx = m
        scrambled_idx = scrambled_indexes[(offset + scrambled_idx) // 8]
        new_flag[scrambled_idx] = scrambled_data[out_idx]

    # print_array(new_flag)
    rev_mapping = {}
    for i, b in enumerate(scrambled_array[offset:offset+0x100]):
        rev_mapping[b] = i

    out = [rev_mapping[c] for c in new_flag]
    return out



# s1_input = list(map(ord, list(cont)))
# print_array(s1_input)
# s1 = scramble(s1_input, 0)
# s2 = scramble(s1, 1)
# s3 = scramble(s2, 2)
# s4 = scramble(s3, 3)
# s1_un = unscramble(s1, 0)
# print_array(s1_un)

# print(list(sorted(s4)) == list(range(0x20)))
# print(s1_input == unscramble_total(s4))


def unscramble_total(enc):
    return unscramble(unscramble(unscramble(unscramble(enc, 3), 2), 1), 0)


print_array(target_bytes)

unscrambled_flag = unscramble_total(target_bytes)
print_array(unscrambled_flag)
recovered_flag = ''.join(map(chr, unscrambled_flag))

print("picoCTF{" + recovered_flag + "}")