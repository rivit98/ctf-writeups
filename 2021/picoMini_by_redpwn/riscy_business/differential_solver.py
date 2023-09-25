import os
import string
from multiprocessing import Pool
import operator

found = 'picoCTF{'

def f(c):
	try_flag = found + c
	file = f'dumps/dump_{ord(c)}'
	os.system(f'echo "{try_flag}" | qemu-riscv64 -d nochain,cpu,in_asm -singlestep ./riscy > /dev/null 2>{file}')
	file_size = os.stat(file).st_size
	print(f'{c} -> {file_size}')
	return (c, file_size)


while '}' not in found:
	os.system("rm -- dumps/*")

	with Pool(8) as pool:
		results = pool.map(f, string.ascii_letters + string.digits + '_@')
	
	c, file_size = max(results, key=operator.itemgetter(1))
	found += c
	print(found)


# after some reversing it turned out that the program compares data char by char and exitting early if there is a mismatch
# we can make use of that and trace program execution length and brute flag char by char
