

sh = open("./test", "rb").read()


parts = [sh[i*2:i*2+2]  for i in range(len(sh) // 2) ]

out = b'\x90\x90'.join(parts)

# print(list(map(hex, out)))

with open("./test2", "wb") as f:
    f.write(bytes(out))