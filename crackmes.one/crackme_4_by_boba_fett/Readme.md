[Challenge](https://crackmes.one/crackme/5ab77f5333c5d40ad448c0d1)

## Solution
Binary is packed with UPX and Aspack, so we have to unpack it.
* [AspackDie](https://www.aldeid.com/wiki/AspackDie)
* For UPX unpacking I used x32dbg + Scylla plugin and dumped PE after code unpacked itself.

Quick analysis and we know that binary is using Visual Basic. VB Decompiler Lite gives us disassembled functions (our target is login button handler). I used some tool with `vitamine` and got decompiled VB code ;)

```c
Private Sub jk_Click() '402C38
  'Data Table: 401DD4
  loc_402A73: If ((Me.we.Text = vbNullString) Or (Me.er.Text = vbNullString)) Then
  loc_402A76:   End
  loc_402A7B: Else
  loc_402A90:   var_88 = Me.we.Text
  loc_402ABF:   var_8C = CStr(Asc(CStr(Left(var_88, 1))))
  loc_402AEB:   var_9C = CStr(Asc(CStr(Right(var_88, 1))))
  loc_402B17:   var_A0 = CStr(Asc(CStr(Right(var_88, 2))))
  loc_402B33:   var_98 = CStr((CDbl(var_8C & var_9C & var_A0) + CDbl(1)))
  loc_402B56:   var_9C = CStr((CDbl(var_8C & var_9C & var_A0) - CDbl(1)))
  loc_402B80:   If (var_98 > Me.er.Text) Then
  loc_402BA3:     If (var_9C < Me.er.Text) Then
  loc_402BEC:       Me.io.Caption = "This CrackMe is Registered to:   " & Me.we.Text & " " & Me.rt.Text
  loc_402C0A:     Else
  loc_402C17:       Me.io.Caption = "This CrackMe is:     UnRegistered"
  loc_402C1F:     End If
  loc_402C1F:     Exit Sub
  loc_402C20:   End If
  loc_402C2D:   Me.io.Caption = "This CrackMe is:   UnRegistered"
  loc_402C35:   Exit Sub
  loc_402C36: End If
  loc_402C36: Exit Sub
End Sub
```

`Me.io` - label with text "This CrackMe is Registered to..." \
`Me.we` - name \
`Me.er` - serial \
`Me.rt` - company

As we can see the serial for our name is concatenated decimal ascii values of first char of name and two last chars (but reversed).
e.g.
name - "ABCDEFG"
serial = "657170"
company - doesn't matter


