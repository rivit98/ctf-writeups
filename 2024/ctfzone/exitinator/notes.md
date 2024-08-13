dprintf *__run_exit_handlers+356,"rax=0x%llx\n",$rax
b *__run_exit_handlers+289


```py
addrs = [
0x7ffff7d83402,
0x7ffff7d81f34,
0x7ffff7d5dcf3,
0x7ffff7c3ace0,
0x7ffff7d1c106,
0x7ffff7d0f99b,
0x7ffff7d83402,
0x7ffff7d81f34,
0x7ffff7d5dcf3,
0x7ffff7c3ace0,
0x7ffff7d1c106,
0x7ffff7d0f99b,
0x7ffff7d83402,
0x7ffff7d81f34,
0x7ffff7d5dcf3,
0x7ffff7c3ace0,
0x7ffff7d1c106,
0x7ffff7d0f99b,
0x7ffff7d83402,
0x7ffff7d81f34,
0x7ffff7d5dcf3,
0x7ffff7c3ace0,
]


import pwndbg.gdblib.memory
r = pwndbg.gdblib.memory.read

for a in addrs:
    print(r(a, 0x10)[2])

```
