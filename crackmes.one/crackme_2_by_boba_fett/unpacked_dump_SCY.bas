' Compiled to: P-Code
' Compiler version: 8176

'Object: Kanel

Private Sub nm_Timer() '404768
  'Data Table: 401FB8
  loc_40475F: Me.nm.Interval = 0
  loc_404767: Exit Sub
End Sub

Private Sub ct_Change() '404BD8
  'Data Table: 401FB8
  loc_404B98: If (Me.ct.Text = "Ex") Then
  loc_404B9B:   End
  loc_404BA0: Else
  loc_404BC0:   If (Me.ct.Text = "Ab") Then
  loc_404BD1:     df.Show var_9C, var_AC
  loc_404BD6:   End If
  loc_404BD6: End If
  loc_404BD6: Exit Sub
End Sub

Private Sub ct_GotFocus() '404948
  'Data Table: 401FB8
  loc_404928: Me.nm.Enabled = False
  loc_40493D: Me.ct.Text = vbNullString
  loc_404945: Exit Sub
End Sub

Private Sub Form_Load() '4065DC
  'Data Table: 401FB8
  Dim var_88 As TextBox
  loc_4057C2: var_88 = Me.Global.Screen
  loc_4057E1: Kanel.Left = ((Screen.Width - Kanel.Width) / CDbl(2))
  loc_405803: var_88 = Me.Global.Screen
  loc_405822: Kanel.Top = ((Screen.Width - Kanel.Height) / CDbl(2))
  loc_405835: Me.Show var_A0, var_B0
  loc_405860: Me.ct.Text = Me.ct.Text & "G"
  loc_405878: Call Wait(2)
  loc_4058A6: Me.ct.Text = Me.ct.Text & "o"
  loc_4058BE: Call Wait(2)
  loc_4058EC: Me.ct.Text = Me.ct.Text & "o"
  loc_405904: Call Wait(2)
  loc_405932: Me.ct.Text = Me.ct.Text & "d"
  loc_40594A: Call Wait(2)
  loc_405978: Me.ct.Text = Me.ct.Text & " "
  loc_405990: Call Wait(2)
  loc_4059BE: Me.ct.Text = Me.ct.Text & "w"
  loc_4059D6: Call Wait(2)
  loc_405A04: Me.ct.Text = Me.ct.Text & "o"
  loc_405A1C: Call Wait(2)
  loc_405A4A: Me.ct.Text = Me.ct.Text & "r"
  loc_405A62: Call Wait(2)
  loc_405A90: Me.ct.Text = Me.ct.Text & "k"
  loc_405AA8: Call Wait(2)
  loc_405AD6: Me.ct.Text = Me.ct.Text & "!"
  loc_405AEE: Call Wait(2)
  loc_405B1C: Me.ct.Text = Me.ct.Text & " "
  loc_405B34: Call Wait(2)
  loc_405B62: Me.ct.Text = Me.ct.Text & "T"
  loc_405B7A: Call Wait(2)
  loc_405BA8: Me.ct.Text = Me.ct.Text & "y"
  loc_405BC0: Call Wait(2)
  loc_405BEE: Me.ct.Text = Me.ct.Text & "p"
  loc_405C06: Call Wait(2)
  loc_405C34: Me.ct.Text = Me.ct.Text & "e"
  loc_405C4C: Call Wait(2)
  loc_405C7A: Me.ct.Text = Me.ct.Text & " "
  loc_405C92: Call Wait(2)
  loc_405CC0: Me.ct.Text = Me.ct.Text & "E"
  loc_405CD8: Call Wait(2)
  loc_405D06: Me.ct.Text = Me.ct.Text & "x"
  loc_405D1E: Call Wait(2)
  loc_405D4C: Me.ct.Text = Me.ct.Text & " "
  loc_405D64: Call Wait(2)
  loc_405D92: Me.ct.Text = Me.ct.Text & "t"
  loc_405DAA: Call Wait(2)
  loc_405DD8: Me.ct.Text = Me.ct.Text & "o"
  loc_405DF0: Call Wait(2)
  loc_405E1E: Me.ct.Text = Me.ct.Text & " "
  loc_405E36: Call Wait(2)
  loc_405E64: Me.ct.Text = Me.ct.Text & "E"
  loc_405E7C: Call Wait(2)
  loc_405EAA: Me.ct.Text = Me.ct.Text & "x"
  loc_405EC2: Call Wait(2)
  loc_405EF0: Me.ct.Text = Me.ct.Text & "i"
  loc_405F08: Call Wait(2)
  loc_405F36: Me.ct.Text = Me.ct.Text & "t"
  loc_405F4E: Call Wait(2)
  loc_405F7C: Me.ct.Text = Me.ct.Text & " "
  loc_405F94: Call Wait(2)
  loc_405FC2: Me.ct.Text = Me.ct.Text & "o"
  loc_405FDA: Call Wait(2)
  loc_406008: Me.ct.Text = Me.ct.Text & "r"
  loc_406020: Call Wait(2)
  loc_40604E: Me.ct.Text = Me.ct.Text & " "
  loc_406066: Call Wait(2)
  loc_406094: Me.ct.Text = Me.ct.Text & "A"
  loc_4060AC: Call Wait(2)
  loc_4060DA: Me.ct.Text = Me.ct.Text & "b"
  loc_4060F2: Call Wait(2)
  loc_406120: Me.ct.Text = Me.ct.Text & " "
  loc_406138: Call Wait(2)
  loc_406166: Me.ct.Text = Me.ct.Text & "f"
  loc_40617E: Call Wait(2)
  loc_4061AC: Me.ct.Text = Me.ct.Text & "o"
  loc_4061C4: Call Wait(2)
  loc_4061F2: Me.ct.Text = Me.ct.Text & "r"
  loc_40620A: Call Wait(2)
  loc_406238: Me.ct.Text = Me.ct.Text & " "
  loc_406250: Call Wait(2)
  loc_40627E: Me.ct.Text = Me.ct.Text & "t"
  loc_406296: Call Wait(2)
  loc_4062C4: Me.ct.Text = Me.ct.Text & "h"
  loc_4062DC: Call Wait(2)
  loc_40630A: Me.ct.Text = Me.ct.Text & "e"
  loc_406322: Call Wait(2)
  loc_406350: Me.ct.Text = Me.ct.Text & " "
  loc_406368: Call Wait(2)
  loc_406396: Me.ct.Text = Me.ct.Text & "a"
  loc_4063AE: Call Wait(2)
  loc_4063DC: Me.ct.Text = Me.ct.Text & "b"
  loc_4063F4: Call Wait(2)
  loc_406422: Me.ct.Text = Me.ct.Text & "o"
  loc_40643A: Call Wait(2)
  loc_406468: Me.ct.Text = Me.ct.Text & "u"
  loc_406480: Call Wait(2)
  loc_4064AE: Me.ct.Text = Me.ct.Text & "t"
  loc_4064C6: Call Wait(2)
  loc_4064F4: Me.ct.Text = Me.ct.Text & " "
  loc_40650C: Call Wait(2)
  loc_40653A: Me.ct.Text = Me.ct.Text & "b"
  loc_406552: Call Wait(2)
  loc_406580: Me.ct.Text = Me.ct.Text & "o"
  loc_406598: Call Wait(2)
  loc_4065C6: Me.ct.Text = Me.ct.Text & "x"
  loc_4065D9: Exit Sub
