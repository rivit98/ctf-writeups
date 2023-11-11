#include <defs.h>


//-------------------------------------------------------------------------
// Function declarations

__int64 __fastcall switch(__int64);
__int64 pop_rax();


//----- (0000000000408E50) ----------------------------------------------------
// positive sp value has been detected, the output may be wrong!
__int64 __fastcall switch(__int64 a1)
{
  _BYTE *v1; // rbx
  _BYTE *v2; // rbp
  _BYTE *v3; // rdi
  char v5; // r12
  _BYTE *v7; // rax
  _BYTE *v8; // rcx
  char v9; // sp
  unsigned __int64 v11; // rax
  __int64 v12; // r8
  _BYTE *v13; // rcx

  switch ( a1 )
  {
    case 1i64:
      pop_rax();
      JUMPOUT(0x408E85i64);
    case 2i64:
      v7 = (_BYTE *)pop_rax();
      *v8 += v9;
      LOBYTE(v7) = 0;
      *v3 += BYTE1(v7);
      *_RSI += BYTE1(v8);
      *v7 = *v7;
      *_RDX += BYTE1(_RDX);
      v11 = *(unsigned int *)v7;
      *v8 += BYTE1(v11);
      *(_BYTE *)(v11 + v12 + 95) += v5;
      *(_BYTE *)(2 * v11 + 0x68) += (_BYTE)_RDX;
      *v1 += BYTE1(_RDX);
      *_RSI += BYTE1(v8);
      *v1 += BYTE1(_RDX);
      *(_BYTE *)v11 ^= v11;
      __asm { test    al, 0A6h }
      *v2 += BYTE1(v11);
      *_RSI += v9;
      __asm { db  17h }
      *v8 += BYTE1(v11);
      __addgsbyte(0x6E40FDE9u, BYTE1(v8));
      *_RSI += BYTE1(v8);
      *v1 += BYTE1(v11);
      __asm { add     eax, 63098E52h }
      *v2 += BYTE1(v8);
      JUMPOUT(0x408EF2i64);
    case 3i64:
      pop_rax();
      *v13 += BYTE1(v13);
      __asm { outsb }
      *_RSI += BYTE1(v13);
      JUMPOUT(0x408F01i64);
  }
  return 0i64;
}
// 408ECF: positive sp value 18 has been found
// 408E80: control flows out of bounds to 408E85
// 408EEF: control flows out of bounds to 408EF2
// 408EFE: control flows out of bounds to 408F01
// 408EA0: variable 'v9' is possibly undefined
// 408EA0: variable 'v8' is possibly undefined
// 408EAB: variable 'v3' is possibly undefined
// 408EAF: variable '_RSI' is possibly undefined
// 408EB5: variable '_RDX' is possibly undefined
// 408EC0: variable 'v5' is possibly undefined
// 408EC0: variable 'v12' is possibly undefined
// 408EC9: variable 'v1' is possibly undefined
// 408ED5: variable 'v2' is possibly undefined
// 408EFA: variable 'v13' is possibly undefined

//----- (0000000000408E6A) ----------------------------------------------------
// positive sp value has been detected, the output may be wrong!
__int64 sub_408E6A()
{
  __int64 v1; // [rsp-8h] [rbp-8h]

  return v1;
}
// 408E6B: positive sp value 8 has been found
// 408E6A: variable 'v1' is possibly undefined

//----- (0000000000408E95) ----------------------------------------------------
__int64 sub_408E95()
{
  return 84i64;
}

//----- (0000000000408F10) ----------------------------------------------------
void *__fastcall memset_wrapper(void *a1, char a2, unsigned __int64 a3)
{
  if ( a3 )
    memset(a1, a2, a3);
  return a1;
}

//----- (0000000000408F40) ----------------------------------------------------
int __cdecl main(int argc, const char **argv, const char **envp)
{
  __int64 v3; // rax
  int v4; // ecx
  int *key; // rdi
  __int64 v6; // r9
  __int64 v7; // r10
  int v8; // edx
  int v9; // eax
  int v10; // ecx
  int v11; // ecx
  int v12; // ecx
  unsigned int data_len; // ebx
  _BYTE *v14; // rax
  __int64 v15; // rbx
  __int64 v16; // rax
  __int64 v18; // [rsp+30h] [rbp-48h] BYREF
  __int64 dest[2]; // [rsp+40h] [rbp-38h] BYREF
  __int64 v20[5]; // [rsp+50h] [rbp-28h] BYREF
  char v21; // [rsp+80h] [rbp+8h] BYREF

  v3 = switch(1i64);
  v4 = 0;
  key = (int *)v3;
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
  if ( v4 == 0x31D9F5FF )
  {
    data_len = set_rax_const();
    v14 = (_BYTE *)switch(2i64);
    decode_sth(key, v14, data_len);
    v15 = switch(2i64);
    v16 = switch(3i64);
    RtlInitUnicodeString((__int64)dest, v16);
    RtlInitUnicodeString((__int64)&v18, v15);
    v20[2] = '0';
    v20[0] = (__int64)&v18;
    v20[1] = (__int64)dest;
    v20[3] = 0xFFFFFFFFi64;
    ((void (__fastcall *)(__int64, __int64, __int64, __int64 *, _DWORD, char *))MessageBox)(
      0x50000018i64,
      4i64,
      3i64,
      v20,
      0,
      &v21);
  }
  return 0;
}

