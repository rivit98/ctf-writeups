%macro PUSH_IMM 1
    db '1'              ; opcode
    db %1               ; 8-byte immediate value
%endmacro

%macro PUSH_REG 1
    db '2'
    db %1
%endmacro

%macro POP_REG 1
    db '3'
    db %1
%endmacro

%macro MOV_REG_REG 2
    db '4'
    db %1
    db %2
%endmacro

%macro MEMCPY 3
    db '6'
    db %1           ; dst reg
    db %2           ; src reg
    db %3           ; size-1
    db 0x61
%endmacro

%macro AND 2
    db '7'
    db %1
    db %2
%endmacro

%macro OR 2
    db '8'
    db %1
    db %2
%endmacro

%macro XOR 2
    db '9'
    db %1
    db %2
%endmacro

%macro SHR 2
    db 'A'
    db %1
    db %2
%endmacro

%macro SHL 2
    db 'B'
    db %1
    db %2
%endmacro

%macro ADD 2
    db 'C'
    db %1
    db %2
%endmacro

%macro SUB 2
    db 'D'
    db %1
    db %2
%endmacro

%macro EXPAND 0
    db 'F'
%endmacro
