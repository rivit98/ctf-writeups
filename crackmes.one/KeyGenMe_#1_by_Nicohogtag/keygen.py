import sys

def main(nick):
    ascii_sum = sum(map(ord, nick))

    parts = [
        ((7 * ascii_sum) + 56) / 2,
        ((9 * ascii_sum) + 45) / 2,
        ((8 * ascii_sum) + 32) / 2,
        ((6 * ascii_sum) + 60) / 2
    ]

    print(f"Serial: {'-'.join(map(lambda x: str(round(x)), parts))}")


if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("usage: python keygen.py nick")
        sys.exit(1)

    main(sys.argv[1])
