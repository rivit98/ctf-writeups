import re
from pathlib import Path


def parse_source(source):
    chunks = []
    current = []
    for line in source.splitlines():
        if line.startswith('func'):
            chunks.append('\n'.join(current))
            current = []

        current.append(line)
    chunks.append('\n'.join(current))

    headers = chunks.pop(0)
    return headers, chunks


def save_chunks(chunks):
    ret = []
    pattern = re.compile('func ([a-zA-Z0-9_]+)\(\) ')
    for func in chunks:
        match = re.search(pattern, func)
        if match:
            ret.append((match.group(1), func))
        else:
            print("unable to find")
            print(func)
            print('-' * 100)
            raise SystemExit("fail")

    return ret


def traverse_up(funcs, current, visited):
    cfname, cbody = current
    if 'main()' in cbody:
        return visited

    candidates = []
    for fname, body in funcs:
        if cfname in body and cfname not in fname:
            candidates.append((fname, body))


    for candidate in candidates:
        if candidate[0] in visited:
            # been there
            continue
        res = traverse_up(funcs, candidate, visited + [candidate[0]])
        if res:
            return res

    return {}

def main():
    source = open("./new_source/new_source.go", "rt").read()

    headers, chunks = parse_source(source)
    funcs = save_chunks(chunks)

    start = None
    for fname, body in funcs:
        if 'congratulation' in body:
            start = (fname, body)
            break

    path = traverse_up(funcs, start, [start[0]])

    path = list(reversed(path))[1:]
    current = path[0]
    path = path[1:]
    input = []
    for node in path:
        for fname, body in funcs:
            if f'func {current}' in body:
                b = body.splitlines()
                idx = None
                for i, line in enumerate(b):
                    if node in line:
                        idx = i -1
                        break

                input.append(b[idx])
                current = node
                break

    flag = []
    for i in input:
        n = i.replace(':', '').replace('case ', '').strip()
        try:
            flag.append(chr(int(n)))
        except:
            flag.append(n.strip("'").strip())

    print(''.join(flag))
    import hashlib
    print(hashlib.md5(''.join(flag).encode()).hexdigest())

if __name__ == '__main__':
    main()