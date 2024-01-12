// bad sp value at call has been detected, the output may be wrong!
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int v3; // ebx
  int v4; // edx
  int v5; // edx
  int v6; // ecx
  int v8; // edx
  int v9; // ecx
  int v10; // [esp+4h] [ebp-14h] BYREF
  int *v11; // [esp+8h] [ebp-10h]
  int *v12; // [esp+Ch] [ebp-Ch]
  int v13; // [esp+10h] [ebp-8h] BYREF

  MEMORY[0x460210](0x8007, v10, v11, v12, v13);
  0x801534();
  v10 = 0;
  v13 = 0x802bc7((int)&v10, v4, &v10, &v13);
  if ( !v10 )
    return 0;
  v13 = v5;
  if ( !v5 )
    return 0;
  v11 = (int *)0x80380d(v6, v5);
  v12 = (int *)0x80620d(v9, v8);
  v13 = v3;
  do_rc6(*v11, v3, *v11, *v11, *v12, *v11);
  0x800a74(v10, 0);
  return 0;
}

int __cdecl 0x800a74(int a1, _DWORD *a2)
{
  int v2; // edx
  _BYTE v4[264]; // [esp+178h] [ebp-190h] BYREF
  int v5; // [esp+280h] [ebp-88h]
  _DWORD v6[19]; // [esp+288h] [ebp-80h] BYREF
  int v7; // [esp+2D4h] [ebp-34h]
  _DWORD v8[6]; // [esp+2E0h] [ebp-28h] BYREF
  int v9; // [esp+2F8h] [ebp-10h]
  char v10; // [esp+2FEh] [ebp-Ah]
  char v11; // [esp+2FFh] [ebp-9h]
  int v12; // [esp+300h] [ebp-8h]

  ((void (__cdecl *)(int))MEMORY[0x46022C])(1000);
  v10 = *(_BYTE *)a1;
  v11 = *(_BYTE *)(a1 + 21);
  v12 = a1 + 1;
  if ( MEMORY[0x478374](0x1F0001, 0, a1 + 1) )
    MEMORY[0x460230](0);
  v9 = 0;
  if ( v11 )
  {
    v6[18] = *(_DWORD *)(a1 + 8 * v9 + 22);
    v8[5] = *(_DWORD *)(a1 + 8 * v9 + 26);
    0x800e2f(v6, 0, 68);
    v6[0] = 68;
    v7 = 0;
    v5 = 30;
    do
    {
      --v5;
      0x8021ab(v4, v9 == 0);
      v7 = MEMORY[0x478378](0, v4, 0, 0, 0, 4, 0, 0, v6, v8);
    }
    while ( !v7 && v5 > 0 );
    JUMPOUT(0x8004112);
  }
  return 0x802bc7(0, v2, (int *)a1, a2);
}

_BYTE *__cdecl 0x800e2f(_BYTE *a1, char a2, int a3)
{
  if ( a3 > 0 )
  {
    *a1 = a2;
    MEMORY[0x46022C](1000, 1);
    JUMPOUT(0x8002528);
  }
  return a1;
}

int 0x801534()
{
  unsigned __int16 v1; // [esp+0h] [ebp-8h]

  MEMORY[0x47838C]();
  return MEMORY[0x478390](v1, 0, 0);
}

// bad sp value at call has been detected, the output may be wrong!
_DWORD *__usercall do_rc6@<eax>(int a1@<ecx>, int a2@<ebx>, int *a3, int a4, int a5, unsigned int a6)
{
  int v6; // eax
  _DWORD *result; // eax
  int v8; // ecx
  int v9; // eax
  unsigned __int8 v10; // ecx^2
  char v11[268]; // [esp+0h] [ebp-2C8h] BYREF
  char v12[20]; // [esp+10Ch] [ebp-1BCh] BYREF
  int v13; // [esp+120h] [ebp-1A8h]
  char *v14; // [esp+124h] [ebp-1A4h]
  int v15; // [esp+128h] [ebp-1A0h]
  int v16; // [esp+12Ch] [ebp-19Ch]
  int v17; // [esp+130h] [ebp-198h]
  int v18; // [esp+240h] [ebp-88h]
  int v19; // [esp+2B8h] [ebp-10h]
  int v20; // [esp+2BCh] [ebp-Ch]
  int v21; // [esp+2C0h] [ebp-8h]
  _DWORD *s; // [esp+2C4h] [ebp-4h]

  v21 = 0x90;
  v19 = a1;
  v6 = MEMORY[0x478370](a1, 8);
  result = (_DWORD *)MEMORY[0x46021C](v6);
  s = result;
  v20 = a2;
  if ( result )
  {
    rc6(a6, s);
    0x8029c5(a3, a5, s);
    v21 = (int)s;
    v9 = MEMORY[0x478370](v8, 8);
    MEMORY[0x460218](v9);
    MEMORY[0x460398](0, v11, 260);
    v16 = (int)&a3[2 * HIBYTE(v20) + 5] + 2;
    v17 = 0xC0000000;
    MEMORY[0x4783C4](v12, 1);
    MEMORY[0x4783C8](v12, 1, 0, 1);
    v13 = 12;
    v14 = v12;
    v15 = 1;
    MEMORY[0x46022C](1000 * v10, v21);
    v20 = a2;
    v18 = 29;
    JUMPOUT(0x8003FAD);
  }
  return result;
}

