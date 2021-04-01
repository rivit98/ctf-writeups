from pwn import *
from collections import defaultdict
import string

p = remote("mercury.picoctf.net", 61477)

p.recvuntil("flag: ")
flag = p.recvline()
flag = int(flag)
print(f"flag - {flag}")

p.recvuntil("n: ")
n = p.recvline()
n = int(n)
print(f"n - {n}")

p.recvuntil("e: ")
e = p.recvline()
e = int(e)
print(f"e - {e}")

def get_number(text):
    p.sendline(text)
    p.recvuntil("go: ")
    ret = p.recvline().decode().strip()
    return ret


pos_letters = defaultdict(dict)

def get_letters(current_idx):
    current_letters = {}

    # for i in range(0x21, 0x7f):
    for i in map(ord, list(string.digits + string.ascii_letters + '{}_')):
    # for i in range(ord('i'), ord('p') + 1):
        c = chr(i)
        n = get_number(c * (current_idx + 1))
        current_letters[c] = n

    for prev_letter_idx in range(current_idx):
        d = pos_letters[prev_letter_idx]
        for k, v in d.items():
            cur_letter = current_letters[k]
            current_letters[k] = cur_letter.replace(v, '')


    pos_letters[current_idx] = current_letters
    # print(current_letters)

def update_flag(flag, idx):
    d = pos_letters[idx]

    found = []

    for k, v in d.items():
        if v in flag:
            found.append(k)
            print(f"Found {idx} - {k}")

    if len(found) != 1:
        print(found)
        raise Exception("sth is wrong")

    return flag.replace(d[found[0]], ''), found[0]


flag_chars = []
letter_idx = 0
flag = str(flag)
while len(flag) > 0:

    get_letters(letter_idx)
    flag, c = update_flag(flag, letter_idx)
    flag_chars.append(c)

    letter_idx += 1

    print(''.join(flag_chars))



# p.interactive()