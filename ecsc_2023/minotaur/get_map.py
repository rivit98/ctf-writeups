from pwn import *
import marshal

context.terminal = ["remotinator", "vsplit", "-x"]

exe = context.binary = ELF('./minotaur')

p = gdb.debug([exe.path], api=True, gdbscript='''
brva 0x1561
continue
''')

p.sendlineafter(b'destination.', b"ECHO")


map = [
    [None for j in range(0x80)] for i in range(0x80)
]

sleep(2)

for i in range(0x80):
    for j in range(0x80):
        map[i][j] = int(p.gdb.parse_and_eval(f"((int(*)(int,int))0x555555554000+0x138A)({i}, {j})"))

    print(i)

with open("mapdump", "wb") as f:
    marshal.dump(map, f)

p.interactive()

