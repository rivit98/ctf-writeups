from pwn import *
import string
from multiprocessing.pool import ThreadPool

alphabet = set(string.printable) - set(string.whitespace)
alphabet = sorted(alphabet)
flag = list('A' * 0x2e)

def worker(c, idx, flag):
    if event.is_set():
        return
    with gdb.debug("./go-power-rangers_strip",
                gdbscript=
                f'''
                b *0x4db354
                c
                ''',
                api=True) as p:
    
        test_flag = flag[:]
        test_flag[idx] = c
        test_flag = ''.join(test_flag)

        p.sendlineafter(b'Enter here:', test_flag.encode())
        p.gdb.wait()

        i = 0
        while i < idx:
            char_ok = int(p.gdb.parse_and_eval('$rax').cast(p.gdb.lookup_type('int')))
            binary_idx = int(p.gdb.parse_and_eval('*(int*)($rbp-0x88)').cast(p.gdb.lookup_type('int')))
            if idx == binary_idx:
                print(test_flag, char_ok, idx, binary_idx)
                i += 1
                break

            p.gdb.continue_and_wait()


        p.gdb.quit()
        if char_ok:
            return c


known = 'ping{d1D_y0U_m4n4g3_G0_or_'

for i in range(len(known)):
    flag[i] = known[i]

for idx in range(len(flag)):
    if idx < len(known): continue

    event = threading.Event()
    with ThreadPool(24) as pool:
        for res in pool.imap_unordered(lambda c: worker(c, idx, flag), alphabet):
            if res is not None:
                flag[idx] = res
                print('FOUNDDDDDDD', res, ''.join(flag))
                event.set()

    