End Sub

Public Sub Wait(seconds) '404D2C
  'Data Table: 401FB8
  loc_404CBC: Me.nm.Enabled = True
  loc_404CE1: Me.nm.Interval = CLng((28 * seconds))
  loc_404CE9: ' Referenced from: 404D11
  loc_404D09: If (Me.nm.Interval > 0) Then
  loc_404D0C:   DoEvents()
  loc_404D11:   GoTo loc_404CE9
  loc_404D14: End If
  loc_404D20: Me.nm.Enabled = False
  loc_404D28: Exit Sub
End Sub

'Object: Homo

Private Sub we_Click() '405704
  'Data Table: 401CB0
  Dim var_88 As Variant
  Dim var_1A8 As Variant
  Dim var_1AC As String
  Dim var_23C As Integer
  Dim var_1FC As Variant

  loc_4054C3: var_F8 = 15 + (CVar(Val(NAME_FIELD_TEXT)) * 100) 'Variant
  loc_405653: var_168 = Left(Val(SERIAL_STAGE1), 3) 'Variant
  
  loc_405661: var_128 = SERIAL_STAGE2 * var_168 'Variant
  loc_40567F: var_178 = ((var_F8 * var_168) - 18) 'Variant
  loc_405693: If var_128 >= var_178 Then
  loc_4056DD:   If Val(CStr(var_128)) <= var_178 Then
  loc_4056E3:     Me.Hide
  loc_4056F6:     Kanel.Show var_1A8, 57
End Sub

