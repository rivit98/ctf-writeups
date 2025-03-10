from pwn import *
import datetime

d = datetime.datetime.now()

def argv_constructor():
    shellcode_fixes = {**shellcode2_fix(), **shellcode3_fix()}
    shellcode_fixes = {k: chr(v) if v is not None else '?'  for k,v in shellcode_fixes.items()}
    shellcode_part = ''.join(shellcode_fixes.get(idx, '?') for idx in range(13))

    argv = [
        '0',
        "7K", # argv[2] + 4 * argv[1] == 295  # 7K na test /k ?
        "??",
        "R",
        "@", # (rwx mem = 0x40 )
        ten_solve(), # 'brUc3' 
        "E", # 0x45 (to fix asm instruction)
        "/",
        "1337", # if ( *ctx2 != 0x11333377 )
        "pr.ost", # fname where to store data
        "/200" + 32 * "?", # [length coded with base4][max 32 chars of data with length from first field]
        f"/{chr(0x1f+int(d.strftime('%d')))}pizza", # chr(0x1f+month_day)
        "/" + shellcode_part, # fix missing bytes in shellcode
        "/" + substitution_part(),
        "/" + "ob5cUr3",
        "/fin",
        "/",
    ]

    print(''.join(argv))

def ten_solve():
    v7 = [0x16, 0x17, 0x3B, 0x17, 0x56]
    ten = list(map(ord, "ten"))

    expected = [chr(i ^ j) for i,j in zip(v7, (ten+ten)[:len(v7)])]
    return ''.join(expected)


def shellcode2_fix():
    sc = [
        0x48, 0x89, 0x5C, 0x24, 0x08, 0x48, 0x89, 0x7C, 0x24, 0x18, 
        0x48, 0x89, 0x54, 0x24, 0x10, 0x4C, 0x8B, 0xC1, 0x48, 0x85, 
        0xC9, 0x74, 0x63, 0xB8, 0x41, 0x41, 0x00, 0x00, 0x66, 0x39, 
        0x01, 0x75, 0x59, 0x48, 0x63, 0x41, 0x3C, 0x81, 0x3C, 0x08, 
        0x50, 0x41, 0x00, 0x00, 0x75, 0x4C, 0x44, 0x8B, 0x8C, 0x08, 
        0x88, 0x00, 0x00, 0x00, 0x4C, 0x03, 0xC9, 0x45, 0x8B, 0x59, 
        0x20, 0x4C, 0x03, 0xD9, 0x33, 0xC9, 0x41, 0x39, 0x49, 0x18, 
        0x76, 0x32, 0x41, 0x8B, 0x04, 0x8B, 0x48, 0x8B, 0x5C, 0x24, 
        0x10, 0x49, 0x03, 0xC0, 0x48, 0x2B, 0xD8, 0x8B, 0xF9, 0x0F, 
        0xB6, 0x10, 0x44, 0x0F, 0xB6, 0x14, 0x18, 0x41, 0x2B, 0xD2, 
        0x75, 0x08, 0x48, 0xFF, 0xC0, 0x45, 0x85, 0xD2, 0x41, 0xEB, 
        0x85, 0xD2, 0x74, 0x15, 0xFF, 0xC1, 0x41, 0x3B, 0x49, 0x18, 
        0x72, 0xCE, 0x33, 0xC0, 0x48, 0x8B, 0x5C, 0x24, 0x08, 0x48, 
        0x8B, 0x7C, 0x24, 0x18, 0xC3, 0x41, 0x8B, 0x49, 0x41, 0x49, 
        0x03, 0xC8, 0x0F, 0xB7, 0x14, 0x79, 0x41, 0x8B, 0x49, 0x1C, 
        0x49, 0x03, 0xC8, 0x8B, 0x04, 0x91, 0x49, 0x03, 0xC0, 0xEB, 
        0xDB
    ]


    indexes_to_fix = [24,25,41,108,138,146,146]
    part_idx =       [1,11,4,2,3,0,10]
    fixes = [ord('M'), 
             ord('Z'), 
             ord('E'), 
             0x75,  # jne
             0x24, 
             0x41,
             0x41
             ]
    
    for f, i in zip(fixes, indexes_to_fix):
        if f is not None:
            sc[i] = f
        else:
            print(hex(i))
    dis = disasm(bytes(sc), arch='amd64')
    print(dis)

    return {k:v for k,v in zip(part_idx, fixes)}

def shellcode3_fix():
    sc = [
        0x41, 0x48, 0x8B, 0x04, 0x25, 0x60, 0x00, 0x00, 0x00, 0x48, 
        0x8B, 0x48, 0x18, 0x48, 0x8B, 0x51, 0x20, 0x48, 0x83, 0xEA, 
        0x10, 0x48, 0x8B, 0x42, 0x41, 0x66, 0x83, 0x78, 0x10, 0x41, 
        0x75, 0x2E, 0x66, 0x83, 0x78, 0x0E, 0x32, 0x75, 0x27, 0x66, 
        0x83, 0x78, 0x0C, 0x33, 0x75, 0x20, 0x66, 0x83, 0x78, 0x0A, 
        0x4C, 0x74, 0x07, 0x66, 0x41, 0x78, 0x08, 0x6C, 0x75, 0x12, 
        0x0F, 0xB7, 0x40, 0x08, 0xB9, 0xDF, 0xFF, 0x00, 0x00, 0x66, 
        0x83, 0xE8, 0x45, 0x66, 0x85, 0xC1, 0x74, 0x12, 0x48, 0x8B, 
        0x41, 0x10, 0x48, 0x83, 0xEA, 0x10, 0x48, 0x83, 0x7A, 0x30, 
        0x00, 0x75, 0xB8, 0x33, 0xC0, 0xC3, 0x48, 0x8B, 0x42, 0x41, 
        0xC3
    ]


    indexes_to_fix = [0,24,29,54,80,99]
    part_idx =       [12,5,8,9,7,6]
    fixes = [0x65, # mov    rax, QWORD PTR gs:0x60
             0x60, # load BaseDllName
             ord('.'), # kerne [L32.] dll 
             0x6b, # does not matter??? 
             0x52, 
             0x30 # to load value from rdx+0x30
             ]

    for f, i in zip(fixes, indexes_to_fix):
        if f is not None:
            sc[i] = f
        # else:
        # print(hex(i))
    dis = disasm(bytes(sc), arch='amd64')
    # print(dis)

    return {k:v for k,v in zip(part_idx, fixes)}

    # rax = peb
    # rcx = ptr PEB_LDR_DATA
    # rdx = LIST_ENTRY InMemoryOrderModuleList
    # 

def substitution_part():
    const = 'AZBQCEDTEXFHGOHLIMJFKKLDMVNNOUPBQWRYSGTIUPVAWCXJYRZS'
    from textwrap import wrap

    mapping = {v:k for k,v in wrap(const, 2)}
    rev_mapping = {v:k for k,v in mapping.items()}

    expected = 'RUECKWAERTSINGENIEURWESENC'

    decoded = ''.join(rev_mapping[c] for c in expected)
    return decoded

if __name__ == "__main__":
    argv_constructor()


# b0rn_t0_5truc7_b4by@flare-on.com
