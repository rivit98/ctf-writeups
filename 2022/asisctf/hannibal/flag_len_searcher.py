from pwn import *
from textwrap import wrap

# seed_to_set = 1665570905
seed_to_set = 1665578105


expected_binary_len = 79 * 8 - 1


def get_shuffle(rand_val, flag_len): # deafult for flag 41
    print(f"rand_val={rand_val}")
    aa = {}
    for i in range(1, flag_len):
        a = pow(rand_val, i, flag_len)
        # print(f'{i}.', hex(a))
        aa[i] = a
    return aa


for seed in range(seed_to_set - 300, seed_to_set + 10, 1):
# for seed in range(seed_to_set, seed_to_set + 1, 1):
    # for i in range(10, 70):
    # for i in [41]:#, 50, 67, 73]:
    # for i in [73, 78]: # 73, 78
    for i in [73]:
        try:
            print("testing flag len=", i)
            with open("./flag.txt", "wt") as f:
                f.write(cyclic(i).decode())

            with gdb.debug("./hannibal.elf",
                           gdbscript=
                           '''
            brva 0x161e
            brva 0x17EA
            brva 0x1988
            brva 0x195E
            brva 0x19A8
                           ''',
                           api=True) as p:
                p.gdb.continue_and_wait()
                # seed = p.gdb.parse_and_eval('$rdi').cast(p.gdb.lookup_type('int'))
                # print(f"old seed={seed}")

                # p.gdb.execute(f'set $rdi={hex(seed_to_set)}')
                p.gdb.execute(f'set $rdi={hex(seed)}')

                p.gdb.continue_and_wait()
                flag_len = int(p.gdb.parse_and_eval('$rax').cast(p.gdb.lookup_type('int')))
                print(f"flag_binary_len={flag_len}")

                if flag_len == expected_binary_len:
                    print(f"Orig flag len was: {i}")

                # p.gdb.quit()
                # continue

                # p.gdb.continue_and_wait()
                # target_index = p.gdb.parse_and_eval('$al').cast(p.gdb.lookup_type('int'))

                # shuffle_map = {
                #     0: target_index
                # }
                # print(0, target_index)

                p.gdb.continue_and_wait()
                rand_val = p.gdb.parse_and_eval('$rcx').cast(p.gdb.lookup_type('int'))
                p.gdb.continue_and_wait()

                shuffle_map = get_shuffle(int(rand_val), flag_len)
                shuffle_map[0] = 1


                # for j in range(1, flag_len):
                #     p.gdb.continue_and_wait()
                #     target_index = p.gdb.parse_and_eval('$rdx').cast(p.gdb.lookup_type('int'))
                #     # print(f"target_index={target_index}")
                #     shuffle_map[j] = target_index
                #     print(j, target_index)

                print("shuffle_map len", len(shuffle_map))
                assert len(shuffle_map) == flag_len

                # orig_string = '1000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000010100000101000001010000011111010001101100011111001001010100100001010111000011111100000110001111000011110001100010110111000100001111110100110110001111010001011000111001111000111111010110101011001100000000000010100100110000101000001010100000011111111001110110100100111001100001011010111000101101011101100000000111100001001111000010'

                # enc = [
                #     orig_string[1]
                # ]
                #
                # for i in range(1, flag_len):
                #     enc.append(orig_string[shuffle_map[i]])
                #
                # print("manual encode")
                # print(''.join(enc))

                flag_enc = list(open("flag4.enc", "rb").read())
                binary = ''.join(map(lambda v: bin(v)[2:].rjust(8, '0'), flag_enc))[1:]

                deshuffled = ['1' for _ in range(flag_len)]

                for ii in range(len(binary)):
                    deshuffled[shuffle_map[ii]] = binary[ii]

                print(deshuffled)

                print(len(deshuffled))

                deshuffled = '0' + ''.join(deshuffled)
                chunks = wrap(deshuffled, 8)
                chunks = list(map(lambda v: chr(int(v, 2)), chunks))

                print(''.join(chunks))
                win = ''.join(chunks)
                if 'ASIS' in win:
                    raise SystemExit

                p.gdb.quit()
        except Exception as e:
            # p.gdb.quit()
            raise e
            print()