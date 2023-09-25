from pwn import *
from collections import defaultdict
import string
import marshal

p = remote("mercury.picoctf.net", 61477)

p.recvuntil("flag: ")
flag = p.recvline()
flag = str(int(flag))
# print(f"flag - {flag}")

p.recvuntil("n: ")
n = p.recvline()
n = str(int(n))
# print(f"n - {n}")

p.recvuntil("e: ")
e = p.recvline()
e = int(e)


# print(f"e - {e}")


def load_flag():
    try:
        with open("./flag_cache", "rb") as f:
            flag_chars = marshal.load(f)

        return flag_chars, len(flag_chars)
    except:
        return ['p'], 1


flag_parts, start_idx = load_flag()
print("Cached flag " + ''.join(flag_parts))


def get_number(text):
    p.sendline(text)
    p.recvuntil("go: ")
    ret = p.recvline().decode().strip()
    # print()
    # print(f'{text}: {ret}')
    return ret


def update_flag(flag, d, idx):
    found = []

    for k, v in d.items():
        if v in flag:
            found.append(k)
            print(f"Found {idx} - {k}")

    if len(found) != 1:
        print(found)
        raise Exception("sth is wrong")

    return flag.replace(d[found[0]], ''), found[0]


def strip_one_letter(to_strip, num, correction=0):
    if len(to_strip) < 100:
        raise Exception(f"to_strip too short")

    a_idx = 0
    b_idx = num.index(to_strip[:100])

    while b_idx < len(num) and a_idx < len(to_strip) and to_strip[a_idx] == num[b_idx]:
        a_idx += 1
        b_idx += 1

    # print(f"returning: {to_strip[:a_idx+correction]}")
    return to_strip[:a_idx + correction]


def nth_letter(target, to_strip):
    if len(to_strip) == 0:
        return True, target

    # print(to_strip)
    # print(target)

    prev_target = target
    prev_to_strip = to_strip
    for correction in range(6):
        target = prev_target
        to_strip = prev_to_strip
        try:
            common_part = strip_one_letter(to_strip, target, -correction)
            to_strip = to_strip.replace(common_part, '')
            target = target.replace(common_part, '')
            end, ret_str = nth_letter(target, to_strip)
            if end:
                return True, ret_str
        except Exception as e:
            # print(e)
            # print(f"Trying next correction because {-correction} failed")
            continue

    return False, ""


def load_data(letter_idx):
    print(f"Loading data for letter {letter_idx}")
    d = {}
    for i in map(ord, list(string.digits + string.ascii_letters + '{}_')):
        # for i in map(ord, list(string.printable)):
        # for i in range(ord('A'), ord('A')+1):
        c = chr(i)
        n = get_number(c * (letter_idx + 1))
        d[c] = n

    return d


def singlify_dict(prev_dict, current_dict):
    res_dict = {}
    for k, v in current_dict.items():
        if len(v) < 3:
            continue
        res_dict[k[0]] = nth_letter(v, prev_dict[k])[1]

    return res_dict


prevs = defaultdict(dict)
for i in range(start_idx, 0x30):
    prev_dict = prevs.get(i - 1)

    if not prev_dict:
        prevs[i - 1] = load_data(i - 1)
        prev_dict = prevs[i - 1]

    current_dict = prevs[i] = load_data(i)
    letter_dict = singlify_dict(prev_dict, current_dict)
    # print("letter_dict")
    # print(letter_dict)

    try:
        flag, flag_char = update_flag(flag, letter_dict, i)

        flag_parts.append(flag_char)
        print(''.join(flag_parts))
        with open("./flag_cache", "wb") as f:
            marshal.dump(flag_parts, f)
    except Exception as e:
        p.clean()
        print(e)
        # p.interactive()
        break


#picoCTF{bad_1d3a5_4981729}