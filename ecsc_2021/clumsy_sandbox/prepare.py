from pwn import *
import sys

with open(sys.argv[1], "rb") as f:
	data = f.read()

with open("./input", "wb") as f:
	f.write(p32(len(data)) + data)
