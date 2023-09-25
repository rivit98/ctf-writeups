[bits 64]

section .text

global _start
_start:
	call setup
	nop
	nop
	nop
	nop

    push    rdi
    push    rsi
    mov     rax, r15
    mov     rdi, rax
    mov     rax, r9
    mov     rsi, rax
    call    sub_2B2
    pop     rsi
    pop     rdi

    mov     rax, r15
    mov     r10, rax
    mov     rax, r15
    mov     r11, rax
    mov     rax, r11
    add     rax, r9
    mov     r11, rax
    mov     rax, r8
    sub     r15, 8
    mov     [r15], rax
    mov     rax, r9
    sub     r15, 8
    mov     [r15], rax

loc_47:         ; CODE XREF: sub_0+CC↓j
    mov     rax, r10
    sub     r15, 8
    mov     [r15], rax
    mov     rax, r11
    sub     r15, 8
    mov     [r15], rax
    mov     rax, r10
    mov     r8, rax
    sub     r15, 8
    lea     rax, loc_74
    mov     [r15], rax
    jmp     loc_120
; ---------------------------------------------------------------------------

loc_74:         ; DATA XREF: sub_0+65↑o
    mov     rax, [r15]
    mov     r11, rax
    add     r15, 8
    mov     rax, [r15]
    mov     r10, rax
    add     r15, 8
    mov     rax, r10
    push    rbx
    mov     rbx, 1
    add     rax, rbx
    pop     rbx
    mov     r10, rax
    pushfq
    mov     rax, r10
    mov     rbx, rax
    mov     rax, r11
    mov     rcx, 2
    cmp     rbx, rax
    jz      short loc_BF
    sbb     rcx, rcx
    and     ecx, 0FFFFFFFDh
    add     ecx, 4

loc_BF:         ; CODE XREF: sub_0+B4↑j
    mov     r14, rcx
    popfq
    mov     rax, r14
    and     al, 1
    test    al, al
    jz      short loc_D1
    jmp     loc_47
; ---------------------------------------------------------------------------

loc_D1:         ; CODE XREF: sub_0+CA↑j
    mov     rax, [r15]
    mov     r9, rax
    add     r15, 8
    mov     rax, [r15]
    mov     r8, rax
    add     r15, 8
    mov     rax, r10
    sub     rax, r9
    mov     r10, rax
    mov     rax, r9
    mov     r11, rax
    mov     rax, r10
    mov     r9, rax
    mov     rax, r11
    mov     r10, rax
    sub     r15, 8
    lea     rax, loc_113
    mov     [r15], rax
    jmp     loc_1BA
; ---------------------------------------------------------------------------

loc_113:        ; DATA XREF: sub_0+104↑o
    mov     rax, r15
    add     rax, r9
    mov     r15, rax
    mov     rax, r8
    retn
; ---------------------------------------------------------------------------

loc_120:        ; CODE XREF: sub_0+6F↑j
    mov     rax, r9
    xor     rax, r9
    mov     r9, rax
    mov     al, [r8]
    mov     r9b, al
    mov     al, r9b
    xor     al, 13h
    mov     r9b, al
    pushfq
    mov     al, r9b
    mov     rbx, rax
    mov     al, 80h
    mov     rcx, 2
    cmp     rbx, rax
    jz      short loc_158
    sbb     rcx, rcx
    and     ecx, 0FFFFFFFDh
    add     ecx, 4

loc_158:        ; CODE XREF: sub_0+14D↑j
    mov     r14, rcx
    popfq
    mov     rax, r14
    and     al, 4
    test    al, al
    jz      short loc_16D
    mov     al, r9b
    xor     al, 37h
    mov     r9b, al
	
loc_16D:        ; CODE XREF: sub_0+163↑j
    mov     al, r9b
    sub     al, 1Eh
    mov     r9b, al
    pushfq
    mov     al, r9b
    mov     rbx, rax
    mov     al, 10h
    mov     rcx, 2
    cmp     rbx, rax
    jz      short loc_196
    sbb     rcx, rcx
    and     ecx, 0FFFFFFFDh
    add     ecx, 4

loc_196:        ; CODE XREF: sub_0+18B↑j
    mov     r14, rcx
    popfq
    mov     rax, r14
    and     al, 3
    test    al, al
    jz      short loc_1AB
    mov     al, r9b
    xor     al, 31h
    mov     r9b, al

