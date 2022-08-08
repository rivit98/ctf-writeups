# European Cyber Security Challenge Eliminations 2021, easy peasy, pwn

## Description
Don't mind me, just testing this cool new programming languge - Zig.

## Solution
We have Zig binary. 
Program allocates 64kB of memory, makes it executable and fills it with random data (not really random, due to fixed seed) and prints it's address. Extracted data is in [random_data_extracted](./random_data_extracted).
There is buffer overflow using `std_os_read` function which will read 256 chars. Using pwntools we deterine offset - it's 105. Having this - we have to do ROP.

There is only one syscall instruction so we have to use it. [filtered_gadgets](./filtered_gadgets.txt) contains useful gadgets (cleaned up, nojop etc).

We are going to use those gadgets to get arbitrary write (we want to put /bin/sh somewhere):
```
0x00000000000093ef : pop rcx ; ret
0x00000000000031d3 : pop rdx ; ret
0x0000000000005157 : mov dword ptr [rcx - 0x7e], edx ; ret
```

The destination will be mmaped region. So we find an address which contains 0 (null terminator) and start writing /bin/sh 8 bytes before it. We are using edx register so have to do it twice.

The next step would be putting address of /bin/sh into `rdi` register using this gadget:
```
0x00000000000011b3 : pop rdi ; ret
```

We need to set `rax` register to 0x3b (sys_execve), but the only `pop rax` gadget is:
```
0x0000000000009f33 : pop rax ; retf
```
and it is crashing due to `retf` instruction. Another gadget which we can use is (actually pair of gadgets):
```
0x00000000000031d3 : pop rdx ; ret
0x000000000000194c : xchg eax, edx ; pop rsi ; ret
```

It's just swapping `rax` and `rdx` and also seting `rsi` which is perfect for us (we have to zero it).

Now we are ready to call `syscall`
```
0x00000000000022b9 : syscall
```

Flag: ecsc21{r0p-z1g-z4gz}
Solve script: [solve.py](./solve.py)
