from Pro.Core import *
from Pro.UI import *
from Pro.ccast import sbyte
import os, struct

R1 = 0x1000a
R2 = 0x4003 * 4
R3 = 0x10008
R4 = 0x10110
R5 = 0x10010
R6 = 0x8004 * 2
R7 = 0x10009
MEM6 = 6
MEM7 = 7
IP = 0

REGS = [
    R1,
    R4,
    R5,

    R2,

    MEM6,
    MEM7,

    R3,
    R7,
    IP
]
REG_COUNT = len(REGS)


def regName(id):
    r = REGS[id]
    if r == MEM6:
        return "mem[6]"
    elif r == MEM7:
        return "mem[7]"
    elif r == IP:
        return "IP"
    elif r == R2:
        return "STAT (R2)"
    elif r == R3:
        return "R3,6"
    elif r == R7:
        return "R7"
    else:
        return "R" + ['1','4','5','6'][id] + ": " + hex(REGS[id])


def disassemble(mem, step):
    output = []

    for op in program[step + 1:]:
        if op == 0x0:
            d = "SKIP"
        elif 0x1 <= op <= 0x8:
            d = f'mem[R1] = {op - 1}'
        elif 0x9 <= op <= 0x10:
            d = f'mem[mem[R1]] = mem[{op - 9}]'
        elif op == 0x11:
            d = f'mem[mem[R1]]++'
        elif op == 0x12:
            d = f'mem[mem[R1]--'
        elif op == 0x13:
            d = f'mem[mem[R1]] = mem[6] + mem[7]'
        elif op == 0x14:
            d = f'mem[mem[R1]] = mem[6] - mem[7]'
        elif op == 0x15:
            d = f'mem[mem[R1]] = mem[7] * mem[6]'
        elif op == 0x16:
            d = f'mem[mem[R1]] = mem[6] / mem[7]'
        elif op == 0x17:
            d = f'mem[mem[R1]] = mem[6] % mem[7]'
        elif op == 0x18:
            d = f'mem[mem[R1]] = ~mem[mem[R1]]'
        elif op == 0x19:
            d = f'mem[mem[R1]] = -mem[mem[R1]]'
        elif op == 0x1a:
            d = f'mem[mem[R1]] = mem[7] & mem[6]'
        elif op == 0x1b:
            d = f'mem[mem[R1]] = mem[7] | mem[6]'
        elif op == 0x1c:
            d = f'mem[mem[R1]] = mem[7] ^ mem[6]'
        elif op == 0x1d:
            d = f'mem[mem[R1]] = mem[6] == mem[7]'
        elif op == 0x1e:
            d = f'mem[mem[R1]] = mem[6] < mem[7]'
        elif op == 0x1f:
            d = [
                f'mem[0] = mem[R3]',
                f'mem[1] = mem[R7]',
                f'mem[2] = mem[R2]'
            ]
        elif op == 0x20:
            d = [
                f'if(mem[mem[R1]] is even: nop',
                f'else:',
                f'  char_array_idx = mem[R2]',
                f'  if(char_array_idx == 2) &',
                f'    ret: mem[256 * mem[R3] + mem[R7] + 8] == &',
                f'    mem[R3]++',
                f'  elif(char_array_idx == 0) (',
                f'    ret: mem[256 * mem[R3] + mem[R7] + 8] == (',
                f'    mem[R3]--',
                f'  elif(char_array_idx == 1) )',
                f'    mem[R7]++',
                f'    ret: mem[256 * mem[R3] + mem[R7] + 8] == )',
                f'  elif(char_array_idx == 3) \'',
                f'    mem[R7]--',
                f'    ret: mem[256 * mem[R3] + mem[R7] + 8] == \'',
            ]
        elif op == 0x21:
            d = f'mem[mem[R1]] = mem[(256 * mem[0]) + 8 + mem[1]]'
        elif op == 0x22:
            d = f'mem[(256 * mem[0]) + 8 + mem[1]] = mem[mem[R1]]'
        elif op == 0x23:
            d = [
                f'mem[R6] = mem[0] (probably copies R6+1 to mem[1] too, verify)',
                f'mem[R2] = mem[2] (4 bytes? verify)'
            ]
        elif op == 0x24:
            d = f"mem[mem[R1]] = getc()"
        elif op == 0x25:
            d = [
                f'temp = mem[R4]',
                f'mem[R4]++ (probably string indexer)',
                f'c = mem[mem[R1]]',
                f'mem[temp + R5] = c',
                f'print: {chr(mem[mem[R1]])}'
            ]
        elif 0x26 <= op <= 0x29:
            d = f"mem[R2] = {op - 0x26}"
        elif op == 0x30:
            d = f"mem[R3]++"
        elif op == 0x31:
            d = f"mem[R3]--"
        elif op == 0x32:
            d = f"mem[R7]++"
        elif op == 0x33:
            d = f"mem[R7]--"
        elif op == 0xff:
            d = "NOP"
        else:
            d = "UNKNOWN"

        if type(d) == str:
            output.append(d)
        else:
            d = list(map(lambda t: f' {str(t[0] + 1)}: {t[1]}', zip(range(len(d)), d)))
            output.extend(d)

    return '\n'.join(output)