loc_1AB:        ; CODE XREF: sub_0+1A1↑j
    mov     al, r9b
    mov     [r8], al
    mov     rax, [r15]
    add     r15, 8
    jmp     rax
; ---------------------------------------------------------------------------

loc_1BA:        ; CODE XREF: sub_0+10E↑j
    nop

loc_1BB:        ; CODE XREF: sub_0+276↓j
    pushfq
    mov     rax, r10
    mov     rbx, rax
    push    rbx
    mov     rbx, 0
    mov     rax, rbx
    pop     rbx
    mov     rcx, 2
    cmp     rbx, rax
    jz      short loc_1E9
    sbb     rcx, rcx
    and     ecx, 0FFFFFFFDh
    add     ecx, 4

loc_1E9:        ; CODE XREF: sub_0+1DE↑j
    mov     r14, rcx
    popfq
    mov     rax, r14
    and     al, 2
    test    al, al
    jz      short loc_1FB
    jmp     loc_296
; ---------------------------------------------------------------------------

loc_1FB:        ; CODE XREF: sub_0+1F4↑j
    pushfq
    mov     al, [r8]
    mov     rbx, rax
    mov     al, [r9]
    mov     rcx, 2
    cmp     rbx, rax
    jz      short loc_21D
    sbb     rcx, rcx
    and     ecx, 0FFFFFFFDh
    add     ecx, 4

loc_21D:        ; CODE XREF: sub_0+212↑j
    mov     r14, rcx
    popfq
    mov     rax, r14
    and     al, 1
    test    al, al
    jz      short loc_22C
    jmp     short loc_27B
; ---------------------------------------------------------------------------

loc_22C:        ; CODE XREF: sub_0+228↑j
    mov     rax, r14
    and     al, 4
    test    al, al
    jz      short loc_237
    jmp     short loc_27B
; ---------------------------------------------------------------------------

loc_237:        ; CODE XREF: sub_0+233↑j
    mov     rax, r8
    push    rbx
    mov     rbx, 1
    add     rax, rbx
    pop     rbx
    mov     r8, rax
    mov     rax, r9
    push    rbx
    mov     rbx, 1
    add     rax, rbx
    pop     rbx
    mov     r9, rax
    mov     rax, r10
    push    rbx
    mov     rbx, 1
    sub     rax, rbx
    pop     rbx
    mov     r10, rax
    jmp     loc_1BB
; ---------------------------------------------------------------------------

loc_27B:        ; CODE XREF: sub_0+22A↑j
    ; sub_0+235↑j
    push    rbx
    mov     rbx, 0
    mov     rax, rbx
    pop     rbx
    mov     r8, rax
    mov     rax, [r15]
    add     r15, 8
    jmp     rax
; ---------------------------------------------------------------------------

loc_296:        ; CODE XREF: sub_0+1F6↑j
    push    rbx
    mov     rbx, 1
    mov     rax, rbx
    pop     rbx
    mov     r8, rax
    mov     rax, [r15]
    add     r15, 8
    jmp     rax

; ---------------------------------------------------------------------------
    retn


; __int64 sub_2B2()
sub_2B2:
    push    rdi
    push    rsi
    push    rdx
    mov     rdx, rsi
    mov     rsi, rdi
    mov     rdi, 0
    mov     rax, 0
    syscall     ; Low latency system call
    pop     rdx
    pop     rsi
    pop     rdi
    retn

setup:
	pop		rax
	push	finish_prog
	push 	rax
	mov 	r15, mem
	mov 	r9, 0x1d
	mov		r8, key
	mov     rax, r15
    sub     rax, r9
    mov     r15, rax
	ret


finish_prog:
	cmp rax, 1
	jz ok
	mov rdi, 0
	jmp sys
ok:
	mov rdi, 1

sys:
	mov rax, 0x3c
	syscall


section .data
	mem1 times 0x1000 db 0
	mem times 0x1000 db 0
	mem2 times 0x1000 db 0

	key db 0x52, 0x5e, 0x43, 0x52, 0x49, 0x57, 0x4a, 0x4d, 0x3c, 0x36, 0x2e, 0x5b, 0x35, 0x49, 0x2e, 0x47, 0x60, 0x2e, 0x43, 0x33, 0x47, 0x33, 0x43, 0x42, 0x35, 0x5f, 0x56, 0x3f, 0x50, 0xd0, 0xa6, 0x79
