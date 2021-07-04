letters =    "abcdefghijklmnopqrstuvwxyz"
translated = "ungvdejoctaywplbkzitmrsfhz"

table = {k: v for k, v in zip(letters, translated)}


text = open('./rozmowa.txt', 'rt', encoding='utf8').read()

out = []
for c in text.lower():
    if c not in letters:
        out.append(c)
        continue

    nl = table.get(c)
    if nl and nl != '1':
        out.append(nl)
    else:
        print("no translation for", c)
        break

print(''.join(out))
