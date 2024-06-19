from capstone import *
from pwn import ELF

exe = ELF("./cosmicrayv3revenge", checksec=False)

CODE = exe.data[exe.vaddr_to_offset(0x4015FA):exe.vaddr_to_offset(0x40160a)]

for idx in range(len(CODE)):
    for i in range(8):
        b = bytearray(CODE)
        b[idx] = b[idx] ^ (1<<(7-i))


        md = Cs(CS_ARCH_X86, CS_MODE_64)
        print(f'{idx}:{i}')
        for i in md.disasm(b, 0):
            print("0x%x:\t%s\t%s" %(0x4015FA+i.address, i.mnemonic, i.op_str))
        print()

