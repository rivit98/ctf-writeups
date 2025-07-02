import multiprocessing
from pwn import *

context.log_level = 'error'

def worker(num):
    if num % 10000 == 0:
        print(f"Processing: {num}/{0xFFFFFFFF+1}")
    p  = process(argv=["./multiarch", "crackme.masm"])
    p.sendlineafter(b'number?', b'2405061754')
    p.sendlineafter(b'joke', b'%{a}T_E7Q4M+/y"&me??Z \'Q\d`%RF "')
    p.sendlineafter(b'the future?', str(num).encode())
    output = p.recvall(timeout=0.1)
    if b'Congrats' in output:
        print(f"Found: {num}")
        with open("found.txt", "a") as f:
            f.write(f"{num}\n")


if __name__ == "__main__":
    with multiprocessing.Pool() as pool:
        for res in pool.imap_unordered(worker, range(0xFFFFFFFF+1)):
            pass

# jMIWcuebYmzYaOgjA1NU
#  470 000/4 294 967 296