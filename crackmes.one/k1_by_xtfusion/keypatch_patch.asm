; detour
call 0x401A44


; initialize variables
mov dword ptr [ebp-0xC], 0
mov dword ptr [ebp-0x14], 0
mov dword ptr [ebp-0x18], 0
mov dword ptr [ebp-0x1C], 0
mov dword ptr [ebp-0x20], 0
ret


;detour
call 0x401A68

;finish crackme
sub esp, 0x4 ; prepare stack
mov dword ptr [esp], 0x403031 ; congrats
call _printf
lea eax, [ebp-0x68]
mov dword ptr [esp], eax
call _gets ; wait for key
add esp, 0x4 ; cleanup stack
ret
