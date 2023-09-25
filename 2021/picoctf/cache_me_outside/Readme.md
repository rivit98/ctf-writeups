# PicoCTF 2021, cache me outside, pwn

## Solution

We have to overwrite pointer in tcache bins, so we can do arbitrary write. It was funny because BUFSIZ (fgets internal buffer) on my machine has 0x2000 bytes but on remote it has 0x1000 :)

Use pwndbg and vis command, calculate offset and read the flag.

Solve script: [go.py](./go.py)
