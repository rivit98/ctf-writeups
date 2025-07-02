from pwn import *
from dataclasses import dataclass

"""
vm PC = 0x1000
vm SP = 0x8F00

stackVM

iter: 1b op + 4b arg

0x10: push arg 1b
0x20: push arg 2b
0x30: push arg 4b
0x40: push [arg]
0x50: pop 4b
0x60: add
0x61: sub
0x62: xor
0x63: and
0x70: pc = arg
0x71: jnz arg
0x72: jz arg
0x80: cmp, sets flag reg
0xa0: syscall 
    pops 1b from stack, call it syscall type
    0x0: push getint()
    0x1: unsupported
    0x2: print(ptr: stack[arg1], len: stack[arg2])
    0x3: srand(stack[arg1])
    0x4: push rand32()
    0x5: print_flag from getenv
    0x6: read(ptr: stack[arg1], len: stack[arg2])
0xff: halt
"""

syscalls = {
    0x0: "getint",
    0x1: "unsupported",
    0x2: "print",
    0x3: "srand",
    0x4: "rand32",
    0x5: "print_flag",
    0x6: "xxx",
}

SEGMENT_HEADER = 5
def parse_segment(d):
    return u8(d[:1]), u16(d[1:3]), u16(d[3:5])



def stack_vm(file):
    potential_syscall = None
    data = open(file, "rb").read()
    magic = data[:4]
    code_segment_type, code_offset, code_size = parse_segment(data[4:4+SEGMENT_HEADER])
    print(f"Magic: {magic}")
    print(f"code Type: {code_segment_type:#x}, Offset: {code_offset:#x}, Size: {code_size:#x}")

    rodata_segment_type, rodata_offset, rodata_size = parse_segment(data[4 + SEGMENT_HEADER:4 + SEGMENT_HEADER + SEGMENT_HEADER])
    print(f"rodata Type: {rodata_segment_type:#x}, Offset: {rodata_offset:#x}, Size: {rodata_size:#x}")

    seg3ment_type, segment_offset, segment_size = parse_segment(data[4 + 2 * SEGMENT_HEADER:4 + 3 * SEGMENT_HEADER])
    print(f"data Type: {seg3ment_type:#x}, Offset: {segment_offset:#x}, Size: {segment_size:#x}")

    code = data[code_offset:code_offset + code_size]
    pc = 0

    while True:
        d = code[pc:pc + 5]
        op, arg = u8(d[:1]), u32(d[1:5])

        print(f'{pc:#x}: ', end='')

        if op == 0x10:
            print(f"PUSH1 {arg:#x}")
            potential_syscall = arg
        elif op == 0x20:
            print(f"PUSH2 {arg:#x}")
        elif op == 0x30:
            print(f"PUSH4 {arg:#x}")
        elif op == 0x40:
            print(f"PUSH4 [{arg:#x}]")
        elif op == 0x50:
            print(f"POP4 {arg:#x}")
        elif op == 0x60:
            print("ADD")
        elif op == 0x61:
            print("SUB")
        elif op == 0x62:
            print("XOR")
        elif op == 0x63:
            print("AND")
        elif op == 0x70:
            print(f"PC = {arg:#x}")
        elif op == 0x71:
            print(f"JNZ {arg:#x}")
        elif op == 0x72:
            print(f"JZ {arg:#x}")
        elif op == 0x80:
            print(f"CMP")
        elif op == 0xff:
            print("HALT")
        elif op == 0xa0:
            print(f"SYSCALL ({syscalls.get(potential_syscall, 'unknown')})")

        else:
            print(f"UNKNOWN {op:#x} {arg:#x}")

        pc += 5