Private Sub Form_Load() '404F58
  'Data Table: 401CB0
  loc_404EEE: var_88 = Me.Global.Screen
  loc_404F0D: Homo.Left = ((Screen.Width - Homo.Width) / CDbl(2))
  loc_404F2F: var_88 = Me.Global.Screen
  loc_404F4E: Homo.Top = ((Screen.Width - Homo.Height) / CDbl(2))
  loc_404F56: Exit Sub
End Sub

Private Sub Proc_1_2_4047C4
  'Data Table: 401CB0
  loc_4047BC: If (input_box.Text = vbNullString) Then
  loc_4047BF:   End
  loc_4047C1: End If
  loc_4047C1: Exit Sub
End Sub

'Object: blot

Private Sub ji_Click() '405378
  'Data Table: 402384
  Dim var_168 As Variant
  loc_40511D: Me.cmdWelcome.Caption = "Time to test"
  loc_40512A: var_98 = 112 'Variant
  loc_405133: var_A8 = 1564 'Variant
  loc_40513C: var_B8 = 1464 'Variant
  loc_40515A: name_field_len = CVar(Len(name_field.Text)) 'Variant
  loc_405185: If Not((name_field.Text = "Ab")) Then
  loc_40518D:   i = 0 'Variant
  loc_4051A9:   var_19C = CVar(name_field.Text) 'Variant
  loc_4051B0:   ' Referenced from: 405246
  loc_4051C3:   If CBool(Not (var_19C = vbNullString)) Then
  loc_4051D2:     i = (i + 1) 'Variant
  loc_405224:     var_1FC = (var_1FC + CVar(Asc(CStr(Left(Left(var_19C, CLng(i)), 1))))) 'Variant
  loc_405242:     var_19C = Right(var_19C, CLng((name_field_len - i))) 'Variant
  loc_405246:     GoTo loc_4051B0
  loc_405249:   End If

  loc_405252:   If (var_1FC = CVar(Asc(CStr(Left(Left(var_19C, CLng(i)), 1))))) Then
  loc_405255:     End
  loc_405257:     GoTo loc_40525A
  loc_40525A:     ' Referenced from: 405257
  loc_40525A:   End If

' sth is broken with decompiler, var_E8 should be on the -10 place....
  loc_405290:   var_108 = (((var_98 * var_A8) Xor var_B8 - var_E8) - 10) 'Variant
  loc_40529E:   var_128 = (var_108 * var_1FC) 'Variant
  loc_4052D4:   var_148 = (CVar(Val(serial_field.Text)) * var_108) 'Variant
  loc_4052E1:   If (var_148 = CVar(Val(serial_field.Text))) Then
  loc_4052E4:     End
  loc_4052E9:   Else
  loc_4052F9:     If CBool(Not (var_148 < var_128)) Then
  loc_40530F:       var_168 = 11
  loc_40532C:       If CBool(Not ((var_148 + var_168) > (var_128 + 11))) Then
  loc_405332:         Me.Hide
  loc_405345:         Homo.Show var_168, var_20C
  loc_40534A:         Exit Sub
  loc_40534B:       End If
  loc_40534B:       End
  loc_40535B:       df.Show var_168, var_20C
  loc_405360:     End If
  loc_405360:   End If
  loc_405360:   End
  loc_405362: End If
  loc_405370: Me.Show var_168, var_20C
  loc_405375: Exit Sub
End Sub

Private Sub ji_GotFocus() '404C78
  'Data Table: 402384
  loc_404C1C: Me.cmdWelcome.Visible = True
  loc_404C31: Me.cmdWelcome.Caption = "Time to test"
  loc_404C45: Me.cmdWelcome.Enabled = True
  loc_404C6D: If (name_field.Text = vbNullString) Then
  loc_404C70:   End
  loc_404C72:   GoTo loc_404C75
  loc_404C75:   ' Referenced from: 404C72
  loc_404C75: End If
  loc_404C75: Exit Sub
End Sub

Private Sub sh_GotFocus() '404ABC
  'Data Table: 402384
  loc_404A75: serial_field.Text = vbNullString
  loc_404A89: Me.cmdWelcome.Visible = True
  loc_404A9E: Me.cmdWelcome.Caption = "Welcome"
  loc_404AB2: Me.cmdWelcome.Enabled = True
  loc_404ABA: Exit Sub
End Sub

Private Sub sh_Click() '4049BC
  'Data Table: 402384
  loc_404988: Me.cmdWelcome.Visible = True
  loc_40499D: Me.cmdWelcome.Caption = "Welcome"
  loc_4049B1: Me.cmdWelcome.Enabled = True
  loc_4049B9: Exit Sub
End Sub

