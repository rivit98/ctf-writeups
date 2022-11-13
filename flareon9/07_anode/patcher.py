import sys


data = open("anode.exe", "rb").read()
code = open(sys.argv[1], "rb").read()
data = bytearray(data)

to_replace = b'readline.question(`Enter flag: `, flag => {'

script_start = data.index(to_replace)
script_end = data.index(b'});', script_start) + 3
code_len = script_end - script_start
code = code.ljust(code_len, b" ")

for i in range(code_len):
	data[script_start+i] = code[i]

open("anode_patched.exe", "wb").write(data)

