

def remap(line):
    if not line.strip(): return ""

#       0    0  OP_BC_TRUNC         [14 / 71/  1]  19 = 1 trunc ffffffff

    toks = line.split(' ')
    toks = list(filter(len, toks))

    bb, idx, op, *rest = toks

    pseudo = ' '.join(rest).split(']')[-1].strip()

    print(bb, idx, op, pseudo)

    if op == 'OP_BC_TRUNC':
        # 19 = 1 trunc ffffffff
        toks = pseudo.split(' ')


def parse_consts(fn_idx):
    from fnconsts import f1, f0

    d = f1
    if fn_idx == 0:
        d = f0

    # mem[436] = 0x1;
    consts = {}
    for line in d:
        if not line: continue
        l,r = line.split('=')
        consts[l.strip()] = r.strip().strip(';')

    return consts


def proc_f(idx, chunk):
    lines = chunk.splitlines()
    consts = parse_consts(idx)
    new_lines = []
    lines_iter = iter(lines)

    tok = 'BB   IDX  OPCODE              [ID /IID/MOD]  INST'

    for line in lines_iter:
        if tok not in line:
            new_lines.append(line)
        else:
            break

    for line in lines_iter:
        for k,v in consts.items():
            while k in line:
                line = line.replace(k,v)
        new_lines.append(line)

    return new_lines


def main():
    import sys
    trace = open(sys.argv[1], "rt").read()
    tof = '####################### Function id'

    funcs = trace.split(tof)[1:]

    new_lines = []
    for i, f in enumerate(funcs):
        nl  = proc_f(i, f)
        new_lines.extend('\n'.join(nl))

    with open(sys.argv[2], "wt") as f:
        f.writelines(new_lines)



if __name__ == '__main__':
    main()