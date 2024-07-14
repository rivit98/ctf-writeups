import concurrent.futures
import subprocess


def parse(d):
    chunks = d.split('--\n')
    ret = []
    for chunk in chunks:
        read_l = list(filter(lambda l: 'read' in l, chunk.splitlines()))
        vals = []
        for line in read_l:
            # LibClamAV debug: bytecode trace: 15, read 0
            toks = line.split(' ')
            val = int(toks[-1], 16)
            vals.append(val)

        ret.append(tuple(vals))
    return ret

MAX_LEN = 0x18c

def prep_payload(known, pos, bytev):
    padding = (MAX_LEN - len(known)) * b'A'
    data = bytearray(known + padding)
    data[pos] = bytev
    fname = f"./payloads/p{pos}_{bytev}.exe"
    with open(fname, "wb") as f:
        f.write(data)
    return fname


def worker(known, pos, byte_value):
    fname = prep_payload(known, pos, byte_value)
    # requires custom build of clamav with trace enabled
    cmd = f"./clamav/build/clamscan/clamscan --bytecode-unsigned --debug -d ./print_flag.cbc {fname} --bytecode-timeout=0 2>&1 | grep -A 2 '21 /106/  1'"
    out = subprocess.check_output(cmd, shell=True).decode()

    matches = parse(out)
    cnt = 0
    for v1, v2 in matches[2:]:
        if v1 == v2:
            cnt += 1
        else:
            break

    return pos, byte_value, cnt, matches


def main():
    try:
        with open("recovered.exe", "rb") as f:
            known = bytearray(f.read())
    except:
        known = bytearray(b'MZ')

    for pos in range(len(known), MAX_LEN):
        print(f'pos: {pos}')
        print(f'known: {known}')

        results = []
        with concurrent.futures.ProcessPoolExecutor(48) as executor:
            futures = [executor.submit(worker, known, pos, i) for i in range(0x100)]
            for future in concurrent.futures.as_completed(futures):
                pos, byte_value, cnt, matches = future.result()

                # print(f'pos: {pos}, bv: {byte_value}, matches: {cnt}, {matches[-2:]}')
                if cnt > pos:
                    results.append(byte_value)
                    print("cancel executor")
                    #for fut in futures:
                    #    fut.cancel()

                    #executor.shutdown(wait=False, cancel_futures=True)
                    #break

        print(f'winners for pos {pos} are: {results}')
        # pick first winner (TODO: might revisit this), multiple winners can be found

        known.append(results[0])
        with open("recovered.exe", "wb") as f:
            f.write(bytes(known))


if __name__ == '__main__':
    main()

    # after getting the binary we can decode flag inside it
    from pwn import xor
    xored = b'\xA0\xA1\xBC\xAB\xA7\xA6\xB3\xBB\xAD\xAB\xBA\xAD\xBC\x97\xBD\xA6\xB8\xA9\xAB\xA3\xAD\xBA\x97\xA1\xA6\x97\xAB\xA4\xA9\xA5\xA9\xBE\x97\xAA\xB1\xBC\xAD\xAB\xA7\xAC\xAD\x97\xBB\xA1\xAF\xA6\xA9\xBC\xBD\xBA\xAD\xB5'
    known = b'hitcon{'
    print(xor(b'\xc8', xored))
    # b'hitcon{secret_unpacker_in_clamav_bytecode_signature}'
