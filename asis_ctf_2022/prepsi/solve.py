import string

lines = open("output.txt", "rt").read().strip().splitlines()


class Line:
    def __init__(self, fake_data, d, i):
        self.data = fake_data.removeprefix("ASIS{")[:-1]
        self.d = int(d.split('=')[1])
        self.i = int(i.split('=')[1])


data = []
for line in lines:
    fake, d, i = line.split(',')
    data.append(Line(fake, d, i))

possibs = [set(string.printable[:62] + '!?@-_{|}') for i in range(40)]

for d in data:
    if d.d == 40:
        for i, c in enumerate(d.data):
            possibs[i].discard(c)

print(possibs)
print("ASIS{" + ''.join([list(x)[0] for x in possibs]) + "}")
