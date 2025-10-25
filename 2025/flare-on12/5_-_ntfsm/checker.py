#!/usr/bin/env python3
"""
remove_proxies_and_cc_trampolines_limited.py

Like the previous patcher but SKIPS any proxy trampoline whose VA is greater
than TRAMPOLINE_MAX_VA.

Usage:
    python remove_proxies_and_cc_trampolines_limited.py input.exe output.exe
"""
import sys
from collections import defaultdict

from pwn import u32

import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_64

MD = Cs(CS_ARCH_X86, CS_MODE_64)
MD.detail = False

INT3_BYTE = b'\xCC'
JMP_STUB_SIZE = 5  # expecting E9 + 4-byte rel32


def find_text_section(pe):
    for sec in pe.sections:
        if sec.Name.rstrip(b'\x00').startswith(b'.text'):
            return sec
    for sec in pe.sections:
        if sec.characteristics & 0x20000000:  # IMAGE_SCN_MEM_EXECUTE
            return sec
    return None

def find_callsites_and_patches(pe, sec):
    array_size = 0x1629d
    jump_array = 0x140c687b8
    cleanup_func = 0x140c685ee
    next_state_instr = "mov qword ptr [rsp + 0x58d30],"
    compare_char = "cmp byte ptr [rsp + "

    text_rva = sec.VirtualAddress
    image_base = pe.OPTIONAL_HEADER.ImageBase
    text_va = image_base + text_rva
    data = sec.get_data()

    raw_offset = jump_array - text_va

    jumps = [
        u32(data[raw_offset+i*4:raw_offset+i*4+4], sign="unsigned")
        for i in range(array_size)
    ]

    jump_addrs = [
        image_base + jump
        for jump in jumps
    ]

    state_to_func = {
        k: jump_addrs[k] for k in range(array_size)
    }

    reachable = defaultdict(list)
    reachable2 = defaultdict(list)
    func_chars = dict()
    for state_idx, jump in enumerate(jump_addrs):
        output = []
        text_offset = jump - text_va
        for insn in MD.disasm(data[text_offset:text_offset+0x200], jump):
            (address, size, mnemonic, op_str) = (insn.address, insn.size, insn.mnemonic, insn.op_str)
            output.append(f'{hex(address)}: {mnemonic} {op_str}')

            if mnemonic == 'jmp':
                opcode = insn.bytes[0]
                if opcode in (0xE9, ) and size == 5:
                    rel32 = u32(insn.bytes[1:5], sign=True)
                    target = insn.address + insn.size + rel32
                    if target == cleanup_func:
                        break


        # remove everything until jl instruction to strip rdtsc shit
        output = output[output.index(next(filter(lambda line: ': jl ' in line, output)))+1:]

        func_chars[state_idx] = {}
        prev_char = None
        to_figureout = []
        for line in output:
            if next_state_instr in line:
                next_state = int(line.split(next_state_instr)[1].strip(), 16)
                if next_state in state_to_func:
                    reachable[state_idx].append(state_to_func[next_state])
                    reachable2[state_idx].append(next_state)

            elif compare_char in line:
                compare_offset = int(line.split(',')[-1], 16)
                prev_char = chr(compare_offset)

            elif 'je ' in line:
                assert prev_char is not None
                target = int(line.split('je ')[1], 16)
                # print(f'{target:#x} {state_to_func.get(target, None)}')
                to_figureout.append((target, prev_char))
                # func_chars[state_idx][state_to_func[target]] = prev_char


        for line in output:
            if next_state_instr in line:
                next_state = int(line.split(next_state_instr)[1].strip(), 16)
                current_address = int(line.split(':')[0], 16)
                for (target, char) in to_figureout:
                    # print(f'Checking if {target:#x} == {current_address:#x}')
                    if target == current_address:
                        func_chars[state_idx][next_state] = char
                        print(f'From state {state_idx} with char {char} can go to {next_state:#x}')

        # print('State', state_idx, 'at', hex(jump), 'can reach states:', [hex(k) for k in reachable[state_idx]])
        full = '\n'.join(output) + '\n'
        # if 'inc rax' in full:
        #     print(full)

        # print('='*80)

    # for k, v in reachable2.items():
    #     print(f'State {k} can reach states: {v}')

    g = dict(reachable2)
    with open("g", "wb") as f:
        import pickle
        pickle.dump({"g": g, "state_to_func": state_to_func, "func_chars": func_chars}, f)

def try_solve():
    with open("g", "rb") as f:
        import pickle
        data = pickle.load(f)

    g = data["g"]
    state_to_func = data["state_to_func"]
    func_chars = data["func_chars"]

    # for k, v in func_chars.items():
    #     if v:
    #         print(k, v)

    winners = []
    for k in g:
        res = dfs(g, k,0, [k])
        if res:
            winners.append(res)

    for w in winners:
        print(w)

    w = winners[0]
    print(w)
    password = []
    for (curr, next) in zip(w, w[1:]):
        func = state_to_func[curr]
        char = func_chars[curr][next]
        password.append(char)
        print(f'state: {curr} {hex(func)} chars: {char} -> next state:{next:#x}')


    print('Password:', ''.join(password))
    # iqg0nSeCHnOMPm2Q


def dfs(g, current, depth, state):
    if depth == 0x10:
        print(current, state)
        return state

    for neighbor in g.get(current, []):
        if ret := dfs(g, neighbor, depth + 1, state + [neighbor]):
            return ret

    return []



if __name__ == '__main__':
    inp = sys.argv[1]
    if inp == 'dfs':
        try_solve()
        sys.exit(0)

    try:
        pe = pefile.PE(inp)
    except Exception as e:
        print("Failed to parse PE:", e)
        sys.exit(2)

    text_sec = find_text_section(pe)
    if not text_sec:
        print("No .text or executable section found.")
        sys.exit(3)

    patches = find_callsites_and_patches(pe, text_sec)
