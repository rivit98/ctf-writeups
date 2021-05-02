import sys

def main(nick):
    var14 = 0
    var18 = 0
    var1C = 0

    for c in nick:
        var14 += ((ord(c) << 2) + ord(c)) << 4
                # ((x << 2) + x) << 4
                # ((x * 4) + x) * 16
                # x * 5 * 16
                # x * 80
        var18 = (var18 + var14) ^ 0x32
        var1C += var18 * 4
        var20 = var14 + var18 + var1C

    print("Serial:", hex(var20)[2:])


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("usage: python keygen.py nick")
        sys.exit(1)

    main(sys.argv[1])
