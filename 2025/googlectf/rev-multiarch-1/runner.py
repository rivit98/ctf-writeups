import os

try:
    with open("/flag", "r") as f:
        flag = f.read().strip()
except FileNotFoundError:
    flag = "CTF{fake_flag}"

MULTIARCH_PATH = "/home/user/multiarch"
CRACKME_PATH = "/home/user/crackme.masm"

os.environ["FLAG"] = flag
os.system(f"timeout 15 {MULTIARCH_PATH} {CRACKME_PATH}")