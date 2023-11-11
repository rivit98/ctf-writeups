seg000:0000 ; Format      : MS-DOS executable (EXE)
seg000:0000 ; Base Address: 1000h Range: 10000h-18F50h Loaded length: 8F50h
seg000:0000 ; Entry Point : 1000:0
seg000:0000
seg000:0000                 .686p
seg000:0000                 .mmx
seg000:0000                 .model large
seg000:0000
seg000:0000 ; ===========================================================================
seg000:0000
seg000:0000 ; Segment type: Pure code
seg000:0000 seg000          segment byte public 'CODE' use16
seg000:0000                 assume cs:seg000
seg000:0000                 assume es:nothing, ss:seg006, ds:nothing, fs:nothing, gs:nothing
seg000:0000
seg000:0000 ; =============== S U B R O U T I N E =======================================
seg000:0000
seg000:0000 ; Attributes: noreturn
seg000:0000
seg000:0000 ; int __cdecl start(int argc, const char **argv, const char **envp)
seg000:0000                 public start
seg000:0000 start           proc near
seg000:0000
seg000:0000 argc            = word ptr  2
seg000:0000 argv            = dword ptr  4
seg000:0000 envp            = dword ptr  8
seg000:0000
seg000:0000                 call    main
seg000:0000 start           endp
seg000:0000
seg000:0000 ; ---------------------------------------------------------------------------
seg000:0003                 db 0C3h
seg000:0004                 db 21h, 54h, 68h, 69h, 73h, 20h, 70h, 72h, 6Fh, 67h, 72h
seg000:0004                 db 61h, 6Dh, 20h, 63h, 61h, 2 dup(6Eh), 6Fh, 74h, 20h
seg000:0004                 db 62h, 65h, 20h, 72h, 75h, 6Eh, 20h, 69h, 6Eh, 20h, 44h
seg000:0004                 db 4Fh, 53h, 20h, 6Dh, 6Fh, 64h, 65h, 2Eh, 2 dup(0Dh)
seg000:0004                 db 0Ah, 24h
seg000:0030
seg000:0030 ; =============== S U B R O U T I N E =======================================
seg000:0030
seg000:0030 ; Attributes: noreturn
seg000:0030
seg000:0030 ; int __cdecl main(int argc, const char **argv, const char **envp)
seg000:0030 main            proc near               ; CODE XREF: start↑p
seg000:0030                 mov     ax, seg seg006
seg000:0033                 mov     ss, ax
seg000:0035                 mov     sp, 20h ; ' '
seg000:0038                 mov     ax, seg seg000
seg000:003B                 mov     ds, ax
seg000:003D                 assume ds:seg000
seg000:003D                 mov     es, ax
seg000:003F                 assume es:seg000
seg000:003F                 mov     fs, ax
seg000:0041                 assume fs:seg000
seg000:0041                 mov     gs, ax
seg000:0043                 assume gs:seg000
seg000:0043                 mov     bl, 0
seg000:0045                 mov     ax, 1003h
seg000:0048                 int     10h             ; - VIDEO - TOGGLE INTENSITY/BLINKING BIT (Jr, PS, TANDY 1000, EGA, VGA)
seg000:0048                                         ; BL = 00h enable background intensity
seg000:0048                                         ; = 01h enable blink
seg000:004A                 mov     ch, 20h ; ' '
seg000:004C                 mov     ah, 1
seg000:004E                 mov     al, 3
seg000:0050                 int     10h             ; - VIDEO - SET CURSOR CHARACTERISTICS
seg000:0050                                         ; CH bits 0-4 = start line for cursor in character cell
seg000:0050                                         ; bits 5-6 = blink attribute
seg000:0050                                         ; CL bits 0-4 = end line for cursor in character cell
seg000:0052                 call    scroll_page_up
seg000:0055                 call    draw_scene
seg000:0058                 call    game
seg000:005B                 call    scroll_page_up
seg000:005E                 xor     dx, dx
seg000:0060                 call    set_cursor_position
seg000:0063                 mov     ax, 4C00h
seg000:0066                 int     21h             ; DOS - 2+ - QUIT WITH EXIT CODE (EXIT)
seg000:0066 main            endp                    ; AL = exit code
seg000:0066
seg000:0068
seg000:0068 ; =============== S U B R O U T I N E =======================================
seg000:0068
seg000:0068
seg000:0068 get_enhanced_keystroke proc near        ; CODE XREF: get_enhanced_keystroke+7↓j
seg000:0068                                         ; unknown_call_dynamics+3↓p ...
seg000:0068                 mov     ah, 11h
seg000:006A                 int     16h             ; KEYBOARD - CHECK ENHANCED KEYSTROKE (AT model 339,XT2,XT286,PS)
seg000:006A                                         ; Return: ZF clear if keystroke available
seg000:006A                                         ; AH = scan code \ meaningless if ZF = 1
seg000:006A                                         ; AL = character /
seg000:006A                                         ; ZF set if kbd buffer empty
seg000:006C                 jnz     short loc_10071
seg000:006E                 hlt
seg000:006F ; ---------------------------------------------------------------------------
seg000:006F                 jmp     short get_enhanced_keystroke
seg000:0071 ; ---------------------------------------------------------------------------
seg000:0071
seg000:0071 loc_10071:                              ; CODE XREF: get_enhanced_keystroke+4↑j
seg000:0071                 mov     ah, 10h
seg000:0073                 int     16h             ; KEYBOARD - GET ENHANCED KEYSTROKE (AT model 339,XT2,XT286,PS)
seg000:0073                                         ; Return: AH = scan code, AL = character
seg000:0075                 retn
seg000:0075 get_enhanced_keystroke endp
seg000:0075
seg000:0076
seg000:0076 ; =============== S U B R O U T I N E =======================================
seg000:0076
seg000:0076
seg000:0076 read_char       proc near               ; CODE XREF: handle_input_on_first_screen_konami:loc_108D2↓p
seg000:0076                 pusha
seg000:0077                 mov     ax, 0
seg000:007A                 mov     ah, 1
seg000:007C                 int     16h             ; KEYBOARD - CHECK BUFFER, DO NOT CLEAR
seg000:007C                                         ; Return: ZF clear if character in buffer
seg000:007C                                         ; AH = scan code, AL = character
seg000:007C                                         ; ZF set if no character in buffer
seg000:007E                 jz      short loc_1008D
seg000:0080                 mov     ax, 0
seg000:0083                 int     16h             ; KEYBOARD - READ CHAR FROM BUFFER, WAIT IF EMPTY
seg000:0083                                         ; Return: AH = scan code, AL = character
seg000:0085                 mov     word_10092, ax
seg000:0088                 popa
seg000:0089                 mov     ax, word_10092
seg000:008C                 retn
seg000:008D ; ---------------------------------------------------------------------------
seg000:008D
seg000:008D loc_1008D:                              ; CODE XREF: read_char+8↑j
seg000:008D                 popa
seg000:008E                 mov     ax, 0
seg000:0091                 retn
seg000:0091 read_char       endp
seg000:0091
seg000:0091 ; ---------------------------------------------------------------------------
seg000:0092 word_10092      dw 0                    ; DATA XREF: read_char+F↑w
seg000:0092                                         ; read_char+13↑r
seg000:0094
seg000:0094 ; =============== S U B R O U T I N E =======================================
seg000:0094
seg000:0094
seg000:0094 srand           proc near               ; CODE XREF: handle_input_on_first_screen_konami:loc_1094D↓p
seg000:0094                 mov     seed, ax
seg000:0097                 retn
seg000:0097 srand           endp
seg000:0097
seg000:0097 ; ---------------------------------------------------------------------------
seg000:0098 seed            dw 0                    ; DATA XREF: srand↑w
seg000:0098                                         ; lcg_maybe+1↓r ...
seg000:009A
seg000:009A ; =============== S U B R O U T I N E =======================================
seg000:009A
seg000:009A
seg000:009A rand            proc near               ; CODE XREF: get_sequence+7↓p
seg000:009A                 push    dx
seg000:009B                 push    bx
seg000:009C                 push    ax
seg000:009D                 sub     bx, ax
seg000:009F                 call    lcg_maybe
seg000:00A2                 mov     dx, bx
seg000:00A4                 add     dx, 1
seg000:00A7                 mul     dx
seg000:00A9                 mov     cx, dx
seg000:00AB                 pop     ax
seg000:00AC                 pop     bx
seg000:00AD                 pop     dx
seg000:00AE                 add     cx, ax
seg000:00B0                 retn
seg000:00B0 rand            endp
seg000:00B0
seg000:00B1
seg000:00B1 ; =============== S U B R O U T I N E =======================================
seg000:00B1
seg000:00B1
seg000:00B1 lcg_maybe       proc near               ; CODE XREF: rand+5↑p
seg000:00B1                 push    dx
seg000:00B2                 mov     ax, seed
seg000:00B5                 mov     dx, 5A7Fh
seg000:00B8                 mul     dx
seg000:00BA                 add     ax, 3079h
seg000:00BD                 adc     dx, 0
seg000:00C0                 mov     seed, ax
seg000:00C3                 pop     dx
seg000:00C4                 retn
seg000:00C4 lcg_maybe       endp
seg000:00C4
seg000:00C5
seg000:00C5 ; =============== S U B R O U T I N E =======================================
seg000:00C5
seg000:00C5
seg000:00C5 sub_100C5       proc near               ; CODE XREF: do_some_operations_on_input+6↓p
seg000:00C5                                         ; do_some_operations_on_input+17↓p
seg000:00C5                 pusha
seg000:00C6                 mov     si, ax
seg000:00C8                 mov     di, 0FAh
seg000:00CB
seg000:00CB loc_100CB:                              ; CODE XREF: sub_100C5+2E↓j
seg000:00CB                 mov     ax, [si]
seg000:00CD                 shl     ax, 1
seg000:00CF                 mov     [di], ax
seg000:00D1                 inc     si
seg000:00D2                 inc     si
seg000:00D3                 inc     di
seg000:00D4                 inc     di
seg000:00D5                 mov     cx, 7
seg000:00D8
seg000:00D8 loc_100D8:                              ; CODE XREF: sub_100C5+23↓j
seg000:00D8                 mov     ax, [si]
seg000:00DA
seg000:00DA loc_100DA:
seg000:00DA                 shl     ax, 1
seg000:00DC                 jnb     short loc_100E2
seg000:00DE                 add     word ptr [di-2], 1
seg000:00E2
seg000:00E2 loc_100E2:                              ; CODE XREF: sub_100C5+17↑j
seg000:00E2                 mov     [di], ax
seg000:00E4                 inc     si
seg000:00E5                 inc     si
seg000:00E6                 inc     di
seg000:00E7                 inc     di
seg000:00E8                 loop    loc_100D8
seg000:00EA                 mov     si, 0FAh
seg000:00ED                 mov     di, 0FAh
seg000:00F0                 dec     dx
seg000:00F1                 test    dx, dx
seg000:00F3                 jnz     short loc_100CB
seg000:00F5                 popa
seg000:00F6                 mov     ax, 0FAh
seg000:00F9                 retn
seg000:00F9 sub_100C5       endp
seg000:00F9
seg000:00F9 ; ---------------------------------------------------------------------------
seg000:00FA                 db 10h dup(0)
seg000:010A
seg000:010A ; =============== S U B R O U T I N E =======================================
seg000:010A
seg000:010A
seg000:010A sum_two_arrays  proc near               ; CODE XREF: do_some_operations_on_input+1D↓p
seg000:010A                                         ; do_some_operations_on_input+2D↓p
seg000:010A                 pusha
seg000:010B                 mov     di, ax
seg000:010D                 add     di, 0Eh
seg000:0110                 mov     si, dx
seg000:0112                 add     si, 0Eh
seg000:0115                 mov     bx, 134h
seg000:0118                 add     bx, 0Eh
seg000:011B                 clc
seg000:011C                 mov     cx, 8
seg000:011F
seg000:011F loc_1011F:                              ; CODE XREF: sum_two_arrays+23↓j
seg000:011F                 mov     ax, [di]
seg000:0121                 mov     dx, [si]
seg000:0123                 adc     ax, dx
seg000:0125                 mov     [bx], ax
seg000:0127                 dec     si
seg000:0128                 dec     si
seg000:0129                 dec     di
seg000:012A                 dec     di
seg000:012B                 dec     bx
seg000:012C                 dec     bx
seg000:012D                 loop    loc_1011F
seg000:012F                 popa
seg000:0130                 mov     ax, 134h
seg000:0133                 retn
seg000:0133 sum_two_arrays  endp
seg000:0133
seg000:0133 ; ---------------------------------------------------------------------------
seg000:0134                 db 10h dup(0)
seg000:0144
seg000:0144 ; =============== S U B R O U T I N E =======================================
seg000:0144
seg000:0144
seg000:0144 subtract_two_arrays proc near           ; CODE XREF: do_some_operations_on_input+31↓p
seg000:0144                 pusha
seg000:0145                 mov     di, ax
seg000:0147                 add     di, 0Eh
seg000:014A                 mov     si, dx
seg000:014C                 add     si, 0Eh
seg000:014F                 mov     bx, 16Eh
seg000:0152                 add     bx, 0Eh
seg000:0155                 clc
seg000:0156                 mov     cx, 8
seg000:0159
seg000:0159 loc_10159:                              ; CODE XREF: subtract_two_arrays+23↓j
seg000:0159                 mov     ax, [di]
seg000:015B                 mov     dx, [si]
seg000:015D                 sbb     ax, dx
seg000:015F                 mov     [bx], ax
seg000:0161                 dec     si
seg000:0162                 dec     si
seg000:0163                 dec     di
seg000:0164                 dec     di
seg000:0165                 dec     bx
seg000:0166                 dec     bx
seg000:0167                 loop    loc_10159
seg000:0169                 popa
seg000:016A                 mov     ax, 16Eh
seg000:016D                 retn
seg000:016D subtract_two_arrays endp
seg000:016D
seg000:016D ; ---------------------------------------------------------------------------
seg000:016E                 db 10h dup(0)
seg000:017E
seg000:017E ; =============== S U B R O U T I N E =======================================
seg000:017E
seg000:017E
seg000:017E do_some_operations_on_input proc near   ; CODE XREF: round_result+37↓p
seg000:017E                 pusha
seg000:017F                 push    ax
seg000:0180                 push    ax
seg000:0181                 mov     dx, 6
seg000:0184                 call    sub_100C5
seg000:0187                 mov     di, 1BAh
seg000:018A                 mov     si, ax
seg000:018C                 mov     cx, 8
seg000:018F                 rep movsw
seg000:0191                 pop     ax
seg000:0192                 mov     dx, 10h
seg000:0195                 call    sub_100C5
seg000:0198                 mov     dx, 1BAh
seg000:019B                 call    sum_two_arrays
seg000:019E                 push    ax
seg000:019F                 mov     si, 1CAh
seg000:01A2                 add     si, 0Eh
seg000:01A5                 mov     [si], bx
seg000:01A7                 mov     ax, 1CAh
seg000:01AA                 pop     dx
seg000:01AB                 call    sum_two_arrays
seg000:01AE                 pop     dx
seg000:01AF                 call    subtract_two_arrays
seg000:01B2                 mov     temp, ax
seg000:01B5                 popa
seg000:01B6                 mov     ax, temp
seg000:01B9                 retn
seg000:01B9 do_some_operations_on_input endp
seg000:01B9
seg000:01B9 ; ---------------------------------------------------------------------------
seg000:01BA                 db 20h dup(0)
seg000:01DA temp            dw 0                    ; DATA XREF: do_some_operations_on_input+34↑w
seg000:01DA                                         ; do_some_operations_on_input+38↑r
seg000:01DC
seg000:01DC ; =============== S U B R O U T I N E =======================================
seg000:01DC
seg000:01DC
seg000:01DC timer           proc near               ; CODE XREF: handle_left+8↓p
seg000:01DC                                         ; handle_down+B↓p ...
seg000:01DC                 pusha
seg000:01DD                 mov     cx, ax
seg000:01DF                 mov     al, 0B6h
seg000:01E1                 out     43h, al         ; Timer 8253-5 (AT: 8254.2).
seg000:01E3                 mov     ax, cx
seg000:01E5                 out     42h, al         ; Timer 8253-5 (AT: 8254.2).
seg000:01E7                 mov     al, ah
seg000:01E9                 out     42h, al         ; Timer 8253-5 (AT: 8254.2).
seg000:01EB                 in      al, 61h         ; PC/XT PPI port B bits:
seg000:01EB                                         ; 0: Tmr 2 gate ═╦═► OR 03H=spkr ON
seg000:01EB                                         ; 1: Tmr 2 data ═╝  AND 0fcH=spkr OFF
seg000:01EB                                         ; 3: 1=read high switches
seg000:01EB                                         ; 4: 0=enable RAM parity checking
seg000:01EB                                         ; 5: 0=enable I/O channel check
seg000:01EB                                         ; 6: 0=hold keyboard clock low
seg000:01EB                                         ; 7: 0=enable kbrd
seg000:01ED                 or      al, 3
seg000:01EF                 out     61h, al         ; PC/XT PPI port B bits:
seg000:01EF                                         ; 0: Tmr 2 gate ═╦═► OR 03H=spkr ON
seg000:01EF                                         ; 1: Tmr 2 data ═╝  AND 0fcH=spkr OFF
seg000:01EF                                         ; 3: 1=read high switches
seg000:01EF                                         ; 4: 0=enable RAM parity checking
seg000:01EF                                         ; 5: 0=enable I/O channel check
seg000:01EF                                         ; 6: 0=hold keyboard clock low
seg000:01EF                                         ; 7: 0=enable kbrd
seg000:01F1                 popa
seg000:01F2                 retn
seg000:01F2 timer           endp
seg000:01F2
seg000:01F3
seg000:01F3 ; =============== S U B R O U T I N E =======================================
seg000:01F3
seg000:01F3
seg000:01F3 sth_with_dev    proc near               ; CODE XREF: handle_left+14↓p
seg000:01F3                                         ; handle_down+17↓p ...
seg000:01F3                 pusha
seg000:01F4                 in      al, 61h         ; PC/XT PPI port B bits:
seg000:01F4                                         ; 0: Tmr 2 gate ═╦═► OR 03H=spkr ON
seg000:01F4                                         ; 1: Tmr 2 data ═╝  AND 0fcH=spkr OFF
seg000:01F4                                         ; 3: 1=read high switches
seg000:01F4                                         ; 4: 0=enable RAM parity checking
seg000:01F4                                         ; 5: 0=enable I/O channel check
seg000:01F4                                         ; 6: 0=hold keyboard clock low
seg000:01F4                                         ; 7: 0=enable kbrd
seg000:01F6                 and     al, 0FCh
seg000:01F8                 out     61h, al         ; PC/XT PPI port B bits:
seg000:01F8                                         ; 0: Tmr 2 gate ═╦═► OR 03H=spkr ON
seg000:01F8                                         ; 1: Tmr 2 data ═╝  AND 0fcH=spkr OFF
seg000:01F8                                         ; 3: 1=read high switches
seg000:01F8                                         ; 4: 0=enable RAM parity checking
seg000:01F8                                         ; 5: 0=enable I/O channel check
seg000:01F8                                         ; 6: 0=hold keyboard clock low
seg000:01F8                                         ; 7: 0=enable kbrd
seg000:01FA                 popa
seg000:01FB                 retn
seg000:01FB sth_with_dev    endp
seg000:01FB
seg000:01FC
seg000:01FC ; =============== S U B R O U T I N E =======================================
seg000:01FC
seg000:01FC
seg000:01FC unknown_call_dynamics proc near         ; CODE XREF: game+76↓p
seg000:01FC                                         ; game+A2↓p
seg000:01FC                 call    call_dynamics1
seg000:01FF                 call    get_enhanced_keystroke
seg000:0202                 call    call_dynamics2
seg000:0205                 retn
seg000:0205 unknown_call_dynamics endp
seg000:0205
seg000:0206
seg000:0206 ; =============== S U B R O U T I N E =======================================
seg000:0206
seg000:0206
seg000:0206 call_dynamics1  proc near               ; CODE XREF: unknown_call_dynamics↑p
seg000:0206                                         ; draw_scene+7↓p
seg000:0206                 pusha
seg000:0207                 push    dx
seg000:0208                 push    ax
seg000:0209                 mov     bx, 2
seg000:020C                 mov     dx, seg seg001
seg000:020F                 mov     ax, 0
seg000:0212                 call    call_dynamic_funcs
seg000:0217                 mov     bx, 3
seg000:021A                 call    call_dynamic_funcs
seg000:021F                 mov     bx, 8
seg000:0222                 pop     ax
seg000:0223                 pop     dx
seg000:0224                 call    call_dynamic_funcs
seg000:0229                 mov     bx, 9
seg000:022C                 call    call_dynamic_funcs
seg000:0231                 popa
seg000:0232                 retn
seg000:0232 call_dynamics1  endp
seg000:0232
seg000:0233
seg000:0233 ; =============== S U B R O U T I N E =======================================
seg000:0233
seg000:0233
seg000:0233 call_dynamics2  proc near               ; CODE XREF: unknown_call_dynamics+6↑p
seg000:0233                                         ; init_screen+7A↓p
seg000:0233                 pusha
seg000:0234                 mov     bx, 0Ah
seg000:0237                 call    call_dynamic_funcs
seg000:023C                 mov     bx, 5
seg000:023F                 call    call_dynamic_funcs
seg000:0244                 mov     bx, 4
seg000:0247                 call    call_dynamic_funcs
seg000:024C                 popa
seg000:024D                 retn
seg000:024D call_dynamics2  endp
seg000:024D
seg000:024E
seg000:024E ; =============== S U B R O U T I N E =======================================
seg000:024E
seg000:024E
seg000:024E write_str       proc near               ; CODE XREF: modal+2F↓p
seg000:024E                                         ; modal+40↓p ...
seg000:024E                 pusha
seg000:024F                 mov     ah, 0Eh
seg000:0251
seg000:0251 loc_10251:                              ; CODE XREF: write_str+A↓j
seg000:0251                 lodsb
seg000:0252                 cmp     al, 0
seg000:0254                 jz      short loc_1025A
seg000:0256                 int     10h             ; - VIDEO - WRITE CHARACTER AND ADVANCE CURSOR (TTY WRITE)
seg000:0256                                         ; AL = character, BH = display page (alpha modes)
seg000:0256                                         ; BL = foreground color (graphics modes)
seg000:0258                 jmp     short loc_10251
seg000:025A ; ---------------------------------------------------------------------------
seg000:025A
seg000:025A loc_1025A:                              ; CODE XREF: write_str+6↑j
seg000:025A                 popa
seg000:025B                 retn
seg000:025B write_str       endp
seg000:025B
seg000:025C
seg000:025C ; =============== S U B R O U T I N E =======================================
seg000:025C
seg000:025C
seg000:025C scroll_page_up  proc near               ; CODE XREF: main+22↑p
seg000:025C                                         ; main+2B↑p ...
seg000:025C                 pusha
seg000:025D                 mov     dx, 0
seg000:0260                 call    set_cursor_position
seg000:0263                 mov     ah, 6
seg000:0265                 mov     al, 0
seg000:0267                 mov     bh, 7
seg000:0269                 mov     cx, 0
seg000:026C                 mov     dh, 18h
seg000:026E                 mov     dl, 4Fh ; 'O'
seg000:0270                 int     10h             ; - VIDEO - SCROLL PAGE UP
seg000:0270                                         ; AL = number of lines to scroll window (0 = blank whole window)
seg000:0270                                         ; BH = attributes to be used on blanked lines
seg000:0270                                         ; CH,CL = row,column of upper left corner of window to scroll
seg000:0270                                         ; DH,DL = row,column of lower right corner of window
seg000:0272                 popa
seg000:0273                 retn
seg000:0273 scroll_page_up  endp
seg000:0273
seg000:0274
seg000:0274 ; =============== S U B R O U T I N E =======================================
seg000:0274
seg000:0274
seg000:0274 set_cursor_position proc near           ; CODE XREF: main+30↑p
seg000:0274                                         ; scroll_page_up+4↑p ...
seg000:0274                 pusha
seg000:0275                 mov     bh, 0
seg000:0277                 mov     ah, 2
seg000:0279                 int     10h             ; - VIDEO - SET CURSOR POSITION
seg000:0279                                         ; DH,DL = row, column (0,0 = upper left)
seg000:0279                                         ; BH = page number
seg000:027B                 popa
seg000:027C                 retn
seg000:027C set_cursor_position endp
seg000:027C
seg000:027D
seg000:027D ; =============== S U B R O U T I N E =======================================
seg000:027D
seg000:027D
seg000:027D write_spaces    proc near               ; CODE XREF: modal+60↓p
seg000:027D                                         ; flash_sides+D↓p ...
seg000:027D                 pusha
seg000:027E
seg000:027E loc_1027E:                              ; CODE XREF: write_spaces+17↓j
seg000:027E                 call    set_cursor_position
seg000:0281                 mov     ah, 9
seg000:0283                 mov     bh, 0
seg000:0285                 mov     cx, si
seg000:0287                 mov     al, 20h ; ' '
seg000:0289                 int     10h             ; - VIDEO - WRITE ATTRIBUTES/CHARACTERS AT CURSOR POSITION
seg000:0289                                         ; AL = character, BH = display page
seg000:0289                                         ; BL = attributes of character (alpha modes) or color (graphics modes)
seg000:0289                                         ; CX = number of times to write character
seg000:028B                 inc     dh
seg000:028D                 mov     ax, 0
seg000:0290                 mov     al, dh
seg000:0292                 cmp     ax, di
seg000:0294                 jnz     short loc_1027E
seg000:0296                 popa
seg000:0297                 retn
seg000:0297 write_spaces    endp
seg000:0297
seg000:0298
seg000:0298 ; =============== S U B R O U T I N E =======================================
seg000:0298
seg000:0298
seg000:0298 write_character proc near
seg000:0298                 pusha
seg000:0299                 cmp     ax, 9
seg000:029C                 jle     short loc_102A1
seg000:029E                 add     ax, 7
seg000:02A1
seg000:02A1 loc_102A1:                              ; CODE XREF: write_character+4↑j
seg000:02A1                 add     ax, 30h ; '0'
seg000:02A4                 mov     ah, 0Eh
seg000:02A6                 int     10h             ; - VIDEO - WRITE CHARACTER AND ADVANCE CURSOR (TTY WRITE)
seg000:02A6                                         ; AL = character, BH = display page (alpha modes)
seg000:02A6                                         ; BL = foreground color (graphics modes)
seg000:02A8                 popa
seg000:02A9                 retn
seg000:02A9 write_character endp
seg000:02A9
seg000:02AA
seg000:02AA ; =============== S U B R O U T I N E =======================================
seg000:02AA
seg000:02AA
seg000:02AA modal           proc near               ; CODE XREF: init_screen+74↓p
seg000:02AA                                         ; game+6D↓p ...
seg000:02AA                 pusha
seg000:02AB                 push    dx
seg000:02AC                 mov     dh, 9
seg000:02AE                 mov     dl, 13h
seg000:02B0
seg000:02B0 loc_102B0:                              ; CODE XREF: modal+1F↓j
seg000:02B0                 call    set_cursor_position
seg000:02B3                 pusha
seg000:02B4                 mov     ah, 9
seg000:02B6                 mov     bh, 0
seg000:02B8                 mov     cx, 2Ah ; '*'
seg000:02BB                 mov     bl, 4Fh ; 'O'
seg000:02BD                 mov     al, 20h ; ' '
seg000:02BF                 int     10h             ; - VIDEO - WRITE ATTRIBUTES/CHARACTERS AT CURSOR POSITION
seg000:02BF                                         ; AL = character, BH = display page
seg000:02BF                                         ; BL = attributes of character (alpha modes) or color (graphics modes)
seg000:02BF                                         ; CX = number of times to write character
seg000:02C1                 popa
seg000:02C2                 inc     dh
seg000:02C4                 cmp     dh, 10h
seg000:02C7                 jz      short loc_102CB
seg000:02C9                 jmp     short loc_102B0
seg000:02CB ; ---------------------------------------------------------------------------
seg000:02CB
seg000:02CB loc_102CB:                              ; CODE XREF: modal+1D↑j
seg000:02CB                 cmp     ax, 0
seg000:02CE                 jz      short loc_102DC
seg000:02D0                 mov     dl, 14h
seg000:02D2                 mov     dh, 0Ah
seg000:02D4                 call    set_cursor_position
seg000:02D7                 mov     si, ax
seg000:02D9                 call    write_str
seg000:02DC
seg000:02DC loc_102DC:                              ; CODE XREF: modal+24↑j
seg000:02DC                 cmp     bx, 0
seg000:02DF                 jz      short loc_102ED
seg000:02E1                 mov     dl, 14h
seg000:02E3                 mov     dh, 0Bh
seg000:02E5                 call    set_cursor_position
seg000:02E8                 mov     si, bx
seg000:02EA                 call    write_str
seg000:02ED
seg000:02ED loc_102ED:                              ; CODE XREF: modal+35↑j
seg000:02ED                 cmp     cx, 0
seg000:02F0                 jz      short loc_102FE
seg000:02F2                 mov     dl, 14h
seg000:02F4                 mov     dh, 0Ch
seg000:02F6                 call    set_cursor_position
seg000:02F9                 mov     si, cx
seg000:02FB                 call    write_str
seg000:02FE
seg000:02FE loc_102FE:                              ; CODE XREF: modal+46↑j
seg000:02FE                 mov     bl, 0F0h
seg000:0300                 mov     dh, 0Eh
seg000:0302                 mov     dl, 23h ; '#'
seg000:0304                 mov     si, 8
seg000:0307                 mov     di, 0Fh
seg000:030A                 call    write_spaces
seg000:030D                 mov     dl, 26h ; '&'
seg000:030F                 mov     dh, 0Eh
seg000:0311                 call    set_cursor_position
seg000:0314                 mov     si, 328h
seg000:0317                 call    write_str
seg000:031A                 pop     dx
seg000:031B                 test    dx, dx
seg000:031D                 jnz     short loc_10326
seg000:031F
seg000:031F loc_1031F:                              ; CODE XREF: modal+7A↓j
seg000:031F                 call    get_enhanced_keystroke
seg000:0322                 cmp     al, 0Dh
seg000:0324                 jnz     short loc_1031F
seg000:0326
seg000:0326 loc_10326:                              ; CODE XREF: modal+73↑j
seg000:0326                 popa
seg000:0327                 retn
seg000:0327 modal           endp
seg000:0327
seg000:0327 ; ---------------------------------------------------------------------------
seg000:0328                 db 4Fh, 4Bh, 3 dup(0)
seg000:032D
seg000:032D ; =============== S U B R O U T I N E =======================================
seg000:032D
seg000:032D
seg000:032D decode_str      proc near               ; CODE XREF: init_screen+12↓p
seg000:032D                                         ; init_screen+20↓p ...
seg000:032D                 pusha
seg000:032E                 cmp     cx, bx
seg000:0330                 jz      short loc_10340
seg000:0332
seg000:0332 loc_10332:                              ; CODE XREF: decode_str+11↓j
seg000:0332                 cmp     byte ptr [si], 0
seg000:0335                 jz      short loc_1033D
seg000:0337                 cmp     [si], dl
seg000:0339                 jz      short loc_1033D
seg000:033B                 xor     [si], dl
seg000:033D
seg000:033D loc_1033D:                              ; CODE XREF: decode_str+8↑j
seg000:033D                                         ; decode_str+C↑j
seg000:033D                 inc     si
seg000:033E                 loop    loc_10332
seg000:0340
seg000:0340 loc_10340:                              ; CODE XREF: decode_str+3↑j
seg000:0340                 popa
seg000:0341                 retn
seg000:0341 decode_str      endp
seg000:0341
seg000:0342
seg000:0342 ; =============== S U B R O U T I N E =======================================
seg000:0342
seg000:0342
seg000:0342 itoa            proc near               ; CODE XREF: print_hud+11↓p
seg000:0342                                         ; print_hud+29↓p
seg000:0342                 pusha
seg000:0343                 mov     cx, 0
seg000:0346                 mov     bx, 0Ah
seg000:0349                 mov     di, 369h
seg000:034C
seg000:034C loc_1034C:                              ; CODE XREF: itoa+13↓j
seg000:034C                 mov     dx, 0
seg000:034F                 div     bx
seg000:0351                 inc     cx
seg000:0352                 push    dx
seg000:0353                 test    ax, ax
seg000:0355                 jnz     short loc_1034C
seg000:0357
seg000:0357 loc_10357:                              ; CODE XREF: itoa+1D↓j
seg000:0357                 pop     dx
seg000:0358                 add     dl, 30h ; '0'
seg000:035B                 mov     [di], dl
seg000:035D                 inc     di
seg000:035E                 dec     cx
seg000:035F                 jnz     short loc_10357
seg000:0361                 mov     byte ptr [di], 0
seg000:0364                 popa
seg000:0365                 mov     ax, 369h
seg000:0368                 retn
seg000:0368 itoa            endp ; sp-analysis failed
seg000:0368
seg000:0368 ; ---------------------------------------------------------------------------
seg000:0369                 align 8
seg000:0370
seg000:0370 ; =============== S U B R O U T I N E =======================================
seg000:0370
seg000:0370
seg000:0370 init_screen     proc near               ; CODE XREF: game+1↓p
seg000:0370                 pusha
seg000:0371                 mov     word ptr unk_10967, 2
seg000:0377                 mov     si, 0A00h
seg000:037A                 mov     cx, word_10A0D
seg000:037E                 mov     dx, word_10A0B
seg000:0382                 call    decode_str
seg000:0385                 mov     si, 0A0Fh
seg000:0388                 mov     cx, word_10A1B
seg000:038C                 mov     dx, word_10A19
seg000:0390                 call    decode_str
seg000:0393                 mov     si, 0A3Dh
seg000:0396                 mov     cx, word_10A67
seg000:039A                 mov     dx, word_10A65
seg000:039E                 call    decode_str
seg000:03A1                 mov     si, 0A69h
seg000:03A4                 mov     cx, word_10A94
seg000:03A8                 mov     dx, word_10A92
seg000:03AC                 call    decode_str
seg000:03AF                 mov     si, 0A96h
seg000:03B2                 mov     cx, word_10AC1
seg000:03B6                 mov     dx, word_10ABF
seg000:03BA                 call    decode_str
seg000:03BD                 mov     si, 0ACFh
seg000:03C0                 mov     cx, word_10AD7
seg000:03C4                 mov     dx, word_10AD9
seg000:03C8                 call    decode_str
seg000:03CB                 mov     si, 0AC3h
seg000:03CE                 mov     cx, word_10ACB
seg000:03D2                 mov     dx, word_10ACD
seg000:03D6                 call    decode_str
seg000:03D9                 mov     ax, 0A3Dh
seg000:03DC                 mov     bx, 0A69h
seg000:03DF                 mov     cx, 0A96h
seg000:03E2                 xor     dx, dx
seg000:03E4                 call    modal
seg000:03E7                 call    draw_initial
seg000:03EA                 call    call_dynamics2
seg000:03ED                 popa
seg000:03EE                 retn
seg000:03EE init_screen     endp
seg000:03EE
seg000:03EF
seg000:03EF ; =============== S U B R O U T I N E =======================================
seg000:03EF
seg000:03EF
seg000:03EF draw_initial    proc near               ; CODE XREF: init_screen+77↑p
seg000:03EF                 pusha
seg000:03F0                 call    scroll_page_up
seg000:03F3                 call    paint_left
seg000:03F6                 call    paint_up
seg000:03F9                 call    paint_right
seg000:03FC                 call    paint_down
seg000:03FF                 call    print_hud
seg000:0402                 mov     dh, 0Ch
seg000:0404                 mov     dl, 23h ; '#'
seg000:0406                 call    set_cursor_position
seg000:0409                 mov     si, 0A00h
seg000:040C                 call    write_str
seg000:040F                 popa
seg000:0410                 retn
seg000:0410 draw_initial    endp
seg000:0410
seg000:0411
seg000:0411 ; =============== S U B R O U T I N E =======================================
seg000:0411
seg000:0411
seg000:0411 game            proc near               ; CODE XREF: main+28↑p
seg000:0411                 pusha
seg000:0412                 call    init_screen
seg000:0415
seg000:0415 start_game:                             ; CODE XREF: game+1B↓j
seg000:0415                                         ; game+25↓j
seg000:0415                 call    _10th_level_check
seg000:0418                 call    print_hud
seg000:041B                 call    get_sequence
seg000:041E                 nop                     ; Keypatch modified this from:
seg000:041E                                         ;   call play_sequence
seg000:041E                                         ; Keypatch padded NOP to next boundary: 2 bytes
seg000:041F                 nop
seg000:0420                 nop
seg000:0421                 call    round_result
seg000:0424                 cmp     ax, 0
seg000:0427                 jz      short fail
seg000:0429                 cmp     ax, 2
seg000:042C                 jz      short start_game
seg000:042E                 inc     level
seg000:0432                 dec     expected_levels
seg000:0436                 jnz     short start_game
seg000:0438                 dec     level
seg000:043C                 call    scroll_page_up
seg000:043F                 call    print_hud
seg000:0442                 mov     dx, 96Fh        ; your_input
seg000:0445                 call    open_read_write_self
seg000:0448                 mov     si, 4B8h
seg000:044B                 mov     cx, word_104D7
seg000:044F                 mov     dx, word_104D5
seg000:0453                 call    decode_str
seg000:0456                 mov     si, 4D9h
seg000:0459                 mov     cx, word_104FB
seg000:045D                 mov     dx, word_104F9
seg000:0461                 call    decode_str
seg000:0464                 mov     si, 4FDh
seg000:0467                 mov     cx, word_10518
seg000:046B                 mov     dx, word_10516
seg000:046F                 call    decode_str
seg000:0472                 mov     ax, 4B8h
seg000:0475                 mov     bx, 4D9h
seg000:0478                 mov     cx, 4FDh
seg000:047B                 xor     dx, dx
seg000:047D                 inc     dx
seg000:047E                 call    modal
seg000:0481                 mov     dx, seg seg004
seg000:0484                 mov     ax, 0
seg000:0487                 call    unknown_call_dynamics
seg000:048A                 popa
seg000:048B                 retn
seg000:048C ; ---------------------------------------------------------------------------
seg000:048C
seg000:048C fail:                                   ; CODE XREF: game+16↑j
seg000:048C                 call    scroll_page_up
seg000:048F                 call    print_hud
seg000:0492                 mov     si, 0A1Dh
seg000:0495                 mov     cx, word_10A3B
seg000:0499                 mov     dx, never_give_up
seg000:049D                 call    decode_str
seg000:04A0                 xor     ax, ax
seg000:04A2                 mov     bx, 0A1Dh
seg000:04A5                 xor     cx, cx
seg000:04A7                 xor     dx, dx
seg000:04A9                 inc     dx
seg000:04AA                 call    modal
seg000:04AD                 mov     dx, seg seg003
seg000:04B0                 mov     ax, 0
seg000:04B3                 call    unknown_call_dynamics
seg000:04B6                 popa
seg000:04B7                 retn
seg000:04B7 game            endp
seg000:04B7
seg000:04B7 ; ---------------------------------------------------------------------------
seg000:04B8                 db 0Ch dup(94h), 0E0h, 0FCh, 0F5h, 0FAh, 0FFh, 94h, 0EDh
seg000:04B8                 db 0FBh, 0E1h, 94h, 0F9h, 0F5h, 0E6h, 0FDh, 0FBh, 95h
seg000:04B8                 db 0
seg000:04D5 word_104D5      dw 0B4h                 ; DATA XREF: game+3E↑r
seg000:04D7 word_104D7      dw 1Dh                  ; DATA XREF: game+3A↑r
seg000:04D9                 db 9 dup(0D1h), 0B3h, 0A4h, 0A5h, 0D1h, 0BEh, 0A4h, 0A3h
seg000:04D9                 db 0D1h, 0A1h, 0A3h, 0B8h, 0BFh, 0B2h, 0B4h, 2 dup(0A2h)
seg000:04D9                 db 0D1h, 0B8h, 0A2h, 0D1h, 0B8h, 0BFh, 0
seg000:04F9 word_104F9      dw 0F1h                 ; DATA XREF: game+4C↑r
seg000:04FB word_104FB      dw 20h                  ; DATA XREF: game+48↑r
seg000:04FD                 db 9 dup(86h), 0E7h, 0E8h, 0E9h, 0F2h, 0EEh, 0E3h, 0F4h
seg000:04FD                 db 86h, 0E5h, 0E7h, 0F5h, 0F2h, 0EAh, 0E3h, 87h, 0
seg000:0516 word_10516      dw 0A6h                 ; DATA XREF: game+5A↑r
seg000:0518 word_10518      dw 19h                  ; DATA XREF: game+56↑r
seg000:051A
seg000:051A ; =============== S U B R O U T I N E =======================================
seg000:051A
seg000:051A
seg000:051A open_read_write_self proc near          ; CODE XREF: game+34↑p
seg000:051A                 pusha
seg000:051B                 mov     data_to_write, dx
seg000:051F                 mov     si, 5AEh
seg000:0522                 mov     cx, ccccccccccc
seg000:0526                 mov     dx, word_105BE
seg000:052A                 call    decode_str
seg000:052D                 mov     si, 5C2h
seg000:0530                 mov     cx, flaresay_exe_str
seg000:0534                 mov     dx, word_105CF
seg000:0538                 call    decode_str
seg000:053B                 mov     al, 2
seg000:053D                 mov     dx, 5C2h
seg000:0540                 mov     ah, 3Dh
seg000:0542                 int     21h             ; DOS - 2+ - OPEN DISK FILE WITH HANDLE
seg000:0542                                         ; DS:DX -> ASCIZ filename
seg000:0542                                         ; AL = access mode
seg000:0542                                         ; 2 - read & write
seg000:0544                 jb      short exit
seg000:0546                 mov     file_handle, ax
seg000:0549
seg000:0549 read_next_0x10_bytes:                   ; CODE XREF: open_read_write_self+4C↓j
seg000:0549                 mov     bx, file_handle
seg000:054D                 mov     cx, 10h
seg000:0550                 lea     dx, buffer
seg000:0554                 mov     ah, 3Fh
seg000:0556                 int     21h             ; DOS - 2+ - READ FROM FILE WITH HANDLE
seg000:0556                                         ; BX = file handle, CX = number of bytes to read
seg000:0556                                         ; DS:DX -> buffer
seg000:0558                 jb      short exit
seg000:055A                 lea     si, expected
seg000:055E                 mov     di, dx
seg000:0560                 mov     cx, 10h
seg000:0563                 cld
seg000:0564                 repe cmpsb
seg000:0566                 jnz     short read_next_0x10_bytes
seg000:0568                 mov     bx, file_handle
seg000:056C                 xor     cx, cx
seg000:056E                 mov     dx, 5
seg000:0571                 mov     al, 1
seg000:0573                 mov     ah, 42h
seg000:0575                 int     21h             ; DOS - 2+ - MOVE FILE READ/WRITE POINTER (LSEEK)
seg000:0575                                         ; AL = method: offset from present location
seg000:0577                 jb      short exit
seg000:0579                 mov     bx, file_handle
seg000:057D                 mov     cx, 10h
seg000:0580                 mov     dx, data_to_write
seg000:0584                 mov     ah, 40h
seg000:0586                 int     21h             ; DOS - 2+ - WRITE TO FILE WITH HANDLE
seg000:0586                                         ; BX = file handle, CX = number of bytes to write, DS:DX -> buffer
seg000:0588                 jb      short exit
seg000:058A                 cmp     ax, cx
seg000:058C                 jnz     short exit
seg000:058E                 mov     bx, file_handle
seg000:0592                 mov     ah, 3Eh
seg000:0594                 int     21h             ; DOS - 2+ - CLOSE A FILE WITH HANDLE
seg000:0594                                         ; BX = file handle
seg000:0596                 jb      short $+2
seg000:0598
seg000:0598 exit:                                   ; CODE XREF: open_read_write_self+2A↑j
seg000:0598                                         ; open_read_write_self+3E↑j ...
seg000:0598                 popa
seg000:0599                 retn
seg000:0599 open_read_write_self endp
seg000:0599
seg000:0599 ; ---------------------------------------------------------------------------
seg000:059A data_to_write   dw 0                    ; DATA XREF: open_read_write_self+1↑w
seg000:059A                                         ; open_read_write_self+66↑r
seg000:059C buffer          db 10h dup(0)           ; DATA XREF: open_read_write_self+36↑o
seg000:05AC file_handle     dw 0                    ; DATA XREF: open_read_write_self+2C↑w
seg000:05AC                                         ; open_read_write_self:read_next_0x10_bytes↑r ...
seg000:05AE expected        db 10h dup(37h)         ; DATA XREF: open_read_write_self+40↑o
seg000:05BE word_105BE      dw 0FBh                 ; DATA XREF: open_read_write_self+C↑r
seg000:05C0 ccccccccccc     dw 10h                  ; DATA XREF: open_read_write_self+8↑r
seg000:05C2                 db 0A5h, 0AFh, 0A2h, 0B1h, 0A6h, 0B0h, 0A2h, 0BAh, 0EDh
seg000:05C2                 db 0A6h, 0BBh, 0A6h, 0
seg000:05CF word_105CF      dw 0C3h                 ; DATA XREF: open_read_write_self+1A↑r
seg000:05D1 flaresay_exe_str dw 0Dh                 ; DATA XREF: open_read_write_self+16↑r
seg000:05D3
seg000:05D3 ; =============== S U B R O U T I N E =======================================
seg000:05D3
seg000:05D3
seg000:05D3 _10th_level_check proc near             ; CODE XREF: game:start_game↑p
seg000:05D3                 cmp     level, 0Ah
seg000:05D8                 jz      short loc_105DC
seg000:05DA                 jmp     short locret_105E0
seg000:05DC ; ---------------------------------------------------------------------------
seg000:05DC
seg000:05DC loc_105DC:                              ; CODE XREF: _10th_level_check+5↑j
seg000:05DC                 dec     word ptr unk_10967
seg000:05E0
seg000:05E0 locret_105E0:                           ; CODE XREF: _10th_level_check+7↑j
seg000:05E0                 retn
seg000:05E0 _10th_level_check endp
seg000:05E0
seg000:05E1
seg000:05E1 ; =============== S U B R O U T I N E =======================================
seg000:05E1
seg000:05E1
seg000:05E1 round_result    proc near               ; CODE XREF: game+10↑p
seg000:05E1                 pusha
seg000:05E2                 xor     bx, bx
seg000:05E4                 xor     dx, dx
seg000:05E6                 mov     cx, level
seg000:05EA                 mov     collected_points, 0
seg000:05F0
seg000:05F0 get_next:                               ; CODE XREF: round_result+28↓j
seg000:05F0                 mov     dl, [bx+97Fh]
seg000:05F4                 xor     ax, ax          ; Keypatch modified this from:
seg000:05F4                                         ;   call get_enhanced_keystroke
seg000:05F4                                         ; Keypatch padded NOP to next boundary: 2 bytes
seg000:05F4                                         ; Keypatch modified this from:
seg000:05F4                                         ;   nop
seg000:05F4                                         ;   nop
seg000:05F6                 mov     ah, dl          ; Keypatch modified this from:
seg000:05F6                                         ;   nop
seg000:05F6                                         ;   nop
seg000:05F8                 nop
seg000:05F9                 nop
seg000:05FA                 cmp     al, 72h ; 'r'
seg000:05FC                 jz      short replay_seq
seg000:05FE                 cmp     ah, dl
seg000:0600                 jnz     short fail2
seg000:0602                 add     collected_points, dx
seg000:0606                 inc     bx
seg000:0607                 cmp     cx, bx
seg000:0609                 jnz     short get_next
seg000:060B                 mov     dx, collected_points
seg000:060F                 mov     points, dx
seg000:0613                 mov     ax, 96Fh
seg000:0616                 mov     bx, dx
seg000:0618                 call    do_some_operations_on_input
seg000:061B                 push    cx
seg000:061C                 mov     di, 96Fh
seg000:061F                 mov     si, ax
seg000:0621                 mov     cx, 8
seg000:0624                 rep movsw
seg000:0626                 pop     cx
seg000:0627                 popa
seg000:0628                 mov     eax, 1
seg000:062E                 retn
seg000:062F ; ---------------------------------------------------------------------------
seg000:062F
seg000:062F fail2:                                  ; CODE XREF: round_result+1F↑j
seg000:062F                 popa
seg000:0630                 xor     eax, eax
seg000:0633                 retn
seg000:0634 ; ---------------------------------------------------------------------------
seg000:0634
seg000:0634 replay_seq:                             ; CODE XREF: round_result+1B↑j
seg000:0634                 call    replay_seq
seg000:0637                 popa
seg000:0638                 mov     eax, 2
seg000:063E                 retn
seg000:063E round_result    endp
seg000:063E
seg000:063E ; ---------------------------------------------------------------------------
seg000:063F collected_points dw 0                   ; DATA XREF: round_result+9↑w
seg000:063F                                         ; round_result+21↑w ...
seg000:0641
seg000:0641 ; =============== S U B R O U T I N E =======================================
seg000:0641
seg000:0641
seg000:0641 get_sequence    proc near               ; CODE XREF: game+A↑p
seg000:0641                 pusha
seg000:0642                 mov     ax, 0
seg000:0645                 mov     bx, 3
seg000:0648                 call    rand
seg000:064B                 mov     bx, level
seg000:064F                 dec     bx
seg000:0650                 cmp     cx, 0
seg000:0653                 jz      short loc_1066D
seg000:0655                 cmp     cx, 1
seg000:0658                 jz      short loc_10674
seg000:065A                 cmp     cx, 2
seg000:065D                 jz      short loc_10666
seg000:065F                 mov     byte ptr [bx+97Fh], 4Dh ; 'M'
seg000:0664                 jmp     short loc_10679
seg000:0666 ; ---------------------------------------------------------------------------
seg000:0666
seg000:0666 loc_10666:                              ; CODE XREF: get_sequence+1C↑j
seg000:0666                 mov     byte ptr [bx+97Fh], 4Bh ; 'K'
seg000:066B                 jmp     short loc_10679
seg000:066D ; ---------------------------------------------------------------------------
seg000:066D
seg000:066D loc_1066D:                              ; CODE XREF: get_sequence+12↑j
seg000:066D                 mov     byte ptr [bx+97Fh], 48h ; 'H'
seg000:0672                 jmp     short loc_10679
seg000:0674 ; ---------------------------------------------------------------------------
seg000:0674
seg000:0674 loc_10674:                              ; CODE XREF: get_sequence+17↑j
seg000:0674                 mov     byte ptr [bx+97Fh], 50h ; 'P'
seg000:0679
seg000:0679 loc_10679:                              ; CODE XREF: get_sequence+23↑j
seg000:0679                                         ; get_sequence+2A↑j ...
seg000:0679                 popa
seg000:067A                 retn
seg000:067A get_sequence    endp
seg000:067A
seg000:067B
seg000:067B ; =============== S U B R O U T I N E =======================================
seg000:067B
seg000:067B
seg000:067B play_sequence   proc near
seg000:067B                 pusha
seg000:067C                 xor     bx, bx
seg000:067E                 mov     cx, level
seg000:0682
seg000:0682 loc_10682:                              ; CODE XREF: play_sequence+F↓j
seg000:0682                 mov     ah, [bx+97Fh]
seg000:0686                 call    handle_input2
seg000:0689                 inc     bx
seg000:068A                 loop    loc_10682
seg000:068C                 popa
seg000:068D                 retn
seg000:068D play_sequence   endp
seg000:068D
seg000:068E
seg000:068E ; =============== S U B R O U T I N E =======================================
seg000:068E
seg000:068E
seg000:068E replay_seq      proc near               ; CODE XREF: round_result:replay_seq↑p
seg000:068E                 pusha
seg000:068F
seg000:068F loc_1068F:                              ; CODE XREF: replay_seq+B↓j
seg000:068F                 call    get_enhanced_keystroke
seg000:0692                 cmp     al, 72h ; 'r'
seg000:0694                 jz      short loc_1069B
seg000:0696                 call    handle_input2
seg000:0699                 jmp     short loc_1068F
seg000:069B ; ---------------------------------------------------------------------------
seg000:069B
seg000:069B loc_1069B:                              ; CODE XREF: replay_seq+6↑j
seg000:069B                 popa
seg000:069C                 retn
seg000:069C replay_seq      endp
seg000:069C
seg000:069D
seg000:069D ; =============== S U B R O U T I N E =======================================
seg000:069D
seg000:069D
seg000:069D handle_input2   proc near               ; CODE XREF: play_sequence+B↑p
seg000:069D                                         ; replay_seq+8↑p
seg000:069D                 pusha
seg000:069E                 cmp     ah, 48h ; 'H'
seg000:06A1                 jz      short handle_up
seg000:06A3                 cmp     ah, 50h ; 'P'
seg000:06A6                 jz      short handle_down
seg000:06A8                 cmp     ah, 4Bh ; 'K'
seg000:06AB                 jz      short handle_left
seg000:06AD                 cmp     ah, 4Dh ; 'M'
seg000:06B0                 jz      short handle_right
seg000:06B2                 jmp     short loc_106C8
seg000:06B4 ; ---------------------------------------------------------------------------
seg000:06B4
seg000:06B4 handle_up:                              ; CODE XREF: handle_input2+4↑j
seg000:06B4                 call    handle_up
seg000:06B7                 jmp     short loc_106C8
seg000:06B9 ; ---------------------------------------------------------------------------
seg000:06B9
seg000:06B9 handle_down:                            ; CODE XREF: handle_input2+9↑j
seg000:06B9                 call    handle_down
seg000:06BC                 jmp     short loc_106C8
seg000:06BE ; ---------------------------------------------------------------------------
seg000:06BE
seg000:06BE handle_left:                            ; CODE XREF: handle_input2+E↑j
seg000:06BE                 call    handle_left
seg000:06C1                 jmp     short loc_106C8
seg000:06C3 ; ---------------------------------------------------------------------------
seg000:06C3
seg000:06C3 handle_right:                           ; CODE XREF: handle_input2+13↑j
seg000:06C3                 call    handle_right
seg000:06C6                 jmp     short $+2
seg000:06C8 ; ---------------------------------------------------------------------------
seg000:06C8
seg000:06C8 loc_106C8:                              ; CODE XREF: handle_input2+15↑j
seg000:06C8                                         ; handle_input2+1A↑j ...
seg000:06C8                 popa
seg000:06C9                 retn
seg000:06C9 handle_input2   endp
seg000:06C9
seg000:06CA
seg000:06CA ; =============== S U B R O U T I N E =======================================
seg000:06CA
seg000:06CA
seg000:06CA print_hud       proc near               ; CODE XREF: draw_initial+10↑p
seg000:06CA                                         ; game+7↑p ...
seg000:06CA                 pusha
seg000:06CB                 mov     dh, 0
seg000:06CD                 mov     dl, 3Ch ; '<'
seg000:06CF                 call    set_cursor_position
seg000:06D2                 mov     si, 0AC3h
seg000:06D5                 call    write_str
seg000:06D8                 mov     ax, points
seg000:06DB                 call    itoa
seg000:06DE                 mov     si, ax
seg000:06E0                 call    write_str
seg000:06E3                 mov     dh, 1
seg000:06E5                 mov     dl, 3Ch ; '<'
seg000:06E7                 call    set_cursor_position
seg000:06EA                 mov     si, 0ACFh
seg000:06ED                 call    write_str
seg000:06F0                 mov     ax, level
seg000:06F3                 call    itoa
seg000:06F6                 mov     si, ax
seg000:06F8                 call    write_str
seg000:06FB                 popa
seg000:06FC                 retn
seg000:06FC print_hud       endp
seg000:06FC
seg000:06FD
seg000:06FD ; =============== S U B R O U T I N E =======================================
seg000:06FD
seg000:06FD
seg000:06FD delay           proc near               ; CODE XREF: flash+C↓p
seg000:06FD                                         ; flash+14↓p ...
seg000:06FD                 pusha
seg000:06FE                 xor     cx, cx
seg000:0700                 xor     dx, dx
seg000:0702                 xor     ah, ah
seg000:0704                 inc     ah
seg000:0706                 int     1Ah             ; CLOCK - SET TIME OF DAY
seg000:0706                                         ; CX:DX = clock count
seg000:0706                                         ; Return: time of day set
seg000:0708                 mov     ah, 0
seg000:070A                 int     1Ah             ; CLOCK - GET TIME OF DAY
seg000:070A                                         ; Return: CX:DX = clock count
seg000:070A                                         ; AL = 00h if clock was read or written (via AH=0,1) since the previous
seg000:070A                                         ; midnight
seg000:070A                                         ; Otherwise, AL > 0
seg000:070C                 add     bx, dx
seg000:070E
seg000:070E loc_1070E:                              ; CODE XREF: delay+19↓j
seg000:070E                 mov     ah, 0
seg000:0710                 int     1Ah             ; CLOCK - GET TIME OF DAY
seg000:0710                                         ; Return: CX:DX = clock count
seg000:0710                                         ; AL = 00h if clock was read or written (via AH=0,1) since the previous
seg000:0710                                         ; midnight
seg000:0710                                         ; Otherwise, AL > 0
seg000:0712                 sub     dx, bx
seg000:0714                 cmp     bx, dx
seg000:0716                 jg      short loc_1070E
seg000:0718                 popa
seg000:0719                 retn
seg000:0719 delay           endp
seg000:0719
seg000:071A
seg000:071A ; =============== S U B R O U T I N E =======================================
seg000:071A
seg000:071A
seg000:071A flash_sides     proc near               ; CODE XREF: flash+9↓p
seg000:071A                                         ; flash+11↓p
seg000:071A                 pusha
seg000:071B                 mov     bl, al
seg000:071D                 mov     dl, 0
seg000:071F                 mov     dh, 0
seg000:0721                 mov     si, 14h
seg000:0724                 mov     di, 19h
seg000:0727                 call    write_spaces
seg000:072A                 add     dl, 3Ch ; '<'
seg000:072D                 call    write_spaces
seg000:0730                 popa
seg000:0731                 retn
seg000:0731 flash_sides     endp
seg000:0731
seg000:0732
seg000:0732 ; =============== S U B R O U T I N E =======================================
seg000:0732
seg000:0732
seg000:0732 flash           proc near               ; CODE XREF: handle_input_on_first_screen_konami+73↓p
seg000:0732                 pusha
seg000:0733                 mov     cx, 2
seg000:0736                 mov     bx, 1
seg000:0739
seg000:0739 loc_10739:                              ; CODE XREF: flash+17↓j
seg000:0739                 mov     al, 0FFh
seg000:073B                 call    flash_sides
seg000:073E                 call    delay
seg000:0741                 mov     al, 0Fh
seg000:0743                 call    flash_sides
seg000:0746                 call    delay
seg000:0749                 loop    loc_10739
seg000:074B                 popa
seg000:074C                 retn
seg000:074C flash           endp
seg000:074C
seg000:074D
seg000:074D ; =============== S U B R O U T I N E =======================================
seg000:074D
seg000:074D
seg000:074D paint_up        proc near               ; CODE XREF: draw_initial+7↑p
seg000:074D                                         ; handle_up+14↓p
seg000:074D                 pusha
seg000:074E                 mov     bl, 4Fh ; 'O'
seg000:0750                 mov     dl, 1Eh
seg000:0752                 mov     dh, 2
seg000:0754                 mov     si, 14h
seg000:0757                 mov     di, 8
seg000:075A                 call    write_spaces
seg000:075D                 popa
seg000:075E                 retn
seg000:075E paint_up        endp
seg000:075E
seg000:075F
seg000:075F ; =============== S U B R O U T I N E =======================================
seg000:075F
seg000:075F
seg000:075F blink_up        proc near               ; CODE XREF: handle_up+E↓p
seg000:075F                 pusha
seg000:0760                 mov     bl, 0CFh
seg000:0762                 mov     dl, 1Eh
seg000:0764                 mov     dh, 2
seg000:0766                 mov     si, 14h
seg000:0769                 mov     di, 8
seg000:076C                 call    write_spaces
seg000:076F                 popa
seg000:0770                 retn
seg000:0770 blink_up        endp
seg000:0770
seg000:0771
seg000:0771 ; =============== S U B R O U T I N E =======================================
seg000:0771
seg000:0771
seg000:0771 paint_down      proc near               ; CODE XREF: draw_initial+D↑p
seg000:0771                                         ; handle_down+14↓p
seg000:0771                 pusha
seg000:0772                 mov     bl, 2Fh ; '/'
seg000:0774                 mov     dl, 1Eh
seg000:0776                 mov     dh, 11h
seg000:0778                 mov     si, 14h
seg000:077B                 mov     di, 17h
seg000:077E                 call    write_spaces
seg000:0781                 popa
seg000:0782                 retn
seg000:0782 paint_down      endp
seg000:0782
seg000:0783
seg000:0783 ; =============== S U B R O U T I N E =======================================
seg000:0783
seg000:0783
seg000:0783 blink_down      proc near               ; CODE XREF: handle_down+E↓p
seg000:0783                 pusha
seg000:0784                 mov     bl, 0AFh
seg000:0786                 mov     dl, 1Eh
seg000:0788                 mov     dh, 11h
seg000:078A                 mov     si, 14h
seg000:078D                 mov     di, 17h
seg000:0790                 call    write_spaces
seg000:0793                 popa
seg000:0794                 retn
seg000:0794 blink_down      endp
seg000:0794
seg000:0795
seg000:0795 ; =============== S U B R O U T I N E =======================================
seg000:0795
seg000:0795
seg000:0795 paint_left      proc near               ; CODE XREF: draw_initial+4↑p
seg000:0795                                         ; handle_left+11↓p
seg000:0795                 pusha
seg000:0796                 mov     bl, 0EFh
seg000:0798                 mov     dl, 4
seg000:079A                 mov     dh, 9
seg000:079C                 mov     si, 14h
seg000:079F                 mov     di, 10h
seg000:07A2                 call    write_spaces
seg000:07A5                 popa
seg000:07A6                 retn
seg000:07A6 paint_left      endp
seg000:07A6
seg000:07A7
seg000:07A7 ; =============== S U B R O U T I N E =======================================
seg000:07A7
seg000:07A7
seg000:07A7 blink_left      proc near               ; CODE XREF: handle_left+B↓p
seg000:07A7                 pusha
seg000:07A8                 mov     bl, 6Fh ; 'o'
seg000:07AA                 mov     dl, 4
seg000:07AC                 mov     dh, 9
seg000:07AE                 mov     si, 14h
seg000:07B1                 mov     di, 10h
seg000:07B4                 call    write_spaces
seg000:07B7                 popa
seg000:07B8                 retn
seg000:07B8 blink_left      endp
seg000:07B8
seg000:07B9
seg000:07B9 ; =============== S U B R O U T I N E =======================================
seg000:07B9
seg000:07B9
seg000:07B9 paint_right     proc near               ; CODE XREF: draw_initial+A↑p
seg000:07B9                                         ; handle_right+14↓p
seg000:07B9                 pusha
seg000:07BA                 mov     bl, 1Fh
seg000:07BC                 mov     dl, 38h ; '8'
seg000:07BE                 mov     dh, 9
seg000:07C0                 mov     si, 14h
seg000:07C3                 mov     di, 10h
seg000:07C6                 call    write_spaces
seg000:07C9                 popa
seg000:07CA                 retn
seg000:07CA paint_right     endp
seg000:07CA
seg000:07CB
seg000:07CB ; =============== S U B R O U T I N E =======================================
seg000:07CB
seg000:07CB
seg000:07CB blink_right     proc near               ; CODE XREF: handle_right+E↓p
seg000:07CB                 pusha
seg000:07CC                 mov     bl, 9Fh
seg000:07CE                 mov     dl, 38h ; '8'
seg000:07D0                 mov     dh, 9
seg000:07D2                 mov     si, 14h
seg000:07D5                 mov     di, 10h
seg000:07D8                 call    write_spaces
seg000:07DB                 popa
seg000:07DC                 retn
seg000:07DC blink_right     endp
seg000:07DC
seg000:07DD
seg000:07DD ; =============== S U B R O U T I N E =======================================
seg000:07DD
seg000:07DD
seg000:07DD handle_left     proc near               ; CODE XREF: handle_input2:handle_left↑p
seg000:07DD                 pusha
seg000:07DE                 mov     bx, word ptr unk_10967
seg000:07E2                 mov     ax, 76Ch
seg000:07E5                 call    timer
seg000:07E8                 call    blink_left
seg000:07EB                 call    delay
seg000:07EE                 call    paint_left
seg000:07F1                 call    sth_with_dev
seg000:07F4                 call    delay
seg000:07F7                 popa
seg000:07F8                 retn
seg000:07F8 handle_left     endp
seg000:07F8
seg000:07F9
seg000:07F9 ; =============== S U B R O U T I N E =======================================
seg000:07F9
seg000:07F9
seg000:07F9 handle_down     proc near               ; CODE XREF: handle_input2:handle_down↑p
seg000:07F9                 pusha
seg000:07FA                 mov     bx, word ptr unk_10967
seg000:07FE                 call    delay
seg000:0801                 mov     ax, 7D0h
seg000:0804                 call    timer
seg000:0807                 call    blink_down
seg000:080A                 call    delay
seg000:080D                 call    paint_down
seg000:0810                 call    sth_with_dev
seg000:0813                 call    delay
seg000:0816                 popa
seg000:0817                 retn
seg000:0817 handle_down     endp
seg000:0817
seg000:0818
seg000:0818 ; =============== S U B R O U T I N E =======================================
seg000:0818
seg000:0818
seg000:0818 handle_right    proc near               ; CODE XREF: handle_input2:handle_right↑p
seg000:0818                 pusha
seg000:0819                 mov     bx, word ptr unk_10967
seg000:081D                 call    delay
seg000:0820                 mov     ax, 708h
seg000:0823                 call    timer
seg000:0826                 call    blink_right
seg000:0829                 call    delay
seg000:082C                 call    paint_right
seg000:082F                 call    sth_with_dev
seg000:0832                 call    delay
seg000:0835                 popa
seg000:0836                 retn
seg000:0836 handle_right    endp
seg000:0836
seg000:0837
seg000:0837 ; =============== S U B R O U T I N E =======================================
seg000:0837
seg000:0837
seg000:0837 handle_up       proc near               ; CODE XREF: handle_input2:handle_up↑p
seg000:0837                 pusha
seg000:0838                 mov     bx, word ptr unk_10967
seg000:083C                 call    delay
seg000:083F                 mov     ax, 6A4h
seg000:0842                 call    timer
seg000:0845                 call    blink_up
seg000:0848                 call    delay
seg000:084B                 call    paint_up
seg000:084E                 call    sth_with_dev
seg000:0851                 call    delay
seg000:0854                 popa
seg000:0855                 retn
seg000:0855 handle_up       endp
seg000:0855
seg000:0856
seg000:0856 ; =============== S U B R O U T I N E =======================================
seg000:0856
seg000:0856
seg000:0856 print_logo      proc near               ; CODE XREF: draw_scene+D↓p
seg000:0856                 pusha
seg000:0857                 mov     si, 0ADBh
seg000:085A                 mov     dx, 14h
seg000:085D                 mov     cx, 19h
seg000:0860
seg000:0860 loc_10860:                              ; CODE XREF: print_logo+15↓j
seg000:0860                 call    set_cursor_position
seg000:0863                 call    write_str
seg000:0866                 add     si, 29h ; ')'
seg000:0869                 inc     dh
seg000:086B                 loop    loc_10860
seg000:086D                 popa
seg000:086E                 retn
seg000:086E print_logo      endp
seg000:086E
seg000:086F
seg000:086F ; =============== S U B R O U T I N E =======================================
seg000:086F
seg000:086F
seg000:086F print_four_blocks proc near             ; CODE XREF: draw_scene+A↓p
seg000:086F                 pusha
seg000:0870                 mov     bl, 90h
seg000:0872                 mov     dl, 14h
seg000:0874                 mov     dh, 0
seg000:0876                 mov     si, 14h
seg000:0879                 mov     di, 0Dh
seg000:087C                 call    write_spaces
seg000:087F                 mov     bl, 0A0h
seg000:0881                 mov     dl, 28h ; '('
seg000:0883                 mov     dh, 0
seg000:0885                 mov     si, 14h
seg000:0888                 mov     di, 0Dh
seg000:088B                 call    write_spaces
seg000:088E                 mov     bl, 40h ; '@'
seg000:0890                 mov     dl, 14h
seg000:0892                 mov     dh, 0Dh
seg000:0894                 mov     si, 14h
seg000:0897                 mov     di, 19h
seg000:089A                 call    write_spaces
seg000:089D                 mov     bl, 0E0h
seg000:089F                 mov     dl, 28h ; '('
seg000:08A1                 mov     dh, 0Dh
seg000:08A3                 mov     si, 14h
seg000:08A6                 mov     di, 19h
seg000:08A9                 call    write_spaces
seg000:08AC                 popa
seg000:08AD                 retn
seg000:08AD print_four_blocks endp
seg000:08AD
seg000:08AE
seg000:08AE ; =============== S U B R O U T I N E =======================================
seg000:08AE
seg000:08AE
seg000:08AE draw_scene      proc near               ; CODE XREF: main+25↑p
seg000:08AE                 pusha
seg000:08AF                 mov     dx, seg seg005
seg000:08B2                 mov     ax, 0
seg000:08B5                 call    call_dynamics1
seg000:08B8                 call    print_four_blocks
seg000:08BB                 call    print_logo
seg000:08BE                 call    handle_input_on_first_screen_konami
seg000:08C1                 popa
seg000:08C2                 retn
seg000:08C2 draw_scene      endp
seg000:08C2
seg000:08C3
seg000:08C3 ; =============== S U B R O U T I N E =======================================
seg000:08C3
seg000:08C3
seg000:08C3 handle_input_on_first_screen_konami proc near
seg000:08C3                                         ; CODE XREF: draw_scene+10↑p
seg000:08C3                 pusha
seg000:08C4                 mov     di, 953h
seg000:08C7                 xor     cx, cx
seg000:08C9                 mov     al, 0
seg000:08CB                 out     70h, al         ; CMOS Memory/RTC Index Register:
seg000:08CB                                         ; RTC Seconds
seg000:08CD                 in      al, 71h         ; CMOS Memory/RTC Data Register
seg000:08CF                 mov     start_time, al
seg000:08D2
seg000:08D2 loc_108D2:                              ; CODE XREF: handle_input_on_first_screen_konami+51↓j
seg000:08D2                 call    read_char
seg000:08D5                 jz      short loc_10908
seg000:08D7                 cmp     al, 0Dh
seg000:08D9                 jz      short enter_pressed
seg000:08DB                 sub     al, 20h ; ' '
seg000:08DD                 cmp     al, 41h ; 'A'
seg000:08DF                 jz      short ab
seg000:08E1                 cmp     al, 42h ; 'B'
seg000:08E3                 jz      short ab
seg000:08E5                 cmp     ah, 48h ; 'H'
seg000:08E8                 jz      short arrow_pressed
seg000:08EA                 cmp     ah, 50h ; 'P'
seg000:08ED                 jz      short arrow_pressed
seg000:08EF                 cmp     ah, 4Bh ; 'K'
seg000:08F2                 jz      short arrow_pressed
seg000:08F4                 cmp     ah, 4Dh ; 'M'
seg000:08F7                 jz      short arrow_pressed
seg000:08F9                 jmp     short loc_10908
seg000:08FB ; ---------------------------------------------------------------------------
seg000:08FB
seg000:08FB ab:                                     ; CODE XREF: handle_input_on_first_screen_konami+1C↑j
seg000:08FB                                         ; handle_input_on_first_screen_konami+20↑j
seg000:08FB                 mov     [di], al
seg000:08FD                 jmp     short loc_10901
seg000:08FF ; ---------------------------------------------------------------------------
seg000:08FF
seg000:08FF arrow_pressed:                          ; CODE XREF: handle_input_on_first_screen_konami+25↑j
seg000:08FF                                         ; handle_input_on_first_screen_konami+2A↑j ...
seg000:08FF                 mov     [di], ah
seg000:0901
seg000:0901 loc_10901:                              ; CODE XREF: handle_input_on_first_screen_konami+3A↑j
seg000:0901                 inc     di
seg000:0902                 inc     cx
seg000:0903                 cmp     cx, 0Bh
seg000:0906                 jz      short enter_pressed
seg000:0908
seg000:0908 loc_10908:                              ; CODE XREF: handle_input_on_first_screen_konami+12↑j
seg000:0908                                         ; handle_input_on_first_screen_konami+36↑j
seg000:0908                 mov     al, 0
seg000:090A                 out     70h, al         ; CMOS Memory/RTC Index Register:
seg000:090A                                         ; RTC Seconds
seg000:090C                 in      al, 71h         ; CMOS Memory/RTC Data Register
seg000:090E                 sub     al, start_time
seg000:0912                 cmp     al, 0Ah
seg000:0914                 jl      short loc_108D2
seg000:0916
seg000:0916 enter_pressed:                          ; CODE XREF: handle_input_on_first_screen_konami+16↑j
seg000:0916                                         ; handle_input_on_first_screen_konami+43↑j
seg000:0916                 mov     cx, 0Ah
seg000:0919                 mov     si, 953h
seg000:091C                 mov     di, 95Dh
seg000:091F                 cld
seg000:0920                 repe cmpsb
seg000:0922                 jnz     short code_not_ok
seg000:0924                 mov     cx, 5
seg000:0927                 mov     si, 953h
seg000:092A                 xor     ax, ax
seg000:092C
seg000:092C validate_code:                          ; CODE XREF: handle_input_on_first_screen_konami+71↓j
seg000:092C                 mov     bx, [si]
seg000:092E                 shr     bx, 5
seg000:0931                 add     ax, bx
seg000:0933                 inc     si
seg000:0934                 loop    validate_code
seg000:0936                 call    flash
seg000:0939                 jmp     short loc_1094D
seg000:093B ; ---------------------------------------------------------------------------
seg000:093B
seg000:093B code_not_ok:                            ; CODE XREF: handle_input_on_first_screen_konami+5F↑j
seg000:093B                 xor     bx, bx
seg000:093D                 mov     al, 2
seg000:093F                 out     70h, al         ; CMOS Memory/RTC Index Register:
seg000:093F                                         ; RTC Minutes
seg000:0941                 in      al, 71h         ; CMOS Memory/RTC Data Register
seg000:0943                 mov     bl, al
seg000:0945                 mov     al, 0
seg000:0947                 out     70h, al         ; CMOS Memory/RTC Index Register:
seg000:0947                                         ; RTC Seconds
seg000:0949                 in      al, 71h         ; CMOS Memory/RTC Data Register
seg000:094B                 mov     ah, bl
seg000:094D
seg000:094D loc_1094D:                              ; CODE XREF: handle_input_on_first_screen_konami+76↑j
seg000:094D                 call    srand
seg000:0950                 popa
seg000:0951                 retn
seg000:0951 handle_input_on_first_screen_konami endp
seg000:0951
seg000:0951 ; ---------------------------------------------------------------------------
seg000:0952 start_time      db 0                    ; DATA XREF: handle_input_on_first_screen_konami+C↑w
seg000:0952                                         ; handle_input_on_first_screen_konami+4B↑r
seg000:0953                 db    0
seg000:0954                 db    0
seg000:0955                 db    0
seg000:0956                 db    0
seg000:0957                 db    0
seg000:0958                 db    0
seg000:0959                 db    0
seg000:095A                 db    0
seg000:095B                 db    0
seg000:095C                 db    0
seg000:095D                 db  48h ; H
seg000:095E                 db  48h ; H
seg000:095F                 db  50h ; P
seg000:0960                 db  50h ; P
seg000:0961                 db  4Bh ; K
seg000:0962                 db  4Dh ; M
seg000:0963                 db  4Bh ; K
seg000:0964                 db  4Dh ; M
seg000:0965                 db  42h ; B
seg000:0966                 db  41h ; A
seg000:0967 unk_10967       db    0                 ; DATA XREF: init_screen+1↑w
seg000:0967                                         ; _10th_level_check:loc_105DC↑w ...
seg000:0968                 db    0
seg000:0969 level           dw 1                    ; DATA XREF: game+1D↑w
seg000:0969                                         ; game+27↑w ...
seg000:096B expected_levels dw 80h                  ; DATA XREF: game+21↑w
seg000:096D points          dw 0                    ; DATA XREF: round_result+2E↑w
seg000:096D                                         ; print_hud+E↑r
seg000:096F guess           db 0
seg000:0970                 db    0
seg000:0971                 db    0
seg000:0972                 db    0
seg000:0973                 db    0
seg000:0974                 db    0
seg000:0975                 db    0
seg000:0976                 db    0
seg000:0977                 db    0
seg000:0978                 db    0
seg000:0979                 db    0
seg000:097A                 db    0
seg000:097B                 db    0
seg000:097C                 db    0
seg000:097D                 db    0
seg000:097E                 db    0
seg000:097F                 db    0
seg000:0980                 db    0
seg000:0981                 db    0
seg000:0982                 db    0
seg000:0983                 db    0
seg000:0984                 db    0
seg000:0985                 db    0
seg000:0986                 db    0
seg000:0987                 db    0
seg000:0988                 db    0
seg000:0989                 db    0
seg000:098A                 db    0
seg000:098B                 db    0
seg000:098C                 db    0
seg000:098D                 db    0
seg000:098E                 db    0
seg000:098F                 db    0
seg000:0990                 db    0
seg000:0991                 db    0
seg000:0992                 db    0
seg000:0993                 db    0
seg000:0994                 db    0
seg000:0995                 db    0
seg000:0996                 db    0
seg000:0997                 db    0
seg000:0998                 db    0
seg000:0999                 db    0
seg000:099A                 db    0
seg000:099B                 db    0
seg000:099C                 db    0
seg000:099D                 db    0
seg000:099E                 db    0
seg000:099F                 db    0
seg000:09A0                 db    0
seg000:09A1                 db    0
seg000:09A2                 db    0
seg000:09A3                 db    0
seg000:09A4                 db    0
seg000:09A5                 db    0
seg000:09A6                 db    0
seg000:09A7                 db    0
seg000:09A8                 db    0
seg000:09A9                 db    0
seg000:09AA                 db    0
seg000:09AB                 db    0
seg000:09AC                 db    0
seg000:09AD                 db    0
seg000:09AE                 db    0
seg000:09AF                 db    0
seg000:09B0                 db    0
seg000:09B1                 db    0
seg000:09B2                 db    0
seg000:09B3                 db    0
seg000:09B4                 db    0
seg000:09B5                 db    0
seg000:09B6                 db    0
seg000:09B7                 db    0
seg000:09B8                 db    0
seg000:09B9                 db    0
seg000:09BA                 db    0
seg000:09BB                 db    0
seg000:09BC                 db    0
seg000:09BD                 db    0
seg000:09BE                 db    0
seg000:09BF                 db    0
seg000:09C0                 db    0
seg000:09C1                 db    0
seg000:09C2                 db    0
seg000:09C3                 db    0
seg000:09C4                 db    0
seg000:09C5                 db    0
seg000:09C6                 db    0
seg000:09C7                 db    0
seg000:09C8                 db    0
seg000:09C9                 db    0
seg000:09CA                 db    0
seg000:09CB                 db    0
seg000:09CC                 db    0
seg000:09CD                 db    0
seg000:09CE                 db    0
seg000:09CF                 db    0
seg000:09D0                 db    0
seg000:09D1                 db    0
seg000:09D2                 db    0
seg000:09D3                 db    0
seg000:09D4                 db    0
seg000:09D5                 db    0
seg000:09D6                 db    0
seg000:09D7                 db    0
seg000:09D8                 db    0
seg000:09D9                 db    0
seg000:09DA                 db    0
seg000:09DB                 db    0
seg000:09DC                 db    0
seg000:09DD                 db    0
seg000:09DE                 db    0
seg000:09DF                 db    0
seg000:09E0                 db    0
seg000:09E1                 db    0
seg000:09E2                 db    0
seg000:09E3                 db    0
seg000:09E4                 db    0
seg000:09E5                 db    0
seg000:09E6                 db    0
seg000:09E7                 db    0
seg000:09E8                 db    0
seg000:09E9                 db    0
seg000:09EA                 db    0
seg000:09EB                 db    0
seg000:09EC                 db    0
seg000:09ED                 db    0
seg000:09EE                 db    0
seg000:09EF                 db    0
seg000:09F0                 db    0
seg000:09F1                 db    0
seg000:09F2                 db    0
seg000:09F3                 db    0
seg000:09F4                 db    0
seg000:09F5                 db    0
seg000:09F6                 db    0
seg000:09F7                 db    0
seg000:09F8                 db    0
seg000:09F9                 db    0
seg000:09FA                 db    0
seg000:09FB                 db    0
seg000:09FC                 db    0
seg000:09FD                 db    0
seg000:09FE                 db    0
seg000:09FF                 db    0
seg000:0A00                 db 0B5h, 9Fh, 92h, 81h, 96h, 0D3h, 80h, 92h, 8Ah, 80h
seg000:0A00                 db 0
seg000:0A0B word_10A0B      dw 0F3h                 ; DATA XREF: init_screen+E↑r
seg000:0A0D word_10A0D      dw 0Ah                  ; DATA XREF: init_screen+A↑r
seg000:0A0F                 db 9Fh, 0B9h, 0B5h, 0BDh, 0F8h, 97h, 0AEh, 0BDh, 0AAh
seg000:0A0F                 db 0
seg000:0A19 word_10A19      dw 0D8h                 ; DATA XREF: init_screen+1C↑r
seg000:0A1B word_10A1B      dw 9                    ; DATA XREF: init_screen+18↑r
seg000:0A1D                 db 0Bh dup(0F2h), 9Ch, 0B7h, 0A4h, 0B7h, 0A0h, 0F2h, 95h
seg000:0A1D                 db 0BBh, 0A4h, 0B7h, 0F2h, 87h, 0A2h, 3 dup(0F3h), 0
seg000:0A39 never_give_up   dw 0D2h                 ; DATA XREF: game+88↑r
seg000:0A3B word_10A3B      dw 1Bh                  ; DATA XREF: game+84↑r
seg000:0A3D                 db 0D0h, 0E2h, 0EBh, 0E4h, 0E8h, 0EAh, 0E2h, 0A7h, 0F3h
seg000:0A3D                 db 0E8h, 0A7h, 0C1h, 0EBh, 0E6h, 0F5h, 0E2h, 0A7h, 0D4h
seg000:0A3D                 db 0E6h, 0FEh, 0F4h, 0ABh, 0A7h, 0F0h, 0EFh, 0E2h, 0F5h
seg000:0A3D                 db 0E2h, 0A7h, 0F3h, 0EFh, 0E2h, 0A7h, 0F7h, 0E8h, 0EEh
seg000:0A3D                 db 0E9h, 0F3h, 0F4h, 0
seg000:0A65 word_10A65      dw 87h                  ; DATA XREF: init_screen+2A↑r
seg000:0A67 word_10A67      dw 27h                  ; DATA XREF: init_screen+26↑r
seg000:0A69                 db 0F7h, 0FCh, 0FDh, 0B4h, 0E7h, 0B3h, 0FEh, 0F2h, 2 dup(0E7h)
seg000:0A69                 db 0F6h, 0E1h, 0BDh, 0B3h, 0C6h, 0E0h, 0F6h, 0B3h, 0E7h
seg000:0A69                 db 0FBh, 0F6h, 0B3h, 0F2h, 2 dup(0E1h), 0FCh, 0E4h, 0B3h
seg000:0A69                 db 0F8h, 0F6h, 0EAh, 0E0h, 0B3h, 0E7h, 0FCh, 0B3h, 0E3h
seg000:0A69                 db 0FFh, 0F2h, 0EAh, 0
seg000:0A92 word_10A92      dw 93h                  ; DATA XREF: init_screen+38↑r
seg000:0A94 word_10A94      dw 28h                  ; DATA XREF: init_screen+34↑r
seg000:0A96                 db 0B0h, 0B3h, 0B1h, 0B9h, 0F2h, 0A6h, 0BAh, 0B7h, 0F2h
seg000:0A96                 db 0A1h, 0B7h, 0A3h, 0A7h, 0B7h, 0BCh, 0B1h, 0B7h, 0FEh
seg000:0A96                 db 0F2h, 0BFh, 0B7h, 2 dup(0A1h), 0F2h, 0A7h, 0A2h, 0F2h
seg000:0A96                 db 0B3h, 0BCh, 0B6h, 0F2h, 0ABh, 0BDh, 0A7h, 0F2h, 0BEh
seg000:0A96                 db 0BDh, 0A1h, 0B7h, 0F3h, 0
seg000:0ABF word_10ABF      dw 0D2h                 ; DATA XREF: init_screen+46↑r
seg000:0AC1 word_10AC1      dw 28h                  ; DATA XREF: init_screen+42↑r
seg000:0AC3                 db 0DAh, 0EAh, 0E6h, 0FBh, 0ECh, 0B3h, 0A9h, 0
seg000:0ACB word_10ACB      dw 7                    ; DATA XREF: init_screen+5E↑r
seg000:0ACD word_10ACD      dw 89h                  ; DATA XREF: init_screen+62↑r
seg000:0ACF                 db 0F5h, 0DCh, 0CFh, 0DCh, 0D5h, 83h, 99h, 0
seg000:0AD7 word_10AD7      dw 7                    ; DATA XREF: init_screen+50↑r
seg000:0AD9 word_10AD9      dw 0B9h                 ; DATA XREF: init_screen+54↑r
seg000:0ADB aMmmmmmmmmmmmmm db 'MMMMMMMMMMMMMMMMMNkolo0WMMMMMMMMMMMMMMMM',0
seg000:0B04 aMmmmmmmmmmmmmm_0 db 'MMMMMMMMMMMMMMMMNkooold0WMMMMMMMMMMMMMMM',0
seg000:0B2D aMmmmmmmmmmmmmm_1 db 'MMMMMMMMMMMMMMMNkoloooldKWMMMMMMMMMMMMMM',0
seg000:0B56 aMmmmmmmmmmmmmm_2 db 'MMMMMMMMMMMMMMNOoloooooldKWMMMMMMMMMMMMM',0
seg000:0B7F aMmmmmmmmmmmmmw db 'MMMMMMMMMMMMMWOoloooooooldKMMMMMMMMMMMMM',0
seg000:0BA8 aMmmmmmmmmmmmw0 db 'MMMMMMMMMMMMW0olooooooooolxXMMMMMMMMMMMM',0
seg000:0BD1 aMmmmmmmmmmmw0d db 'MMMMMMMMMMMW0doooooooooooooxXMMMMMMMMMMM',0
seg000:0BFA aMmmmmmmmmmw0dl db 'MMMMMMMMMMW0dlooooooooooooooxXMMMMMMMMMM',0
seg000:0C23 aMmmmmmmmmwkdlo db 'MMMMMMMMMWKdloooolx0XOoloooookNMMMMMMMMM',0
seg000:0C4C aMmmmmmmmwkdloo db 'MMMMMMMMWKdlooooldKWMNkoooooookNMMMMMMMM',0
seg000:0C75 aMmmmmmmmkxlooo db 'MMMMMMMMKxloooold0WMMMNkoooooookNMMMMMMM',0
seg000:0C9E aMmmmmmmxxloooo db 'MMMMMMMXxloooolo0WMMMMMNkoooooloONMMMMMM',0
seg000:0CC7 aMmmmmmxxoooooo db 'MMMMMMXxoooooooOWMMMMMMMXxoooooooOWMMMMM',0
seg000:0CF0 aMmmmmnxooooooo db 'MMMMMNxoooooooONMMMMMMMMMXxloooolo0WMMMM',0
seg000:0D19 aMmmmnkoooooold db 'MMMMNkooooooldOKKKKKKKKKKNKdloooolo0WMMM',0
seg000:0D42 aMmmnkooooooooo db 'MMMNkoooooooooooooollooldKW0dloooold0WMM',0
seg000:0D6B aMmnooooooooooo db 'MMNOoooooooooooooooooooxKWMW0olooooldKWM',0
seg000:0D94 aMwoolllllloooo db 'MWOolllllloooooooooooxKWMMMMWOolllllldKM',0
seg000:0DBD aMn0oooookdoooo db 'MN0OOOOOkdooooooood0XNMMMMMMMWKOOOOOOOXM',0
seg000:0DE6 aMmmmmmmwkdlooo db 'MMMMMMMWKdlooooodONMMMMMMMMMMMMMMMMMMMMM',0
seg000:0E0F aMmmmmmmxxloooo_0 db 'MMMMMMMXxloooodOXWMMMMMMMMMMMMMMMMMMMMMM',0
seg000:0E38 aMmmmmmnkoooook db 'MMMMMMNkoooookXWMMMMMMMMMMMMMMMMMMMMMMMM',0
seg000:0E61 aMmmmmnkooooxkw db 'MMMMMNkooooxKWMMMMMMMMMMMMMMMMMMMMMMMMMM',0
seg000:0E8A aMmmmwooloxkwmm db 'MMMMWOoloxKWMMMMMMMMMMMMMMMMMMMMMMMMMMMM',0
seg000:0EB3 aMmmw0ood0nmmmm db 'MMMW0ood0NMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM',0
seg000:0EDC aMmwkddonmmmmmm db 'MMWKddONMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM',0
seg000:0F05 aMmnkdkwmmmmmmm db 'MMNkdKWMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM',0
seg000:0F2E                 align 4
seg000:0F2E seg000          ends
seg000:0F2E
seg001:0000 ; ===========================================================================
seg001:0000
seg001:0000 ; Segment type: Regular
seg001:0000 seg001          segment byte public 'UNK' use16
seg001:0000                 assume cs:seg001
seg001:0000                 assume es:nothing, ss:nothing, ds:nothing, fs:nothing, gs:nothing
seg001:0000 unk_10F30       db  41h ; A
seg001:0001                 db  32h ; 2
seg001:0002                 db  32h ; 2
seg001:0003                 db  30h ; 0
seg001:0004                 db  20h
seg001:0005                 db  49h ; I
seg001:0006                 db  37h ; 7
seg001:0007                 db  20h
seg001:0008                 db  44h ; D
seg001:0009                 db  31h ; 1
seg001:000A                 db  20h
seg001:000B                 db  48h ; H
seg001:000C                 db  35h ; 5
seg001:000D                 db  20h
seg001:000E                 db  54h ; T
seg001:000F                 db  36h ; 6
seg001:000F seg001          ends
seg001:000F
seg002:0000 ; ===========================================================================
seg002:0000
seg002:0000 ; Segment type: Pure code
seg002:0000 seg002          segment byte public 'CODE' use16
seg002:0000                 assume cs:seg002
seg002:0000                 assume es:nothing, ss:nothing, ds:nothing, fs:nothing, gs:nothing
seg002:0000
seg002:0000 ; =============== S U B R O U T I N E =======================================
seg002:0000
seg002:0000 ; Attributes: thunk
seg002:0000
seg002:0000 call_dynamic_funcs proc far             ; CODE XREF: call_dynamics1+C↑P
seg002:0000                                         ; call_dynamics1+14↑P ...
seg002:0000                 jmp     near ptr sub_10FF0
seg002:0000 call_dynamic_funcs endp
seg002:0000
seg002:0000 ; ---------------------------------------------------------------------------
seg002:0003                 db 0ACh dup(0), 1Ah
seg002:00B0
seg002:00B0 ; =============== S U B R O U T I N E =======================================
seg002:00B0
seg002:00B0
seg002:00B0 sub_10FF0       proc far                ; CODE XREF: call_dynamic_funcs↑j
seg002:00B0                 pushf
seg002:00B1                 cli
seg002:00B2                 push    ds
seg002:00B3                 push    es
seg002:00B4                 push    ax
seg002:00B5                 push    bx
seg002:00B6                 push    cx
seg002:00B7                 push    dx
seg002:00B8                 push    di
seg002:00B9                 push    si
seg002:00BA                 push    bp
seg002:00BB                 mov     bp, sp
seg002:00BD                 push    ax
seg002:00BE                 mov     ax, cs
seg002:00C0                 mov     ds, ax
seg002:00C2                 assume ds:seg002
seg002:00C2                 mov     es, ax
seg002:00C4                 assume es:seg002
seg002:00C4                 pop     ax
seg002:00C5                 or      word ptr [bp+12h], 1
seg002:00C9
seg002:00C9 loc_11009:
seg002:00C9                 mov     word ptr [bp+0Ch], 0FFFFh
seg002:00CE                 cmp     byte_12FAF, 0
seg002:00D3                 jnz     short loc_11039
seg002:00D5                 mov     byte_12FAF, 1
seg002:00DA
seg002:00DA loc_1101A:
seg002:00DA                 sti
seg002:00DB                 cld
seg002:00DC                 cmp     bx, 28h ; '('
seg002:00E0                 jb      short loc_11027
seg002:00E2                 mov     ax, 8000h
seg002:00E5                 jmp     short loc_11034
seg002:00E7 ; ---------------------------------------------------------------------------
seg002:00E7
seg002:00E7 loc_11027:                              ; CODE XREF: sub_10FF0+30↑j
seg002:00E7                 and     word ptr [bp+12h], 0FFFEh
seg002:00EB                 shl     bx, 1
seg002:00ED                 call    funcs_1102D[bx]
seg002:00F1                 mov     [bp+0Ch], ax
seg002:00F4
seg002:00F4 loc_11034:                              ; CODE XREF: sub_10FF0+35↑j
seg002:00F4                 mov     byte_12FAF, 0
seg002:00F9
seg002:00F9 loc_11039:                              ; CODE XREF: sub_10FF0+23↑j
seg002:00F9                 pop     bp
seg002:00FA                 pop     si
seg002:00FB                 pop     di
seg002:00FC                 pop     dx
seg002:00FD                 pop     cx
seg002:00FE                 pop     bx
seg002:00FF                 pop     ax
seg002:0100                 pop     es
seg002:0101                 assume es:nothing
seg002:0101                 pop     ds
seg002:0102                 assume ds:nothing
seg002:0102                 popf
seg002:0103                 retf
seg002:0103 sub_10FF0       endp
seg002:0103
seg002:0104
seg002:0104 ; =============== S U B R O U T I N E =======================================
seg002:0104
seg002:0104
seg002:0104 sub_11044       proc far
seg002:0104                 push    ds
seg002:0105                 push    es
seg002:0106                 push    ax
seg002:0107                 push    bx
seg002:0108                 push    cx
seg002:0109                 push    dx
seg002:010A                 push    di
seg002:010B                 push    si
seg002:010C                 push    bp
seg002:010D                 mov     ax, cs
seg002:010F                 mov     ds, ax
seg002:0111                 assume ds:seg002
seg002:0111                 mov     es, ax
seg002:0113                 assume es:seg002
seg002:0113                 mov     byte_12FB0, 1
seg002:0118                 cmp     byte_12FAE, 1
seg002:011D                 jz      short loc_110CB
seg002:011F                 mov     byte_12FAE, 1
seg002:0124                 cli
seg002:0125                 mov     word_12FCA, ss
seg002:0129                 mov     word_12FC8, sp
seg002:012D                 mov     ax, ds
seg002:012F                 mov     ss, ax
seg002:0131                 assume ss:seg002
seg002:0131                 mov     sp, 22DCh
seg002:0134                 sti
seg002:0135                 cld
seg002:0136                 cmp     word_132D7, 1
seg002:013B                 jnz     short loc_11080
seg002:013D                 call    sub_11946
seg002:0140
seg002:0140 loc_11080:                              ; CODE XREF: sub_11044+37↑j
seg002:0140                 cmp     byte_1326B, 0
seg002:0145                 jz      short loc_1108B
seg002:0147                 inc     score_maybe
seg002:014B
seg002:014B loc_1108B:                              ; CODE XREF: sub_11044+41↑j
seg002:014B                 mov     ax, word_12FB9
seg002:014E                 mov     dx, word_12FBB
seg002:0152                 add     ax, word_12FB3
seg002:0156                 adc     dx, 0
seg002:0159                 cmp     ax, word_12FB1
seg002:015D                 jnb     short loc_110A4
seg002:015F                 cmp     dx, 1
seg002:0162                 jb      short loc_110B5
seg002:0164
seg002:0164 loc_110A4:                              ; CODE XREF: sub_11044+59↑j
seg002:0164                 pushf
seg002:0165                 call    dword_12FC4
seg002:0169                 mov     byte_12FB0, 0
seg002:016E                 sub     ax, word_12FB1
seg002:0172                 sbb     dx, 0
seg002:0175
seg002:0175 loc_110B5:                              ; CODE XREF: sub_11044+5E↑j
seg002:0175                 mov     word_12FB9, ax
seg002:0178                 mov     word_12FBB, dx
seg002:017C                 cli
seg002:017D                 mov     ss, word_12FCA
seg002:0181                 assume ss:nothing
seg002:0181                 mov     sp, word_12FC8
seg002:0185                 mov     byte_12FAE, 0
seg002:018A                 sti
seg002:018B
seg002:018B loc_110CB:                              ; CODE XREF: sub_11044+19↑j
seg002:018B                 cmp     byte_12FB0, 0
seg002:0190                 jz      short loc_110D6
seg002:0192                 mov     al, 20h ; ' '
seg002:0194                 out     20h, al         ; Interrupt controller, 8259A.
seg002:0196
seg002:0196 loc_110D6:                              ; CODE XREF: sub_11044+8C↑j
seg002:0196                 pop     bp
seg002:0197                 pop     si
seg002:0198                 pop     di
seg002:0199                 pop     dx
seg002:019A                 pop     cx
seg002:019B                 pop     bx
seg002:019C                 pop     ax
seg002:019D                 pop     es
seg002:019E                 assume es:nothing
seg002:019E                 pop     ds
seg002:019F                 assume ds:nothing
seg002:019F                 iret
seg002:019F sub_11044       endp
seg002:019F
seg002:01A0
seg002:01A0 ; =============== S U B R O U T I N E =======================================
seg002:01A0
seg002:01A0
seg002:01A0 sub_110E0       proc near               ; CODE XREF: sub_11213+3D↓p
seg002:01A0                                         ; sub_1125B+1A↓p ...
seg002:01A0                 pushf
seg002:01A1                 push    ds
seg002:01A2                 shl     bx, 1
seg002:01A4                 shl     bx, 1
seg002:01A6                 cli
seg002:01A7                 push    ax
seg002:01A8                 sub     ax, ax
seg002:01AA                 mov     ds, ax
seg002:01AC                 assume ds:nothing
seg002:01AC                 pop     ax
seg002:01AD                 mov     [bx], ax
seg002:01AF                 mov     [bx+2], dx
seg002:01B2                 pop     ds
seg002:01B3                 assume ds:nothing
seg002:01B3                 popf
seg002:01B4                 retn
seg002:01B4 sub_110E0       endp
seg002:01B4
seg002:01B5
seg002:01B5 ; =============== S U B R O U T I N E =======================================
seg002:01B5
seg002:01B5
seg002:01B5 sub_110F5       proc near               ; CODE XREF: sub_11108+3↓p
seg002:01B5                                         ; sub_11213+2B↓p ...
seg002:01B5                 pushf
seg002:01B6                 push    ds
seg002:01B7                 shl     bx, 1
seg002:01B9                 shl     bx, 1
seg002:01BB                 cli
seg002:01BC                 sub     ax, ax
seg002:01BE                 mov     ds, ax
seg002:01C0                 assume ds:nothing
seg002:01C0                 mov     ax, [bx]
seg002:01C2                 mov     dx, [bx+2]
seg002:01C5                 pop     ds
seg002:01C6                 assume ds:nothing
seg002:01C6                 popf
seg002:01C7                 retn
seg002:01C7 sub_110F5       endp
seg002:01C7
seg002:01C8
seg002:01C8 ; =============== S U B R O U T I N E =======================================
seg002:01C8
seg002:01C8
seg002:01C8 sub_11108       proc near               ; CODE XREF: sub_1125B+B↓p
seg002:01C8                 mov     bx, 8
seg002:01CB                 call    sub_110F5
seg002:01CE                 mov     bx, cs
seg002:01D0                 cmp     dx, bx
seg002:01D2                 jnz     short loc_1111C
seg002:01D4                 cmp     ax, 104h
seg002:01D7                 jnz     short loc_1111C
seg002:01D9                 clc
seg002:01DA                 jmp     short locret_1111D
seg002:01DC ; ---------------------------------------------------------------------------
seg002:01DC
seg002:01DC loc_1111C:                              ; CODE XREF: sub_11108+A↑j
seg002:01DC                                         ; sub_11108+F↑j
seg002:01DC                 stc
seg002:01DD
seg002:01DD locret_1111D:                           ; CODE XREF: sub_11108+12↑j
seg002:01DD                 retn
seg002:01DD sub_11108       endp
seg002:01DD
seg002:01DE
seg002:01DE ; =============== S U B R O U T I N E =======================================
seg002:01DE
seg002:01DE
seg002:01DE sub_1111E       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:01DE                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:01DE                 mov     ax, ds:33h
seg002:01E1                 retn
seg002:01E1 sub_1111E       endp
seg002:01E1
seg002:01E2
seg002:01E2 ; =============== S U B R O U T I N E =======================================
seg002:01E2
seg002:01E2
seg002:01E2 sub_11122       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:01E2                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:01E2                 push    ds
seg002:01E3                 push    es
seg002:01E4                 push    si
seg002:01E5                 push    di
seg002:01E6                 push    bx
seg002:01E7                 push    dx
seg002:01E8                 or      word ptr es:1FDCh, 8003h
seg002:01EF                 cmp     byte ptr ds:206Dh, 0
seg002:01F4                 jz      short loc_11139
seg002:01F6                 jmp     loc_111BB
seg002:01F9 ; ---------------------------------------------------------------------------
seg002:01F9
seg002:01F9 loc_11139:                              ; CODE XREF: sub_11122+12↑j
seg002:01F9                 and     word ptr es:1FDCh, 7FFFh
seg002:0200                 mov     ds, dx
seg002:0202                 mov     si, ax
seg002:0204                 mov     di, 1FECh
seg002:0207                 call    sub_1133D
seg002:020A                 mov     dx, di
seg002:020C                 mov     si, di
seg002:020E                 push    es
seg002:020F                 pop     ds
seg002:0210                 call    sub_1134D
seg002:0213                 mov     di, 1FE0h
seg002:0216                 call    sub_111C6
seg002:0219                 jnb     short loc_11177
seg002:021B                 mov     bx, ax
seg002:021D                 cmp     byte ptr [bx], 31h ; '1'
seg002:0220                 jb      short loc_11177
seg002:0222                 cmp     byte ptr [bx], 32h ; '2'
seg002:0225                 ja      short loc_11177
seg002:0227                 mov     al, [bx]
seg002:0229                 mov     ah, 0
seg002:022B                 sub     al, 31h ; '1'
seg002:022D                 mov     es:233Eh, ax
seg002:0231                 and     word ptr es:1FDCh, 0FFFEh
seg002:0237
seg002:0237 loc_11177:                              ; CODE XREF: sub_11122+37↑j
seg002:0237                                         ; sub_11122+3E↑j ...
seg002:0237                 mov     di, 1FE7h
seg002:023A                 call    sub_111C6
seg002:023D                 jnb     short loc_111BB
seg002:023F                 mov     bx, ax
seg002:0241                 cmp     byte ptr [bx], 47h ; 'G'
seg002:0244                 jz      short loc_11192
seg002:0246                 cmp     byte ptr [bx], 45h ; 'E'
seg002:0249                 jz      short loc_1119B
seg002:024B                 cmp     byte ptr [bx], 42h ; 'B'
seg002:024E                 jz      short loc_111A4
seg002:0250                 jmp     short loc_111BB
seg002:0252 ; ---------------------------------------------------------------------------
seg002:0252
seg002:0252 loc_11192:                              ; CODE XREF: sub_11122+62↑j
seg002:0252                 mov     word ptr es:2338h, 0
seg002:0259                 jmp     short loc_111AB
seg002:025B ; ---------------------------------------------------------------------------
seg002:025B
seg002:025B loc_1119B:                              ; CODE XREF: sub_11122+67↑j
seg002:025B                 mov     word ptr es:2338h, 1
seg002:0262                 jmp     short loc_111AB
seg002:0264 ; ---------------------------------------------------------------------------
seg002:0264
seg002:0264 loc_111A4:                              ; CODE XREF: sub_11122+6C↑j
seg002:0264                 mov     word ptr es:2338h, 2
seg002:026B
seg002:026B loc_111AB:                              ; CODE XREF: sub_11122+77↑j
seg002:026B                                         ; sub_11122+80↑j
seg002:026B                 push    word ptr es:2338h
seg002:0270                 pop     word ptr es:233Ah
seg002:0275                 and     word ptr es:1FDCh, 0FFFDh
seg002:027B
seg002:027B loc_111BB:                              ; CODE XREF: sub_11122+14↑j
seg002:027B                                         ; sub_11122+5B↑j ...
seg002:027B                 mov     ax, es:1FDCh
seg002:027F                 pop     dx
seg002:0280                 pop     bx
seg002:0281                 pop     di
seg002:0282                 pop     si
seg002:0283                 pop     es
seg002:0284                 pop     ds
seg002:0285                 retn
seg002:0285 sub_11122       endp
seg002:0285
seg002:0286
seg002:0286 ; =============== S U B R O U T I N E =======================================
seg002:0286
seg002:0286
seg002:0286 sub_111C6       proc near               ; CODE XREF: sub_11122+34↑p
seg002:0286                                         ; sub_11122+58↑p
seg002:0286                 push    si
seg002:0287                 push    di
seg002:0288                 push    bx
seg002:0289                 push    cx
seg002:028A                 push    dx
seg002:028B                 mov     cx, 0
seg002:028E                 mov     dx, di
seg002:0290
seg002:0290 loc_111D0:                              ; CODE XREF: sub_111C6+25↓j
seg002:0290                                         ; sub_111C6+2F↓j
seg002:0290                 mov     al, es:[di]
seg002:0293                 or      al, al
seg002:0295                 jz      short loc_111F7
seg002:0297
seg002:0297 loc_111D7:                              ; CODE XREF: sub_111C6+28↓j
seg002:0297                 mov     bl, [si]
seg002:0299                 or      bl, bl
seg002:029B                 jz      short loc_111F7
seg002:029D                 cmp     al, bl
seg002:029F                 jz      short loc_111F0
seg002:02A1                 or      cx, cx
seg002:02A3                 jz      short loc_111ED
seg002:02A5                 mov     cx, 0
seg002:02A8                 mov     di, dx
seg002:02AA                 inc     si
seg002:02AB                 jmp     short loc_111D0
seg002:02AD ; ---------------------------------------------------------------------------
seg002:02AD
seg002:02AD loc_111ED:                              ; CODE XREF: sub_111C6+1D↑j
seg002:02AD                 inc     si
seg002:02AE                 jmp     short loc_111D7
seg002:02B0 ; ---------------------------------------------------------------------------
seg002:02B0
seg002:02B0 loc_111F0:                              ; CODE XREF: sub_111C6+19↑j
seg002:02B0                 mov     cx, 1
seg002:02B3                 inc     si
seg002:02B4                 inc     di
seg002:02B5                 jmp     short loc_111D0
seg002:02B7 ; ---------------------------------------------------------------------------
seg002:02B7
seg002:02B7 loc_111F7:                              ; CODE XREF: sub_111C6+F↑j
seg002:02B7                                         ; sub_111C6+15↑j
seg002:02B7                 or      cx, cx
seg002:02B9                 jnz     short loc_111FE
seg002:02BB                 clc
seg002:02BC                 jmp     short loc_11201
seg002:02BE ; ---------------------------------------------------------------------------
seg002:02BE
seg002:02BE loc_111FE:                              ; CODE XREF: sub_111C6+33↑j
seg002:02BE                 mov     ax, si
seg002:02C0                 stc
seg002:02C1
seg002:02C1 loc_11201:                              ; CODE XREF: sub_111C6+36↑j
seg002:02C1                 pop     dx
seg002:02C2                 pop     cx
seg002:02C3                 pop     bx
seg002:02C4                 pop     di
seg002:02C5                 pop     si
seg002:02C6                 retn
seg002:02C6 sub_111C6       endp
seg002:02C6
seg002:02C7
seg002:02C7 ; =============== S U B R O U T I N E =======================================
seg002:02C7
seg002:02C7
seg002:02C7 sub_11207       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:02C7                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:02C7                 push    es
seg002:02C8                 push    ds
seg002:02C9                 call    sub_112A5
seg002:02CC                 or      ax, ax
seg002:02CE                 jnz     short $+2
seg002:02D0
seg002:02D0 loc_11210:                              ; CODE XREF: sub_11207+7↑j
seg002:02D0                 pop     ds
seg002:02D1                 pop     es
seg002:02D2                 retn
seg002:02D2 sub_11207       endp
seg002:02D2
seg002:02D3
seg002:02D3 ; =============== S U B R O U T I N E =======================================
seg002:02D3
seg002:02D3
seg002:02D3 sub_11213       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:02D3                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:02D3                 cmp     byte ptr ds:206Dh, 0
seg002:02D8                 jz      short loc_1121F
seg002:02DA                 mov     ax, 1
seg002:02DD                 jmp     short locret_1125A
seg002:02DF ; ---------------------------------------------------------------------------
seg002:02DF
seg002:02DF loc_1121F:                              ; CODE XREF: sub_11213+5↑j
seg002:02DF                 call    sub_12328
seg002:02E2                 or      ax, ax
seg002:02E4                 jz      short loc_11229
seg002:02E6                 inc     ax
seg002:02E7                 jmp     short locret_1125A
seg002:02E9 ; ---------------------------------------------------------------------------
seg002:02E9
seg002:02E9 loc_11229:                              ; CODE XREF: sub_11213+11↑j
seg002:02E9                 call    sub_11416
seg002:02EC                 call    sub_11434
seg002:02EF                 or      ax, ax
seg002:02F1                 jz      short loc_11238
seg002:02F3                 add     ax, 7
seg002:02F6                 jmp     short locret_1125A
seg002:02F8 ; ---------------------------------------------------------------------------
seg002:02F8
seg002:02F8 loc_11238:                              ; CODE XREF: sub_11213+1E↑j
seg002:02F8                 call    sub_113CE
seg002:02FB                 mov     bx, 8
seg002:02FE                 call    sub_110F5
seg002:0301                 mov     ds:2084h, ax
seg002:0304                 mov     ds:2086h, dx
seg002:0308                 mov     bx, 8
seg002:030B                 mov     dx, cs
seg002:030D                 mov     ax, 104h
seg002:0310                 call    sub_110E0
seg002:0313                 mov     byte ptr ds:206Dh, 1
seg002:0318                 sub     ax, ax
seg002:031A
seg002:031A locret_1125A:                           ; CODE XREF: sub_11213+A↑j
seg002:031A                                         ; sub_11213+14↑j ...
seg002:031A                 retn
seg002:031A sub_11213       endp
seg002:031A
seg002:031B
seg002:031B ; =============== S U B R O U T I N E =======================================
seg002:031B
seg002:031B
seg002:031B sub_1125B       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:031B                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:031B                 cmp     byte ptr ds:206Dh, 0
seg002:0320                 jz      short loc_1128E
seg002:0322                 or      word ptr [bp+12h], 1
seg002:0326                 call    sub_11108
seg002:0329                 jb      short loc_11285
seg002:032B                 mov     bx, 8
seg002:032E                 mov     ax, ds:2084h
seg002:0331                 mov     dx, ds:2086h
seg002:0335                 call    sub_110E0
seg002:0338                 cmp     word ptr ds:233Eh, 0
seg002:033D                 jz      short loc_11282
seg002:033F                 call    sub_12591
seg002:0342
seg002:0342 loc_11282:                              ; CODE XREF: sub_1125B+22↑j
seg002:0342                 call    sub_1212E
seg002:0345
seg002:0345 loc_11285:                              ; CODE XREF: sub_1125B+E↑j
seg002:0345                 mov     byte ptr ds:206Dh, 0
seg002:034A                 xor     ax, ax
seg002:034C                 jmp     short locret_11291
seg002:034E ; ---------------------------------------------------------------------------
seg002:034E
seg002:034E loc_1128E:                              ; CODE XREF: sub_1125B+5↑j
seg002:034E                 mov     ax, 1
seg002:0351
seg002:0351 locret_11291:                           ; CODE XREF: sub_1125B+31↑j
seg002:0351                 retn
seg002:0351 sub_1125B       endp
seg002:0351
seg002:0352
seg002:0352 ; =============== S U B R O U T I N E =======================================
seg002:0352
seg002:0352
seg002:0352 sub_11292       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:0352                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:0352                 pushf
seg002:0353                 cli
seg002:0354                 call    sub_11464
seg002:0357                 call    sub_11416
seg002:035A                 call    sub_11434
seg002:035D                 xor     ax, ax
seg002:035F                 popf
seg002:0360                 retn
seg002:0360 sub_11292       endp
seg002:0360
seg002:0361
seg002:0361 ; =============== S U B R O U T I N E =======================================
seg002:0361
seg002:0361
seg002:0361 ax_0x8000       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:0361                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:0361                 mov     ax, 8000h
seg002:0364                 retn
seg002:0364 ax_0x8000       endp
seg002:0364
seg002:0365
seg002:0365 ; =============== S U B R O U T I N E =======================================
seg002:0365
seg002:0365
seg002:0365 sub_112A5       proc near               ; CODE XREF: sub_11207+2↑p
seg002:0365                 or      word ptr ds:1FDEh, 8007h
seg002:036B                 cmp     byte ptr ds:206Dh, 0
seg002:0370                 jz      short loc_112B5
seg002:0372                 jmp     loc_11339
seg002:0375 ; ---------------------------------------------------------------------------
seg002:0375
seg002:0375 loc_112B5:                              ; CODE XREF: sub_112A5+B↑j
seg002:0375                 and     word ptr ds:1FDEh, 7FFFh
seg002:037B                 mov     ds, dx
seg002:037D                 mov     si, ax
seg002:037F                 mov     di, 1FECh
seg002:0382                 call    sub_1133D
seg002:0385                 mov     dx, di
seg002:0387                 mov     si, di
seg002:0389                 push    es
seg002:038A                 pop     ds
seg002:038B                 call    sub_1134D
seg002:038E                 push    es
seg002:038F                 push    si
seg002:0390                 mov     al, 41h ; 'A'
seg002:0392                 call    sub_1136D
seg002:0395                 jb      short loc_112F9
seg002:0397                 mov     bx, ax
seg002:0399                 call    sub_11386
seg002:039C                 jb      short loc_112F9
seg002:039E                 cmp     ah, 2
seg002:03A1                 jnz     short loc_112F9
seg002:03A3                 and     al, 0F0h
seg002:03A5                 cmp     al, 80h
seg002:03A7                 ja      short loc_112F9
seg002:03A9                 cmp     al, 10h
seg002:03AB                 jb      short loc_112F9
seg002:03AD                 test    al, 10h
seg002:03AF                 jnz     short loc_112F9
seg002:03B1                 mov     ds:207Dh, ax
seg002:03B4                 and     word ptr ds:1FDEh, 0FFFEh
seg002:03B9
seg002:03B9 loc_112F9:                              ; CODE XREF: sub_112A5+30↑j
seg002:03B9                                         ; sub_112A5+37↑j ...
seg002:03B9                 mov     al, 50h ; 'P'
seg002:03BB                 call    sub_1136D
seg002:03BE                 jb      short loc_11313
seg002:03C0                 mov     bx, ax
seg002:03C2                 call    sub_11386
seg002:03C5                 jb      short loc_11313
seg002:03C7                 mov     ds:207Fh, ax
seg002:03CA                 inc     ax
seg002:03CB                 mov     ds:2081h, ax
seg002:03CE                 and     word ptr ds:1FDEh, 0FFFBh
seg002:03D3
seg002:03D3 loc_11313:                              ; CODE XREF: sub_112A5+59↑j
seg002:03D3                                         ; sub_112A5+60↑j
seg002:03D3                 mov     al, 49h ; 'I'
seg002:03D5                 call    sub_1136D
seg002:03D8                 jb      short loc_11332
seg002:03DA                 mov     bx, ax
seg002:03DC                 call    sub_11386
seg002:03DF                 jb      short loc_11332
seg002:03E1                 and     ax, 0FFh
seg002:03E4                 cmp     al, 9
seg002:03E6                 jbe     short loc_1132A
seg002:03E8                 sub     al, 6
seg002:03EA
seg002:03EA loc_1132A:                              ; CODE XREF: sub_112A5+81↑j
seg002:03EA                 mov     ds:2083h, al
seg002:03ED                 and     word ptr ds:1FDEh, 0FFFDh
seg002:03F2
seg002:03F2 loc_11332:                              ; CODE XREF: sub_112A5+73↑j
seg002:03F2                                         ; sub_112A5+7A↑j
seg002:03F2                 mov     ax, ds:1FDEh
seg002:03F5                 pop     si
seg002:03F6                 pop     es
seg002:03F7                 jmp     short locret_1133C
seg002:03F9 ; ---------------------------------------------------------------------------
seg002:03F9
seg002:03F9 loc_11339:                              ; CODE XREF: sub_112A5+D↑j
seg002:03F9                 mov     ax, 0FFFFh
seg002:03FC
seg002:03FC locret_1133C:                           ; CODE XREF: sub_112A5+92↑j
seg002:03FC                 retn
seg002:03FC sub_112A5       endp
seg002:03FC
seg002:03FD
seg002:03FD ; =============== S U B R O U T I N E =======================================
seg002:03FD
seg002:03FD
seg002:03FD sub_1133D       proc near               ; CODE XREF: sub_11122+25↑p
seg002:03FD                                         ; sub_112A5+1D↑p
seg002:03FD                 push    si
seg002:03FE                 push    di
seg002:03FF                 push    ax
seg002:0400
seg002:0400 loc_11340:                              ; CODE XREF: sub_1133D+9↓j
seg002:0400                 lodsb
seg002:0401                 or      al, al
seg002:0403                 jz      short loc_11348
seg002:0405                 stosb
seg002:0406                 jmp     short loc_11340
seg002:0408 ; ---------------------------------------------------------------------------
seg002:0408
seg002:0408 loc_11348:                              ; CODE XREF: sub_1133D+6↑j
seg002:0408                 stosb
seg002:0409                 pop     ax
seg002:040A                 pop     di
seg002:040B                 pop     si
seg002:040C                 retn
seg002:040C sub_1133D       endp
seg002:040C
seg002:040D
seg002:040D ; =============== S U B R O U T I N E =======================================
seg002:040D
seg002:040D
seg002:040D sub_1134D       proc near               ; CODE XREF: sub_11122+2E↑p
seg002:040D                                         ; sub_112A5+26↑p
seg002:040D                 push    si
seg002:040E                 push    ax
seg002:040F                 mov     si, dx
seg002:0411                 cld
seg002:0412
seg002:0412 loc_11352:                              ; CODE XREF: sub_1134D+11↓j
seg002:0412                 lodsb
seg002:0413                 cmp     al, 60h ; '`'
seg002:0415                 jb      short loc_1135C
seg002:0417                 sub     al, 20h ; ' '
seg002:0419                 mov     [si-1], al
seg002:041C
seg002:041C loc_1135C:                              ; CODE XREF: sub_1134D+8↑j
seg002:041C                 or      al, al
seg002:041E                 jnz     short loc_11352
seg002:0420                 pop     ax
seg002:0421                 pop     si
seg002:0422                 retn
seg002:0422 sub_1134D       endp
seg002:0422
seg002:0423 ; ---------------------------------------------------------------------------
seg002:0423                 cld
seg002:0424
seg002:0424 loc_11364:                              ; CODE XREF: seg002:042A↓j
seg002:0424                 lodsb
seg002:0425                 scasb
seg002:0426                 jnz     short locret_1136C
seg002:0428                 or      al, al
seg002:042A                 jnz     short loc_11364
seg002:042C
seg002:042C locret_1136C:                           ; CODE XREF: seg002:0426↑j
seg002:042C                 retn
seg002:042D
seg002:042D ; =============== S U B R O U T I N E =======================================
seg002:042D
seg002:042D
seg002:042D sub_1136D       proc near               ; CODE XREF: sub_112A5+2D↑p
seg002:042D                                         ; sub_112A5+56↑p ...
seg002:042D                 push    ds
seg002:042E                 push    si
seg002:042F                 push    es
seg002:0430                 pop     ds
seg002:0431                 mov     ah, al
seg002:0433                 cld
seg002:0434
seg002:0434 loc_11374:                              ; CODE XREF: sub_1136D+E↓j
seg002:0434                 lodsb
seg002:0435                 or      al, al
seg002:0437                 jz      short loc_11382
seg002:0439                 cmp     al, ah
seg002:043B                 jnz     short loc_11374
seg002:043D                 mov     ax, si
seg002:043F                 clc
seg002:0440                 jmp     short loc_11383
seg002:0442 ; ---------------------------------------------------------------------------
seg002:0442
seg002:0442 loc_11382:                              ; CODE XREF: sub_1136D+A↑j
seg002:0442                 stc
seg002:0443
seg002:0443 loc_11383:                              ; CODE XREF: sub_1136D+13↑j
seg002:0443                 pop     si
seg002:0444                 pop     ds
seg002:0445                 retn
seg002:0445 sub_1136D       endp
seg002:0445
seg002:0446
seg002:0446 ; =============== S U B R O U T I N E =======================================
seg002:0446
seg002:0446
seg002:0446 sub_11386       proc near               ; CODE XREF: sub_112A5+34↑p
seg002:0446                                         ; sub_112A5+5D↑p ...
seg002:0446                 sub     dx, dx
seg002:0448                 mov     al, es:[bx]
seg002:044B                 inc     bx
seg002:044C                 cmp     al, 20h ; ' '
seg002:044E                 jz      short loc_113CC
seg002:0450                 cmp     al, 0
seg002:0452                 jz      short loc_113CC
seg002:0454
seg002:0454 loc_11394:                              ; CODE XREF: sub_11386+40↓j
seg002:0454                 mov     cl, 4
seg002:0456                 shl     dx, cl
seg002:0458                 cmp     al, 30h ; '0'
seg002:045A                 jb      short loc_113A6
seg002:045C                 cmp     al, 39h ; '9'
seg002:045E                 ja      short loc_113A6
seg002:0460                 sub     al, 30h ; '0'
seg002:0462                 or      dl, al
seg002:0464                 jmp     short loc_113BC
seg002:0466 ; ---------------------------------------------------------------------------
seg002:0466
seg002:0466 loc_113A6:                              ; CODE XREF: sub_11386+14↑j
seg002:0466                                         ; sub_11386+18↑j
seg002:0466                 cmp     al, 61h ; 'a'
seg002:0468                 jb      short loc_113B0
seg002:046A                 cmp     al, 7Ah ; 'z'
seg002:046C                 ja      short loc_113B0
seg002:046E                 sub     al, 61h ; 'a'
seg002:0470
seg002:0470 loc_113B0:                              ; CODE XREF: sub_11386+22↑j
seg002:0470                                         ; sub_11386+26↑j
seg002:0470                 cmp     al, 41h ; 'A'
seg002:0472                 jb      short loc_113CC
seg002:0474                 cmp     al, 46h ; 'F'
seg002:0476                 ja      short loc_113CC
seg002:0478                 sub     al, 37h ; '7'
seg002:047A                 or      dl, al
seg002:047C
seg002:047C loc_113BC:                              ; CODE XREF: sub_11386+1E↑j
seg002:047C                 mov     al, es:[bx]
seg002:047F                 inc     bx
seg002:0480                 cmp     al, 20h ; ' '
seg002:0482                 jz      short loc_113C8
seg002:0484                 or      al, al
seg002:0486                 jnz     short loc_11394
seg002:0488
seg002:0488 loc_113C8:                              ; CODE XREF: sub_11386+3C↑j
seg002:0488                 mov     ax, dx
seg002:048A                 jmp     short locret_113CD
seg002:048C ; ---------------------------------------------------------------------------
seg002:048C
seg002:048C loc_113CC:                              ; CODE XREF: sub_11386+8↑j
seg002:048C                                         ; sub_11386+C↑j ...
seg002:048C                 stc
seg002:048D
seg002:048D locret_113CD:                           ; CODE XREF: sub_11386+44↑j
seg002:048D                 retn
seg002:048D sub_11386       endp
seg002:048D
seg002:048E
seg002:048E ; =============== S U B R O U T I N E =======================================
seg002:048E
seg002:048E
seg002:048E sub_113CE       proc near               ; CODE XREF: sub_11213:loc_11238↑p
seg002:048E                 push    ax
seg002:048F                 push    bx
seg002:0490                 push    cx
seg002:0491                 push    dx
seg002:0492                 mov     bx, 0
seg002:0495                 mov     cx, 8000h
seg002:0498
seg002:0498 loc_113D8:                              ; CODE XREF: sub_113CE:loc_113EE↓j
seg002:0498                 mov     al, 0C2h
seg002:049A                 mov     dx, 43h ; 'C'
seg002:049D                 out     dx, al          ; Timer 8253-5 (AT: 8254.2).
seg002:049E                 mov     dx, 40h ; '@'
seg002:04A1                 in      al, dx          ; Timer 8253-5 (AT: 8254.2).
seg002:04A2                 in      al, dx          ; Timer 8253-5 (AT: 8254.2).
seg002:04A3                 mov     ah, al
seg002:04A5                 in      al, dx          ; Timer 8253-5 (AT: 8254.2).
seg002:04A6                 xchg    ah, al
seg002:04A8                 cmp     ax, bx
seg002:04AA                 jb      short loc_113EE
seg002:04AC                 mov     bx, ax
seg002:04AE
seg002:04AE loc_113EE:                              ; CODE XREF: sub_113CE+1C↑j
seg002:04AE                 loop    loc_113D8
seg002:04B0                 cmp     bx, 0FFF0h
seg002:04B3                 jb      short loc_113F8
seg002:04B5                 mov     bx, 0FFFFh
seg002:04B8
seg002:04B8 loc_113F8:                              ; CODE XREF: sub_113CE+25↑j
seg002:04B8                 mov     ds:2071h, bx
seg002:04BC                 mov     ds:2073h, bx
seg002:04C0                 pop     dx
seg002:04C1                 pop     cx
seg002:04C2                 pop     bx
seg002:04C3                 pop     ax
seg002:04C4                 retn
seg002:04C4 sub_113CE       endp
seg002:04C4
seg002:04C5
seg002:04C5 ; =============== S U B R O U T I N E =======================================
seg002:04C5
seg002:04C5
seg002:04C5 do_sth_with_keyboard proc near          ; CODE XREF: sub_1266E+D↓p
seg002:04C5                                         ; sub_1266E+17↓p
seg002:04C5                 push    ax
seg002:04C6
seg002:04C6 loc_11406:                              ; CODE XREF: do_sth_with_keyboard+5↓j
seg002:04C6                                         ; do_sth_with_keyboard+D↓j
seg002:04C6                 in      al, 61h         ; PC/XT PPI port B bits:
seg002:04C6                                         ; 0: Tmr 2 gate ═╦═► OR 03H=spkr ON
seg002:04C6                                         ; 1: Tmr 2 data ═╝  AND 0fcH=spkr OFF
seg002:04C6                                         ; 3: 1=read high switches
seg002:04C6                                         ; 4: 0=enable RAM parity checking
seg002:04C6                                         ; 5: 0=enable I/O channel check
seg002:04C6                                         ; 6: 0=hold keyboard clock low
seg002:04C6                                         ; 7: 0=enable kbrd
seg002:04C8                 test    al, 10h
seg002:04CA                 jnz     short loc_11406
seg002:04CC
seg002:04CC loc_1140C:                              ; CODE XREF: do_sth_with_keyboard+B↓j
seg002:04CC                 in      al, 61h         ; PC/XT PPI port B bits:
seg002:04CC                                         ; 0: Tmr 2 gate ═╦═► OR 03H=spkr ON
seg002:04CC                                         ; 1: Tmr 2 data ═╝  AND 0fcH=spkr OFF
seg002:04CC                                         ; 3: 1=read high switches
seg002:04CC                                         ; 4: 0=enable RAM parity checking
seg002:04CC                                         ; 5: 0=enable I/O channel check
seg002:04CC                                         ; 6: 0=hold keyboard clock low
seg002:04CC                                         ; 7: 0=enable kbrd
seg002:04CE                 test    al, 10h
seg002:04D0                 jz      short loc_1140C
seg002:04D2                 loop    loc_11406
seg002:04D4                 pop     ax
seg002:04D5                 retn
seg002:04D5 do_sth_with_keyboard endp
seg002:04D5
seg002:04D6
seg002:04D6 ; =============== S U B R O U T I N E =======================================
seg002:04D6
seg002:04D6
seg002:04D6 sub_11416       proc near               ; CODE XREF: sub_11213:loc_11229↑p
seg002:04D6                                         ; sub_11292+5↑p
seg002:04D6                 mov     word ptr ds:23AAh, 0
seg002:04DC                 mov     word ptr ds:23A1h, 0
seg002:04E2                 mov     word ptr ds:23B0h, 100h
seg002:04E8                 push    word ptr ds:233Ah
seg002:04EC                 pop     word ptr ds:2338h
seg002:04F0                 call    sub_11446
seg002:04F3                 retn
seg002:04F3 sub_11416       endp
seg002:04F3
seg002:04F4
seg002:04F4 ; =============== S U B R O U T I N E =======================================
seg002:04F4
seg002:04F4
seg002:04F4 sub_11434       proc near               ; CODE XREF: sub_11213+19↑p
seg002:04F4                                         ; sub_11292+8↑p ...
seg002:04F4                 call    sub_12383
seg002:04F7                 or      ax, ax
seg002:04F9                 jnz     short locret_11445
seg002:04FB                 call    sub_12363
seg002:04FE                 mov     byte ptr ds:22F6h, 1
seg002:0503                 xor     ax, ax
seg002:0505
seg002:0505 locret_11445:                           ; CODE XREF: sub_11434+5↑j
seg002:0505                 retn
seg002:0505 sub_11434       endp
seg002:0505
seg002:0506
seg002:0506 ; =============== S U B R O U T I N E =======================================
seg002:0506
seg002:0506
seg002:0506 sub_11446       proc near               ; CODE XREF: sub_11416+1A↑p
seg002:0506                                         ; sub_116AF+20↓p
seg002:0506                 push    di
seg002:0507                 push    si
seg002:0508                 mov     cx, 8
seg002:050B                 mov     si, ds:2338h
seg002:050F                 shl     si, 1
seg002:0511                 shl     si, 1
seg002:0513                 shl     si, 1
seg002:0515                 shl     si, 1
seg002:0517                 add     si, 2352h
seg002:051B                 mov     di, 2342h
seg002:051E                 cld
seg002:051F                 rep movsw
seg002:0521                 pop     si
seg002:0522                 pop     di
seg002:0523                 retn
seg002:0523 sub_11446       endp
seg002:0523
seg002:0524
seg002:0524 ; =============== S U B R O U T I N E =======================================
seg002:0524
seg002:0524
seg002:0524 sub_11464       proc near               ; CODE XREF: sub_11292+2↑p
seg002:0524                                         ; sub_11484+12↓p ...
seg002:0524                 push    ax
seg002:0525                 call    sub_12373
seg002:0528                 call    sub_123A2
seg002:052B                 mov     ax, 0
seg002:052E                 call    sub_1173B
seg002:0531                 mov     ax, ds:2071h
seg002:0534                 call    sub_118DD
seg002:0537                 pop     ax
seg002:0538                 retn
seg002:0538 sub_11464       endp
seg002:0538
seg002:0539
seg002:0539 ; =============== S U B R O U T I N E =======================================
seg002:0539
seg002:0539
seg002:0539 sub_11479       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:0539                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:0539                 xchg    dx, ds:22E2h
seg002:053D                 xchg    ax, ds:22E0h
seg002:0541                 xor     ax, ax
seg002:0543                 retn
seg002:0543 sub_11479       endp
seg002:0543
seg002:0544
seg002:0544 ; =============== S U B R O U T I N E =======================================
seg002:0544
seg002:0544
seg002:0544 sub_11484       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:0544                                         ; sub_1160E+3D↓p
seg002:0544                                         ; DATA XREF: ...
seg002:0544                 pushf
seg002:0545                 cli
seg002:0546                 push    es
seg002:0547                 push    di
seg002:0548                 cmp     byte ptr ds:22DEh, 1
seg002:054D                 jz      short loc_11499
seg002:054F                 cmp     word ptr ds:2397h, 0
seg002:0554                 jz      short loc_11499
seg002:0556                 call    sub_11464
seg002:0559
seg002:0559 loc_11499:                              ; CODE XREF: sub_11484+9↑j
seg002:0559                                         ; sub_11484+10↑j
seg002:0559                 mov     word ptr ds:2392h, 0
seg002:055F                 mov     ds:2335h, dx
seg002:0563                 mov     ds:2333h, ax
seg002:0566                 mov     es, dx
seg002:0568                 mov     di, ax
seg002:056A                 call    sub_1176C
seg002:056D                 cmp     dx, 4D54h
seg002:0571                 jz      short loc_114B6
seg002:0573                 jmp     loc_11575
seg002:0576 ; ---------------------------------------------------------------------------
seg002:0576
seg002:0576 loc_114B6:                              ; CODE XREF: sub_11484+2D↑j
seg002:0576                 cmp     ax, 6864h
seg002:0579                 jz      short loc_114BE
seg002:057B                 jmp     loc_11575
seg002:057E ; ---------------------------------------------------------------------------
seg002:057E
seg002:057E loc_114BE:                              ; CODE XREF: sub_11484+35↑j
seg002:057E                 call    sub_1176C
seg002:0581                 call    sub_11776
seg002:0584                 cmp     ax, 2
seg002:0587                 jb      short loc_114CC
seg002:0589                 jmp     loc_11575
seg002:058C ; ---------------------------------------------------------------------------
seg002:058C
seg002:058C loc_114CC:                              ; CODE XREF: sub_11484+43↑j
seg002:058C                 call    sub_11776
seg002:058F                 mov     ds:239Fh, ax
seg002:0592                 call    sub_11776
seg002:0595                 or      ah, ah
seg002:0597                 js      short loc_11503
seg002:0599                 mov     ds:239Bh, ax
seg002:059C                 mov     byte ptr ds:23EDh, 0
seg002:05A1                 mov     word ptr ds:23B2h, 0
seg002:05A7                 jmp     short loc_1150C
seg002:05A7 ; ---------------------------------------------------------------------------
seg002:05A9                 db 34h, 12h, 86h, 0E4h, 0CAh, 0C2h, 0E8h, 0D2h, 0ECh, 0CAh
seg002:05A9                 db 40h, 0A8h, 0CAh, 0C6h, 0D0h, 0DCh, 0DEh, 0D8h, 0DEh
seg002:05A9                 db 0CEh, 0F2h, 40h, 98h, 0E8h, 0C8h, 5Ch
seg002:05C3 ; ---------------------------------------------------------------------------
seg002:05C3
seg002:05C3 loc_11503:                              ; CODE XREF: sub_11484+53↑j
seg002:05C3                 neg     ah
seg002:05C5                 mul     ah
seg002:05C7                 sub     dx, dx
seg002:05C9                 call    sub_11816
seg002:05CC
seg002:05CC loc_1150C:                              ; CODE XREF: sub_11484+63↑j
seg002:05CC                 mov     cx, ds:239Fh
seg002:05D0                 cmp     cx, 41h ; 'A'
seg002:05D3                 jb      short loc_11518
seg002:05D5                 mov     cx, 41h ; 'A'
seg002:05D8
seg002:05D8 loc_11518:                              ; CODE XREF: sub_11484+8F↑j
seg002:05D8                 mov     si, ds:2A08h
seg002:05DC                 dec     cx
seg002:05DD                 jcxz    short loc_11529
seg002:05DF
seg002:05DF loc_1151F:                              ; CODE XREF: sub_11484+A3↓j
seg002:05DF                 mov     byte ptr [si+9], 1
seg002:05E3                 add     si, ds:2A06h
seg002:05E7                 loop    loc_1151F
seg002:05E9
seg002:05E9 loc_11529:                              ; CODE XREF: sub_11484+99↑j
seg002:05E9                 mov     byte ptr [si+9], 81h
seg002:05ED                 mov     si, ds:2A08h
seg002:05F1
seg002:05F1 loc_11531:                              ; CODE XREF: sub_11484+E5↓j
seg002:05F1                 call    sub_1176C
seg002:05F4                 cmp     ax, 726Bh
seg002:05F7                 jnz     short loc_11575
seg002:05F9                 cmp     dx, 4D54h
seg002:05FD                 jnz     short loc_11575
seg002:05FF                 call    sub_1176C
seg002:0602                 push    di
seg002:0603                 push    es
seg002:0604                 push    ax
seg002:0605                 push    dx
seg002:0606                 call    sub_1177F
seg002:0609                 mov     [si], di
seg002:060B                 mov     word ptr [si+2], es
seg002:060E                 mov     [si+4], ax
seg002:0611                 mov     [si+6], dx
seg002:0614                 pop     dx
seg002:0615                 pop     ax
seg002:0616                 pop     es
seg002:0617                 pop     di
seg002:0618                 test    byte ptr [si+9], 80h
seg002:061C                 jnz     short loc_1156B
seg002:061E                 call    sub_117E1
seg002:0621                 mov     byte ptr [si+9], 1
seg002:0625                 add     si, ds:2A06h
seg002:0629                 jmp     short loc_11531
seg002:062B ; ---------------------------------------------------------------------------
seg002:062B
seg002:062B loc_1156B:                              ; CODE XREF: sub_11484+D8↑j
seg002:062B                 mov     word ptr ds:2392h, 1
seg002:0631                 sub     ax, ax
seg002:0633                 jmp     short loc_11578
seg002:0635 ; ---------------------------------------------------------------------------
seg002:0635
seg002:0635 loc_11575:                              ; CODE XREF: sub_11484+2F↑j
seg002:0635                                         ; sub_11484+37↑j ...
seg002:0635                 mov     ax, 1
seg002:0638
seg002:0638 loc_11578:                              ; CODE XREF: sub_11484+EF↑j
seg002:0638                 pop     di
seg002:0639                 pop     es
seg002:063A                 popf
seg002:063B                 retn
seg002:063B sub_11484       endp
seg002:063B
seg002:063C
seg002:063C ; =============== S U B R O U T I N E =======================================
seg002:063C
seg002:063C
seg002:063C sub_1157C       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:063C                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:063C                 mov     ax, 0FFFFh
seg002:063F                 cmp     word ptr ds:2392h, 0
seg002:0644                 jz      short locret_11597
seg002:0646                 call    sub_12383
seg002:0649                 call    sub_12363
seg002:064C                 call    sub_11946
seg002:064F                 mov     ax, 1
seg002:0652                 call    sub_1173B
seg002:0655                 sub     ax, ax
seg002:0657
seg002:0657 locret_11597:                           ; CODE XREF: sub_1157C+8↑j
seg002:0657                 retn
seg002:0657 sub_1157C       endp
seg002:0657
seg002:0658
seg002:0658 ; =============== S U B R O U T I N E =======================================
seg002:0658
seg002:0658
seg002:0658 sub_11598       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:0658                                         ; sub_11598+5↓j
seg002:0658                                         ; DATA XREF: ...
seg002:0658                 cmp     byte ptr ds:2396h, 1
seg002:065D                 jz      short sub_11598
seg002:065F                 pushf
seg002:0660                 cli
seg002:0661                 call    sub_11464
seg002:0664                 mov     word ptr ds:2392h, 0
seg002:066A                 popf
seg002:066B                 retn
seg002:066B sub_11598       endp
seg002:066B
seg002:066C
seg002:066C ; =============== S U B R O U T I N E =======================================
seg002:066C
seg002:066C
seg002:066C sub_115AC       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:066C                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:066C                 cmp     word ptr ds:2397h, 1
seg002:0671                 jnz     short loc_115C0
seg002:0673                 call    sub_12373
seg002:0676                 mov     ax, 2
seg002:0679                 call    sub_1173B
seg002:067C                 xor     ax, ax
seg002:067E                 jmp     short locret_115C3
seg002:0680 ; ---------------------------------------------------------------------------
seg002:0680
seg002:0680 loc_115C0:                              ; CODE XREF: sub_115AC+5↑j
seg002:0680                 mov     ax, 1
seg002:0683
seg002:0683 locret_115C3:                           ; CODE XREF: sub_115AC+12↑j
seg002:0683                 retn
seg002:0683 sub_115AC       endp
seg002:0683
seg002:0684
seg002:0684 ; =============== S U B R O U T I N E =======================================
seg002:0684
seg002:0684
seg002:0684 sub_115C4       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:0684                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:0684                 cmp     word ptr ds:2397h, 2
seg002:0689                 jnz     short loc_115DB
seg002:068B                 call    sub_12363
seg002:068E                 call    sub_1160E
seg002:0691                 mov     ax, 1
seg002:0694                 call    sub_1173B
seg002:0697                 xor     ax, ax
seg002:0699                 jmp     short locret_115DE
seg002:069B ; ---------------------------------------------------------------------------
seg002:069B
seg002:069B loc_115DB:                              ; CODE XREF: sub_115C4+5↑j
seg002:069B                 mov     ax, 1
seg002:069E
seg002:069E locret_115DE:                           ; CODE XREF: sub_115C4+15↑j
seg002:069E                 retn
seg002:069E sub_115C4       endp
seg002:069E
seg002:069F
seg002:069F ; =============== S U B R O U T I N E =======================================
seg002:069F
seg002:069F
seg002:069F sub_115DF       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:069F                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:069F                 push    di
seg002:06A0                 push    si
seg002:06A1                 push    es
seg002:06A2                 push    ds
seg002:06A3                 mov     si, ax
seg002:06A5                 mov     ds, dx
seg002:06A7                 mov     cx, 8
seg002:06AA                 mov     di, 3
seg002:06AD                 shl     di, 1
seg002:06AF                 shl     di, 1
seg002:06B1                 shl     di, 1
seg002:06B3                 shl     di, 1
seg002:06B5                 add     di, 2352h
seg002:06B9                 cld
seg002:06BA                 rep movsw
seg002:06BC                 pop     ds
seg002:06BD                 mov     byte ptr ds:2337h, 1
seg002:06C2                 mov     ax, 3
seg002:06C5                 call    sub_116AF
seg002:06C8                 xor     ax, ax
seg002:06CA                 pop     es
seg002:06CB                 pop     si
seg002:06CC                 pop     di
seg002:06CD                 retn
seg002:06CD sub_115DF       endp
seg002:06CD
seg002:06CE
seg002:06CE ; =============== S U B R O U T I N E =======================================
seg002:06CE
seg002:06CE
seg002:06CE sub_1160E       proc near               ; CODE XREF: sub_115C4+A↑p
seg002:06CE                                         ; sub_116AF+26↓p ...
seg002:06CE                 push    cx
seg002:06CF                 push    bx
seg002:06D0                 push    si
seg002:06D1                 push    di
seg002:06D2                 pushf
seg002:06D3                 cli
seg002:06D4                 cmp     word ptr ds:2392h, 0
seg002:06D9                 jnz     short loc_1161E
seg002:06DB                 jmp     loc_116A5
seg002:06DE ; ---------------------------------------------------------------------------
seg002:06DE
seg002:06DE loc_1161E:                              ; CODE XREF: sub_1160E+B↑j
seg002:06DE                 mov     ax, ds:2397h
seg002:06E1                 mov     ds:2399h, ax
seg002:06E4                 mov     ax, 2
seg002:06E7                 call    sub_1173B
seg002:06EA                 mov     byte ptr ds:22DEh, 1
seg002:06EF                 push    word ptr ds:2A08h
seg002:06F3                 mov     word ptr ds:2A08h, 2678h
seg002:06F9                 push    word ptr ds:2A06h
seg002:06FD                 mov     word ptr ds:2A06h, 0Eh
seg002:0703                 mov     dx, ds:2335h
seg002:0707                 mov     ax, ds:2333h
seg002:070A                 sti
seg002:070B                 call    sub_11484
seg002:070E                 mov     si, 23EEh
seg002:0711                 mov     bx, 2678h
seg002:0714
seg002:0714 loc_11654:                              ; CODE XREF: sub_1160E+5D↓j
seg002:0714                 mov     ax, [si]
seg002:0716                 mov     [bx+0Ah], ax
seg002:0719                 mov     ax, [si+2]
seg002:071C                 mov     [bx+0Ch], ax
seg002:071F                 test    byte ptr [si+9], 80h
seg002:0723                 jnz     short loc_1166D
seg002:0725                 add     si, 0Ah
seg002:0728                 add     bx, 0Eh
seg002:072B                 jmp     short loc_11654
seg002:072D ; ---------------------------------------------------------------------------
seg002:072D
seg002:072D loc_1166D:                              ; CODE XREF: sub_1160E+55↑j
seg002:072D                 mov     byte ptr ds:22DFh, 0
seg002:0732                 mov     word ptr ds:23B6h, 0FFFFh
seg002:0738                 push    word ptr ds:23B4h
seg002:073C                 mov     word ptr ds:23B4h, 1
seg002:0742
seg002:0742 loc_11682:                              ; CODE XREF: sub_1160E+7E↓j
seg002:0742                 call    sub_11946
seg002:0745                 cmp     byte ptr ds:22DFh, 1
seg002:074A                 jz      short loc_1168E
seg002:074C                 jmp     short loc_11682
seg002:074E ; ---------------------------------------------------------------------------
seg002:074E
seg002:074E loc_1168E:                              ; CODE XREF: sub_1160E+7C↑j
seg002:074E                 pop     word ptr ds:23B4h
seg002:0752                 pop     word ptr ds:2A06h
seg002:0756                 pop     word ptr ds:2A08h
seg002:075A                 mov     byte ptr ds:22DEh, 0
seg002:075F                 mov     ax, ds:2399h
seg002:0762                 call    sub_1173B
seg002:0765
seg002:0765 loc_116A5:                              ; CODE XREF: sub_1160E+D↑j
seg002:0765                 popf
seg002:0766                 pop     di
seg002:0767                 pop     si
seg002:0768                 pop     bx
seg002:0769                 pop     cx
seg002:076A                 retn
seg002:076A sub_1160E       endp
seg002:076A
seg002:076B
seg002:076B ; =============== S U B R O U T I N E =======================================
seg002:076B
seg002:076B
seg002:076B sub_116AB       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:076B                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:076B                 mov     ax, ds:2338h
seg002:076E                 retn
seg002:076E sub_116AB       endp
seg002:076E
seg002:076F
seg002:076F ; =============== S U B R O U T I N E =======================================
seg002:076F
seg002:076F
seg002:076F sub_116AF       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:076F                                         ; sub_115DF+26↑p
seg002:076F                                         ; DATA XREF: ...
seg002:076F                 pushf
seg002:0770                 cli
seg002:0771                 cmp     byte ptr ds:22F6h, 0
seg002:0776                 jz      short loc_116E1
seg002:0778                 cmp     ax, 3
seg002:077B                 jb      short loc_116C9
seg002:077D                 cmp     ax, 3
seg002:0780                 jnz     short loc_116DC
seg002:0782                 cmp     byte ptr ds:2337h, 0
seg002:0787                 jz      short loc_116DC
seg002:0789
seg002:0789 loc_116C9:                              ; CODE XREF: sub_116AF+C↑j
seg002:0789                 call    sub_12373
seg002:078C                 mov     ds:2338h, ax
seg002:078F                 call    sub_11446
seg002:0792                 call    sub_12363
seg002:0795                 call    sub_1160E
seg002:0798                 xor     ax, ax
seg002:079A                 jmp     short loc_116E4
seg002:079C ; ---------------------------------------------------------------------------
seg002:079C
seg002:079C loc_116DC:                              ; CODE XREF: sub_116AF+11↑j
seg002:079C                                         ; sub_116AF+18↑j
seg002:079C                 mov     ax, 2
seg002:079F                 jmp     short loc_116E4
seg002:07A1 ; ---------------------------------------------------------------------------
seg002:07A1
seg002:07A1 loc_116E1:                              ; CODE XREF: sub_116AF+7↑j
seg002:07A1                 mov     ax, 1
seg002:07A4
seg002:07A4 loc_116E4:                              ; CODE XREF: sub_116AF+2B↑j
seg002:07A4                                         ; sub_116AF+30↑j
seg002:07A4                 popf
seg002:07A5                 retn
seg002:07A5 sub_116AF       endp
seg002:07A5
seg002:07A6
seg002:07A6 ; =============== S U B R O U T I N E =======================================
seg002:07A6
seg002:07A6
seg002:07A6 sub_116E6       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:07A6                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:07A6                 mov     ax, ds:233Eh
seg002:07A9                 retn
seg002:07A9 sub_116E6       endp
seg002:07A9
seg002:07AA
seg002:07AA ; =============== S U B R O U T I N E =======================================
seg002:07AA
seg002:07AA
seg002:07AA sub_116EA       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:07AA                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:07AA                 push    bx
seg002:07AB                 pushf
seg002:07AC                 cli
seg002:07AD                 cmp     byte ptr ds:22F6h, 0
seg002:07B2                 jz      short loc_11735
seg002:07B4                 or      ax, ax
seg002:07B6                 jz      short loc_116FD
seg002:07B8                 cmp     ax, 1
seg002:07BB                 jnz     short loc_11730
seg002:07BD
seg002:07BD loc_116FD:                              ; CODE XREF: sub_116EA+C↑j
seg002:07BD                 call    sub_12373
seg002:07C0                 mov     bx, ds:233Eh
seg002:07C4                 mov     ds:233Ch, bx
seg002:07C8                 mov     ds:233Eh, ax
seg002:07CB                 call    sub_12328
seg002:07CE                 or      ax, ax
seg002:07D0                 jz      short loc_11715
seg002:07D2                 inc     ax
seg002:07D3                 jmp     short loc_1171C
seg002:07D5 ; ---------------------------------------------------------------------------
seg002:07D5
seg002:07D5 loc_11715:                              ; CODE XREF: sub_116EA+26↑j
seg002:07D5                 call    sub_11434
seg002:07D8                 or      ax, ax
seg002:07DA                 jz      short loc_11729
seg002:07DC
seg002:07DC loc_1171C:                              ; CODE XREF: sub_116EA+29↑j
seg002:07DC                 push    ax
seg002:07DD                 mov     bx, ds:233Ch
seg002:07E1                 mov     ds:233Eh, bx
seg002:07E5                 call    sub_11434
seg002:07E8                 pop     ax
seg002:07E9
seg002:07E9 loc_11729:                              ; CODE XREF: sub_116EA+30↑j
seg002:07E9                 push    ax
seg002:07EA                 call    sub_1160E
seg002:07ED                 pop     ax
seg002:07EE                 jmp     short loc_11738
seg002:07F0 ; ---------------------------------------------------------------------------
seg002:07F0
seg002:07F0 loc_11730:                              ; CODE XREF: sub_116EA+11↑j
seg002:07F0                 mov     ax, 1
seg002:07F3                 jmp     short loc_11738
seg002:07F5 ; ---------------------------------------------------------------------------
seg002:07F5
seg002:07F5 loc_11735:                              ; CODE XREF: sub_116EA+8↑j
seg002:07F5                 mov     ax, 1
seg002:07F8
seg002:07F8 loc_11738:                              ; CODE XREF: sub_116EA+44↑j
seg002:07F8                                         ; sub_116EA+49↑j
seg002:07F8                 popf
seg002:07F9                 pop     bx
seg002:07FA                 retn
seg002:07FA sub_116EA       endp
seg002:07FA
seg002:07FB
seg002:07FB ; =============== S U B R O U T I N E =======================================
seg002:07FB
seg002:07FB
seg002:07FB sub_1173B       proc near               ; CODE XREF: sub_11464+A↑p
seg002:07FB                                         ; sub_1157C+16↑p ...
seg002:07FB                 push    es
seg002:07FC                 push    di
seg002:07FD                 cmp     word ptr ds:22E2h, 0
seg002:0802                 jnz     short loc_1174D
seg002:0804                 cmp     word ptr ds:22E0h, 0
seg002:0809                 jnz     short loc_1174D
seg002:080B                 jmp     short loc_11754
seg002:080D ; ---------------------------------------------------------------------------
seg002:080D
seg002:080D loc_1174D:                              ; CODE XREF: sub_1173B+7↑j
seg002:080D                                         ; sub_1173B+E↑j
seg002:080D                 les     di, ds:22E0h
seg002:0811                 mov     es:[di], ax
seg002:0814
seg002:0814 loc_11754:                              ; CODE XREF: sub_1173B+10↑j
seg002:0814                 mov     ds:2397h, ax
seg002:0817                 pop     di
seg002:0818                 pop     es
seg002:0819                 retn
seg002:0819 sub_1173B       endp
seg002:0819
seg002:081A
seg002:081A ; =============== S U B R O U T I N E =======================================
seg002:081A
seg002:081A
seg002:081A sub_1175A       proc near               ; CODE XREF: sub_1176C↓p
seg002:081A                                         ; sub_1176C+5↓p ...
seg002:081A                 mov     al, es:[di]
seg002:081D                 inc     di
seg002:081E                 or      di, di
seg002:0820                 jnz     short locret_1176B
seg002:0822                 push    ax
seg002:0823                 mov     ax, es
seg002:0825                 add     ax, 1000h
seg002:0828                 mov     es, ax
seg002:082A                 assume es:nothing
seg002:082A                 pop     ax
seg002:082B
seg002:082B locret_1176B:                           ; CODE XREF: sub_1175A+6↑j
seg002:082B                 retn
seg002:082B sub_1175A       endp
seg002:082B
seg002:082C
seg002:082C ; =============== S U B R O U T I N E =======================================
seg002:082C
seg002:082C
seg002:082C sub_1176C       proc near               ; CODE XREF: sub_11484+26↑p
seg002:082C                                         ; sub_11484:loc_114BE↑p ...
seg002:082C                 call    sub_1175A
seg002:082F                 mov     dh, al
seg002:0831                 call    sub_1175A
seg002:0834                 mov     dl, al
seg002:0834 sub_1176C       endp
seg002:0834
seg002:0836
seg002:0836 ; =============== S U B R O U T I N E =======================================
seg002:0836
seg002:0836
seg002:0836 sub_11776       proc near               ; CODE XREF: sub_11484+3D↑p
seg002:0836                                         ; sub_11484:loc_114CC↑p ...
seg002:0836                 call    sub_1175A
seg002:0839                 mov     ah, al
seg002:083B                 call    sub_1175A
seg002:083E                 retn
seg002:083E sub_11776       endp
seg002:083E
seg002:083F
seg002:083F ; =============== S U B R O U T I N E =======================================
seg002:083F
seg002:083F
seg002:083F sub_1177F       proc near               ; CODE XREF: sub_11484+C2↑p
seg002:083F                                         ; sub_11946:loc_11A20↓p ...
seg002:083F                 sub     dx, dx
seg002:0841                 sub     ah, ah
seg002:0843                 call    sub_1175A
seg002:0846                 or      al, al
seg002:0848                 jns     short locret_117E0
seg002:084A                 mov     ah, al
seg002:084C                 and     ah, 7Fh
seg002:084F                 call    sub_1175A
seg002:0852                 or      al, al
seg002:0854                 js      short loc_1179C
seg002:0856                 shl     al, 1
seg002:0858                 shr     ax, 1
seg002:085A                 jmp     short locret_117E0
seg002:085C ; ---------------------------------------------------------------------------
seg002:085C
seg002:085C loc_1179C:                              ; CODE XREF: sub_1177F+15↑j
seg002:085C                 mov     dl, ah
seg002:085E                 mov     ah, al
seg002:0860                 and     ah, 7Fh
seg002:0863                 call    sub_1175A
seg002:0866                 or      al, al
seg002:0868                 js      short loc_117BF
seg002:086A                 shl     al, 1
seg002:086C                 shr     ax, 1
seg002:086E                 ror     dl, 1
seg002:0870                 ror     dl, 1
seg002:0872                 mov     dh, dl
seg002:0874                 and     dh, 0C0h
seg002:0877                 or      ah, dh
seg002:0879                 xor     dl, dh
seg002:087B                 sub     dh, dh
seg002:087D                 jmp     short locret_117E0
seg002:087F ; ---------------------------------------------------------------------------
seg002:087F
seg002:087F loc_117BF:                              ; CODE XREF: sub_1177F+29↑j
seg002:087F                 mov     dh, dl
seg002:0881                 mov     dl, ah
seg002:0883                 mov     ah, al
seg002:0885                 and     ah, 7Fh
seg002:0888                 call    sub_1175A
seg002:088B                 shl     dl, 1
seg002:088D                 shl     al, 1
seg002:088F                 shr     ax, 1
seg002:0891                 ror     dx, 1
seg002:0893                 ror     dx, 1
seg002:0895                 ror     dx, 1
seg002:0897                 mov     ch, dh
seg002:0899                 and     ch, 3Fh
seg002:089C                 or      ah, ch
seg002:089E                 xor     dx, cx
seg002:08A0
seg002:08A0 locret_117E0:                           ; CODE XREF: sub_1177F+9↑j
seg002:08A0                                         ; sub_1177F+1B↑j ...
seg002:08A0                 retn
seg002:08A0 sub_1177F       endp
seg002:08A0
seg002:08A1
seg002:08A1 ; =============== S U B R O U T I N E =======================================
seg002:08A1
seg002:08A1
seg002:08A1 sub_117E1       proc near               ; CODE XREF: sub_11484+DA↑p
seg002:08A1                                         ; sub_11B7D+6↓p ...
seg002:08A1                 add     di, ax
seg002:08A3                 adc     dx, 0
seg002:08A6                 jz      short locret_117F2
seg002:08A8                 mov     ax, es
seg002:08AA
seg002:08AA loc_117EA:                              ; CODE XREF: sub_117E1+D↓j
seg002:08AA                 add     ax, 1000h
seg002:08AD                 dec     dx
seg002:08AE                 jnz     short loc_117EA
seg002:08B0                 mov     es, ax
seg002:08B2                 assume es:nothing
seg002:08B2
seg002:08B2 locret_117F2:                           ; CODE XREF: sub_117E1+5↑j
seg002:08B2                 retn
seg002:08B2 sub_117E1       endp
seg002:08B2
seg002:08B3
seg002:08B3 ; =============== S U B R O U T I N E =======================================
seg002:08B3
seg002:08B3
seg002:08B3 sub_117F3       proc near               ; CODE XREF: sub_1245A+7↓p
seg002:08B3                 push    ax
seg002:08B4                 push    si
seg002:08B5                 push    di
seg002:08B6                 push    es
seg002:08B7                 push    ds
seg002:08B8                 cmp     al, 0F0h
seg002:08BA                 jnz     short loc_117FF
seg002:08BC                 call    sub_12468
seg002:08BF
seg002:08BF loc_117FF:                              ; CODE XREF: sub_117F3+7↑j
seg002:08BF                 push    cx
seg002:08C0                 call    sub_1175A
seg002:08C3                 mov     cx, ax
seg002:08C5                 xor     ch, ch
seg002:08C7
seg002:08C7 loc_11807:                              ; CODE XREF: sub_117F3+1A↓j
seg002:08C7                 call    sub_1175A
seg002:08CA                 call    sub_12468
seg002:08CD                 loop    loc_11807
seg002:08CF                 pop     cx
seg002:08D0                 pop     ds
seg002:08D1                 pop     es
seg002:08D2                 assume es:nothing
seg002:08D2                 pop     di
seg002:08D3                 pop     si
seg002:08D4                 pop     ax
seg002:08D5                 retn
seg002:08D5 sub_117F3       endp
seg002:08D5
seg002:08D6
seg002:08D6 ; =============== S U B R O U T I N E =======================================
seg002:08D6
seg002:08D6
seg002:08D6 sub_11816       proc near               ; CODE XREF: sub_11484+85↑p
seg002:08D6                                         ; sub_11BC8+DC↓p
seg002:08D6                 push    bx
seg002:08D7                 sub     cx, cx
seg002:08D9                 mov     ds:23AEh, cx
seg002:08DD
seg002:08DD loc_1181D:                              ; CODE XREF: sub_11816+10↓j
seg002:08DD                 or      dx, dx
seg002:08DF                 jz      short loc_11828
seg002:08E1                 shr     dx, 1
seg002:08E3                 rcr     ax, 1
seg002:08E5                 inc     cx
seg002:08E6                 jmp     short loc_1181D
seg002:08E8 ; ---------------------------------------------------------------------------
seg002:08E8
seg002:08E8 loc_11828:                              ; CODE XREF: sub_11816+9↑j
seg002:08E8                 mov     bx, 180h
seg002:08EB                 cmp     ax, 13h
seg002:08EE                 jnb     short loc_11833
seg002:08F0                 mov     ax, 13h
seg002:08F3
seg002:08F3 loc_11833:                              ; CODE XREF: sub_11816+18↑j
seg002:08F3                 cmp     ax, bx
seg002:08F5                 jbe     short loc_11853
seg002:08F7                 push    di
seg002:08F8                 mov     di, ax
seg002:08FA
seg002:08FA loc_1183A:                              ; CODE XREF: sub_11816+29↓j
seg002:08FA                 inc     cx
seg002:08FB                 shr     ax, 1
seg002:08FD                 cmp     ax, bx
seg002:08FF                 ja      short loc_1183A
seg002:0901                 sub     dx, dx
seg002:0903                 xchg    ax, di
seg002:0904                 div     di
seg002:0906                 mov     ax, dx
seg002:0908                 mov     dx, di
seg002:090A                 call    sub_11875
seg002:090D                 mov     ds:23AEh, ax
seg002:0910                 mov     ax, di
seg002:0912                 pop     di
seg002:0913
seg002:0913 loc_11853:                              ; CODE XREF: sub_11816+1F↑j
seg002:0913                 mov     ds:239Dh, ax
seg002:0916                 mov     ax, 1
seg002:0919                 shl     ax, cl
seg002:091B                 mov     ds:23ACh, ax
seg002:091E                 mov     dx, 12h
seg002:0921                 mov     ax, 34DCh
seg002:0924                 div     word ptr ds:239Dh
seg002:0928                 add     dx, dx
seg002:092A                 adc     ax, 0
seg002:092D                 call    sub_1189B
seg002:0930                 call    sub_118DD
seg002:0933                 pop     bx
seg002:0934                 retn
seg002:0934 sub_11816       endp
seg002:0934
seg002:0935
seg002:0935 ; =============== S U B R O U T I N E =======================================
seg002:0935
seg002:0935
seg002:0935 sub_11875       proc near               ; CODE XREF: sub_11816+34↑p
seg002:0935                                         ; sub_11BC8+3B↓p ...
seg002:0935                 push    bx
seg002:0936                 push    cx
seg002:0937                 push    dx
seg002:0938                 sub     bx, bx
seg002:093A                 or      ax, ax
seg002:093C                 jz      short loc_11895
seg002:093E                 or      dx, dx
seg002:0940                 jz      short loc_11895
seg002:0942                 mov     cx, 8000h
seg002:0945
seg002:0945 loc_11885:                              ; CODE XREF: sub_11875+1E↓j
seg002:0945                 shl     ax, 1
seg002:0947                 jb      short loc_1188D
seg002:0949                 cmp     ax, dx
seg002:094B                 jb      short loc_11891
seg002:094D
seg002:094D loc_1188D:                              ; CODE XREF: sub_11875+12↑j
seg002:094D                 or      bx, cx
seg002:094F                 sub     ax, dx
seg002:0951
seg002:0951 loc_11891:                              ; CODE XREF: sub_11875+16↑j
seg002:0951                 shr     cx, 1
seg002:0953                 jnz     short loc_11885
seg002:0955
seg002:0955 loc_11895:                              ; CODE XREF: sub_11875+7↑j
seg002:0955                                         ; sub_11875+B↑j
seg002:0955                 mov     ax, bx
seg002:0957                 pop     dx
seg002:0958                 pop     cx
seg002:0959                 pop     bx
seg002:095A                 retn
seg002:095A sub_11875       endp
seg002:095A
seg002:095B
seg002:095B ; =============== S U B R O U T I N E =======================================
seg002:095B
seg002:095B
seg002:095B sub_1189B       proc near               ; CODE XREF: sub_11816+57↑p
seg002:095B                 mul     word ptr ds:23B0h
seg002:095F                 add     al, al
seg002:0961                 adc     ah, 0
seg002:0964                 adc     dx, 0
seg002:0967                 or      dh, dh
seg002:0969                 jz      short loc_118B1
seg002:096B                 mov     ax, 0FFFFh
seg002:096E                 stc
seg002:096F                 jmp     short locret_118BE
seg002:0971 ; ---------------------------------------------------------------------------
seg002:0971
seg002:0971 loc_118B1:                              ; CODE XREF: sub_1189B+E↑j
seg002:0971                 mov     al, dl
seg002:0973                 xchg    ah, al
seg002:0975                 cmp     ax, ds:22ECh
seg002:0979                 jnb     short locret_118BE
seg002:097B                 mov     ax, ds:22ECh
seg002:097E
seg002:097E locret_118BE:                           ; CODE XREF: sub_1189B+14↑j
seg002:097E                                         ; sub_1189B+1E↑j
seg002:097E                 retn
seg002:097E sub_1189B       endp
seg002:097E
seg002:097F
seg002:097F ; =============== S U B R O U T I N E =======================================
seg002:097F
seg002:097F
seg002:097F sub_118BF       proc near               ; CODE XREF: sub_118DD+C↓p
seg002:097F                 push    ax
seg002:0980                 push    bx
seg002:0981                 push    cx
seg002:0982                 push    dx
seg002:0983                 push    si
seg002:0984                 mov     bx, ax
seg002:0986                 mov     ax, ds:2075h
seg002:0989                 mov     cx, ds:2073h
seg002:098D                 mul     cx
seg002:098F                 div     bx
seg002:0991                 mov     ds:2077h, ax
seg002:0994                 mov     ds:2075h, ax
seg002:0997                 pop     si
seg002:0998                 pop     dx
seg002:0999                 pop     cx
seg002:099A                 pop     bx
seg002:099B                 pop     ax
seg002:099C                 retn
seg002:099C sub_118BF       endp
seg002:099C
seg002:099D
seg002:099D ; =============== S U B R O U T I N E =======================================
seg002:099D
seg002:099D
seg002:099D sub_118DD       proc near               ; CODE XREF: sub_11464+10↑p
seg002:099D                                         ; sub_11816+5A↑p ...
seg002:099D                 push    ax
seg002:099E                 push    bx
seg002:099F                 push    dx
seg002:09A0                 pushf
seg002:09A1                 cli
seg002:09A2                 cmp     word ptr ds:2394h, 0
seg002:09A7                 jz      short loc_118EC
seg002:09A9                 call    sub_118BF
seg002:09AC
seg002:09AC loc_118EC:                              ; CODE XREF: sub_118DD+A↑j
seg002:09AC                 mov     ds:2073h, ax
seg002:09AF                 mov     word ptr ds:2079h, 0
seg002:09B5                 mov     word ptr ds:207Bh, 0
seg002:09BB                 mov     bx, ds:22EAh
seg002:09BF                 mov     dx, 0
seg002:09C2                 div     bx
seg002:09C4                 mov     ax, ds:2071h
seg002:09C7                 mov     bx, ds:2073h
seg002:09CB                 mov     ds:22E8h, bx
seg002:09CF                 push    ax
seg002:09D0                 mov     dx, 0
seg002:09D3                 div     bx
seg002:09D5                 mov     ds:22E4h, ax
seg002:09D8                 mov     ds:22E6h, dx
seg002:09DC                 pop     ax
seg002:09DD                 xchg    ax, bx
seg002:09DE                 mov     ds:2073h, ax
seg002:09E1                 mov     al, 36h ; '6'
seg002:09E3                 mov     dx, 43h ; 'C'
seg002:09E6                 out     dx, al          ; Timer 8253-5 (AT: 8254.2).
seg002:09E7                 jmp     short $+2
seg002:09E9 ; ---------------------------------------------------------------------------
seg002:09E9
seg002:09E9 loc_11929:                              ; CODE XREF: sub_118DD+4A↑j
seg002:09E9                 jmp     short $+2
seg002:09EB ; ---------------------------------------------------------------------------
seg002:09EB
seg002:09EB loc_1192B:                              ; CODE XREF: sub_118DD:loc_11929↑j
seg002:09EB                 mov     al, ds:2073h
seg002:09EE                 out     40h, al         ; Timer 8253-5 (AT: 8254.2).
seg002:09F0                 jmp     short $+2
seg002:09F2 ; ---------------------------------------------------------------------------
seg002:09F2
seg002:09F2 loc_11932:                              ; CODE XREF: sub_118DD+53↑j
seg002:09F2                 jmp     short $+2
seg002:09F4 ; ---------------------------------------------------------------------------
seg002:09F4
seg002:09F4 loc_11934:                              ; CODE XREF: sub_118DD:loc_11932↑j
seg002:09F4                 mov     al, ah
seg002:09F6                 out     40h, al         ; Timer 8253-5 (AT: 8254.2).
seg002:09F8                 jmp     short $+2
seg002:09FA ; ---------------------------------------------------------------------------
seg002:09FA
seg002:09FA loc_1193A:                              ; CODE XREF: sub_118DD+5B↑j
seg002:09FA                 jmp     short $+2
seg002:09FC ; ---------------------------------------------------------------------------
seg002:09FC
seg002:09FC loc_1193C:                              ; CODE XREF: sub_118DD:loc_1193A↑j
seg002:09FC                 mov     byte ptr ds:22F7h, 1
seg002:0A01                 popf
seg002:0A02                 pop     dx
seg002:0A03                 pop     bx
seg002:0A04                 pop     ax
seg002:0A05                 retn
seg002:0A05 sub_118DD       endp
seg002:0A05
seg002:0A06
seg002:0A06 ; =============== S U B R O U T I N E =======================================
seg002:0A06
seg002:0A06
seg002:0A06 sub_11946       proc near               ; CODE XREF: sub_11044+39↑p
seg002:0A06                                         ; sub_1157C+10↑p ...
seg002:0A06                 cmp     byte ptr ds:2396h, 1
seg002:0A0B                 jnz     short loc_11950
seg002:0A0D                 jmp     locret_11A9C
seg002:0A10 ; ---------------------------------------------------------------------------
seg002:0A10
seg002:0A10 loc_11950:                              ; CODE XREF: sub_11946+5↑j
seg002:0A10                 mov     byte ptr ds:2396h, 1
seg002:0A15                 push    es
seg002:0A16                 mov     si, ds:2A08h
seg002:0A1A                 mov     byte ptr ds:23ECh, 0
seg002:0A1F                 cmp     byte ptr ds:22DEh, 1
seg002:0A24                 jz      short loc_11979
seg002:0A26                 mov     cx, ds:23AEh
seg002:0A2A                 add     ds:23B2h, cx
seg002:0A2E                 mov     ax, ds:23ACh
seg002:0A31                 adc     ax, 0
seg002:0A34                 mov     ds:23B4h, ax
seg002:0A37                 jmp     short loc_1197F
seg002:0A39 ; ---------------------------------------------------------------------------
seg002:0A39
seg002:0A39 loc_11979:                              ; CODE XREF: sub_11946+1E↑j
seg002:0A39                 mov     word ptr ds:23B6h, 0FFFFh
seg002:0A3F
seg002:0A3F loc_1197F:                              ; CODE XREF: sub_11946+31↑j
seg002:0A3F                                         ; sub_11946+125↓j
seg002:0A3F                 les     di, [si]
seg002:0A41                 test    byte ptr [si+9], 1
seg002:0A45                 jnz     short loc_1198A
seg002:0A47                 jmp     loc_11A3E
seg002:0A4A ; ---------------------------------------------------------------------------
seg002:0A4A
seg002:0A4A loc_1198A:                              ; CODE XREF: sub_11946+3F↑j
seg002:0A4A                 mov     byte ptr ds:23ECh, 1
seg002:0A4F                 cmp     word ptr [si+4], 0
seg002:0A53                 jnz     short loc_1199B
seg002:0A55                 cmp     word ptr [si+6], 0
seg002:0A59                 jz      short loc_119B5
seg002:0A5B
seg002:0A5B loc_1199B:                              ; CODE XREF: sub_11946+4D↑j
seg002:0A5B                 mov     ax, ds:23B4h
seg002:0A5E                 sub     [si+4], ax
seg002:0A61                 sbb     word ptr [si+6], 0
seg002:0A65                 js      short loc_119B5
seg002:0A67                 jz      short loc_119AC
seg002:0A69                 jmp     loc_11A3E
seg002:0A6C ; ---------------------------------------------------------------------------
seg002:0A6C
seg002:0A6C loc_119AC:                              ; CODE XREF: sub_11946+61↑j
seg002:0A6C                 cmp     word ptr [si+4], 0
seg002:0A70                 jz      short loc_119B5
seg002:0A72                 jmp     loc_11A3E
seg002:0A75 ; ---------------------------------------------------------------------------
seg002:0A75
seg002:0A75 loc_119B5:                              ; CODE XREF: sub_11946+53↑j
seg002:0A75                                         ; sub_11946+5F↑j ...
seg002:0A75                 mov     al, [si+8]
seg002:0A78                 mov     ds:2A0Ch, al
seg002:0A7B                 test    byte ptr es:[di], 80h
seg002:0A7F                 jz      short loc_119CA
seg002:0A81                 call    sub_1175A
seg002:0A84                 mov     [si+8], al
seg002:0A87                 mov     ds:2A0Ch, al
seg002:0A8A
seg002:0A8A loc_119CA:                              ; CODE XREF: sub_11946+79↑j
seg002:0A8A                 mov     bl, [si+8]
seg002:0A8D                 mov     cl, bl
seg002:0A8F                 cmp     bl, 0F0h
seg002:0A92                 jnb     short loc_119F2
seg002:0A94                 sub     bh, bh
seg002:0A96                 and     bl, 0Fh
seg002:0A99                 mov     al, [bx+2342h]
seg002:0A9D                 cbw
seg002:0A9E                 mov     ds:2340h, ax
seg002:0AA1                 push    cx
seg002:0AA2                 mov     cl, ds:2A0Ch
seg002:0AA6                 and     cl, 0F0h
seg002:0AA9                 and     al, 0Fh
seg002:0AAB                 or      cl, al
seg002:0AAD                 mov     ds:2A0Ch, cl
seg002:0AB1                 pop     cx
seg002:0AB2
seg002:0AB2 loc_119F2:                              ; CODE XREF: sub_11946+8C↑j
seg002:0AB2                 mov     bl, cl
seg002:0AB4                 and     bx, 70h
seg002:0AB7                 shr     bx, 1
seg002:0AB9                 shr     bx, 1
seg002:0ABB                 shr     bx, 1
seg002:0ABD                 call    word ptr [bx+23B8h]
seg002:0AC1                 test    byte ptr [si+9], 1
seg002:0AC5                 jz      short loc_11A3E
seg002:0AC7                 cmp     byte ptr ds:22DEh, 1
seg002:0ACC                 jnz     short loc_11A20
seg002:0ACE                 cmp     di, [si+0Ah]
seg002:0AD1                 jb      short loc_11A20
seg002:0AD3                 mov     cx, es
seg002:0AD5                 cmp     cx, [si+0Ch]
seg002:0AD8                 jb      short loc_11A20
seg002:0ADA                 and     byte ptr [si+9], 0FEh
seg002:0ADE                 jmp     short loc_11A3E
seg002:0AE0 ; ---------------------------------------------------------------------------
seg002:0AE0
seg002:0AE0 loc_11A20:                              ; CODE XREF: sub_11946+C6↑j
seg002:0AE0                                         ; sub_11946+CB↑j ...
seg002:0AE0                 call    sub_1177F
seg002:0AE3                 or      ax, ax
seg002:0AE5                 jnz     short loc_11A2B
seg002:0AE7                 or      dx, dx
seg002:0AE9                 jz      short loc_119B5
seg002:0AEB
seg002:0AEB loc_11A2B:                              ; CODE XREF: sub_11946+DF↑j
seg002:0AEB                 add     [si+4], ax
seg002:0AEE                 adc     [si+6], dx
seg002:0AF1                 js      short loc_119B5
seg002:0AF3                 jnz     short loc_11A3E
seg002:0AF5                 cmp     word ptr [si+4], 0
seg002:0AF9                 jnz     short loc_11A3E
seg002:0AFB                 jmp     loc_119B5
seg002:0AFE ; ---------------------------------------------------------------------------
seg002:0AFE
seg002:0AFE loc_11A3E:                              ; CODE XREF: sub_11946+41↑j
seg002:0AFE                                         ; sub_11946+63↑j ...
seg002:0AFE                 cmp     byte ptr ds:22DEh, 1
seg002:0B03                 jnz     short loc_11A5C
seg002:0B05                 mov     ax, [si+4]
seg002:0B08                 mov     dx, [si+6]
seg002:0B0B                 or      dx, dx
seg002:0B0D                 jnz     short loc_11A5C
seg002:0B0F                 or      ax, ax
seg002:0B11                 jz      short loc_11A5C
seg002:0B13                 cmp     ax, ds:23B6h
seg002:0B17                 jnb     short loc_11A5C
seg002:0B19                 mov     ds:23B6h, ax
seg002:0B1C
seg002:0B1C loc_11A5C:                              ; CODE XREF: sub_11946+FD↑j
seg002:0B1C                                         ; sub_11946+107↑j ...
seg002:0B1C                 test    byte ptr [si+9], 80h
seg002:0B20                 jnz     short loc_11A6E
seg002:0B22                 mov     [si], di
seg002:0B24                 mov     word ptr [si+2], es
seg002:0B27                 add     si, ds:2A06h
seg002:0B2B                 jmp     loc_1197F
seg002:0B2E ; ---------------------------------------------------------------------------
seg002:0B2E
seg002:0B2E loc_11A6E:                              ; CODE XREF: sub_11946+11A↑j
seg002:0B2E                 cmp     byte ptr ds:22DEh, 1
seg002:0B33                 jnz     short loc_11A7B
seg002:0B35                 mov     ax, ds:23B6h
seg002:0B38                 mov     ds:23B4h, ax
seg002:0B3B
seg002:0B3B loc_11A7B:                              ; CODE XREF: sub_11946+12D↑j
seg002:0B3B                 mov     [si], di
seg002:0B3D                 mov     word ptr [si+2], es
seg002:0B40                 cmp     byte ptr ds:23ECh, 0
seg002:0B45                 jnz     short loc_11A96
seg002:0B47                 mov     byte ptr ds:22DFh, 1
seg002:0B4C                 cmp     byte ptr ds:22DEh, 1
seg002:0B51                 jz      short loc_11A96
seg002:0B53                 call    sub_11464
seg002:0B56
seg002:0B56 loc_11A96:                              ; CODE XREF: sub_11946+13F↑j
seg002:0B56                                         ; sub_11946+14B↑j
seg002:0B56                 pop     es
seg002:0B57                 mov     byte ptr ds:2396h, 0
seg002:0B5C
seg002:0B5C locret_11A9C:                           ; CODE XREF: sub_11946+7↑j
seg002:0B5C                 retn
seg002:0B5C sub_11946       endp
seg002:0B5C
seg002:0B5D
seg002:0B5D ; =============== S U B R O U T I N E =======================================
seg002:0B5D
seg002:0B5D
seg002:0B5D sub_11A9D       proc near
seg002:0B5D                 push    dx
seg002:0B5E                 call    sub_1175A
seg002:0B61                 mov     ah, al
seg002:0B63                 call    sub_1175A
seg002:0B66                 cmp     byte ptr ds:22DEh, 1
seg002:0B6B                 jz      short loc_11AD5
seg002:0B6D                 cmp     word ptr ds:2340h, 0FFFFh
seg002:0B72                 jz      short loc_11AD5
seg002:0B74                 cmp     word ptr ds:23AAh, 0
seg002:0B79                 jz      short loc_11AD2
seg002:0B7B                 cmp     word ptr ds:2340h, 9
seg002:0B80                 jz      short loc_11AD2
seg002:0B82                 jg      short loc_11ACE
seg002:0B84                 mov     dx, ds:23AAh
seg002:0B88                 neg     dx
seg002:0B8A                 sub     ah, dl
seg002:0B8C                 jmp     short loc_11AD2
seg002:0B8E ; ---------------------------------------------------------------------------
seg002:0B8E
seg002:0B8E loc_11ACE:                              ; CODE XREF: sub_11A9D+25↑j
seg002:0B8E                 add     ah, ds:23AAh
seg002:0B92
seg002:0B92 loc_11AD2:                              ; CODE XREF: sub_11A9D+1C↑j
seg002:0B92                                         ; sub_11A9D+23↑j ...
seg002:0B92                 call    sub_123C8
seg002:0B95
seg002:0B95 loc_11AD5:                              ; CODE XREF: sub_11A9D+E↑j
seg002:0B95                                         ; sub_11A9D+15↑j
seg002:0B95                 pop     dx
seg002:0B96                 retn
seg002:0B96 sub_11A9D       endp
seg002:0B96
seg002:0B97 ; ---------------------------------------------------------------------------
seg002:0B97                 push    dx
seg002:0B98                 call    sub_1175A
seg002:0B9B                 mov     ah, al
seg002:0B9D                 call    sub_1175A
seg002:0BA0                 cmp     byte ptr ds:22DEh, 1
seg002:0BA5                 jz      short loc_11B14
seg002:0BA7                 cmp     word ptr ds:2340h, 0FFFFh
seg002:0BAC                 jz      short loc_11B14
seg002:0BAE                 cmp     word ptr ds:23AAh, 0
seg002:0BB3                 jz      short loc_11B0C
seg002:0BB5                 cmp     word ptr ds:2340h, 9
seg002:0BBA                 jz      short loc_11B0C
seg002:0BBC                 jg      short sub_11B08
seg002:0BBE                 mov     dx, ds:23AAh
seg002:0BC2                 neg     dx
seg002:0BC4                 sub     ah, dl
seg002:0BC6                 jmp     short loc_11B0C
seg002:0BC8
seg002:0BC8 ; =============== S U B R O U T I N E =======================================
seg002:0BC8
seg002:0BC8
seg002:0BC8 sub_11B08       proc near               ; CODE XREF: seg002:0BBC↑j
seg002:0BC8                 add     ah, ds:23AAh
seg002:0BCC
seg002:0BCC loc_11B0C:                              ; CODE XREF: seg002:0BB3↑j
seg002:0BCC                                         ; seg002:0BBA↑j ...
seg002:0BCC                 cmp     ah, 7Fh
seg002:0BCF                 ja      short loc_11B14
seg002:0BD1                 call    sub_123E0
seg002:0BD4
seg002:0BD4 loc_11B14:                              ; CODE XREF: seg002:0BA5↑j
seg002:0BD4                                         ; seg002:0BAC↑j ...
seg002:0BD4                 pop     dx
seg002:0BD5                 retn
seg002:0BD5 sub_11B08       endp ; sp-analysis failed
seg002:0BD5
seg002:0BD6
seg002:0BD6 ; =============== S U B R O U T I N E =======================================
seg002:0BD6
seg002:0BD6
seg002:0BD6 sub_11B16       proc near
seg002:0BD6                 call    sub_1175A
seg002:0BD9                 mov     ah, al
seg002:0BDB                 call    sub_1175A
seg002:0BDE                 cmp     word ptr ds:2340h, 0FFFFh
seg002:0BE3                 jz      short locret_11B28
seg002:0BE5                 call    sub_123F4
seg002:0BE8
seg002:0BE8 locret_11B28:                           ; CODE XREF: sub_11B16+D↑j
seg002:0BE8                 retn
seg002:0BE8 sub_11B16       endp
seg002:0BE8
seg002:0BE9
seg002:0BE9 ; =============== S U B R O U T I N E =======================================
seg002:0BE9
seg002:0BE9
seg002:0BE9 sub_11B29       proc near
seg002:0BE9                 call    sub_1175A
seg002:0BEC                 mov     ah, al
seg002:0BEE                 call    sub_1175A
seg002:0BF1                 cmp     word ptr ds:2340h, 0FFFFh
seg002:0BF6                 jz      short locret_11B3B
seg002:0BF8                 call    sub_12403
seg002:0BFB
seg002:0BFB locret_11B3B:                           ; CODE XREF: sub_11B29+D↑j
seg002:0BFB                 retn
seg002:0BFB sub_11B29       endp
seg002:0BFB
seg002:0BFC
seg002:0BFC ; =============== S U B R O U T I N E =======================================
seg002:0BFC
seg002:0BFC
seg002:0BFC sub_11B3C       proc near
seg002:0BFC                 call    sub_1175A
seg002:0BFF                 mov     ah, al
seg002:0C01                 cmp     word ptr ds:2340h, 0FFFFh
seg002:0C06                 jz      short locret_11B4B
seg002:0C08                 call    sub_1241F
seg002:0C0B
seg002:0C0B locret_11B4B:                           ; CODE XREF: sub_11B3C+A↑j
seg002:0C0B                 retn
seg002:0C0B sub_11B3C       endp
seg002:0C0B
seg002:0C0C
seg002:0C0C ; =============== S U B R O U T I N E =======================================
seg002:0C0C
seg002:0C0C
seg002:0C0C sub_11B4C       proc near
seg002:0C0C                 mov     ah, al
seg002:0C0E                 call    sub_1175A
seg002:0C11                 cmp     word ptr ds:2340h, 0FFFFh
seg002:0C16                 jz      short locret_11B5B
seg002:0C18                 call    sub_1243B
seg002:0C1B
seg002:0C1B locret_11B5B:                           ; CODE XREF: sub_11B4C+A↑j
seg002:0C1B                 retn
seg002:0C1B sub_11B4C       endp
seg002:0C1B
seg002:0C1C
seg002:0C1C ; =============== S U B R O U T I N E =======================================
seg002:0C1C
seg002:0C1C
seg002:0C1C sub_11B5C       proc near
seg002:0C1C                 call    sub_1175A
seg002:0C1F                 mov     ah, al
seg002:0C21                 call    sub_1175A
seg002:0C24                 cmp     word ptr ds:2340h, 0FFFFh
seg002:0C29                 jz      short locret_11B6E
seg002:0C2B                 call    sub_1244A
seg002:0C2E
seg002:0C2E locret_11B6E:                           ; CODE XREF: sub_11B5C+D↑j
seg002:0C2E                 retn
seg002:0C2E sub_11B5C       endp
seg002:0C2E
seg002:0C2F
seg002:0C2F ; =============== S U B R O U T I N E =======================================
seg002:0C2F
seg002:0C2F
seg002:0C2F sub_11B6F       proc near
seg002:0C2F                 mov     bl, cl
seg002:0C31                 and     bl, 0Fh
seg002:0C34                 shl     bl, 1
seg002:0C36                 sub     bh, bh
seg002:0C38                 call    word ptr [bx+23C8h]
seg002:0C3C                 retn
seg002:0C3C sub_11B6F       endp
seg002:0C3C
seg002:0C3D
seg002:0C3D ; =============== S U B R O U T I N E =======================================
seg002:0C3D
seg002:0C3D
seg002:0C3D sub_11B7D       proc near
seg002:0C3D                 call    sub_1245A
seg002:0C40                 call    sub_1177F
seg002:0C43                 call    sub_117E1
seg002:0C46                 retn
seg002:0C46 sub_11B7D       endp
seg002:0C46
seg002:0C47
seg002:0C47 ; =============== S U B R O U T I N E =======================================
seg002:0C47
seg002:0C47
seg002:0C47 sub_11B87       proc near
seg002:0C47                 call    sub_1175A
seg002:0C4A                 call    sub_1175A
seg002:0C4D                 retn
seg002:0C4D sub_11B87       endp
seg002:0C4D
seg002:0C4E
seg002:0C4E ; =============== S U B R O U T I N E =======================================
seg002:0C4E
seg002:0C4E
seg002:0C4E sub_11B8E       proc near
seg002:0C4E                 call    sub_1175A
seg002:0C51                 retn
seg002:0C51 sub_11B8E       endp
seg002:0C51
seg002:0C52 ; ---------------------------------------------------------------------------
seg002:0C52                 retn
seg002:0C53 ; ---------------------------------------------------------------------------
seg002:0C53                 retn
seg002:0C54 ; ---------------------------------------------------------------------------
seg002:0C54                 retn
seg002:0C55 ; ---------------------------------------------------------------------------
seg002:0C55                 retn
seg002:0C56 ; ---------------------------------------------------------------------------
seg002:0C56                 retn
seg002:0C57 ; ---------------------------------------------------------------------------
seg002:0C57                 retn
seg002:0C58 ; ---------------------------------------------------------------------------
seg002:0C58                 retn
seg002:0C59 ; ---------------------------------------------------------------------------
seg002:0C59                 call    sub_1175A
seg002:0C5C                 push    es
seg002:0C5D                 push    di
seg002:0C5E                 mov     cx, ds
seg002:0C60                 mov     es, cx
seg002:0C62                 mov     di, 2A0Ah
seg002:0C65                 mov     cx, 2
seg002:0C68                 repne scasb
seg002:0C6A                 jnz     short loc_11BBF
seg002:0C6C                 mov     bx, di
seg002:0C6E                 pop     di
seg002:0C6F                 pop     es
seg002:0C70                 push    es
seg002:0C71                 push    di
seg002:0C72                 call    sub_1177F
seg002:0C75                 sub     bx, 2A0Bh
seg002:0C79                 shl     bx, 1
seg002:0C7B                 call    word ptr [bx+23E8h]
seg002:0C7F
seg002:0C7F loc_11BBF:                              ; CODE XREF: seg002:0C6A↑j
seg002:0C7F                 pop     di
seg002:0C80                 pop     es
seg002:0C81                 call    sub_1177F
seg002:0C84                 call    sub_117E1
seg002:0C87                 retn
seg002:0C88
seg002:0C88 ; =============== S U B R O U T I N E =======================================
seg002:0C88
seg002:0C88
seg002:0C88 sub_11BC8       proc near               ; CODE XREF: seg002:0D83↓p
seg002:0C88                                         ; sub_11CC8+23↓p
seg002:0C88                 push    bx
seg002:0C89                 push    cx
seg002:0C8A                 push    dx
seg002:0C8B                 mov     word ptr ds:23A4h, 1
seg002:0C91                 cmp     byte ptr ds:23EDh, 0
seg002:0C96                 jz      short loc_11BDB
seg002:0C98                 jmp     loc_11CA7
seg002:0C9B ; ---------------------------------------------------------------------------
seg002:0C9B
seg002:0C9B loc_11BDB:                              ; CODE XREF: sub_11BC8+E↑j
seg002:0C9B                 mov     cx, 4
seg002:0C9E
seg002:0C9E loc_11BDE:                              ; CODE XREF: sub_11BC8+1A↓j
seg002:0C9E                 shr     dx, 1
seg002:0CA0                 rcr     ax, 1
seg002:0CA2                 loop    loc_11BDE
seg002:0CA4                 adc     ax, 0
seg002:0CA7                 adc     dx, 0
seg002:0CAA                 mov     cx, 0F424h
seg002:0CAD                 or      dx, dx
seg002:0CAF                 jnz     short loc_11C0A
seg002:0CB1                 cmp     ax, 0F424h
seg002:0CB4                 ja      short loc_11C0A
seg002:0CB6                 cmp     ax, 3D09h
seg002:0CB9                 jnb     short loc_11BFE
seg002:0CBB                 mov     ax, 3D09h
seg002:0CBE
seg002:0CBE loc_11BFE:                              ; CODE XREF: sub_11BC8+31↑j
seg002:0CBE                 xchg    ax, cx
seg002:0CBF                 div     cx
seg002:0CC1                 xchg    ax, cx
seg002:0CC2                 xchg    ax, dx
seg002:0CC3                 call    sub_11875
seg002:0CC6                 mov     dx, cx
seg002:0CC8                 jmp     short loc_11C31
seg002:0CCA ; ---------------------------------------------------------------------------
seg002:0CCA
seg002:0CCA loc_11C0A:                              ; CODE XREF: sub_11BC8+27↑j
seg002:0CCA                                         ; sub_11BC8+2C↑j
seg002:0CCA                 or      dx, dx
seg002:0CCC                 jz      short loc_11C28
seg002:0CCE                 cmp     dx, 1
seg002:0CD1                 ja      short loc_11C18
seg002:0CD3                 cmp     ax, 6E36h
seg002:0CD6                 jbe     short loc_11C1E
seg002:0CD8
seg002:0CD8 loc_11C18:                              ; CODE XREF: sub_11BC8+49↑j
seg002:0CD8                 mov     dx, 1
seg002:0CDB                 mov     ax, 63E6h
seg002:0CDE
seg002:0CDE loc_11C1E:                              ; CODE XREF: sub_11BC8+4E↑j
seg002:0CDE                                         ; sub_11BC8+5E↓j
seg002:0CDE                 shr     dx, 1
seg002:0CE0                 rcr     ax, 1
seg002:0CE2                 shr     cx, 1
seg002:0CE4                 or      dx, dx
seg002:0CE6                 jnz     short loc_11C1E
seg002:0CE8
seg002:0CE8 loc_11C28:                              ; CODE XREF: sub_11BC8+44↑j
seg002:0CE8                 mov     dx, ax
seg002:0CEA                 mov     ax, dx
seg002:0CEC                 call    sub_11875
seg002:0CEF                 sub     dx, dx
seg002:0CF1
seg002:0CF1 loc_11C31:                              ; CODE XREF: sub_11BC8+40↑j
seg002:0CF1                 mov     cx, dx
seg002:0CF3                 mul     word ptr ds:239Bh
seg002:0CF7                 add     ax, ax
seg002:0CF9                 adc     dx, 0
seg002:0CFC                 mov     bx, dx
seg002:0CFE                 mov     ax, cx
seg002:0D00                 mul     word ptr ds:239Bh
seg002:0D04                 add     ax, bx
seg002:0D06                 adc     dx, 0
seg002:0D09                 push    si
seg002:0D0A                 push    bx
seg002:0D0B                 push    dx
seg002:0D0C                 push    ax
seg002:0D0D                 mov     si, ax
seg002:0D0F                 mov     ax, dx
seg002:0D11                 cwd
seg002:0D12                 mov     cx, 14h
seg002:0D15                 div     cx
seg002:0D17                 mov     bx, ax
seg002:0D19                 mov     ax, si
seg002:0D1B                 div     cx
seg002:0D1D                 mov     dx, bx
seg002:0D1F                 pop     bx
seg002:0D20                 pop     si
seg002:0D21                 xchg    ax, bx
seg002:0D22                 xchg    dx, si
seg002:0D24                 mov     cx, ds:23A1h
seg002:0D28                 mov     byte ptr ds:23A3h, 1
seg002:0D2D                 or      cx, cx
seg002:0D2F                 jz      short loc_11C95
seg002:0D31                 jns     short loc_11C7A
seg002:0D33                 neg     cx
seg002:0D35                 mov     byte ptr ds:23A3h, 0
seg002:0D3A
seg002:0D3A loc_11C7A:                              ; CODE XREF: sub_11BC8+A9↑j
seg002:0D3A                 cmp     cx, 80h
seg002:0D3E                 jnb     short loc_11C9B
seg002:0D40                 cmp     byte ptr ds:23A3h, 0
seg002:0D45                 jz      short loc_11C8F
seg002:0D47
seg002:0D47 loc_11C87:                              ; CODE XREF: sub_11BC8+C3↓j
seg002:0D47                 add     ax, bx
seg002:0D49                 adc     dx, si
seg002:0D4B                 loop    loc_11C87
seg002:0D4D                 jmp     short loc_11C95
seg002:0D4F ; ---------------------------------------------------------------------------
seg002:0D4F
seg002:0D4F loc_11C8F:                              ; CODE XREF: sub_11BC8+BD↑j
seg002:0D4F                                         ; sub_11BC8+CB↓j
seg002:0D4F                 sub     ax, bx
seg002:0D51                 sbb     dx, si
seg002:0D53                 loop    loc_11C8F
seg002:0D55
seg002:0D55 loc_11C95:                              ; CODE XREF: sub_11BC8+A7↑j
seg002:0D55                                         ; sub_11BC8+C5↑j
seg002:0D55                 mov     word ptr ds:23A4h, 0
seg002:0D5B
seg002:0D5B loc_11C9B:                              ; CODE XREF: sub_11BC8+B6↑j
seg002:0D5B                 pop     bx
seg002:0D5C                 pop     si
seg002:0D5D                 cmp     word ptr ds:23A4h, 0
seg002:0D62                 jnz     short loc_11CA7
seg002:0D64                 call    sub_11816
seg002:0D67
seg002:0D67 loc_11CA7:                              ; CODE XREF: sub_11BC8+10↑j
seg002:0D67                                         ; sub_11BC8+DA↑j
seg002:0D67                 mov     ax, ds:23A4h
seg002:0D6A                 pop     dx
seg002:0D6B                 pop     cx
seg002:0D6C                 pop     bx
seg002:0D6D                 retn
seg002:0D6D sub_11BC8       endp
seg002:0D6D
seg002:0D6E ; ---------------------------------------------------------------------------
seg002:0D6E                 push    dx
seg002:0D6F                 call    sub_1175A
seg002:0D72                 mov     dl, al
seg002:0D74                 call    sub_1175A
seg002:0D77                 mov     ah, al
seg002:0D79                 call    sub_1175A
seg002:0D7C                 mov     ds:23A6h, ax
seg002:0D7F                 mov     ds:23A8h, dx
seg002:0D83                 call    sub_11BC8
seg002:0D86                 pop     dx
seg002:0D87                 retn
seg002:0D88
seg002:0D88 ; =============== S U B R O U T I N E =======================================
seg002:0D88
seg002:0D88
seg002:0D88 sub_11CC8       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:0D88                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:0D88                 push    dx
seg002:0D89                 cmp     ds:23A1h, ax
seg002:0D8D                 jz      short loc_11CEE
seg002:0D8F                 mov     dx, ax
seg002:0D91                 or      dx, dx
seg002:0D93                 jns     short loc_11CD7
seg002:0D95                 neg     dx
seg002:0D97
seg002:0D97 loc_11CD7:                              ; CODE XREF: sub_11CC8+B↑j
seg002:0D97                 cmp     dx, 14h
seg002:0D9A                 jbe     short loc_11CE1
seg002:0D9C                 mov     ax, 1
seg002:0D9F                 jmp     short loc_11CF0
seg002:0DA1 ; ---------------------------------------------------------------------------
seg002:0DA1
seg002:0DA1 loc_11CE1:                              ; CODE XREF: sub_11CC8+12↑j
seg002:0DA1                 mov     ds:23A1h, ax
seg002:0DA4                 mov     ax, ds:23A6h
seg002:0DA7                 mov     dx, ds:23A8h
seg002:0DAB                 call    sub_11BC8
seg002:0DAE
seg002:0DAE loc_11CEE:                              ; CODE XREF: sub_11CC8+5↑j
seg002:0DAE                 xor     ax, ax
seg002:0DB0
seg002:0DB0 loc_11CF0:                              ; CODE XREF: sub_11CC8+17↑j
seg002:0DB0                 pop     dx
seg002:0DB1                 retn
seg002:0DB1 sub_11CC8       endp
seg002:0DB1
seg002:0DB2
seg002:0DB2 ; =============== S U B R O U T I N E =======================================
seg002:0DB2
seg002:0DB2
seg002:0DB2 sub_11CF2       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:0DB2                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:0DB2                 push    dx
seg002:0DB3                 pushf
seg002:0DB4                 cli
seg002:0DB5                 cmp     ds:23AAh, ax
seg002:0DB9                 jz      short loc_11D19
seg002:0DBB                 mov     dx, ax
seg002:0DBD                 or      dx, dx
seg002:0DBF                 jns     short loc_11D03
seg002:0DC1                 neg     dx
seg002:0DC3
seg002:0DC3 loc_11D03:                              ; CODE XREF: sub_11CF2+D↑j
seg002:0DC3                 cmp     dx, 0Ch
seg002:0DC6                 jbe     short loc_11D0D
seg002:0DC8                 mov     ax, 1
seg002:0DCB                 jmp     short loc_11D1B
seg002:0DCD ; ---------------------------------------------------------------------------
seg002:0DCD
seg002:0DCD loc_11D0D:                              ; CODE XREF: sub_11CF2+14↑j
seg002:0DCD                 mov     ds:23AAh, ax
seg002:0DD0                 call    sub_12373
seg002:0DD3                 call    sub_12363
seg002:0DD6                 call    sub_1160E
seg002:0DD9
seg002:0DD9 loc_11D19:                              ; CODE XREF: sub_11CF2+7↑j
seg002:0DD9                 xor     ax, ax
seg002:0DDB
seg002:0DDB loc_11D1B:                              ; CODE XREF: sub_11CF2+19↑j
seg002:0DDB                 popf
seg002:0DDC                 pop     dx
seg002:0DDD                 retn
seg002:0DDD sub_11CF2       endp
seg002:0DDD
seg002:0DDE
seg002:0DDE ; =============== S U B R O U T I N E =======================================
seg002:0DDE
seg002:0DDE
seg002:0DDE sub_11D1E       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:0DDE                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:0DDE                 push    bx
seg002:0DDF                 push    es
seg002:0DE0                 push    di
seg002:0DE1                 mov     bx, 1
seg002:0DE4                 cmp     byte ptr ds:206Dh, 0
seg002:0DE9                 jz      short loc_11D70
seg002:0DEB                 pushf
seg002:0DEC                 cli
seg002:0DED                 cld
seg002:0DEE                 push    ax
seg002:0DEF                 mov     bx, ax
seg002:0DF1                 sub     bh, bh
seg002:0DF3                 and     bl, 0Fh
seg002:0DF6                 mov     al, [bx+2342h]
seg002:0DFA                 cbw
seg002:0DFB                 mov     ds:2340h, ax
seg002:0DFE                 mov     di, 22FAh
seg002:0E01                 mov     al, dl
seg002:0E03                 stosb
seg002:0E04                 mov     al, cl
seg002:0E06                 stosb
seg002:0E07                 pop     ax
seg002:0E08
seg002:0E08 loc_11D48:                              ; CODE XREF: sub_11D1E+2F↓j
seg002:0E08                 cmp     byte ptr ds:2396h, 1
seg002:0E0D                 jz      short loc_11D48
seg002:0E0F                 mov     cl, ds:2A0Ch
seg002:0E13                 mov     ds:2A0Ch, al
seg002:0E16                 mov     bl, al
seg002:0E18                 and     bx, 70h
seg002:0E1B                 shr     bx, 1
seg002:0E1D                 shr     bx, 1
seg002:0E1F                 shr     bx, 1
seg002:0E21                 mov     di, 22FAh
seg002:0E24                 call    word ptr [bx+23B8h]
seg002:0E28                 mov     ds:2A0Ch, cl
seg002:0E2C                 popf
seg002:0E2D                 mov     bx, 0
seg002:0E30
seg002:0E30 loc_11D70:                              ; CODE XREF: sub_11D1E+B↑j
seg002:0E30                 mov     ax, bx
seg002:0E32                 pop     di
seg002:0E33                 pop     es
seg002:0E34                 pop     bx
seg002:0E35                 retn
seg002:0E35 sub_11D1E       endp
seg002:0E35
seg002:0E36
seg002:0E36 ; =============== S U B R O U T I N E =======================================
seg002:0E36
seg002:0E36
seg002:0E36 sub_11D76       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:0E36                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:0E36                 xor     bx, bx
seg002:0E38                 call    sub_11D7C
seg002:0E3B                 retn
seg002:0E3B sub_11D76       endp
seg002:0E3B
seg002:0E3C
seg002:0E3C ; =============== S U B R O U T I N E =======================================
seg002:0E3C
seg002:0E3C
seg002:0E3C sub_11D7C       proc near               ; CODE XREF: sub_11D76+2↑p
seg002:0E3C                 push    bx
seg002:0E3D                 push    es
seg002:0E3E                 push    di
seg002:0E3F                 push    si
seg002:0E40                 mov     word ptr ds:22DCh, 1
seg002:0E46                 cmp     byte ptr ds:206Dh, 0
seg002:0E4B                 jz      short loc_11E04
seg002:0E4D                 mov     di, ax
seg002:0E4F                 mov     ax, dx
seg002:0E51                 mov     es, ax
seg002:0E53                 push    di
seg002:0E54                 mov     si, 2678h
seg002:0E57                 mov     byte ptr [si+9], 1
seg002:0E5B                 add     di, cx
seg002:0E5D                 adc     ax, bx
seg002:0E5F                 mov     [si], di
seg002:0E61                 mov     [si+2], ax
seg002:0E64                 pop     di
seg002:0E65                 mov     al, es:[di]
seg002:0E68                 inc     di
seg002:0E69                 jmp     short loc_11DBB
seg002:0E6B ; ---------------------------------------------------------------------------
seg002:0E6B
seg002:0E6B loc_11DAB:                              ; CODE XREF: sub_11D7C+35↓j
seg002:0E6B                                         ; sub_11D7C+77↓j ...
seg002:0E6B                 mov     al, es:[di]
seg002:0E6E                 inc     di
seg002:0E6F                 test    al, 80h
seg002:0E71                 jnz     short loc_11DAB
seg002:0E73                 mov     al, es:[di]
seg002:0E76                 inc     di
seg002:0E77                 test    al, 80h
seg002:0E79                 jz      short loc_11E04
seg002:0E7B
seg002:0E7B loc_11DBB:                              ; CODE XREF: sub_11D7C+2D↑j
seg002:0E7B                 push    ax
seg002:0E7C                 mov     bx, ax
seg002:0E7E                 sub     bh, bh
seg002:0E80                 and     bl, 0Fh
seg002:0E83                 mov     al, [bx+2342h]
seg002:0E87                 cbw
seg002:0E88                 mov     ds:2340h, ax
seg002:0E8B                 pop     ax
seg002:0E8C
seg002:0E8C loc_11DCC:                              ; CODE XREF: sub_11D7C+55↓j
seg002:0E8C                 cmp     byte ptr ds:2396h, 1
seg002:0E91                 jz      short loc_11DCC
seg002:0E93                 push    cx
seg002:0E94                 mov     cl, ds:2A0Ch
seg002:0E98                 mov     ds:2A0Ch, al
seg002:0E9B                 mov     cl, al
seg002:0E9D                 mov     bl, al
seg002:0E9F                 and     bx, 70h
seg002:0EA2                 shr     bx, 1
seg002:0EA4                 shr     bx, 1
seg002:0EA6                 shr     bx, 1
seg002:0EA8                 call    word ptr [bx+23B8h]
seg002:0EAC                 mov     ds:2A0Ch, cl
seg002:0EB0                 pop     cx
seg002:0EB1                 cmp     di, [si]
seg002:0EB3                 jb      short loc_11DAB
seg002:0EB5                 mov     ax, es
seg002:0EB7                 cmp     ax, [si+2]
seg002:0EBA                 jnb     short loc_11DFE
seg002:0EBC                 loop    loc_11DAB
seg002:0EBE
seg002:0EBE loc_11DFE:                              ; CODE XREF: sub_11D7C+7E↑j
seg002:0EBE                 mov     word ptr ds:22DCh, 0
seg002:0EC4
seg002:0EC4 loc_11E04:                              ; CODE XREF: sub_11D7C+F↑j
seg002:0EC4                                         ; sub_11D7C+3D↑j
seg002:0EC4                 mov     ax, ds:22DCh
seg002:0EC7                 pop     si
seg002:0EC8                 pop     di
seg002:0EC9                 pop     es
seg002:0ECA                 pop     bx
seg002:0ECB                 retn
seg002:0ECB sub_11D7C       endp
seg002:0ECB
seg002:0ECC ; ---------------------------------------------------------------------------
seg002:0ECC                 and     byte ptr [si+9], 0FEh
seg002:0ED0                 retn
seg002:0ED1
seg002:0ED1 ; =============== S U B R O U T I N E =======================================
seg002:0ED1
seg002:0ED1
seg002:0ED1 sub_11E11       proc near               ; CODE XREF: sub_12198+1E↓p
seg002:0ED1                                         ; sub_12246+71↓p ...
seg002:0ED1                 push    es
seg002:0ED2                 push    di
seg002:0ED3                 cmp     word ptr ds:2314h, 0
seg002:0ED8                 jnz     short loc_11E23
seg002:0EDA                 cmp     word ptr ds:2312h, 0
seg002:0EDF                 jnz     short loc_11E23
seg002:0EE1                 jmp     short loc_11E2A
seg002:0EE3 ; ---------------------------------------------------------------------------
seg002:0EE3
seg002:0EE3 loc_11E23:                              ; CODE XREF: sub_11E11+7↑j
seg002:0EE3                                         ; sub_11E11+E↑j
seg002:0EE3                 les     di, ds:2312h
seg002:0EE7                 mov     es:[di], ax
seg002:0EEA
seg002:0EEA loc_11E2A:                              ; CODE XREF: sub_11E11+10↑j
seg002:0EEA                 mov     ds:2394h, ax
seg002:0EED                 pop     di
seg002:0EEE                 pop     es
seg002:0EEF                 retn
seg002:0EEF sub_11E11       endp
seg002:0EEF
seg002:0EF0
seg002:0EF0 ; =============== S U B R O U T I N E =======================================
seg002:0EF0
seg002:0EF0
seg002:0EF0 sub_11E30       proc near               ; CODE XREF: sub_11ED0+137↓p
seg002:0EF0                                         ; sub_121D4+1D↓p
seg002:0EF0                 push    ax
seg002:0EF1                 shr     ax, 1
seg002:0EF3                 shr     ax, 1
seg002:0EF5                 shr     ax, 1
seg002:0EF7                 shr     ax, 1
seg002:0EF9                 add     dx, ax
seg002:0EFB                 pop     ax
seg002:0EFC                 and     ax, 0Fh
seg002:0EFF                 retn
seg002:0EFF sub_11E30       endp
seg002:0EFF
seg002:0F00
seg002:0F00 ; =============== S U B R O U T I N E =======================================
seg002:0F00
seg002:0F00
seg002:0F00 sub_11E40       proc near               ; CODE XREF: sub_11ED0+B3↓p
seg002:0F00                 push    si
seg002:0F01                 push    di
seg002:0F02                 push    bx
seg002:0F03                 push    cx
seg002:0F04                 pushf
seg002:0F05                 cli
seg002:0F06                 mov     al, 0
seg002:0F08                 mov     dx, 43h ; 'C'
seg002:0F0B                 out     dx, al          ; Timer 8253-5 (AT: 8254.2).
seg002:0F0C                 jmp     short $+2
seg002:0F0E ; ---------------------------------------------------------------------------
seg002:0F0E
seg002:0F0E loc_11E4E:                              ; CODE XREF: sub_11E40+C↑j
seg002:0F0E                 jmp     short $+2
seg002:0F10 ; ---------------------------------------------------------------------------
seg002:0F10
seg002:0F10 loc_11E50:                              ; CODE XREF: sub_11E40:loc_11E4E↑j
seg002:0F10                 in      al, 40h         ; Timer 8253-5 (AT: 8254.2).
seg002:0F12                 xchg    ah, al
seg002:0F14                 in      al, 40h         ; Timer 8253-5 (AT: 8254.2).
seg002:0F16                 xchg    ah, al
seg002:0F18                 sti
seg002:0F19                 mov     di, ds:2075h
seg002:0F1D                 cmp     di, ds:2077h
seg002:0F21                 jz      short loc_11E74
seg002:0F23                 ja      short loc_11E6C
seg002:0F25                 xor     ax, ax
seg002:0F27                 mov     dx, 0
seg002:0F2A                 jmp     short loc_11ECA
seg002:0F2C ; ---------------------------------------------------------------------------
seg002:0F2C
seg002:0F2C loc_11E6C:                              ; CODE XREF: sub_11E40+23↑j
seg002:0F2C                                         ; sub_11E40+3B↓j
seg002:0F2C                 mov     ds:22E8h, ax
seg002:0F2F                 mov     dx, 0
seg002:0F32                 jmp     short loc_11E7D
seg002:0F34 ; ---------------------------------------------------------------------------
seg002:0F34
seg002:0F34 loc_11E74:                              ; CODE XREF: sub_11E40+21↑j
seg002:0F34                 cmp     ax, ds:22E8h
seg002:0F38                 jbe     short loc_11E7D
seg002:0F3A                 inc     di
seg002:0F3B                 jmp     short loc_11E6C
seg002:0F3D ; ---------------------------------------------------------------------------
seg002:0F3D
seg002:0F3D loc_11E7D:                              ; CODE XREF: sub_11E40+32↑j
seg002:0F3D                                         ; sub_11E40+38↑j
seg002:0F3D                 mov     cx, ds:2073h
seg002:0F41                 sub     cx, ax
seg002:0F43                 mov     ds:22E8h, ax
seg002:0F46                 mov     ax, cx
seg002:0F48                 mov     dx, 0
seg002:0F4B                 mov     ds:2077h, di
seg002:0F4F                 mov     bx, ax
seg002:0F51                 mov     ax, di
seg002:0F53                 mul     word ptr ds:2073h
seg002:0F57                 add     ax, bx
seg002:0F59                 adc     dx, 0
seg002:0F5C                 mov     si, ax
seg002:0F5E                 mov     ax, dx
seg002:0F60                 cwd
seg002:0F61                 mov     cx, ds:22EAh
seg002:0F65                 div     cx
seg002:0F67                 mov     di, ax
seg002:0F69                 mov     ax, si
seg002:0F6B                 div     cx
seg002:0F6D                 mov     dx, di
seg002:0F6F                 mov     ds:22EEh, ax
seg002:0F72                 mov     ds:22F0h, dx
seg002:0F76                 mov     bx, ax
seg002:0F78                 mov     si, dx
seg002:0F7A                 sub     ax, ds:22F2h
seg002:0F7E                 sbb     dx, ds:22F4h
seg002:0F82                 mov     ds:22F2h, bx
seg002:0F86                 mov     ds:22F4h, si
seg002:0F8A
seg002:0F8A loc_11ECA:                              ; CODE XREF: sub_11E40+2A↑j
seg002:0F8A                 popf
seg002:0F8B                 pop     cx
seg002:0F8C                 pop     bx
seg002:0F8D                 pop     di
seg002:0F8E                 pop     si
seg002:0F8F                 retn
seg002:0F8F sub_11E40       endp
seg002:0F8F
seg002:0F90
seg002:0F90 ; =============== S U B R O U T I N E =======================================
seg002:0F90
seg002:0F90
seg002:0F90 sub_11ED0       proc far
seg002:0F90                 push    ds
seg002:0F91                 push    es
seg002:0F92                 push    ax
seg002:0F93                 push    bx
seg002:0F94                 push    cx
seg002:0F95                 push    dx
seg002:0F96                 push    di
seg002:0F97                 push    si
seg002:0F98                 push    bp
seg002:0F99                 mov     ax, cs
seg002:0F9B                 mov     ds, ax
seg002:0F9D                 assume ds:seg002
seg002:0F9D                 mov     es, ax
seg002:0F9F                 assume es:seg002
seg002:0F9F                 mov     dx, word_12FBD
seg002:0FA3                 add     dx, 4
seg002:0FA6                 mov     al, 82h
seg002:0FA8                 out     dx, al
seg002:0FA9                 jmp     short $+2
seg002:0FAB ; ---------------------------------------------------------------------------
seg002:0FAB
seg002:0FAB loc_11EEB:                              ; CODE XREF: sub_11ED0+19↑j
seg002:0FAB                 jmp     short $+2
seg002:0FAD ; ---------------------------------------------------------------------------
seg002:0FAD
seg002:0FAD loc_11EED:                              ; CODE XREF: sub_11ED0:loc_11EEB↑j
seg002:0FAD                 jmp     short $+2
seg002:0FAF ; ---------------------------------------------------------------------------
seg002:0FAF
seg002:0FAF loc_11EEF:                              ; CODE XREF: sub_11ED0:loc_11EED↑j
seg002:0FAF                 jmp     short $+2
seg002:0FB1 ; ---------------------------------------------------------------------------
seg002:0FB1
seg002:0FB1 loc_11EF1:                              ; CODE XREF: sub_11ED0:loc_11EEF↑j
seg002:0FB1                 inc     dx
seg002:0FB2                 in      al, dx
seg002:0FB3                 test    al, 4
seg002:0FB5                 jnz     short loc_11EFA
seg002:0FB7                 jmp     loc_1202A
seg002:0FBA ; ---------------------------------------------------------------------------
seg002:0FBA
seg002:0FBA loc_11EFA:                              ; CODE XREF: sub_11ED0+25↑j
seg002:0FBA                 mov     byte_13271, 1
seg002:0FBF                 mov     cl, byte_12FC3
seg002:0FC3                 call    sub_12087
seg002:0FC6                 cli
seg002:0FC7                 mov     word_13250, ss
seg002:0FCB                 mov     word_1324E, sp
seg002:0FCF                 mov     ax, ds
seg002:0FD1                 mov     ss, ax
seg002:0FD3                 assume ss:seg002
seg002:0FD3                 mov     sp, 2B0Eh
seg002:0FD6                 sti
seg002:0FD7                 call    sub_1204C
seg002:0FDA                 cld
seg002:0FDB                 mov     di, 40h ; '@'
seg002:0FDE
seg002:0FDE loc_11F1E:                              ; CODE XREF: sub_11ED0+124↓j
seg002:0FDE                 call    sub_12609
seg002:0FE1                 jb      short loc_11F26
seg002:0FE3                 jmp     loc_11FF7
seg002:0FE6 ; ---------------------------------------------------------------------------
seg002:0FE6
seg002:0FE6 loc_11F26:                              ; CODE XREF: sub_11ED0+51↑j
seg002:0FE6                 call    sub_125F1
seg002:0FE9                 cmp     byte_1326B, 0
seg002:0FEE                 jnz     short loc_11F3B
seg002:0FF0                 mov     byte_1326B, 1
seg002:0FF5                 mov     score_maybe, 0
seg002:0FFB
seg002:0FFB loc_11F3B:                              ; CODE XREF: sub_11ED0+5E↑j
seg002:0FFB                 push    es
seg002:0FFC                 push    di
seg002:0FFD                 cmp     byte_1326C, 0
seg002:1002                 jz      short loc_11F73
seg002:1004                 les     di, dword_1325A
seg002:1008                 assume es:nothing
seg002:1008                 push    ax
seg002:1009                 mov     ax, word_13248
seg002:100C                 mov     dx, word_1324A
seg002:1010                 inc     ax
seg002:1011                 adc     dx, 0
seg002:1014                 cmp     dx, word_13246
seg002:1018                 jb      short loc_11F69
seg002:101A                 cmp     ax, word_13244
seg002:101E                 jbe     short loc_11F69
seg002:1020                 pop     ax
seg002:1021                 mov     word_1324C, 1
seg002:1027                 jmp     short loc_11FD5
seg002:1029 ; ---------------------------------------------------------------------------
seg002:1029
seg002:1029 loc_11F69:                              ; CODE XREF: sub_11ED0+88↑j
seg002:1029                                         ; sub_11ED0+8E↑j
seg002:1029                 mov     word_13248, ax
seg002:102C                 mov     word_1324A, dx
seg002:1030                 pop     ax
seg002:1031                 jmp     short loc_11F78
seg002:1033 ; ---------------------------------------------------------------------------
seg002:1033
seg002:1033 loc_11F73:                              ; CODE XREF: sub_11ED0+72↑j
seg002:1033                 push    cs
seg002:1034                 pop     es
seg002:1035                 assume es:seg002
seg002:1035                 mov     di, 2300h
seg002:1038
seg002:1038 loc_11F78:                              ; CODE XREF: sub_11ED0+A1↑j
seg002:1038                 mov     word_13266, di
seg002:103C                 mov     bx, es
seg002:103E                 mov     word_13268, bx
seg002:1042                 stosb
seg002:1043                 call    sub_11E40
seg002:1046                 cmp     byte_1326F, 1
seg002:104B                 jnz     short loc_11F94
seg002:104D                 mov     ax, word_1322E
seg002:1050                 mov     dx, word_13230
seg002:1054
seg002:1054 loc_11F94:                              ; CODE XREF: sub_11ED0+BB↑j
seg002:1054                 stosw
seg002:1055                 mov     ax, dx
seg002:1057                 stosb
seg002:1058                 cmp     word ptr dword_1325E, 0
seg002:105D                 jnz     short loc_11FA8
seg002:105F                 cmp     word ptr dword_1325E+2, 0
seg002:1064                 jnz     short loc_11FA8
seg002:1066                 jmp     short loc_11FBE
seg002:1068 ; ---------------------------------------------------------------------------
seg002:1068
seg002:1068 loc_11FA8:                              ; CODE XREF: sub_11ED0+CD↑j
seg002:1068                                         ; sub_11ED0+D4↑j
seg002:1068                 push    ax
seg002:1069                 push    word_13268
seg002:106D                 push    word_13266
seg002:1071                 push    word_13264
seg002:1075                 push    word_13262
seg002:1079                 call    dword_1325E
seg002:107D                 pop     ax
seg002:107E
seg002:107E loc_11FBE:                              ; CODE XREF: sub_11ED0+D6↑j
seg002:107E                 cmp     byte_1326C, 0
seg002:1083                 jz      short loc_11FD5
seg002:1085                 mov     bx, word_13266
seg002:1089                 add     bx, 4
seg002:108C                 adc     word ptr dword_1325A+2, 0
seg002:1091                 mov     word ptr dword_1325A, bx
seg002:1095
seg002:1095 loc_11FD5:                              ; CODE XREF: sub_11ED0+97↑j
seg002:1095                                         ; sub_11ED0+F3↑j
seg002:1095                 pop     di
seg002:1096                 pop     es
seg002:1097                 assume es:nothing
seg002:1097                 cmp     byte_1326C, 0
seg002:109C                 jz      short loc_11FEF
seg002:109E                 cmp     word_1324C, 0
seg002:10A3                 jz      short loc_11FEF
seg002:10A5                 mov     byte_13272, 1
seg002:10AA                 call    sub_122E0
seg002:10AD                 jmp     short loc_12013
seg002:10AF ; ---------------------------------------------------------------------------
seg002:10AF
seg002:10AF loc_11FEF:                              ; CODE XREF: sub_11ED0+10C↑j
seg002:10AF                                         ; sub_11ED0+113↑j
seg002:10AF                 dec     di
seg002:10B0                 or      di, di
seg002:10B2                 jz      short loc_11FF7
seg002:10B4                 jmp     loc_11F1E
seg002:10B7 ; ---------------------------------------------------------------------------
seg002:10B7
seg002:10B7 loc_11FF7:                              ; CODE XREF: sub_11ED0+53↑j
seg002:10B7                                         ; sub_11ED0+122↑j
seg002:10B7                 cmp     byte_1326C, 0
seg002:10BC                 jz      short loc_12013
seg002:10BE                 push    ax
seg002:10BF                 push    dx
seg002:10C0                 mov     ax, word ptr dword_1325A
seg002:10C3                 mov     dx, word ptr dword_1325A+2
seg002:10C7                 call    sub_11E30
seg002:10CA                 mov     word ptr dword_1325A, ax
seg002:10CD                 mov     word ptr dword_1325A+2, dx
seg002:10D1                 pop     dx
seg002:10D2                 pop     ax
seg002:10D3
seg002:10D3 loc_12013:                              ; CODE XREF: sub_11ED0+11D↑j
seg002:10D3                                         ; sub_11ED0+12C↑j
seg002:10D3                 cli
seg002:10D4                 mov     sp, word_1324E
seg002:10D8                 mov     ss, word_13250
seg002:10DC                 assume ss:nothing
seg002:10DC                 mov     byte_13271, 0
seg002:10E1                 mov     cl, byte_12FC3
seg002:10E5                 call    sub_1205C
seg002:10E8                 jmp     short loc_12042
seg002:10EA ; ---------------------------------------------------------------------------
seg002:10EA
seg002:10EA loc_1202A:                              ; CODE XREF: sub_11ED0+27↑j
seg002:10EA                 cmp     word ptr dword_1323C, 0
seg002:10EF                 jnz     short loc_1203D
seg002:10F1                 cmp     word ptr dword_1323C+2, 0
seg002:10F6                 jnz     short loc_1203D
seg002:10F8                 call    sub_1204C
seg002:10FB                 jmp     short loc_12042
seg002:10FD ; ---------------------------------------------------------------------------
seg002:10FD
seg002:10FD loc_1203D:                              ; CODE XREF: sub_11ED0+15F↑j
seg002:10FD                                         ; sub_11ED0+166↑j
seg002:10FD                 pushf
seg002:10FE                 call    dword_1323C
seg002:1102
seg002:1102 loc_12042:                              ; CODE XREF: sub_11ED0+158↑j
seg002:1102                                         ; sub_11ED0+16B↑j
seg002:1102                 pop     bp
seg002:1103                 pop     si
seg002:1104                 pop     di
seg002:1105                 pop     dx
seg002:1106                 pop     cx
seg002:1107                 pop     bx
seg002:1108                 pop     ax
seg002:1109                 pop     es
seg002:110A                 pop     ds
seg002:110B                 assume ds:nothing
seg002:110B                 iret
seg002:110B sub_11ED0       endp
seg002:110B
seg002:110C
seg002:110C ; =============== S U B R O U T I N E =======================================
seg002:110C
seg002:110C
seg002:110C sub_1204C       proc near               ; CODE XREF: sub_11ED0+47↑p
seg002:110C                                         ; sub_11ED0+168↑p
seg002:110C                 push    ax
seg002:110D                 mov     al, 20h ; ' '
seg002:110F                 cmp     byte ptr ds:2083h, 7
seg002:1114                 jbe     short loc_12058
seg002:1116                 out     0A0h, al        ; PIC 2  same as 0020 for PIC 1
seg002:1118
seg002:1118 loc_12058:                              ; CODE XREF: sub_1204C+8↑j
seg002:1118                 out     20h, al         ; Interrupt controller, 8259A.
seg002:111A                 pop     ax
seg002:111B                 retn
seg002:111B sub_1204C       endp
seg002:111B
seg002:111C
seg002:111C ; =============== S U B R O U T I N E =======================================
seg002:111C
seg002:111C
seg002:111C sub_1205C       proc near               ; CODE XREF: sub_11ED0+155↑p
seg002:111C                                         ; sub_120C9+57↓p
seg002:111C                 push    ax
seg002:111D                 push    dx
seg002:111E                 pushf
seg002:111F                 cli
seg002:1120                 cmp     cl, 8
seg002:1123                 jnb     short loc_1206A
seg002:1125                 mov     dx, 21h ; '!'
seg002:1128                 jmp     short loc_12070
seg002:112A ; ---------------------------------------------------------------------------
seg002:112A
seg002:112A loc_1206A:                              ; CODE XREF: sub_1205C+7↑j
seg002:112A                 mov     dx, 0A1h
seg002:112D                 sub     cl, 8
seg002:1130
seg002:1130 loc_12070:                              ; CODE XREF: sub_1205C+C↑j
seg002:1130                 mov     ax, 100h
seg002:1133                 shl     ah, cl
seg002:1135                 not     ah
seg002:1137                 in      al, dx          ; Interrupt Controller #2, 8259A
seg002:1138                 jmp     short $+2
seg002:113A ; ---------------------------------------------------------------------------
seg002:113A
seg002:113A loc_1207A:                              ; CODE XREF: sub_1205C+1C↑j
seg002:113A                 jmp     short $+2
seg002:113C ; ---------------------------------------------------------------------------
seg002:113C
seg002:113C loc_1207C:                              ; CODE XREF: sub_1205C:loc_1207A↑j
seg002:113C                 and     al, ah
seg002:113E                 out     dx, al          ; Interrupt Controller #2, 8259A
seg002:113F                 jmp     short $+2
seg002:1141 ; ---------------------------------------------------------------------------
seg002:1141
seg002:1141 loc_12081:                              ; CODE XREF: sub_1205C+23↑j
seg002:1141                 jmp     short $+2
seg002:1143 ; ---------------------------------------------------------------------------
seg002:1143
seg002:1143 loc_12083:                              ; CODE XREF: sub_1205C:loc_12081↑j
seg002:1143                 popf
seg002:1144                 pop     dx
seg002:1145                 pop     ax
seg002:1146                 retn
seg002:1146 sub_1205C       endp
seg002:1146
seg002:1147
seg002:1147 ; =============== S U B R O U T I N E =======================================
seg002:1147
seg002:1147
seg002:1147 sub_12087       proc near               ; CODE XREF: sub_11ED0+33↑p
seg002:1147                 push    ax
seg002:1148                 push    dx
seg002:1149                 pushf
seg002:114A                 cli
seg002:114B                 cmp     cl, 8
seg002:114E                 jnb     short loc_12095
seg002:1150                 mov     dx, 21h ; '!'
seg002:1153                 jmp     short loc_1209B
seg002:1155 ; ---------------------------------------------------------------------------
seg002:1155
seg002:1155 loc_12095:                              ; CODE XREF: sub_12087+7↑j
seg002:1155                 mov     dx, 0A1h
seg002:1158                 sub     cl, 8
seg002:115B
seg002:115B loc_1209B:                              ; CODE XREF: sub_12087+C↑j
seg002:115B                 mov     ax, 100h
seg002:115E                 shl     ah, cl
seg002:1160                 in      al, dx          ; Interrupt Controller #2, 8259A
seg002:1161                 jmp     short $+2
seg002:1163 ; ---------------------------------------------------------------------------
seg002:1163
seg002:1163 loc_120A3:                              ; CODE XREF: sub_12087+1A↑j
seg002:1163                 jmp     short $+2
seg002:1165 ; ---------------------------------------------------------------------------
seg002:1165
seg002:1165 loc_120A5:                              ; CODE XREF: sub_12087:loc_120A3↑j
seg002:1165                 or      al, ah
seg002:1167                 out     dx, al          ; Interrupt Controller #2, 8259A
seg002:1168                 jmp     short $+2
seg002:116A ; ---------------------------------------------------------------------------
seg002:116A
seg002:116A loc_120AA:                              ; CODE XREF: sub_12087+21↑j
seg002:116A                 jmp     short $+2
seg002:116C ; ---------------------------------------------------------------------------
seg002:116C
seg002:116C loc_120AC:                              ; CODE XREF: sub_12087:loc_120AA↑j
seg002:116C                 popf
seg002:116D                 pop     dx
seg002:116E                 pop     ax
seg002:116F                 retn
seg002:116F sub_12087       endp
seg002:116F
seg002:1170
seg002:1170 ; =============== S U B R O U T I N E =======================================
seg002:1170
seg002:1170
seg002:1170 sub_120B0       proc near               ; CODE XREF: sub_1212E+A↓p
seg002:1170                 push    bx
seg002:1171                 mov     bx, ds:232Dh
seg002:1175                 call    sub_110F5
seg002:1178                 mov     bx, cs
seg002:117A                 cmp     dx, bx
seg002:117C                 jnz     short loc_120C6
seg002:117E                 cmp     ax, 0F90h
seg002:1181                 jnz     short loc_120C6
seg002:1183                 clc
seg002:1184                 jmp     short loc_120C7
seg002:1186 ; ---------------------------------------------------------------------------
seg002:1186
seg002:1186 loc_120C6:                              ; CODE XREF: sub_120B0+C↑j
seg002:1186                                         ; sub_120B0+11↑j
seg002:1186                 stc
seg002:1187
seg002:1187 loc_120C7:                              ; CODE XREF: sub_120B0+14↑j
seg002:1187                 pop     bx
seg002:1188                 retn
seg002:1188 sub_120B0       endp
seg002:1188
seg002:1189
seg002:1189 ; =============== S U B R O U T I N E =======================================
seg002:1189
seg002:1189
seg002:1189 sub_120C9       proc near               ; CODE XREF: sub_12246+74↓p
seg002:1189                 push    ax
seg002:118A                 push    bx
seg002:118B                 push    cx
seg002:118C                 push    dx
seg002:118D                 pushf
seg002:118E                 cli
seg002:118F                 mov     al, ds:2083h
seg002:1192                 cmp     al, 8
seg002:1194                 jnb     short loc_120DA
seg002:1196                 add     al, 8
seg002:1198                 jmp     short loc_120DE
seg002:119A ; ---------------------------------------------------------------------------
seg002:119A
seg002:119A loc_120DA:                              ; CODE XREF: sub_120C9+B↑j
seg002:119A                 sub     al, 8
seg002:119C                 add     al, 70h ; 'p'
seg002:119E
seg002:119E loc_120DE:                              ; CODE XREF: sub_120C9+F↑j
seg002:119E                 sub     ah, ah
seg002:11A0                 mov     ds:232Dh, ax
seg002:11A3                 mov     bx, ds:232Dh
seg002:11A7                 call    sub_110F5
seg002:11AA                 mov     ds:22FEh, dx
seg002:11AE                 mov     ds:22FCh, ax
seg002:11B1                 mov     bx, ds:232Dh
seg002:11B5                 mov     dx, cs
seg002:11B7                 mov     ax, 0F90h
seg002:11BA                 call    sub_110E0
seg002:11BD                 mov     cl, ds:2083h
seg002:11C1                 cmp     cl, 8
seg002:11C4                 jnb     short loc_1210B
seg002:11C6                 mov     dx, 21h ; '!'
seg002:11C9                 jmp     short loc_12111
seg002:11CB ; ---------------------------------------------------------------------------
seg002:11CB
seg002:11CB loc_1210B:                              ; CODE XREF: sub_120C9+3B↑j
seg002:11CB                 mov     dx, 0A1h
seg002:11CE                 sub     cl, 8
seg002:11D1
seg002:11D1 loc_12111:                              ; CODE XREF: sub_120C9+40↑j
seg002:11D1                 mov     ax, 100h
seg002:11D4                 shl     ah, cl
seg002:11D6                 in      al, dx          ; Interrupt Controller #2, 8259A
seg002:11D7                 and     al, ah
seg002:11D9                 mov     ds:232Ah, al
seg002:11DC                 mov     cl, ds:2083h
seg002:11E0                 call    sub_1205C
seg002:11E3                 mov     byte ptr ds:2330h, 1
seg002:11E8                 popf
seg002:11E9                 pop     dx
seg002:11EA                 pop     cx
seg002:11EB                 pop     bx
seg002:11EC                 pop     ax
seg002:11ED                 retn
seg002:11ED sub_120C9       endp
seg002:11ED
seg002:11EE
seg002:11EE ; =============== S U B R O U T I N E =======================================
seg002:11EE
seg002:11EE
seg002:11EE sub_1212E       proc near               ; CODE XREF: sub_1125B:loc_11282↑p
seg002:11EE                                         ; sub_122E0+1B↓p
seg002:11EE                 push    dx
seg002:11EF                 pushf
seg002:11F0                 cli
seg002:11F1                 cmp     byte ptr ds:2330h, 0
seg002:11F6                 jz      short loc_12165
seg002:11F8                 call    sub_120B0
seg002:11FB                 jb      short loc_12165
seg002:11FD                 cmp     byte ptr ds:2083h, 8
seg002:1202                 jnb     short loc_12149
seg002:1204                 mov     dx, 21h ; '!'
seg002:1207                 jmp     short loc_1214C
seg002:1209 ; ---------------------------------------------------------------------------
seg002:1209
seg002:1209 loc_12149:                              ; CODE XREF: sub_1212E+14↑j
seg002:1209                 mov     dx, 0A1h
seg002:120C
seg002:120C loc_1214C:                              ; CODE XREF: sub_1212E+19↑j
seg002:120C                 in      al, dx          ; Interrupt Controller #2, 8259A
seg002:120D                 or      al, ds:232Ah
seg002:1211                 out     dx, al          ; Interrupt Controller #2, 8259A
seg002:1212                 mov     bx, ds:232Dh
seg002:1216                 mov     dx, ds:22FEh
seg002:121A                 mov     ax, ds:22FCh
seg002:121D                 call    sub_110E0
seg002:1220                 mov     byte ptr ds:2330h, 0
seg002:1225
seg002:1225 loc_12165:                              ; CODE XREF: sub_1212E+8↑j
seg002:1225                                         ; sub_1212E+D↑j
seg002:1225                 popf
seg002:1226                 pop     dx
seg002:1227                 retn
seg002:1227 sub_1212E       endp
seg002:1227
seg002:1228
seg002:1228 ; =============== S U B R O U T I N E =======================================
seg002:1228
seg002:1228
seg002:1228 sub_12168       proc near               ; CODE XREF: sub_12246+6B↓p
seg002:1228                 push    ax
seg002:1229                 pushf
seg002:122A                 cli
seg002:122B                 mov     word ptr ds:2079h, 0
seg002:1231                 mov     word ptr ds:207Bh, 0
seg002:1237                 cmp     byte ptr ds:22F7h, 0
seg002:123C                 jnz     short loc_1218F
seg002:123E                 mov     ax, ds:22F8h
seg002:1241                 cmp     ds:2071h, ax
seg002:1245                 jnb     short loc_1218D
seg002:1247                 mov     ax, ds:2071h
seg002:124A                 mov     ds:22F8h, ax
seg002:124D
seg002:124D loc_1218D:                              ; CODE XREF: sub_12168+1D↑j
seg002:124D                 jmp     short loc_12192
seg002:124F ; ---------------------------------------------------------------------------
seg002:124F
seg002:124F loc_1218F:                              ; CODE XREF: sub_12168+14↑j
seg002:124F                 mov     ax, ds:2073h
seg002:1252
seg002:1252 loc_12192:                              ; CODE XREF: sub_12168:loc_1218D↑j
seg002:1252                 call    sub_118DD
seg002:1255                 popf
seg002:1256                 pop     ax
seg002:1257                 retn
seg002:1257 sub_12168       endp
seg002:1257
seg002:1258
seg002:1258 ; =============== S U B R O U T I N E =======================================
seg002:1258
seg002:1258
seg002:1258 sub_12198       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:1258                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:1258                 cmp     byte ptr ds:206Dh, 0
seg002:125D                 jz      short loc_121BE
seg002:125F                 cmp     byte ptr ds:2083h, 0FFh
seg002:1264                 jnz     short loc_121AB
seg002:1266                 mov     ax, 1
seg002:1269                 jmp     short loc_121BC
seg002:126B ; ---------------------------------------------------------------------------
seg002:126B
seg002:126B loc_121AB:                              ; CODE XREF: sub_12198+C↑j
seg002:126B                 xchg    dx, ds:2314h
seg002:126F                 xchg    ax, ds:2312h
seg002:1273                 push    ax
seg002:1274                 sub     ax, ax
seg002:1276                 call    sub_11E11
seg002:1279                 pop     ax
seg002:127A                 xor     ax, ax
seg002:127C
seg002:127C loc_121BC:                              ; CODE XREF: sub_12198+11↑j
seg002:127C                 jmp     short locret_121C1
seg002:127E ; ---------------------------------------------------------------------------
seg002:127E
seg002:127E loc_121BE:                              ; CODE XREF: sub_12198+5↑j
seg002:127E                 mov     ax, 1
seg002:1281
seg002:1281 locret_121C1:                           ; CODE XREF: sub_12198:loc_121BC↑j
seg002:1281                 retn
seg002:1281 sub_12198       endp
seg002:1281
seg002:1282
seg002:1282 ; =============== S U B R O U T I N E =======================================
seg002:1282
seg002:1282
seg002:1282 sub_121C2       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:1282                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:1282                 cmp     byte ptr ds:2083h, 0FFh
seg002:1287                 jnz     short loc_121CE
seg002:1289                 mov     ax, 1
seg002:128C                 jmp     short locret_121D3
seg002:128E ; ---------------------------------------------------------------------------
seg002:128E
seg002:128E loc_121CE:                              ; CODE XREF: sub_121C2+5↑j
seg002:128E                 mov     ds:232Fh, al
seg002:1291                 xor     ax, ax
seg002:1293
seg002:1293 locret_121D3:                           ; CODE XREF: sub_121C2+A↑j
seg002:1293                 retn
seg002:1293 sub_121C2       endp
seg002:1293
seg002:1294
seg002:1294 ; =============== S U B R O U T I N E =======================================
seg002:1294
seg002:1294
seg002:1294 sub_121D4       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:1294                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:1294                 push    cx
seg002:1295                 cmp     byte ptr ds:206Dh, 0
seg002:129A                 jz      short loc_12216
seg002:129C                 cmp     byte ptr ds:2083h, 0FFh
seg002:12A1                 jnz     short loc_121E8
seg002:12A3                 mov     ax, 1
seg002:12A6                 jmp     short loc_12214
seg002:12A8 ; ---------------------------------------------------------------------------
seg002:12A8
seg002:12A8 loc_121E8:                              ; CODE XREF: sub_121D4+D↑j
seg002:12A8                 dec     cx
seg002:12A9                 mov     ds:2304h, cx
seg002:12AD                 mov     ds:2306h, di
seg002:12B1                 call    sub_11E30
seg002:12B4                 mov     ds:2316h, ax
seg002:12B7                 add     ax, 4
seg002:12BA                 mov     ds:231Ah, ax
seg002:12BD                 mov     ds:2318h, dx
seg002:12C1                 adc     dx, 0
seg002:12C4                 mov     ds:231Ch, dx
seg002:12C8                 mov     byte ptr ds:232Ch, 1
seg002:12CD                 mov     byte ptr ds:232Bh, 0
seg002:12D2                 xor     ax, ax
seg002:12D4
seg002:12D4 loc_12214:                              ; CODE XREF: sub_121D4+12↑j
seg002:12D4                 jmp     short loc_12219
seg002:12D6 ; ---------------------------------------------------------------------------
seg002:12D6
seg002:12D6 loc_12216:                              ; CODE XREF: sub_121D4+6↑j
seg002:12D6                 mov     ax, 1
seg002:12D9
seg002:12D9 loc_12219:                              ; CODE XREF: sub_121D4:loc_12214↑j
seg002:12D9                 pop     cx
seg002:12DA                 retn
seg002:12DA sub_121D4       endp
seg002:12DA
seg002:12DB
seg002:12DB ; =============== S U B R O U T I N E =======================================
seg002:12DB
seg002:12DB
seg002:12DB sub_1221B       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:12DB                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:12DB                 cmp     byte ptr ds:206Dh, 0
seg002:12E0                 jz      short loc_12242
seg002:12E2                 cmp     byte ptr ds:2083h, 0FFh
seg002:12E7                 jnz     short loc_1222E
seg002:12E9                 mov     ax, 1
seg002:12EC                 jmp     short loc_12240
seg002:12EE ; ---------------------------------------------------------------------------
seg002:12EE
seg002:12EE loc_1222E:                              ; CODE XREF: sub_1221B+C↑j
seg002:12EE                 xchg    dx, ds:2320h
seg002:12F2                 xchg    ax, ds:231Eh
seg002:12F6                 xchg    di, ds:2324h
seg002:12FA                 xchg    cx, ds:2322h
seg002:12FE                 xor     ax, ax
seg002:1300
seg002:1300 loc_12240:                              ; CODE XREF: sub_1221B+11↑j
seg002:1300                 jmp     short locret_12245
seg002:1302 ; ---------------------------------------------------------------------------
seg002:1302
seg002:1302 loc_12242:                              ; CODE XREF: sub_1221B+5↑j
seg002:1302                 mov     ax, 1
seg002:1305
seg002:1305 locret_12245:                           ; CODE XREF: sub_1221B:loc_12240↑j
seg002:1305                 retn
seg002:1305 sub_1221B       endp
seg002:1305
seg002:1306
seg002:1306 ; =============== S U B R O U T I N E =======================================
seg002:1306
seg002:1306
seg002:1306 sub_12246       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:1306                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:1306                 pushf
seg002:1307                 cli
seg002:1308                 cmp     byte ptr ds:206Dh, 0
seg002:130D                 jz      short loc_122CB
seg002:130F                 cmp     word ptr ds:2394h, 0
seg002:1314                 jnz     short loc_122C6
seg002:1316                 cmp     word ptr ds:207Dh, 0FFFFh
seg002:131B                 jz      short loc_1226B
seg002:131D                 cmp     byte ptr ds:2083h, 0FFh
seg002:1322                 jz      short loc_1226B
seg002:1324                 call    sub_1264C
seg002:1327                 jb      short loc_1226B
seg002:1329                 jmp     short loc_12270
seg002:132B ; ---------------------------------------------------------------------------
seg002:132B
seg002:132B loc_1226B:                              ; CODE XREF: sub_12246+15↑j
seg002:132B                                         ; sub_12246+1C↑j ...
seg002:132B                 mov     ax, 1
seg002:132E                 jmp     short loc_122C4
seg002:1330 ; ---------------------------------------------------------------------------
seg002:1330
seg002:1330 loc_12270:                              ; CODE XREF: sub_12246+23↑j
seg002:1330                 mov     ax, ds:22F8h
seg002:1333                 cmp     ax, ds:22EAh
seg002:1337                 jnb     short loc_1227E
seg002:1339                 mov     ax, 1
seg002:133C                 jmp     short loc_122C4
seg002:133E ; ---------------------------------------------------------------------------
seg002:133E
seg002:133E loc_1227E:                              ; CODE XREF: sub_12246+31↑j
seg002:133E                 push    es
seg002:133F                 push    di
seg002:1340                 push    ax
seg002:1341                 les     di, ds:2316h
seg002:1345                 mov     ax, ds:2308h
seg002:1348                 stosw
seg002:1349                 mov     ax, ds:230Ah
seg002:134C                 stosw
seg002:134D                 pop     ax
seg002:134E                 pop     di
seg002:134F                 pop     es
seg002:1350                 clc
seg002:1351                 cmp     word ptr ds:2397h, 0
seg002:1356                 jnz     short loc_1229D
seg002:1358                 call    sub_1251F
seg002:135B                 jmp     short loc_122A7
seg002:135D ; ---------------------------------------------------------------------------
seg002:135D
seg002:135D loc_1229D:                              ; CODE XREF: sub_12246+50↑j
seg002:135D                 cmp     word ptr ds:233Eh, 0
seg002:1362                 jnz     short loc_122A7
seg002:1364                 call    sub_1251F
seg002:1367
seg002:1367 loc_122A7:                              ; CODE XREF: sub_12246+55↑j
seg002:1367                                         ; sub_12246+5C↑j
seg002:1367                 jnb     short loc_122AE
seg002:1369                 mov     ax, 1
seg002:136C                 jmp     short loc_122C4
seg002:136E ; ---------------------------------------------------------------------------
seg002:136E
seg002:136E loc_122AE:                              ; CODE XREF: sub_12246:loc_122A7↑j
seg002:136E                 call    sub_1250B
seg002:1371                 call    sub_12168
seg002:1374                 mov     ax, 0FFFFh
seg002:1377                 call    sub_11E11
seg002:137A                 call    sub_120C9
seg002:137D                 mov     byte ptr ds:2332h, 0
seg002:1382                 xor     ax, ax
seg002:1384
seg002:1384 loc_122C4:                              ; CODE XREF: sub_12246+28↑j
seg002:1384                                         ; sub_12246+36↑j ...
seg002:1384                 jmp     short loc_122CE
seg002:1386 ; ---------------------------------------------------------------------------
seg002:1386
seg002:1386 loc_122C6:                              ; CODE XREF: sub_12246+E↑j
seg002:1386                 mov     ax, 1
seg002:1389                 jmp     short loc_122CE
seg002:138B ; ---------------------------------------------------------------------------
seg002:138B
seg002:138B loc_122CB:                              ; CODE XREF: sub_12246+7↑j
seg002:138B                 mov     ax, 1
seg002:138E
seg002:138E loc_122CE:                              ; CODE XREF: sub_12246:loc_122C4↑j
seg002:138E                                         ; sub_12246+83↑j
seg002:138E                 popf
seg002:138F                 retn
seg002:138F sub_12246       endp
seg002:138F
seg002:1390
seg002:1390 ; =============== S U B R O U T I N E =======================================
seg002:1390
seg002:1390
seg002:1390 sub_122D0       proc near               ; CODE XREF: sub_10FF0+3D↑p
seg002:1390                                         ; DATA XREF: seg002:funcs_1102D↓o
seg002:1390                 cmp     word ptr ds:2394h, 0
seg002:1395                 jz      short locret_122DF
seg002:1397                 pushf
seg002:1398                 cli
seg002:1399                 call    sub_122E0
seg002:139C                 xor     ax, ax
seg002:139E                 popf
seg002:139F
seg002:139F locret_122DF:                           ; CODE XREF: sub_122D0+5↑j
seg002:139F                 retn
seg002:139F sub_122D0       endp
seg002:139F
seg002:13A0
seg002:13A0 ; =============== S U B R O U T I N E =======================================
seg002:13A0
seg002:13A0
seg002:13A0 sub_122E0       proc near               ; CODE XREF: sub_11ED0+11A↑p
seg002:13A0                                         ; sub_122D0+9↑p
seg002:13A0                 pushf
seg002:13A1                 cli
seg002:13A2                 push    dx
seg002:13A3                 cmp     word ptr ds:2397h, 0
seg002:13A8                 jnz     short loc_122F3
seg002:13AA                 mov     ax, ds:2071h
seg002:13AD                 call    sub_118DD
seg002:13B0                 call    sub_12591
seg002:13B3
seg002:13B3 loc_122F3:                              ; CODE XREF: sub_122E0+8↑j
seg002:13B3                 call    sub_124F7
seg002:13B6                 sub     ax, ax
seg002:13B8                 call    sub_11E11
seg002:13BB                 call    sub_1212E
seg002:13BE                 push    es
seg002:13BF                 push    di
seg002:13C0                 push    ax
seg002:13C1                 cmp     byte ptr ds:2332h, 1
seg002:13C6                 jz      short loc_1230F
seg002:13C8
seg002:13C8 loc_12308:                              ; CODE XREF: sub_122E0+2D↓j
seg002:13C8                 cmp     byte ptr ds:2331h, 1
seg002:13CD                 jz      short loc_12308
seg002:13CF
seg002:13CF loc_1230F:                              ; CODE XREF: sub_122E0+26↑j
seg002:13CF                 mov     byte ptr ds:2332h, 0
seg002:13D4                 cli
seg002:13D5                 les     di, ds:2316h
seg002:13D9                 mov     ax, ds:2308h
seg002:13DC                 stosw
seg002:13DD                 mov     ax, ds:230Ah
seg002:13E0                 stosw
seg002:13E1                 pop     ax
seg002:13E2                 pop     di
seg002:13E3                 pop     es
seg002:13E4                 pop     dx
seg002:13E5                 popf
seg002:13E6                 retn
seg002:13E6 sub_122E0       endp
seg002:13E6
seg002:13E6 ; ---------------------------------------------------------------------------
seg002:13E7                 align 2
seg002:13E8
seg002:13E8 ; =============== S U B R O U T I N E =======================================
seg002:13E8
seg002:13E8
seg002:13E8 sub_12328       proc near               ; CODE XREF: sub_11213:loc_1121F↑p
seg002:13E8                                         ; sub_116EA+21↑p
seg002:13E8                 cmp     word ptr ds:233Eh, 1
seg002:13ED                 jz      short loc_12348
seg002:13EF                 mov     ax, ds:207Dh
seg002:13F2                 cmp     ax, 0FFFFh
seg002:13F5                 jnz     short loc_1233C
seg002:13F7                 mov     ax, 1
seg002:13FA                 jmp     short locret_12362
seg002:13FC ; ---------------------------------------------------------------------------
seg002:13FC
seg002:13FC loc_1233C:                              ; CODE XREF: sub_12328+D↑j
seg002:13FC                 call    sub_126AA
seg002:13FF                 or      ax, ax
seg002:1401                 jz      short locret_12362
seg002:1403                 mov     ax, 2
seg002:1406                 jmp     short locret_12362
seg002:1408 ; ---------------------------------------------------------------------------
seg002:1408
seg002:1408 loc_12348:                              ; CODE XREF: sub_12328+5↑j
seg002:1408                 cmp     word ptr ds:207Fh, 0FFFFh
seg002:140D                 jnz     short loc_12354
seg002:140F                 mov     ax, 3
seg002:1412                 jmp     short locret_12362
seg002:1414 ; ---------------------------------------------------------------------------
seg002:1414
seg002:1414 loc_12354:                              ; CODE XREF: sub_12328+25↑j
seg002:1414                 call    sub_1264C
seg002:1417                 jnb     short loc_1235E
seg002:1419                 mov     ax, 4
seg002:141C                 jmp     short locret_12362
seg002:141E ; ---------------------------------------------------------------------------
seg002:141E
seg002:141E loc_1235E:                              ; CODE XREF: sub_12328+2F↑j
seg002:141E                 xor     ax, ax
seg002:1420                 sub     ax, ax
seg002:1422
seg002:1422 locret_12362:                           ; CODE XREF: sub_12328+12↑j
seg002:1422                                         ; sub_12328+19↑j ...
seg002:1422                 retn
seg002:1422 sub_12328       endp
seg002:1422
seg002:1423
seg002:1423 ; =============== S U B R O U T I N E =======================================
seg002:1423
seg002:1423
seg002:1423 sub_12363       proc near               ; CODE XREF: sub_11434+7↑p
seg002:1423                                         ; sub_1157C+D↑p ...
seg002:1423                 cmp     word ptr ds:233Eh, 0
seg002:1428                 jz      short loc_1236F
seg002:142A                 call    sub_124DA
seg002:142D                 jmp     short locret_12372
seg002:142F ; ---------------------------------------------------------------------------
seg002:142F
seg002:142F loc_1236F:                              ; CODE XREF: sub_12363+5↑j
seg002:142F                 call    sub_127BB
seg002:1432
seg002:1432 locret_12372:                           ; CODE XREF: sub_12363+A↑j
seg002:1432                 retn
seg002:1432 sub_12363       endp
seg002:1432
seg002:1433
seg002:1433 ; =============== S U B R O U T I N E =======================================
seg002:1433
seg002:1433
seg002:1433 sub_12373       proc near               ; CODE XREF: sub_11464+1↑p
seg002:1433                                         ; sub_115AC+7↑p ...
seg002:1433                 cmp     word ptr ds:233Eh, 0
seg002:1438                 jz      short loc_1237F
seg002:143A                 call    sub_12475
seg002:143D                 jmp     short locret_12382
seg002:143F ; ---------------------------------------------------------------------------
seg002:143F
seg002:143F loc_1237F:                              ; CODE XREF: sub_12373+5↑j
seg002:143F                 call    sub_129C4
seg002:1442
seg002:1442 locret_12382:                           ; CODE XREF: sub_12373+A↑j
seg002:1442                 retn
seg002:1442 sub_12373       endp
seg002:1442
seg002:1443
seg002:1443 ; =============== S U B R O U T I N E =======================================
seg002:1443
seg002:1443
seg002:1443 sub_12383       proc near               ; CODE XREF: sub_11434↑p
seg002:1443                                         ; sub_1157C+A↑p
seg002:1443                 cmp     word ptr ds:233Eh, 0
seg002:1448                 jz      short loc_1239C
seg002:144A                 cmp     word ptr ds:2394h, 0
seg002:144F                 jnz     short loc_12398
seg002:1451                 call    sub_1251F
seg002:1454                 xor     ax, ax
seg002:1456                 jmp     short loc_1239A
seg002:1458 ; ---------------------------------------------------------------------------
seg002:1458
seg002:1458 loc_12398:                              ; CODE XREF: sub_12383+C↑j
seg002:1458                 xor     ax, ax
seg002:145A
seg002:145A loc_1239A:                              ; CODE XREF: sub_12383+13↑j
seg002:145A                 jmp     short locret_123A1
seg002:145C ; ---------------------------------------------------------------------------
seg002:145C
seg002:145C loc_1239C:                              ; CODE XREF: sub_12383+5↑j
seg002:145C                 call    sub_126ED
seg002:145F                 xor     ax, ax
seg002:1461
seg002:1461 locret_123A1:                           ; CODE XREF: sub_12383:loc_1239A↑j
seg002:1461                 retn
seg002:1461 sub_12383       endp
seg002:1461
seg002:1462
seg002:1462 ; =============== S U B R O U T I N E =======================================
seg002:1462
seg002:1462
seg002:1462 sub_123A2       proc near               ; CODE XREF: sub_11464+4↑p
seg002:1462                 cmp     word ptr ds:233Eh, 0
seg002:1467                 jz      short loc_123AB
seg002:1469                 jmp     short locret_123AE
seg002:146B ; ---------------------------------------------------------------------------
seg002:146B
seg002:146B loc_123AB:                              ; CODE XREF: sub_123A2+5↑j
seg002:146B                 call    sub_12752
seg002:146E
seg002:146E locret_123AE:                           ; CODE XREF: sub_123A2+7↑j
seg002:146E                 retn
seg002:146E sub_123A2       endp
seg002:146E
seg002:146F
seg002:146F ; =============== S U B R O U T I N E =======================================
seg002:146F
seg002:146F
seg002:146F sub_123AF       proc near               ; CODE XREF: sub_123C2↓p
seg002:146F                                         ; sub_123D8+4↓p ...
seg002:146F                 push    ax
seg002:1470                 mov     al, ds:2A0Ch
seg002:1473                 call    sub_12468
seg002:1476                 pop     ax
seg002:1477                 xchg    ah, al
seg002:1479                 call    sub_12468
seg002:147C                 xchg    ah, al
seg002:147E                 call    sub_12468
seg002:1481                 retn
seg002:1481 sub_123AF       endp
seg002:1481
seg002:1482
seg002:1482 ; =============== S U B R O U T I N E =======================================
seg002:1482
seg002:1482
seg002:1482 sub_123C2       proc near               ; CODE XREF: sub_123C6↓j
seg002:1482                                         ; sub_123C8+7↓p
seg002:1482                 call    sub_123AF
seg002:1485                 retn
seg002:1485 sub_123C2       endp
seg002:1485
seg002:1486
seg002:1486 ; =============== S U B R O U T I N E =======================================
seg002:1486
seg002:1486
seg002:1486 sub_123C6       proc near               ; CODE XREF: sub_123D8+2↓j
seg002:1486                 jmp     short sub_123C2
seg002:1486 sub_123C6       endp
seg002:1486
seg002:1488
seg002:1488 ; =============== S U B R O U T I N E =======================================
seg002:1488
seg002:1488
seg002:1488 sub_123C8       proc near               ; CODE XREF: sub_11A9D:loc_11AD2↑p
seg002:1488                 cmp     word ptr ds:233Eh, 0
seg002:148D                 jz      short loc_123D4
seg002:148F                 call    sub_123C2
seg002:1492                 jmp     short locret_123D7
seg002:1494 ; ---------------------------------------------------------------------------
seg002:1494
seg002:1494 loc_123D4:                              ; CODE XREF: sub_123C8+5↑j
seg002:1494                 call    sub_12D5F
seg002:1497
seg002:1497 locret_123D7:                           ; CODE XREF: sub_123C8+A↑j
seg002:1497                 retn
seg002:1497 sub_123C8       endp
seg002:1497
seg002:1498
seg002:1498 ; =============== S U B R O U T I N E =======================================
seg002:1498
seg002:1498
seg002:1498 sub_123D8       proc near               ; CODE XREF: sub_123E0+7↓p
seg002:1498                 or      al, al
seg002:149A                 jz      short sub_123C6
seg002:149C                 call    sub_123AF
seg002:149F                 retn
seg002:149F sub_123D8       endp
seg002:149F
seg002:14A0
seg002:14A0 ; =============== S U B R O U T I N E =======================================
seg002:14A0
seg002:14A0
seg002:14A0 sub_123E0       proc near               ; CODE XREF: sub_11B08+9↑p
seg002:14A0                 cmp     word ptr ds:233Eh, 0
seg002:14A5                 jz      short loc_123EC
seg002:14A7                 call    sub_123D8
seg002:14AA                 jmp     short locret_123EF
seg002:14AC ; ---------------------------------------------------------------------------
seg002:14AC
seg002:14AC loc_123EC:                              ; CODE XREF: sub_123E0+5↑j
seg002:14AC                 call    sub_12DD3
seg002:14AF
seg002:14AF locret_123EF:                           ; CODE XREF: sub_123E0+A↑j
seg002:14AF                 retn
seg002:14AF sub_123E0       endp
seg002:14AF
seg002:14B0
seg002:14B0 ; =============== S U B R O U T I N E =======================================
seg002:14B0
seg002:14B0
seg002:14B0 sub_123F0       proc near               ; CODE XREF: sub_123F4+7↓p
seg002:14B0                 call    sub_123AF
seg002:14B3                 retn
seg002:14B3 sub_123F0       endp
seg002:14B3
seg002:14B4
seg002:14B4 ; =============== S U B R O U T I N E =======================================
seg002:14B4
seg002:14B4
seg002:14B4 sub_123F4       proc near               ; CODE XREF: sub_11B16+F↑p
seg002:14B4                 cmp     word ptr ds:233Eh, 0
seg002:14B9                 jz      short locret_123FE
seg002:14BB                 call    sub_123F0
seg002:14BE
seg002:14BE locret_123FE:                           ; CODE XREF: sub_123F4+5↑j
seg002:14BE                 retn
seg002:14BE sub_123F4       endp
seg002:14BE
seg002:14BF
seg002:14BF ; =============== S U B R O U T I N E =======================================
seg002:14BF
seg002:14BF
seg002:14BF sub_123FF       proc near               ; CODE XREF: sub_12403+7↓p
seg002:14BF                 call    sub_123AF
seg002:14C2                 retn
seg002:14C2 sub_123FF       endp
seg002:14C2
seg002:14C3
seg002:14C3 ; =============== S U B R O U T I N E =======================================
seg002:14C3
seg002:14C3
seg002:14C3 sub_12403       proc near               ; CODE XREF: sub_11B29+F↑p
seg002:14C3                 cmp     word ptr ds:233Eh, 0
seg002:14C8                 jz      short loc_1240F
seg002:14CA                 call    sub_123FF
seg002:14CD                 jmp     short locret_12412
seg002:14CF ; ---------------------------------------------------------------------------
seg002:14CF
seg002:14CF loc_1240F:                              ; CODE XREF: sub_12403+5↑j
seg002:14CF                 call    sub_12E50
seg002:14D2
seg002:14D2 locret_12412:                           ; CODE XREF: sub_12403+A↑j
seg002:14D2                 retn
seg002:14D2 sub_12403       endp
seg002:14D2
seg002:14D3
seg002:14D3 ; =============== S U B R O U T I N E =======================================
seg002:14D3
seg002:14D3
seg002:14D3 sub_12413       proc near               ; CODE XREF: sub_1241F+7↓p
seg002:14D3                 push    ax
seg002:14D4                 mov     al, ds:2A0Ch
seg002:14D7                 call    sub_12468
seg002:14DA                 pop     ax
seg002:14DB                 call    sub_12468
seg002:14DE                 retn
seg002:14DE sub_12413       endp
seg002:14DE
seg002:14DF
seg002:14DF ; =============== S U B R O U T I N E =======================================
seg002:14DF
seg002:14DF
seg002:14DF sub_1241F       proc near               ; CODE XREF: sub_11B3C+C↑p
seg002:14DF                 cmp     word ptr ds:233Eh, 0
seg002:14E4                 jz      short loc_1242B
seg002:14E6                 call    sub_12413
seg002:14E9                 jmp     short locret_1242E
seg002:14EB ; ---------------------------------------------------------------------------
seg002:14EB
seg002:14EB loc_1242B:                              ; CODE XREF: sub_1241F+5↑j
seg002:14EB                 call    sub_12E7E
seg002:14EE
seg002:14EE locret_1242E:                           ; CODE XREF: sub_1241F+A↑j
seg002:14EE                 retn
seg002:14EE sub_1241F       endp
seg002:14EE
seg002:14EF
seg002:14EF ; =============== S U B R O U T I N E =======================================
seg002:14EF
seg002:14EF
seg002:14EF sub_1242F       proc near               ; CODE XREF: sub_1243B+7↓p
seg002:14EF                 push    ax
seg002:14F0                 mov     al, ds:2A0Ch
seg002:14F3                 call    sub_12468
seg002:14F6                 pop     ax
seg002:14F7                 call    sub_12468
seg002:14FA                 retn
seg002:14FA sub_1242F       endp
seg002:14FA
seg002:14FB
seg002:14FB ; =============== S U B R O U T I N E =======================================
seg002:14FB
seg002:14FB
seg002:14FB sub_1243B       proc near               ; CODE XREF: sub_11B4C+C↑p
seg002:14FB                 cmp     word ptr ds:233Eh, 0
seg002:1500                 jz      short locret_12445
seg002:1502                 call    sub_1242F
seg002:1505
seg002:1505 locret_12445:                           ; CODE XREF: sub_1243B+5↑j
seg002:1505                 retn
seg002:1505 sub_1243B       endp
seg002:1505
seg002:1506
seg002:1506 ; =============== S U B R O U T I N E =======================================
seg002:1506
seg002:1506
seg002:1506 sub_12446       proc near               ; CODE XREF: sub_1244A+7↓p
seg002:1506                 call    sub_123AF
seg002:1509                 retn
seg002:1509 sub_12446       endp
seg002:1509
seg002:150A
seg002:150A ; =============== S U B R O U T I N E =======================================
seg002:150A
seg002:150A
seg002:150A sub_1244A       proc near               ; CODE XREF: sub_11B5C+F↑p
seg002:150A                 cmp     word ptr ds:233Eh, 0
seg002:150F                 jz      short loc_12456
seg002:1511                 call    sub_12446
seg002:1514                 jmp     short locret_12459
seg002:1516 ; ---------------------------------------------------------------------------
seg002:1516
seg002:1516 loc_12456:                              ; CODE XREF: sub_1244A+5↑j
seg002:1516                 call    sub_12ECA
seg002:1519
seg002:1519 locret_12459:                           ; CODE XREF: sub_1244A+A↑j
seg002:1519                 retn
seg002:1519 sub_1244A       endp
seg002:1519
seg002:151A
seg002:151A ; =============== S U B R O U T I N E =======================================
seg002:151A
seg002:151A
seg002:151A sub_1245A       proc near               ; CODE XREF: sub_11B7D↑p
seg002:151A                 cmp     word ptr ds:233Eh, 0
seg002:151F                 jz      short locret_12466
seg002:1521                 call    sub_117F3
seg002:1524                 jmp     short $+2
seg002:1526 ; ---------------------------------------------------------------------------
seg002:1526
seg002:1526 locret_12466:                           ; CODE XREF: sub_1245A+5↑j
seg002:1526                                         ; sub_1245A+A↑j
seg002:1526                 retn
seg002:1526 sub_1245A       endp
seg002:1526
seg002:1526 ; ---------------------------------------------------------------------------
seg002:1527                 align 2
seg002:1528
seg002:1528 ; =============== S U B R O U T I N E =======================================
seg002:1528
seg002:1528
seg002:1528 sub_12468       proc near               ; CODE XREF: sub_117F3+9↑p
seg002:1528                                         ; sub_117F3+17↑p ...
seg002:1528                 push    ax
seg002:1529                 push    dx
seg002:152A                 push    cx
seg002:152B                 pushf
seg002:152C                 cli
seg002:152D                 call    sub_125D2
seg002:1530                 popf
seg002:1531                 pop     cx
seg002:1532                 pop     dx
seg002:1533                 pop     ax
seg002:1534                 retn
seg002:1534 sub_12468       endp
seg002:1534
seg002:1535
seg002:1535 ; =============== S U B R O U T I N E =======================================
seg002:1535
seg002:1535
seg002:1535 sub_12475       proc near               ; CODE XREF: sub_12373+7↑p
seg002:1535                 push    ax
seg002:1536                 push    bx
seg002:1537                 push    cx
seg002:1538                 push    dx
seg002:1539
seg002:1539 loc_12479:                              ; CODE XREF: sub_12475+B↓j
seg002:1539                 cmp     byte ptr ds:2396h, 0
seg002:153E                 jz      short loc_12482
seg002:1540                 loop    loc_12479
seg002:1542
seg002:1542 loc_12482:                              ; CODE XREF: sub_12475+9↑j
seg002:1542                 pushf
seg002:1543                 cli
seg002:1544                 cmp     word ptr ds:233Eh, 1
seg002:1549                 jnz     short loc_1249C
seg002:154B                 cmp     word ptr ds:2397h, 0
seg002:1550                 jnz     short loc_1249C
seg002:1552                 cmp     byte ptr ds:2B0Fh, 1
seg002:1557                 jz      short loc_1249C
seg002:1559                 call    sub_1251F
seg002:155C
seg002:155C loc_1249C:                              ; CODE XREF: sub_12475+14↑j
seg002:155C                                         ; sub_12475+1B↑j ...
seg002:155C                 mov     ax, 0B0h
seg002:155F
seg002:155F loc_1249F:                              ; CODE XREF: sub_12475+5D↓j
seg002:155F                 call    sub_12468
seg002:1562                 push    ax
seg002:1563                 mov     al, 78h ; 'x'
seg002:1565                 call    sub_12468
seg002:1568                 mov     al, 0
seg002:156A                 call    sub_12468
seg002:156D                 pop     ax
seg002:156E                 call    sub_12468
seg002:1571                 push    ax
seg002:1572                 mov     al, 79h ; 'y'
seg002:1574                 call    sub_12468
seg002:1577                 mov     al, 0
seg002:1579                 call    sub_12468
seg002:157C                 pop     ax
seg002:157D                 call    sub_12468
seg002:1580                 push    ax
seg002:1581                 mov     al, 7Bh ; '{'
seg002:1583                 call    sub_12468
seg002:1586                 mov     al, 0
seg002:1588                 call    sub_12468
seg002:158B                 pop     ax
seg002:158C                 inc     al
seg002:158E                 test    al, 0Fh
seg002:1590                 jz      short loc_124D4
seg002:1592                 jmp     short loc_1249F
seg002:1594 ; ---------------------------------------------------------------------------
seg002:1594
seg002:1594 loc_124D4:                              ; CODE XREF: sub_12475+5B↑j
seg002:1594                 popf
seg002:1595                 pop     dx
seg002:1596                 pop     cx
seg002:1597                 pop     bx
seg002:1598                 pop     ax
seg002:1599                 retn
seg002:1599 sub_12475       endp
seg002:1599
seg002:159A
seg002:159A ; =============== S U B R O U T I N E =======================================
seg002:159A
seg002:159A
seg002:159A sub_124DA       proc near               ; CODE XREF: sub_12363+7↑p
seg002:159A                 push    ax
seg002:159B                 mov     ax, 0B0h
seg002:159E
seg002:159E loc_124DE:                              ; CODE XREF: sub_124DA+19↓j
seg002:159E                 call    sub_12468
seg002:15A1                 push    ax
seg002:15A2                 mov     al, 7
seg002:15A4                 call    sub_12468
seg002:15A7                 mov     al, 64h ; 'd'
seg002:15A9                 call    sub_12468
seg002:15AC                 pop     ax
seg002:15AD                 inc     al
seg002:15AF                 test    al, 0Fh
seg002:15B1                 jz      short loc_124F5
seg002:15B3                 jmp     short loc_124DE
seg002:15B5 ; ---------------------------------------------------------------------------
seg002:15B5
seg002:15B5 loc_124F5:                              ; CODE XREF: sub_124DA+17↑j
seg002:15B5                 pop     ax
seg002:15B6                 retn
seg002:15B6 sub_124DA       endp
seg002:15B6
seg002:15B7
seg002:15B7 ; =============== S U B R O U T I N E =======================================
seg002:15B7
seg002:15B7
seg002:15B7 sub_124F7       proc near               ; CODE XREF: sub_122E0:loc_122F3↑p
seg002:15B7                 push    ax
seg002:15B8                 push    dx
seg002:15B9                 mov     dx, ds:207Dh
seg002:15BD                 add     dx, 4
seg002:15C0                 mov     al, 83h
seg002:15C2                 out     dx, al
seg002:15C3                 inc     dx
seg002:15C4                 in      al, dx
seg002:15C5                 and     al, 0FBh
seg002:15C7                 out     dx, al
seg002:15C8                 pop     dx
seg002:15C9                 pop     ax
seg002:15CA                 retn
seg002:15CA sub_124F7       endp
seg002:15CA
seg002:15CB
seg002:15CB ; =============== S U B R O U T I N E =======================================
seg002:15CB
seg002:15CB
seg002:15CB sub_1250B       proc near               ; CODE XREF: sub_12246:loc_122AE↑p
seg002:15CB                 push    ax
seg002:15CC                 push    dx
seg002:15CD                 mov     dx, ds:207Dh
seg002:15D1                 add     dx, 4
seg002:15D4                 mov     al, 83h
seg002:15D6                 out     dx, al
seg002:15D7                 inc     dx
seg002:15D8                 in      al, dx
seg002:15D9                 or      al, 4
seg002:15DB                 out     dx, al
seg002:15DC                 pop     dx
seg002:15DD                 pop     ax
seg002:15DE                 retn
seg002:15DE sub_1250B       endp
seg002:15DE
seg002:15DF
seg002:15DF ; =============== S U B R O U T I N E =======================================
seg002:15DF
seg002:15DF
seg002:15DF sub_1251F       proc near               ; CODE XREF: sub_12246+52↑p
seg002:15DF                                         ; sub_12246+5E↑p ...
seg002:15DF                 push    ax
seg002:15E0                 push    cx
seg002:15E1                 push    dx
seg002:15E2                 pushf
seg002:15E3                 cli
seg002:15E4                 clc
seg002:15E5                 cmp     byte ptr ds:2B0Fh, 1
seg002:15EA                 jz      short loc_12587
seg002:15EC                 cmp     word ptr ds:2394h, 1
seg002:15F1                 jz      short loc_12587
seg002:15F3                 mov     cx, 2
seg002:15F6
seg002:15F6 loc_12536:                              ; CODE XREF: sub_1251F+30↓j
seg002:15F6                 push    cx
seg002:15F7                 mov     al, 0FFh
seg002:15F9                 mov     dx, ds:2081h
seg002:15FD                 out     dx, al
seg002:15FE                 mov     cx, 1000h
seg002:1601
seg002:1601 loc_12541:                              ; CODE XREF: sub_1251F+27↓j
seg002:1601                 in      al, dx
seg002:1602                 or      al, al
seg002:1604                 jns     short loc_1254B
seg002:1606                 loop    loc_12541
seg002:1608                 stc
seg002:1609                 jmp     short loc_1254C
seg002:160B ; ---------------------------------------------------------------------------
seg002:160B
seg002:160B loc_1254B:                              ; CODE XREF: sub_1251F+25↑j
seg002:160B                 clc
seg002:160C
seg002:160C loc_1254C:                              ; CODE XREF: sub_1251F+2A↑j
seg002:160C                 pop     cx
seg002:160D                 jnb     short loc_12553
seg002:160F                 loop    loc_12536
seg002:1611                 jmp     short loc_1257D
seg002:1613 ; ---------------------------------------------------------------------------
seg002:1613
seg002:1613 loc_12553:                              ; CODE XREF: sub_1251F+2E↑j
seg002:1613                 mov     dx, ds:207Fh
seg002:1617                 in      al, dx
seg002:1618                 xor     al, 0FEh
seg002:161A                 jnz     short loc_1257D
seg002:161C                 mov     al, 3Fh ; '?'
seg002:161E                 mov     dx, ds:2081h
seg002:1622                 out     dx, al
seg002:1623                 mov     cx, 1000h
seg002:1626
seg002:1626 loc_12566:                              ; CODE XREF: sub_1251F+4C↓j
seg002:1626                 in      al, dx
seg002:1627                 or      al, al
seg002:1629                 jns     short loc_12570
seg002:162B                 loop    loc_12566
seg002:162D                 stc
seg002:162E                 jmp     short loc_1257D
seg002:1630 ; ---------------------------------------------------------------------------
seg002:1630
seg002:1630 loc_12570:                              ; CODE XREF: sub_1251F+4A↑j
seg002:1630                 mov     dx, ds:207Fh
seg002:1634                 in      al, dx
seg002:1635                 xor     al, 0FEh
seg002:1637                 jz      short loc_1257C
seg002:1639                 stc
seg002:163A                 jmp     short loc_1257D
seg002:163C ; ---------------------------------------------------------------------------
seg002:163C
seg002:163C loc_1257C:                              ; CODE XREF: sub_1251F+58↑j
seg002:163C                 clc
seg002:163D
seg002:163D loc_1257D:                              ; CODE XREF: sub_1251F+32↑j
seg002:163D                                         ; sub_1251F+3B↑j ...
seg002:163D                 mov     dx, ds:207Fh
seg002:1641                 in      al, dx
seg002:1642                 mov     byte ptr ds:2B0Fh, 1
seg002:1647
seg002:1647 loc_12587:                              ; CODE XREF: sub_1251F+B↑j
seg002:1647                                         ; sub_1251F+12↑j
seg002:1647                 mov     dx, ds:207Fh
seg002:164B                 in      al, dx
seg002:164C                 popf
seg002:164D                 pop     dx
seg002:164E                 pop     cx
seg002:164F                 pop     ax
seg002:1650                 retn
seg002:1650 sub_1251F       endp
seg002:1650
seg002:1651
seg002:1651 ; =============== S U B R O U T I N E =======================================
seg002:1651
seg002:1651
seg002:1651 sub_12591       proc near               ; CODE XREF: sub_1125B+24↑p
seg002:1651                                         ; sub_122E0+10↑p
seg002:1651                 push    ax
seg002:1652                 push    cx
seg002:1653                 push    dx
seg002:1654                 pushf
seg002:1655                 cli
seg002:1656                 clc
seg002:1657                 cmp     byte ptr ds:2B0Fh, 0
seg002:165C                 jz      short loc_125CD
seg002:165E                 cmp     word ptr ds:2394h, 1
seg002:1663                 jz      short loc_125CD
seg002:1665                 mov     cx, 2
seg002:1668
seg002:1668 loc_125A8:                              ; CODE XREF: sub_12591+30↓j
seg002:1668                 push    cx
seg002:1669                 mov     al, 0FFh
seg002:166B                 mov     dx, ds:2081h
seg002:166F                 out     dx, al
seg002:1670                 mov     cx, 1000h
seg002:1673
seg002:1673 loc_125B3:                              ; CODE XREF: sub_12591+27↓j
seg002:1673                 in      al, dx
seg002:1674                 or      al, al
seg002:1676                 jns     short loc_125BD
seg002:1678                 loop    loc_125B3
seg002:167A                 stc
seg002:167B                 jmp     short loc_125BE
seg002:167D ; ---------------------------------------------------------------------------
seg002:167D
seg002:167D loc_125BD:                              ; CODE XREF: sub_12591+25↑j
seg002:167D                 clc
seg002:167E
seg002:167E loc_125BE:                              ; CODE XREF: sub_12591+2A↑j
seg002:167E                 pop     cx
seg002:167F                 jnb     short loc_125C3
seg002:1681                 loop    loc_125A8
seg002:1683
seg002:1683 loc_125C3:                              ; CODE XREF: sub_12591+2E↑j
seg002:1683                 mov     dx, ds:207Fh
seg002:1687                 in      al, dx
seg002:1688                 mov     byte ptr ds:2B0Fh, 0
seg002:168D
seg002:168D loc_125CD:                              ; CODE XREF: sub_12591+B↑j
seg002:168D                                         ; sub_12591+12↑j
seg002:168D                 popf
seg002:168E                 pop     dx
seg002:168F                 pop     cx
seg002:1690                 pop     ax
seg002:1691                 retn
seg002:1691 sub_12591       endp
seg002:1691
seg002:1692
seg002:1692 ; =============== S U B R O U T I N E =======================================
seg002:1692
seg002:1692
seg002:1692 sub_125D2       proc near               ; CODE XREF: sub_12468+5↑p
seg002:1692                 push    cx
seg002:1693                 push    dx
seg002:1694                 push    ax
seg002:1695                 mov     cx, 1000h
seg002:1698                 mov     dx, ds:2081h
seg002:169C
seg002:169C loc_125DC:                              ; CODE XREF: sub_125D2+F↓j
seg002:169C                 in      al, dx
seg002:169D                 test    al, 40h
seg002:169F                 jz      short loc_125E7
seg002:16A1                 loop    loc_125DC
seg002:16A3                 stc
seg002:16A4                 pop     ax
seg002:16A5                 jmp     short loc_125EE
seg002:16A7 ; ---------------------------------------------------------------------------
seg002:16A7
seg002:16A7 loc_125E7:                              ; CODE XREF: sub_125D2+D↑j
seg002:16A7                 pop     ax
seg002:16A8                 mov     dx, ds:207Fh
seg002:16AC                 out     dx, al
seg002:16AD                 clc
seg002:16AE
seg002:16AE loc_125EE:                              ; CODE XREF: sub_125D2+13↑j
seg002:16AE                 pop     dx
seg002:16AF                 pop     cx
seg002:16B0                 retn
seg002:16B0 sub_125D2       endp
seg002:16B0
seg002:16B1
seg002:16B1 ; =============== S U B R O U T I N E =======================================
seg002:16B1
seg002:16B1
seg002:16B1 sub_125F1       proc near               ; CODE XREF: sub_11ED0:loc_11F26↑p
seg002:16B1                 push    cx
seg002:16B2                 push    dx
seg002:16B3                 mov     cx, 1000h
seg002:16B6                 mov     dx, ds:2081h
seg002:16BA
seg002:16BA loc_125FA:                              ; CODE XREF: sub_125F1+E↓j
seg002:16BA                 in      al, dx
seg002:16BB                 or      al, al
seg002:16BD                 jns     short loc_12601
seg002:16BF                 loop    loc_125FA
seg002:16C1
seg002:16C1 loc_12601:                              ; CODE XREF: sub_125F1+C↑j
seg002:16C1                 mov     dx, ds:207Fh
seg002:16C5                 in      al, dx
seg002:16C6                 pop     dx
seg002:16C7                 pop     cx
seg002:16C8                 retn
seg002:16C8 sub_125F1       endp
seg002:16C8
seg002:16C9
seg002:16C9 ; =============== S U B R O U T I N E =======================================
seg002:16C9
seg002:16C9
seg002:16C9 sub_12609       proc near               ; CODE XREF: sub_11ED0:loc_11F1E↑p
seg002:16C9                 push    ax
seg002:16CA                 push    dx
seg002:16CB                 mov     dx, ds:2081h
seg002:16CF                 in      al, dx
seg002:16D0                 or      al, al
seg002:16D2                 jns     short loc_12617
seg002:16D4                 clc
seg002:16D5                 jmp     short loc_12618
seg002:16D7 ; ---------------------------------------------------------------------------
seg002:16D7
seg002:16D7 loc_12617:                              ; CODE XREF: sub_12609+9↑j
seg002:16D7                 stc
seg002:16D8
seg002:16D8 loc_12618:                              ; CODE XREF: sub_12609+C↑j
seg002:16D8                 pop     dx
seg002:16D9                 pop     ax
seg002:16DA                 retn
seg002:16DA sub_12609       endp
seg002:16DA
seg002:16DB
seg002:16DB ; =============== S U B R O U T I N E =======================================
seg002:16DB
seg002:16DB
seg002:16DB sub_1261B       proc near               ; CODE XREF: sub_1264C:loc_12659↓p
seg002:16DB                 push    cx
seg002:16DC                 push    dx
seg002:16DD                 pushf
seg002:16DE                 cli
seg002:16DF                 clc
seg002:16E0                 mov     bx, 0
seg002:16E3                 push    ax
seg002:16E4                 mov     dx, ax
seg002:16E6                 inc     dx
seg002:16E7                 mov     al, 0FFh
seg002:16E9                 out     dx, al
seg002:16EA                 mov     cx, 1000h
seg002:16ED
seg002:16ED loc_1262D:                              ; CODE XREF: sub_1261B:loc_1262D↓j
seg002:16ED                 loop    loc_1262D
seg002:16EF                 in      al, dx
seg002:16F0                 mov     al, 0FFh
seg002:16F2                 out     dx, al
seg002:16F3                 mov     cx, 1000h
seg002:16F6
seg002:16F6 loc_12636:                              ; CODE XREF: sub_1261B+20↓j
seg002:16F6                 in      al, dx
seg002:16F7                 or      al, al
seg002:16F9                 jns     short loc_1263E
seg002:16FB                 loop    loc_12636
seg002:16FD                 stc
seg002:16FE
seg002:16FE loc_1263E:                              ; CODE XREF: sub_1261B+1E↑j
seg002:16FE                 dec     dx
seg002:16FF                 in      al, dx
seg002:1700                 pop     ax
seg002:1701                 jb      short loc_12645
seg002:1703                 jmp     short loc_12648
seg002:1705 ; ---------------------------------------------------------------------------
seg002:1705
seg002:1705 loc_12645:                              ; CODE XREF: sub_1261B+26↑j
seg002:1705                 mov     bx, 1
seg002:1708
seg002:1708 loc_12648:                              ; CODE XREF: sub_1261B+28↑j
seg002:1708                 popf
seg002:1709                 pop     dx
seg002:170A                 pop     cx
seg002:170B                 retn
seg002:170B sub_1261B       endp
seg002:170B
seg002:170C
seg002:170C ; =============== S U B R O U T I N E =======================================
seg002:170C
seg002:170C
seg002:170C sub_1264C       proc near               ; CODE XREF: sub_12246+1E↑p
seg002:170C                                         ; sub_12328:loc_12354↑p
seg002:170C                 push    bx
seg002:170D                 mov     ax, ds:207Fh
seg002:1710                 cmp     byte ptr ds:2B0Eh, 1
seg002:1715                 jnz     short loc_12659
seg002:1717                 jmp     short loc_1266B
seg002:1719 ; ---------------------------------------------------------------------------
seg002:1719
seg002:1719 loc_12659:                              ; CODE XREF: sub_1264C+9↑j
seg002:1719                 call    sub_1261B
seg002:171C                 or      bx, bx
seg002:171E                 jz      short loc_12663
seg002:1720                 stc
seg002:1721                 jmp     short loc_1266C
seg002:1723 ; ---------------------------------------------------------------------------
seg002:1723
seg002:1723 loc_12663:                              ; CODE XREF: sub_1264C+12↑j
seg002:1723                 mov     byte ptr ds:2B0Eh, 1
seg002:1728                 mov     ds:207Fh, ax
seg002:172B
seg002:172B loc_1266B:                              ; CODE XREF: sub_1264C+B↑j
seg002:172B                 clc
seg002:172C
seg002:172C loc_1266C:                              ; CODE XREF: sub_1264C+15↑j
seg002:172C                 pop     bx
seg002:172D                 retn
seg002:172D sub_1264C       endp
seg002:172D
seg002:172E
seg002:172E ; =============== S U B R O U T I N E =======================================
seg002:172E
seg002:172E
seg002:172E sub_1266E       proc near               ; CODE XREF: sub_126AA+6↓p
seg002:172E                                         ; sub_126AA+C↓p ...
seg002:172E                 push    ax
seg002:172F                 push    cx
seg002:1730                 push    dx
seg002:1731                 add     dx, ds:207Dh
seg002:1735                 xchg    ah, al
seg002:1737                 out     dx, al
seg002:1738                 mov     cx, 1
seg002:173B                 call    do_sth_with_keyboard
seg002:173E                 inc     dx
seg002:173F                 mov     al, ah
seg002:1741                 out     dx, al
seg002:1742                 mov     cx, 3
seg002:1745                 call    do_sth_with_keyboard
seg002:1748                 pop     dx
seg002:1749                 pop     cx
seg002:174A                 pop     ax
seg002:174B                 retn
seg002:174B sub_1266E       endp
seg002:174B
seg002:174C
seg002:174C ; =============== S U B R O U T I N E =======================================
seg002:174C
seg002:174C
seg002:174C sub_1268C       proc near               ; CODE XREF: sub_126AA+17↓p
seg002:174C                                         ; sub_126AA+2A↓p
seg002:174C                 push    cx
seg002:174D                 push    dx
seg002:174E                 mov     cx, 100h
seg002:1751                 mov     ah, al
seg002:1753                 and     ah, 0E0h
seg002:1756                 mov     dx, ds:207Dh
seg002:175A
seg002:175A loc_1269A:                              ; CODE XREF: sub_1268C+15↓j
seg002:175A                 in      al, dx
seg002:175B                 and     al, 0E0h
seg002:175D                 cmp     ah, al
seg002:175F                 jz      short loc_126A6
seg002:1761                 loop    loc_1269A
seg002:1763                 stc
seg002:1764                 jmp     short loc_126A7
seg002:1766 ; ---------------------------------------------------------------------------
seg002:1766
seg002:1766 loc_126A6:                              ; CODE XREF: sub_1268C+13↑j
seg002:1766                 clc
seg002:1767
seg002:1767 loc_126A7:                              ; CODE XREF: sub_1268C+18↑j
seg002:1767                 pop     dx
seg002:1768                 pop     cx
seg002:1769                 retn
seg002:1769 sub_1268C       endp
seg002:1769
seg002:176A
seg002:176A ; =============== S U B R O U T I N E =======================================
seg002:176A
seg002:176A
seg002:176A sub_126AA       proc near               ; CODE XREF: sub_12328:loc_1233C↑p
seg002:176A                 mov     dx, 0
seg002:176D                 mov     ax, 100h
seg002:1770                 call    sub_1266E
seg002:1773                 mov     ax, 460h
seg002:1776                 call    sub_1266E
seg002:1779                 mov     ax, 480h
seg002:177C                 call    sub_1266E
seg002:177F                 mov     al, 0
seg002:1781                 call    sub_1268C
seg002:1784                 jb      short loc_126E9
seg002:1786                 mov     ax, 2FFh
seg002:1789                 call    sub_1266E
seg002:178C                 mov     ax, 421h
seg002:178F                 call    sub_1266E
seg002:1792                 mov     al, 0C0h
seg002:1794                 call    sub_1268C
seg002:1797                 jb      short loc_126E9
seg002:1799                 mov     ax, 460h
seg002:179C                 call    sub_1266E
seg002:179F                 mov     ax, 480h
seg002:17A2                 call    sub_1266E
seg002:17A5                 sub     ax, ax
seg002:17A7                 jmp     short locret_126EC
seg002:17A9 ; ---------------------------------------------------------------------------
seg002:17A9
seg002:17A9 loc_126E9:                              ; CODE XREF: sub_126AA+1A↑j
seg002:17A9                                         ; sub_126AA+2D↑j
seg002:17A9                 mov     ax, 1
seg002:17AC
seg002:17AC locret_126EC:                           ; CODE XREF: sub_126AA+3D↑j
seg002:17AC                 retn
seg002:17AC sub_126AA       endp
seg002:17AC
seg002:17AD
seg002:17AD ; =============== S U B R O U T I N E =======================================
seg002:17AD
seg002:17AD
seg002:17AD sub_126ED       proc near               ; CODE XREF: sub_12383:loc_1239C↑p
seg002:17AD                 mov     dx, 0
seg002:17B0                 mov     ax, 460h
seg002:17B3                 call    sub_1266E
seg002:17B6                 mov     ax, 480h
seg002:17B9                 call    sub_1266E
seg002:17BC                 mov     dx, 2
seg002:17BF                 mov     ax, 501h
seg002:17C2                 call    sub_1266E
seg002:17C5                 mov     ax, 43Fh
seg002:17C8                 call    sub_1266E
seg002:17CB                 mov     word ptr ds:2B10h, 6
seg002:17D1                 mov     dx, 0
seg002:17D4                 mov     ax, 120h
seg002:17D7                 call    sub_1266E
seg002:17DA                 mov     ax, 800h
seg002:17DD                 call    sub_1266E
seg002:17E0                 mov     ax, 0BD20h
seg002:17E3                 call    sub_1266E
seg002:17E6                 call    sub_1272A
seg002:17E9                 retn
seg002:17E9 sub_126ED       endp
seg002:17E9
seg002:17EA
seg002:17EA ; =============== S U B R O U T I N E =======================================
seg002:17EA
seg002:17EA
seg002:17EA sub_1272A       proc near               ; CODE XREF: sub_126ED+39↑p
seg002:17EA                                         ; sub_127BB+58↓p
seg002:17EA                 mov     dx, 0
seg002:17ED                 mov     ax, 0A600h
seg002:17F0                 call    sub_1266E
seg002:17F3                 mov     ax, 0B60Ah
seg002:17F6                 call    sub_1266E
seg002:17F9                 mov     ax, 0A70Bh
seg002:17FC                 call    sub_1266E
seg002:17FF                 mov     ax, 0B70Ah
seg002:1802                 call    sub_1266E
seg002:1805                 mov     ax, 0A857h
seg002:1808                 call    sub_1266E
seg002:180B                 mov     ax, 0B809h
seg002:180E                 call    sub_1266E
seg002:1811                 retn
seg002:1811 sub_1272A       endp
seg002:1811
seg002:1812
seg002:1812 ; =============== S U B R O U T I N E =======================================
seg002:1812
seg002:1812
seg002:1812 sub_12752       proc near               ; CODE XREF: sub_123A2:loc_123AB↑p
seg002:1812                 mov     dx, 2
seg002:1815                 mov     ax, 0C030h
seg002:1818
seg002:1818 loc_12758:                              ; CODE XREF: sub_12752+E↓j
seg002:1818                 call    sub_1266E
seg002:181B                 inc     ah
seg002:181D                 cmp     ah, 0C8h
seg002:1820                 jbe     short loc_12758
seg002:1822                 mov     al, 0
seg002:1824                 sub     bx, bx
seg002:1826
seg002:1826 loc_12766:                              ; CODE XREF: sub_12752+21↓j
seg002:1826                 mov     ah, 0C0h
seg002:1828                 add     ah, [bx+4646h]
seg002:182C                 call    sub_1266E
seg002:182F                 inc     bx
seg002:1830                 cmp     bx, 12h
seg002:1833                 jb      short loc_12766
seg002:1835                 mov     dx, 0
seg002:1838                 mov     ax, 0C030h
seg002:183B
seg002:183B loc_1277B:                              ; CODE XREF: sub_12752+31↓j
seg002:183B                 call    sub_1266E
seg002:183E                 inc     ah
seg002:1840                 cmp     ah, 0C8h
seg002:1843                 jbe     short loc_1277B
seg002:1845                 mov     al, 0
seg002:1847                 sub     bx, bx
seg002:1849
seg002:1849 loc_12789:                              ; CODE XREF: sub_12752+44↓j
seg002:1849                 mov     ah, 0C0h
seg002:184B                 add     ah, [bx+4646h]
seg002:184F                 call    sub_1266E
seg002:1852                 inc     bx
seg002:1853                 cmp     bx, 12h
seg002:1856                 jb      short loc_12789
seg002:1858                 mov     dx, 2
seg002:185B                 mov     ax, 400h
seg002:185E                 call    sub_1266E
seg002:1861                 mov     ax, 500h
seg002:1864                 call    sub_1266E
seg002:1867                 push    es
seg002:1868                 push    di
seg002:1869                 mov     ax, ds
seg002:186B                 mov     es, ax
seg002:186D                 cld
seg002:186E                 mov     al, 0FFh
seg002:1870                 mov     cx, 0Bh
seg002:1873                 mov     di, 4542h
seg002:1876                 rep stosb
seg002:1878                 pop     di
seg002:1879                 pop     es
seg002:187A                 retn
seg002:187A sub_12752       endp
seg002:187A
seg002:187B
seg002:187B ; =============== S U B R O U T I N E =======================================
seg002:187B
seg002:187B
seg002:187B sub_127BB       proc near               ; CODE XREF: sub_12363:loc_1236F↑p
seg002:187B                 push    es
seg002:187C                 push    di
seg002:187D                 mov     di, ds
seg002:187F                 mov     es, di
seg002:1881                 cld
seg002:1882                 sub     ax, ax
seg002:1884                 mov     ds:2B12h, ax
seg002:1887                 mov     byte ptr ds:4603h, 20h ; ' '
seg002:188C                 mov     ax, 3030h
seg002:188F                 mov     cx, 8
seg002:1892                 mov     di, 4464h
seg002:1895                 rep stosw
seg002:1897                 sub     ax, ax
seg002:1899                 mov     cx, 8
seg002:189C                 mov     di, 4474h
seg002:189F                 rep stosw
seg002:18A1                 sub     ax, ax
seg002:18A3                 mov     cx, 8
seg002:18A6                 mov     di, 4484h
seg002:18A9                 rep stosw
seg002:18AB                 sub     ax, ax
seg002:18AD                 mov     cx, 10h
seg002:18B0                 mov     di, 4494h
seg002:18B3                 rep stosw
seg002:18B5                 mov     ax, 100h
seg002:18B8                 mov     cx, 10h
seg002:18BB                 mov     di, 44B4h
seg002:18BE                 rep stosw
seg002:18C0                 mov     al, 0FFh
seg002:18C2                 mov     cx, 0Bh
seg002:18C5                 mov     di, 456Eh
seg002:18C8                 rep stosb
seg002:18CA                 mov     dx, 0
seg002:18CD                 mov     ax, 0BD20h
seg002:18D0                 call    sub_1266E
seg002:18D3                 call    sub_1272A
seg002:18D6                 pop     di
seg002:18D7                 pop     es
seg002:18D8                 retn
seg002:18D8 sub_127BB       endp
seg002:18D8
seg002:18D9
seg002:18D9 ; =============== S U B R O U T I N E =======================================
seg002:18D9
seg002:18D9
seg002:18D9 sub_12819       proc near               ; CODE XREF: sub_1285A+48↓p
seg002:18D9                                         ; sub_1285A+68↓p ...
seg002:18D9                 push    ax
seg002:18DA                 push    cx
seg002:18DB                 push    si
seg002:18DC                 mov     ah, cl
seg002:18DE                 lodsb
seg002:18DF                 call    sub_1266E
seg002:18E2                 lodsb
seg002:18E3                 mov     cl, al
seg002:18E5                 and     cl, 0C0h
seg002:18E8                 mov     [di+457Fh], cl
seg002:18EC                 mov     cl, al
seg002:18EE                 and     cl, 3Fh
seg002:18F1                 sub     cl, 3Fh ; '?'
seg002:18F4                 neg     cl
seg002:18F6                 mov     [di+45ABh], cl
seg002:18FA                 add     ah, 20h ; ' '
seg002:18FD                 call    sub_1266E
seg002:1900                 lodsb
seg002:1901                 add     ah, 20h ; ' '
seg002:1904                 call    sub_1266E
seg002:1907                 lodsb
seg002:1908                 add     ah, 20h ; ' '
seg002:190B                 call    sub_1266E
seg002:190E                 inc     si
seg002:190F                 lodsb
seg002:1910                 add     ah, 60h ; '`'
seg002:1913                 call    sub_1266E
seg002:1916                 pop     si
seg002:1917                 pop     cx
seg002:1918                 pop     ax
seg002:1919                 retn
seg002:1919 sub_12819       endp
seg002:1919
seg002:191A
seg002:191A ; =============== S U B R O U T I N E =======================================
seg002:191A
seg002:191A
seg002:191A sub_1285A       proc near               ; CODE XREF: sub_12DD3+3E↓p
seg002:191A                 push    cx
seg002:191B                 push    di
seg002:191C                 push    si
seg002:191D                 mov     di, ds:2340h
seg002:1921                 mov     cl, [di+4464h]
seg002:1925                 mov     [bx+452Ch], cl
seg002:1929                 mov     cl, 5
seg002:192B                 sub     ah, ah
seg002:192D                 shl     ax, cl
seg002:192F                 mov     si, ax
seg002:1931                 add     si, 3114h
seg002:1935                 mov     al, [si+1Fh]
seg002:1938                 cbw
seg002:1939                 mov     cl, 4
seg002:193B                 shl     ax, cl
seg002:193D                 shl     bx, 1
seg002:193F                 mov     [bx+4516h], ax
seg002:1943                 shr     bx, 1
seg002:1945                 mov     al, [si+4]
seg002:1948                 mov     ah, [si+10h]
seg002:194B                 and     ax, 101h
seg002:194E                 shl     al, 1
seg002:1950                 or      al, ah
seg002:1952                 mov     [bx+4563h], al
seg002:1956                 sub     dh, dh
seg002:1958                 mov     dl, [bx+44D4h]
seg002:195C                 mov     cl, [bx+44DFh]
seg002:1960                 mov     di, bx
seg002:1962                 call    sub_12819
seg002:1965                 mov     ah, [bx+4579h]
seg002:1969                 mov     al, [si+4]
seg002:196C                 and     al, 0Fh
seg002:196E                 mov     [di+45D7h], al
seg002:1972                 or      al, [bx+452Ch]
seg002:1976                 call    sub_1266E
seg002:1979                 add     cl, 3
seg002:197C                 add     si, 6
seg002:197F                 add     di, 0Bh
seg002:1982                 call    sub_12819
seg002:1985                 add     si, 6
seg002:1988                 add     cl, 5
seg002:198B                 add     di, 0Bh
seg002:198E                 call    sub_12819
seg002:1991                 mov     ah, [bx+4579h]
seg002:1995                 add     ah, 3
seg002:1998                 mov     al, [si+4]
seg002:199B                 and     al, 0Fh
seg002:199D                 mov     [di+45D7h], al
seg002:19A1                 or      al, [bx+452Ch]
seg002:19A5                 call    sub_1266E
seg002:19A8                 add     cl, 3
seg002:19AB                 add     si, 6
seg002:19AE                 add     di, 0Bh
seg002:19B1                 call    sub_12819
seg002:19B4                 pop     si
seg002:19B5                 pop     di
seg002:19B6                 pop     cx
seg002:19B7                 retn
seg002:19B7 sub_1285A       endp
seg002:19B7
seg002:19B8
seg002:19B8 ; =============== S U B R O U T I N E =======================================
seg002:19B8
seg002:19B8
seg002:19B8 sub_128F8       proc near               ; CODE XREF: sub_12A56+14↓p
seg002:19B8                 push    cx
seg002:19B9                 push    si
seg002:19BA                 mov     byte ptr [bx+452Ch], 30h ; '0'
seg002:19BF                 sub     ah, ah
seg002:19C1                 sub     ax, 80h
seg002:19C4                 shl     ax, 1
seg002:19C6                 shl     ax, 1
seg002:19C8                 shl     ax, 1
seg002:19CA                 shl     ax, 1
seg002:19CC                 mov     si, 4114h
seg002:19CF                 add     si, ax
seg002:19D1                 mov     al, [si+3]
seg002:19D4                 cmp     bl, 7
seg002:19D7                 jb      short loc_1291C
seg002:19D9                 mov     al, [si+2]
seg002:19DC
seg002:19DC loc_1291C:                              ; CODE XREF: sub_128F8+1F↑j
seg002:19DC                 mov     ah, al
seg002:19DE                 and     ax, 0C03Fh
seg002:19E1                 mov     [bx+457Fh], ah
seg002:19E5                 sub     al, 3Fh ; '?'
seg002:19E7                 neg     al
seg002:19E9                 mov     [bx+45ABh], al
seg002:19ED                 cmp     bl, 6
seg002:19F0                 jnz     short loc_12987
seg002:19F2                 mov     ah, [bx+44DFh]
seg002:19F6                 mov     dx, 0
seg002:19F9                 lodsb
seg002:19FA                 call    sub_1266E
seg002:19FD                 add     ah, 3
seg002:1A00                 lodsb
seg002:1A01                 call    sub_1266E
seg002:1A04                 sub     ah, 3
seg002:1A07                 add     ah, 20h ; ' '
seg002:1A0A                 lodsb
seg002:1A0B                 call    sub_1266E
seg002:1A0E                 inc     si
seg002:1A0F                 mov     cx, 2
seg002:1A12
seg002:1A12 loc_12952:                              ; CODE XREF: sub_128F8+6B↓j
seg002:1A12                 add     ah, 20h ; ' '
seg002:1A15                 lodsb
seg002:1A16                 call    sub_1266E
seg002:1A19                 add     ah, 3
seg002:1A1C                 lodsb
seg002:1A1D                 call    sub_1266E
seg002:1A20                 sub     ah, 3
seg002:1A23                 loop    loc_12952
seg002:1A25                 add     ah, 60h ; '`'
seg002:1A28                 lodsb
seg002:1A29                 call    sub_1266E
seg002:1A2C                 add     ah, 3
seg002:1A2F                 lodsb
seg002:1A30                 call    sub_1266E
seg002:1A33                 sub     ah, 3
seg002:1A36                 mov     ah, bl
seg002:1A38                 add     ah, 0C0h
seg002:1A3B                 lodsb
seg002:1A3C                 and     al, 3Fh
seg002:1A3E                 or      al, [bx+452Ch]
seg002:1A42                 call    sub_1266E
seg002:1A45                 jmp     short loc_129C1
seg002:1A47 ; ---------------------------------------------------------------------------
seg002:1A47
seg002:1A47 loc_12987:                              ; CODE XREF: sub_128F8+38↑j
seg002:1A47                 mov     ah, [bx+44DFh]
seg002:1A4B                 mov     dx, 0
seg002:1A4E                 lodsb
seg002:1A4F                 inc     si
seg002:1A50                 call    sub_1266E
seg002:1A53                 add     ah, 20h ; ' '
seg002:1A56                 lodsb
seg002:1A57                 inc     si
seg002:1A58                 call    sub_1266E
seg002:1A5B                 mov     cx, 2
seg002:1A5E
seg002:1A5E loc_1299E:                              ; CODE XREF: sub_128F8+AE↓j
seg002:1A5E                 add     ah, 20h ; ' '
seg002:1A61                 lodsb
seg002:1A62                 inc     si
seg002:1A63                 call    sub_1266E
seg002:1A66                 loop    loc_1299E
seg002:1A68                 add     ah, 60h ; '`'
seg002:1A6B                 lodsb
seg002:1A6C                 inc     si
seg002:1A6D                 call    sub_1266E
seg002:1A70                 mov     ah, [bx+4603h]
seg002:1A74                 add     ah, 0C0h
seg002:1A77                 lodsb
seg002:1A78                 or      al, [bx+452Ch]
seg002:1A7C                 and     al, 3Fh
seg002:1A7E                 call    sub_1266E
seg002:1A81
seg002:1A81 loc_129C1:                              ; CODE XREF: sub_128F8+8D↑j
seg002:1A81                 pop     si
seg002:1A82                 pop     cx
seg002:1A83                 retn
seg002:1A83 sub_128F8       endp
seg002:1A83
seg002:1A84
seg002:1A84 ; =============== S U B R O U T I N E =======================================
seg002:1A84
seg002:1A84
seg002:1A84 sub_129C4       proc near               ; CODE XREF: sub_12373:loc_1237F↑p
seg002:1A84                                         ; sub_12E50+6↓p
seg002:1A84                 push    ax
seg002:1A85                 push    bx
seg002:1A86                 push    dx
seg002:1A87                 mov     dx, 0
seg002:1A8A                 and     byte ptr ds:4603h, 20h
seg002:1A8F                 mov     al, ds:4603h
seg002:1A92                 mov     ah, 0BDh
seg002:1A94                 call    sub_1266E
seg002:1A97                 mov     bx, ds:2B10h
seg002:1A9B                 dec     bx
seg002:1A9C
seg002:1A9C loc_129DC:                              ; CODE XREF: sub_129C4+24↓j
seg002:1A9C                 cmp     byte ptr [bx+4542h], 7Fh
seg002:1AA1                 ja      short loc_129E6
seg002:1AA3                 call    sub_12A25
seg002:1AA6
seg002:1AA6 loc_129E6:                              ; CODE XREF: sub_129C4+1D↑j
seg002:1AA6                 dec     bl
seg002:1AA8                 jns     short loc_129DC
seg002:1AAA                 pop     dx
seg002:1AAB                 pop     bx
seg002:1AAC                 pop     ax
seg002:1AAD                 retn
seg002:1AAD sub_129C4       endp
seg002:1AAD
seg002:1AAE
seg002:1AAE ; =============== S U B R O U T I N E =======================================
seg002:1AAE
seg002:1AAE
seg002:1AAE sub_129EE       proc near               ; CODE XREF: sub_12A56+1↓p
seg002:1AAE                                         ; sub_12D5F+13↓p
seg002:1AAE                 push    di
seg002:1AAF                 sub     bx, bx
seg002:1AB1                 mov     al, ds:4617h
seg002:1AB4                 cmp     al, 23h ; '#'
seg002:1AB6                 jb      short loc_12A1F
seg002:1AB8                 cmp     al, 4Bh ; 'K'
seg002:1ABA                 ja      short loc_12A1F
seg002:1ABC                 sub     ah, ah
seg002:1ABE                 sub     al, 23h ; '#'
seg002:1AC0                 mov     ds:4617h, al
seg002:1AC3                 mov     di, ax
seg002:1AC5                 mov     bl, [di+4404h]
seg002:1AC9                 or      bl, bl
seg002:1ACB                 jz      short loc_12A1F
seg002:1ACD                 sub     bx, 80h
seg002:1AD1                 shl     bx, 1
seg002:1AD3                 shl     bx, 1
seg002:1AD5                 shl     bx, 1
seg002:1AD7                 shl     bx, 1
seg002:1AD9                 mov     bl, [bx+411Fh]
seg002:1ADD                 sub     bh, bh
seg002:1ADF
seg002:1ADF loc_12A1F:                              ; CODE XREF: sub_129EE+8↑j
seg002:1ADF                                         ; sub_129EE+C↑j ...
seg002:1ADF                 mov     ax, bx
seg002:1AE1                 or      ax, ax
seg002:1AE3                 pop     di
seg002:1AE4                 retn
seg002:1AE4 sub_129EE       endp
seg002:1AE4
seg002:1AE5
seg002:1AE5 ; =============== S U B R O U T I N E =======================================
seg002:1AE5
seg002:1AE5
seg002:1AE5 sub_12A25       proc near               ; CODE XREF: sub_129C4+1F↑p
seg002:1AE5                                         ; sub_12C34+6F↓p ...
seg002:1AE5                 push    cx
seg002:1AE6                 push    dx
seg002:1AE7                 or      byte ptr [bx+4542h], 80h
seg002:1AEC                 mov     byte ptr [bx+456Eh], 0FFh
seg002:1AF1                 shl     bx, 1
seg002:1AF3                 mov     ax, [bx+44EAh]
seg002:1AF7                 shr     bx, 1
seg002:1AF9                 mov     cl, ah
seg002:1AFB                 sub     dh, dh
seg002:1AFD                 mov     dl, [bx+44D4h]
seg002:1B01                 mov     ah, [bx+44DFh]
seg002:1B05                 add     ah, 80h
seg002:1B08                 call    sub_1266E
seg002:1B0B                 mov     al, cl
seg002:1B0D                 add     ah, 10h
seg002:1B10                 call    sub_1266E
seg002:1B13                 pop     dx
seg002:1B14                 pop     cx
seg002:1B15                 retn
seg002:1B15 sub_12A25       endp
seg002:1B15
seg002:1B16
seg002:1B16 ; =============== S U B R O U T I N E =======================================
seg002:1B16
seg002:1B16
seg002:1B16 sub_12A56       proc near               ; CODE XREF: sub_12DD3+16↓p
seg002:1B16                 push    di
seg002:1B17                 call    sub_129EE
seg002:1B1A                 jnz     short loc_12A5F
seg002:1B1C                 jmp     loc_12AE3
seg002:1B1F ; ---------------------------------------------------------------------------
seg002:1B1F
seg002:1B1F loc_12A5F:                              ; CODE XREF: sub_12A56+4↑j
seg002:1B1F                 mov     al, ds:4617h
seg002:1B22                 sub     ah, ah
seg002:1B24                 mov     di, ax
seg002:1B26                 mov     al, [di+4404h]
seg002:1B2A                 call    sub_128F8
seg002:1B2D                 mov     al, [bx+45FEh]
seg002:1B31                 or      ds:4603h, al
seg002:1B35                 mov     al, ds:4618h
seg002:1B38                 call    sub_12AE5
seg002:1B3B                 call    sub_12BBD
seg002:1B3E                 cmp     bl, 6
seg002:1B41                 jz      short loc_12A88
seg002:1B43                 cmp     bl, 8
seg002:1B46                 jnz     short loc_12AD8
seg002:1B48
seg002:1B48 loc_12A88:                              ; CODE XREF: sub_12A56+2B↑j
seg002:1B48                 mov     al, ds:4617h
seg002:1B4B                 sub     ah, ah
seg002:1B4D                 mov     di, ax
seg002:1B4F                 mov     al, [di+4434h]
seg002:1B53                 call    sub_12BE6
seg002:1B56                 jb      short loc_12AE3
seg002:1B58                 mov     cl, ah
seg002:1B5A                 sub     dh, dh
seg002:1B5C                 mov     dl, [bx+44D4h]
seg002:1B60                 mov     ah, [bx+460Ch]
seg002:1B64                 call    sub_1266E
seg002:1B67                 mov     al, cl
seg002:1B69                 add     ah, 10h
seg002:1B6C                 call    sub_1266E
seg002:1B6F                 cmp     bl, 8
seg002:1B72                 jnz     short loc_12AD8
seg002:1B74                 mov     al, ds:4617h
seg002:1B77                 sub     ah, ah
seg002:1B79                 mov     di, ax
seg002:1B7B                 mov     al, [di+4434h]
seg002:1B7F                 add     al, 7
seg002:1B81                 call    sub_12BE6
seg002:1B84                 jb      short loc_12AE3
seg002:1B86                 mov     cl, ah
seg002:1B88                 mov     ah, 0A7h
seg002:1B8A                 mov     dx, 0
seg002:1B8D                 call    sub_1266E
seg002:1B90                 mov     al, cl
seg002:1B92                 add     ah, 10h
seg002:1B95                 call    sub_1266E
seg002:1B98
seg002:1B98 loc_12AD8:                              ; CODE XREF: sub_12A56+30↑j
seg002:1B98                                         ; sub_12A56+5C↑j
seg002:1B98                 mov     al, ds:4603h
seg002:1B9B                 mov     ah, 0BDh
seg002:1B9D                 mov     dx, 0
seg002:1BA0                 call    sub_1266E
seg002:1BA3
seg002:1BA3 loc_12AE3:                              ; CODE XREF: sub_12A56+6↑j
seg002:1BA3                                         ; sub_12A56+40↑j ...
seg002:1BA3                 pop     di
seg002:1BA4                 retn
seg002:1BA4 sub_12A56       endp
seg002:1BA4
seg002:1BA5
seg002:1BA5 ; =============== S U B R O U T I N E =======================================
seg002:1BA5
seg002:1BA5
seg002:1BA5 sub_12AE5       proc near               ; CODE XREF: sub_12A56+22↑p
seg002:1BA5                                         ; sub_12DD3+45↓p
seg002:1BA5                 push    di
seg002:1BA6                 sub     ah, ah
seg002:1BA8                 stc
seg002:1BA9                 rcl     ax, 1
seg002:1BAB                 mov     di, ds:2340h
seg002:1BAF                 shl     di, 1
seg002:1BB1                 mul     word ptr [di+44B4h]
seg002:1BB5                 mov     al, ah
seg002:1BB7                 shr     al, 1
seg002:1BB9                 shr     al, 1
seg002:1BBB                 shr     al, 1
seg002:1BBD                 shr     al, 1
seg002:1BBF                 adc     al, 0
seg002:1BC1                 sub     ah, ah
seg002:1BC3                 mov     di, ax
seg002:1BC5                 shl     di, 1
seg002:1BC7                 mov     ax, [di+4619h]
seg002:1BCB                 pop     di
seg002:1BCC                 retn
seg002:1BCC sub_12AE5       endp
seg002:1BCC
seg002:1BCD
seg002:1BCD ; =============== S U B R O U T I N E =======================================
seg002:1BCD
seg002:1BCD
seg002:1BCD sub_12B0D       proc near               ; CODE XREF: sub_12B27+27↓p
seg002:1BCD                                         ; sub_12B27+45↓p ...
seg002:1BCD                 sub     ah, ah
seg002:1BCF                 add     ax, cx
seg002:1BD1                 cmp     ax, 3Fh ; '?'
seg002:1BD4                 jbe     short loc_12B21
seg002:1BD6                 or      ax, ax
seg002:1BD8                 js      short loc_12B1F
seg002:1BDA                 mov     ax, 3Fh ; '?'
seg002:1BDD                 jmp     short loc_12B21
seg002:1BDF ; ---------------------------------------------------------------------------
seg002:1BDF
seg002:1BDF loc_12B1F:                              ; CODE XREF: sub_12B0D+B↑j
seg002:1BDF                 sub     ax, ax
seg002:1BE1
seg002:1BE1 loc_12B21:                              ; CODE XREF: sub_12B0D+7↑j
seg002:1BE1                                         ; sub_12B0D+10↑j
seg002:1BE1                 sub     ax, 3Fh ; '?'
seg002:1BE4                 neg     ax
seg002:1BE6                 retn
seg002:1BE6 sub_12B0D       endp
seg002:1BE6
seg002:1BE7
seg002:1BE7 ; =============== S U B R O U T I N E =======================================
seg002:1BE7
seg002:1BE7
seg002:1BE7 sub_12B27       proc near               ; CODE XREF: sub_12DD3+4A↓p
seg002:1BE7                 push    cx
seg002:1BE8                 push    di
seg002:1BE9                 push    si
seg002:1BEA                 sub     dh, dh
seg002:1BEC                 mov     dl, [bx+44D4h]
seg002:1BF0                 push    cx
seg002:1BF1                 mov     cl, [bx+4563h]
seg002:1BF5                 sub     ch, ch
seg002:1BF7                 mov     di, cx
seg002:1BF9                 mov     cl, [di+460Eh]
seg002:1BFD                 sub     ch, ch
seg002:1BFF                 mov     si, cx
seg002:1C01                 pop     cx
seg002:1C02                 mov     di, bx
seg002:1C04                 test    si, 1
seg002:1C08                 jz      short loc_12B5F
seg002:1C0A                 mov     al, [di+45ABh]
seg002:1C0E                 call    sub_12B0D
seg002:1C11                 or      al, [di+457Fh]
seg002:1C15                 mov     ah, [bx+44DFh]
seg002:1C19                 add     ah, 20h ; ' '
seg002:1C1C                 call    sub_1266E
seg002:1C1F
seg002:1C1F loc_12B5F:                              ; CODE XREF: sub_12B27+21↑j
seg002:1C1F                 add     di, 0Bh
seg002:1C22                 test    si, 2
seg002:1C26                 jz      short loc_12B7D
seg002:1C28                 mov     al, [di+45ABh]
seg002:1C2C                 call    sub_12B0D
seg002:1C2F                 or      al, [di+457Fh]
seg002:1C33                 mov     ah, [bx+44DFh]
seg002:1C37                 add     ah, 23h ; '#'
seg002:1C3A                 call    sub_1266E
seg002:1C3D
seg002:1C3D loc_12B7D:                              ; CODE XREF: sub_12B27+3F↑j
seg002:1C3D                 add     di, 0Bh
seg002:1C40                 test    si, 4
seg002:1C44                 jz      short loc_12B9B
seg002:1C46                 mov     al, [di+45ABh]
seg002:1C4A                 call    sub_12B0D
seg002:1C4D                 or      al, [di+457Fh]
seg002:1C51                 mov     ah, [bx+44DFh]
seg002:1C55                 add     ah, 28h ; '('
seg002:1C58                 call    sub_1266E
seg002:1C5B
seg002:1C5B loc_12B9B:                              ; CODE XREF: sub_12B27+5D↑j
seg002:1C5B                 add     di, 0Bh
seg002:1C5E                 test    si, 8
seg002:1C62                 jz      short loc_12BB9
seg002:1C64                 mov     al, [di+45ABh]
seg002:1C68                 call    sub_12B0D
seg002:1C6B                 or      al, [di+457Fh]
seg002:1C6F                 mov     ah, [bx+44DFh]
seg002:1C73                 add     ah, 2Bh ; '+'
seg002:1C76                 call    sub_1266E
seg002:1C79
seg002:1C79 loc_12BB9:                              ; CODE XREF: sub_12B27+7B↑j
seg002:1C79                 pop     si
seg002:1C7A                 pop     di
seg002:1C7B                 pop     cx
seg002:1C7C                 retn
seg002:1C7C sub_12B27       endp
seg002:1C7C
seg002:1C7D
seg002:1C7D ; =============== S U B R O U T I N E =======================================
seg002:1C7D
seg002:1C7D
seg002:1C7D sub_12BBD       proc near               ; CODE XREF: sub_12A56+25↑p
seg002:1C7D                 push    di
seg002:1C7E                 mov     di, bx
seg002:1C80                 sub     ah, ah
seg002:1C82                 add     al, [di+45ABh]
seg002:1C86                 sub     cx, cx
seg002:1C88                 call    sub_12B0D
seg002:1C8B                 or      al, [bx+457Fh]
seg002:1C8F                 mov     ah, [bx+44DFh]
seg002:1C93                 cmp     bl, 6
seg002:1C96                 jnz     short loc_12BDB
seg002:1C98                 add     ah, 3
seg002:1C9B
seg002:1C9B loc_12BDB:                              ; CODE XREF: sub_12BBD+19↑j
seg002:1C9B                 add     ah, 20h ; ' '
seg002:1C9E                 mov     dx, 0
seg002:1CA1                 call    sub_1266E
seg002:1CA4                 pop     di
seg002:1CA5                 retn
seg002:1CA5 sub_12BBD       endp
seg002:1CA5
seg002:1CA6
seg002:1CA6 ; =============== S U B R O U T I N E =======================================
seg002:1CA6
seg002:1CA6
seg002:1CA6 sub_12BE6       proc near               ; CODE XREF: sub_12A56+3D↑p
seg002:1CA6                                         ; sub_12A56+6B↑p ...
seg002:1CA6                 push    di
seg002:1CA7                 mov     ah, al
seg002:1CA9                 sub     al, al
seg002:1CAB                 shr     ax, 1
seg002:1CAD                 shr     ax, 1
seg002:1CAF                 shl     bx, 1
seg002:1CB1                 add     ax, [bx+4516h]
seg002:1CB5                 shr     bx, 1
seg002:1CB7                 mov     di, ds:2340h
seg002:1CBB                 shl     di, 1
seg002:1CBD                 add     ax, [di+4494h]
seg002:1CC1                 mov     di, 300h
seg002:1CC4                 sub     ax, di
seg002:1CC6                 jb      short loc_12C32
seg002:1CC8                 cmp     ax, 1800h
seg002:1CCB                 cmc
seg002:1CCC                 jb      short loc_12C32
seg002:1CCE                 sub     dx, dx
seg002:1CD0                 div     di
seg002:1CD2                 shl     al, 1
seg002:1CD4                 shl     al, 1
seg002:1CD6                 mov     ah, al
seg002:1CD8                 sub     al, al
seg002:1CDA                 mov     di, dx
seg002:1CDC                 shl     di, 1
seg002:1CDE                 or      ax, [di+2B14h]
seg002:1CE2                 shl     bx, 1
seg002:1CE4                 mov     [bx+44EAh], ax
seg002:1CE8                 mov     cx, ds:2B12h
seg002:1CEC                 mov     [bx+4500h], cx
seg002:1CF0                 shr     bx, 1
seg002:1CF2
seg002:1CF2 loc_12C32:                              ; CODE XREF: sub_12BE6+20↑j
seg002:1CF2                                         ; sub_12BE6+26↑j
seg002:1CF2                 pop     di
seg002:1CF3                 retn
seg002:1CF3 sub_12BE6       endp
seg002:1CF3
seg002:1CF4
seg002:1CF4 ; =============== S U B R O U T I N E =======================================
seg002:1CF4
seg002:1CF4
seg002:1CF4 sub_12C34       proc near               ; CODE XREF: sub_12DD3+1F↓p
seg002:1CF4                 push    es
seg002:1CF5                 push    di
seg002:1CF6                 mov     cx, ds
seg002:1CF8                 mov     es, cx
seg002:1CFA                 mov     cx, ds:2B10h
seg002:1CFE                 mov     ah, al
seg002:1D00                 or      al, 80h
seg002:1D02                 mov     di, 4542h
seg002:1D05                 repne scasb
seg002:1D07                 jz      short loc_12C69
seg002:1D09                 mov     cx, ds:2B10h
seg002:1D0D                 mov     al, 0FFh
seg002:1D0F                 mov     di, 4542h
seg002:1D12                 repne scasb
seg002:1D14                 jz      short loc_12C69
seg002:1D16                 mov     cx, ds:2B10h
seg002:1D1A                 mov     al, 80h
seg002:1D1C                 mov     di, 4542h
seg002:1D1F
seg002:1D1F loc_12C5F:                              ; CODE XREF: sub_12C34+30↓j
seg002:1D1F                 test    [di], al
seg002:1D21                 jnz     short loc_12C68
seg002:1D23                 inc     di
seg002:1D24                 loop    loc_12C5F
seg002:1D26                 jmp     short loc_12C6B
seg002:1D28 ; ---------------------------------------------------------------------------
seg002:1D28
seg002:1D28 loc_12C68:                              ; CODE XREF: sub_12C34+2D↑j
seg002:1D28                 inc     di
seg002:1D29
seg002:1D29 loc_12C69:                              ; CODE XREF: sub_12C34+13↑j
seg002:1D29                                         ; sub_12C34+20↑j
seg002:1D29                 jmp     short loc_12CAC
seg002:1D2B ; ---------------------------------------------------------------------------
seg002:1D2B
seg002:1D2B loc_12C6B:                              ; CODE XREF: sub_12C34+32↑j
seg002:1D2B                 push    si
seg002:1D2C                 sub     si, si
seg002:1D2E                 mov     cx, ds:2B10h
seg002:1D32                 mov     di, 4500h
seg002:1D35                 mov     bx, 4542h
seg002:1D38                 mov     ax, bx
seg002:1D3A
seg002:1D3A loc_12C7A:                              ; CODE XREF: sub_12C34+61↓j
seg002:1D3A                 push    ax
seg002:1D3B                 mov     ax, [di]
seg002:1D3D                 sub     ax, ds:2B12h
seg002:1D41                 cwd
seg002:1D42                 xor     ax, dx
seg002:1D44                 sub     ax, dx
seg002:1D46                 mov     dx, ax
seg002:1D48                 pop     ax
seg002:1D49                 cmp     dx, si
seg002:1D4B                 jbe     short loc_12C91
seg002:1D4D                 mov     si, dx
seg002:1D4F                 mov     ax, bx
seg002:1D51
seg002:1D51 loc_12C91:                              ; CODE XREF: sub_12C34+57↑j
seg002:1D51                 inc     di
seg002:1D52                 inc     di
seg002:1D53                 inc     bx
seg002:1D54                 dec     cx
seg002:1D55                 jnz     short loc_12C7A
seg002:1D57                 or      si, si
seg002:1D59                 jnz     short loc_12C9E
seg002:1D5B                 stc
seg002:1D5C                 jmp     short loc_12CA9
seg002:1D5E ; ---------------------------------------------------------------------------
seg002:1D5E
seg002:1D5E loc_12C9E:                              ; CODE XREF: sub_12C34+65↑j
seg002:1D5E                 sub     ax, 4542h
seg002:1D61                 mov     bx, ax
seg002:1D63                 call    sub_12A25
seg002:1D66                 mov     ax, bx
seg002:1D68                 clc
seg002:1D69
seg002:1D69 loc_12CA9:                              ; CODE XREF: sub_12C34+68↑j
seg002:1D69                 pop     si
seg002:1D6A                 jmp     short loc_12CB3
seg002:1D6C ; ---------------------------------------------------------------------------
seg002:1D6C
seg002:1D6C loc_12CAC:                              ; CODE XREF: sub_12C34:loc_12C69↑j
seg002:1D6C                 sub     di, 4543h
seg002:1D70                 mov     ax, di
seg002:1D72                 clc
seg002:1D73
seg002:1D73 loc_12CB3:                              ; CODE XREF: sub_12C34+76↑j
seg002:1D73                 pop     di
seg002:1D74                 pop     es
seg002:1D75                 retn
seg002:1D75 sub_12C34       endp
seg002:1D75
seg002:1D76
seg002:1D76 ; =============== S U B R O U T I N E =======================================
seg002:1D76
seg002:1D76
seg002:1D76 sub_12CB6       proc near
seg002:1D76                 sub     ah, ah
seg002:1D78                 stc
seg002:1D79                 shl     al, 1
seg002:1D7B                 mov     bx, ds:2340h
seg002:1D7F                 shl     bx, 1
seg002:1D81                 mov     [bx+44B4h], ax
seg002:1D85                 shr     bx, 1
seg002:1D87                 retn
seg002:1D87 sub_12CB6       endp
seg002:1D87
seg002:1D88 ; ---------------------------------------------------------------------------
seg002:1D88                 cmp     word ptr ds:2340h, 9
seg002:1D8D                 jz      short locret_12D28
seg002:1D8F                 mov     ah, 10h
seg002:1D91                 cmp     al, 2Ah ; '*'
seg002:1D93                 jbe     short loc_12CDD
seg002:1D95                 mov     ah, 30h ; '0'
seg002:1D97                 cmp     al, 54h ; 'T'
seg002:1D99                 jbe     short loc_12CDD
seg002:1D9B                 mov     ah, 20h ; ' '
seg002:1D9D
seg002:1D9D loc_12CDD:                              ; CODE XREF: seg002:1D93↑j
seg002:1D9D                                         ; seg002:1D99↑j
seg002:1D9D                 mov     bx, ds:2340h
seg002:1DA1                 mov     [bx+4464h], ah
seg002:1DA5                 push    si
seg002:1DA6                 mov     si, 4542h
seg002:1DA9                 mov     cx, ds:2B10h
seg002:1DAD                 sub     dh, dh
seg002:1DAF
seg002:1DAF loc_12CEF:                              ; CODE XREF: seg002:1DE5↓j
seg002:1DAF                 lodsb
seg002:1DB0                 and     al, 7Fh
seg002:1DB2                 cmp     al, ds:2340h
seg002:1DB6                 jnz     short loc_12D24
seg002:1DB8                 mov     bx, si
seg002:1DBA                 sub     bx, 4543h
seg002:1DBE                 mov     [bx+452Ch], ah
seg002:1DC2                 push    ax
seg002:1DC3                 mov     al, ah
seg002:1DC5                 mov     dl, [bx+44D4h]
seg002:1DC9                 mov     ah, [bx+44DFh]
seg002:1DCD                 add     ah, 0A0h
seg002:1DD0                 or      al, [bx+45D7h]
seg002:1DD4                 call    sub_1266E
seg002:1DD7                 and     al, 30h
seg002:1DD9                 add     ah, 3
seg002:1DDC                 or      al, [bx+45EDh]
seg002:1DE0                 call    sub_1266E
seg002:1DE3                 pop     ax
seg002:1DE4
seg002:1DE4 loc_12D24:                              ; CODE XREF: seg002:1DB6↑j
seg002:1DE4                 dec     cx
seg002:1DE5                 jnz     short loc_12CEF
seg002:1DE7                 pop     si
seg002:1DE8
seg002:1DE8 locret_12D28:                           ; CODE XREF: seg002:1D8D↑j
seg002:1DE8                 retn
seg002:1DE9 ; ---------------------------------------------------------------------------
seg002:1DE9                 push    es
seg002:1DEA                 push    di
seg002:1DEB                 cmp     word ptr ds:2340h, 9
seg002:1DF0                 jz      short loc_12D5C
seg002:1DF2                 mov     bx, ds:2340h
seg002:1DF6                 mov     [bx+4484h], al
seg002:1DFA                 or      al, al
seg002:1DFC                 jnz     short loc_12D5C
seg002:1DFE                 mov     cx, ds
seg002:1E00                 mov     es, cx
seg002:1E02                 mov     cx, 0Bh
seg002:1E05                 mov     di, 456Eh
seg002:1E08                 mov     al, ds:2340h
seg002:1E0B
seg002:1E0B loc_12D4B:                              ; CODE XREF: seg002:1E1A↓j
seg002:1E0B                 repne scasb
seg002:1E0D                 jnz     short loc_12D5C
seg002:1E0F                 mov     bx, di
seg002:1E11                 sub     bx, 456Fh
seg002:1E15                 call    sub_12A25
seg002:1E18                 or      cx, cx
seg002:1E1A                 jnz     short loc_12D4B
seg002:1E1C
seg002:1E1C loc_12D5C:                              ; CODE XREF: seg002:1DF0↑j
seg002:1E1C                                         ; seg002:1DFC↑j ...
seg002:1E1C                 pop     di
seg002:1E1D                 pop     es
seg002:1E1E                 retn
seg002:1E1F
seg002:1E1F ; =============== S U B R O U T I N E =======================================
seg002:1E1F
seg002:1E1F
seg002:1E1F sub_12D5F       proc near               ; CODE XREF: sub_123C8:loc_123D4↑p
seg002:1E1F                 cld
seg002:1E20                 mov     ds:4617h, ah
seg002:1E24                 mov     ds:4618h, al
seg002:1E27
seg002:1E27 loc_12D67:                              ; CODE XREF: sub_12DD3:loc_12DD1↓j
seg002:1E27                 mov     cx, ds:2B10h
seg002:1E2B                 cmp     byte ptr ds:2340h, 9
seg002:1E30                 jnz     short loc_12D90
seg002:1E32                 call    sub_129EE
seg002:1E35                 jz      short locret_12DD0
seg002:1E37                 mov     bx, ax
seg002:1E39                 mov     al, [bx+45FEh]
seg002:1E3D                 not     al
seg002:1E3F                 and     al, ds:4603h
seg002:1E43                 mov     ds:4603h, al
seg002:1E46                 mov     ah, 0BDh
seg002:1E48                 mov     dx, 0
seg002:1E4B                 call    sub_1266E
seg002:1E4E                 jmp     short locret_12DD0
seg002:1E50 ; ---------------------------------------------------------------------------
seg002:1E50
seg002:1E50 loc_12D90:                              ; CODE XREF: sub_12D5F+11↑j
seg002:1E50                 push    es
seg002:1E51                 push    di
seg002:1E52                 mov     ax, ds
seg002:1E54                 mov     es, ax
seg002:1E56                 mov     al, ds:4617h
seg002:1E59                 mov     ah, ds:2340h
seg002:1E5D                 mov     di, 4537h
seg002:1E60                 mov     cx, ds:2B10h
seg002:1E64
seg002:1E64 loc_12DA4:                              ; CODE XREF: sub_12D5F+57↓j
seg002:1E64                 repne scasb
seg002:1E66                 jnz     short loc_12DCE
seg002:1E68                 mov     bx, di
seg002:1E6A                 sub     bx, 4538h
seg002:1E6E                 cmp     ah, [bx+4542h]
seg002:1E72                 jz      short loc_12DB8
seg002:1E74                 jcxz    short loc_12DCE
seg002:1E76                 jmp     short loc_12DA4
seg002:1E78 ; ---------------------------------------------------------------------------
seg002:1E78
seg002:1E78 loc_12DB8:                              ; CODE XREF: sub_12D5F+53↑j
seg002:1E78                 mov     di, ds:2340h
seg002:1E7C                 cmp     byte ptr [di+4484h], 0
seg002:1E81                 jz      short loc_12DCB
seg002:1E83                 mov     ax, di
seg002:1E85                 mov     [bx+456Eh], al
seg002:1E89                 jmp     short loc_12DCE
seg002:1E8B ; ---------------------------------------------------------------------------
seg002:1E8B
seg002:1E8B loc_12DCB:                              ; CODE XREF: sub_12D5F+62↑j
seg002:1E8B                 call    sub_12A25
seg002:1E8E
seg002:1E8E loc_12DCE:                              ; CODE XREF: sub_12D5F+47↑j
seg002:1E8E                                         ; sub_12D5F+55↑j ...
seg002:1E8E                 pop     di
seg002:1E8F                 pop     es
seg002:1E90
seg002:1E90 locret_12DD0:                           ; CODE XREF: sub_12D5F+16↑j
seg002:1E90                                         ; sub_12D5F+2F↑j
seg002:1E90                 retn
seg002:1E90 sub_12D5F       endp
seg002:1E90
seg002:1E91 ; ---------------------------------------------------------------------------
seg002:1E91 ; START OF FUNCTION CHUNK FOR sub_12DD3
seg002:1E91
seg002:1E91 loc_12DD1:                              ; CODE XREF: sub_12DD3+7↓j
seg002:1E91                 jmp     short loc_12D67
seg002:1E91 ; END OF FUNCTION CHUNK FOR sub_12DD3
seg002:1E93
seg002:1E93 ; =============== S U B R O U T I N E =======================================
seg002:1E93
seg002:1E93
seg002:1E93 sub_12DD3       proc near               ; CODE XREF: sub_123E0:loc_123EC↑p
seg002:1E93
seg002:1E93 ; FUNCTION CHUNK AT seg002:1E91 SIZE 00000002 BYTES
seg002:1E93
seg002:1E93                 cld
seg002:1E94                 mov     ds:4617h, ah
seg002:1E98                 or      al, al
seg002:1E9A                 jz      short loc_12DD1
seg002:1E9C                 mov     ds:4618h, al
seg002:1E9F                 mov     bx, ds:2340h
seg002:1EA3                 mov     al, bl
seg002:1EA5                 cmp     al, 9
seg002:1EA7                 jnz     short loc_12DEE
seg002:1EA9                 call    sub_12A56
seg002:1EAC                 jmp     short locret_12E4F
seg002:1EAE ; ---------------------------------------------------------------------------
seg002:1EAE
seg002:1EAE loc_12DEE:                              ; CODE XREF: sub_12DD3+14↑j
seg002:1EAE                 inc     word ptr ds:2B12h
seg002:1EB2                 call    sub_12C34
seg002:1EB5                 jb      short locret_12E4F
seg002:1EB7                 mov     bx, ax
seg002:1EB9                 mov     al, ds:2340h
seg002:1EBC                 xchg    al, [bx+4542h]
seg002:1EC0                 and     al, 7Fh
seg002:1EC2                 cmp     al, ds:2340h
seg002:1EC6                 jz      short loc_12E15
seg002:1EC8                 push    di
seg002:1EC9                 mov     di, ds:2340h
seg002:1ECD                 mov     al, [di+4474h]
seg002:1ED1                 call    sub_1285A
seg002:1ED4                 pop     di
seg002:1ED5
seg002:1ED5 loc_12E15:                              ; CODE XREF: sub_12DD3+33↑j
seg002:1ED5                 mov     al, ds:4618h
seg002:1ED8                 call    sub_12AE5
seg002:1EDB                 mov     cx, ax
seg002:1EDD                 call    sub_12B27
seg002:1EE0                 mov     al, ds:4617h
seg002:1EE3                 mov     [bx+4537h], al
seg002:1EE7                 call    sub_12BE6
seg002:1EEA                 jnb     short loc_12E33
seg002:1EEC                 or      byte ptr [bx+4542h], 80h
seg002:1EF1                 jmp     short locret_12E4F
seg002:1EF3 ; ---------------------------------------------------------------------------
seg002:1EF3
seg002:1EF3 loc_12E33:                              ; CODE XREF: sub_12DD3+57↑j
seg002:1EF3                 sub     dh, dh
seg002:1EF5                 mov     dl, [bx+44D4h]
seg002:1EF9                 mov     cl, ah
seg002:1EFB                 mov     ah, [bx+44DFh]
seg002:1EFF                 add     ah, 80h
seg002:1F02                 call    sub_1266E
seg002:1F05                 mov     al, cl
seg002:1F07                 or      al, 20h
seg002:1F09                 add     ah, 10h
seg002:1F0C                 call    sub_1266E
seg002:1F0F
seg002:1F0F locret_12E4F:                           ; CODE XREF: sub_12DD3+19↑j
seg002:1F0F                                         ; sub_12DD3+22↑j ...
seg002:1F0F                 retn
seg002:1F0F sub_12DD3       endp
seg002:1F0F
seg002:1F10
seg002:1F10 ; =============== S U B R O U T I N E =======================================
seg002:1F10
seg002:1F10
seg002:1F10 sub_12E50       proc near               ; CODE XREF: sub_12403:loc_1240F↑p
seg002:1F10                 cld
seg002:1F11                 cmp     ah, 7Bh ; '{'
seg002:1F14                 jb      short loc_12E5B
seg002:1F16                 call    sub_129C4
seg002:1F19                 jmp     short locret_12E7D
seg002:1F1B ; ---------------------------------------------------------------------------
seg002:1F1B
seg002:1F1B loc_12E5B:                              ; CODE XREF: sub_12E50+4↑j
seg002:1F1B                 push    es
seg002:1F1C                 push    di
seg002:1F1D                 xchg    al, ah
seg002:1F1F                 mov     di, ds
seg002:1F21                 mov     es, di
seg002:1F23                 mov     di, 463Dh
seg002:1F26                 mov     cx, 3
seg002:1F29                 repne scasb
seg002:1F2B                 mov     bx, di
seg002:1F2D                 pop     di
seg002:1F2E                 pop     es
seg002:1F2F                 jnz     short locret_12E7D
seg002:1F31                 xchg    al, ah
seg002:1F33                 sub     bx, 463Eh
seg002:1F37                 shl     bx, 1
seg002:1F39                 call    word ptr [bx+4640h]
seg002:1F3D
seg002:1F3D locret_12E7D:                           ; CODE XREF: sub_12E50+9↑j
seg002:1F3D                                         ; sub_12E50+1F↑j
seg002:1F3D                 retn
seg002:1F3D sub_12E50       endp
seg002:1F3D
seg002:1F3E
seg002:1F3E ; =============== S U B R O U T I N E =======================================
seg002:1F3E
seg002:1F3E
seg002:1F3E sub_12E7E       proc near               ; CODE XREF: sub_1241F:loc_1242B↑p
seg002:1F3E                 cld
seg002:1F3F                 mov     bx, ds:2340h
seg002:1F43                 mov     [bx+4474h], ah
seg002:1F47                 push    es
seg002:1F48                 push    di
seg002:1F49                 mov     ax, ds
seg002:1F4B                 mov     es, ax
seg002:1F4D                 cmp     byte ptr ds:2340h, 9
seg002:1F52                 jz      short loc_12EC7
seg002:1F54                 mov     cx, ds:2B10h
seg002:1F58                 mov     al, ds:2340h
seg002:1F5B                 or      al, 80h
seg002:1F5D                 mov     di, 4542h
seg002:1F60
seg002:1F60 loc_12EA0:                              ; CODE XREF: sub_12E7E+2C↓j
seg002:1F60                 repne scasb
seg002:1F62                 jnz     short loc_12EAC
seg002:1F64                 mov     byte ptr [di-1], 0FFh
seg002:1F68                 or      cx, cx
seg002:1F6A                 jnz     short loc_12EA0
seg002:1F6C
seg002:1F6C loc_12EAC:                              ; CODE XREF: sub_12E7E+24↑j
seg002:1F6C                 mov     cx, ds:2B10h
seg002:1F70                 mov     di, 4542h
seg002:1F73
seg002:1F73 loc_12EB3:                              ; CODE XREF: sub_12E7E+47↓j
seg002:1F73                 mov     al, ds:2340h
seg002:1F76                 repne scasb
seg002:1F78                 jnz     short loc_12EC7
seg002:1F7A                 mov     bx, di
seg002:1F7C                 sub     bx, 4543h
seg002:1F80                 call    sub_12A25
seg002:1F83                 or      cx, cx
seg002:1F85                 jnz     short loc_12EB3
seg002:1F87
seg002:1F87 loc_12EC7:                              ; CODE XREF: sub_12E7E+14↑j
seg002:1F87                                         ; sub_12E7E+3A↑j
seg002:1F87                 pop     di
seg002:1F88                 pop     es
seg002:1F89                 retn
seg002:1F89 sub_12E7E       endp
seg002:1F89
seg002:1F8A
seg002:1F8A ; =============== S U B R O U T I N E =======================================
seg002:1F8A
seg002:1F8A
seg002:1F8A sub_12ECA       proc near               ; CODE XREF: sub_1244A:loc_12456↑p
seg002:1F8A                 cld
seg002:1F8B                 push    di
seg002:1F8C                 mov     di, ds:2340h
seg002:1F90                 cmp     di, 9
seg002:1F93                 jz      short loc_12F19
seg002:1F95                 shl     ah, 1
seg002:1F97                 rol     ax, 1
seg002:1F99                 sub     al, 80h
seg002:1F9B                 cbw
seg002:1F9C                 shl     di, 1
seg002:1F9E                 mov     [di+4494h], ax
seg002:1FA2                 sub     bx, bx
seg002:1FA4
seg002:1FA4 loc_12EE4:                              ; CODE XREF: sub_12ECA+4D↓j
seg002:1FA4                 mov     al, ds:2340h
seg002:1FA7                 cmp     al, [bx+4542h]
seg002:1FAB                 jnz     short loc_12F12
seg002:1FAD                 mov     al, [bx+4537h]
seg002:1FB1                 call    sub_12BE6
seg002:1FB4                 jb      short loc_12F12
seg002:1FB6                 mov     cl, ah
seg002:1FB8                 mov     ah, [bx+44DFh]
seg002:1FBC                 add     ah, 80h
seg002:1FBF                 sub     dh, dh
seg002:1FC1                 mov     dl, [bx+44D4h]
seg002:1FC5                 call    sub_1266E
seg002:1FC8                 mov     al, cl
seg002:1FCA                 or      al, 20h
seg002:1FCC                 add     ah, 10h
seg002:1FCF                 call    sub_1266E
seg002:1FD2
seg002:1FD2 loc_12F12:                              ; CODE XREF: sub_12ECA+21↑j
seg002:1FD2                                         ; sub_12ECA+2A↑j
seg002:1FD2                 inc     bx
seg002:1FD3                 cmp     bx, ds:2B10h
seg002:1FD7                 jb      short loc_12EE4
seg002:1FD9
seg002:1FD9 loc_12F19:                              ; CODE XREF: sub_12ECA+9↑j
seg002:1FD9                 pop     di
seg002:1FDA                 retn
seg002:1FDA sub_12ECA       endp
seg002:1FDA
seg002:1FDA ; ---------------------------------------------------------------------------
seg002:1FDB                 align 2
seg002:1FDC                 db 3, 80h, 7, 80h, 53h, 59h, 4Eh, 54h, 48h, 3Ah, 0, 4Dh
seg002:1FDC                 db 41h, 50h, 3Ah, 83h dup(0)
seg002:206E byte_12FAE      db 0                    ; DATA XREF: sub_11044+14↑r
seg002:206E                                         ; sub_11044+1B↑w ...
seg002:206F byte_12FAF      db 0                    ; DATA XREF: sub_10FF0+1E↑r
seg002:206F                                         ; sub_10FF0+25↑w ...
seg002:2070 byte_12FB0      db 0                    ; DATA XREF: sub_11044+F↑w
seg002:2070                                         ; sub_11044+65↑w ...
seg002:2071 word_12FB1      dw 0FFFFh               ; DATA XREF: sub_11044+55↑r
seg002:2071                                         ; sub_11044+6A↑r
seg002:2073 word_12FB3      dw 0FFFFh               ; DATA XREF: sub_11044+4E↑r
seg002:2075 score_maybe     dw 0                    ; DATA XREF: sub_11044+43↑w
seg002:2075                                         ; sub_11ED0+65↑w
seg002:2077                 db 2 dup(0)
seg002:2079 word_12FB9      dw 0                    ; DATA XREF: sub_11044:loc_1108B↑r
seg002:2079                                         ; sub_11044:loc_110B5↑w
seg002:207B word_12FBB      dw 0                    ; DATA XREF: sub_11044+4A↑r
seg002:207B                                         ; sub_11044+74↑w
seg002:207D word_12FBD      dw 0FFFFh               ; DATA XREF: sub_11ED0+F↑r
seg002:207F                 db 2 dup(0FFh), 2 dup(0)
seg002:2083 byte_12FC3      db 0FFh                 ; DATA XREF: sub_11ED0+2F↑r
seg002:2083                                         ; sub_11ED0+151↑r
seg002:2084 dword_12FC4     dd 0                    ; DATA XREF: sub_11044+61↑r
seg002:2088 word_12FC8      dw 0                    ; DATA XREF: sub_11044+25↑w
seg002:2088                                         ; sub_11044+7D↑r
seg002:208A word_12FCA      dw 0                    ; DATA XREF: sub_11044+21↑w
seg002:208A                                         ; sub_11044+79↑r
seg002:208C funcs_1102D     dw offset sub_1111E     ; DATA XREF: sub_10FF0+3D↑r
seg002:208C                 dw offset sub_11122
seg002:208C                 dw offset sub_11207
seg002:208C                 dw offset sub_11213
seg002:208C                 dw offset sub_1125B
seg002:208C                 dw offset sub_11292
seg002:208C                 dw offset sub_115DF
seg002:208C                 dw offset sub_11479
seg002:208C                 dw offset sub_11484
seg002:208C                 dw offset sub_1157C
seg002:208C                 dw offset sub_11598
seg002:208C                 dw offset sub_115AC
seg002:208C                 dw offset sub_115C4
seg002:208C                 dw offset sub_116AB
seg002:208C                 dw offset sub_116AF
seg002:208C                 dw offset sub_11CC8
seg002:208C                 dw offset sub_11CF2
seg002:208C                 dw offset sub_11D1E
seg002:208C                 dw offset sub_11D76
seg002:208C                 dw offset ax_0x8000
seg002:208C                 dw offset ax_0x8000
seg002:208C                 dw offset ax_0x8000
seg002:208C                 dw offset ax_0x8000
seg002:208C                 dw offset ax_0x8000
seg002:208C                 dw offset ax_0x8000
seg002:208C                 dw offset ax_0x8000
seg002:208C                 dw offset ax_0x8000
seg002:208C                 dw offset ax_0x8000
seg002:208C                 dw offset sub_116E6
seg002:208C                 dw offset sub_116EA
seg002:208C                 dw offset sub_12198
seg002:208C                 dw offset sub_121C2
seg002:208C                 dw offset sub_121D4
seg002:208C                 dw offset sub_1221B
seg002:208C                 dw offset sub_12246
seg002:208C                 dw offset sub_122D0
seg002:208C                 dw offset ax_0x8000
seg002:208C                 dw offset ax_0x8000
seg002:208C                 dw offset ax_0x8000
seg002:208C                 dw offset ax_0x8000
seg002:20DC ; ---------------------------------------------------------------------------
seg002:20DC                 retn
seg002:20DD ; ---------------------------------------------------------------------------
seg002:20DD                 retn
seg002:20DE ; ---------------------------------------------------------------------------
seg002:20DE                 retn
seg002:20DF ; ---------------------------------------------------------------------------
seg002:20DF                 retn
seg002:20E0 ; ---------------------------------------------------------------------------
seg002:20E0                 retn
seg002:20E1 ; ---------------------------------------------------------------------------
seg002:20E1                 retn
seg002:20E2 ; ---------------------------------------------------------------------------
seg002:20E2                 retn
seg002:20E3 ; ---------------------------------------------------------------------------
seg002:20E3                 retn
seg002:20E4 ; ---------------------------------------------------------------------------
seg002:20E4                 retn
seg002:20E5 ; ---------------------------------------------------------------------------
seg002:20E5                 retn
seg002:20E6 ; ---------------------------------------------------------------------------
seg002:20E6                 retn
seg002:20E7 ; ---------------------------------------------------------------------------
seg002:20E7                 retn
seg002:20E8 ; ---------------------------------------------------------------------------
seg002:20E8                 retn
seg002:20E9 ; ---------------------------------------------------------------------------
seg002:20E9                 retn
seg002:20EA ; ---------------------------------------------------------------------------
seg002:20EA                 retn
seg002:20EB ; ---------------------------------------------------------------------------
seg002:20EB                 retn
seg002:20EC ; ---------------------------------------------------------------------------
seg002:20EC                 retn
seg002:20ED ; ---------------------------------------------------------------------------
seg002:20ED                 retn
seg002:20EE ; ---------------------------------------------------------------------------
seg002:20EE                 retn
seg002:20EF ; ---------------------------------------------------------------------------
seg002:20EF                 retn
seg002:20F0 ; ---------------------------------------------------------------------------
seg002:20F0                 retn
seg002:20F1 ; ---------------------------------------------------------------------------
seg002:20F1                 retn
seg002:20F2 ; ---------------------------------------------------------------------------
seg002:20F2                 retn
seg002:20F3 ; ---------------------------------------------------------------------------
seg002:20F3                 retn
seg002:20F4 ; ---------------------------------------------------------------------------
seg002:20F4                 retn
seg002:20F5 ; ---------------------------------------------------------------------------
seg002:20F5                 retn
seg002:20F6 ; ---------------------------------------------------------------------------
seg002:20F6                 retn
seg002:20F7 ; ---------------------------------------------------------------------------
seg002:20F7                 retn
seg002:20F8 ; ---------------------------------------------------------------------------
seg002:20F8                 retn
seg002:20F9 ; ---------------------------------------------------------------------------
seg002:20F9                 retn
seg002:20FA ; ---------------------------------------------------------------------------
seg002:20FA                 retn
seg002:20FB ; ---------------------------------------------------------------------------
seg002:20FB                 retn
seg002:20FC ; ---------------------------------------------------------------------------
seg002:20FC                 retn
seg002:20FD ; ---------------------------------------------------------------------------
seg002:20FD                 retn
seg002:20FE ; ---------------------------------------------------------------------------
seg002:20FE                 retn
seg002:20FF ; ---------------------------------------------------------------------------
seg002:20FF                 retn
seg002:2100 ; ---------------------------------------------------------------------------
seg002:2100                 retn
seg002:2101 ; ---------------------------------------------------------------------------
seg002:2101                 retn
seg002:2102 ; ---------------------------------------------------------------------------
seg002:2102                 retn
seg002:2103 ; ---------------------------------------------------------------------------
seg002:2103                 retn
seg002:2104 ; ---------------------------------------------------------------------------
seg002:2104                 retn
seg002:2105 ; ---------------------------------------------------------------------------
seg002:2105                 retn
seg002:2106 ; ---------------------------------------------------------------------------
seg002:2106                 retn
seg002:2107 ; ---------------------------------------------------------------------------
seg002:2107                 retn
seg002:2108 ; ---------------------------------------------------------------------------
seg002:2108                 retn
seg002:2109 ; ---------------------------------------------------------------------------
seg002:2109                 retn
seg002:210A ; ---------------------------------------------------------------------------
seg002:210A                 retn
seg002:210B ; ---------------------------------------------------------------------------
seg002:210B                 retn
seg002:210C ; ---------------------------------------------------------------------------
seg002:210C                 retn
seg002:210D ; ---------------------------------------------------------------------------
seg002:210D                 retn
seg002:210E ; ---------------------------------------------------------------------------
seg002:210E                 retn
seg002:210F ; ---------------------------------------------------------------------------
seg002:210F                 retn
seg002:2110 ; ---------------------------------------------------------------------------
seg002:2110                 retn
seg002:2111 ; ---------------------------------------------------------------------------
seg002:2111                 retn
seg002:2112 ; ---------------------------------------------------------------------------
seg002:2112                 retn
seg002:2113 ; ---------------------------------------------------------------------------
seg002:2113                 retn
seg002:2114 ; ---------------------------------------------------------------------------
seg002:2114                 retn
seg002:2115 ; ---------------------------------------------------------------------------
seg002:2115                 retn
seg002:2116 ; ---------------------------------------------------------------------------
seg002:2116                 retn
seg002:2117 ; ---------------------------------------------------------------------------
seg002:2117                 retn
seg002:2118 ; ---------------------------------------------------------------------------
seg002:2118                 retn
seg002:2119 ; ---------------------------------------------------------------------------
seg002:2119                 retn
seg002:211A ; ---------------------------------------------------------------------------
seg002:211A                 retn
seg002:211B ; ---------------------------------------------------------------------------
seg002:211B                 retn
seg002:211C ; ---------------------------------------------------------------------------
seg002:211C                 retn
seg002:211D ; ---------------------------------------------------------------------------
seg002:211D                 retn
seg002:211E ; ---------------------------------------------------------------------------
seg002:211E                 retn
seg002:211F ; ---------------------------------------------------------------------------
seg002:211F                 retn
seg002:2120 ; ---------------------------------------------------------------------------
seg002:2120                 retn
seg002:2121 ; ---------------------------------------------------------------------------
seg002:2121                 retn
seg002:2122 ; ---------------------------------------------------------------------------
seg002:2122                 retn
seg002:2123 ; ---------------------------------------------------------------------------
seg002:2123                 retn
seg002:2124 ; ---------------------------------------------------------------------------
seg002:2124                 retn
seg002:2125 ; ---------------------------------------------------------------------------
seg002:2125                 retn
seg002:2126 ; ---------------------------------------------------------------------------
seg002:2126                 retn
seg002:2127 ; ---------------------------------------------------------------------------
seg002:2127                 retn
seg002:2128 ; ---------------------------------------------------------------------------
seg002:2128                 retn
seg002:2129 ; ---------------------------------------------------------------------------
seg002:2129                 retn
seg002:212A ; ---------------------------------------------------------------------------
seg002:212A                 retn
seg002:212B ; ---------------------------------------------------------------------------
seg002:212B                 retn
seg002:212C ; ---------------------------------------------------------------------------
seg002:212C                 retn
seg002:212D ; ---------------------------------------------------------------------------
seg002:212D                 retn
seg002:212E ; ---------------------------------------------------------------------------
seg002:212E                 retn
seg002:212F ; ---------------------------------------------------------------------------
seg002:212F                 retn
seg002:2130 ; ---------------------------------------------------------------------------
seg002:2130                 retn
seg002:2131 ; ---------------------------------------------------------------------------
seg002:2131                 retn
seg002:2132 ; ---------------------------------------------------------------------------
seg002:2132                 retn
seg002:2133 ; ---------------------------------------------------------------------------
seg002:2133                 retn
seg002:2134 ; ---------------------------------------------------------------------------
seg002:2134                 retn
seg002:2135 ; ---------------------------------------------------------------------------
seg002:2135                 retn
seg002:2136 ; ---------------------------------------------------------------------------
seg002:2136                 retn
seg002:2137 ; ---------------------------------------------------------------------------
seg002:2137                 retn
seg002:2138 ; ---------------------------------------------------------------------------
seg002:2138                 retn
seg002:2139 ; ---------------------------------------------------------------------------
seg002:2139                 retn
seg002:213A ; ---------------------------------------------------------------------------
seg002:213A                 retn
seg002:213B ; ---------------------------------------------------------------------------
seg002:213B                 retn
seg002:213C ; ---------------------------------------------------------------------------
seg002:213C                 retn
seg002:213D ; ---------------------------------------------------------------------------
seg002:213D                 retn
seg002:213E ; ---------------------------------------------------------------------------
seg002:213E                 retn
seg002:213F ; ---------------------------------------------------------------------------
seg002:213F                 retn
seg002:2140 ; ---------------------------------------------------------------------------
seg002:2140                 retn
seg002:2141 ; ---------------------------------------------------------------------------
seg002:2141                 retn
seg002:2142 ; ---------------------------------------------------------------------------
seg002:2142                 retn
seg002:2143 ; ---------------------------------------------------------------------------
seg002:2143                 retn
seg002:2144 ; ---------------------------------------------------------------------------
seg002:2144                 retn
seg002:2145 ; ---------------------------------------------------------------------------
seg002:2145                 retn
seg002:2146 ; ---------------------------------------------------------------------------
seg002:2146                 retn
seg002:2147 ; ---------------------------------------------------------------------------
seg002:2147                 retn
seg002:2148 ; ---------------------------------------------------------------------------
seg002:2148                 retn
seg002:2149 ; ---------------------------------------------------------------------------
seg002:2149                 retn
seg002:214A ; ---------------------------------------------------------------------------
seg002:214A                 retn
seg002:214B ; ---------------------------------------------------------------------------
seg002:214B                 retn
seg002:214C ; ---------------------------------------------------------------------------
seg002:214C                 retn
seg002:214D ; ---------------------------------------------------------------------------
seg002:214D                 retn
seg002:214E ; ---------------------------------------------------------------------------
seg002:214E                 retn
seg002:214F ; ---------------------------------------------------------------------------
seg002:214F                 retn
seg002:2150 ; ---------------------------------------------------------------------------
seg002:2150                 retn
seg002:2151 ; ---------------------------------------------------------------------------
seg002:2151                 retn
seg002:2152 ; ---------------------------------------------------------------------------
seg002:2152                 retn
seg002:2153 ; ---------------------------------------------------------------------------
seg002:2153                 retn
seg002:2154 ; ---------------------------------------------------------------------------
seg002:2154                 retn
seg002:2155 ; ---------------------------------------------------------------------------
seg002:2155                 retn
seg002:2156 ; ---------------------------------------------------------------------------
seg002:2156                 retn
seg002:2157 ; ---------------------------------------------------------------------------
seg002:2157                 retn
seg002:2158 ; ---------------------------------------------------------------------------
seg002:2158                 retn
seg002:2159 ; ---------------------------------------------------------------------------
seg002:2159                 retn
seg002:215A ; ---------------------------------------------------------------------------
seg002:215A                 retn
seg002:215B ; ---------------------------------------------------------------------------
seg002:215B                 retn
seg002:215C ; ---------------------------------------------------------------------------
seg002:215C                 retn
seg002:215D ; ---------------------------------------------------------------------------
seg002:215D                 retn
seg002:215E ; ---------------------------------------------------------------------------
seg002:215E                 retn
seg002:215F ; ---------------------------------------------------------------------------
seg002:215F                 retn
seg002:2160 ; ---------------------------------------------------------------------------
seg002:2160                 retn
seg002:2161 ; ---------------------------------------------------------------------------
seg002:2161                 retn
seg002:2162 ; ---------------------------------------------------------------------------
seg002:2162                 retn
seg002:2163 ; ---------------------------------------------------------------------------
seg002:2163                 retn
seg002:2164 ; ---------------------------------------------------------------------------
seg002:2164                 retn
seg002:2165 ; ---------------------------------------------------------------------------
seg002:2165                 retn
seg002:2166 ; ---------------------------------------------------------------------------
seg002:2166                 retn
seg002:2167 ; ---------------------------------------------------------------------------
seg002:2167                 retn
seg002:2168 ; ---------------------------------------------------------------------------
seg002:2168                 retn
seg002:2169 ; ---------------------------------------------------------------------------
seg002:2169                 retn
seg002:216A ; ---------------------------------------------------------------------------
seg002:216A                 retn
seg002:216B ; ---------------------------------------------------------------------------
seg002:216B                 retn
seg002:216C ; ---------------------------------------------------------------------------
seg002:216C                 retn
seg002:216D ; ---------------------------------------------------------------------------
seg002:216D                 retn
seg002:216E ; ---------------------------------------------------------------------------
seg002:216E                 retn
seg002:216F ; ---------------------------------------------------------------------------
seg002:216F                 retn
seg002:2170 ; ---------------------------------------------------------------------------
seg002:2170                 retn
seg002:2171 ; ---------------------------------------------------------------------------
seg002:2171                 retn
seg002:2172 ; ---------------------------------------------------------------------------
seg002:2172                 retn
seg002:2173 ; ---------------------------------------------------------------------------
seg002:2173                 retn
seg002:2174 ; ---------------------------------------------------------------------------
seg002:2174                 retn
seg002:2175 ; ---------------------------------------------------------------------------
seg002:2175                 retn
seg002:2176 ; ---------------------------------------------------------------------------
seg002:2176                 retn
seg002:2177 ; ---------------------------------------------------------------------------
seg002:2177                 retn
seg002:2178 ; ---------------------------------------------------------------------------
seg002:2178                 retn
seg002:2179 ; ---------------------------------------------------------------------------
seg002:2179                 retn
seg002:217A ; ---------------------------------------------------------------------------
seg002:217A                 retn
seg002:217B ; ---------------------------------------------------------------------------
seg002:217B                 retn
seg002:217C ; ---------------------------------------------------------------------------
seg002:217C                 retn
seg002:217D ; ---------------------------------------------------------------------------
seg002:217D                 retn
seg002:217E ; ---------------------------------------------------------------------------
seg002:217E                 retn
seg002:217F ; ---------------------------------------------------------------------------
seg002:217F                 retn
seg002:2180 ; ---------------------------------------------------------------------------
seg002:2180                 retn
seg002:2181 ; ---------------------------------------------------------------------------
seg002:2181                 retn
seg002:2182 ; ---------------------------------------------------------------------------
seg002:2182                 retn
seg002:2183 ; ---------------------------------------------------------------------------
seg002:2183                 retn
seg002:2184 ; ---------------------------------------------------------------------------
seg002:2184                 retn
seg002:2185 ; ---------------------------------------------------------------------------
seg002:2185                 retn
seg002:2186 ; ---------------------------------------------------------------------------
seg002:2186                 retn
seg002:2187 ; ---------------------------------------------------------------------------
seg002:2187                 retn
seg002:2188 ; ---------------------------------------------------------------------------
seg002:2188                 retn
seg002:2189 ; ---------------------------------------------------------------------------
seg002:2189                 retn
seg002:218A ; ---------------------------------------------------------------------------
seg002:218A                 retn
seg002:218B ; ---------------------------------------------------------------------------
seg002:218B                 retn
seg002:218C ; ---------------------------------------------------------------------------
seg002:218C                 retn
seg002:218D ; ---------------------------------------------------------------------------
seg002:218D                 retn
seg002:218E ; ---------------------------------------------------------------------------
seg002:218E                 retn
seg002:218F ; ---------------------------------------------------------------------------
seg002:218F                 retn
seg002:2190 ; ---------------------------------------------------------------------------
seg002:2190                 retn
seg002:2191 ; ---------------------------------------------------------------------------
seg002:2191                 retn
seg002:2192 ; ---------------------------------------------------------------------------
seg002:2192                 retn
seg002:2193 ; ---------------------------------------------------------------------------
seg002:2193                 retn
seg002:2194 ; ---------------------------------------------------------------------------
seg002:2194                 retn
seg002:2195 ; ---------------------------------------------------------------------------
seg002:2195                 retn
seg002:2196 ; ---------------------------------------------------------------------------
seg002:2196                 retn
seg002:2197 ; ---------------------------------------------------------------------------
seg002:2197                 retn
seg002:2198 ; ---------------------------------------------------------------------------
seg002:2198                 retn
seg002:2199 ; ---------------------------------------------------------------------------
seg002:2199                 retn
seg002:219A ; ---------------------------------------------------------------------------
seg002:219A                 retn
seg002:219B ; ---------------------------------------------------------------------------
seg002:219B                 retn
seg002:219C ; ---------------------------------------------------------------------------
seg002:219C                 retn
seg002:219D ; ---------------------------------------------------------------------------
seg002:219D                 retn
seg002:219E ; ---------------------------------------------------------------------------
seg002:219E                 retn
seg002:219F ; ---------------------------------------------------------------------------
seg002:219F                 retn
seg002:21A0 ; ---------------------------------------------------------------------------
seg002:21A0                 retn
seg002:21A1 ; ---------------------------------------------------------------------------
seg002:21A1                 retn
seg002:21A2 ; ---------------------------------------------------------------------------
seg002:21A2                 retn
seg002:21A3 ; ---------------------------------------------------------------------------
seg002:21A3                 retn
seg002:21A4 ; ---------------------------------------------------------------------------
seg002:21A4                 retn
seg002:21A5 ; ---------------------------------------------------------------------------
seg002:21A5                 retn
seg002:21A6 ; ---------------------------------------------------------------------------
seg002:21A6                 retn
seg002:21A7 ; ---------------------------------------------------------------------------
seg002:21A7                 retn
seg002:21A8 ; ---------------------------------------------------------------------------
seg002:21A8                 retn
seg002:21A9 ; ---------------------------------------------------------------------------
seg002:21A9                 retn
seg002:21AA ; ---------------------------------------------------------------------------
seg002:21AA                 retn
seg002:21AB ; ---------------------------------------------------------------------------
seg002:21AB                 retn
seg002:21AC ; ---------------------------------------------------------------------------
seg002:21AC                 retn
seg002:21AD ; ---------------------------------------------------------------------------
seg002:21AD                 retn
seg002:21AE ; ---------------------------------------------------------------------------
seg002:21AE                 retn
seg002:21AF ; ---------------------------------------------------------------------------
seg002:21AF                 retn
seg002:21B0 ; ---------------------------------------------------------------------------
seg002:21B0                 retn
seg002:21B1 ; ---------------------------------------------------------------------------
seg002:21B1                 retn
seg002:21B2 ; ---------------------------------------------------------------------------
seg002:21B2                 retn
seg002:21B3 ; ---------------------------------------------------------------------------
seg002:21B3                 retn
seg002:21B4 ; ---------------------------------------------------------------------------
seg002:21B4                 retn
seg002:21B5 ; ---------------------------------------------------------------------------
seg002:21B5                 retn
seg002:21B6 ; ---------------------------------------------------------------------------
seg002:21B6                 retn
seg002:21B7 ; ---------------------------------------------------------------------------
seg002:21B7                 retn
seg002:21B8 ; ---------------------------------------------------------------------------
seg002:21B8                 retn
seg002:21B9 ; ---------------------------------------------------------------------------
seg002:21B9                 retn
seg002:21BA ; ---------------------------------------------------------------------------
seg002:21BA                 retn
seg002:21BB ; ---------------------------------------------------------------------------
seg002:21BB                 retn
seg002:21BC ; ---------------------------------------------------------------------------
seg002:21BC                 retn
seg002:21BD ; ---------------------------------------------------------------------------
seg002:21BD                 retn
seg002:21BE ; ---------------------------------------------------------------------------
seg002:21BE                 retn
seg002:21BF ; ---------------------------------------------------------------------------
seg002:21BF                 retn
seg002:21C0 ; ---------------------------------------------------------------------------
seg002:21C0                 retn
seg002:21C1 ; ---------------------------------------------------------------------------
seg002:21C1                 retn
seg002:21C2 ; ---------------------------------------------------------------------------
seg002:21C2                 retn
seg002:21C3 ; ---------------------------------------------------------------------------
seg002:21C3                 retn
seg002:21C4 ; ---------------------------------------------------------------------------
seg002:21C4                 retn
seg002:21C5 ; ---------------------------------------------------------------------------
seg002:21C5                 retn
seg002:21C6 ; ---------------------------------------------------------------------------
seg002:21C6                 retn
seg002:21C7 ; ---------------------------------------------------------------------------
seg002:21C7                 retn
seg002:21C8 ; ---------------------------------------------------------------------------
seg002:21C8                 retn
seg002:21C9 ; ---------------------------------------------------------------------------
seg002:21C9                 retn
seg002:21CA ; ---------------------------------------------------------------------------
seg002:21CA                 retn
seg002:21CB ; ---------------------------------------------------------------------------
seg002:21CB                 retn
seg002:21CC ; ---------------------------------------------------------------------------
seg002:21CC                 retn
seg002:21CD ; ---------------------------------------------------------------------------
seg002:21CD                 retn
seg002:21CE ; ---------------------------------------------------------------------------
seg002:21CE                 retn
seg002:21CF ; ---------------------------------------------------------------------------
seg002:21CF                 retn
seg002:21D0 ; ---------------------------------------------------------------------------
seg002:21D0                 retn
seg002:21D1 ; ---------------------------------------------------------------------------
seg002:21D1                 retn
seg002:21D2 ; ---------------------------------------------------------------------------
seg002:21D2                 retn
seg002:21D3 ; ---------------------------------------------------------------------------
seg002:21D3                 retn
seg002:21D4 ; ---------------------------------------------------------------------------
seg002:21D4                 retn
seg002:21D5 ; ---------------------------------------------------------------------------
seg002:21D5                 retn
seg002:21D6 ; ---------------------------------------------------------------------------
seg002:21D6                 retn
seg002:21D7 ; ---------------------------------------------------------------------------
seg002:21D7                 retn
seg002:21D8 ; ---------------------------------------------------------------------------
seg002:21D8                 retn
seg002:21D9 ; ---------------------------------------------------------------------------
seg002:21D9                 retn
seg002:21DA ; ---------------------------------------------------------------------------
seg002:21DA                 retn
seg002:21DB ; ---------------------------------------------------------------------------
seg002:21DB                 retn
seg002:21DC ; ---------------------------------------------------------------------------
seg002:21DC                 retn
seg002:21DD ; ---------------------------------------------------------------------------
seg002:21DD                 retn
seg002:21DE ; ---------------------------------------------------------------------------
seg002:21DE                 retn
seg002:21DF ; ---------------------------------------------------------------------------
seg002:21DF                 retn
seg002:21E0 ; ---------------------------------------------------------------------------
seg002:21E0                 retn
seg002:21E1 ; ---------------------------------------------------------------------------
seg002:21E1                 retn
seg002:21E2 ; ---------------------------------------------------------------------------
seg002:21E2                 retn
seg002:21E3 ; ---------------------------------------------------------------------------
seg002:21E3                 retn
seg002:21E4 ; ---------------------------------------------------------------------------
seg002:21E4                 retn
seg002:21E5 ; ---------------------------------------------------------------------------
seg002:21E5                 retn
seg002:21E6 ; ---------------------------------------------------------------------------
seg002:21E6                 retn
seg002:21E7 ; ---------------------------------------------------------------------------
seg002:21E7                 retn
seg002:21E8 ; ---------------------------------------------------------------------------
seg002:21E8                 retn
seg002:21E9 ; ---------------------------------------------------------------------------
seg002:21E9                 retn
seg002:21EA ; ---------------------------------------------------------------------------
seg002:21EA                 retn
seg002:21EB ; ---------------------------------------------------------------------------
seg002:21EB                 retn
seg002:21EC ; ---------------------------------------------------------------------------
seg002:21EC                 retn
seg002:21ED ; ---------------------------------------------------------------------------
seg002:21ED                 retn
seg002:21EE ; ---------------------------------------------------------------------------
seg002:21EE                 retn
seg002:21EF ; ---------------------------------------------------------------------------
seg002:21EF                 retn
seg002:21F0 ; ---------------------------------------------------------------------------
seg002:21F0                 retn
seg002:21F1 ; ---------------------------------------------------------------------------
seg002:21F1                 retn
seg002:21F2 ; ---------------------------------------------------------------------------
seg002:21F2                 retn
seg002:21F3 ; ---------------------------------------------------------------------------
seg002:21F3                 retn
seg002:21F4 ; ---------------------------------------------------------------------------
seg002:21F4                 retn
seg002:21F5 ; ---------------------------------------------------------------------------
seg002:21F5                 retn
seg002:21F6 ; ---------------------------------------------------------------------------
seg002:21F6                 retn
seg002:21F7 ; ---------------------------------------------------------------------------
seg002:21F7                 retn
seg002:21F8 ; ---------------------------------------------------------------------------
seg002:21F8                 retn
seg002:21F9 ; ---------------------------------------------------------------------------
seg002:21F9                 retn
seg002:21FA ; ---------------------------------------------------------------------------
seg002:21FA                 retn
seg002:21FB ; ---------------------------------------------------------------------------
seg002:21FB                 retn
seg002:21FC ; ---------------------------------------------------------------------------
seg002:21FC                 retn
seg002:21FD ; ---------------------------------------------------------------------------
seg002:21FD                 retn
seg002:21FE ; ---------------------------------------------------------------------------
seg002:21FE                 retn
seg002:21FF ; ---------------------------------------------------------------------------
seg002:21FF                 retn
seg002:2200 ; ---------------------------------------------------------------------------
seg002:2200                 retn
seg002:2201 ; ---------------------------------------------------------------------------
seg002:2201                 retn
seg002:2202 ; ---------------------------------------------------------------------------
seg002:2202                 retn
seg002:2203 ; ---------------------------------------------------------------------------
seg002:2203                 retn
seg002:2204 ; ---------------------------------------------------------------------------
seg002:2204                 retn
seg002:2205 ; ---------------------------------------------------------------------------
seg002:2205                 retn
seg002:2206 ; ---------------------------------------------------------------------------
seg002:2206                 retn
seg002:2207 ; ---------------------------------------------------------------------------
seg002:2207                 retn
seg002:2208 ; ---------------------------------------------------------------------------
seg002:2208                 retn
seg002:2209 ; ---------------------------------------------------------------------------
seg002:2209                 retn
seg002:220A ; ---------------------------------------------------------------------------
seg002:220A                 retn
seg002:220B ; ---------------------------------------------------------------------------
seg002:220B                 retn
seg002:220C ; ---------------------------------------------------------------------------
seg002:220C                 retn
seg002:220D ; ---------------------------------------------------------------------------
seg002:220D                 retn
seg002:220E ; ---------------------------------------------------------------------------
seg002:220E                 retn
seg002:220F ; ---------------------------------------------------------------------------
seg002:220F                 retn
seg002:2210 ; ---------------------------------------------------------------------------
seg002:2210                 retn
seg002:2211 ; ---------------------------------------------------------------------------
seg002:2211                 retn
seg002:2212 ; ---------------------------------------------------------------------------
seg002:2212                 retn
seg002:2213 ; ---------------------------------------------------------------------------
seg002:2213                 retn
seg002:2214 ; ---------------------------------------------------------------------------
seg002:2214                 retn
seg002:2215 ; ---------------------------------------------------------------------------
seg002:2215                 retn
seg002:2216 ; ---------------------------------------------------------------------------
seg002:2216                 retn
seg002:2217 ; ---------------------------------------------------------------------------
seg002:2217                 retn
seg002:2218 ; ---------------------------------------------------------------------------
seg002:2218                 retn
seg002:2219 ; ---------------------------------------------------------------------------
seg002:2219                 retn
seg002:221A ; ---------------------------------------------------------------------------
seg002:221A                 retn
seg002:221B ; ---------------------------------------------------------------------------
seg002:221B                 retn
seg002:221C ; ---------------------------------------------------------------------------
seg002:221C                 retn
seg002:221D ; ---------------------------------------------------------------------------
seg002:221D                 retn
seg002:221E ; ---------------------------------------------------------------------------
seg002:221E                 retn
seg002:221F ; ---------------------------------------------------------------------------
seg002:221F                 retn
seg002:2220 ; ---------------------------------------------------------------------------
seg002:2220                 retn
seg002:2221 ; ---------------------------------------------------------------------------
seg002:2221                 retn
seg002:2222 ; ---------------------------------------------------------------------------
seg002:2222                 retn
seg002:2223 ; ---------------------------------------------------------------------------
seg002:2223                 retn
seg002:2224 ; ---------------------------------------------------------------------------
seg002:2224                 retn
seg002:2225 ; ---------------------------------------------------------------------------
seg002:2225                 retn
seg002:2226 ; ---------------------------------------------------------------------------
seg002:2226                 retn
seg002:2227 ; ---------------------------------------------------------------------------
seg002:2227                 retn
seg002:2228 ; ---------------------------------------------------------------------------
seg002:2228                 retn
seg002:2229 ; ---------------------------------------------------------------------------
seg002:2229                 retn
seg002:222A ; ---------------------------------------------------------------------------
seg002:222A                 retn
seg002:222B ; ---------------------------------------------------------------------------
seg002:222B                 retn
seg002:222C ; ---------------------------------------------------------------------------
seg002:222C                 retn
seg002:222D ; ---------------------------------------------------------------------------
seg002:222D                 retn
seg002:222E ; ---------------------------------------------------------------------------
seg002:222E                 retn
seg002:222F ; ---------------------------------------------------------------------------
seg002:222F                 retn
seg002:2230 ; ---------------------------------------------------------------------------
seg002:2230                 retn
seg002:2231 ; ---------------------------------------------------------------------------
seg002:2231                 retn
seg002:2232 ; ---------------------------------------------------------------------------
seg002:2232                 retn
seg002:2233 ; ---------------------------------------------------------------------------
seg002:2233                 retn
seg002:2234 ; ---------------------------------------------------------------------------
seg002:2234                 retn
seg002:2235 ; ---------------------------------------------------------------------------
seg002:2235                 retn
seg002:2236 ; ---------------------------------------------------------------------------
seg002:2236                 retn
seg002:2237 ; ---------------------------------------------------------------------------
seg002:2237                 retn
seg002:2238 ; ---------------------------------------------------------------------------
seg002:2238                 retn
seg002:2239 ; ---------------------------------------------------------------------------
seg002:2239                 retn
seg002:223A ; ---------------------------------------------------------------------------
seg002:223A                 retn
seg002:223B ; ---------------------------------------------------------------------------
seg002:223B                 retn
seg002:223C ; ---------------------------------------------------------------------------
seg002:223C                 retn
seg002:223D ; ---------------------------------------------------------------------------
seg002:223D                 retn
seg002:223E ; ---------------------------------------------------------------------------
seg002:223E                 retn
seg002:223F ; ---------------------------------------------------------------------------
seg002:223F                 retn
seg002:2240 ; ---------------------------------------------------------------------------
seg002:2240                 retn
seg002:2241 ; ---------------------------------------------------------------------------
seg002:2241                 retn
seg002:2242 ; ---------------------------------------------------------------------------
seg002:2242                 retn
seg002:2243 ; ---------------------------------------------------------------------------
seg002:2243                 retn
seg002:2244 ; ---------------------------------------------------------------------------
seg002:2244                 retn
seg002:2245 ; ---------------------------------------------------------------------------
seg002:2245                 retn
seg002:2246 ; ---------------------------------------------------------------------------
seg002:2246                 retn
seg002:2247 ; ---------------------------------------------------------------------------
seg002:2247                 retn
seg002:2248 ; ---------------------------------------------------------------------------
seg002:2248                 retn
seg002:2249 ; ---------------------------------------------------------------------------
seg002:2249                 retn
seg002:224A ; ---------------------------------------------------------------------------
seg002:224A                 retn
seg002:224B ; ---------------------------------------------------------------------------
seg002:224B                 retn
seg002:224C ; ---------------------------------------------------------------------------
seg002:224C                 retn
seg002:224D ; ---------------------------------------------------------------------------
seg002:224D                 retn
seg002:224E ; ---------------------------------------------------------------------------
seg002:224E                 retn
seg002:224F ; ---------------------------------------------------------------------------
seg002:224F                 retn
seg002:2250 ; ---------------------------------------------------------------------------
seg002:2250                 retn
seg002:2251 ; ---------------------------------------------------------------------------
seg002:2251                 retn
seg002:2252 ; ---------------------------------------------------------------------------
seg002:2252                 retn
seg002:2253 ; ---------------------------------------------------------------------------
seg002:2253                 retn
seg002:2254 ; ---------------------------------------------------------------------------
seg002:2254                 retn
seg002:2255 ; ---------------------------------------------------------------------------
seg002:2255                 retn
seg002:2256 ; ---------------------------------------------------------------------------
seg002:2256                 retn
seg002:2257 ; ---------------------------------------------------------------------------
seg002:2257                 retn
seg002:2258 ; ---------------------------------------------------------------------------
seg002:2258                 retn
seg002:2259 ; ---------------------------------------------------------------------------
seg002:2259                 retn
seg002:225A ; ---------------------------------------------------------------------------
seg002:225A                 retn
seg002:225B ; ---------------------------------------------------------------------------
seg002:225B                 retn
seg002:225C ; ---------------------------------------------------------------------------
seg002:225C                 retn
seg002:225D ; ---------------------------------------------------------------------------
seg002:225D                 retn
seg002:225E ; ---------------------------------------------------------------------------
seg002:225E                 retn
seg002:225F ; ---------------------------------------------------------------------------
seg002:225F                 retn
seg002:2260 ; ---------------------------------------------------------------------------
seg002:2260                 retn
seg002:2261 ; ---------------------------------------------------------------------------
seg002:2261                 retn
seg002:2262 ; ---------------------------------------------------------------------------
seg002:2262                 retn
seg002:2263 ; ---------------------------------------------------------------------------
seg002:2263                 retn
seg002:2264 ; ---------------------------------------------------------------------------
seg002:2264                 retn
seg002:2265 ; ---------------------------------------------------------------------------
seg002:2265                 retn
seg002:2266 ; ---------------------------------------------------------------------------
seg002:2266                 retn
seg002:2267 ; ---------------------------------------------------------------------------
seg002:2267                 retn
seg002:2268 ; ---------------------------------------------------------------------------
seg002:2268                 retn
seg002:2269 ; ---------------------------------------------------------------------------
seg002:2269                 retn
seg002:226A ; ---------------------------------------------------------------------------
seg002:226A                 retn
seg002:226B ; ---------------------------------------------------------------------------
seg002:226B                 retn
seg002:226C ; ---------------------------------------------------------------------------
seg002:226C                 retn
seg002:226D ; ---------------------------------------------------------------------------
seg002:226D                 retn
seg002:226E ; ---------------------------------------------------------------------------
seg002:226E                 retn
seg002:226F ; ---------------------------------------------------------------------------
seg002:226F                 retn
seg002:2270 ; ---------------------------------------------------------------------------
seg002:2270                 retn
seg002:2271 ; ---------------------------------------------------------------------------
seg002:2271                 retn
seg002:2272 ; ---------------------------------------------------------------------------
seg002:2272                 retn
seg002:2273 ; ---------------------------------------------------------------------------
seg002:2273                 retn
seg002:2274 ; ---------------------------------------------------------------------------
seg002:2274                 retn
seg002:2275 ; ---------------------------------------------------------------------------
seg002:2275                 retn
seg002:2276 ; ---------------------------------------------------------------------------
seg002:2276                 retn
seg002:2277 ; ---------------------------------------------------------------------------
seg002:2277                 retn
seg002:2278 ; ---------------------------------------------------------------------------
seg002:2278                 retn
seg002:2279 ; ---------------------------------------------------------------------------
seg002:2279                 retn
seg002:227A ; ---------------------------------------------------------------------------
seg002:227A                 retn
seg002:227B ; ---------------------------------------------------------------------------
seg002:227B                 retn
seg002:227C ; ---------------------------------------------------------------------------
seg002:227C                 retn
seg002:227D ; ---------------------------------------------------------------------------
seg002:227D                 retn
seg002:227E ; ---------------------------------------------------------------------------
seg002:227E                 retn
seg002:227F ; ---------------------------------------------------------------------------
seg002:227F                 retn
seg002:2280 ; ---------------------------------------------------------------------------
seg002:2280                 retn
seg002:2281 ; ---------------------------------------------------------------------------
seg002:2281                 retn
seg002:2282 ; ---------------------------------------------------------------------------
seg002:2282                 retn
seg002:2283 ; ---------------------------------------------------------------------------
seg002:2283                 retn
seg002:2284 ; ---------------------------------------------------------------------------
seg002:2284                 retn
seg002:2285 ; ---------------------------------------------------------------------------
seg002:2285                 retn
seg002:2286 ; ---------------------------------------------------------------------------
seg002:2286                 retn
seg002:2287 ; ---------------------------------------------------------------------------
seg002:2287                 retn
seg002:2288 ; ---------------------------------------------------------------------------
seg002:2288                 retn
seg002:2289 ; ---------------------------------------------------------------------------
seg002:2289                 retn
seg002:228A ; ---------------------------------------------------------------------------
seg002:228A                 retn
seg002:228B ; ---------------------------------------------------------------------------
seg002:228B                 retn
seg002:228C ; ---------------------------------------------------------------------------
seg002:228C                 retn
seg002:228D ; ---------------------------------------------------------------------------
seg002:228D                 retn
seg002:228E ; ---------------------------------------------------------------------------
seg002:228E                 retn
seg002:228F ; ---------------------------------------------------------------------------
seg002:228F                 retn
seg002:2290 ; ---------------------------------------------------------------------------
seg002:2290                 retn
seg002:2291 ; ---------------------------------------------------------------------------
seg002:2291                 retn
seg002:2292 ; ---------------------------------------------------------------------------
seg002:2292                 retn
seg002:2293 ; ---------------------------------------------------------------------------
seg002:2293                 retn
seg002:2294 ; ---------------------------------------------------------------------------
seg002:2294                 retn
seg002:2295 ; ---------------------------------------------------------------------------
seg002:2295                 retn
seg002:2296 ; ---------------------------------------------------------------------------
seg002:2296                 retn
seg002:2297 ; ---------------------------------------------------------------------------
seg002:2297                 retn
seg002:2298 ; ---------------------------------------------------------------------------
seg002:2298                 retn
seg002:2299 ; ---------------------------------------------------------------------------
seg002:2299                 retn
seg002:229A ; ---------------------------------------------------------------------------
seg002:229A                 retn
seg002:229B ; ---------------------------------------------------------------------------
seg002:229B                 retn
seg002:229C ; ---------------------------------------------------------------------------
seg002:229C                 retn
seg002:229D ; ---------------------------------------------------------------------------
seg002:229D                 retn
seg002:229E ; ---------------------------------------------------------------------------
seg002:229E                 retn
seg002:229F ; ---------------------------------------------------------------------------
seg002:229F                 retn
seg002:22A0 ; ---------------------------------------------------------------------------
seg002:22A0                 retn
seg002:22A1 ; ---------------------------------------------------------------------------
seg002:22A1                 retn
seg002:22A2 ; ---------------------------------------------------------------------------
seg002:22A2                 retn
seg002:22A3 ; ---------------------------------------------------------------------------
seg002:22A3                 retn
seg002:22A4 ; ---------------------------------------------------------------------------
seg002:22A4                 retn
seg002:22A5 ; ---------------------------------------------------------------------------
seg002:22A5                 retn
seg002:22A6 ; ---------------------------------------------------------------------------
seg002:22A6                 retn
seg002:22A7 ; ---------------------------------------------------------------------------
seg002:22A7                 retn
seg002:22A8 ; ---------------------------------------------------------------------------
seg002:22A8                 retn
seg002:22A9 ; ---------------------------------------------------------------------------
seg002:22A9                 retn
seg002:22AA ; ---------------------------------------------------------------------------
seg002:22AA                 retn
seg002:22AB ; ---------------------------------------------------------------------------
seg002:22AB                 retn
seg002:22AC ; ---------------------------------------------------------------------------
seg002:22AC                 retn
seg002:22AD ; ---------------------------------------------------------------------------
seg002:22AD                 retn
seg002:22AE ; ---------------------------------------------------------------------------
seg002:22AE                 retn
seg002:22AF ; ---------------------------------------------------------------------------
seg002:22AF                 retn
seg002:22B0 ; ---------------------------------------------------------------------------
seg002:22B0                 retn
seg002:22B1 ; ---------------------------------------------------------------------------
seg002:22B1                 retn
seg002:22B2 ; ---------------------------------------------------------------------------
seg002:22B2                 retn
seg002:22B3 ; ---------------------------------------------------------------------------
seg002:22B3                 retn
seg002:22B4 ; ---------------------------------------------------------------------------
seg002:22B4                 retn
seg002:22B5 ; ---------------------------------------------------------------------------
seg002:22B5                 retn
seg002:22B6 ; ---------------------------------------------------------------------------
seg002:22B6                 retn
seg002:22B7 ; ---------------------------------------------------------------------------
seg002:22B7                 retn
seg002:22B8 ; ---------------------------------------------------------------------------
seg002:22B8                 retn
seg002:22B9 ; ---------------------------------------------------------------------------
seg002:22B9                 retn
seg002:22BA ; ---------------------------------------------------------------------------
seg002:22BA                 retn
seg002:22BB ; ---------------------------------------------------------------------------
seg002:22BB                 retn
seg002:22BC ; ---------------------------------------------------------------------------
seg002:22BC                 retn
seg002:22BD ; ---------------------------------------------------------------------------
seg002:22BD                 retn
seg002:22BE ; ---------------------------------------------------------------------------
seg002:22BE                 retn
seg002:22BF ; ---------------------------------------------------------------------------
seg002:22BF                 retn
seg002:22C0 ; ---------------------------------------------------------------------------
seg002:22C0                 retn
seg002:22C1 ; ---------------------------------------------------------------------------
seg002:22C1                 retn
seg002:22C2 ; ---------------------------------------------------------------------------
seg002:22C2                 retn
seg002:22C3 ; ---------------------------------------------------------------------------
seg002:22C3                 retn
seg002:22C4 ; ---------------------------------------------------------------------------
seg002:22C4                 retn
seg002:22C5 ; ---------------------------------------------------------------------------
seg002:22C5                 retn
seg002:22C6 ; ---------------------------------------------------------------------------
seg002:22C6                 retn
seg002:22C7 ; ---------------------------------------------------------------------------
seg002:22C7                 retn
seg002:22C8 ; ---------------------------------------------------------------------------
seg002:22C8                 retn
seg002:22C9 ; ---------------------------------------------------------------------------
seg002:22C9                 retn
seg002:22CA ; ---------------------------------------------------------------------------
seg002:22CA                 retn
seg002:22CB ; ---------------------------------------------------------------------------
seg002:22CB                 retn
seg002:22CC ; ---------------------------------------------------------------------------
seg002:22CC                 retn
seg002:22CD ; ---------------------------------------------------------------------------
seg002:22CD                 retn
seg002:22CE ; ---------------------------------------------------------------------------
seg002:22CE                 retn
seg002:22CF ; ---------------------------------------------------------------------------
seg002:22CF                 retn
seg002:22D0 ; ---------------------------------------------------------------------------
seg002:22D0                 retn
seg002:22D1 ; ---------------------------------------------------------------------------
seg002:22D1                 retn
seg002:22D2 ; ---------------------------------------------------------------------------
seg002:22D2                 retn
seg002:22D3 ; ---------------------------------------------------------------------------
seg002:22D3                 retn
seg002:22D4 ; ---------------------------------------------------------------------------
seg002:22D4                 retn
seg002:22D5 ; ---------------------------------------------------------------------------
seg002:22D5                 retn
seg002:22D6 ; ---------------------------------------------------------------------------
seg002:22D6                 retn
seg002:22D7 ; ---------------------------------------------------------------------------
seg002:22D7                 retn
seg002:22D8 ; ---------------------------------------------------------------------------
seg002:22D8                 retn
seg002:22D9 ; ---------------------------------------------------------------------------
seg002:22D9                 retn
seg002:22DA ; ---------------------------------------------------------------------------
seg002:22DA                 retn
seg002:22DB ; ---------------------------------------------------------------------------
seg002:22DB                 retn
seg002:22DB ; ---------------------------------------------------------------------------
seg002:22DC                 db 0Eh dup(0), 0A9h, 4, 0A9h, 4
seg002:22EE word_1322E      dw 0                    ; DATA XREF: sub_11ED0+BD↑r
seg002:22F0 word_13230      dw 0                    ; DATA XREF: sub_11ED0+C0↑r
seg002:22F2                 db 7 dup(0), 80h, 2 dup(0)
seg002:22FC dword_1323C     dd 0                    ; DATA XREF: sub_11ED0:loc_1202A↑r
seg002:22FC                                         ; sub_11ED0+16E↑r ...
seg002:2300                 db 4 dup(0)
seg002:2304 word_13244      dw 0                    ; DATA XREF: sub_11ED0+8A↑r
seg002:2306 word_13246      dw 0                    ; DATA XREF: sub_11ED0+84↑r
seg002:2308 word_13248      dw 0                    ; DATA XREF: sub_11ED0+79↑r
seg002:2308                                         ; sub_11ED0:loc_11F69↑w
seg002:230A word_1324A      dw 0                    ; DATA XREF: sub_11ED0+7C↑r
seg002:230A                                         ; sub_11ED0+9C↑w
seg002:230C word_1324C      dw 0                    ; DATA XREF: sub_11ED0+91↑w
seg002:230C                                         ; sub_11ED0+10E↑r
seg002:230E word_1324E      dw 0                    ; DATA XREF: sub_11ED0+3B↑w
seg002:230E                                         ; sub_11ED0+144↑r
seg002:2310 word_13250      dw 0                    ; DATA XREF: sub_11ED0+37↑w
seg002:2310                                         ; sub_11ED0+148↑r
seg002:2312                 db 8 dup(0)
seg002:231A dword_1325A     dd 0                    ; DATA XREF: sub_11ED0+74↑r
seg002:231A                                         ; sub_11ED0+101↑w ...
seg002:231E dword_1325E     dd 0                    ; DATA XREF: sub_11ED0+C8↑r
seg002:231E                                         ; sub_11ED0+E9↑r ...
seg002:2322 word_13262      dw 0                    ; DATA XREF: sub_11ED0+E5↑r
seg002:2324 word_13264      dw 0                    ; DATA XREF: sub_11ED0+E1↑r
seg002:2326 word_13266      dw 0                    ; DATA XREF: sub_11ED0:loc_11F78↑w
seg002:2326                                         ; sub_11ED0+DD↑r ...
seg002:2328 word_13268      dw 0                    ; DATA XREF: sub_11ED0+AE↑w
seg002:2328                                         ; sub_11ED0+D9↑r
seg002:232A                 db 0
seg002:232B byte_1326B      db 0                    ; DATA XREF: sub_11044:loc_11080↑r
seg002:232B                                         ; sub_11ED0+59↑r ...
seg002:232C byte_1326C      db 0                    ; DATA XREF: sub_11ED0+6D↑r
seg002:232C                                         ; sub_11ED0:loc_11FBE↑r ...
seg002:232D                 db 2 dup(0)
seg002:232F byte_1326F      db 0                    ; DATA XREF: sub_11ED0+B6↑r
seg002:2330                 db 0
seg002:2331 byte_13271      db 0                    ; DATA XREF: sub_11ED0:loc_11EFA↑w
seg002:2331                                         ; sub_11ED0+14C↑w
seg002:2332 byte_13272      db 0                    ; DATA XREF: sub_11ED0+115↑w
seg002:2333                 align 8
seg002:2338                 db 1, 0, 1, 8 dup(0), 1, 2, 3, 4, 5, 6, 7, 8, 9, 6 dup(0FFh)
seg002:2338                 db 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0Ah, 0Bh, 0Ch, 0Dh, 0Eh
seg002:2338                 db 0Fh, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 12h dup(0FFh), 0Ch
seg002:2338                 db 0Dh, 0Eh, 9, 10h dup(0FFh), 5 dup(0)
seg002:2397 word_132D7      dw 0                    ; DATA XREF: sub_11044+32↑r
seg002:2399                 db 18h dup(0), 1, 6 dup(0), 5Dh, 0Bh, 97h, 0Bh, 0D6h, 0Bh
seg002:2399                 db 0E9h, 0Bh, 0FCh, 0Bh, 2 dup(0Ch), 1Ch, 0Ch, 2Fh, 0Ch
seg002:2399                 db 3Dh, 0Ch, 3Ch, 0Ch, 47h, 0Ch, 4Eh, 0Ch, 3Ch, 0Ch, 3Ch
seg002:2399                 db 0Ch, 52h, 0Ch, 3Dh, 0Ch, 54h, 0Ch, 3Ch, 0Ch, 55h, 0Ch
seg002:2399                 db 56h, 0Ch, 57h, 0Ch, 3Ch, 0Ch, 58h, 0Ch, 59h, 0Ch, 6Eh
seg002:2399                 db 0Dh, 0CCh, 0Eh, 61Ah dup(0), 0Ah, 0, 0EEh, 23h, 51h
seg002:2399                 db 2Fh, 2 dup(0), 100h dup(0C3h), 2 dup(0), 6, 3 dup(0)
seg002:2399                 db 57h, 1, 57h, 1, 58h, 1, 58h, 1, 58h, 1, 58h, 1, 59h
seg002:2399                 db 1, 59h, 1, 59h, 1, 5Ah, 1, 5Ah, 1, 5Ah, 1, 5Bh, 1, 5Bh
seg002:2399                 db 1, 5Bh, 1, 5Ch, 1, 5Ch, 1, 5Ch, 1, 5Dh, 1, 5Dh, 1, 5Dh
seg002:2399                 db 1, 5Dh, 1, 5Eh, 1, 5Eh, 1, 5Eh, 1, 5Fh, 1, 5Fh, 1, 5Fh
seg002:2399                 db 1, 60h, 1, 60h, 1, 60h, 1, 61h, 1, 61h, 1, 61h, 1, 62h
seg002:2399                 db 1, 62h, 1, 62h, 1, 63h, 1, 63h, 1, 63h, 1, 64h, 1, 64h
seg002:2399                 db 1, 64h, 1, 64h, 1, 65h, 1, 65h, 1, 65h, 1, 66h, 1, 66h
seg002:2399                 db 1, 66h, 1, 67h, 1, 67h, 1, 67h, 1, 68h, 1, 68h, 1, 68h
seg002:2399                 db 1, 69h, 1, 69h, 1, 69h, 1, 6Ah, 1, 6Ah, 1, 6Ah, 1, 6Bh
seg002:2399                 db 1, 6Bh, 1, 6Bh, 1, 6Ch, 1, 6Ch, 1, 6Ch, 1, 6Dh, 1, 6Dh
seg002:2399                 db 1, 6Dh, 1, 6Eh, 1, 6Eh, 1, 6Eh, 1, 6Fh, 1, 6Fh, 1, 6Fh
seg002:2399                 db 1, 70h, 1, 70h, 1, 70h, 1, 71h, 1, 71h, 1, 71h, 1, 72h
seg002:2399                 db 1, 72h, 1, 72h, 1, 73h, 1, 73h, 1, 73h, 1, 74h, 1, 74h
seg002:2399                 db 1, 74h, 1, 75h, 1, 75h, 1, 75h, 1, 76h, 1, 76h, 1, 76h
seg002:2399                 db 1, 77h, 1, 77h, 1, 77h, 1, 78h, 1, 78h, 1, 78h, 1, 79h
seg002:2399                 db 1, 79h, 1, 79h, 1, 7Ah, 1, 7Ah, 1, 7Ah, 1, 7Bh, 1, 7Bh
seg002:2399                 db 1, 7Bh, 1, 7Ch, 1, 7Ch, 1, 7Ch, 1, 7Dh, 1, 7Dh, 1, 7Dh
seg002:2399                 db 1, 7Eh, 1, 7Eh, 1, 7Eh, 1, 7Fh, 1, 7Fh, 1, 80h, 1, 80h
seg002:2399                 db 1, 80h, 1, 81h, 1, 81h, 1, 81h, 1, 82h, 1, 82h, 1, 82h
seg002:2399                 db 1, 83h, 1, 83h, 1, 83h, 1, 84h, 1, 84h, 1, 84h, 1, 85h
seg002:2399                 db 1, 85h, 1, 85h, 1, 86h, 1, 86h, 1, 87h, 1, 87h, 1, 87h
seg002:2399                 db 1, 88h, 1, 88h, 1, 88h, 1, 89h, 1, 89h, 1, 89h, 1, 8Ah
seg002:2399                 db 1, 8Ah, 1, 8Ah, 1, 8Bh, 1, 8Bh, 1, 8Bh, 1, 8Ch, 1, 8Ch
seg002:2399                 db 1, 8Dh, 1, 8Dh, 1, 8Dh, 1, 8Eh, 1, 8Eh, 1, 8Eh, 1, 8Fh
seg002:2399                 db 1, 8Fh, 1, 8Fh, 1, 90h, 1, 90h, 1, 91h, 1, 91h, 1, 91h
seg002:2399                 db 1, 92h, 1, 92h, 1, 92h, 1, 93h, 1, 93h, 1, 93h, 1, 94h
seg002:2399                 db 1, 94h, 1, 95h, 1, 95h, 1, 95h, 1, 96h, 1, 96h, 1, 96h
seg002:2399                 db 1, 97h, 1, 97h, 1, 97h, 1, 98h, 1, 98h, 1, 99h, 1, 99h
seg002:2399                 db 1, 99h, 1, 9Ah, 1, 9Ah, 1, 9Ah, 1, 9Bh, 1, 9Bh, 1, 9Ch
seg002:2399                 db 1, 9Ch, 1, 9Ch, 1, 9Dh, 1, 9Dh, 1, 9Dh, 1, 9Eh, 1, 9Eh
seg002:2399                 db 1, 9Eh, 1, 9Fh, 1, 9Fh, 1, 0A0h, 1, 0A0h, 1, 0A0h, 1
seg002:2399                 db 0A1h, 1, 0A1h, 1, 0A1h, 1, 0A2h, 1, 0A2h, 1, 0A3h, 1
seg002:2399                 db 0A3h, 1
seg002:2CD2                 db 0A3h, 1, 0A4h, 1, 0A4h, 1, 0A5h, 1, 0A5h, 1, 0A5h, 1
seg002:2CD2                 db 0A6h, 1, 0A6h, 1, 0A6h, 1, 0A7h, 1, 0A7h, 1, 0A8h, 1
seg002:2CD2                 db 0A8h, 1, 0A8h, 1, 0A9h, 1, 0A9h, 1, 0A9h, 1, 0AAh, 1
seg002:2CD2                 db 0AAh, 1, 0ABh, 1, 0ABh, 1, 0ABh, 1, 0ACh, 1, 0ACh, 1
seg002:2CD2                 db 0ADh, 1, 0ADh, 1, 0ADh, 1, 0AEh, 1, 0AEh, 1, 0AEh, 1
seg002:2CD2                 db 0AFh, 1, 0AFh, 1, 0B0h, 1, 0B0h, 1, 0B0h, 1, 0B1h, 1
seg002:2CD2                 db 0B1h, 1, 0B2h, 1, 0B2h, 1, 0B2h, 1, 0B3h, 1, 0B3h, 1
seg002:2CD2                 db 0B4h, 1, 0B4h, 1, 0B4h, 1, 0B5h, 1, 0B5h, 1, 0B6h, 1
seg002:2CD2                 db 0B6h, 1, 0B6h, 1, 0B7h, 1, 0B7h, 1, 0B8h, 1, 0B8h, 1
seg002:2CD2                 db 0B8h, 1, 0B9h, 1, 0B9h, 1, 0BAh, 1, 0BAh, 1, 0BAh, 1
seg002:2CD2                 db 0BBh, 1, 0BBh, 1, 0BCh, 1, 0BCh, 1, 0BCh, 1, 0BDh, 1
seg002:2CD2                 db 0BDh, 1, 0BEh, 1, 0BEh, 1, 0BEh, 1, 0BFh, 1, 0BFh, 1
seg002:2CD2                 db 0C0h, 1, 0C0h, 1, 0C0h, 1, 0C1h, 1, 0C1h, 1, 0C2h, 1
seg002:2CD2                 db 0C2h, 1, 0C2h, 1, 0C3h, 1, 0C3h, 1, 0C4h, 1, 0C4h, 1
seg002:2CD2                 db 0C4h, 1, 0C5h, 1, 0C5h, 1, 0C6h, 1, 0C6h, 1, 0C6h, 1
seg002:2CD2                 db 0C7h, 1, 0C7h, 1, 0C8h, 1, 0C8h, 1, 0C9h, 1, 0C9h, 1
seg002:2CD2                 db 0C9h, 1, 0CAh, 1, 0CAh, 1, 0CBh, 1, 0CBh, 1, 0CBh, 1
seg002:2CD2                 db 0CCh, 1, 0CCh, 1, 0CDh, 1, 0CDh, 1, 0CDh, 1, 0CEh, 1
seg002:2CD2                 db 0CEh, 1, 0CFh, 1, 0CFh, 1, 0D0h, 1, 0D0h, 1, 0D0h, 1
seg002:2CD2                 db 0D1h, 1, 0D1h, 1, 0D2h, 1, 0D2h, 1, 0D3h, 1, 0D3h, 1
seg002:2CD2                 db 0D3h, 1, 0D4h, 1, 0D4h, 1, 0D5h, 1, 0D5h, 1, 0D5h, 1
seg002:2CD2                 db 0D6h, 1, 0D6h, 1, 0D7h, 1, 0D7h, 1, 0D8h, 1, 0D8h, 1
seg002:2CD2                 db 0D8h, 1, 0D9h, 1, 0D9h, 1, 0DAh, 1, 0DAh, 1, 0DBh, 1
seg002:2CD2                 db 0DBh, 1, 0DBh, 1, 0DCh, 1, 0DCh, 1, 0DDh, 1, 0DDh, 1
seg002:2CD2                 db 0DEh, 1, 0DEh, 1, 0DEh, 1, 0DFh, 1, 0DFh, 1, 0E0h, 1
seg002:2CD2                 db 0E0h, 1, 0E1h, 1, 0E1h, 1, 0E1h, 1, 0E2h, 1, 0E2h, 1
seg002:2CD2                 db 0E3h, 1, 0E3h, 1, 0E4h, 1, 0E4h, 1, 0E5h, 1, 0E5h, 1
seg002:2CD2                 db 0E5h, 1, 0E6h, 1, 0E6h, 1, 0E7h, 1, 0E7h, 1, 0E8h, 1
seg002:2CD2                 db 0E8h, 1, 0E8h, 1, 0E9h, 1, 0E9h, 1, 0EAh, 1, 0EAh, 1
seg002:2CD2                 db 0EBh, 1, 0EBh, 1, 0ECh, 1, 0ECh, 1, 0ECh, 1, 0EDh, 1
seg002:2CD2                 db 0EDh, 1, 0EEh, 1, 0EEh, 1, 0EFh, 1, 0EFh, 1, 0F0h, 1
seg002:2CD2                 db 0F0h, 1, 0F0h, 1, 0F1h, 1, 0F1h, 1, 0F2h, 1, 0F2h, 1
seg002:2CD2                 db 0F3h, 1, 0F3h, 1, 0F4h, 1, 0F4h, 1, 0F5h, 1, 0F5h, 1
seg002:2CD2                 db 0F5h, 1, 0F6h, 1, 0F6h, 1, 0F7h, 1, 0F7h, 1, 0F8h, 1
seg002:2CD2                 db 0F8h, 1, 0F9h, 1, 0F9h, 1, 0FAh, 1, 0FAh, 1, 0FAh, 1
seg002:2CD2                 db 0FBh, 1, 0FBh, 1, 0FCh, 1, 0FCh, 1, 0FDh, 1, 0FDh, 1
seg002:2CD2                 db 0FEh, 1, 0FEh, 1, 0FFh, 1, 0FFh, 1, 0FFh, 1, 0, 2, 0
seg002:2CD2                 db 2, 1, 2, 1, 5 dup(2), 3, 2, 3, 2, 4, 2, 4, 2, 5, 2
seg002:2CD2                 db 5, 2, 6, 2, 6, 2, 6, 2, 7, 2, 7, 2, 8, 2, 8, 2, 9, 2
seg002:2CD2                 db 9, 2, 0Ah, 2, 0Ah, 2, 0Bh, 2, 0Bh, 2, 0Ch, 2, 0Ch, 2
seg002:2CD2                 db 0Dh, 2, 0Dh, 2, 0Eh, 2, 0Eh, 2, 0Eh, 2, 0Fh, 2, 0Fh
seg002:2CD2                 db 2, 10h, 2, 10h, 2, 11h, 2
seg002:2ED6                 db 11h, 2, 12h, 2, 12h, 2, 13h, 2, 13h, 2, 14h, 2, 14h
seg002:2ED6                 db 2, 15h, 2, 15h, 2, 16h, 2, 16h, 2, 17h, 2, 17h, 2, 18h
seg002:2ED6                 db 2, 18h, 2, 19h, 2, 19h, 2, 1Ah, 2, 1Ah, 2, 1Ah, 2, 1Bh
seg002:2ED6                 db 2, 1Bh, 2, 1Ch, 2, 1Ch, 2, 1Dh, 2, 1Dh, 2, 1Eh, 2, 1Eh
seg002:2ED6                 db 2, 1Fh, 2, 1Fh, 2, 20h, 2, 20h, 2, 21h, 2, 21h, 2, 22h
seg002:2ED6                 db 2, 22h, 2, 23h, 2, 23h, 2, 24h, 2, 24h, 2, 25h, 2, 25h
seg002:2ED6                 db 2, 26h, 2, 26h, 2, 27h, 2, 27h, 2, 28h, 2, 28h, 2, 29h
seg002:2ED6                 db 2, 29h, 2, 2Ah, 2, 2Ah, 2, 2Bh, 2, 2Bh, 2, 2Ch, 2, 2Ch
seg002:2ED6                 db 2, 2Dh, 2, 2Dh, 2, 2Eh, 2, 2Eh, 2, 2Fh, 2, 2Fh, 2, 30h
seg002:2ED6                 db 2, 30h, 2, 31h, 2, 31h, 2, 32h, 2, 32h, 2, 33h, 2, 33h
seg002:2ED6                 db 2, 34h, 2, 34h, 2, 35h, 2, 35h, 2, 36h, 2, 36h, 2, 37h
seg002:2ED6                 db 2, 37h, 2, 38h, 2, 38h, 2, 39h, 2, 39h, 2, 3Ah, 2, 3Bh
seg002:2ED6                 db 2, 3Bh, 2, 3Ch, 2, 3Ch, 2, 3Dh, 2, 3Dh, 2, 3Eh, 2, 3Eh
seg002:2ED6                 db 2, 3Fh, 2, 3Fh, 2, 40h, 2, 40h, 2, 41h, 2, 41h, 2, 42h
seg002:2ED6                 db 2, 42h, 2, 43h, 2, 43h, 2, 44h, 2, 44h, 2, 45h, 2, 45h
seg002:2ED6                 db 2, 46h, 2, 46h, 2, 47h, 2, 48h, 2, 48h, 2, 49h, 2, 49h
seg002:2ED6                 db 2, 4Ah, 2, 4Ah, 2, 4Bh, 2, 4Bh, 2, 4Ch, 2, 4Ch, 2, 4Dh
seg002:2ED6                 db 2, 4Dh, 2, 4Eh, 2, 4Eh, 2, 4Fh, 2, 4Fh, 2, 50h, 2, 51h
seg002:2ED6                 db 2, 51h, 2, 52h, 2, 52h, 2, 53h, 2, 53h, 2, 54h, 2, 54h
seg002:2ED6                 db 2, 55h, 2, 55h, 2, 56h, 2, 56h, 2, 57h, 2, 58h, 2, 58h
seg002:2ED6                 db 2, 59h, 2, 59h, 2, 5Ah, 2, 5Ah, 2, 5Bh, 2, 5Bh, 2, 5Ch
seg002:2ED6                 db 2, 5Ch, 2, 5Dh, 2, 5Eh, 2, 5Eh, 2, 5Fh, 2, 5Fh, 2, 60h
seg002:2ED6                 db 2, 60h, 2, 61h, 2, 61h, 2, 62h, 2, 62h, 2, 63h, 2, 64h
seg002:2ED6                 db 2, 64h, 2, 65h, 2, 65h, 2, 66h, 2, 66h, 2, 67h, 2, 67h
seg002:2ED6                 db 2, 68h, 2, 69h, 2, 69h, 2, 6Ah, 2, 6Ah, 2, 6Bh, 2, 6Bh
seg002:2ED6                 db 2, 6Ch, 2, 6Ch, 2, 6Dh, 2, 6Eh, 2, 6Eh, 2, 6Fh, 2, 6Fh
seg002:2ED6                 db 2, 70h, 2, 70h, 2, 71h, 2, 72h, 2, 72h, 2, 73h, 2, 73h
seg002:2ED6                 db 2, 74h, 2, 74h, 2, 75h, 2, 75h, 2, 76h, 2, 77h, 2, 77h
seg002:2ED6                 db 2, 78h, 2, 78h, 2, 79h, 2, 79h, 2, 7Ah, 2, 7Bh, 2, 7Bh
seg002:2ED6                 db 2, 7Ch, 2, 7Ch, 2, 7Dh, 2, 7Dh, 2, 7Eh, 2, 7Fh, 2, 7Fh
seg002:2ED6                 db 2, 80h, 2, 80h, 2, 81h, 2, 82h, 2, 82h, 2, 83h, 2, 83h
seg002:2ED6                 db 2, 84h, 2, 84h, 2, 85h, 2, 86h, 2, 86h, 2, 87h, 2, 87h
seg002:2ED6                 db 2, 88h, 2, 89h, 2, 89h, 2, 8Ah, 2, 8Ah, 2, 8Bh, 2, 8Bh
seg002:2ED6                 db 2, 8Ch, 2, 8Dh, 2, 8Dh, 2, 8Eh, 2, 8Eh, 2, 8Fh, 2, 90h
seg002:2ED6                 db 2, 90h, 2, 91h, 2, 91h, 2, 92h, 2, 93h, 2, 93h, 2, 94h
seg002:2ED6                 db 2, 94h, 2, 95h, 2, 96h, 2, 96h, 2, 97h, 2, 97h, 2, 98h
seg002:2ED6                 db 2, 99h, 2, 99h, 2, 9Ah, 2, 9Ah, 2
seg002:30D6                 db 9Bh, 2, 9Ch, 2, 9Ch, 2, 9Dh, 2, 9Dh, 2, 9Eh, 2, 9Fh
seg002:30D6                 db 2, 9Fh, 2, 0A0h, 2, 0A0h, 2, 0A1h, 2, 0A2h, 2, 0A2h
seg002:30D6                 db 2, 0A3h, 2, 0A3h, 2, 0A4h, 2, 0A5h, 2, 0A5h, 2, 0A6h
seg002:30D6                 db 2, 0A6h, 2, 0A7h, 2, 0A8h, 2, 0A8h, 2, 0A9h, 2, 0AAh
seg002:30D6                 db 2, 0AAh, 2, 0ABh, 2, 0ABh, 2, 0ACh, 2, 0ADh, 2, 0ADh
seg002:30D6                 db 2, 14h, 0ABh, 2 dup(0FFh), 0Fh, 0, 14h, 9Eh, 2 dup(0FFh)
seg002:30D6                 db 0, 1, 12h, 19h, 2 dup(0F0h), 0Eh, 1, 11h, 0, 0F3h, 0F4h
seg002:30D6                 db 0Ah dup(0), 12h, 0, 2 dup(0FFh), 2 dup(0), 12h, 1Ah
seg002:30D6                 db 2 dup(0FFh), 0, 5, 13h, 1Bh, 0F3h, 0F5h, 0, 2 dup(1)
seg002:30D6                 db 0, 0F4h, 0F5h, 0Ah dup(0), 31h, 93h, 0FDh, 0CDh, 1
seg002:30D6                 db 2, 72h, 93h, 0FDh, 0DDh, 0, 3, 32h, 15h, 0FFh, 24h
seg002:30D6                 db 0, 1, 0F1h, 2, 0D3h, 0F3h, 0Ah dup(0), 31h, 94h, 0DFh
seg002:30D6                 db 0FFh, 1, 0, 72h, 94h, 0DFh, 0FFh, 0, 4, 32h, 12h, 0D9h
seg002:30D6                 db 29h, 0, 2, 0F1h, 2, 0D3h, 0B9h, 0Ah dup(0), 10h, 0
seg002:30D6                 db 0FFh, 0F9h, 0Eh, 0, 10h, 9, 0FFh, 0AFh, 0, 2, 1, 10h
seg002:30D6                 db 0F4h, 0E9h, 0Fh, 1, 11h, 1, 0F3h, 0C9h, 0Ah dup(0)
seg002:30D6                 db 0B3h, 0C1h, 2 dup(0DFh), 2 dup(0), 0F3h, 0D7h, 0DCh
seg002:30D6                 db 0FFh, 0, 7, 0B2h, 17h, 2 dup(0D3h), 1, 2, 0F1h, 80h
seg002:30D6                 db 0D2h, 0F3h, 0Bh dup(0), 1Ch, 0EFh, 0AFh, 1, 0, 2, 12h
seg002:30D6                 db 0FFh, 0A0h, 0, 3 dup(1), 0DFh, 22h, 2 dup(0), 1, 4
seg002:30D6                 db 0F5h, 0D5h, 0Ch dup(0), 2 dup(0FFh), 0Fh, 0, 2, 1Eh
seg002:30D6                 db 0FFh, 6, 0, 4, 2, 25h, 0F3h, 0F5h, 0Eh, 2 dup(0), 3
seg002:30D6                 db 0B3h, 0F5h, 9 dup(0), 30h, 0, 8, 2 dup(0FFh), 3 dup(0)
seg002:30D6                 db 1Eh, 9Ch, 0FFh, 2 dup(0), 2, 1Ch, 0D4h, 0F7h, 1, 0
seg002:30D6                 db 1, 0, 0D4h, 0F7h, 0Ah dup(0), 30h, 0E1h, 0FBh, 0E0h
seg002:30D6                 db 0Eh, 3, 32h, 0DCh, 0F4h, 0E6h, 0, 3, 35h, 94h, 0F0h
seg002:30D6                 db 0F3h, 0Fh, 2, 2 dup(1), 0F4h, 0F5h, 0Ah dup(0), 2 dup(12h)
seg002:30D6                 db 0DFh, 0FFh, 1, 0, 17h, 14h, 0DFh, 0FDh, 0, 6, 1Ch, 0Bh
seg002:30D6                 db 0F6h, 0FCh, 1, 6, 1, 0, 0D4h, 0F5h, 0Ah dup(0), 80h
seg002:30D6                 db 0, 2 dup(0FFh), 0Eh, 0, 80h, 36h, 2 dup(0FFh), 0, 1
seg002:30D6                 db 8Ch, 5Ch, 0F3h, 0F5h, 0Eh, 1, 0C2h, 0, 0F3h, 0F5h, 0Ch dup(0)
seg002:30D6                 db 2 dup(0FFh), 3 dup(0), 0Eh, 9Fh, 0FFh, 2 dup(0), 2
seg002:30D6                 db 18h, 2 dup(0F5h), 1, 0, 1, 0, 2 dup(0F5h), 0Ah dup(0)
seg002:30D6                 db 3, 12h, 2 dup(0FFh), 0Eh, 1, 3, 0D2h, 0FFh, 0FEh, 0
seg002:30D6                 db 1, 5, 0CFh, 0F8h, 58h, 0Fh, 6, 1, 0, 0F3h, 0F6h, 0Ah dup(0)
seg002:30D6                 db 21h, 1Ch, 0CFh, 0EFh, 2 dup(0), 21h, 12h, 0F5h, 0E6h
seg002:30D6                 db 0, 1, 24h, 17h, 0F5h, 0E5h, 1, 0, 1, 6, 0C4h, 0E4h
seg002:30D6                 db 0Ah dup(0), 1, 9Eh, 0FFh, 0EFh, 0Eh, 0, 2, 9Eh, 0F3h
seg002:30D6                 db 0EFh, 0, 2, 1, 1Eh, 0F7h, 43h, 0Eh, 3, 11h, 0, 0F3h
seg002:30D6                 db 0D4h, 0Ah dup(0), 22h, 52h, 7Fh, 0BFh, 4, 7, 22h, 52h
seg002:30D6                 db 7Fh, 9Fh, 0, 6, 22h, 4Eh, 73h, 0FFh, 2 dup(5), 0E1h
seg002:30D6                 db 3, 73h, 0FFh, 0Ah dup(0), 22h, 52h, 7Fh, 0BFh, 4, 7
seg002:30D6                 db 22h, 52h, 7Fh, 9Fh, 0, 6, 21h, 8Eh, 73h, 0FFh, 2 dup(5)
seg002:30D6                 db 0E2h, 3, 73h, 0FFh, 0Ah dup(0), 2, 48h, 0FFh, 0BFh
seg002:30D6                 db 4, 0, 2, 48h, 0FFh, 9Eh, 0, 2 dup(2), 4Eh, 0F3h, 0FFh
seg002:30D6                 db 5, 2, 1, 0, 0F4h, 0FFh, 0Ah dup(0), 22h, 5Bh, 7Fh, 0BFh
seg002:30D6                 db 4, 0, 22h, 5Ch, 7Fh, 9Fh, 2 dup(0), 21h, 18h, 73h, 0FCh
seg002:30D6                 db 2 dup(5), 0E1h, 0, 74h, 0FFh, 0Ah dup(0), 20h, 43h
seg002:30D6                 db 7Fh, 0BFh, 4, 0, 20h, 12h, 7Fh, 9Fh, 2 dup(0), 21h
seg002:30D6                 db 14h, 73h, 0FCh, 5, 4, 0E1h, 0, 74h, 0FFh, 0Ah dup(0)
seg002:30D6                 db 31h, 25h, 50h, 0FFh, 0Eh, 4, 31h, 0
seg002:33BC                 db 50h, 0FFh, 0, 5, 32h, 2Dh, 2 dup(0FFh), 0Fh, 2, 0B1h
seg002:33BC                 db 0, 55h, 0FFh, 0Ah dup(0), 0C1h, 45h, 7Fh, 0FFh, 2 dup(0)
seg002:33BC                 db 0C1h, 68h, 7Dh, 0FFh, 0, 2, 0C1h, 1Eh, 74h, 0FFh, 1
seg002:33BC                 db 3, 0C1h, 0, 74h, 0FFh, 0Ah dup(0), 11h, 21h, 50h, 0FFh
seg002:33BC                 db 0Eh, 4, 11h, 0, 40h, 0FFh, 0, 4, 13h, 0, 2 dup(0FFh)
seg002:33BC                 db 0Fh, 2, 0D1h, 0, 55h, 0FFh, 0Ah dup(0), 11h, 0, 0F2h
seg002:33BC                 db 0FFh, 0Eh, 0, 10h, 1Ch, 0FCh, 0FFh, 0, 5, 12h, 1Bh
seg002:33BC                 db 0F1h, 0F2h, 0Eh, 2 dup(1), 0, 0D4h, 0FFh, 0Ah dup(0)
seg002:33BC                 db 11h, 8, 2 dup(0FFh), 8, 0, 10h, 28h, 2 dup(0FFh), 0
seg002:33BC                 db 3, 1, 8, 0F4h, 0F3h, 8, 1, 2, 1, 0F4h, 0FFh, 0Ah dup(0)
seg002:33BC                 db 11h, 12h, 2 dup(0FFh), 0Eh, 0, 12h, 1Eh, 2 dup(0FFh)
seg002:33BC                 db 0, 5, 13h, 1Eh, 0F3h, 0FFh, 0Eh, 2 dup(1), 0, 0D3h
seg002:33BC                 db 0FFh, 0Bh dup(0), 25h, 2 dup(0FFh), 3 dup(0), 21h, 2 dup(0FFh)
seg002:33BC                 db 0, 5, 1, 5, 2 dup(0F0h), 1, 0, 1, 0, 0F4h, 0F6h, 0Bh dup(0)
seg002:33BC                 db 8, 2 dup(0FFh), 3 dup(0), 5, 2 dup(0FFh), 0, 2, 1, 8
seg002:33BC                 db 0F0h, 0FFh, 2 dup(1), 2, 1, 0F4h, 0FFh, 0Ah dup(0)
seg002:33BC                 db 20h, 8, 2 dup(0FFh), 1, 0, 20h, 8, 2 dup(0FFh), 2 dup(0)
seg002:33BC                 db 21h, 8, 0F0h, 0FFh, 0, 1, 22h, 0, 0F3h, 0FFh, 0Ah dup(0)
seg002:33BC                 db 20h, 8, 2 dup(0FFh), 1, 0, 20h, 8, 2 dup(0FFh), 2 dup(0)
seg002:33BC                 db 21h, 8, 0F0h, 0FFh, 0, 1, 22h, 1, 0F3h, 0FFh, 0Ah dup(0)
seg002:33BC                 db 10h, 1Ch, 2 dup(0FFh), 1, 0, 10h, 8, 2 dup(0FFh), 2 dup(0)
seg002:33BC                 db 14h, 4Ch, 0F0h, 0F1h, 0, 1, 18h, 0Bh, 0F0h, 0F4h, 0Ah dup(0)
seg002:33BC                 db 11h, 0, 0C4h, 0EFh, 9, 0, 10h, 8Fh, 0DFh, 0EFh, 0, 7
seg002:33BC                 db 10h, 17h, 0EFh, 0F0h, 9, 7, 0D1h, 0, 0E3h, 0F6h, 0
seg002:33BC                 db 4, 8 dup(0), 11h, 2, 0F3h, 0EFh, 7, 5, 10h, 0A1h, 0D7h
seg002:33BC                 db 0EFh, 0, 3, 10h, 1Eh, 0E5h, 0FFh, 6, 2, 0D1h, 0, 0E3h
seg002:33BC                 db 0FFh, 0Ah dup(0), 1, 1Eh, 0FFh, 0EFh, 6, 0, 2, 0, 0FFh
seg002:33BC                 db 0EFh, 2 dup(0), 1, 12h, 0F0h, 0F6h, 7, 2 dup(2), 0
seg002:33BC                 db 0F4h, 0F5h, 0Ah dup(0), 20h, 1Ch, 2 dup(0FFh), 1, 0
seg002:33BC                 db 20h, 17h, 0F3h, 0FFh, 0, 2, 23h, 0, 0F3h, 0FFh, 1, 0
seg002:33BC                 db 22h, 3, 2 dup(0FFh), 0Ah dup(0), 1, 1Ch, 0FFh, 0F7h
seg002:33BC                 db 1, 0, 1, 1Eh, 0F4h, 0F7h, 0, 2, 1, 0Eh, 0F2h, 0FFh
seg002:33BC                 db 2 dup(0), 2, 1, 0F5h, 0FFh, 0Ah dup(0), 1, 1Ch, 0FFh
seg002:33BC                 db 0F7h, 1, 0, 1, 1Eh, 0F4h, 0F7h, 0, 2, 1, 4Eh, 0F2h
seg002:33BC                 db 0FFh, 2 dup(0), 2, 0, 0F5h, 0FFh, 0Bh dup(0), 21h, 0F5h
seg002:33BC                 db 0EFh, 0Eh, 2, 0, 1Dh, 0F5h, 0EFh, 0, 2, 0, 90h, 0F3h
seg002:33BC                 db 0EFh, 0Eh, 3 dup(0), 0F5h, 0F9h, 0Ah dup(0), 1, 19h
seg002:33BC                 db 0FFh, 0F7h, 1, 0, 1, 13h, 0F4h, 0F7h, 0, 2, 1, 53h
seg002:33BC                 db 0F2h, 0FFh, 2 dup(0), 2, 1, 0F5h, 0FFh, 0Ah dup(0)
seg002:33BC                 db 12h, 1Fh, 51h, 0F2h, 0Eh, 0, 11h, 0, 50h, 0F6h, 0, 1
seg002:33BC                 db 12h, 40h, 4Fh, 0FFh, 0Fh, 0, 12h, 1Ch, 5Fh, 0FFh, 0Ah dup(0)
seg002:33BC                 db 11h, 1Fh, 51h, 0D2h, 0Eh, 0, 11h, 0, 50h, 0D3h, 0, 1
seg002:33BC                 db 13h, 40h, 4Fh, 0FFh, 0Fh, 0, 13h, 1Ch, 5Fh, 0FFh, 0Ah dup(0)
seg002:33BC                 db 11h, 1Eh, 51h, 0F2h, 0Eh, 0, 11h, 0, 50h, 0F9h, 0, 1
seg002:33BC                 db 11h, 0, 4Fh, 0FFh, 0Fh, 0, 11h, 1Ch, 5Fh, 0FFh, 0Ah dup(0)
seg002:33BC                 db 11h, 1Fh, 50h, 0D2h, 0Eh, 0, 11h, 0, 51h, 0D3h, 0, 1
seg002:33BC                 db 10h, 93h, 4Fh, 0FFh, 0Fh, 3, 12h, 17h, 5Fh, 0FFh, 0
seg002:33BC                 db 2, 8 dup(0), 0D1h, 1Eh, 42h, 0F3h, 0Eh, 4, 0D1h, 0
seg002:33BC                 db 40h, 0F4h, 0, 1, 0D2h, 7, 4Fh, 0FFh, 0Fh, 3, 0D1h, 1Ch
seg002:33BC                 db 4Fh, 0FFh, 0, 2, 0Ah dup(0), 2 dup(0FFh), 0
seg002:36B9                 db 2 dup(0), 26h, 0DFh, 0FFh, 0, 2 dup(1), 1Ch, 0F6h, 0FFh
seg002:36B9                 db 0, 2 dup(1), 0, 0B5h, 0F5h, 0Ah dup(0), 10h, 29h, 8Fh
seg002:36B9                 db 0DFh, 0, 1, 10h, 29h, 0A1h, 0D2h, 2 dup(0), 12h, 29h
seg002:36B9                 db 0D1h, 0D2h, 2 dup(0), 10h, 6, 92h, 0D2h, 9 dup(0), 30h
seg002:36B9                 db 11h, 0, 0F4h, 0F6h, 7, 0, 12h, 0, 0FCh, 0FDh, 2 dup(0)
seg002:36B9                 db 12h, 1Eh, 0FEh, 0FFh, 7, 0, 11h, 0, 0FCh, 0FFh, 0Ah dup(0)
seg002:36B9                 db 31h, 1Eh, 4Fh, 0FFh, 0Eh, 0, 31h, 1Eh, 4Fh, 0FFh, 2 dup(0)
seg002:36B9                 db 31h, 13h, 40h, 0F3h, 0Fh, 1, 0F1h, 3, 40h, 0F3h, 0Ah dup(0)
seg002:36B9                 db 31h, 1Eh, 2Fh, 0FFh, 0Eh, 0, 31h, 1Eh, 2Fh, 0FFh, 2 dup(0)
seg002:36B9                 db 31h, 13h, 20h, 0F0h, 0Fh, 1, 0F1h, 3, 20h, 0F4h, 0Ah dup(0)
seg002:36B9                 db 31h, 1Eh, 4Fh, 0FFh, 0Eh, 0, 31h, 1Eh, 4Fh, 0FFh, 2 dup(0)
seg002:36B9                 db 31h, 13h, 40h, 0F3h, 0Fh, 1, 0F0h, 1, 40h, 0F3h, 0Bh dup(0)
seg002:36B9                 db 7, 4Fh, 0FFh, 6, 2 dup(0), 21h, 4Fh, 0FFh, 0, 1, 2
seg002:36B9                 db 13h, 44h, 0C6h, 7, 2, 1, 8, 44h, 0C6h, 0Ah dup(0), 50h
seg002:36B9                 db 17h, 7Fh, 0FFh, 0, 1, 50h, 45h, 7Fh, 0FFh, 0, 4, 50h
seg002:36B9                 db 52h, 80h, 0FFh, 1, 4, 0D1h, 1, 71h, 0FFh, 0Ah dup(0)
seg002:36B9                 db 11h, 12h, 4Fh, 0FFh, 0, 4, 11h, 57h, 4Fh, 0FFh, 0, 4
seg002:36B9                 db 11h, 4Bh, 42h, 0F2h, 1, 2, 11h, 3, 41h, 0F3h, 0Ah dup(0)
seg002:36B9                 db 0C0h, 0, 5Fh, 0FFh, 2 dup(0), 0C0h, 26h, 4Fh, 0FFh
seg002:36B9                 db 0, 5, 0C0h, 13h, 40h, 0F0h, 1, 2, 31h, 0, 51h, 0F4h
seg002:36B9                 db 0Ah dup(0), 12h, 0C0h, 0FFh, 0FBh, 1, 0, 12h, 0C0h
seg002:36B9                 db 0FFh, 0FDh, 0, 2, 12h, 0C0h, 0FCh, 0FDh, 1, 3, 11h
seg002:36B9                 db 0, 0C4h, 69h, 0, 4, 8 dup(0), 1, 1Dh, 7Fh, 0FFh, 0Eh
seg002:36B9                 db 2, 1, 1Ch, 55h, 0F9h, 0, 2 dup(1), 10h, 72h, 0EFh, 0Eh
seg002:36B9                 db 2 dup(1), 4, 82h, 0FCh, 0Ah dup(0), 1, 1Ah, 0F1h, 0FFh
seg002:36B9                 db 0Eh, 0, 2, 1, 73h, 0FFh, 4 dup(0), 2 dup(0FFh), 0Fh
seg002:36B9                 db 1, 80h, 0, 7Fh, 0FFh, 0, 2, 8 dup(0), 1, 21h, 0F1h
seg002:36B9                 db 0FFh, 0Eh, 0, 2, 0, 74h, 0FFh, 2 dup(0), 1, 9Eh, 2 dup(0FFh)
seg002:36B9                 db 0Fh, 1, 80h, 0, 57h, 0F7h, 0, 2, 8 dup(0), 0D0h, 19h
seg002:36B9                 db 2 dup(0FFh), 6, 2, 10h, 1Ch, 4Eh, 0FDh, 0, 2, 12h, 14h
seg002:36B9                 db 40h, 0D7h, 7, 1, 51h, 3, 40h, 0D8h, 0Ah dup(0), 1, 1Dh
seg002:36B9                 db 0F1h, 0FFh, 0Eh, 0, 2, 0, 74h, 0FFh, 3 dup(0), 5Eh
seg002:36B9                 db 2 dup(0FFh), 0Fh, 1, 80h, 0, 57h, 0F7h, 0, 2, 8 dup(0)
seg002:36B9                 db 1, 26h, 7Fh, 0FFh, 0Eh, 2, 1, 1Eh, 74h, 0FFh, 0, 2 dup(1)
seg002:36B9                 db 14h, 72h, 0FFh, 0Eh, 2 dup(1), 0, 72h, 0FFh, 0Ah dup(0)
seg002:36B9                 db 1, 1Dh, 7Fh, 0DFh, 0Eh, 2, 1, 5Ch, 74h, 0F9h, 0, 2 dup(1)
seg002:36B9                 db 12h, 70h, 0EFh, 0Eh, 1, 2, 3, 72h, 0FCh, 0Ah dup(0)
seg002:36B9                 db 1, 28h, 7Fh, 0FFh, 0Eh, 2, 1, 28h, 55h, 0FFh, 0, 1
seg002:36B9                 db 3, 53h, 72h, 0E7h, 0Eh, 3 dup(1), 81h, 0F8h, 0Ah dup(0)
seg002:36B9                 db 0D1h, 3Ah, 53h, 87h, 7, 3, 11h, 1Fh, 40h, 87h, 0, 2
seg002:36B9                 db 11h, 17h, 40h, 0A7h, 6, 1, 51h, 2, 40h, 0A8h, 0Ah dup(0)
seg002:36B9                 db 0D1h, 3Ah, 53h, 87h, 7, 3, 11h, 1Fh, 40h, 87h, 0, 2
seg002:36B9                 db 11h, 17h, 40h, 0A7h, 6, 1, 52h, 2, 40h, 0A8h, 0Ah dup(0)
seg002:36B9                 db 80h, 28h, 2 dup(0FFh), 0Fh, 0, 80h, 33h, 2 dup(0FFh)
seg002:36B9                 db 2 dup(0), 41h, 48h, 0F2h, 0F9h, 0Eh, 0, 92h, 0, 52h
seg002:36B9                 db 0F9h, 0Ah dup(0), 80h, 28h, 2 dup(0FFh), 0Fh, 0, 80h
seg002:36B9                 db 33h, 2 dup(0FFh), 2 dup(0), 41h, 8, 0F2h, 0F9h, 0Eh
seg002:36B9                 db 0, 92h, 0, 52h, 0F9h, 0Ah dup(0), 10h, 21h, 5Fh, 0FFh
seg002:36B9                 db 0Eh, 0, 10h, 21h, 5Fh, 0FFh, 0, 1, 11h, 0Fh
seg002:39A2                 db 50h, 0F0h, 0Fh, 0, 11h, 0, 50h, 0FFh, 0Ah dup(0), 1
seg002:39A2                 db 1Ch, 0F1h, 0FFh, 0Eh, 0, 2, 5, 73h, 0FFh, 3 dup(0)
seg002:39A2                 db 40h, 2 dup(0FFh), 0Fh, 1, 80h, 0, 7Fh, 0FFh, 0, 2, 8 dup(0)
seg002:39A2                 db 10h, 21h, 5Fh, 0FFh, 0Eh, 0, 10h, 21h, 5Fh, 0FFh, 0
seg002:39A2                 db 1, 11h, 0Fh, 50h, 0F0h, 0Fh, 0, 11h, 0, 50h, 0FFh, 0Ah dup(0)
seg002:39A2                 db 11h, 52h, 5Fh, 0FDh, 0Eh, 0, 11h, 61h, 5Fh, 0FDh, 2 dup(0)
seg002:39A2                 db 12h, 97h, 50h, 0EBh, 0Fh, 1, 10h, 2, 50h, 0F8h, 0Ah dup(0)
seg002:39A2                 db 2, 5Eh, 9Fh, 0FFh, 1, 0, 2, 53h, 72h, 0FDh, 2 dup(0)
seg002:39A2                 db 1, 57h, 73h, 0CCh, 2 dup(0), 2 dup(2), 72h, 0BCh, 0Ah dup(0)
seg002:39A2                 db 1, 40h, 5Fh, 0BFh, 4, 3, 1, 61h, 5Fh, 0FFh, 0, 2, 1
seg002:39A2                 db 4Dh, 52h, 0F0h, 5, 2, 11h, 0, 50h, 0FFh, 0Ah dup(0)
seg002:39A2                 db 1, 52h, 6Fh, 0CDh, 0, 2, 1, 66h, 6Fh, 0CDh, 0, 2 dup(1)
seg002:39A2                 db 48h, 62h, 0CFh, 1, 2, 1, 2, 62h, 0CFh, 0Ah dup(0), 1
seg002:39A2                 db 53h, 6Fh, 0FEh, 2 dup(0), 1, 48h, 6Dh, 0FEh, 2 dup(0)
seg002:39A2                 db 1, 53h, 61h, 0FCh, 2 dup(1), 41h, 0, 61h, 0FCh, 0Ah dup(0)
seg002:39A2                 db 2, 69h, 5Fh, 0BFh, 4, 0, 1, 9Bh, 5Fh, 0FFh, 0, 2, 1
seg002:39A2                 db 4Fh, 61h, 0FFh, 5, 1, 11h, 0, 41h, 0FFh, 0Ah dup(0)
seg002:39A2                 db 81h, 40h, 2 dup(0FFh), 2 dup(0), 81h, 4Bh, 2 dup(0FFh)
seg002:39A2                 db 0, 1, 0C1h, 5Bh, 92h, 0F6h, 1, 3, 0C1h, 0, 92h, 0F7h
seg002:39A2                 db 0Bh dup(0), 9Eh, 3Ch, 0FFh, 6, 2 dup(2), 9Eh, 3Ch, 0FEh
seg002:39A2                 db 0, 2 dup(1), 9Eh, 2, 0FFh, 7, 4, 2, 0, 62h, 0FFh, 0Ah dup(0)
seg002:39A2                 db 91h, 4Eh, 5Fh, 0FDh, 0Eh, 2, 91h, 53h, 5Fh, 0FDh, 2 dup(0)
seg002:39A2                 db 92h, 55h, 50h, 0EBh, 0Fh, 1, 91h, 0, 50h, 0F8h, 0Ah dup(0)
seg002:39A2                 db 10h, 8, 5Fh, 0FFh, 0Eh, 6, 0, 29h, 5Fh, 0FFh, 0, 2 dup(6)
seg002:39A2                 db 0C0h, 2 dup(0FFh), 0Fh, 6, 1, 5, 0F2h, 0F6h, 0, 6, 8 dup(0)
seg002:39A2                 db 10h, 1, 2 dup(0FFh), 0Eh, 0, 10h, 0, 2 dup(0FFh), 0
seg002:39A2                 db 3, 12h, 0, 0FFh, 0E2h, 0Eh, 0, 10h, 0, 90h, 0F9h, 0
seg002:39A2                 db 3, 8 dup(0), 20h, 21h, 7Fh, 0BFh, 4, 7, 20h, 21h, 7Fh
seg002:39A2                 db 0BFh, 0, 6, 21h, 13h, 73h, 0F9h, 2 dup(5), 0E2h, 1
seg002:39A2                 db 73h, 0F9h, 0Ah dup(0), 20h, 1Eh, 9Fh, 0BFh, 0Eh, 7
seg002:39A2                 db 20h, 1Eh, 9Fh, 0BFh, 0, 6, 21h, 13h, 93h, 0F9h, 0Fh
seg002:39A2                 db 5, 0E2h, 1, 93h, 0F9h, 0Ah dup(0), 10h, 1Eh, 4Fh, 0FFh
seg002:39A2                 db 0Eh, 0, 10h, 5, 4Fh, 0FFh, 0, 7, 1, 5Eh, 40h, 0F7h
seg002:39A2                 db 0Fh, 7, 11h, 0, 41h, 0F7h, 0Ah dup(0), 2, 62h, 6Ch
seg002:39A2                 db 0BFh, 4, 3, 2, 5Bh, 6Ch, 0FFh, 0, 2 dup(2), 54h, 63h
seg002:39A2                 db 0FAh, 5, 2, 11h, 40h, 60h, 0FAh, 0Ah dup(0), 10h, 1Eh
seg002:39A2                 db 2 dup(0FFh), 0Eh, 0, 10h, 1Eh, 2 dup(0FFh), 0, 7, 1
seg002:39A2                 db 5Eh, 0F0h, 0F7h, 0Fh, 7, 11h, 0, 41h, 0F7h, 0Ah dup(0)
seg002:39A2                 db 10h, 12h, 2 dup(0FFh), 0Eh, 2, 10h, 11h, 0FFh, 0A9h
seg002:39A2                 db 0, 2, 1, 44h, 0F3h, 0E7h, 0Fh, 1, 11h, 0, 0F0h, 0C6h
seg002:39A2                 db 0Ah dup(0), 20h, 8, 2 dup(0FFh), 4, 2, 20h, 1Ch, 2 dup(0FFh)
seg002:39A2                 db 0, 2, 21h, 18h, 0F2h, 0F5h, 5, 2, 0E1h, 0, 0F2h, 0F5h
seg002:39A2                 db 0Ah dup(0), 20h, 1Eh, 5Fh, 0FFh, 4, 2, 20h, 1Eh, 5Fh
seg002:39A2                 db 0FFh, 0, 2, 22h, 5Eh, 52h, 0F5h, 5, 2, 0E1h, 0, 52h
seg002:39A2                 db 0F5h, 0Ah dup(0), 1, 19h, 53h, 0F5h, 0Ah, 1, 3, 12h
seg002:39A2                 db 53h, 0E5h, 2 dup(0), 1, 8, 53h, 0E5h, 0Bh, 1, 81h, 0
seg002:39A2                 db 53h, 0F5h, 0Ah dup(0), 11h, 1Ch, 3Fh, 0FFh, 2 dup(0)
seg002:39A2                 db 11h, 1Ch, 2 dup(0FFh), 0, 3, 12h, 1Ch, 32h, 0F5h, 0
seg002:39A2                 db 2, 91h, 0, 31h, 0E5h, 0
seg002:3C8B                 db 9 dup(0), 12h, 6Bh, 0FFh, 0FBh, 0, 2, 12h, 0ABh, 0FFh
seg002:3C8B                 db 0FBh, 0, 3, 12h, 92h, 42h, 0F5h, 0, 2, 91h, 0, 41h
seg002:3C8B                 db 0F5h, 0Ah dup(0), 31h, 1Eh, 4Fh, 0FFh, 0Eh, 0, 31h
seg002:3C8B                 db 1Eh, 4Fh, 0FFh, 2 dup(0), 31h, 13h, 40h, 0F3h, 0Fh
seg002:3C8B                 db 1, 0F1h, 3, 40h, 0F3h, 0Ah dup(0), 2, 28h, 5Fh, 0EFh
seg002:3C8B                 db 0Eh, 0, 1, 1Ch, 5Fh, 0EFh, 2 dup(0), 1, 16h, 51h, 0E9h
seg002:3C8B                 db 0Fh, 2, 1, 0, 51h, 0E9h, 0Ah dup(0), 11h, 21h, 31h
seg002:3C8B                 db 0F1h, 0Eh, 0, 0D2h, 0, 32h, 0F1h, 0, 1, 51h, 25h, 3Fh
seg002:3C8B                 db 0FFh, 0Fh, 0, 0D1h, 0, 14h, 0FFh, 0Bh dup(0), 21h, 0CFh
seg002:3C8B                 db 0EDh, 0Eh, 2 dup(1), 21h, 0FCh, 0EDh, 2 dup(0), 6, 21h
seg002:3C8B                 db 0F5h, 0E5h, 0Fh, 2 dup(2), 3, 0C4h, 0E4h, 0Ch dup(0)
seg002:3C8B                 db 6Fh, 0EFh, 0Eh, 1, 0, 29h, 6Fh, 0EFh, 2 dup(0), 2, 1Eh
seg002:3C8B                 db 63h, 0E2h, 0Fh, 2, 2 dup(1), 60h, 0E5h, 0Ah dup(0)
seg002:3C8B                 db 5, 21h, 0CFh, 0EFh, 0Eh, 0, 1, 21h, 0FFh, 0EFh, 2 dup(0)
seg002:3C8B                 db 1, 48h, 0F4h, 0E7h, 0Fh, 2 dup(1), 0, 0C3h, 0E5h, 0Bh dup(0)
seg002:3C8B                 db 1Ch, 0CFh, 0EEh, 0Eh, 2 dup(0), 1Ch, 0FFh, 0EEh, 0
seg002:3C8B                 db 2, 1, 12h, 0F4h, 0E4h, 0Fh, 2, 1, 0, 2 dup(0F4h), 0Ah dup(0)
seg002:3C8B                 db 10h, 1, 2 dup(0FFh), 0Ah, 0, 10h, 1, 2 dup(0FFh), 2 dup(0)
seg002:3C8B                 db 11h, 5Eh, 0F1h, 0F2h, 0Ah, 3, 0D1h, 0, 0F2h, 0F4h, 0Ah dup(0)
seg002:3C8B                 db 12h, 1Fh, 21h, 0F5h, 0Eh, 4, 0D1h, 3, 22h, 0F5h, 0
seg002:3C8B                 db 1, 52h, 0, 3, 0F5h, 0Fh, 7, 0D1h, 0, 22h, 0F5h, 0, 4
seg002:3C8B                 db 8 dup(0), 14h, 0, 2 dup(0FFh), 0Eh, 2, 0D2h, 8, 0FFh
seg002:3C8B                 db 0FDh, 0, 1, 50h, 0C0h, 0F4h, 0F5h, 0Fh, 2, 0D1h, 0
seg002:3C8B                 db 0F3h, 0F5h, 0Ah dup(0), 0D1h, 1Dh, 42h, 0F3h, 0Eh, 4
seg002:3C8B                 db 0D1h, 0, 40h, 0F4h, 0, 1, 0D2h, 3, 4Fh, 0FFh, 0Fh, 3
seg002:3C8B                 db 0D1h, 1Dh, 4Fh, 0FFh, 0, 2, 8 dup(0), 81h, 48h, 0FDh
seg002:3C8B                 db 0FEh, 0Eh, 4, 81h, 5Eh, 2 dup(0FEh), 0, 3, 82h, 0Dh
seg002:3C8B                 db 2 dup(0F4h), 0Fh, 1, 0C1h, 5, 0B4h, 0F6h, 0Ah dup(0)
seg002:3C8B                 db 83h, 66h, 9Fh, 0FFh, 0Eh, 2, 0C3h, 53h, 9Fh, 0FFh, 2 dup(0)
seg002:3C8B                 db 83h, 51h, 95h, 0F5h, 0Fh, 0, 0C1h, 0, 94h, 0F5h, 0Bh dup(0)
seg002:3C8B                 db 32h, 0F4h, 94h, 1, 0, 3, 16h, 0F4h, 7, 0, 4, 2, 25h
seg002:3C8B                 db 0F3h, 6, 2 dup(0), 0C0h, 0, 0F3h, 5, 0, 3, 8 dup(0)
seg002:3C8B                 db 2 dup(80h), 2 dup(0FFh), 0Fh, 2, 83h, 18h, 2 dup(0FFh)
seg002:3C8B                 db 0, 3, 82h, 92h, 0F3h, 0F4h, 0Eh, 1, 81h, 0, 0F4h, 0F5h
seg002:3C8B                 db 0Ah dup(0), 80h, 0, 2 dup(0FFh), 1, 0, 83h, 52h, 0FFh
seg002:3C8B                 db 26h, 0, 2, 81h, 1Ch, 0F5h, 0F6h, 2 dup(0), 81h, 0, 0F4h
seg002:3C8B                 db 0F5h, 0Ah dup(0), 31h, 26h, 50h, 0FFh, 0Eh, 4, 31h
seg002:3C8B                 db 0, 40h, 0FFh, 0, 5, 30h, 19h, 2 dup(0FFh), 0Fh, 2, 0B1h
seg002:3C8B                 db 0, 55h, 0FFh, 0, 5, 8 dup(0), 31h, 1Ch, 0F2h, 0FFh
seg002:3C8B                 db 0Eh, 4, 31h, 3, 42h, 0FFh, 0, 5, 30h, 1Ch, 0F2h, 0FFh
seg002:3C8B                 db 0Fh, 2, 0B2h, 0, 52h, 0FFh, 0Ah dup(0), 11h, 61h, 5Fh
seg002:3C8B                 db 0FFh, 0Eh, 0, 11h, 61h, 5Fh, 0FFh, 0, 1, 11h, 0Bh, 50h
seg002:3C8B                 db 0F0h, 0Fh, 0, 11h, 0, 50h, 0FFh, 0Ch dup(0), 0Fh, 0FFh
seg002:3C8B                 db 4 dup(0), 0Fh, 0FFh, 2 dup(0), 2, 0, 5, 0F5h, 1, 0
seg002:3C8B                 db 2, 0, 2 dup(0F5h), 0Ah dup(0), 0Dh, 74h, 0F2h, 0F3h
seg002:3C8B                 db 2 dup(0), 0Ch, 5Eh, 0F2h, 0F5h, 0, 1, 6, 0C8h, 0F2h
seg002:3C8B                 db 0F5h, 0, 1, 2, 0, 0F4h, 0D6h, 0Ch dup(0), 0FFh, 0EFh
seg002:3C8B                 db 3 dup(0), 0C0h, 0FFh, 0EFh, 2 dup(0), 5, 14h, 0F4h
seg002:3C8B                 db 0E6h, 1, 2, 82h, 0, 0F6h, 0E5h, 0Ah dup(0), 1, 3, 2 dup(0FFh)
seg002:3C8B                 db 1, 0, 2, 13h, 0F6h, 0FFh, 2 dup(0), 1, 3, 0F8h, 0F5h
seg002:3C8B                 db 1, 0, 81h
seg002:3F87                 db 0, 0D5h, 0F5h, 0Bh dup(0), 40h, 2 dup(0FFh), 3 dup(0)
seg002:3F87                 db 0C0h, 0FCh, 0FFh, 0, 7, 2 dup(0), 0FCh, 53h, 1, 5, 2 dup(0)
seg002:3F87                 db 0C4h, 26h, 0Ch dup(0), 2 dup(0FFh), 4 dup(0), 0FCh
seg002:3F87                 db 0FFh, 0, 2, 2 dup(0), 0FCh, 53h, 1, 2, 3, 0, 0C4h, 26h
seg002:3F87                 db 0Ah dup(0), 10h, 40h, 2 dup(0FFh), 1, 3, 10h, 40h, 2 dup(0FFh)
seg002:3F87                 db 0, 1, 10h, 40h, 2 dup(0F9h), 2 dup(1), 11h, 0, 94h
seg002:3F87                 db 0F5h, 0, 6, 9 dup(0), 14h, 0F0h, 0FFh, 0Eh, 2 dup(0)
seg002:3F87                 db 2, 0F0h, 0FFh, 3 dup(0), 2, 0F0h, 0FFh, 0Eh, 2 dup(0)
seg002:3F87                 db 5, 3Fh, 0FFh, 0Ah dup(0), 31h, 1Eh, 42h, 0FFh, 0Fh
seg002:3F87                 db 0, 31h, 0D3h, 42h, 0FFh, 0, 2, 30h, 13h, 32h, 0FFh
seg002:3F87                 db 0Fh, 2, 28h, 8, 4Dh, 0FFh, 0Ah dup(0), 4, 5, 49h, 0FFh
seg002:3F87                 db 0Eh, 0, 2, 45h, 99h, 0FFh, 2 dup(0), 2, 5, 96h, 0FFh
seg002:3F87                 db 0Eh, 2 dup(1), 5, 42h, 9Fh, 0Ch dup(0), 0F0h, 0F1h
seg002:3F87                 db 0Eh, 2 dup(0), 2, 0F0h, 0F1h, 3 dup(0), 2, 0F0h, 0F1h
seg002:3F87                 db 0Eh, 2 dup(0), 8, 22h, 0F2h, 0Ah dup(0), 0C0h, 0, 0Dh
seg002:3F87                 db 0FFh, 0Fh, 0, 0C0h, 0, 0Eh, 0CFh, 0, 1, 0C3h, 0, 0Dh
seg002:3F87                 db 0FFh, 0Fh, 1, 0C3h, 0, 42h, 0FBh, 0Ah dup(0), 0Fh, 12h
seg002:3F87                 db 0CCh, 0FFh, 1, 5, 0Fh, 0ECh, 0FCh, 0FFh, 0, 5, 7, 97h
seg002:3F87                 db 0FCh, 11h, 0, 5, 6, 0, 0FCh, 5, 0Ah dup(0), 2, 1Ch
seg002:3F87                 db 9Fh, 0FFh, 0Eh, 0, 2, 21h, 1Fh, 0FFh, 4 dup(0), 91h
seg002:3F87                 db 0F1h, 0Eh, 0, 1, 0, 2 dup(32h), 9 dup(0), 0D0h, 2 dup(0)
seg002:3F87                 db 0F0h, 0F1h, 0Eh, 2 dup(0), 8, 0F2h, 0F1h, 3 dup(0)
seg002:3F87                 db 8, 70h, 0F1h, 0Eh, 2 dup(0), 0Dh, 72h, 0F2h, 0Bh dup(0)
seg002:3F87                 db 40h, 2 dup(0FFh), 3 dup(0), 0C0h, 0FCh, 0FFh, 0, 6
seg002:3F87                 db 2 dup(0), 0FCh, 53h, 1, 4, 2 dup(0), 0C4h, 26h, 0Ch dup(0)
seg002:3F87                 db 0Bh, 0, 0A8h, 0D6h, 4Ch, 45h, 3 dup(0), 6, 6 dup(0)
seg002:3F87                 db 0Bh, 0, 0AAh, 0D2h, 0C8h, 0B7h, 3 dup(0), 6, 4 dup(0)
seg002:3F87                 db 26h, 3 dup(0), 0F0h, 0FAh, 0F0h, 0B7h, 2 dup(3), 0Eh
seg002:3F87                 db 6, 4 dup(0), 10h, 0C2h, 7, 23h, 0F7h, 0E0h, 0F5h, 41h
seg002:3F87                 db 2 dup(2), 82h, 7, 4 dup(0), 0F2h, 0F1h, 0Ah, 38h, 88h
seg002:3F87                 db 0ADh, 0F4h, 88h, 3 dup(2), 7, 4 dup(0), 0D0h, 0C2h
seg002:3F87                 db 81h, 23h, 0A6h, 0E0h, 0F6h, 41h, 2 dup(2), 81h, 7, 4 dup(0)
seg002:3F87                 db 40h, 0C2h, 0, 23h, 0F5h, 0E0h, 38h, 41h, 0, 2, 5, 8
seg002:3F87                 db 4 dup(0), 1, 0C2h, 3, 23h, 0B8h, 0E0h, 0B5h, 41h, 1
seg002:3F87                 db 2, 7Dh, 0Ah, 4 dup(0), 40h, 0C2h, 0, 23h, 0F5h, 0E0h
seg002:3F87                 db 38h, 41h, 0, 2, 0F1h, 8, 4 dup(0), 1, 0B3h, 8, 0C1h
seg002:3F87                 db 88h, 18h, 0A5h, 50h, 1, 0, 0A3h, 0Ah, 5 dup(0), 0C2h
seg002:3F87                 db 0, 23h, 0C6h, 0E0h, 98h, 41h, 0, 2, 83h, 8, 4 dup(0)
seg002:3F87                 db 1, 0B3h, 9, 0C1h, 86h, 18h, 0A5h, 50h, 1, 0, 0A3h, 0Ah
seg002:3F87                 db 5 dup(0), 0C2h, 0, 23h, 0C6h, 0E0h, 98h, 41h, 0, 2
seg002:3F87                 db 3, 8, 5 dup(0), 0C2h, 0, 23h, 0C6h, 0E0h, 98h, 41h
seg002:3F87                 db 0, 2, 5, 8, 4 dup(0), 4, 0C2h, 0Ch, 23h, 0C5h, 0E0h
seg002:3F87                 db 0F6h, 41h, 0, 2, 5, 9, 4 dup(0), 1, 0C2h, 0, 23h, 0C6h
seg002:3F87                 db 0E0h, 98h, 41h, 0, 2, 5, 8, 4 dup(0), 1, 0C2h, 82h
seg002:3F87                 db 23h, 0F6h, 0E0h, 0D5h, 41h, 1, 2, 83h, 0Ah, 4 dup(0)
seg002:3F87                 db 3, 0BFh, 9, 0FFh, 0E3h, 0D0h, 97h, 50h, 2 dup(0), 0BBh
seg002:3F87                 db 0Ah, 4 dup(0), 0Eh, 0BFh, 7, 0FFh, 0B5h, 0D1h, 15h
seg002:3F87                 db 50h, 1, 0, 0BBh, 0Ah, 4 dup(0), 1, 0BFh, 7, 0C1h, 77h
seg002:3F87                 db 0D1h, 73h, 50h, 1, 0, 0BBh, 0Ah, 4 dup(0), 0Eh, 0F1h
seg002:3F87                 db 0C7h, 38h, 95h, 0ADh, 78h, 8Eh, 0, 2 dup(2), 9, 4 dup(0)
seg002:3F87                 db 1, 0BFh, 0, 0FFh, 0F8h, 0D2h, 0B6h, 50h, 1, 0, 0BAh
seg002:3F87                 db 0Ah, 4 dup(0), 0Ah, 0C2h, 0C7h, 23h, 95h, 0E0h, 78h
seg002:3F87                 db 41h
seg002:427C                 db 0, 2, 7Ch, 9, 4 dup(0), 1, 0BFh, 7, 0C1h, 0F9h, 0D4h
seg002:427C                 db 0B5h, 50h, 2 dup(0), 0BBh, 9, 4 dup(0), 0D1h, 0C2h
seg002:427C                 db 5, 23h, 0E7h, 0E0h, 65h, 41h, 1, 2, 9Dh, 9, 4 dup(0)
seg002:427C                 db 1, 0FEh, 0, 38h, 0E7h, 0A9h, 94h, 82h, 0, 2, 3, 8, 4 dup(0)
seg002:427C                 db 1, 0BFh, 0, 0FFh, 0E7h, 0D8h, 94h, 50h, 2 dup(0), 0BBh
seg002:427C                 db 8, 4 dup(0), 1, 0BFh, 0, 0FFh, 96h, 0D8h, 67h, 50h
seg002:427C                 db 2 dup(0), 0BAh, 8, 4 dup(0), 1, 0BFh, 0, 0FFh, 0B4h
seg002:427C                 db 0DAh, 26h, 50h, 2 dup(0), 0BAh, 8, 4 dup(0), 1, 0BFh
seg002:427C                 db 0, 0C1h, 0B4h, 0DBh, 26h, 50h, 2 dup(0), 0BAh, 8, 4 dup(0)
seg002:427C                 db 95h, 13h, 81h, 0, 0E7h, 95h, 1, 65h, 2 dup(0), 0Eh
seg002:427C                 db 6, 4 dup(0), 95h, 13h, 81h, 0, 0E7h, 95h, 1, 65h, 2 dup(0)
seg002:427C                 db 0Eh, 6, 4 dup(0), 10h, 0BFh, 0, 0C1h, 96h, 0DEh, 67h
seg002:427C                 db 50h, 2 dup(0), 0BAh, 9, 4 dup(0), 11h, 0BFh, 0, 0FFh
seg002:427C                 db 96h, 0DFh, 67h, 50h, 2 dup(0), 0BAh, 9, 5 dup(0), 0BFh
seg002:427C                 db 0Eh, 0C1h, 58h, 0D0h, 0DCh, 50h, 2, 0, 0BAh, 7, 5 dup(0)
seg002:427C                 db 0BFh, 0Eh, 0FFh, 5Ah, 0D2h, 0D6h, 50h, 2, 0, 0BAh, 7
seg002:427C                 db 4 dup(0), 52h, 0BFh, 7, 0C1h, 49h, 0D3h, 4, 50h, 3
seg002:427C                 db 0, 0BBh, 8, 4 dup(0), 52h, 0BFh, 7, 0C1h, 41h, 0D4h
seg002:427C                 db 2, 50h, 3, 0, 0BBh, 8, 5 dup(0), 0BFh, 0Eh, 0FFh, 5Ah
seg002:427C                 db 0D5h, 0D6h, 50h, 1, 0, 0BAh, 7, 4 dup(0), 10h, 0BFh
seg002:427C                 db 0Eh, 0C1h, 53h, 0D6h, 9Fh, 50h, 1, 0, 0BAh, 7, 4 dup(0)
seg002:427C                 db 11h, 0FEh, 0, 38h, 0F5h, 0A9h, 75h, 80h, 0, 2 dup(2)
seg002:427C                 db 8, 4 dup(0), 4, 0C2h, 0, 23h, 0F8h, 0E0h, 0B6h, 41h
seg002:427C                 db 1, 2, 3, 8, 4 dup(0), 4, 0C2h, 0, 23h, 0F8h, 0E0h, 0B7h
seg002:427C                 db 41h, 1, 2, 3, 8, 4 dup(0), 1, 0BFh, 0Bh, 0C1h, 5Eh
seg002:427C                 db 0D8h, 0DCh, 50h, 1, 0, 0BAh, 7, 5 dup(0), 0BFh, 7, 0C1h
seg002:427C                 db 5Ch, 0DAh, 0DCh, 50h, 1, 0, 0BAh, 7, 4 dup(0), 0C5h
seg002:427C                 db 0D5h, 4Fh, 0, 0F2h, 0F4h, 60h, 7Ah, 2 dup(0), 8, 6
seg002:427C                 db 4 dup(0), 0C5h, 0D5h, 4Fh, 0, 2 dup(0F2h), 60h, 72h
seg002:427C                 db 2 dup(0), 8, 6, 4 dup(0), 80h, 81h, 82h, 83h, 84h, 0
seg002:427C                 db 8Fh, 87h, 8Fh, 89h, 8Fh, 8Bh, 2 dup(8Fh), 8Eh, 8Fh
seg002:427C                 db 90h, 2 dup(0), 93h, 0, 0A0h, 3 dup(0), 99h, 9Ah, 9Bh
seg002:427C                 db 9Ch, 9Dh, 2 dup(8Fh), 0A0h, 0A1h, 0A2h, 0A3h, 0A4h
seg002:427C                 db 0A5h, 0A6h, 0, 0A8h, 7 dup(0)
seg002:4434 aC047C0CCc750Oo db '/$C<<<0<4<7<<@<C<<<<<0<<<C>CC<<750<<OO<<[<5<<OO',0
seg002:4464 a00000000000000 db '0000000000000000',0
seg002:4475                 db 62h dup(0), 3 dup(2), 5 dup(0), 20h, 21h, 22h, 20h
seg002:4475                 db 21h, 22h, 30h, 34h, 32h, 35h, 31h, 58h dup(0), 0Bh dup(0FFh)
seg002:4475                 db 21h dup(0), 0Bh dup(0FFh), 0C0h, 0C1h, 0C2h, 0C0h, 0C1h
seg002:4475                 db 0C2h, 85h dup(0), 10h, 8, 4, 2, 1, 6, 7, 2 dup(8), 7
seg002:4475                 db 8, 0Ah, 9, 0Dh, 0A6h, 0A7h, 2 dup(0A8h), 0A7h, 2 dup(0)
seg002:4475                 db 0C1h, 0FFh, 0F0h, 0FFh, 0F8h, 0FFh, 0FAh, 0FFh, 0FCh
seg002:4475                 db 0FFh, 0FDh, 0FFh, 0FEh, 3 dup(0FFh), 2 dup(0), 2, 0
seg002:4475                 db 4, 0, 5, 0, 6, 0, 7, 0, 8, 0, 9, 0, 0Ah, 0, 0Ch, 0
seg002:4475                 db 0Ah, 7, 40h, 88h, 1Dh, 76h, 1Dh, 0E9h, 1Dh
seg002:4646 a012345         db ' !"#$%()*+,-012345',0
seg002:4659                 align 8
seg002:4659 seg002          ends
seg002:4659
seg003:0000 ; ===========================================================================
