[bits 64]

section .data

exit_code_format: db "%lld", 0

data_start:
incbin "exported.ida.bin"

data_end:

extern exit
extern printf

section .text
_start:

mov rdi, data_start
mov rsi, data_end

push exit_label
incbin "server_challenge_code"

exit_label:

mov rdi, exit_code_format
mov rsi, rax
call printf

mov rdi, 0
call exit

