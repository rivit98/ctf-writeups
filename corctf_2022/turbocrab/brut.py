target = 'dc136f8bf4ba6cc1b3d2f35708a0b2b55cb32c2deb03bdab1e45fcd1102ae00a'

almost_flag = 'corctf{xIG_jit_vm_reversingN}'
# corctf{xIG_j@t_vm_rBvBrs@ngN}
import string
import hashlib



for c3 in string.printable:
	print(c3)
	for c4 in string.printable:
		for c6 in string.printable:
			new_flag = f'corctf{{x{c4}{c3}_j1t_vm_r3v3rs1ng{c6}}}'
			if hashlib.sha256(new_flag.encode('utf-8')).hexdigest() == target:
				print("FOUND", new_flag)
				exit(1)
			# print(new_flag)
