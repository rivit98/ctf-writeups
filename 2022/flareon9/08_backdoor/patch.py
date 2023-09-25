import os 
from pwn import unhex
import shutil

def read_methodbase():
	lines = open("methodBase.txt", "rt").read().splitlines()[1:]

	method_base = {}
	token_to_name = {}
	for line in lines:
		# RID	Token	Offset	RVA	ImplFlags	Flags	Name	Signature	ParamList	Info
		# 1	0x06000001	0x0001C09C	0x2194	0	0x96	1	0xA	1	flared_00
		tokens = line.split('\t')
		rid, token, offset, rva, impleFlags, flags, name, sig, param, info = tokens

		method_base[int(token, 16)] = int(rva, 16) + 0x7000  # file offset
		method_base[info] = method_base[int(token, 16)]
		token_to_name[int(token, 16)] = info

	return method_base, token_to_name


methodBase, token_to_name = read_methodbase()
# shutil.rmtree("patches")
os.makedirs("patches", exist_ok=True)

lines = open("Output-Debug.txt", "rt").read().splitlines()
lines = list(filter(
	lambda line: "FlareOn.Backdoor.FLARE15.flare_67" in line,
	lines
))

parsed_new = {}
bytecode_for_method = None
for line in lines:
	if not  'after_call_method' in line: continue
	# 12:23:21.657 FlareOn.Backdoor.FLARE15.flare_67(byte[], int, object[]) "call_method: 100663420 bytecode: 00022838A698A80A2B00062A"
	line = line[line.index('"'):].strip('"')
	_, metadataToken, _, new_bytecode = line.split(" ")

	# print(metadataToken, new_bytecode)
	parsed_new[int(metadataToken)] = new_bytecode


with open("./FlareOn.Backdoor-patched.exe", "rb") as f:
	program = bytearray(f.read())


for k in parsed_new.keys():
	new = unhex(parsed_new.get(k))
	method_name = token_to_name[k]
	offset = methodBase[k] + 0xC # skip method header
	# print(f'applying patch for {method_name}, offset {offset:#x}, len {len(new):#x}')

	if not os.path.exists(f'patches/{method_name}.new'):
		print(f'new patch for {method_name}, offset {offset:#x}, len {len(new):#x}')
		with open(f'patches/{method_name}.new', "wb") as fnew:
			fnew.write(new)

	for i, patch_byte in enumerate(new):
		program[offset+i] = patch_byte


with open("FlareOn.Backdoor-patched2.exe", "wb") as f:
	f.write(program)
