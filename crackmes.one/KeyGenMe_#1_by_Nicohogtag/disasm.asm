  loc_00402520: push ebp
  loc_00402521: mov ebp, esp
  loc_00402523: sub esp, 0000000Ch
  loc_00402526: push 00401136h ; undef 'Ignore this
  loc_0040252B: mov eax, fs:[00000000h]
  loc_00402531: push eax
  loc_00402532: mov fs:[00000000h], esp
  loc_00402539: sub esp, 000001ACh
  loc_0040253F: push ebx
  loc_00402540: push esi
  loc_00402541: push edi
  loc_00402542: mov var_C, esp
  loc_00402545: mov var_8, 00401108h
  loc_0040254C: mov esi, arg_8
  loc_0040254F: mov eax, esi
  loc_00402551: and eax, 00000001h
  loc_00402554: mov var_4, eax
  loc_00402557: and esi, FFFFFFFEh
  loc_0040255A: push esi
  loc_0040255B: mov arg_8, esi
  loc_0040255E: mov ecx, [esi]
  loc_00402560: call [ecx+00000004h]
  loc_00402563: mov edx, [esi]
  loc_00402565: xor edi, edi
  loc_00402567: push esi
  loc_00402568: mov var_24, 0
  loc_0040256B: mov var_34, 0
  loc_0040256E: mov var_38, 0
  loc_00402571: mov var_40, 0
  loc_00402574: mov var_44, 0
  loc_00402577: mov var_54, 0
  loc_0040257A: mov var_68, 0
  loc_0040257D: mov var_78, 0
  loc_00402580: mov var_88, 0
  loc_00402586: mov var_8C, 0
  loc_0040258C: mov var_90, 0
  loc_00402592: mov var_94, 0
  loc_00402598: mov var_98, 0
  loc_0040259E: mov var_A8, 0
  loc_004025A4: mov var_B8, 0
  loc_004025AA: mov var_C8, 0
  loc_004025B0: mov var_D8, 0
  loc_004025B6: mov var_E8, 0
  loc_004025BC: mov var_F8, 0
  loc_004025C2: mov var_108, 0
  loc_004025C8: mov var_118, 0
  loc_004025CE: mov var_128, 0
  loc_004025D4: mov var_158, 0
  loc_004025DA: mov var_168, 0
  loc_004025E0: call [edx+00000304h]
  loc_004025E6: push eax
  loc_004025E7: lea eax, var_94
  loc_004025ED: push eax
  loc_004025EE: call [00401048h] ; Set %StkVar1 = %StkVar2 'Ignore this
  loc_004025F4: mov ebx, eax
  loc_004025F6: lea edx, var_8C
  loc_004025FC: push edx
  loc_004025FD: push ebx
  loc_004025FE: mov ecx, [ebx]
  loc_00402600: call [ecx+000000A0h]
  loc_00402606: cmp eax, edi
  loc_00402608: fnclex
  loc_0040260A: jge 0040261Eh
  loc_0040260C: push 000000A0h
  loc_00402611: push 00401AA8h
  loc_00402616: push ebx
  loc_00402617: push eax
  loc_00402618: call [00401034h] ; %StkVar1 = CheckObj(%StkVar2, %StkVar3, %StkVar4)
  loc_0040261E: mov eax, var_8C
  loc_00402624: push eax
  loc_00402625: call [00401014h] ; @Len(%StkVar1)
  loc_0040262B: mov ebx, [0040100Ch] ; %ecx = %S_edx_S '__vbaVarMove
  loc_00402631: lea edx, var_108
  loc_00402637: lea ecx, var_54
  loc_0040263A: mov var_100, eax
  loc_00402640: mov var_108, 00000003h
  loc_0040264A: call ebx
  loc_0040264C: lea ecx, var_8C
  loc_00402652: call [004010F0h] ; %ecx = "" '__vbaFreeStr
  loc_00402658: lea ecx, var_94
  loc_0040265E: call [004010F4h] ; %fobj '__vbaFreeObj
  loc_00402664: mov ecx, [esi]
  loc_00402666: push esi
  loc_00402667: call [ecx+00000300h]
  loc_0040266D: lea edx, var_94
  loc_00402673: push eax
  loc_00402674: push edx
  loc_00402675: call [00401048h] ; Set %StkVar1 = %StkVar2 'Ignore this
  loc_0040267B: mov ecx, [eax]
  loc_0040267D: lea edx, var_8C
  loc_00402683: push edx
  loc_00402684: push eax
  loc_00402685: mov var_13C, eax
  loc_0040268B: call [ecx+000000A0h]
  loc_00402691: cmp eax, edi
  loc_00402693: fnclex
  loc_00402695: jge 004026AFh
  loc_00402697: mov ecx, var_13C
  loc_0040269D: push 000000A0h
  loc_004026A2: push 00401AA8h
  loc_004026A7: push ecx
  loc_004026A8: push eax
  loc_004026A9: call [00401034h] ; %StkVar1 = CheckObj(%StkVar2, %StkVar3, %StkVar4)
  loc_004026AF: mov edx, var_8C
  loc_004026B5: push edx
  loc_004026B6: call [00401014h] ; @Len(%StkVar1)
  loc_004026BC: mov ecx, eax
  loc_004026BE: call [00401074h] ; %S_eax_S = %ecx '__vbaI2I4
  loc_004026C4: lea ecx, var_8C
  loc_004026CA: mov username_len, eax
  loc_004026CD: call [004010F0h] ; %ecx = "" '__vbaFreeStr
  loc_004026D3: lea ecx, var_94
  loc_004026D9: call [004010F4h] ; %fobj '__vbaFreeObj
  loc_004026DF: mov eax, [esi]
  loc_004026E1: push esi
  loc_004026E2: call [eax+00000304h]
  loc_004026E8: lea ecx, var_94
  loc_004026EE: push eax
  loc_004026EF: push ecx
  loc_004026F0: call [00401048h] ; Set %StkVar1 = %StkVar2 'Ignore this
  loc_004026F6: mov edx, [eax]
  loc_004026F8: lea ecx, var_8C
  loc_004026FE: push ecx
  loc_004026FF: push eax
  loc_00402700: mov var_13C, eax
  loc_00402706: call [edx+000000A0h]
  loc_0040270C: cmp eax, edi
  loc_0040270E: fnclex
  loc_00402710: jge 0040272Ah
  loc_00402712: mov edx, var_13C
  loc_00402718: push 000000A0h
  loc_0040271D: push 00401AA8h
  loc_00402722: push edx
  loc_00402723: push eax
  loc_00402724: call [00401034h] ; %StkVar1 = CheckObj(%StkVar2, %StkVar3, %StkVar4)
  loc_0040272A: mov edx, var_8C
  loc_00402730: lea ecx, var_40
  loc_00402733: mov var_8C, edi
  loc_00402739: call [004010DCh] ; %ecx = %S_edx_S '__vbaStrMove
  loc_0040273F: lea ecx, var_94
  loc_00402745: call [004010F4h] ; %fobj '__vbaFreeObj
  loc_0040274B: mov eax, 00000006h
  loc_00402750: xor ecx, ecx

  loc_00402752: cmp username_len, ax    //check if username is greater than 6
  loc_00402756: mov var_100, eax
  loc_0040275C: lea edx, var_54
  loc_0040275F: lea eax, var_108
  loc_00402765: setl cl
  loc_00402768: neg ecx
  loc_0040276A: mov var_110, cx
  loc_00402771: push edx
  loc_00402772: lea ecx, var_A8
  loc_00402778: push eax
  loc_00402779: push ecx
  loc_0040277A: mov var_108, 00008002h
  loc_00402784: mov var_118, 0000000Bh
  loc_0040278E: call [004010B4h] ; %S_eax_S = (#StkVar1%StkVar3 < %StkVar2) '__vbaVarCmpLt
  loc_00402794: push eax
  loc_00402795: lea edx, var_118
  loc_0040279B: lea eax, var_B8
  loc_004027A1: push edx
  loc_004027A2: push eax
  loc_004027A3: call [00401078h] ; Or
  loc_004027A9: push eax
  loc_004027AA: call [00401058h] ; @CBool(%StkVar1)
  loc_004027B0: lea ecx, var_118
  loc_004027B6: mov var_13C, ax
  loc_004027BD: call [00401010h] ; undef 'Ignore this '__vbaFreeVar
  loc_004027C3: cmp var_13C, di
  loc_004027CA: jz 00402873h
  loc_004027D0: mov eax, 80020004h
  loc_004027D5: mov ebx, 0000000Ah
  loc_004027DA: lea edx, var_108
  loc_004027E0: lea ecx, var_A8
  loc_004027E6: mov var_D0, eax
  loc_004027EC: mov var_D8, ebx
  loc_004027F2: mov var_C0, eax
  loc_004027F8: mov var_C8, ebx
  loc_004027FE: mov var_B0, eax
  loc_00402804: mov var_B8, ebx
  loc_0040280A: mov var_100, 00401ABCh ; "Please make sure both username and password contain six or more characters."
  loc_00402814: mov var_108, 00000008h
  loc_0040281E: call [004010D0h] ; %ecx = %S_edx_S '__vbaVarDup
  loc_00402824: lea ecx, var_D8
  loc_0040282A: lea edx, var_C8
  loc_00402830: push ecx
  loc_00402831: lea eax, var_B8
  loc_00402837: push edx
  loc_00402838: push eax
  loc_00402839: lea ecx, var_A8
  loc_0040283F: push edi
  loc_00402840: push ecx
  loc_00402841: call [0040104Ch] ; MsgBox(%StkVar1, %StkVar2, %StkVar3, %StkVar4, %StkVar5)
  loc_00402847: lea edx, var_D8
  loc_0040284D: lea eax, var_C8
  loc_00402853: push edx
  loc_00402854: lea ecx, var_B8
  loc_0040285A: push eax
  loc_0040285B: lea edx, var_A8
  loc_00402861: push ecx
  loc_00402862: push edx
  loc_00402863: push 00000004h
  loc_00402865: call [0040101Ch] ; undef 'Ignore this '__vbaFreeVarList
  loc_0040286B: add esp, 00000014h
  loc_0040286E: jmp 00403099h
  loc_00402873: mov eax, [esi]
  loc_00402875: push esi
  loc_00402876: mov var_100, 00000001h
  loc_00402880: mov var_108, 00000002h
  loc_0040288A: call [eax+00000304h]
  loc_00402890: lea ecx, var_94
  loc_00402896: push eax
  loc_00402897: push ecx
  loc_00402898: call [00401048h] ; Set %StkVar1 = %StkVar2 'Ignore this
  loc_0040289E: mov edx, [eax]
  loc_004028A0: lea ecx, var_8C
  loc_004028A6: push ecx
  loc_004028A7: push eax
  loc_004028A8: mov var_13C, eax
  loc_004028AE: call [edx+000000A0h]
  loc_004028B4: test eax, eax
  loc_004028B6: fnclex
  loc_004028B8: jge 004028D2h
  loc_004028BA: mov edx, var_13C
  loc_004028C0: push 000000A0h
  loc_004028C5: push 00401AA8h
  loc_004028CA: push edx
  loc_004028CB: push eax
  loc_004028CC: call [00401034h] ; %StkVar1 = CheckObj(%StkVar2, %StkVar3, %StkVar4)
  loc_004028D2: mov eax, var_8C
  loc_004028D8: push eax
  loc_004028D9: call [00401014h] ; @Len(%StkVar1)
  loc_004028DF: lea ecx, var_108
  loc_004028E5: mov var_110, eax
  loc_004028EB: lea edx, var_118
  loc_004028F1: push ecx
  loc_004028F2: lea eax, var_128
  loc_004028F8: push edx
  loc_004028F9: lea ecx, var_168
  loc_004028FF: push eax
  loc_00402900: lea edx, var_158
  loc_00402906: push ecx
  loc_00402907: lea eax, var_24
  loc_0040290A: push edx
  loc_0040290B: push eax
  loc_0040290C: mov var_118, 00000003h
  loc_00402916: mov var_120, 00000001h
  loc_00402920: mov var_128, 00000002h

  loc_0040292A: call [0040103Ch] ; For %x1#x2#x3 = %StkVar4 To %StkVar5 Step %StkVar6
  loc_00402930: lea ecx, var_8C
  loc_00402936: mov var_178, eax
  loc_0040293C: call [004010F0h] ; %ecx = "" '__vbaFreeStr
  loc_00402942: lea ecx, var_94
  loc_00402948: call [004010F4h] ; %fobj '__vbaFreeObj
  loc_0040294E: mov eax, var_178
  loc_00402954: test eax, eax
  loc_00402956: jz 00402BFEh
  loc_0040295C: mov ecx, [esi]
  loc_0040295E: push esi
  loc_0040295F: call [ecx+00000304h]
  loc_00402965: mov ebx, [00401048h] ; Set %StkVar1 = %StkVar2 'Ignore this
  loc_0040296B: lea edx, var_98
  loc_00402971: push eax
  loc_00402972: push edx
  loc_00402973: call ebx
  loc_00402975: mov eax, [esi]
  loc_00402977: push esi
  loc_00402978: call [eax+0000031Ch]
  loc_0040297E: lea ecx, var_94
  loc_00402984: push eax
  loc_00402985: push ecx
  loc_00402986: call ebx
  loc_00402988: mov ebx, eax
  loc_0040298A: mov eax, var_98
  loc_00402990: mov var_A0, eax
  loc_00402996: lea edx, var_B8
  loc_0040299C: lea eax, var_24
  loc_0040299F: push edx
  loc_004029A0: push eax
  loc_004029A1: mov var_13C, ebx
  loc_004029A7: mov var_B0, 00000001h
  loc_004029B1: mov var_B8, 00000002h
  loc_004029BB: mov var_98, 00000000h
  loc_004029C5: mov var_A8, 00000009h
  loc_004029CF: call [004010C8h] ; %S_eax_S = CLng(%StkVar1) '__vbaI4Var
  loc_004029D5: lea ecx, var_A8
  loc_004029DB: push eax
  loc_004029DC: lea edx, var_C8
  loc_004029E2: push ecx
  loc_004029E3: push edx
  loc_004029E4: call [00401064h] ; %x1 = Mid(%StkVar2, %StkVar3, %StkVar4)
  loc_004029EA: mov ebx, [ebx]
  loc_004029EC: lea eax, var_C8
  loc_004029F2: lea ecx, var_8C
  loc_004029F8: push eax
  loc_004029F9: push ecx
  loc_004029FA: call [0040109Ch] ; %StkVar1 = CStr(%StkVar2)
  loc_00402A00: mov edx, ebx
  loc_00402A02: mov ebx, var_13C
  loc_00402A08: push eax
  loc_00402A09: push ebx
  loc_00402A0A: call [edx+00000054h]
  loc_00402A0D: test eax, eax
  loc_00402A0F: fnclex
  loc_00402A11: jge 00402A22h
  loc_00402A13: push 00000054h
  loc_00402A15: push 00401B54h
  loc_00402A1A: push ebx
  loc_00402A1B: push eax
  loc_00402A1C: call [00401034h] ; %StkVar1 = CheckObj(%StkVar2, %StkVar3, %StkVar4)
  loc_00402A22: lea ecx, var_8C
  loc_00402A28: call [004010F0h] ; %ecx = "" '__vbaFreeStr
  loc_00402A2E: lea eax, var_98
  loc_00402A34: lea ecx, var_94
  loc_00402A3A: push eax
  loc_00402A3B: push ecx
  loc_00402A3C: push 00000002h
  loc_00402A3E: call [00401024h] ; %v = ""
  loc_00402A44: lea edx, var_C8
  loc_00402A4A: lea eax, var_B8
  loc_00402A50: push edx
  loc_00402A51: lea ecx, var_A8
  loc_00402A57: push eax
  loc_00402A58: push ecx
  loc_00402A59: push 00000003h
  loc_00402A5B: call [0040101Ch] ; undef 'Ignore this '__vbaFreeVarList
  loc_00402A61: mov edx, [esi]
  loc_00402A63: add esp, 0000001Ch
  loc_00402A66: push esi
  loc_00402A67: call [edx+00000318h]
  loc_00402A6D: mov ebx, [00401048h] ; Set %StkVar1 = %StkVar2 'Ignore this
  loc_00402A73: push eax
  loc_00402A74: lea eax, var_98
  loc_00402A7A: push eax
  loc_00402A7B: call ebx
  loc_00402A7D: mov ecx, [esi]
  loc_00402A7F: push esi
  loc_00402A80: mov var_144, eax
  loc_00402A86: call [ecx+0000031Ch]
  loc_00402A8C: lea edx, var_94
  loc_00402A92: push eax
  loc_00402A93: push edx
  loc_00402A94: call ebx
  loc_00402A96: mov ebx, eax
  loc_00402A98: lea ecx, var_8C
  loc_00402A9E: push ecx
  loc_00402A9F: push ebx
  loc_00402AA0: mov eax, [ebx]
  loc_00402AA2: call [eax+00000050h]
  loc_00402AA5: test eax, eax
  loc_00402AA7: fnclex
  loc_00402AA9: jge 00402ABAh
  loc_00402AAB: push 00000050h
  loc_00402AAD: push 00401B54h
  loc_00402AB2: push ebx
  loc_00402AB3: push eax
  loc_00402AB4: call [00401034h] ; %StkVar1 = CheckObj(%StkVar2, %StkVar3, %StkVar4)
  loc_00402ABA: mov edx, var_144
  loc_00402AC0: mov eax, var_8C
  loc_00402AC6: push eax
  loc_00402AC7: mov ebx, [edx]
  loc_00402AC9: call [00401028h] ; @Asc(%StkVar1)
  loc_00402ACF: push eax
  loc_00402AD0: call [00401000h] ; @CStr(%StkVar1) '__vbaStrI2
  loc_00402AD6: mov edx, eax
  loc_00402AD8: lea ecx, var_90
  loc_00402ADE: call [004010DCh] ; %ecx = %S_edx_S '__vbaStrMove
  loc_00402AE4: mov ecx, ebx
  loc_00402AE6: mov ebx, var_144
  loc_00402AEC: push eax
  loc_00402AED: push ebx
  loc_00402AEE: call [ecx+00000054h]
  loc_00402AF1: test eax, eax
  loc_00402AF3: fnclex
  loc_00402AF5: jge 00402B06h
  loc_00402AF7: push 00000054h
  loc_00402AF9: push 00401B54h
  loc_00402AFE: push ebx
  loc_00402AFF: push eax
  loc_00402B00: call [00401034h] ; %StkVar1 = CheckObj(%StkVar2, %StkVar3, %StkVar4)
  loc_00402B06: lea edx, var_90
  loc_00402B0C: lea eax, var_8C
  loc_00402B12: push edx
  loc_00402B13: push eax
  loc_00402B14: push 00000002h
  loc_00402B16: call [004010B8h] ; %v = ""
  loc_00402B1C: lea ecx, var_98
  loc_00402B22: lea edx, var_94
  loc_00402B28: push ecx
  loc_00402B29: push edx
  loc_00402B2A: push 00000002h
  loc_00402B2C: call [00401024h] ; %v = ""
  loc_00402B32: mov eax, [esi]
  loc_00402B34: add esp, 00000018h
  loc_00402B37: push esi
  loc_00402B38: call [eax+00000318h]
  loc_00402B3E: lea ecx, var_94
  loc_00402B44: push eax
  loc_00402B45: push ecx
  loc_00402B46: call [00401048h] ; Set %StkVar1 = %StkVar2 'Ignore this
  loc_00402B4C: mov ebx, eax
  loc_00402B4E: lea eax, var_8C
  loc_00402B54: push eax
  loc_00402B55: push ebx
  loc_00402B56: mov edx, [ebx]
  loc_00402B58: call [edx+00000050h]
  loc_00402B5B: test eax, eax
  loc_00402B5D: fnclex
  loc_00402B5F: jge 00402B70h
  loc_00402B61: push 00000050h
  loc_00402B63: push 00401B54h
  loc_00402B68: push ebx
  loc_00402B69: push eax
  loc_00402B6A: call [00401034h] ; %StkVar1 = CheckObj(%StkVar2, %StkVar3, %StkVar4)
  loc_00402B70: mov ecx, var_8C
  loc_00402B76: push ecx
  loc_00402B77: call [004010A8h] ; %PushFPU %StkVar1
  loc_00402B7D: movsx edx, di
  loc_00402B80: mov var_188, edx
  loc_00402B86: fild real4 ptr var_188
  loc_00402B8C: fstp real8 ptr var_190
  loc_00402B92: fadd st0, real8 ptr var_190
  loc_00402B98: fnstsw ax
  loc_00402B9A: test al, 0Dh
  loc_00402B9C: jnz 004033A9h
  loc_00402BA2: call [004010D4h] ; @CInt(%FPU) '__vbaFpI2
  loc_00402BA8: lea ecx, var_8C
  loc_00402BAE: mov edi, eax
  loc_00402BB0: call [004010F0h] ; %ecx = "" '__vbaFreeStr
  loc_00402BB6: lea ecx, var_94
  loc_00402BBC: call [004010F4h] ; %fobj '__vbaFreeObj
  loc_00402BC2: push FFFFFFFFh
  loc_00402BC4: call [00401040h] ; __vbaStrBool
  loc_00402BCA: mov edx, eax
  loc_00402BCC: lea ecx, var_40
  loc_00402BCF: call [004010DCh] ; %ecx = %S_edx_S '__vbaStrMove
  loc_00402BD5: lea eax, var_168
  loc_00402BDB: lea ecx, var_158
  loc_00402BE1: push eax
  loc_00402BE2: lea edx, var_24
  loc_00402BE5: push ecx
  loc_00402BE6: push edx
  loc_00402BE7: call [004010E8h] ; Next %x1
  loc_00402BED: mov ebx, [0040100Ch] ; %ecx = %S_edx_S '__vbaVarMove
  loc_00402BF3: mov var_178, eax
  loc_00402BF9: jmp 0040294Eh
  
  loc_00402BFE: mov ax, di
  loc_00402C01: imul ax, ax, 0007h
  loc_00402C05: jo 004033AEh
  loc_00402C0B: add ax, 0038h
  loc_00402C0F: jo 004033AEh
  loc_00402C15: movsx ecx, ax
  loc_00402C18: mov var_194, ecx
  loc_00402C1E: fild real4 ptr var_194
  loc_00402C24: fstp real8 ptr var_19C
  loc_00402C2A: fld real8 ptr var_19C
  loc_00402C30: cmp [00404000h], 00000000h
  loc_00402C37: jnz 00402C41h
  loc_00402C39: fdiv st0, real8 ptr [00401100h]
  loc_00402C3F: jmp 00402C52h
  loc_00402C41: push [00401104h]
  loc_00402C47: push [00401100h]
  loc_00402C4D: call 00401154h ; undef 'Ignore this '_adj_fdiv_m64
  loc_00402C52: fnstsw ax
  loc_00402C54: test al, 0Dh
  loc_00402C56: jnz 004033A9h
  loc_00402C5C: call [004010D4h] ; @CInt(%FPU) '__vbaFpI2
  loc_00402C62: push eax
  loc_00402C63: call [00401000h] ; @CStr(%StkVar1) '__vbaStrI2
  loc_00402C69: lea edx, var_A8
  loc_00402C6F: lea ecx, var_78
  loc_00402C72: mov var_A0, eax
  loc_00402C78: mov var_A8, 00000008h
  loc_00402C82: call ebx
  loc_00402C84: lea edx, var_A8
  loc_00402C8A: lea eax, var_78
  loc_00402C8D: push edx
  loc_00402C8E: push 00000001h
  loc_00402C90: lea ecx, var_8C
  loc_00402C96: push eax
  loc_00402C97: push ecx
  loc_00402C98: mov var_A0, 00000004h
  loc_00402CA2: mov var_A8, 00000002h
  loc_00402CAC: call [0040109Ch] ; %StkVar1 = CStr(%StkVar2)
  loc_00402CB2: push eax
  loc_00402CB3: call [00401060h] ; @Mid$(%StkVar1, %StkVar2, %StkVar3)
  loc_00402CB9: lea edx, var_B8
  loc_00402CBF: lea ecx, var_78
  loc_00402CC2: mov var_B0, eax
  loc_00402CC8: mov var_B8, 00000008h
  loc_00402CD2: call ebx
  loc_00402CD4: lea ecx, var_8C
  loc_00402CDA: call [004010F0h] ; %ecx = "" '__vbaFreeStr
  loc_00402CE0: lea ecx, var_A8
  loc_00402CE6: call [00401010h] ; undef 'Ignore this '__vbaFreeVar
  loc_00402CEC: mov dx, di
  loc_00402CEF: imul dx, dx, 0009h
  loc_00402CF3: jo 004033AEh
  loc_00402CF9: add dx, 002Dh
  loc_00402CFD: jo 004033AEh
  loc_00402D03: movsx eax, dx
  loc_00402D06: mov var_1A0, eax
  loc_00402D0C: fild real4 ptr var_1A0
  loc_00402D12: fstp real8 ptr var_1A8
  loc_00402D18: fld real8 ptr var_1A8
  loc_00402D1E: cmp [00404000h], 00000000h
  loc_00402D25: jnz 00402D2Fh
  loc_00402D27: fdiv st0, real8 ptr [00401100h]
  loc_00402D2D: jmp 00402D40h
  loc_00402D2F: push [00401104h]
  loc_00402D35: push [00401100h]
  loc_00402D3B: call 00401154h ; undef 'Ignore this '_adj_fdiv_m64
  loc_00402D40: fnstsw ax
  loc_00402D42: test al, 0Dh
  loc_00402D44: jnz 004033A9h
  loc_00402D4A: call [004010D4h] ; @CInt(%FPU) '__vbaFpI2
  loc_00402D50: push eax
  loc_00402D51: call [00401000h] ; @CStr(%StkVar1) '__vbaStrI2
  loc_00402D57: lea edx, var_A8
  loc_00402D5D: lea ecx, var_88
  loc_00402D63: mov var_A0, eax
  loc_00402D69: mov var_A8, 00000008h
  loc_00402D73: call ebx
  loc_00402D75: lea ecx, var_A8
  loc_00402D7B: lea edx, var_88
  loc_00402D81: push ecx
  loc_00402D82: push 00000001h
  loc_00402D84: lea eax, var_8C
  loc_00402D8A: push edx
  loc_00402D8B: push eax
  loc_00402D8C: mov var_A0, 00000004h
  loc_00402D96: mov var_A8, 00000002h
  loc_00402DA0: call [0040109Ch] ; %StkVar1 = CStr(%StkVar2)
  loc_00402DA6: push eax
  loc_00402DA7: call [00401060h] ; @Mid$(%StkVar1, %StkVar2, %StkVar3)
  loc_00402DAD: lea edx, var_B8
  loc_00402DB3: lea ecx, var_88
  loc_00402DB9: mov var_B0, eax
  loc_00402DBF: mov var_B8, 00000008h
  loc_00402DC9: call ebx
  loc_00402DCB: lea ecx, var_8C
  loc_00402DD1: call [004010F0h] ; %ecx = "" '__vbaFreeStr
  loc_00402DD7: lea ecx, var_A8
  loc_00402DDD: call [00401010h] ; undef 'Ignore this '__vbaFreeVar
  loc_00402DE3: mov cx, di
  loc_00402DE6: imul cx, cx, 0008h
  loc_00402DEA: jo 004033AEh
  loc_00402DF0: add cx, 0020h
  loc_00402DF4: jo 004033AEh
  loc_00402DFA: movsx edx, cx
  loc_00402DFD: mov var_1AC, edx
  loc_00402E03: fild real4 ptr var_1AC
  loc_00402E09: fstp real8 ptr var_1B4
  loc_00402E0F: fld real8 ptr var_1B4
  loc_00402E15: cmp [00404000h], 00000000h
  loc_00402E1C: jnz 00402E26h
  loc_00402E1E: fdiv st0, real8 ptr [00401100h]
  loc_00402E24: jmp 00402E37h
  loc_00402E26: push [00401104h]
  loc_00402E2C: push [00401100h]
  loc_00402E32: call 00401154h ; undef 'Ignore this '_adj_fdiv_m64
  loc_00402E37: fnstsw ax
  loc_00402E39: test al, 0Dh
  loc_00402E3B: jnz 004033A9h
  loc_00402E41: call [004010D4h] ; @CInt(%FPU) '__vbaFpI2
  loc_00402E47: push eax
  loc_00402E48: call [00401000h] ; @CStr(%StkVar1) '__vbaStrI2
  loc_00402E4E: lea edx, var_A8
  loc_00402E54: lea ecx, var_68
  loc_00402E57: mov var_A0, eax
  loc_00402E5D: mov var_A8, 00000008h
  loc_00402E67: call ebx
  loc_00402E69: lea eax, var_A8
  loc_00402E6F: lea ecx, var_68
  loc_00402E72: push eax
  loc_00402E73: push 00000001h
  loc_00402E75: lea edx, var_8C
  loc_00402E7B: push ecx
  loc_00402E7C: push edx
  loc_00402E7D: mov var_A0, 00000004h
  loc_00402E87: mov var_A8, 00000002h
  loc_00402E91: call [0040109Ch] ; %StkVar1 = CStr(%StkVar2)
  loc_00402E97: push eax
  loc_00402E98: call [00401060h] ; @Mid$(%StkVar1, %StkVar2, %StkVar3)
  loc_00402E9E: lea edx, var_B8
  loc_00402EA4: lea ecx, var_68
  loc_00402EA7: mov var_B0, eax
  loc_00402EAD: mov var_B8, 00000008h
  loc_00402EB7: call ebx
  loc_00402EB9: lea ecx, var_8C
  loc_00402EBF: call [004010F0h] ; %ecx = "" '__vbaFreeStr
  loc_00402EC5: lea ecx, var_A8
  loc_00402ECB: call [00401010h] ; undef 'Ignore this '__vbaFreeVar
  loc_00402ED1: imul di, di, 0006h
  loc_00402ED5: jo 004033AEh
  loc_00402EDB: add di, 003Ch
  loc_00402EDF: jo 004033AEh
  loc_00402EE5: movsx eax, di
  loc_00402EE8: mov var_1B8, eax
  loc_00402EEE: fild real4 ptr var_1B8
  loc_00402EF4: fstp real8 ptr var_1C0
  loc_00402EFA: fld real8 ptr var_1C0
  loc_00402F00: cmp [00404000h], 00000000h
  loc_00402F07: jnz 00402F11h
  loc_00402F09: fdiv st0, real8 ptr [00401100h]
  loc_00402F0F: jmp 00402F22h
  loc_00402F11: push [00401104h]
  loc_00402F17: push [00401100h]
  loc_00402F1D: call 00401154h ; undef 'Ignore this '_adj_fdiv_m64
  loc_00402F22: fnstsw ax
  loc_00402F24: test al, 0Dh
  loc_00402F26: jnz 004033A9h
  loc_00402F2C: call [004010D4h] ; @CInt(%FPU) '__vbaFpI2
  loc_00402F32: push eax
  loc_00402F33: call [00401000h] ; @CStr(%StkVar1) '__vbaStrI2
  loc_00402F39: mov edi, 00000008h
  loc_00402F3E: lea edx, var_A8
  loc_00402F44: lea ecx, var_34
  loc_00402F47: mov var_A0, eax
  loc_00402F4D: mov var_A8, edi
  loc_00402F53: call ebx
  loc_00402F55: lea ecx, var_A8
  loc_00402F5B: lea edx, var_34
  loc_00402F5E: push ecx
  loc_00402F5F: push 00000001h
  loc_00402F61: lea eax, var_8C
  loc_00402F67: push edx
  loc_00402F68: push eax
  loc_00402F69: mov var_A0, 00000004h
  loc_00402F73: mov var_A8, 00000002h
  loc_00402F7D: call [0040109Ch] ; %StkVar1 = CStr(%StkVar2)
  loc_00402F83: push eax
  loc_00402F84: call [00401060h] ; @Mid$(%StkVar1, %StkVar2, %StkVar3)
  loc_00402F8A: mov var_B0, eax
  loc_00402F90: mov var_B8, edi
  loc_00402F96: lea edx, var_B8
  loc_00402F9C: lea ecx, var_34
  loc_00402F9F: call ebx
  loc_00402FA1: lea ecx, var_8C
  loc_00402FA7: call [004010F0h] ; %ecx = "" '__vbaFreeStr
  loc_00402FAD: lea ecx, var_A8
  loc_00402FB3: call [00401010h] ; undef 'Ignore this '__vbaFreeVar
  loc_00402FB9: mov eax, 00401B68h
  loc_00402FBE: lea ecx, var_78
  loc_00402FC1: mov var_100, eax
  loc_00402FC7: mov var_110, eax
  loc_00402FCD: mov var_120, eax
  loc_00402FD3: lea edx, var_108
  loc_00402FD9: push ecx
  loc_00402FDA: lea eax, var_A8
  loc_00402FE0: mov var_108, edi
  loc_00402FE6: mov var_118, edi
  loc_00402FEC: mov var_128, edi
  loc_00402FF2: mov edi, [004010CCh] ; @#StkVar1%StkVar3 + %StkVar2 '__vbaVarAdd
  loc_00402FF8: push edx
  loc_00402FF9: push eax
  loc_00402FFA: call edi
  loc_00402FFC: lea ecx, var_88
  loc_00403002: push eax
  loc_00403003: lea edx, var_B8
  loc_00403009: push ecx
  loc_0040300A: push edx
  loc_0040300B: call edi
  loc_0040300D: push eax
  loc_0040300E: lea eax, var_118
  loc_00403014: lea ecx, var_C8
  loc_0040301A: push eax
  loc_0040301B: push ecx
  loc_0040301C: call edi
  loc_0040301E: push eax
  loc_0040301F: lea edx, var_68
  loc_00403022: lea eax, var_D8
  loc_00403028: push edx
  loc_00403029: push eax
  loc_0040302A: call edi
  loc_0040302C: lea ecx, var_128
  loc_00403032: push eax
  loc_00403033: lea edx, var_E8
  loc_00403039: push ecx
  loc_0040303A: push edx
  loc_0040303B: call edi
  loc_0040303D: push eax
  loc_0040303E: lea eax, var_34
  loc_00403041: lea ecx, var_F8
  loc_00403047: push eax
  loc_00403048: push ecx
  loc_00403049: call edi
  loc_0040304B: push eax
  loc_0040304C: call [00401018h] ; @%x1 '__vbaStrVarMove
  loc_00403052: mov edx, eax
  loc_00403054: lea ecx, var_38
  loc_00403057: call [004010DCh] ; %ecx = %S_edx_S '__vbaStrMove
  loc_0040305D: lea edx, var_F8
  loc_00403063: lea eax, var_E8
  loc_00403069: push edx
  loc_0040306A: lea ecx, var_D8
  loc_00403070: push eax
  loc_00403071: lea edx, var_C8
  loc_00403077: push ecx
  loc_00403078: lea eax, var_B8
  loc_0040307E: push edx
  loc_0040307F: lea ecx, var_A8
  loc_00403085: push eax
  loc_00403086: push ecx
  loc_00403087: push 00000006h
  loc_00403089: call [0040101Ch] ; undef 'Ignore this '__vbaFreeVarList
  loc_0040308F: add esp, 0000001Ch
  loc_00403092: mov ebx, 0000000Ah
  loc_00403097: xor edi, edi
  loc_00403099: mov edx, var_40
  loc_0040309C: push edx
  loc_0040309D: call [00401044h] ; @CBool(%StkVar1)
  loc_004030A3: cmp ax, FFFFFFh
  loc_004030A7: jnz 004032C7h
  loc_004030AD: mov eax, [esi]
  loc_004030AF: push esi
  loc_004030B0: call [eax+00000300h]
  loc_004030B6: lea ecx, var_94
  loc_004030BC: push eax
  loc_004030BD: push ecx
  loc_004030BE: call [00401048h] ; Set %StkVar1 = %StkVar2 'Ignore this
  loc_004030C4: mov edx, [eax]
  loc_004030C6: lea ecx, var_8C
  loc_004030CC: push ecx
  loc_004030CD: push eax
  loc_004030CE: mov var_13C, eax
  loc_004030D4: call [edx+000000A0h]
  loc_004030DA: cmp eax, edi
  loc_004030DC: fnclex
  loc_004030DE: jge 004030F8h
  loc_004030E0: mov edx, var_13C
  loc_004030E6: push 000000A0h
  loc_004030EB: push 00401AA8h
  loc_004030F0: push edx
  loc_004030F1: push eax
  loc_004030F2: call [00401034h] ; %StkVar1 = CheckObj(%StkVar2, %StkVar3, %StkVar4)
  loc_004030F8: mov eax, var_8C
  loc_004030FE: mov ecx, var_38
  loc_00403101: push eax
  loc_00403102: push ecx
  loc_00403103: call [00401070h] ; @(%StkVar2 = %x1) '__vbaStrCmp
  loc_00403109: neg eax
  loc_0040310B: sbb eax, eax
  loc_0040310D: lea ecx, var_8C
  loc_00403113: inc eax
  loc_00403114: neg eax
  loc_00403116: mov var_144, eax
  loc_0040311C: call [004010F0h] ; %ecx = "" '__vbaFreeStr
  loc_00403122: lea ecx, var_94
  loc_00403128: call [004010F4h] ; %fobj '__vbaFreeObj
  loc_0040312E: cmp var_144, di
  loc_00403135: mov eax, 80020004h
  loc_0040313A: mov var_D0, eax
  loc_00403140: mov var_D8, ebx
  loc_00403146: mov var_C0, eax
  loc_0040314C: mov var_C8, ebx
  loc_00403152: mov var_B0, eax
  loc_00403158: mov var_B8, ebx
  loc_0040315E: jz 00403245h
  loc_00403164: mov edx, [esi]
  loc_00403166: push esi
  loc_00403167: call [edx+00000304h]
  loc_0040316D: push eax
  loc_0040316E: lea eax, var_94
  loc_00403174: push eax
  loc_00403175: call [00401048h] ; Set %StkVar1 = %StkVar2 'Ignore this
  loc_0040317B: mov esi, eax
  loc_0040317D: lea edx, var_8C
  loc_00403183: push edx
  loc_00403184: push esi
  loc_00403185: mov ecx, [esi]
  loc_00403187: call [ecx+000000A0h]
  loc_0040318D: cmp eax, edi
  loc_0040318F: fnclex
  loc_00403191: jge 004031A5h
  loc_00403193: push 000000A0h
  loc_00403198: push 00401AA8h
  loc_0040319D: push esi
  loc_0040319E: push eax
  loc_0040319F: call [00401034h] ; %StkVar1 = CheckObj(%StkVar2, %StkVar3, %StkVar4)
  loc_004031A5: mov eax, var_8C
  loc_004031AB: mov esi, [00401030h] ; @%StkVar2 & %x1 '__vbaStrCat
  loc_004031B1: push 00401B70h ; "Congrats "
  loc_004031B6: push eax
  loc_004031B7: call @%StkVar2 & %x1 '__vbaStrCat
  loc_004031B9: mov edx, eax
  loc_004031BB: lea ecx, var_90
  loc_004031C1: call [004010DCh] ; %ecx = %S_edx_S '__vbaStrMove
  loc_004031C7: push eax
  loc_004031C8: push 00401B88h ; ", you got your serial right. Now make a keygen for this."
  loc_004031CD: call @%StkVar2 & %x1 '__vbaStrCat
  loc_004031CF: lea ecx, var_D8
  loc_004031D5: mov var_A0, eax
  loc_004031DB: lea edx, var_C8
  loc_004031E1: push ecx
  loc_004031E2: lea eax, var_B8
  loc_004031E8: push edx
  loc_004031E9: push eax
  loc_004031EA: lea ecx, var_A8
  loc_004031F0: push edi
  loc_004031F1: push ecx
  loc_004031F2: mov var_A8, 00000008h
  loc_004031FC: call [0040104Ch] ; MsgBox(%StkVar1, %StkVar2, %StkVar3, %StkVar4, %StkVar5)
  loc_00403202: lea edx, var_90
  loc_00403208: lea eax, var_8C
  loc_0040320E: push edx
  loc_0040320F: push eax
  loc_00403210: push 00000002h
  loc_00403212: call [004010B8h] ; %v = ""
  loc_00403218: add esp, 0000000Ch
  loc_0040321B: lea ecx, var_94
  loc_00403221: call [004010F4h] ; %fobj '__vbaFreeObj
  loc_00403227: lea ecx, var_D8
  loc_0040322D: lea edx, var_C8
  loc_00403233: push ecx
  loc_00403234: lea eax, var_B8
  loc_0040323A: push edx
  loc_0040323B: lea ecx, var_A8
  loc_00403241: push eax
  loc_00403242: push ecx
  loc_00403243: jmp 004032AAh
  loc_00403245: lea edx, var_108
  loc_0040324B: lea ecx, var_A8
  loc_00403251: mov var_100, 00401C00h ; "Sorry, try again."
  loc_0040325B: mov var_108, 00000008h
  loc_00403265: call [004010D0h] ; %ecx = %S_edx_S '__vbaVarDup
  loc_0040326B: lea edx, var_D8
  loc_00403271: lea eax, var_C8
  loc_00403277: push edx
  loc_00403278: lea ecx, var_B8
  loc_0040327E: push eax
  loc_0040327F: push ecx
  loc_00403280: lea edx, var_A8
  loc_00403286: push edi
  loc_00403287: push edx
  loc_00403288: call [0040104Ch] ; MsgBox(%StkVar1, %StkVar2, %StkVar3, %StkVar4, %StkVar5)
  loc_0040328E: lea eax, var_D8
  loc_00403294: lea ecx, var_C8
  loc_0040329A: push eax
  loc_0040329B: lea edx, var_B8
  loc_004032A1: push ecx
  loc_004032A2: lea eax, var_A8
  loc_004032A8: push edx
  loc_004032A9: push eax
  loc_004032AA: push 00000004h
  loc_004032AC: call [0040101Ch] ; undef 'Ignore this '__vbaFreeVarList
  loc_004032B2: add esp, 00000014h
  loc_004032B5: push edi
  loc_004032B6: call [00401040h] ; __vbaStrBool
  loc_004032BC: mov edx, eax
  loc_004032BE: lea ecx, var_40
  loc_004032C1: call [004010DCh] ; %ecx = %S_edx_S '__vbaStrMove
  loc_004032C7: mov var_4, edi
  loc_004032CA: fwait
  loc_004032CB: push 0040338Ah
  loc_004032D0: jmp 00403334h
  loc_004032D2: lea ecx, var_90
  loc_004032D8: lea edx, var_8C
  loc_004032DE: push ecx
  loc_004032DF: push edx
  loc_004032E0: push 00000002h
  loc_004032E2: call [004010B8h] ; %v = ""
  loc_004032E8: lea eax, var_98
  loc_004032EE: lea ecx, var_94
  loc_004032F4: push eax
  loc_004032F5: push ecx
  loc_004032F6: push 00000002h
  loc_004032F8: call [00401024h] ; %v = ""
  loc_004032FE: lea edx, var_F8
  loc_00403304: lea eax, var_E8
  loc_0040330A: push edx
  loc_0040330B: lea ecx, var_D8
  loc_00403311: push eax
  loc_00403312: lea edx, var_C8
  loc_00403318: push ecx
  loc_00403319: lea eax, var_B8
  loc_0040331F: push edx
  loc_00403320: lea ecx, var_A8
  loc_00403326: push eax
  loc_00403327: push ecx
  loc_00403328: push 00000006h
  loc_0040332A: call [0040101Ch] ; undef 'Ignore this '__vbaFreeVarList
  loc_00403330: add esp, 00000034h
  loc_00403333: ret
  loc_00403334: lea edx, var_168
  loc_0040333A: lea eax, var_158
  loc_00403340: push edx
  loc_00403341: push eax
  loc_00403342: push 00000002h
  loc_00403344: call [0040101Ch] ; undef 'Ignore this '__vbaFreeVarList
  loc_0040334A: mov esi, [00401010h] ; undef 'Ignore this '__vbaFreeVar
  loc_00403350: add esp, 0000000Ch
  loc_00403353: lea ecx, var_24
  loc_00403356: call undef 'Ignore this '__vbaFreeVar
  loc_00403358: lea ecx, var_34
  loc_0040335B: call undef 'Ignore this '__vbaFreeVar
  loc_0040335D: mov edi, [004010F0h] ; %ecx = "" '__vbaFreeStr
  loc_00403363: lea ecx, var_38
  loc_00403366: call edi
  loc_00403368: lea ecx, var_40
  loc_0040336B: call edi
  loc_0040336D: lea ecx, var_44
  loc_00403370: call edi
  loc_00403372: lea ecx, var_54
  loc_00403375: call undef 'Ignore this '__vbaFreeVar
  loc_00403377: lea ecx, var_68
  loc_0040337A: call undef 'Ignore this '__vbaFreeVar
  loc_0040337C: lea ecx, var_78
  loc_0040337F: call undef 'Ignore this '__vbaFreeVar
  loc_00403381: lea ecx, var_88
  loc_00403387: call undef 'Ignore this '__vbaFreeVar
  loc_00403389: ret
  loc_0040338A: mov eax, arg_8
  loc_0040338D: push eax
  loc_0040338E: mov ecx, [eax]
  loc_00403390: call [ecx+00000008h]
  loc_00403393: mov eax, var_4
  loc_00403396: mov ecx, var_14
  loc_00403399: pop edi
  loc_0040339A: pop esi
  loc_0040339B: mov fs:[00000000h], ecx
  loc_004033A2: pop ebx
  loc_004033A3: mov esp, ebp
  loc_004033A5: pop ebp
  loc_004033A6: retn 0004h
