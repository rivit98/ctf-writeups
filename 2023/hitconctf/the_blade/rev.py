import itertools
from pwn import *

expected = [
    0xA7, 0x51, 0x68, 0x52, 0x85, 0x27, 0xFF, 0x31,
    0x88, 0x87, 0xD2, 0xC7, 0xD3, 0x23, 0x3F, 0x52,
    0x55, 0x10, 0x1F, 0xAF, 0x27, 0xF0, 0x94, 0x5C,
    0xCD, 0x3F, 0x7A, 0x79, 0x9F, 0x2F, 0xF0, 0xE7,
    0x45, 0xF0, 0x86, 0x3C, 0xF9, 0xB0, 0xEA, 0x6D,
    0x90, 0x42, 0xF7, 0x91, 0xED, 0x3A, 0x9A, 0x7C,
    0x01, 0x6B, 0x84, 0xDC, 0x6C, 0xC8, 0x43, 0x07,
    0x5C, 0x08, 0xF7, 0xDF, 0xEB, 0xE3, 0xAE, 0xA4
]
def grouper(iterator, n: int):
    while chunk := list(itertools.islice(iterator, n)):
        yield chunk

def shuffle(data, table):
    ridx = 64
    tidx = 0
    while ridx:
        swap_idx = table[tidx]
        tidx += 1
        data[ridx-1], data[swap_idx] = data[swap_idx], data[ridx-1]

        swap_idx = table[tidx]
        tidx += 1
        data[ridx-2], data[swap_idx] = data[swap_idx], data[ridx-2]

        ridx -= 2

    return data

def rev_shuffle(data, table):
    tidx=64
    for ridx in range(0, 64, 2):
        swap_idx = table[tidx - 1]
        tidx -= 1

        data[ridx], data[swap_idx] = data[swap_idx], data[ridx]

        swap_idx = table[tidx - 1]
        tidx -= 1

        data[ridx + 1], data[swap_idx] = data[swap_idx], data[ridx + 1]

    return data

