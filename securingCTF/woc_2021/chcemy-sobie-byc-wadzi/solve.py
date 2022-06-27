from binascii import unhexlify

with open("./changed-words.txt", "rt", encoding='utf8') as f:
    rows = f.readlines()


rows = filter(lambda r: len(r) > 2, rows)
rows = map(lambda r: r.split('-')[0].strip(), rows)
rows = map(lambda r: len(r), rows)
rows = map(lambda r: hex(r)[2:], rows)

print(unhexlify(''.join(rows)))
