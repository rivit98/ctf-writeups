
#!/usr/bin/env python3
import sys
import struct
import binascii

# Improved solver v2
# Fixes byte-ordering within each 8-byte window when reconstructing the flag.

def ror32(x, n):
    n &= 31
    return ((x >> n) | ((x & 0xFFFFFFFF) << (32 - n))) & 0xFFFFFFFF

def read_at(f, off, n):
    f.seek(off)
    b = f.read(n)
    if len(b) != n:
        raise IOError(f"Short read at 0x{off:X} (wanted {n}, got {len(b)})")
    return b

# TEA-like inverse (reverse of the sub_100003E30 transform)
GOLD = 0x9E3779B9

def tea9_inverse(new_hi, new_lo, k, sched):
    v9 = (k[2] ^ (new_hi & 0xFFFFFFFF)) & 0xFFFFFFFF
    v5 = ((new_lo & 0xFFFFFFFF) - k[3]) & 0xFFFFFFFF
    for i in reversed(range(9)):
        v7 = sched[i] & 0xFFFFFFFF
        s2 = (-5 - ((v7 >> 3) & 7)) & 31
        tmp = (v9 + k[(i + 1) & 3] + ror32(v9, s2)) & 0xFFFFFFFF
        v6_in = v5 ^ tmp
        s1 = (-3 - (v7 & 7)) & 31
        v8 = (v9 - ror32(v6_in, s1)) & 0xFFFFFFFF
        v5_in = (v8 - k[i & 3] - (v7 ^ GOLD)) & 0xFFFFFFFF
        v9 = v6_in
        v5 = v5_in
    lo = v9 & 0xFFFFFFFF
    hi = v5 & 0xFFFFFFFF
    return lo, hi

# Mach-O parsing to map virtual addresses to file offsets
MH_MAGIC_64 = 0xfeedfacf
LC_SEGMENT_64 = 0x19

def find_fileoff_for_addr(f, target_addr):
    hdr = read_at(f, 0, 32)
    magic = struct.unpack("<I", hdr[0:4])[0]
    if magic != MH_MAGIC_64:
        raise ValueError("Not a 64-bit little-endian Mach-O (magic mismatch)")
    # unpack ncmds and sizeofcmds
    _, _, _, _, ncmds, sizeofcmds, _, _ = struct.unpack("<IiiIIII", hdr[:28]) + (struct.unpack("<I", hdr[28:32])[0],)
    off = 32
    for _ in range(ncmds):
        cmd, cmdsize = struct.unpack("<II", read_at(f, off, 8))
        if cmd == LC_SEGMENT_64:
            seg = read_at(f, off, cmdsize)
            (cmd2, cmdsize2, segname, vmaddr, vmsize, fileoff, filesize, maxprot, initprot, nsects, flags) = struct.unpack("<II16sQQQQiiII", seg[:72])
            if vmaddr <= target_addr < vmaddr + vmsize:
                return fileoff + (target_addr - vmaddr)
        off += cmdsize
    raise ValueError(f"Address 0x{target_addr:X} not found in LC_SEGMENT_64 commands")

def read_qwords(f, fileoff, count):
    data = read_at(f, fileoff, 8*count)
    return list(struct.unpack("<" + "Q"*count, data))

def read_dwords(f, fileoff, count):
    data = read_at(f, fileoff, 4*count)
    return list(struct.unpack("<" + "I"*count, data))

def crc32_custom(data):
    return binascii.crc32(data) & 0xFFFFFFFF

def extract_constants(f):
    a3_addr = 0x100003F30
    a4_addr_0 = 0x100003F40
    a4_addr_1 = 0x100003F50
    a4_last_dword = 0xD55AD554  # -715467436 as unsigned
    ref_addr = 0x100003F68

    a3_off = find_fileoff_for_addr(f, a3_addr)
    a4_off0 = find_fileoff_for_addr(f, a4_addr_0)
    a4_off1 = find_fileoff_for_addr(f, a4_addr_1)
    ref_off = find_fileoff_for_addr(f, ref_addr)

    k = read_dwords(f, a3_off, 4)
    # schedule is 9 dwords: 8 from xmmword_100003F40/50 and last explicit v30
    sched = read_dwords(f, a4_off0, 8) + [a4_last_dword]
    # read 5 qwords (36 byte flag => 5 blocks)
    ref_qwords = read_qwords(f, ref_off, 5)
    return k, sched, ref_qwords

def invert_blocks(ref_qwords, k, sched, flag_len=36):
    flag = bytearray(b"\x00" * flag_len)
    known = [False] * flag_len
    for j, cipher in enumerate(ref_qwords):
        base_index = 8 * j  # corresponds to v16-3 .. v16+4 where v16 = 3 + 8*j
        new_lo = cipher & 0xFFFFFFFF
        new_hi = (cipher >> 32) & 0xFFFFFFFF
        lo_in, hi_in = tea9_inverse(new_hi, new_lo, k, sched)
        # Extract bytes
        b0 = lo_in & 0xFF
        b1 = (lo_in >> 8) & 0xFF
        b2 = (lo_in >> 16) & 0xFF
        b3 = (lo_in >> 24) & 0xFF
        b4 = hi_in & 0xFF
        b5 = (hi_in >> 8) & 0xFF
        b6 = (hi_in >> 16) & 0xFF
        b7 = (hi_in >> 24) & 0xFF
        block_bytes = [b4, b5, b6, b7, b0, b1, b2, b3]  # map to indices base..base+7
        for i in range(8):
            idx = base_index + i
            if idx >= flag_len:
                continue
            if known[idx] and flag[idx] != block_bytes[i]:
                raise ValueError(f"Overlap mismatch at idx {idx}: {flag[idx]:02x} vs {block_bytes[i]:02x}")
            flag[idx] = block_bytes[i]
            known[idx] = True
    if not all(known):
        missing = [i for i,x in enumerate(known) if not x]
        raise ValueError(f"Some flag bytes unresolved at positions: {missing}")
    return bytes(flag)

def main():
    if len(sys.argv) != 2:
        print("Usage: python3 solve_flag_v2.py <Mach-O-binary>")
        sys.exit(1)
    path = sys.argv[1]
    with open(path, "rb") as f:
        k, sched, ref_qwords = extract_constants(f)
    print("Key (k):", [hex(x) for x in k])
    print("Sched (9 dwords):", [hex(x) for x in sched])
    print("Ref qwords:", [hex(x) for x in ref_qwords])

    flag_bytes = invert_blocks(ref_qwords, k, sched, flag_len=36)
    print("Recovered bytes:", flag_bytes)
    try:
        flag_str = flag_bytes.decode('utf-8')
    except Exception:
        flag_str = flag_bytes.decode('latin-1', errors='replace')
    # Basic format check
    if not (len(flag_bytes) == 36 and flag_str.startswith("BHFlagY{") and flag_str.endswith("}")):
        print("Format check failed (prefix/length/suffix).")
        print("Recovered (as string):", flag_str)
        sys.exit(2)
    crc = crc32_custom(flag_bytes)
    if crc != 0xD95BC8CB:
        print(f"CRC mismatch: got 0x{crc:08X}, expected 0xD95BC8CB")
        sys.exit(3)
    print("FLAG:", flag_str)

if __name__ == "__main__":
    main()