STEP_VIEW_ID = 1
DISASM_VIEW_ID = 2
MEMORY_VIEW_ID = 3
REGISTERS_VIEW_ID = 4
STACK_VIEW_ID = 5

# the dump directory should have files with increasing number as name
# e.g.: 0, 1, 2, etc.
DBGDIR = r"D:\dice_ctf_2021\lost_in_your_eyes\mem"


def loadStepDescr(ud, steps):
    stepsdescr = []
    for step in steps:
        stepsdescr.append("0x%04X" % (step,))
    ud["stepsdescr"] = stepsdescr


prev_mem = [0 for _ in range(0x100000)]
prev_off = 0
prev_end = 0


def loadStep(cv, step, ud):
    global prev_mem
    global prev_off
    global prev_end

    with open(os.path.join(DBGDIR, str(step) + "_m.bin"), "rb") as f:
        mem = f.read()

    ud["regs"] = [mem[reg] for reg in REGS]

    # set up regs table
    t = cv.getView(REGISTERS_VIEW_ID)
    labels = NTStringList()
    labels.append("Register")
    labels.append("Value")
    t.setColumnCount(2)
    t.setRowCount(REG_COUNT)
    t.setColumnLabels(labels)
    t.setColumnCWidth(0, 12)
    t.setColumnCWidth(1, 25)

    # set up memory
    h = cv.getView(MEMORY_VIEW_ID)
    ud["mem"] = mem

    mem = mem[:0xFFFF+1]
    h.setBytes(mem[:0xFFFF+1])

    if mem != prev_mem:
        newOffset = -1
        end = 0
        for i, b in enumerate(mem):
            if b != prev_mem[i]:
                if newOffset == -1:
                    newOffset = i
                end += 1

        h.setSelectedRange(newOffset, end)
        h.setCurrentOffset(max(0, min(newOffset - 0x60, 0xFFFF)))

        prev_off = newOffset
        prev_end = end
    else:
        h.setSelectedRange(prev_off, prev_end)
        h.setCurrentOffset(max(0, min(prev_off - 0x60, 0xFFFF)))

    prev_mem = mem

    # set up disasm
    t = cv.getView(DISASM_VIEW_ID)
    disasm = disassemble(ud["mem"], step)
    t.setText(disasm)


def tracerCallback(cv, ud, code, view, data):
    if code == pvnInit:
        # get steps
        steps = os.listdir(DBGDIR)
        steps = [int(e.split('_')[0]) for e in steps if e.endswith("_o.bin")]
        steps = sorted(steps)
        ud["steps"] = steps
        loadStepDescr(ud, steps)
        # set up steps
        t = cv.getView(STEP_VIEW_ID)
        labels = NTStringList()
        labels.append("Trace")
        t.setColumnCount(1)
        t.setRowCount(len(steps))
        t.setColumnLabels(labels)
        t.setColumnCWidth(0, 10)
        return 1
    elif code == pvnGetTableRow:
        vid = view.id()
        if vid == STEP_VIEW_ID:
            data.setText(0, str(ud["stepsdescr"][data.row]))
        elif vid == REGISTERS_VIEW_ID:
            data.setText(0, regName(data.row))
            mem = ud["mem"]
            if REGS[data.row] == IP:
                a = (mem[R3] << 8) + mem[R7] + 8
                v = mem[a]
                data.setText(1, f'{hex(v)} at: {hex(a)}')
            else:
                v = mem[REGS[data.row]]
                desc = "0x%X (%d)" % (v, v)
                try:
                    desc += " -> 0x%X (%d)" % (mem[v], mem[v])
                except:
                    pass

                data.setText(1, desc)

    elif code == pvnRowSelected:
        vid = view.id()
        if vid == STEP_VIEW_ID:
            loadStep(cv, ud["steps"][data.row], ud)
    return 0


def tracerDlg():
    ctx = proContext()
    v = ctx.createView(ProView.Type_Custom, "Tracer")
    user_data = {}
    v.setup("<ui><hs><table id='1'/><vs><text id='2'/><hex id='3'/></vs><table id='4'/></hs></ui>", tracerCallback,
            user_data)
    dlg = ctx.createDialog(v)
    dlg.show()


def load_opcodes():
    o = []
    steps = os.listdir(DBGDIR)
    steps = [int(e.split('_')[0]) for e in steps if e.endswith("_o.bin")]
    for s in sorted(steps):
        with open(os.path.join(DBGDIR, str(s) + "_o.bin"), "rb") as f:
            op = int.from_bytes(f.read(), 'little')
            o.append(op)

    return o


program = load_opcodes()
tracerDlg()
