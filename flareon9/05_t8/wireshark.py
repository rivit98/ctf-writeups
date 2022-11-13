import base64
from hashlib import md5
from dataclasses import dataclass

rand_str = 11950
print("rand_str", hex(rand_str))
first_data = 'ydN8BXq16RE='
first_response = 'TdQdBRa1nxGU06dbB27E7SQ7TJ2+cd7zstLXRQcLbmh2nTvDm1p5IfT/Cu0JxShk6tHQBRWwPlo9zA1dISfslkLgGDs41WK12ibWIflqLE4Yq3OYIEnLNjwVHrjL2U4Lu3ms+HQc4nfMWXPgcOHb4fhokk93/AJd5GTuC5z+4YsmgRh1Z90yinLBKB+fmGUyagT6gon/KHmJdvAOQ8nAnl8K/0XG+8zYQbZRwgY6tHvvpfyn9OXCyuct5/cOi8KWgALvVHQWafrp8qB/JtT+t5zmnezQlp3zPL4sj2CJfcUTK5copbZCyHexVD4jJN+LezJEtrDXP1DJNg=='
first_response_decoded = list(base64.b64decode(first_response))

second_data = 'VYBUpZdG'
second_response = 'F1KFlZbNGuKQxrTD/ORwudM8S8kKiL5F906YlR8TKd8XrKPeDYZ0HouiBamyQf9/Ns7u3C2UEMLoCA0B8EuZp1FpwnedVjPSdZFjkieYqWzKA7up+LYe9B4dmAUM2lYkmBSqPJYT6nEg27n3X656MMOxNIHt0HsOD0d+'


three_letter_str = 'FO9' + str(rand_str)
three_letter_str_enc = three_letter_str.encode('utf-16-le')
md5_three_letters = md5(three_letter_str_enc).hexdigest()
print(three_letter_str, md5_three_letters)

@dataclass
class Ctx:
    a: int
    b: int
    c: int
    data: list

def scramble(data, data_len):
    c = Ctx(data_len, 0, 0, [i for i in range(256)])

    lena = 0
    for i in range(256):
        v6 = c.data[i]
        v7 = (lena + v6 + data[i % c.a]) % 256
        result = c.data[v7]
        c.data[i] = result
        lena = v7
        c.data[v7] = v6

    return c


def scramble2(ctx, xor_data, out_max_len):
    out = []
    for out_iter in range(out_max_len):
        v5 = (ctx.b + 1) % 256
        ctx.b = v5
        v6 = (ctx.c + ctx.data[v5]) % 256
        ctx.c = v6
        ctx.data[v5], ctx.data[v6] = ctx.data[v6], ctx.data[v5]
        r = xor_data[out_iter] ^ ctx.data[(ctx.data[ctx.b] + ctx.data[ctx.c]) & 0xFF]
        out.append(r)
        # print(hex(out[out_iter]), hex(ctx.b), hex(ctx.c))

    return out


def scramble_wrapper(seed, xor_data, out_max_len):
    c = scramble(seed, len(seed))
    scramble2_out = scramble2(c, xor_data, out_max_len)
    print(''.join(map(lambda v: f'{v:02x} ', scramble2_out)))

    return scramble2_out


def gen_code(md5_seed, read_data):
    decoded = base64.b64decode(read_data)
    return scramble_wrapper(md5_seed, decoded, len(decoded))


def split_by_comma():
    pass

e = md5_three_letters.encode('utf-16-le')
ahoy = 'ahoy'.encode('utf-16-le')
first_scramble_output = scramble_wrapper(e, ahoy, len(ahoy))

second_scramble_output = scramble_wrapper(e, first_response_decoded, len(first_response_decoded))

print(bytes(second_scramble_output).split(b','))

after_first_communication = 'i_s33_you_m00n@flare-on.com'.encode('utf-16-le')
after_first_communication_md5 = md5(after_first_communication).hexdigest().encode('utf-16-le')
print(after_first_communication_md5)

sce = 'sce'.encode('utf-16-le')
before_shellcode_call_scramble_output = scramble_wrapper(after_first_communication_md5, sce, len(sce))
print(list(base64.b64decode(second_data)))
print(before_shellcode_call_scramble_output)

generated_code = gen_code(after_first_communication_md5, second_response)
print(generated_code, len(generated_code))



