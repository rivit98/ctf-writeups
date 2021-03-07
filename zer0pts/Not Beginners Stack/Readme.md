# DiceCTF 2021, not beginners stack, pwn

## Description
Elementary pwners love to overwrite the return address. This time you can't!

## Solution
We have binary which is using array as stack, so we cannot override return addresses directly, but... we can overflow RBP pointer to get arbitrary write. Since the binary has no ASLR and there are two `read`'s. So we overwrite RBP, store shellcode on 'new stack' and also overwrite return address (ofc on 'new stack') and thats is, we got the shell.
