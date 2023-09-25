# DiceCTF 2021, babyrop, pwn

## Description
"FizzBuzz101: Who wants to write a ret2libc"

## Solution
We have buffer overflow (`gets`) and we can use ROP technique to get a shell. 
Start with determining how many characters are needed to overflow return address of main function. After that we want to leak libc address, so we need to print address of a function from GOT table (which contains only `gets` and `write`). `write` function needs three arguments:
```c
ssize_t write(int fd, const void *buf, size_t count);
```
We are on 64bits, so args are passed in registers (`rdi`, `rsi`, `rdx`). Quick look for gadgets - we can control `rdi` and `rsi`, but `rdx` requires technique called `ret2csu`. This requires adjusting `r15`, `rbp` (due to internals of csu func). After setting everything properly we can call our `write` function with following arguments:
```c
write(1, address_of_gets_in_got, 8);
```
which gives us `gets` address. Now we can look for proper glibc (`libc6_2.31-0ubuntu9.2_amd64` in this case), calculate base address, find `/bin/sh`, `system`, `exit` offsets and use `pop rdi` gadget to call system. After this we got a shell.

Solve script: [go.py](./go.py)
