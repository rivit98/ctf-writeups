import sys
import ctypes

def main(nick):
    if len(nick) != 10:
        print("nick must be ten characters long")
        return

    pass_sum = 0
    weird_number = 0x80899
    expected_serial = 7

    for b in nick.encode("ascii"):
        pass_sum += b
        weird_number += pass_sum

    expected_serial *= weird_number + pass_sum

    edx = weird_number + (weird_number >> (0x1f + 0x1f))
    edx >>= 1
    eax = (((edx * 2) + edx) << 2) + edx
    edx = eax + expected_serial - pass_sum

    expected_serial *= edx
    expected_serial &= (2 ** 32) - 1

    cint = ctypes.c_int32(expected_serial)
    if cint.value < 0:
        cint.value *= -1

    print(f"{nick}:{cint.value}")


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("usage: keygen.py nick")
        sys.exit(1)

    main(sys.argv[1])