//----- (0000000000409070) ----------------------------------------------------
void __fastcall decode_sth(int *key, _BYTE *ciphertext, unsigned int data_len)
{
  int BeingDebugged; // r9d
  unsigned int idx; // ebx
  uint32_t key2_rol; // r13d
  __int64 v7; // rdi
  int key0; // [rsp+20h] [rbp-79h]
  uint32_t key0_rol; // [rsp+24h] [rbp-75h]
  uint32_t key1_rol; // [rsp+28h] [rbp-71h]
  uint32_t in[16]; // [rsp+30h] [rbp-69h] BYREF
  uint8_t v12[32]; // [rsp+70h] [rbp-29h] BYREF
  uint32_t out[16]; // [rsp+90h] [rbp-9h] BYREF

  BeingDebugged = NtCurrentPeb()->BeingDebugged;
  idx = 0;
  key0 = *key;
  memset(v12, 0, sizeof(v12));
  key0_rol = __ROL4__(
               key0,
               (NtCurrentPeb()->BeingDebugged + 1) << ((BeingDebugged + 1) << (NtCurrentPeb()->BeingDebugged + 1)));
  key1_rol = __ROL4__(
               key[1],
               (NtCurrentPeb()->BeingDebugged + 1) << (((NtCurrentPeb()->BeingDebugged + 1) << (NtCurrentPeb()->BeingDebugged
                                                                                              + 1))
                                                     + NtCurrentPeb()->BeingDebugged
                                                     + 1));
  key2_rol = __ROL4__(
               key[2],
               ((NtCurrentPeb()->BeingDebugged + 1) << ((NtCurrentPeb()->BeingDebugged + 1) << (NtCurrentPeb()->BeingDebugged
                                                                                              + 1)))
             * (((NtCurrentPeb()->BeingDebugged + 1) << (NtCurrentPeb()->BeingDebugged + 1))
              + NtCurrentPeb()->BeingDebugged
              + 1));
  if ( data_len )
  {
    do
    {
      v7 = idx & 0x8000001F;
      if ( (idx & 0x8000001F) == 0 )
      {
        in[0] = 'ralf';
        in[1] = key0;
        in[3] = idx ^ key0;
        in[6] = key0_rol;
        in[11] = key1_rol;
        in[2] = ~key0;
        in[5] = 'on-e';
        in[10] = 'kcor';
        in[12] = key2_rol;
        in[4] = idx ^ key0_rol;
        in[15] = '!!!s';
        in[7] = ~key0_rol;
        in[8] = ~key1_rol;
        in[9] = idx ^ key1_rol;
        in[13] = ~key2_rol;
        in[14] = idx ^ key2_rol;
        memset(out, 0, 32);
        salsa20_block(out, in);
        *(_OWORD *)v12 = *(_OWORD *)out;
        *(_OWORD *)&v12[16] = *(_OWORD *)&out[4];
      }
      ++idx;
      *ciphertext++ ^= v12[v7];
    }
    while ( idx < data_len );
  }
}

