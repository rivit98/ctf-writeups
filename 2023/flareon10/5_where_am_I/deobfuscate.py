import itertools

from capstone import *
from pwn import asm

BASE = 0x800_000
blocks = {}


class Block:
    def __init__(self, base):
        self.addresses = set()
        self.instructions = []
        self.base = base
        self.children = []

    def add_instr(self, a, i):
        self.addresses.add(a)
        self.instructions.append(i)

    def __repr__(self):
        return f'Block @{self.base:#08x}'


def discover_blocks(code, ip, current_block: Block):
    # if we were here
    if any(ip in b.addresses for b in blocks.values()):
        # print(f"was here before (call) {ip:#08x}")
        return

    # print(f"discover_blocks {ip:#08x} {current_block}")
    # while ip < 0x666 + BASE:
    while ip < 0x66666 + BASE:
        instr = next(cs.disasm(code[ip-BASE:], ip, 1))
        # print(hex(instr.address), instr.mnemonic, instr.op_str)

        # what if we jump into a known address?
        # there should be a map of known addresses to blocks, then target block should be split into two blocks
        if any(ip in b.addresses for b in blocks.values()):
            # print(f"was here before (jmp) {ip:#08x}")
            blocks[current_block.base] = current_block
            break

        if CS_GRP_JUMP in instr.groups:
            if 'jmp' in instr.mnemonic:
                # go to the next instr (same block)
                current_block.add_instr(ip, instr)
                ip = int(instr.op_str, 16)
            else:
                current_block.add_instr(ip, instr)

                # conditional block - end the current block and create two new ones and explore recursively
                new_ip = ip + instr.size
                next_block = Block(new_ip)

                new_ip2 = int(instr.op_str, 16)
                jump_taken_block = Block(new_ip2)

                # current block has two children
                current_block.children.append(next_block)
                # current_block.add_instr(ip, next(cs.disasm(asm(f"jmp {new_ip}", vma=new_ip), new_ip, 1)))
                current_block.add_instr(ip, (ip, new_ip))
                current_block.children.append(jump_taken_block)
                blocks[current_block.base] = current_block

                # first one - next instruction (jump not taken)
                discover_blocks(code, new_ip, next_block)

                # second one - jump taken
                discover_blocks(code, new_ip2, jump_taken_block)

                # stop discovery of current block
                break

        elif CS_GRP_CALL in instr.groups:
            try:
                # tricky - calls return, so need to create new block and explore it
                new_ip = int(instr.op_str, 16)
                call_taken = Block(new_ip)
                discover_blocks(code, new_ip, call_taken)

                # add child and continue
                current_block.children.append(call_taken)
                current_block.add_instr(ip, instr)
            except:
                # print("unknown call")
                current_block.add_instr(ip, instr)

            ip += instr.size

        elif CS_GRP_RET in instr.groups:
            # end current block
            current_block.add_instr(ip, instr)
            blocks[current_block.base] = current_block

            # stop discovery
            break
        else:
            # instructions other that jump/call - append to the current block
            current_block.add_instr(ip, instr)
            ip += instr.size

    else:
        raise SystemExit("end")

def main():
    code = open("./firsc_sc", "rb").read()

    discover_blocks(code, BASE, Block(BASE))

    must_preserve = set()
    for block in sorted(blocks.values(), key=lambda b: b.base):
        for idx, instr in enumerate(block.instructions):
            if isinstance(instr, tuple):
                arg1, arg2 = instr
                # emit unconditional jump if block is not taken
                target_block = blocks[arg2]
                target_instruction = target_block.instructions[0].address
                must_preserve.add(target_instruction)
                continue

            if idx == len(block.instructions)-1:
                must_preserve.add(instr.address)

            op_str = instr.op_str
            if CS_GRP_JUMP in instr.groups or CS_GRP_CALL in instr.groups and 'dword' not in op_str and 'jmp' not in instr.mnemonic:
                must_preserve.add(int(instr.op_str, 16))

    print('global main')
    print('_start:')
    print('main:')
    for block in sorted(blocks.values(), key=lambda b: b.base):
        for idx, instr in enumerate(block.instructions):
            if isinstance(instr, tuple):
                arg1, arg2 = instr
                # emit unconditional jump if block is not taken
                target_block = blocks[arg2]
                target_instruction = target_block.instructions[0].address
                print(f'jmp _{target_instruction:#x}')
                continue

            if 'jmp' in instr.mnemonic and idx != len(block.instructions)-1 and instr.address not in must_preserve:
                continue

            op_str = instr.op_str
            if CS_GRP_JUMP in instr.groups or CS_GRP_CALL in instr.groups and 'dword' not in op_str:
                op_str = f'_{op_str}'

            print('_' + hex(instr.address) + ': ', instr.mnemonic, op_str.replace('ptr', ''))

        # print(block.children)
        # print('-'*20)

        print()
        print()

    # with open("raw_sc_data", "wb") as f:
    #     f.write(code[0x640:])
    # print('section .data')
    # print('incbin "raw_sc_data"')

if __name__ == '__main__':
    cs = Cs(CS_ARCH_X86, CS_MODE_32)
    cs.detail = True
    main()

