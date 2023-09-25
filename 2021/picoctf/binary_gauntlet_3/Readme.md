# PicoCTF 2021, binary gauntlet 3, pwn

## Solution

Format string to leak libc address (__libc_start_main_ret), calculate libc base, use one_gadget and pop the shell.

Solve script: [go.py](./go.py)
