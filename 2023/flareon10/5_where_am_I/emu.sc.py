from contextlib import contextmanager

from unicorn import *
from unicorn.x86_const import *
from capstone import *
from pwn import *
from pefile import PE

SC_ADDR = 0x800_000
FAKE_CALLS = SC_ADDR-0x2000
BASE = 0x400_000
_2MB = 2 * 1024 * 1024
TIB = 0
PEB = 0x1000


def dump_regions():
    for start, end, perms in uc.mem_regions():
        perm = ""
        if perms & 1:
            perm += 'r'
        if perms & 2:
            perm += 'w'
        if perms & 4:
            perm += 'x'

        print(f"  {start:#010x} - {end:#010x}  {perm}")


def dump_regs():
    output = ['-' * 10]
    names = [ "EAX", "EBP", "EBX", "ECX", "EDI", "EDX", "XXX", "EIP", "XXX", "XXX", "ESI", "ESP" ]
    for i, reg in enumerate(range(UC_X86_REG_EAX, UC_X86_REG_ESP+1)):
        if names[i] == "XXX": continue
        output.append(f'{names[i]} {uc.reg_read(reg):#x}')

    print('\n'.join(output))

def dump_stack(num=10):
    for i in range(num):
        a = uc.reg_read(UC_X86_REG_ESP) + i * 4
        v = u32(uc.mem_read(a, 4))
        print(f'{a:#x}: {v:#08x}')

def load_resource(idx, idx2):
    for res in pe.DIRECTORY_ENTRY_RESOURCE.entries:
        if res.id == idx:
            for entry in res.directory.entries:
                if entry.id == idx2:
                    return entry.directory.entries[0]


free_res_ids = [0x1337 + i for i in range(10)]
free_memory_maps = [0x30000 + i for i in range(0, 0x10000, 10)]
resources = {}


def get_args(args_num):
    return tuple(u32(uc.mem_read(uc.reg_read(UC_X86_REG_ESP) + i * 4, 4)) for i in range(args_num))


@contextmanager
def call(args_num):
    try:
        yield get_args(args_num)
    except:
        pass


def LoadResource():
    with call(2) as (arg1, arg2):
        size, data_ptr = resources[arg2]
        return data_ptr


def FindResourceA():
    with call(3) as (arg1, arg2, arg3):
        res = load_resource(arg2, arg3)
        res_id = free_res_ids.pop(0)
        resources[res_id] = (res.data.struct.Size, BASE + res.data.struct.OffsetToData)
        return res_id


def SizeofResource():
    with call(2) as (arg1, arg2):
        size, data_ptr = resources[arg2]
        return size


def VirtualAlloc():
    with call(4) as (arg1, arg2, arg3, arg4):
        mem = free_memory_maps.pop(0)
        uc.mem_map(mem, memalign(arg2, 0x1000))
        dump_regions()
        return mem


def dummycall():
    return 0


known = {
    0x460210: ("SetErrorMode", dummycall, 1),
    0x47838c: ("GetSystemDefaultLangID", dummycall, 0),
    0x478390: ("GetAtomNameA", dummycall, 3),
    0x4603d8: ("FindResourceA", FindResourceA, 3),
    0x4603e4: ("SizeofResource", SizeofResource, 2),
    0x4603dc: ("LoadResource", LoadResource, 2),
    0x4603e0: ("LockResource", dummycall, 1),
    0x46023c: ("VirtualAlloc", VirtualAlloc, 4),
}


def hook_code(uc, address, size, user_data):
    instr = next(cs.disasm(uc.mem_read(address, size), address, 1))

    if 'jmp' in instr.mnemonic:
        return

    if CS_GRP_CALL in instr.groups and '[' in instr.op_str:
        try:
            arg = instr.op_str
            arg = arg[arg.index('[') + 1:][:-1]
            arg = int(arg, 16)
            name, ret, _ = known.get(arg)
            print(hex(instr.address), instr.mnemonic, instr.op_str, name)
            return
        except Exception as e:
            print(e)
            print(instr.op_str)
            raise

    print(hex(instr.address), instr.mnemonic, instr.op_str)


def hook_mem_access(uc, access, address, size, value, a):
    print(f"hook_mem_access: {address:#x}")
    data = known.get(address)
    dump_stack()
    if data:
        dump_regs()

        _, ret, args_num = data
        patch(address, ret(), args_num)

    return True



def patch(address, ret, args_num):
    global FAKE_CALLS
    info(f"Patching {address:#x} with {FAKE_CALLS:#x} to return {ret:#x}")
    a = asm(f'''
    mov eax, {ret}
    pop ecx
    add esp, {args_num*4}
    jmp ecx
    ''')
    uc.mem_write(FAKE_CALLS, a)
    uc.mem_write(address, p32(FAKE_CALLS))
    FAKE_CALLS += 0x20


def main():
    code = open("./firsc_sc", "rb").read()
    uc.mem_map(SC_ADDR, _2MB)
    uc.mem_write(SC_ADDR, code)

    uc.mem_map(FAKE_CALLS, 0x2000, 7)

    uc.mem_map(TIB, 0x1000, 1)
    uc.mem_write(TIB, fit({0x30: PEB}))
    uc.mem_map(PEB, 0x1000, 1)
    uc.mem_write(PEB, fit({0x8: BASE}))

    orig_code = open("./where_am_i.exe", "rb").read()
    uc.mem_map(BASE, 0x1000)
    uc.mem_write(BASE, orig_code[:0x1000])

    for section in pe.sections:
        virtual = BASE + section.VirtualAddress
        size = section.SizeOfRawData
        aligned_size = memalign(size)

        uc.mem_map(virtual, aligned_size)
        uc.mem_write(virtual, section.get_data())

    stack_base = 0xf000_0000
    stack_size = 0x1_000_000
    uc.mem_map(stack_base, memalign(stack_size))
    uc.reg_write(UC_X86_REG_ESP, stack_base + stack_size)
    uc.reg_write(UC_X86_REG_EIP, SC_ADDR)

    dump_regs()

    uc.hook_add(UC_HOOK_CODE, hook_code)
    uc.hook_add(UC_HOOK_MEM_READ, hook_mem_access)
    uc.emu_start(SC_ADDR, SC_ADDR + len(code))

def memalign(v, a=0x1000):
    return ((v // a) + 1) * a


if __name__ == '__main__':
    cs = Cs(CS_ARCH_X86, CS_MODE_32)
    cs.detail = True
    uc = Uc(UC_ARCH_X86, UC_MODE_32)
    pe = PE("./where_am_i.exe")
    main()