int __cdecl 0x8021ab(int a1, int a2)
{
  char v3[16]; // [esp+6Ch] [ebp-10h] BYREF

  if ( !a2 )
    JUMPOUT(0x8002FAC);
  strcpy(v3, "Explorer.exe");
  return 0x802cff(a1, v3);
}

int 0x8026c1()
{
  return *(_DWORD *)(__readfsdword(0x30u) + 8);
}

void __cdecl 0x8029c5(int *a1, int a2, _DWORD *a3)
{
  char v3; // al
  char v4; // [esp+0h] [ebp-20h]
  char v5; // [esp+0h] [ebp-20h]
  char v6; // [esp+0h] [ebp-20h]
  int v7; // [esp+4h] [ebp-1Ch]
  int v8; // [esp+8h] [ebp-18h]
  int v9; // [esp+Ch] [ebp-14h]

  if ( a2 )
  {
    a1[1] += *a3;
    a1[3] += a3[1];
    v4 = and(5);
    v7 = rol(a1[1] * (2 * a1[1] + 1), v4);
    v5 = and(5);
    v9 = rol(a1[3] * (2 * a1[3] + 1), v5);
    v6 = and(v9);
    *a1 = a3[2] + rol(v7 ^ *a1, v6);
    v3 = and(v7);
    a1[2] = a3[3] + rol(v9 ^ a1[2], v3);
    v8 = *a1;
    *a1 = a1[1];
    a1[1] = a1[2];
    a1[2] = a1[3];
    a1[3] = v8;
    JUMPOUT(0x8000CE7);
  }
}

int __cdecl 0x802b3e(int a1, char a2)
{
  return __ROL4__(a1, a2);
}

int __fastcall 0x802bc7(int a1, int a2, int *a3, _DWORD *a4)
{
  int result; // eax
  int v5; // ecx
  int v6; // [esp+0h] [ebp-20h]
  int v7; // [esp+8h] [ebp-18h]
  int v8; // [esp+Ch] [ebp-14h]
  int v9; // [esp+10h] [ebp-10h]
  int v10; // [esp+18h] [ebp-8h]
  int v11; // [esp+1Ch] [ebp-4h]

  result = 0x8026c1(a1, a2);
  LOWORD(v5) = *(_WORD *)(result + 1000);
  if ( (_WORD)v5 )
  {
    v11 = MEMORY[0x4603D8](v5, 0, (unsigned __int16)v5, 2);
    v7 = MEMORY[0x4603E4](0, v11);
    v6 = MEMORY[0x4603DC](0, v11);
    v10 = MEMORY[0x4603E0](v6);
    result = MEMORY[0x46023C](0, v7, 12288, 64);
    v9 = result;
    v8 = result;
    if ( result )
    {
      0x80438f(result, v10, v7);
      *a3 = v9;
      *a4 = v7 + v8 - v9;
      return rc6();
    }
  }
  return result;
}

int __cdecl 0x802cff(int a1, int a2)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; *(_BYTE *)(i + a2); ++i )
    *(_BYTE *)(i + a1) = *(_BYTE *)(i + a2);
  *(_BYTE *)(i + a1) = 0;
  return a1;
}

int __fastcall 0x80380d(int a1, int a2)
{
  int v2; // eax

  v2 = 0x8026c1(a1, a2);
  if ( !v2 )
    JUMPOUT(0x80027F7);
  return v2 + 1020;
}

int __cdecl 0x80438f(_BYTE *a1, _BYTE *a2, int a3)
{
  if ( a3 <= 0 )
    return (int)a1;
  *a1 = *a2;
  MEMORY[1] += *(_DWORD *)(a3 + 136);
  MEMORY[9] += *(_DWORD *)(a3 + 140);
  return 0x80620d(1, MEMORY[9]);
}

int __cdecl rc6(unsigned int a1, _DWORD *s)
{
  int result; // eax
  char v3; // [esp+29Ch] [ebp-30h]
  char v4; // [esp+29Ch] [ebp-30h]
  int j; // [esp+2A0h] [ebp-2Ch]
  int v6; // [esp+2A4h] [ebp-28h]
  unsigned int v7; // [esp+2B0h] [ebp-1Ch]
  unsigned int i; // [esp+2B4h] [ebp-18h]
  unsigned int v9; // [esp+2B4h] [ebp-18h]
  unsigned int v10; // [esp+2D4h] [ebp+8h]

  v10 = (a1 << 24) | ((_WORD)a1 << 8) & 0x100 | (a1 >> 8) & 0x10 | HIBYTE(a1);
  *s = 0xB7E15163;
  for ( i = 1; i < 0x24; ++i )
    s[i] = s[i - 1] - 0x61C88647;
  v7 = 0;
  v6 = 0;
  v9 = 0;
  for ( j = 1; ; ++j )
  {
    result = j;
    if ( j > 0x6C )
      break;
    v3 = and(3);
    s[v9] = rol(v7 + v6 + s[v9], v3);
    v6 = s[v9];
    v4 = and(v7 + v6);
    v10 = rol(v7 + v6 + v10, v4);
    v7 = v10;
    v9 = (v9 + 1) % 0x24;
  }
  return result;
}

int __fastcall 0x80620d(int a1, int a2)
{
  __int64 v3; // rax
  int v4; // ecx

  v3 = 0x8026c1(a1, a2);
  if ( (_DWORD)v3 )
    return v3 + 1016;
  else
    return 0x8026c1(v4, HIDWORD(v3));
}

int __cdecl 0x8064e7(char a1)
{
  return a1 & 0x1F;
}
