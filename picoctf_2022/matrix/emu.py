bytecode_orig = [
    0x81, 0x75, 0x00, 0x80, 0x00, 0x80, 0x0A, 0x80, 0x3F, 0x80,
    0x65, 0x80, 0x76, 0x80, 0x69, 0x80, 0x6C, 0x80, 0x61, 0x80,
    0x20, 0x80, 0x74, 0x80, 0x75, 0x80, 0x6F, 0x80, 0x20, 0x80,
    0x74, 0x80, 0x69, 0x80, 0x20, 0x80, 0x65, 0x80, 0x6B, 0x80,
    0x61, 0x80, 0x6D, 0x80, 0x20, 0x80, 0x75, 0x80, 0x6F, 0x80,
    0x79, 0x80, 0x20, 0x80, 0x6E, 0x80, 0x61, 0x80, 0x43, 0x80,
    0x0A, 0x80, 0x58, 0x80, 0x20, 0x80, 0x49, 0x80, 0x20, 0x80,
    0x52, 0x80, 0x20, 0x80, 0x54, 0x80, 0x20, 0x80, 0x41, 0x80,
    0x20, 0x80, 0x4D, 0x80, 0x20, 0x80, 0x65, 0x80, 0x68, 0x80,
    0x74, 0x80, 0x20, 0x80, 0x6F, 0x80, 0x74, 0x80, 0x20, 0x80,
    0x65, 0x80, 0x6D, 0x80, 0x6F, 0x80, 0x63, 0x80, 0x6C, 0x80,
    0x65, 0x80, 0x57, 0x81, 0x3B, 0x01, 0x30, 0x80, 0x01, 0x80,
    0x01, 0x80, 0x00, 0xC0, 0x10, 0x80, 0x75, 0x13, 0x81, 0xA0,
    0x00, 0x31, 0x10, 0x80, 0x64, 0x13, 0x81, 0xAA, 0x00, 0x31,
    0x10, 0x80, 0x6C, 0x13, 0x81, 0xB4, 0x00, 0x31, 0x10, 0x80,
    0x72, 0x13, 0x81, 0xC0, 0x00, 0x31, 0x81, 0xFB, 0x00, 0x30,
    0x11, 0x20, 0x80, 0x01, 0x13, 0x21, 0x81, 0xCC, 0x00, 0x30,
    0x11, 0x20, 0x80, 0x01, 0x12, 0x21, 0x81, 0xCC, 0x00, 0x30,
    0x11, 0x20, 0x20, 0x80, 0x01, 0x13, 0x21, 0x21, 0x81, 0xCC,
    0x00, 0x30, 0x11, 0x20, 0x20, 0x80, 0x01, 0x12, 0x21, 0x21,
    0x81, 0xCC, 0x00, 0x30, 0x20, 0x20, 0x81, 0xDA, 0x00, 0x21,
    0x10, 0x20, 0x80, 0x10, 0x81, 0x47, 0x01, 0x30, 0x14, 0x10,
    0x20, 0x12, 0x21, 0x14, 0x21, 0x14, 0x21, 0x14, 0x20, 0x81,
    0xEF, 0x00, 0x21, 0x80, 0x02, 0x81, 0x61, 0x01, 0x30, 0x81,
    0x7B, 0x00, 0x14, 0x81, 0x74, 0x01, 0x12, 0x30, 0x80, 0x00,
    0x01, 0x81, 0x38, 0x01, 0x80, 0x00, 0x80, 0x0A, 0x80, 0x2E,
    0x80, 0x65, 0x80, 0x75, 0x80, 0x72, 0x80, 0x67, 0x80, 0x20,
    0x80, 0x61, 0x80, 0x20, 0x80, 0x79, 0x80, 0x62, 0x80, 0x20,
    0x80, 0x6E, 0x80, 0x65, 0x80, 0x74, 0x80, 0x61, 0x80, 0x65,
    0x80, 0x20, 0x80, 0x65, 0x80, 0x72, 0x80, 0x65, 0x80, 0x77,
    0x80, 0x20, 0x80, 0x75, 0x80, 0x6F, 0x80, 0x59, 0x81, 0x3B,
    0x01, 0x30, 0x80, 0x01, 0x01, 0x10, 0x81, 0x45, 0x01, 0x31,
    0xC1, 0x81, 0x3B, 0x01, 0x30, 0x11, 0x30, 0x80, 0x00, 0x20,
    0x20, 0x10, 0x81, 0x5B, 0x01, 0x31, 0x80, 0x01, 0x13, 0x21,
    0x10, 0x21, 0x12, 0x81, 0x49, 0x01, 0x30, 0x11, 0x21, 0x11,
    0x21, 0x14, 0x30, 0x10, 0x81, 0x71, 0x01, 0x31, 0x80, 0x01,
    0x13, 0x20, 0x10, 0x12, 0x21, 0x81, 0x61, 0x01, 0x30, 0x11,
    0x14, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30,
    0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB,
    0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30,
    0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB,
    0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30,
    0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB,
    0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30,
    0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00,
    0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x81, 0x7F, 0x05, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00,
    0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x81, 0x7F, 0x05, 0x30,
    0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB,
    0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30,
    0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB,
    0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0x74, 0x05, 0x30,
    0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB,
    0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30,
    0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00,
    0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00,
    0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00,
    0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00,
    0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB,
    0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30,
    0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB,
    0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00,
    0x81, 0xFB, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB,
    0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30,
    0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00,
    0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00,
    0x81, 0x74, 0x05, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB,
    0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00,
    0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x81, 0x7F, 0x05, 0x30,
    0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB,
    0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30,
    0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00,
    0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30,
    0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB,
    0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30,
    0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00,
    0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00,
    0x81, 0xFB, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB,
    0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30,
    0x81, 0xFB, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB,
    0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00,
    0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30,
    0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00,
    0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00,
    0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00,
    0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00,
    0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB,
    0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30,
    0x81, 0xFB, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB,
    0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30,
    0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB,
    0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30,
    0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00,
    0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00,
    0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00,
    0x81, 0xFB, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB,
    0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00,
    0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB,
    0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30,
    0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB,
    0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30,
    0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00,
    0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30,
    0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00,
    0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x81, 0x74, 0x05, 0x30, 0x30, 0x00,
    0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30,
    0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB,
    0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30,
    0x81, 0xFB, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB,
    0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30,
    0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB,
    0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x81, 0xFB, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB,
    0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00,
    0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00, 0x00, 0x00,
    0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB,
    0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30,
    0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x30, 0x00,
    0x00, 0x00, 0x81, 0xFB, 0x00, 0x30, 0x81, 0x74, 0x05, 0x30,
    0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB,
    0x00, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30,
    0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x30, 0x00,
    0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30,
    0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x81, 0x74,
    0x05, 0x30, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB, 0x00, 0x30,
    0x30, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x81, 0xFB,
    0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30,
    0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB,
    0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30,
    0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB,
    0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30,
    0x81, 0xFB, 0x00, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x81, 0x85,
    0x05, 0x30, 0x81, 0xFB, 0x00, 0x30, 0x20, 0x10, 0x81, 0xFB,
    0x00, 0x31, 0x80, 0x01, 0x13, 0x21, 0x30, 0x20, 0x80, 0x01,
    0x12, 0x21, 0x30, 0x11, 0x11, 0x11, 0x11, 0x81, 0xCE, 0x05,
    0x80, 0x00, 0x80, 0x0A, 0x80, 0x21, 0x80, 0x74, 0x80, 0x69,
    0x80, 0x20, 0x80, 0x65, 0x80, 0x64, 0x80, 0x61, 0x80, 0x6D,
    0x80, 0x20, 0x80, 0x75, 0x80, 0x6F, 0x80, 0x79, 0x80, 0x20,
    0x80, 0x2C, 0x80, 0x73, 0x80, 0x6E, 0x80, 0x6F, 0x80, 0x69,
    0x80, 0x74, 0x80, 0x61, 0x80, 0x6C, 0x80, 0x75, 0x80, 0x74,
    0x80, 0x61, 0x80, 0x72, 0x80, 0x67, 0x80, 0x6E, 0x80, 0x6F,
    0x80, 0x43, 0x81, 0x3B, 0x01, 0x30, 0x81, 0xF8, 0x00, 0x30
]