//----- (00000000004092D0) ----------------------------------------------------
void __fastcall salsa20_block(uint32_t *out, uint32_t *a2)
{
  unsigned int v2; // r11d
  __m128i v3; // xmm0
  __m128i v4; // xmm1
  int v5; // r13d
  __int32 v6; // esi
  __m128i v7; // xmm0
  __int32 v8; // r9d
  int v9; // ebx
  __int32 v10; // r14d
  __int32 v11; // r15d
  int v12; // r12d
  __int32 v13; // r10d
  int v14; // edx
  __int32 v15; // edi
  __int32 v16; // eax
  int v17; // r8d
  int v18; // edx
  int v19; // r9d
  int v20; // ecx
  __int32 v21; // ecx
  int v22; // r8d
  int v23; // r9d
  int v24; // edx
  int v25; // ecx
  __int64 v26; // rdx
  __m128i *v27; // rax
  __m128i v28; // xmm0
  __m128i v29; // xmm1
  __m128i v30; // xmm0
  int v31; // [rsp+0h] [rbp-58h]
  int v32; // [rsp+4h] [rbp-54h]
  int v33; // [rsp+8h] [rbp-50h]
  __m128i v34; // [rsp+10h] [rbp-48h] BYREF
  __m128i v35; // [rsp+20h] [rbp-38h]
  __m128i v36; // [rsp+30h] [rbp-28h]
  __m128i v37; // [rsp+40h] [rbp-18h]
  __int32 v40; // [rsp+B0h] [rbp+58h]
  int v41; // [rsp+B8h] [rbp+60h]

  v2 = 0;
  v3 = *(__m128i *)a2;
  v35 = *((__m128i *)a2 + 1);
  v4 = *((__m128i *)a2 + 3);
  v5 = v35.m128i_i32[2];
  v6 = v35.m128i_i32[1];
  v34 = v3;
  v7 = *((__m128i *)a2 + 2);
  v8 = v34.m128i_i32[3];
  v9 = v34.m128i_i32[1];
  v10 = v34.m128i_i32[0];
  v37 = v4;
  v11 = v4.m128i_i32[3];
  v12 = v4.m128i_i32[0];
  v13 = v4.m128i_i32[1];
  v36 = v7;
  v14 = v7.m128i_i32[3];
  v15 = v7.m128i_i32[2];
  v41 = v4.m128i_i32[2];
  v31 = v7.m128i_i32[1];
  v16 = v35.m128i_i32[0];
  v32 = v35.m128i_i32[0];
  v40 = v7.m128i_i32[3];
  v33 = v34.m128i_i32[3];
  do
  {
    if ( (v2 & 1) != 0 )
    {
      v17 = v16 ^ __ROL4__(v12 + v10 + v36.m128i_i32[0], 5);
      v36.m128i_i32[0] ^= __ROL4__(v17 + v10 + v12, 7);
      v18 = v12 ^ __ROL4__(v17 + v36.m128i_i32[0] + v10, 11);
      v19 = v41 ^ __ROL4__(v15 + v34.m128i_i32[2] + v5, 5);
      v10 ^= __ROL4__(v36.m128i_i32[0] + 2 * v18, 16);
      v34.m128i_i32[0] = v10;
      v34.m128i_i32[2] ^= __ROL4__(v19 + v15 + v5, 7);
      v20 = v5 ^ __ROL4__(v19 + v34.m128i_i32[2] + v15, 11);
      v5 = v20 ^ __ROL4__(v17 + v6 + v35.m128i_i32[3], 5);
      v15 ^= __ROL4__(v34.m128i_i32[2] + 2 * v20, 16);
      v36.m128i_i32[2] = v15;
      v35.m128i_i32[3] ^= __ROL4__(v17 + v6 + v5, 7);
      v12 = v18 ^ __ROL4__(v19 + v13 + v11, 5);
      v14 = v40;
      v37.m128i_i32[0] = v12;
      v32 = v17 ^ __ROL4__(v5 + v35.m128i_i32[3] + v6, 11);
      v35.m128i_i32[0] = v32;
      v6 ^= __ROL4__(v35.m128i_i32[3] + 2 * v32, 16);
      *(__int64 *)((char *)v35.m128i_i64 + 4) = __PAIR64__(v5, v6);
      v13 ^= __ROL4__(v19 + v11 + v12, 7);
      v37.m128i_i32[1] = v13;
      v41 = v19 ^ __ROL4__(v12 + v13 + v11, 11);
      v37.m128i_i32[2] = v41;
      v11 ^= __ROL4__(v13 + 2 * v41, 16);
      v37.m128i_i32[3] = v11;
    }
    else
    {
      v21 = v14 + v11;
      v22 = v8 ^ __ROL4__(v14 + v11 + v35.m128i_i32[3], 5);
      v23 = v31 ^ __ROL4__(v6 + v9 + v13, 5);
      v13 ^= __ROL4__(v6 + v9 + v23, 7);
      v37.m128i_i32[1] = v13;
      v24 = v9 ^ __ROL4__(v6 + v13 + v23, 11);
      v9 = v24 ^ __ROL4__(v22 + v10 + v34.m128i_i32[2], 5);
      v6 ^= __ROL4__(v13 + 2 * v24, 16);
      v35.m128i_i32[1] = v6;
      v35.m128i_i32[3] ^= __ROL4__(v21 + v22, 7);
      v25 = v40 ^ __ROL4__(v22 + v35.m128i_i32[3] + v11, 11);
      v11 ^= __ROL4__(v35.m128i_i32[3] + 2 * v25, 16);
      v37.m128i_i32[3] = v11;
      v34.m128i_i32[2] ^= __ROL4__(v22 + v9 + v10, 7);
      v33 = v22 ^ __ROL4__(v10 + v34.m128i_i32[2] + v9, 11);
      v34.m128i_i32[3] = v33;
      v10 ^= __ROL4__(v34.m128i_i32[2] + 2 * v33, 16);
      v14 = v25 ^ __ROL4__(v36.m128i_i32[0] + v23 + v15, 5);
      v34.m128i_i64[0] = __PAIR64__(v9, v10);
      v40 = v14;
      v36.m128i_i32[0] ^= __ROL4__(v15 + v14 + v23, 7);
      v31 = v23 ^ __ROL4__(v15 + v36.m128i_i32[0] + v14, 11);
      v36.m128i_i32[1] = v31;
      v15 ^= __ROL4__(v36.m128i_i32[0] + 2 * v31, 16);
      v36.m128i_i64[1] = __PAIR64__(v14, v15);
    }
    v16 = v32;
    ++v2;
    v8 = v33;
  }
  while ( v2 < 20 );
  if ( out > a2 + 15 || out + 15 < a2 )
  {
    v28 = _mm_loadu_si128((const __m128i *)a2 + 1);
    *(__m128i *)out = _mm_add_epi32(_mm_loadu_si128(&v34), _mm_loadu_si128((const __m128i *)a2));
    v29 = _mm_loadu_si128((const __m128i *)a2 + 2);
    *((__m128i *)out + 1) = _mm_add_epi32(v28, v35);
    v30 = _mm_add_epi32(_mm_loadu_si128((const __m128i *)a2 + 3), v37);
    *((__m128i *)out + 2) = _mm_add_epi32(v29, v36);
    *((__m128i *)out + 3) = v30;
  }
  else
  {
    v26 = 16i64;
    v27 = &v34;
    do
    {
      *(__int32 *)((char *)v27->m128i_i32 + (char *)out - (char *)&v34) = v27->m128i_i32[0]
                                                                        + *(__int32 *)((char *)v27->m128i_i32
                                                                                     + (char *)a2
                                                                                     - (char *)&v34);
      v27 = (__m128i *)((char *)v27 + 4);
      --v26;
    }
    while ( v26 );
  }
}
// 4092D0: using guessed type __m128i var_18;

