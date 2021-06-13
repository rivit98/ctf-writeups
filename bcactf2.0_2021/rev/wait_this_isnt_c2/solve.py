import string
import numpy as np

np.set_printoptions(formatter={'int': lambda x: hex(int(x))})

flag = [0] + list(map(ord, string.ascii_uppercase[:24]))
flag_matrix = list(zip(*(iter(flag),) * 5))

matrix = np.array(flag_matrix, np.int32)
print(matrix)

for i in range(1, 6):
    for j in range(-2, 3):
        idx = 5 * j + 9 + i
        x = idx // 5
        y = idx % 5
        matrix[x, y] += j * i

print(matrix)
# print(np.roll(matrix, shift=3, axis=1))
print(np.roll(matrix, shift=2, axis=1))

v51 = 1
v44 = np.zeros(25, dtype=np.int32)
for i in range(0, 5):
    v6 = i
    for j in range(v6 + 1):
        v44[5 * j + i] = v51
        v44[5 * i + j] = v51

        v51 += 1

v44 = v44.reshape((5, 5))
print(v44)

prod = np.matmul(v44, matrix)
print(prod)
test_rolled = np.roll(prod, shift=3, axis=1)
print(test_rolled)


final = [
    0x0AC0, 0x779, 0x0A43, 0x859, 0x982, 0x0CDA, 0x92C, 0x0C10, 0x9D5, 0x0B5E, 0x0FC9, 0x0BA1, 0x0E65, 0x0BC2,
    0x0DFC, 0x1465, 0x0F9E, 0x120C, 0x0F08, 0x1200, 0x1B6E, 0x15C2, 0x17DE, 0x13D5, 0x183B
]

final_matrix = np.array(final, dtype=np.int32)
final_matrix = final_matrix.reshape((5,5))
final_matrix = np.roll(final_matrix, shift=-3, axis=1)
print(final_matrix)
inv = np.linalg.inv(v44)
final_matrix = np.matmul(inv, final_matrix)
print(final_matrix)
# final_matrix = np.roll(final_matrix, shift=-2, axis=1)


for i in range(1, 6):
    for j in range(-2, 3):
        idx = 5 * j + 9 + i
        x = idx // 5
        y = idx % 5
        final_matrix[x, y] -= j * i

final_matrix = np.rint(final_matrix)
final_matrix = final_matrix.reshape(25).tolist()
print(''.join(map(lambda x: chr(int(x)), final_matrix)))