def reg_vm(file):
    syscalls = {
        0x0: "getint",
        0x1: "read",
        0x2: "print",
        0x3: "srand",
        0x4: "rand32",
        0x5: "unsupported",
        0x6: "mem_magic",
    }

    data = open(file, "rb").read()
    code_segment_type, code_offset, code_size = parse_segment(data[4:4+SEGMENT_HEADER])
    code = data[code_offset:code_offset + code_size]
    pc = 0x5a

    def handle_c0(v4, op, dst):
        nonlocal pc
        if v4 >> 2:
            if ( ((op >> 3) & 4) != 0 ):
                pass
            else:
                print(f'STORE4 vm->regs[{dst:#x}], temp')
        else:
            if ( (op & 0x20) == 0 ):
                print(f'vm->regs[{dst:#x}] = temp')
            if ( dst != 4 or (op & 7) == 6 ):
                pass
            else:
                arg = u32(code[pc:pc + 4])
                pc += 4
                print(f'STORE4 [{arg:#x}] = temp')

    while True:
        v4 = 0
        op = u8(code[pc:pc + 1])
        pc += 1

        print(f'{pc:#x}: ', end='')

        if op >> 4 == 0xA:
            op = u8(code[pc:pc + 1])
            pc += 1
            v4 = op & 0xF
            print(f"DOUBLE LEN OPCODE: {op:#x} {v4:#x}")
        elif op & 0xc0:
            v9 = op & 7
            v10 = v4 & 3
            dst = ((op >> 3) & 7)

            if op & 4 == 0:
                print(f'temp = vm->regs[{op & 7:#x}]')
                handle_c0(v4, op, dst)
            elif v9 == 4:
                arg = u32(code[pc:pc + 4])
                pc += 4
                print(f"temp = {arg:#x}; FETCH4 [{arg:#x}]")
                handle_c0(v4, op, dst)
            elif v9 == 5:
                arg = u32(code[pc:pc + 4])
                pc += 4
                print(f"temp = {arg:#x}")
                handle_c0(v4, op, dst)
            elif v9 == 6:
                print(f'temp = [sp]')
                handle_c0(v4, op, dst)

            if v10:
                continue
        elif op == 0:
            # print("NOP")
            continue
        elif op == 0x1:
            print("SYSCALL")
        elif op == 0x10:
            arg = u32(code[pc:pc + 4])
            pc += 4
            print(f'PUSH4 {arg:#x}')
        elif op == 0x20:
            arg = u8(code[pc:pc + 1])
            pc += 1

            dst = ((arg >> 4) -1 ) & 3
            src = (arg - 1) & 3
            print(f"vm->regs[{dst:#x}] += vm->regs[{src:#x}]")
        elif op == 0x21:
            temp = u8(code[pc:pc + 1])
            pc += 1
            tmp = u32(code[pc:pc + 4])
            pc += 4

            dst = (temp >> 4) - 1
            print(f"vm->regs[{dst:#x}] += {tmp:#x}")
        elif op == 0x30:
            arg = u8(code[pc:pc + 1])
            pc += 1
            dst = (arg >> 4) -1 
            src = (arg & 0xF) - 1
            print(f"vm->regs[{dst:#x}] -= vm->regs[{src:#x}]")
        elif op == 0x31:
            temp = u8(code[pc:pc + 1])
            pc += 1
            tmp = u32(code[pc:pc + 4])
            pc += 4
            dst = (temp >> 4) - 1
            if dst <= 3:
                print(f"vm->regs[{dst:#x}] -= {tmp:#x}")
            else:
                print(f'vm->sp -= {tmp:#x}')
        elif op == 0x40:
            arg = u8(code[pc:pc + 1])
            pc += 1
            dst = (arg >> 4) -1 
            src = (arg & 0xF) - 1
            print(f"vm->regs[{dst:#x}] ^= vm->regs[{src:#x}]")
        elif op == 0x41:
            raise NotImplemented
        elif op - 17 <= 3:
            print(f"PUSH4 vm->regs[{op - 17:#x}]")
        elif op - 21 <= 3:
            print(f"POP4 vm->regs[{op - 21:#x}]")
        else:
            print(f"UNKNOWN {op:#x}")
            break




if __name__ == "__main__":
    import sys
    stack_vm(sys.argv[1])
    # reg_vm(sys.argv[1])


# zrobil 5 (fetch4 -> 2)
# read z stdin na 0x8EE0; len 0x20

# Challenge 2 - Tell me a joke:


# %{a}T_E7Q4M+/y"&me??Z 'Q\d`%RF "



seed: 0x7b

0x9E95C3A1