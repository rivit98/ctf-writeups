https://github.com/jthuraisamy/SysWhispers2.git

Stack[000018F4]:000000000008F9E8 dd 9FCC0h   ZwRaiseException


Stack[000018F4]:000000000008F9EC dd 4B966903h
Stack[000018F4]:000000000008F9F0 dd 9FCE0h    ZwRaiseHardError


v4 = 0;
v5 = (int *)v3;
v6 = v3 + 2;
v7 = 4i64;
do
{
  v8 = *(unsigned __int8 *)(v6 - 2);
  v9 = *(unsigned __int8 *)(v6 - 1);
  v6 += 4i64;
  v10 = (v8 + __ROL4__(v4, 7)) ^ v4;
  v11 = (v9 + __ROL4__(v10, 7)) ^ v10;
  v12 = (*(unsigned __int8 *)(v6 - 4) + __ROL4__(v11, 7)) ^ v11;
  v4 = (*(unsigned __int8 *)(v6 - 3) + __ROL4__(v12, 7)) ^ v12;
  --v7;
}
while ( v7 );




Stack[00000700]:000000000008FDE0 dd 72616C66h
Stack[00000700]:000000000008FDE4 dd 31713433h
Stack[00000700]:000000000008FDE8 dd 0CE8ECBCCh
Stack[00000700]:000000000008FDEC dd 31713433h

Stack[00000700]:000000000008FDF0 dd 17134333h
Stack[00000700]:000000000008FDF4 dd 6F6E2D65h
Stack[00000700]:000000000008FDF8 dd 17134333h
Stack[00000700]:000000000008FDFC dd 0E8ECBCCCh

Stack[00000700]:000000000008FE00 dd 939ACABCh
Stack[00000700]:000000000008FE04 dd 6C653543h
Stack[00000700]:000000000008FE08 dd 6B636F72h
Stack[00000700]:000000000008FE0C dd 6C653543h

Stack[00000700]:000000000008FE10 dd 96536327h
Stack[00000700]:000000000008FE14 dd 69AC9CD8h
Stack[00000700]:000000000008FE18 dd 96536327h
Stack[00000700]:000000000008FE1C dd 21212173h


DOS:

r = reroll
arrows - select


konami code on first screen gives fixed seed

looks for 0x37 * 0x10 in binary and replaces pos+5 with your input
maybe 0xcc * 0x10

486124687461675F6E305F7263345F614E645F5468336E5F73306D6540666C6172652D6F6E2E636F6D

Ha$htag_n0_rc4_aNd_Th3n_s0me@flare-on.com
