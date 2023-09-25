# PicoCTF 2021, binary gauntlet 2, pwn

## Solution

Stack is executable, we have format string bug.
Use format string to leak address of the buffer, prepare nop slide, overwrite return address and pop the shell. 

Solve script: [go.py](./go.py)
