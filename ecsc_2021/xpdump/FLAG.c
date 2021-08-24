.text:0044E420 ; =============== S U B R O U T I N E =======================================
.text:0044E420
.text:0044E420 ; Attributes: bp-based frame
.text:0044E420
.text:0044E420 ; int __cdecl main_0(int argc, const char **argv, const char **envp)
.text:0044E420 _main_0         proc near               ; CODE XREF: _main↑j
.text:0044E420
.text:0044E420 var_10C         = byte ptr -10Ch
.text:0044E420 var_48          = dword ptr -48h
.text:0044E420 var_3C          = byte ptr -3Ch
.text:0044E420 var_3B          = byte ptr -3Bh
.text:0044E420 var_3A          = byte ptr -3Ah
.text:0044E420 var_39          = byte ptr -39h
.text:0044E420 var_38          = byte ptr -38h
.text:0044E420 var_37          = byte ptr -37h
.text:0044E420 var_36          = byte ptr -36h
.text:0044E420 var_35          = byte ptr -35h
.text:0044E420 var_34          = byte ptr -34h
.text:0044E420 var_33          = byte ptr -33h
.text:0044E420 var_32          = byte ptr -32h
.text:0044E420 var_31          = byte ptr -31h
.text:0044E420 var_30          = byte ptr -30h
.text:0044E420 var_2F          = byte ptr -2Fh
.text:0044E420 var_2E          = byte ptr -2Eh
.text:0044E420 var_2D          = byte ptr -2Dh
.text:0044E420 var_2C          = byte ptr -2Ch
.text:0044E420 var_2B          = byte ptr -2Bh
.text:0044E420 var_2A          = byte ptr -2Ah
.text:0044E420 var_29          = byte ptr -29h
.text:0044E420 var_28          = byte ptr -28h
.text:0044E420 var_27          = byte ptr -27h
.text:0044E420 var_26          = byte ptr -26h
.text:0044E420 var_25          = byte ptr -25h
.text:0044E420 var_1C          = byte ptr -1Ch
.text:0044E420 var_1B          = byte ptr -1Bh
.text:0044E420 var_1A          = byte ptr -1Ah
.text:0044E420 var_19          = byte ptr -19h
.text:0044E420 var_18          = byte ptr -18h
.text:0044E420 var_17          = byte ptr -17h
.text:0044E420 var_16          = byte ptr -16h
.text:0044E420 var_15          = byte ptr -15h
.text:0044E420 var_14          = byte ptr -14h
.text:0044E420 var_13          = byte ptr -13h
.text:0044E420 var_12          = byte ptr -12h
.text:0044E420 var_11          = byte ptr -11h
.text:0044E420 var_10          = byte ptr -10h
.text:0044E420 var_F           = byte ptr -0Fh
.text:0044E420 var_E           = byte ptr -0Eh
.text:0044E420 var_D           = byte ptr -0Dh
.text:0044E420 var_C           = byte ptr -0Ch
.text:0044E420 var_B           = byte ptr -0Bh
.text:0044E420 var_A           = byte ptr -0Ah
.text:0044E420 var_9           = byte ptr -9
.text:0044E420 var_8           = byte ptr -8
.text:0044E420 var_7           = byte ptr -7
.text:0044E420 var_6           = byte ptr -6
.text:0044E420 var_5           = byte ptr -5
.text:0044E420 argc            = dword ptr  8
.text:0044E420 argv            = dword ptr  0Ch
.text:0044E420 envp            = dword ptr  10h
.text:0044E420
.text:0044E420                 push    ebp
.text:0044E421                 mov     ebp, esp
.text:0044E423                 sub     esp, 10Ch
.text:0044E429                 push    ebx
.text:0044E42A                 push    esi
.text:0044E42B                 push    edi
.text:0044E42C                 lea     edi, [ebp+var_10C]
.text:0044E432                 mov     ecx, 43h
.text:0044E437                 mov     eax, 0CCCCCCCCh
.text:0044E43C                 rep stosd
.text:0044E43E                 cmp     dword_4FFD0C, 0
.text:0044E445                 jz      short loc_44E451
.text:0044E447                 mov     eax, 4
.text:0044E44C                 jmp     loc_44E578
.text:0044E451 ; ---------------------------------------------------------------------------
.text:0044E451
.text:0044E451 loc_44E451:                             ; CODE XREF: _main_0+25↑j
.text:0044E451                 mov     dword_4FFD0C, 539h
.text:0044E45B                 mov     esi, esp
.text:0044E45D                 push    2710h           ; dwMilliseconds
.text:0044E462                 call    ds:Sleep
.text:0044E468                 cmp     esi, esp
.text:0044E46A                 call    j___RTC_CheckEsp
.text:0044E46F                 mov     [ebp+var_1C], 0C7h ; 'Ç'
.text:0044E473                 mov     [ebp+var_1B], 26h ; '&'
.text:0044E477                 mov     [ebp+var_1A], 4Eh ; 'N'
.text:0044E47B                 mov     [ebp+var_19], 57h ; 'W'
.text:0044E47F                 mov     [ebp+var_18], 7Dh ; '}'
.text:0044E483                 mov     [ebp+var_17], 0E6h ; 'ć'
.text:0044E487                 mov     [ebp+var_16], 31h ; '1'
.text:0044E48B                 mov     [ebp+var_15], 45h ; 'E'
.text:0044E48F                 mov     [ebp+var_14], 4Eh ; 'N'
.text:0044E493                 mov     [ebp+var_13], 2Dh ; '-'
.text:0044E497                 mov     [ebp+var_12], 47h ; 'G'
.text:0044E49B                 mov     [ebp+var_11], 37h ; '7'
.text:0044E49F                 mov     [ebp+var_10], 58h ; 'X'
.text:0044E4A3                 mov     [ebp+var_F], 0E3h ; 'ă'
.text:0044E4A7                 mov     [ebp+var_E], 8Ah ; 'Š'
.text:0044E4AB                 mov     [ebp+var_D], 0A2h ; '˘'
.text:0044E4AF                 mov     [ebp+var_C], 71h ; 'q'
.text:0044E4B3                 mov     [ebp+var_B], 0B8h ; '¸'
.text:0044E4B7                 mov     [ebp+var_A], 0EEh ; 'î'
.text:0044E4BB                 mov     [ebp+var_9], 13h
.text:0044E4BF                 mov     [ebp+var_8], 8Fh ; 'Ź'
.text:0044E4C3                 mov     [ebp+var_7], 0F0h ; 'đ'
.text:0044E4C7                 mov     [ebp+var_6], 4Eh ; 'N'
.text:0044E4CB                 mov     [ebp+var_5], 0FFh
.text:0044E4CF                 mov     [ebp+var_3C], 0A2h ; '˘'
.text:0044E4D3                 mov     [ebp+var_3B], 45h ; 'E'
.text:0044E4D7                 mov     [ebp+var_3A], 3Dh ; '='
.text:0044E4DB                 mov     [ebp+var_39], 34h ; '4'
.text:0044E4DF                 mov     [ebp+var_38], 4Fh ; 'O'
.text:0044E4E3                 mov     [ebp+var_37], 0D7h ; '×'
.text:0044E4E7                 mov     [ebp+var_36], 4Ah ; 'J'
.text:0044E4EB                 mov     [ebp+var_35], 3Ch ; '<'
.text:0044E4EF                 mov     [ebp+var_34], 21h ; '!'
.text:0044E4F3                 mov     [ebp+var_33], 72h ; 'r'
.text:0044E4F7                 mov     [ebp+var_32], 23h ; '#'
.text:0044E4FB                 mov     [ebp+var_31], 56h ; 'V'
.text:0044E4FF                 mov     [ebp+var_30], 2Fh ; '/'
.text:0044E503                 mov     [ebp+var_2F], 84h ; '„'
.text:0044E507                 mov     [ebp+var_2E], 0D5h ; 'Ő'
.text:0044E50B                 mov     [ebp+var_2D], 0CEh ; 'Î'
.text:0044E50F                 mov     [ebp+var_2C], 18h
.text:0044E513                 mov     [ebp+var_2B], 0CEh ; 'Î'
.text:0044E517                 mov     [ebp+var_2A], 8Bh ; '‹'
.text:0044E51B                 mov     [ebp+var_29], 4Ch ; 'L'
.text:0044E51F                 mov     [ebp+var_28], 0D9h ; 'Ů'
.text:0044E523                 mov     [ebp+var_27], 0BDh ; '˝'
.text:0044E527                 mov     [ebp+var_26], 34h ; '4'
.text:0044E52B                 mov     [ebp+var_25], 82h ; '‚'
.text:0044E52F                 mov     [ebp+var_48], 0
.text:0044E536                 jmp     short loc_44E541
.text:0044E538 ; ---------------------------------------------------------------------------
.text:0044E538
.text:0044E538 loc_44E538:                             ; CODE XREF: _main_0+147↓j
.text:0044E538                 mov     eax, [ebp+var_48]
.text:0044E53B                 add     eax, 1
.text:0044E53E                 mov     [ebp+var_48], eax
.text:0044E541
.text:0044E541 loc_44E541:                             ; CODE XREF: _main_0+116↑j
.text:0044E541                 cmp     [ebp+var_48], 18h
.text:0044E545                 jnb     short loc_44E569
.text:0044E547                 mov     eax, [ebp+var_48]
.text:0044E54A                 movsx   ecx, [ebp+eax+var_1C]
.text:0044E54F                 mov     edx, [ebp+var_48]
.text:0044E552                 movsx   eax, [ebp+edx+var_3C]
.text:0044E557                 xor     ecx, eax
.text:0044E559                 push    ecx
.text:0044E55A                 push    offset unk_4DCE50
.text:0044E55F                 call    sub_44AE8B
.text:0044E564                 add     esp, 8
.text:0044E567                 jmp     short loc_44E538
.text:0044E569 ; ---------------------------------------------------------------------------
.text:0044E569
.text:0044E569 loc_44E569:                             ; CODE XREF: _main_0+125↑j
.text:0044E569                 push    offset unk_4DCE54
.text:0044E56E                 call    sub_44AE8B
.text:0044E573                 add     esp, 4
.text:0044E576                 xor     eax, eax
.text:0044E578
.text:0044E578 loc_44E578:                             ; CODE XREF: _main_0+2C↑j
.text:0044E578                 push    edx
.text:0044E579                 mov     ecx, ebp        ; Esp
.text:0044E57B                 push    eax
.text:0044E57C                 lea     edx, Fd         ; Fd
.text:0044E582                 call    j_@_RTC_CheckStackVars@8 ; _RTC_CheckStackVars(x,x)
.text:0044E587                 pop     eax
.text:0044E588                 pop     edx
.text:0044E589                 pop     edi
.text:0044E58A                 pop     esi
.text:0044E58B                 pop     ebx
.text:0044E58C                 add     esp, 10Ch
.text:0044E592                 cmp     ebp, esp
.text:0044E594                 call    j___RTC_CheckEsp
.text:0044E599                 mov     esp, ebp
.text:0044E59B                 pop     ebp
.text:0044E59C                 retn
.text:0044E59C _main_0         endp
.text:0044E59C