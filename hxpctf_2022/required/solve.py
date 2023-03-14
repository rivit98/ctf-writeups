from z3 import *
from textwrap import wrap
from pathlib import Path
from subprocess import check_output

def bitrev8(x):
    x = LShR(x, 4) | (x << 4)
    x = LShR(x & 0xCC, 2) | ((x & 0x33) << 2)
    x = LShR(x & 0xAA, 1) | ((x & 0x55) << 1)
    return x


def gen_dump():

    jsfiles = list(filter(lambda p: p.suffix == '.js', list(Path('./files').iterdir())))
    jsfiles = list(filter(lambda p: p.stem.isnumeric(), jsfiles))

    for fname in jsfiles:
        with open(fname, "rt") as f:
            text = f.read().splitlines()

        for i, line in enumerate(text):
            if 'f[i]' in line or 'f[j]' in line or 'f[t]' in line:
                text[i] = f'console.log(i, j, t), console.log("{line.strip()}"), {line}'

        with open(fname, "wt") as f:
            f.write('\n'.join(text))

    out = check_output('node required.js', shell=True, cwd="./files")
    with open("dump", "wb") as f:
        f.write(out)

def main():
    s = Solver()

    f = [BitVec(f'f{i}', 8) for i in range(30)]

    data = open("dump", "rt").read().splitlines()

    target = wrap('d19ee193b461fd8d1452e7659acb1f47dc3ed445c8eb4ff191b1abfa7969', 2)
    target = list(map(lambda v: int(v, 16), target))

    data = data[:-1]
    for ii in range(0, len(data), 2):
        i, j, t = list(map(int, data[ii].split(" ")))
        constraint = data[ii + 1].strip(',').replace('>>>', '>>')
        if constraint[0] == '(' and constraint[-1] == ')':
            constraint = constraint[1:-1]

        if any(x in constraint for x in [
            '+=',
            '&=',
            '-=',
            '^=',
            '= ~f'
        ]):
            exec(constraint)
        elif '>> 7' in constraint and '<< 1' in constraint:
            idx = constraint.split('=')[0].strip()
            exec(f'{idx} = RotateLeft({idx},1)')
        elif '>> 1' in constraint and '<< 7' in constraint:
            idx = constraint.split('=')[0].strip()
            exec(f'{idx} = RotateRight({idx},1)')
        elif '0x88440' in constraint:
            idx = constraint.split('=')[0].strip()
            exec(f'{idx} = bitrev8({idx})')
        elif '^' in constraint and '>> 1' in constraint:
            idx = constraint.split('=')[0].strip()
            l, r = constraint.split('^')
            new_c = f'{l} ^ (LShR({idx}, 1))'
            exec(new_c)
        else:
            print(constraint)

    for i in range(len(f)):
        # s.add(f[i] <= 0x80)
        s.add(f[i] == target[i])

    print(s.check())
    mdl = s.model()
    solution = str(mdl)[1:-1].split(',')
    solution = list(map(lambda v: v.replace('f', '').strip().split('='), solution))
    solution = list(map(lambda v: (int(v[0]), int(v[1])), solution))
    solution = sorted(solution, key=lambda v: v[0])
    print(''.join(map(lambda v: chr(v[1]), solution)))

if __name__ == '__main__':
    input("Run 'prettier --write .' first on the js files")
    gen_dump()
    main()
