from pwn import *
import subprocess

p = remote('secure-asset-manager-4235c8a4.challenges.bsidessf.net', 6112)


def parse_msg(msg):
    l = u16(msg[:2])
    print(f'[{l}] | {msg[2:]}')
    return msg[2:]


def send_msg(content):
    p.send(p16(len(content)))
    p.send(content)


parse_msg(p.recv())

my_version = b"secure-asset-manager client v1.00\x00"
send_msg(my_version)

challenge = p.recv()
challenge = parse_msg(challenge)

with open("server_challenge_code", "wb") as f:
    f.write(challenge)


# print(disasm(challenge))

subprocess.run("nasm -f elf64 challenge.asm".split())
subprocess.run("gcc -nostartfiles -no-pie challenge.o -o calc_challenge".split())

res = 0
try:
    res = subprocess.check_output("./calc_challenge", shell=True)
    print("[+] Challenge code " + hex(int(res.decode())))
except subprocess.CalledProcessError as e:
    print("error code", e.returncode, e.output)

res = int(res.decode())
send_msg(p32(res))

res = p.recv()
res = parse_msg(res)

send_msg(b"CHECK_UPDATES")
res = p.recv()
res = parse_msg(res)


send_msg(b"I_AM admin")
res = p.recv()
res = parse_msg(res)


send_msg(b"HELP")
res = p.recv()
res = parse_msg(res)


send_msg(b"FLAG")
res = p.recv()
res = parse_msg(res)


