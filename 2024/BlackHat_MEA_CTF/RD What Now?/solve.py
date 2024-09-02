from z3 import *

s = Solver()

def substr(flag, start, end):
    if start == end:
        return flag[start]
    raise ""


flag = [BitVec(f"flag_{i}", 8) for i in range(95)]


s.add((flag[1] == flag[2]) & (flag[1] == flag[3]) & (flag[1] == flag[4]) & (flag[1] == flag[5]) & (flag[1] == ord('0')))

val_1 = substr(flag, 54, 54)
val_2 = substr(flag, 84, 84)
val_3 = substr(flag, 12, 12)
s.add((val_1 == val_2) & (val_1 == ord("e")) & (val_1 == val_3))


val_1 = substr(flag, 22, 22)
val_2 = substr(flag, 48, 48)
val_3 = substr(flag, 78, 78)
val_4 = substr(flag, 89, 89)
s.add((val_1 == val_2) & (val_1 == val_3) & (val_1 == val_4))


val_1 = substr(flag, 42, 42)
val_2 = substr(flag, 50, 50)
val_3 = substr(flag, 56, 56)
val_4 = substr(flag, 80, 80)
s.add((val_1 == val_2) & (val_1 == ord("d")) & (val_1 == val_3) & (val_3 == val_4))


# val_1 = as.integer(substr(flag, 7, 8))
# val_2 = as.integer(substr(flag, 9, 10))
# val_3 = as.integer(substr(flag, 89, 91))
# val_4 = as.integer(substr(flag, 92, 93))
# s.add(((val_1 - val_2) == 9) & ((val_3 + val_4) == 680))


val_1 = substr(flag, 72, 72)
val_2 = substr(flag, 92, 92)
val_3 = substr(flag, 26, 26)
val_4 = substr(flag, 34, 34)
val_5 = substr(flag, 60, 60)
s.add((val_1 == val_2) & (val_1 == val_3) & (val_1 == val_4) & (val_1 == val_5))


val_1 = substr(flag, 51, 51)
val_2 = substr(flag, 59, 59)
val_3 = substr(flag, 63, 63)
val_4 = substr(flag, 65, 65)
val_5 = substr(flag, 77, 77)
val_6 = substr(flag, 91, 91)
s.add((val_1 == val_2) & (val_1 == val_3) & (val_1 == val_4) & (val_1 == val_5) & (val_1 == val_6))


val_1 = substr(flag, 14, 14)
val_2 = substr(flag, 18, 18)
val_3 = substr(flag, 24, 24)
val_4 = substr(flag, 32, 32)
val_5 = substr(flag, 36, 36)
val_6 = substr(flag, 62, 62)
s.add((val_1 == val_2) & (val_1 == ord("a")) & (val_1 == val_3) & (val_3 == val_4) & (val_5 == val_4) & (val_6 == val_5))





def check_val_11(index, value):
    return (flag[index] == ord(value))

def check_val_6(index1, index2, value):
    value = str(value)
    assert len(value) == index2 - index1 + 1
    r = None
    for i in range(index1, index2 + 1):
        if r is None:
            r = flag[i] == ord(value[i - index1])
        else:
            r = r & (flag[i] == ord(value[i - index1]))
    return r

def check_val_1(index1, index2, index3):
    return (flag[index1] == flag[index2]) & (flag[index1] == flag[index3])


def parse_int(index1, index2):
    r = 0
    for i in range(index1, index2 + 1):
        s.add((flag[i] >= ord("0")) & (flag[i] <= ord("9")))
        r = r * 10 + BV2Int(flag[i]) - ord("0")
    return r

###

val_1 = parse_int(7, 8)
val_2 = parse_int(9, 10)
val_3 = parse_int(89, 91)
val_4 = parse_int(92, 93)
s.add(((val_1 - val_2) == 9) & ((val_3 + val_4) == 680))


val_1  = substr(flag, 16, 16)
val_2  = substr(flag, 30, 30)
s.add((val_1 == val_2) & (val_1 == ord("f")))

val_1 = parse_int(51, 51)
val_2 = parse_int(22, 22)
s.add((val_1 - val_2) == 1)

val_1 = parse_int(17, 17)
val_2 = parse_int(87, 87)
s.add((val_1 - val_2) == -2)




###


s.add(check_val_6(25, 29, 25213))
s.add(check_val_6(7, 11, 29202))



s.add(check_val_1(94, 82, 6))
s.add(check_val_1(1, 86, 10))
s.add(check_val_1(90,83, 9))
s.add(check_val_1(9, 11, 15))
s.add(check_val_1(29, 61, 57))
s.add(check_val_6(67, 71, 22103))
s.add(check_val_6(72, 76, 50138))
s.add((substr(flag, 6, 6) == ord("b")))
s.add(check_val_6(37, 41, 19230))
s.add(check_val_6(43, 47, 11202))
s.add(check_val_11(76, "8"))
s.add(check_val_11(93, "3"))
s.add(check_val_11(13, "0"))
s.add(check_val_6(77, 79, 763))
s.add(check_val_6(85, 87, 303))
s.add(check_val_6(59, 61, 753))
s.add(check_val_11(26, "5"))
s.add(check_val_11(87, "3"))
s.add(check_val_11(88, "c"))
s.add(check_val_11(81, "0"))
s.add(check_val_11(86, "0"))
s.add(check_val_11(17, "1"))
s.add(check_val_11(18, "a"))
s.add(check_val_6(39, 41, 230))
s.add(check_val_6(21, 23, 361))
s.add(check_val_11(39, "2"))
s.add(check_val_11(58, "2"))
s.add(check_val_6(51, 53, 713))
s.add(check_val_6(33, 35, 351))
s.add(check_val_11(19, "2"))
s.add(check_val_11(20, "b"))
s.add(check_val_11(31, "3"))
s.add(check_val_6(45, 47, 202))
s.add(check_val_11(44, "1"))
s.add(check_val_11(49, "3"))
s.add(check_val_11(55, "3"))
s.add(check_val_11(44, "1"))
s.add(check_val_11(45, "2"))
s.add(check_val_6(63, 65, 707))
s.add(check_val_11(66, "c"))

if s.check() == sat:
    m = s.model()

    r = b''
    for i in range(1, 95):
        if m[flag[i]] is None:
            print('?', end=" ")
            r += bytes([0])
            continue
        print(m[flag[i]].as_long(), end=" ")
        r += bytes([m[flag[i]].as_long()])
    print()
    print(r)
    
    x = list(b'BHMEAISTHEBESTCTFEVERBETTERTHANALLOFTHEOTHERCTF')
    from pwn import *
    from textwrap import wrap
    chunk = list(map(lambda v: int(v, 16), wrap(r.decode(), 2)))
    print(xor(x, chunk))
    
    # print("".join([chr(m[flag[i]].as_long()) for i in range(1, 94)]))

# b'BHFlagY{Rnt_vu|ns_Of_Seri4liz4t10n_sUp3r_fun!!}'
