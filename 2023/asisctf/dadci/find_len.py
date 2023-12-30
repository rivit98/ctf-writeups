import os

# find 343 encrypted len
# just to dump mask from memory
for i in range(0x100):
    with open("./flag.txt", "wt") as f:
        f.write('A' * i)

    os.system('./dadci.elf')

    with open("./flag.enc", "rb") as f:
        d = f.read()

    print(f'{i} {len(d)}')
    if len(d) == 343:
        break
