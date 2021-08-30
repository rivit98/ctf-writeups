unsigned __int64 sub_400F0F()
{
  unsigned __int64 result; // rax
  unsigned int i; // [rsp+Ch] [rbp-54h]
  char v2[40]; // [rsp+20h] [rbp-40h]
  unsigned __int64 v3; // [rsp+48h] [rbp-18h]

  v3 = __readfsqword(0x28u);
  v2[0] = 0;
  v2[1] = 0;
  v2[2] = 0;
  v2[3] = 0;
  v2[4] = 0;
  v2[5] = 0;
  v2[6] = 0;
  v2[7] = 0;
  v2[8] = 0;
  v2[9] = 0;
  v2[10] = 0;
  v2[11] = 0;
  v2[12] = 0;
  v2[13] = 27;
  v2[14] = 25;
  v2[15] = 10;
  v2[16] = 6;
  v2[17] = 58;
  v2[18] = 44;
  v2[19] = 27;
  v2[20] = 9;
  v2[21] = 12;
  v2[22] = 8;
  v2[23] = 58;
  v2[24] = 48;
  v2[25] = 1;
  v2[26] = 49;
  v2[27] = 38;
  v2[28] = 2;
  v2[29] = 16;
  v2[30] = 0;
  for ( i = 0; i <= 30; ++i )
    *((_BYTE *)&unk_4D3E30 + (int)i + 0x20) = xor(*((_BYTE *)&unk_4D3E30 + (int)i + 0x20), v2[i]);
  *((_BYTE *)main + 0x57) -= 0x1A;
  result = __readfsqword(0x28u) ^ v3;
  if ( result )
    stack_check_fail();
  return result;
}
