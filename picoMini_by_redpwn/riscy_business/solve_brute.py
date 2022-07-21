import string

to_compare = [0xC5, 0x75, 0x95, 0xa5, 0x81, 0x80, 0xf3, 0x44, 0xf1, 0x99, 0x34, 0x81, 0x3a, 0x5f, 0x50, 0x93, 0x67, 0xee, 0x12, 0x0c, 0x15, 0x3a, 0xda, 0x1c, 0x6f, 0x50, 0x80, 0x49, 0x63, 0xf2, 0x36, 0xd3, 0x93, 0x64, 0x46, 0x63, 0x84, 0xb5, 0x3a, 0x5a, 0x9c, 0x3e, 0x40, 0xf5, 0x19, 0x20, 0x7f, 0x08, 0x00, 0x48, 0x0a, 0x03]

flag = 'picoCTF{'

while '}' not in flag:
    for try_char in string.printable:
        try_flag = flag + try_char
        out_buf = [i for i in range(0x100)]
        out_buf_ptr = 0
        uVar4 = 0
        for i in range(0, 0x100):
            uVar2 = i % 8
            bVar1 = out_buf[out_buf_ptr]
            uVar2 = uVar4 + ord(try_flag[uVar2]) + bVar1
            uVar4 = uVar2 & 0xFF
            out_buf[out_buf_ptr] = out_buf[uVar2 & 0xFF]
            out_buf[uVar2 & 0xFF] = bVar1
            out_buf_ptr += 1

        out_buf.extend([0,0])
        buf = out_buf

        def sth():
            u2 = (buf[0x100] + 0x1) & 0xFF
            buf[0x100] = u2
            b1 = buf[u2]
            u3 = (buf[0x101] + b1) & 0xFF
            buf[0x101] = u3

            tmp = buf[u3]
            buf[u2] = tmp
            buf[u3] = b1

            return buf[(b1 + tmp) & 0xFF]


        new_flag = []
        for i in range(len(try_flag)):
            new_flag.append(ord(try_flag[i]) ^ sth())

        good = sum(map(lambda t: t[0] == t[1], zip(new_flag, to_compare)))
        if good > len(flag):
            flag = try_flag
            print(flag)
            break

