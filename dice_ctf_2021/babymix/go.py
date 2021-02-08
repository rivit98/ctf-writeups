import angr
import claripy

def do_one(ii):
	p = angr.Project("babymix")

	key_bytes = [claripy.BVS("byte_{}".format(i), 8) for i in range(ii)]
	key_bytes_AST = claripy.Concat(*key_bytes)

	state = p.factory.entry_state(args=['./babymix'], stdin=key_bytes_AST)

	for byte in key_bytes:
		state.solver.add(byte > 0x20, byte < 0x7f)

	sm = p.factory.simulation_manager(state)

	print(sm.explore(find=lambda x: b"Correct!" in x.posix.dumps(1)))

	for found in sm.found:
		print(found.solver.eval(key_bytes_AST, cast_to=bytes))
	else:
		print("Nope")

	return len(sm.found)


for i in range(21, 0x30):
	print("Trying", i)
	if do_one(i) > 0:
		break