Private Sub lk_GotFocus() '404B44
  'Data Table: 402384
  loc_404AFD: name_field.Text = vbNullString
  loc_404B11: Me.cmdWelcome.Visible = True
  loc_404B26: Me.cmdWelcome.Caption = "Welcome"
  loc_404B3A: Me.cmdWelcome.Enabled = True
  loc_404B42: Exit Sub
End Sub

Private Sub lk_Click() '404888
  'Data Table: 402384
  loc_404868: Me.cmdWelcome.Visible = True
  loc_40487C: Me.cmdWelcome.Enabled = True
  loc_404884: Exit Sub
End Sub

Private Sub hg_Click() '404374
  'Data Table: 402384
  loc_404370: End
  loc_404372: Exit Sub
End Sub

Private Sub hg_GotFocus() '404828
  'Data Table: 402384
  loc_404808: Me.cmdWelcome.Visible = True
  loc_40481D: Me.cmdWelcome.Caption = "Bye"
  loc_404825: Exit Sub
End Sub

Private Sub hg_MouseDown(Button As Integer, Shift As Integer, X As Single, Y As Single) '4048E8
  'Data Table: 402384
  loc_4048C8: Me.cmdWelcome.Visible = True
  loc_4048DC: Me.cmdWelcome.Enabled = False
  loc_4048E4: Exit Sub
End Sub

Private Sub Form_Load() '4050DC
  'Data Table: 402384
  Dim var_88 As CommandButton
  loc_40505E: var_88 = Me.Global.Screen
  loc_40507D: blot.Left = ((Screen.Width - blot.Width) / CDbl(2))
  loc_40509F: var_88 = Me.Global.Screen
  loc_4050BE: blot.Top = ((Screen.Width - blot.Height) / CDbl(2))
  loc_4050D2: Me.cmdWelcome.Visible = False
  loc_4050DA: Exit Sub
End Sub

'Object: df

Private Sub gk1_Click() '404464
  'Data Table: 4029EC
  loc_40445B: Me.Hide
  loc_404460: Exit Sub
End Sub

Private Sub hh_Click() '404720
  'Data Table: 4029EC
  loc_40471A: ok.Show var_94, var_A4
  loc_40471F: Exit Sub
End Sub

Private Sub hj_Click() '404428
  'Data Table: 4029EC
  loc_40441F: Me.Hide
  loc_404424: Exit Sub
End Sub

Private Sub fg_Click() '4043B0
  'Data Table: 4029EC
  loc_4043A7: Me.Hide
  loc_4043AC: Exit Sub
End Sub

Private Sub gg_Click() '4046DC
  'Data Table: 4029EC
  loc_4046D6: jj.Show var_94, var_A4
  loc_4046DB: Exit Sub
End Sub

Private Sub gk_Click() '4044A0
  'Data Table: 4029EC
  loc_404497: Me.Hide
  loc_40449C: Exit Sub
End Sub

Private Sub as1_Click() '4044DC
  'Data Table: 4029EC
  loc_4044D3: Me.Hide
  loc_4044D8: Exit Sub
End Sub

Private Sub Form_Load() '404DE8
  'Data Table: 4029EC
  loc_404D7E: var_88 = Me.Global.Screen
  loc_404D9D: df.Left = ((Screen.Width - df.Width) / CDbl(2))
  loc_404DBF: var_88 = Me.Global.Screen
  loc_404DDE: df.Top = ((Screen.Width - df.Height) / CDbl(2))
  loc_404DE6: Exit Sub
End Sub

Private Sub Form_Click() '404518
  'Data Table: 4029EC
  loc_40450F: Me.Hide
  loc_404514: Exit Sub
End Sub

Private Sub as2_Click() '4043EC
  'Data Table: 4029EC
  loc_4043E3: Me.Hide
  loc_4043E8: Exit Sub
End Sub

'Object: ok

Private Sub Form_Load() '404EA0
  'Data Table: 40164C
  loc_404E36: var_88 = Me.Global.Screen
  loc_404E55: ok.Left = ((Screen.Width - ok.Width) / CDbl(2))
  loc_404E77: var_88 = Me.Global.Screen
  loc_404E96: ok.Top = ((Screen.Width - ok.Height) / CDbl(2))
  loc_404E9E: Exit Sub
End Sub

'Object: jj

Private Sub Form_Load() '405010
  'Data Table: 401860
  loc_404FA6: var_88 = Me.Global.Screen
  loc_404FC5: jj.Left = ((Screen.Width - jj.Width) / CDbl(2))
  loc_404FE7: var_88 = Me.Global.Screen
  loc_405006: jj.Top = ((Screen.Width - jj.Height) / CDbl(2))
  loc_40500E: Exit Sub
End Sub

