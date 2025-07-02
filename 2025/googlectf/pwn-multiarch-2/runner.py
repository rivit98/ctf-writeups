import os
import signal
import sys
import tempfile

TIMEOUT = 3000
MULTIARCH_PATH = "/home/user/multiarch"

def sigalrm(*_):
    print("Too slow!")
    sys.exit(0)

signal.signal(signal.SIGALRM, sigalrm)
signal.alarm(TIMEOUT)

print("===[ Multiarch pwn-a-rizmo")
sz = input("How big is your program? ")

prog = sys.stdin.buffer.read(int(sz.strip()))

with tempfile.NamedTemporaryFile() as tf:
    with open(tf.name, "wb") as f:
        f.write(prog)
    print("running! " + tf.name)
    os.system(f"timeout {TIMEOUT} {MULTIARCH_PATH} {tf.name} 2>&1")
    print("done!")
