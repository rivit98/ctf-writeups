from pwn import *
import itertools
import hashlib
import string
import re

table = string.ascii_letters + string.digits + "._"

def crack(suffix, hashval):
    for v in itertools.product(table, repeat=4):
        if hashlib.sha256((''.join(v) + suffix).encode()).hexdigest() == hashval:
            print("[+] Prefix = " + ''.join(v))
            return ''.join(v)
    else:
        print("[-] Solution not found :thinking_face:")

p = remote('any.ctf.zer0pts.com', 11011)

line = p.recvline().decode()
print(line)
p1, p2 = line.split('=')

res = re.match(r'sha256\("\?\?\?\?(.*)"\)', p1)
p1 = res.group(1)
prefix = crack(p1, p2.strip())

p.sendline(prefix)


p.interactive()