class VM:
    def __init__(self, input, debug=0):
        self.pc = 0
        self.bytecode = bytecode_orig
        self.mem = []
        self.input = input
        self.input_idx = 0
        self.executed_instr = 0
        self.DEBUG = debug
        self.DEBUG2 = False
        self.callstack = []
        self.s = []
        print(''.join(input))

    def lh(self, l):
        return list(map(hex, l))

    def print(self, m):
        if self.DEBUG2:
            print(f'{hex(self.pc)}: {m}')
            print(f"mem={self.lh(self.mem)} stack={self.lh(self.s)}")
            print()

    def run(self):
        running, (out1, out2) = self.step()
        while running:
            running, (out1, out2) = self.step()

        return running == 0  # finished successfully

    def step(self):
        bytecode = self.bytecode
        pc = self.pc
        instr = bytecode[self.pc]
        next_instr = self.pc + 1
        self.pc += 1
        match instr:
            case 0:
                self.print("NOP")
                pass
            case 1:
                v1 = self.s.pop()
                self.print(f"POP RET")
                return 0, (0, v1)
            case 0x10:
                self.s.append(self.s[-1])
                self.print("DUP")
            case 0x11:
                self.s.pop()
                self.print("POP")
            case 0x12:
                self.s.append(self.s.pop() + self.s.pop())
                self.print(f"ADD")
            case 0x13:
                v1 = self.s.pop()
                v2 = self.s.pop()
                self.s.append(v2 - v1)
                self.print(f"SUB")
            case 0x14:
                v1 = self.s.pop()
                v2 = self.s.pop()
                self.s.append(v1)
                self.s.append(v2)
                self.print(f"SWAP")
            case 0x20:
                self.mem.append(self.s.pop())
                self.print(f"WRITE_MEM")
            case 0x21:
                self.s.append(self.mem.pop())
                self.print(f"READ_MEM")
            case 0x30:
                self.pc = self.s.pop()
                self.print(f"RET {hex(self.pc)}")
                self.callstack.append(self.pc)
                if self.pc == 251:
                    self.print("You were eaten...")
                    return 0, (None, None)
                elif self.pc == 117:  # start game loop
                    self.DEBUG2 = self.DEBUG
            case 0x31:
                target = self.s.pop()
                v = self.s.pop()
                self.print(f"JZ ({v} == 0) -> {hex(target)}")
                if v == 0:
                    self.pc = target
                    if self.pc == 251:
                        self.print("You were eaten...")
                        return 0, (None, None)
            case 0x32:
                target = self.s.pop()
                v = self.s.pop()
                self.print(f"JZ ({v} != 0) -> {hex(target)}")
                if v != 0:
                    self.pc = target
            case 0x33:
                target = self.s.pop()
                v = self.s.pop()
                self.print(f"JZ ({v} < 0) -> {hex(target)}")
                if v < 0:
                    self.pc = target
            case 0x34:
                target = self.s.pop()
                v = self.s.pop()
                self.print(f"JZ ({v} <= 0) -> {hex(target)}")
                if v <= 0:
                    self.pc = target
            case 0xc0:
                # c = sys.stdin.read(1)
                c = self.input[self.input_idx]
                self.input_idx += 1
                self.s.append(ord(c))
                self.print(f"GETC {c} {ord(c)}")
            case 0xc1:
                v9 = self.s.pop()
                c = chr(v9)
                # sys.stdout.write(chr(v9))
                self.print(f"PUTC {v9} '{c}'")
            case 0x80:
                self.pc = pc + 2
                v = bytecode[next_instr]
                self.s.append(v)
                self.print(f"PUSH2 {hex(v)}")
            case 0x81:
                self.pc = pc + 3
                v = (bytecode[next_instr]) | bytecode[next_instr + 1] << 8
                self.s.append(v)
                self.print(f"PUSH3 {hex(v)}")
            case _:
                self.print("BAD INSTR")
                return 0, (1, 0)

        self.executed_instr += 1
        return 1, (None, None)


def test_simple():
    correct_seq = 'rrrddrrrrrrddddddlllllddrrrrdddrruuuruuuuuuurrddddddddlddrd'
    inc_c = 'rrrrr' + 'lr' * 10 + 'lllll'  # increase health
    moves = inc_c + correct_seq
    vm = VM(list(moves), debug=1)
    vm.run()
    print(moves)


if __name__ == '__main__':
    test_simple()