//----- (0000000000409600) ----------------------------------------------------
void __fastcall RtlInitUnicodeString(__int64 dest, __int64 a2)
{
  unsigned __int64 v2; // [rsp+20h] [rbp-18h]

  if ( a2 )
  {
    v2 = 2i64 * (unsigned int)sub_409690(a2, 0xFFFFui64);
    if ( v2 > 0xFFFC )
      LOWORD(v2) = -4;
    *(_WORD *)dest = v2;
    *(_WORD *)(dest + 2) = v2 + 2;
  }
  else
  {
    *(_WORD *)(dest + 2) = 0;
    *(_WORD *)dest = 0;
  }
  *(_QWORD *)(dest + 8) = a2;
}

//----- (0000000000409690) ----------------------------------------------------
unsigned __int64 __fastcall sub_409690(__int64 a1, unsigned __int64 a2)
{
  unsigned __int64 i; // [rsp+0h] [rbp-18h]

  for ( i = 0i64; *(_WORD *)(a1 + 2 * i) && i < a2; ++i )
    ;
  return i;
}

//----- (00000000004096E0) ----------------------------------------------------
__int64 __fastcall SW2_GetSyscallNumber(int a1)
{
  unsigned int v2; // ebx
  _DWORD *v3; // rdx
  struct _LIST_ENTRY *Flink; // r9
  struct _LIST_ENTRY *v5; // rax
  struct _LIST_ENTRY *v6; // r8
  __int64 v7; // rcx
  __int64 v8; // rcx
  unsigned int v9; // r11d
  __int64 v10; // rbp
  unsigned int v11; // edi
  __int64 v12; // r14
  __int64 v13; // r15
  _WORD *v14; // rdx
  unsigned int v15; // r10d
  int v16; // r9d
  _BYTE *v17; // rax
  int v18; // ecx
  __int64 v19; // rax
  __int64 v20; // rdx
  __int64 v21; // rax
  unsigned int v22; // esi
  int v23; // eax
  __int64 v24; // r8
  unsigned int v25; // r11d
  unsigned int v26; // edi
  int v27; // ecx
  unsigned int v29; // [rsp+20h] [rbp-FD8h]
  int v30; // [rsp+24h] [rbp-FD4h]
  int SW2_SyscallList[1002]; // [rsp+28h] [rbp-FD0h] BYREF

  v30 = 1;
  v2 = 0;
  memset_wrapper(SW2_SyscallList, 0, 0xF9Cui64);
  v3 = 0i64;
  Flink = NtCurrentPeb()->Ldr->InLoadOrderModuleList.Flink;
  v5 = Flink[3].Flink;
  if ( !v5 )
    return 0i64;
  do
  {
    v6 = v5;
    v7 = *(unsigned int *)((char *)&v5[8].Blink + SHIDWORD(v5[3].Blink));
    if ( (_DWORD)v7 )
    {
      v3 = (_DWORD *)((char *)v5 + v7);
      v8 = *(unsigned int *)((char *)&v5->Blink + v7 + 4);
      if ( (*(_DWORD *)((char *)&v5->Flink + v8) | 0x20202020) == 0x6C64746E
        && (*(_DWORD *)((char *)&v5->Flink + v8 + 4) | 0x20202020) == 0x6C642E6C )
      {
        break;
      }
    }
    Flink = Flink->Flink;
    v5 = Flink[3].Flink;
  }
  while ( v5 );
  if ( !v3 )
    return 0i64;
  v9 = 0;
  v10 = (__int64)v6 + (unsigned int)v3[8];
  v11 = v3[6];
  v12 = (__int64)v6 + (unsigned int)v3[7];
  v13 = (__int64)v6 + (unsigned int)v3[9];
  do
  {
    v14 = (_WORD *)((char *)v6 + *(unsigned int *)(v10 + 4i64 * --v11));
    if ( *v14 == 'wZ' )
    {
      v15 = 0;
      v16 = 0x62B5B7AE;
      v17 = (char *)v6 + *(unsigned int *)(v10 + 4i64 * v11);
      do
      {
        ++v15;
        v18 = *(unsigned __int16 *)v17 + __ROR4__(v16, 8);
        v17 = (char *)v14 + v15;
        v16 ^= v18;
      }
      while ( *v17 );
      v19 = v9++;
      v20 = 2 * v19;
      v21 = *(unsigned __int16 *)(v13 + 2i64 * v11);
      SW2_SyscallList[v20 - 1] = v16;
      SW2_SyscallList[v20] = *(_DWORD *)(v12 + 4 * v21);
      if ( v9 == 0x1F4 )
        break;
    }
  }
  while ( v11 );
  v22 = 0;
  v29 = v9;
  if ( v9 != 1 )
  {
    do
    {
      v23 = 0;
      if ( ~v22 + v29 )
      {
        do
        {
          v24 = (unsigned int)(v23 + 1);
          v25 = SW2_SyscallList[2 * v24];
          v26 = SW2_SyscallList[2 * v23];
          if ( v26 > v25 )
          {
            v27 = SW2_SyscallList[2 * v23 - 1];
            SW2_SyscallList[2 * v23 - 1] = SW2_SyscallList[2 * v24 - 1];
            SW2_SyscallList[2 * v24 - 1] = v27;
            SW2_SyscallList[2 * v23] = v25;
            SW2_SyscallList[2 * v24] = v26;
          }
          ++v23;
        }
        while ( (unsigned int)v24 < ~v22 + v29 );
      }
      ++v22;
    }
    while ( v22 < v29 - 1 );
  }
  if ( !v29 )
    return 0xFFFFFFFFi64;
  while ( a1 != SW2_SyscallList[2 * v2 - 1] )
  {
    if ( ++v2 >= v29 )
      return 0xFFFFFFFFi64;
  }
  return v2;
}
// 409714: conditional instruction was optimized away because %var_FD8.4==0
// 4096E0: using guessed type int SW2_SyscallList[1002];

//----- (0000000000409954) ----------------------------------------------------
// positive sp value has been detected, the output may be wrong!
__int64 __fastcall WhisperMain()
{
  int v0; // r10d
  __int64 result; // rax

  result = SW2_GetSyscallNumber(v0);
  __asm { syscall; Low latency system call }
  return result;
}
// 409955: positive sp value 8 has been found
// 409970: variable 'v0' is possibly undefined

// nfuncs=12 queued=11 decompiled=11 lumina nreq=0 worse=0 better=0
// ALL OK, 11 function(s) have been successfully decompiled
