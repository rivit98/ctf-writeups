import angr
import claripy

base = 0x00400000
proj = angr.Project('uncertain', main_opts={'base_addr': base})

desired_adr = 0x00442622
wrong_adr = 0x0044262C

input_chars = [claripy.BVS("char_%d" % i, 8) for i in range(0x80)]

entry_state = proj.factory.entry_state()
entry_state.solver.add(input_chars[0] == "p")
entry_state.solver.add(input_chars[1] == "i")
entry_state.solver.add(input_chars[2] == "n")
entry_state.solver.add(input_chars[3] == "g")
entry_state.solver.add(input_chars[4] == "{")
for byte in input_chars:
    entry_state.solver.add(byte >= 0x20, byte <= 0x7e)

class my_scanf(angr.SimProcedure):
    def run(self, fmt, ptr):
        for i in range(len(input_chars)):
            self.state.mem[ptr+i].byte = input_chars[i]

proj.hook_symbol('__isoc23_scanf', my_scanf(), replace=True)

sm = proj.factory.simgr(entry_state)
sm.one_active.options.add(angr.options.LAZY_SOLVES)

print(sm.explore(find = desired_adr, avoid = wrong_adr))

flag = ''.join(chr(sm.one_found.solver.eval(c)) for c in input_chars)
print(flag)
