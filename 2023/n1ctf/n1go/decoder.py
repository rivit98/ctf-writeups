import concurrent.futures
import re
import subprocess
from pathlib import Path
from subprocess import check_output


try:
    Path("./builds/").mkdir(exist_ok=True)
except:pass

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

def build_and_get_output(fname, func, headers):
    source = f"""
{headers}
{func}
    
func main() {{
    {fname}()  
}}
""".strip()

    if fname.startswith('_'):
        fname = "A" + fname

    new_fname = f"./builds/{fname}.go"
    with open(new_fname, "wt") as f:
        f.write(source)

    try:
        out = check_output(f"/home/rivit/go/bin/goimports -w {new_fname} && /usr/local/go/bin/go run {new_fname} && rm {new_fname}", shell=True, stderr=subprocess.STDOUT, timeout=2)
        return new_fname, out
    except Exception as e:
        print(source)
        print(e)
        # pass

    return None, None


def replace_simple_strings(source, headers, funcs):
    with concurrent.futures.ProcessPoolExecutor(24) as executor:
        futures = []
        for fname, func in funcs:
            if 'get_byte' in func: continue

            futures.append((
                executor.submit(build_and_get_output, fname, func, headers),
                fname, func
            ))

        for fut, fname, func in futures:
            new_fname, out = fut.result()
            if out is None: continue
            newsource = f"""
func {fname}() {{
    println("{out.decode().strip()}")
}}
                """

            source = source.replace(func, newsource)

    return source


def parse_get_byte_func(func):
    chunks = []
    current = []
    for line in func.splitlines():
        if line.startswith('	case ') or line.startswith('	default:'):
            chunks.append('\n'.join(current))
            current = []

        current.append(line)
    chunks.append('\n'.join(current))

    headers = chunks.pop(0)
    if not chunks:
        return headers, [], ""
    last = chunks.pop(-1)
    footer = last.split('}')
    chunks.append(footer[0])
    return headers, chunks, '}'.join(footer[1:])


def build_and_get_output_case(func, i):
    source = f"""
package main

import (
	"fmt"
	"os"
)

func main() {{
    {func} 
}}
""".strip()

    fname = f"tmp{i}"
    new_fname = f"./builds/{fname}.go"
    with open(new_fname, "wt") as f:
        f.write(source)

    try:
        out = check_output(f"/home/rivit/go/bin/goimports -w {new_fname} && /usr/local/go/bin/go run {new_fname} && rm {new_fname}",
                           shell=True, stderr=subprocess.STDOUT, timeout=2)
        return out
    except Exception as e:
        # print(source)
        # print(e)
        pass

    return None

def replace_in_get_byte(source, funcs):
    # list of 'cases', if lines > 1 then try to optimize

    with concurrent.futures.ProcessPoolExecutor(32) as executor:
        futures = []
        i = 0
        for fname, func in funcs:
            if 'get_byte' not in func: continue

            headers, cases, footer = parse_get_byte_func(func)
            if not cases: continue

            for c in cases:
                if c.count('\n') == 1: continue  # simple case, skip

                case_body = c.split('\n')[1:]
                case_body = '\n'.join(case_body)

                futures.append((
                    executor.submit(build_and_get_output_case, case_body, i),
                    case_body
                ))
                i += 1

        for fut, case_body in futures:
            out = fut.result()
            if not out: continue
            newsource = f'println("{out.decode().strip()}")'
            source = source.replace(case_body, newsource)

    return source


def main():
    source = open("./N1G0.go", "rt").read()

    headers, chunks = parse_source(source)
    funcs = save_chunks(chunks)
    new_source = replace_simple_strings(source, headers, funcs)
    new_source = replace_in_get_byte(new_source, funcs)

    with open("./new_source/new_source.go", "wt") as f:
        f.write(new_source)

if __name__ == '__main__':
    main()