import numpy as np

C = [
    [17, 3, 4, 14],
    [6, 13, 13, 12],
    [10, 10, 12, 22],
    [5, 18, 25, 21]
]

target = [
    [2094, 2962, 1014, 2102],
    [2172, 3955, 1174, 3266],
    [3186, 4188, 1462, 3936],
    [3583, 5995, 1859, 5150]
]

b = np.array(target, dtype=np.double)
invA = np.linalg.inv(C)
x = invA @ b
x = np.rot90(x, 3)
x = np.transpose(x)
print('SEKAI{' + ''.join(map(lambda v: chr(round(v) ^ 42), x.flatten())) + '}')
