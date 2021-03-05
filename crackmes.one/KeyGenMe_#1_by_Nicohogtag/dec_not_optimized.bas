Private Sub Command1_Click() '402520
  Dim arg_8 As Variant
  Dim var_94 As TextBox
  Dim var_54 As TextBox
  Dim var_13C As Label
  Dim var_98 As Label
  Dim var_144 As Label
  loc_00402542: var_C = ""
  loc_00402545: var_8 = &H401108
  loc_00402565: edi = ""
  loc_00402568: var_24 = ""
  loc_0040256B: var_34 = ""
  loc_0040256E: var_38 = ""
  loc_00402571: var_40 = ""
  loc_00402574: var_44 = ""
  loc_00402577: var_54 = ""
  loc_0040257A: var_68 = ""
  loc_0040257D: var_78 = ""
  loc_00402580: var_88 = ""
  loc_00402586: var_8C = ""
  loc_0040258C: var_90 = ""
  loc_00402592: var_94 = ""
  loc_00402598: var_98 = ""
  loc_0040259E: var_A8 = ""
  loc_004025A4: var_B8 = ""
  loc_004025AA: var_C8 = ""
  loc_004025B0: var_D8 = ""
  loc_004025B6: var_E8 = ""
  loc_004025BC: var_F8 = ""
  loc_004025C2: var_108 = ""
  loc_004025C8: var_118 = ""
  loc_004025CE: var_128 = ""
  loc_004025D4: var_158 = ""
  loc_004025DA: var_168 = ""
  loc_00402600: var_8C = Text1.Text
  loc_0040260A: If var_8C >= 0 Then GoTo loc_0040261E
  loc_00402618: var_8C = CheckObj(var_94, global_00401AA8, 160)
  loc_0040261E: 'Referenced from: 0040260A
  loc_0040263A: var_100 = Len(var_8C)
  loc_00402640: var_108 = 3
  loc_0040264A: var_54 = Len(var_8C)
  loc_00402685: var_13C = var_54
  loc_0040268B: var_8C = Text2.Text
  loc_00402695: If var_8C >= 0 Then GoTo loc_004026AF
  loc_004026A9: var_8C = CheckObj(var_13C, global_00401AA8, 160)
  loc_004026AF: 'Referenced from: 00402695
  loc_004026BE: var_ret_1 = Len(var_8C)
  loc_004026CA: var_58 = var_ret_1
  loc_00402706: var_8C = Text1.Text
  loc_00402710: If var_8C >= 0 Then GoTo loc_0040272A
  loc_00402724: var_8C = CheckObj(var_13C, global_00401AA8, 160)
  loc_0040272A: 'Referenced from: 00402710
  loc_00402739: var_40 = var_8C
  loc_00402750: ecx = ""
  loc_00402756: var_100 = 6
  loc_00402765: If var_58 < 6 Then ecx = 1
  loc_0040276A: var_110 = ""
  loc_0040277A: var_108 = &H8002
  loc_00402784: var_118 = 11
  loc_0040278E: var_ret_2 = (var_54 < 6)
  loc_004027A3: call Or(var_B8, var_118, var_ret_2, var_94, arg_8, arg_8, var_94, var_54, arg_8, var_94, arg_8, arg_8, edi, arg_8, %ecx = %S_edx_S)
  loc_004027B6: var_13C = CBool(Or(var_B8, var_118, var_ret_2, var_94, arg_8, arg_8, var_94, var_54, arg_8, var_94, arg_8, arg_8, edi, arg_8, var_A8 = %S_edx_S))
  loc_004027CA: If var_13C = 0 Then GoTo loc_00402873
  loc_004027E6: var_D0 = 80020004h
  loc_004027EC: var_D8 = 10
  loc_004027F2: var_C0 = 80020004h
  loc_0040281E: var_A8 = "Please make sure both username and password contain six or more characters."
  loc_00402841: MsgBox(var_A8, 0, var_B8, var_C8, var_D8)
  loc_0040286E: GoTo loc_00403099
  loc_00402873: 'Referenced from: 004027CA
  loc_00402876: var_100 = 1
  loc_00402880: var_108 = 2
  loc_004028AE: var_8C = Text1.Text
  loc_004028B8: If var_8C >= 0 Then GoTo loc_004028D2
  loc_004028CC: var_8C = CheckObj(var_13C, global_00401AA8, 160)
  loc_004028D2: 'Referenced from: 004028B8
  loc_004028E5: var_110 = Len(var_8C)
  loc_0040290C: var_118 = 3
  loc_00402916: var_120 = 1
  loc_00402920: var_128 = 2
  loc_0040292A: For var_24 = 1 To Len(var_8C) Step 1
  loc_00402936: var_178 = var_24
  loc_0040294E: 
  loc_00402956: If var_178 = 0 Then GoTo loc_00402BFE
  loc_00402990: var_A0 = var_98
  loc_004029A7: var_B0 = 1
  loc_004029B1: var_B8 = 2
  loc_004029BB: var_98 = 0
  loc_004029C5: var_A8 = 9
  loc_004029CF: var_ret_3 = CLng(var_24)
  loc_004029E4: var_C8 = Mid(var_98, var_ret_3, 1)
  loc_004029FA: var_8C = CStr(var_C8)
  loc_00402A0A: Label1.Caption = var_8C
  loc_00402A11: If var_8C >= 0 Then GoTo loc_00402A22
  loc_00402A1C: var_8C = CheckObj(var_13C, global_00401B54, 84)
  loc_00402A22: 'Referenced from: 00402A11
  loc_00402A80: var_144 = var_98
  loc_00402AA2: var_8C = Label1.Caption
  loc_00402AA9: If var_8C >= 0 Then GoTo loc_00402ABA
  loc_00402AB4: var_8C = CheckObj(var_98, global_00401B54, 80)
  loc_00402ABA: 'Referenced from: 00402AA9
  loc_00402ADE: var_90 = CStr(Asc(var_8C))
  loc_00402AEE: Label1.Caption = var_90
  loc_00402AF5: If var_90 >= 0 Then GoTo loc_00402B06
  loc_00402B00: var_90 = CheckObj(var_144, global_00401B54, 84)
  loc_00402B06: 'Referenced from: 00402AF5
  loc_00402B58: var_8C = Label2.Caption
  loc_00402B5F: If var_8C >= 0 Then GoTo loc_00402B70
  loc_00402B6A: var_8C = CheckObj(arg_8, global_00401B54, 80)
  loc_00402B70: 'Referenced from: 00402B5F
  loc_00402B80: var_188 = ""
  loc_00402B8C: var_190 = var_188
  loc_00402BC4: call __vbaStrBool(FFFFFFFFh, var_94, arg_8, arg_8, var_94, var_98, arg_8, var_98, var_B8, arg_8, var_94, arg_8, arg_8)
  loc_00402BCF: var_40 = __vbaStrBool(FFFFFFFFh, var_94, arg_8, arg_8, var_94, var_98, arg_8, var_98, var_B8, arg_8, var_94, arg_8, arg_8)
  loc_00402BE7: Next var_24
  loc_00402BF3: var_178 = Next var_24
  loc_00402BF9: GoTo loc_0040294E
  loc_00402BFE: 'Referenced from: 00402956
  loc_00402C01: CInt((var_8C + var_190)) = CInt((var_8C + var_190)) * 0007h
  loc_00402C0B: CInt((var_8C + var_190)) = CInt((var_8C + var_190)) + 0038h
  loc_00402C18: var_194 = CInt((var_8C + var_190))+0038h
  loc_00402C24: var_19C = var_194
  loc_00402C37: If global_404000 <> 0 Then GoTo loc_00402C41
  loc_00402C3F: GoTo loc_00402C52
  loc_00402C41: 'Referenced from: 00402C37
  loc_00402C52: 'Referenced from: 00402C3F
  loc_00402C72: var_A0 = CStr(CInt((var_19C / global_401100)))
  loc_00402C78: var_A8 = 8
  loc_00402C82: var_78 = CStr(CInt((var_19C / global_401100)))
  loc_00402C98: var_A0 = 4
  loc_00402CA2: var_A8 = 2
  loc_00402CAC: var_8C = CStr(var_78)
  loc_00402CC2: var_B0 = Mid$(var_8C, 1, 4)
  loc_00402CC8: var_B8 = 8
  loc_00402CD2: var_78 = Mid$(var_8C, 1, 4)
  loc_00402CEF: CInt((var_8C + var_190)) = CInt((var_8C + var_190)) * 0009h
  loc_00402CF9: CInt((var_8C + var_190)) = CInt((var_8C + var_190)) + 002Dh
  loc_00402D06: var_1A0 = CInt((var_8C + var_190))+002Dh
  loc_00402D12: var_1A8 = var_1A0
  loc_00402D25: If global_404000 <> 0 Then GoTo loc_00402D2F
  loc_00402D2D: GoTo loc_00402D40
  loc_00402D2F: 'Referenced from: 00402D25
  loc_00402D40: 'Referenced from: 00402D2D
  loc_00402D63: var_A0 = CStr(CInt((var_1A8 / global_401100)))
  loc_00402D69: var_A8 = 8
  loc_00402D73: var_88 = CStr(CInt((var_1A8 / global_401100)))
  loc_00402D8C: var_A0 = 4
  loc_00402D96: var_A8 = 2
  loc_00402DA0: var_8C = CStr(var_88)
  loc_00402DB9: var_B0 = Mid$(var_8C, 1, 4)
  loc_00402DBF: var_B8 = 8
  loc_00402DC9: var_88 = Mid$(var_8C, 1, 4)
  loc_00402DE6: CInt((var_8C + var_190)) = CInt((var_8C + var_190)) * 0008h
  loc_00402DF0: CInt((var_8C + var_190)) = CInt((var_8C + var_190)) + 0020h
  loc_00402DFD: var_1AC = CInt((var_8C + var_190))+0020h
  loc_00402E09: var_1B4 = var_1AC
  loc_00402E1C: If global_404000 <> 0 Then GoTo loc_00402E26
  loc_00402E24: GoTo loc_00402E37
  loc_00402E26: 'Referenced from: 00402E1C
  loc_00402E37: 'Referenced from: 00402E24
  loc_00402E57: var_A0 = CStr(CInt((var_1B4 / global_401100)))
  loc_00402E5D: var_A8 = 8
  loc_00402E67: var_68 = CStr(CInt((var_1B4 / global_401100)))
  loc_00402E7D: var_A0 = 4
  loc_00402E87: var_A8 = 2
  loc_00402E91: var_8C = CStr(var_68)
  loc_00402EA7: var_B0 = Mid$(var_8C, 1, 4)
  loc_00402EAD: var_B8 = 8
  loc_00402EB7: var_68 = Mid$(var_8C, 1, 4)
  loc_00402ED1: CInt((var_8C + var_190)) = CInt((var_8C + var_190)) * 0006h
  loc_00402EDB: CInt((var_8C + var_190)) = CInt((var_8C + var_190)) + 003Ch
  loc_00402EE8: var_1B8 = CInt((var_8C + var_190))+003Ch
  loc_00402EF4: var_1C0 = var_1B8
  loc_00402F07: If global_404000 <> 0 Then GoTo loc_00402F11
  loc_00402F0F: GoTo loc_00402F22
  loc_00402F11: 'Referenced from: 00402F07
  loc_00402F22: 'Referenced from: 00402F0F
  loc_00402F47: var_A0 = CStr(CInt((var_1C0 / global_401100)))
  loc_00402F4D: var_A8 = 8
  loc_00402F53: var_34 = CStr(CInt((var_1C0 / global_401100)))
  loc_00402F69: var_A0 = 4
  loc_00402F73: var_A8 = 2
  loc_00402F7D: var_8C = CStr(var_34)
  loc_00402F8A: var_B0 = Mid$(var_8C, 1, 4)
  loc_00402F90: var_B8 = 8
  loc_00402F9F: var_34 = Mid$(var_8C, 1, 4)
  loc_00402FC1: var_100 = &H401B68
  loc_00402FC7: var_110 = &H401B68
  loc_00402FCD: var_120 = &H401B68
  loc_00402FE0: var_108 = 8
  loc_00402FE6: var_118 = 8
  loc_00402FEC: var_128 = 8
  loc_00403057: var_38 = var_78 + &H401B68 + var_88 + &H401B68 + var_68 + &H401B68 + var_34
  loc_00403097: edi = ""
  loc_00403099: 'Referenced from: 0040286E
  loc_004030A7: If CBool(var_40) <> var_FFFFFF Then GoTo loc_004032C7
  loc_004030D4: var_8C = Text2.Text
  loc_004030DE: If var_8C >= 0 Then GoTo loc_004030F8
  loc_004030F2: var_8C = CheckObj(var_13C, global_00401AA8, 160)
  loc_004030F8: 'Referenced from: 004030DE
  loc_00403113: eax = (var_8C = var_38) + 1
  loc_00403116: var_144 = (var_8C = var_38) + 1
  loc_0040313A: var_D0 = 80020004h
  loc_00403140: var_D8 = 10
  loc_00403146: var_C0 = 80020004h
  loc_0040314C: var_C8 = 10
  loc_00403152: var_B0 = 80020004h
  loc_00403158: var_B8 = 10
  loc_0040315E: If var_144 = 0 Then GoTo loc_00403245
  loc_00403187: var_8C = Text1.Text
  loc_00403191: If var_8C >= 0 Then GoTo loc_004031A5
  loc_0040319F: var_8C = CheckObj(var_94, global_00401AA8, 160)
  loc_004031A5: 'Referenced from: 00403191
  loc_004031C1: var_90 = "Congrats " & var_8C
  loc_004031D5: var_A0 = var_90 & ", you got your serial right. Now make a keygen for this."
  loc_004031F2: var_A8 = 8
  loc_004031FC: MsgBox(var_90 & ", you got your serial right. Now make a keygen for this.", 0, var_B8, var_C8, var_D8)
  loc_00403243: GoTo loc_004032AA
  loc_00403245: 'Referenced from: 0040315E
  loc_00403265: var_A8 = "Sorry, try again."
  loc_00403288: MsgBox(var_A8, 0, var_B8, var_C8, var_D8)
  loc_004032AA: 'Referenced from: 00403243
  loc_004032B6: call __vbaStrBool(edi, var_A8, var_B8, var_C8, var_D8, var_94, global_80020004, arg_8, var_94, arg_8, arg_8, global_401100)
  loc_004032C1: var_40 = __vbaStrBool(edi, var_A8, var_B8, var_C8, var_D8, var_94, global_80020004, arg_8, var_94, arg_8, arg_8, global_401100)
  loc_004032C7: 'Referenced from: 004030A7
  loc_004032C7: var_4 = ""
  loc_004032D0: GoTo loc_00403334
  loc_00403333: Exit Sub
  loc_00403334: 'Referenced from: 004032D0
  loc_00403389: Exit Sub
End Sub