def transform(data):
    for idx in range(0x40):
        uVar23 = 0
        uVar18 = 1
        b = data[idx] + 1
        a = 0x101
        while b:
            t = b
            uVar27 = uVar18
            b = a % t
            iVar24 = uVar27
            iVar26 = uVar23
            uVar23 = uVar27
            uVar18 = (iVar26 - (a // t) * uVar27)
            a = t

        iVar26 = 0
        if 0 < uVar27:
            iVar26 = iVar24

        data[idx] = ((uVar27 & 0xffff) >> 0xf) + uVar27 + \
                    (((((uVar27 >> 0xf) - iVar24) + iVar26 & 0xffff) // 0x101) + 0x71) ^ 0x89

        if data[idx] < 0:
            data[idx] += 256

    return data

_transform_rev_mapping = {0: 251, 1: 123, 2: 78, 3: 187, 4: 81, 5: 21, 6: 141, 7: 219, 8: 176, 9: 172, 10: 165, 11: 142, 12: 170, 13: 178, 14: 96, 15: 235, 16: 99, 17: 92, 18: 222, 19: 66, 20: 43, 21: 198, 22: 166, 23: 53, 24: 48, 25: 67, 26: 214, 27: 95, 28: 189, 29: 36, 30: 177, 31: 227, 32: 140, 33: 167, 34: 213, 35: 42, 36: 124, 37: 109, 38: 139, 39: 23, 40: 157, 41: 131, 42: 254, 43: 105, 44: 16, 45: 89, 46: 169, 47: 158, 48: 15, 49: 28, 50: 102, 51: 151, 52: 91, 53: 97, 54: 237, 55: 173, 56: 224, 57: 218, 58: 39, 59: 6, 60: 37, 61: 220, 62: 94, 63: 231, 64: 65, 65: 50, 66: 210, 67: 217, 68: 143, 69: 238, 70: 175, 71: 3, 72: 147, 73: 58, 74: 0, 75: 162, 76: 225, 77: 179, 78: 236, 79: 129, 80: 159, 81: 202, 82: 88, 83: 183, 84: 121, 85: 253, 86: 59, 87: 160, 88: 2, 89: 12, 90: 203, 91: 168, 92: 128, 93: 192, 94: 22, 95: 77, 96: 47, 97: 117, 98: 113, 99: 10, 100: 4, 101: 57, 102: 255, 103: 193, 104: 156, 105: 171, 106: 239, 107: 164, 108: 216, 109: 226, 110: 20, 111: 194, 112: 108, 113: 100, 114: 30, 115: 107, 116: 126, 117: 153, 118: 46, 119: 9, 120: 11, 121: 134, 122: 116, 123: 106, 124: 196, 125: 45, 126: 79, 127: 249, 128: 250, 129: 148, 130: 182, 131: 31, 132: 137, 133: 111, 134: 93, 135: 232, 136: 234, 137: 181, 138: 90, 139: 101, 140: 136, 141: 197, 142: 127, 143: 119, 144: 17, 145: 207, 146: 241, 147: 27, 148: 63, 149: 244, 150: 72, 151: 71, 152: 18, 153: 228, 154: 186, 155: 223, 156: 233, 157: 98, 158: 110, 159: 180, 160: 150, 161: 205, 162: 19, 163: 83, 164: 75, 165: 40, 166: 215, 167: 209, 168: 51, 169: 184, 170: 230, 171: 122, 172: 44, 173: 155, 174: 41, 175: 68, 176: 82, 177: 247, 178: 32, 179: 242, 180: 49, 181: 211, 182: 185, 183: 64, 184: 208, 185: 52, 186: 245, 187: 84, 188: 26, 189: 1, 190: 161, 191: 146, 192: 252, 193: 133, 194: 7, 195: 190, 196: 221, 197: 188, 198: 25, 199: 243, 200: 54, 201: 246, 202: 114, 203: 152, 204: 76, 205: 125, 206: 199, 207: 212, 208: 69, 209: 74, 210: 154, 211: 195, 212: 138, 213: 229, 214: 80, 215: 70, 216: 204, 217: 104, 218: 118, 219: 103, 220: 201, 221: 14, 222: 60, 223: 87, 224: 240, 225: 34, 226: 191, 227: 38, 228: 132, 229: 13, 230: 144, 231: 163, 232: 174, 233: 61, 234: 29, 235: 200, 236: 145, 237: 5, 238: 135, 239: 112, 240: 8, 241: 115, 242: 33, 243: 73, 244: 85, 245: 62, 246: 55, 247: 35, 248: 24, 249: 86, 250: 206, 251: 130, 252: 56, 253: 149, 254: 120, 255: 248}
transform_rev_mapping = {v: k for k,v in _transform_rev_mapping.items()}
def rev_transform(v):
    return [transform_rev_mapping[d] for d in v]

def encode(flag):
    assert len(flag) == 64
    flag = list(map(ord, flag))

    tables = open("./shuffle_tables", "rb").read()
    assert len(tables) == 8*64*8
    tables = list(map(lambda v: u64(bytes(v)), grouper(iter(tables), 8)))

    for _ in range(0x100):
        for table in grouper(iter(tables), 64):
            flag = shuffle(flag, table)

        flag = transform(flag)

    return flag

def decode(flag):
    tables = open("./shuffle_tables", "rb").read()
    assert len(tables) == 8*64*8
    tables = list(map(lambda v: u64(bytes(v)), grouper(iter(tables), 8)))

    to_decode = flag.copy()
    for _ in range(0x100):
        to_decode = rev_transform(to_decode)

        for table in list(grouper(iter(tables), 64))[::-1]:
            to_decode = rev_shuffle(to_decode, table)

    return ''.join(map(chr, to_decode))


def phex(d):
    print(' '.join(map(lambda v: hex(v)[2:].zfill(2), d)))


def get_target_val(v):
    a = f'''
    mov eax, {v}
    mov r14d, 0x31f3831f
    mov r13d, 0x746f6f72
    mov r12d, 0x464c457f

    xor eax, r14d
    not eax
    rol eax, 0xb
    xor eax, r13d
    sub eax, r12d

    int3
    '''

    context.arch = 'amd64'
    p = debug_assembly(a, gdbscript='', api=True)

    p.gdb.continue_and_wait()
    eax = int(p.gdb.parse_and_eval('$rax'))
    p.gdb.quit()
    p.close()

    # p.interactive()
    return eax

def prepare_expected():
    chunks = list(grouper(iter(expected), 4))
    rev_chunks = []
    for c in chunks:
        target = u32(bytes(c))
        rev_target = get_target_val(target)
        rev_chunks.append(p32(rev_target))

    return list(b''.join(rev_chunks))

if __name__ == '__main__':
    expected = prepare_expected()
    test_flag = 'hitcon{abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234}'
    decoded = decode(encode(test_flag))
    print(decoded)
    assert test_flag == decoded

    print(decode(expected))
