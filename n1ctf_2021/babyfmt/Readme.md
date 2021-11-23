# N1CTF 2021, babyFMT, pwn

## Solution

Steps:
- fill tcache bin
- leak main_arena with unsorted bin
- calculate libc base address
- investigate `babyprintf` function
- it allows using only two tags - `%m` and `%r`
- there is a bug related to tag handling which allows you to do heap overflow
- with `%\00` you can bypass length check in `babyprintf`
- steal tcache bin pointer to get arbitrary write
- overwrite `__free_hook` with `system`
- do `show("/bin/sh\x00)` which spawns the shell

Solve script: [solve.py](./solve.py)

flag: `n1ctf{BBBBBBaby_format_string}`
