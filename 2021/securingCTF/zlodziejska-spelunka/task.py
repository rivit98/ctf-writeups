import random
from db import flag

# LLL ?
ror = lambda lll, l, ll: (lll >> l) | ((lll & ((1 << l) - 1)) << (ll - l))

N = 1
for b in [2, 3, 7, 11]:
    N *= b ** random.randint(b, 31337)
e = 65537
m = int(flag.encode('hex'), 16)
m_len = len(flag * 8)

with open('task.txt', 'w') as f:
    for i in range(m_len):
        f.write(str(pow(ror(m, i, m_len), e, N))+'\n')
