import pyshark
from collections import defaultdict
from solve import solve

STREAMID = 10

cap = pyshark.FileCapture('./hermes_traffic.pcap')

groups = defaultdict(int)
gid = 0
THRE = 400000
prev_ms = -1

drop = False

for c in cap:
    if not hasattr(c, 'tcp'): continue

    srcport = int(c.tcp.srcport)
    if srcport != 21473: continue

    sid = int(c.tcp.stream)
    if sid != STREAMID: continue

    if not hasattr(c, 'http'): continue

    if not drop:
        drop = not drop
        continue

    ms = c.sniff_time.microsecond
    groups[gid] += 1

    if abs(prev_ms - ms) > THRE and prev_ms != -1:
        gid += 1

    prev_ms = ms

# print(groups)

letter_codes = [groups[i] for i in range(len(sorted(groups.keys())))]
# print(letter_codes)

out = []
idx = 0
while idx < len(letter_codes):
    v = letter_codes[idx]
    if v > 15:
        r = v - 15
        c = 15 + (r-1) * 16
        out.append(chr(c))
        idx += 1
    else:
        try:
            a = v - 1
            m = letter_codes[idx+1] - 1
            out.append(chr(a + m * 16))
            idx += 2
        except:
            idx += 1



print(''.join(out))

