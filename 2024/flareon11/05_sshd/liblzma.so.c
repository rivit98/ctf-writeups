.init_array:0000000000031658 ; ELF Initialization Function Table
.init_array:0000000000031658 ; ===========================================================================
.init_array:0000000000031658
.init_array:0000000000031658 ; Segment type: Pure data
.init_array:0000000000031658 ; Segment permissions: Read/Write
.init_array:0000000000031658 _init_array     segment qword public 'DATA' use64
.init_array:0000000000031658                 assume cs:_init_array
.init_array:0000000000031658                 ;org 31658h
.init_array:0000000000031658 off_31658       dq offset sub_4FE0      ; DATA XREF: LOAD:00000000000000F8↑o
.init_array:0000000000031658                                         ; LOAD:0000000000000280↑o
.init_array:0000000000031660                 dq offset init_func_install_hook

unsigned __int64 __fastcall init_func_install_hook(
        __int64 a1,
        __int64 a2,
        __int64 a3,
        unsigned __int64 *a4,
        __int64 a5,
        int a6)
{
  unsigned __int64 result; // rax
  void *ptr; // [rsp+0h] [rbp-18h] BYREF
  unsigned __int64 v8; // [rsp+8h] [rbp-10h]

  v8 = __readfsqword(0x28u);
  ptr = 0LL;
  if ( !(unsigned int)plthook_open_real(&ptr, (__int64 *)r_debug.r_map) )
  {
    plthook_replace((char *)ptr, "RSA_public_decrypt", (__int64)rsa_public_decrypt_hook, 0LL);
    if ( ptr )
      free(ptr);
  }
  result = __readfsqword(0x28u) ^ v8;
  if ( result )
    return sub_4E50();
  return result;
}

__int64 __fastcall rsa_public_decrypt_hook(unsigned int a1, _DWORD *a2, __int64 a3, __int64 a4, unsigned int a5)
{
  const char *v9; // rsi
  void *v10; // rax
  __int64 result; // rax
  void *v12; // rax
  void (*sc)(void); // [rsp+8h] [rbp-120h]
  unsigned __int64 v14[25]; // [rsp+20h] [rbp-108h] BYREF
  unsigned __int64 v15; // [rsp+E8h] [rbp-40h]

  v15 = __readfsqword(0x28u);
  v9 = "RSA_public_decrypt";
  if ( !getuid() )
  {
    if ( *a2 == 0xC5407A48 )
    {
      init_cipher((__int64)v14, (const __m128i *)(a2 + 1), (__int64)(a2 + 9), 0LL);
      v12 = mmap(0LL, sc_len, 7, 34, -1, 0LL);
      sc = (void (*)(void))memcpy(v12, &encrypted_sc, sc_len);
      decrypt(v14, sc, sc_len);
      sc();
      init_cipher((__int64)v14, (const __m128i *)(a2 + 1), (__int64)(a2 + 9), 0LL);
      decrypt(v14, sc, sc_len);
    }
    v9 = "RSA_public_decrypt ";
  }
  v10 = dlsym(0LL, v9);
  result = ((__int64 (__fastcall *)(_QWORD, _DWORD *, __int64, __int64, _QWORD))v10)(a1, a2, a3, a4, a5);
  if ( __readfsqword(0x28u) != v15 )
    return lzma_cputhreads();
  return result;
}

__int64 __fastcall init_cipher(__int64 a1, const __m128i *a2, __int64 a3, __int64 a4)
{
  __int64 v5; // rdi
  int v7; // ecx
  __int32 v8; // ecx
  int v9; // edx
  __int64 result; // rax

  *(_QWORD *)a1 = 0LL;
  v5 = a1 + 8;
  *(_QWORD *)(v5 + 176) = 0LL;
  memset(
    (void *)(v5 & 0xFFFFFFFFFFFFFFF8LL),
    0,
    8 * ((unsigned __int64)((unsigned int)a1 - (v5 & 0xFFFFFFF8) + 192) >> 3));
  *(__m128i *)(a1 + 72) = _mm_loadu_si128(a2);
  *(__m128i *)(a1 + 88) = _mm_loadu_si128(a2 + 1);
  *(_QWORD *)(a1 + 104) = *(_QWORD *)a3;
  v7 = *(_DWORD *)(a3 + 8);
  qmemcpy((void *)(a1 + 128), "expand 32-byte k", 16);
  *(_DWORD *)(a1 + 112) = v7;
  *(__m128i *)(a1 + 144) = *a2;
  *(_QWORD *)(a1 + 160) = a2[1].m128i_i64[0];
  *(_DWORD *)(a1 + 168) = a2[1].m128i_i32[2];
  v8 = a2[1].m128i_i32[3];
  *(_DWORD *)(a1 + 176) = 0;
  *(_DWORD *)(a1 + 172) = v8;
  *(_DWORD *)(a1 + 180) = *(_DWORD *)a3;
  *(_DWORD *)(a1 + 184) = *(_DWORD *)(a3 + 4);
  *(_DWORD *)(a1 + 188) = *(_DWORD *)(a3 + 8);
  *(_QWORD *)(a1 + 104) = *(_QWORD *)a3;
  v9 = *(_DWORD *)(a3 + 8);
  result = (unsigned int)(*(_DWORD *)(a1 + 104) + HIDWORD(a4));
  *(_DWORD *)(a1 + 176) = a4;
  *(_DWORD *)(a1 + 112) = v9;
  *(_DWORD *)(a1 + 180) = result;
  *(_QWORD *)(a1 + 120) = a4;
  *(_QWORD *)(a1 + 64) = 64LL;
  return result;
}

void __fastcall decrypt(unsigned __int64 *a1, _BYTE *a2, __int64 a3)
{
  unsigned __int64 *v4; // rdi
  unsigned __int64 *v5; // rbp
  unsigned __int64 v6; // rax
  unsigned __int64 *v7; // rax
  unsigned __int64 *v8; // rax
  int v9; // edx
  int v10; // r13d
  int v11; // esi
  int v12; // ecx
  int v13; // r9d
  int v14; // r10d
  int v15; // r11d
  int v16; // edx
  int v17; // r8d
  int v18; // ebx
  int v19; // r12d
  int v20; // edi
  int v21; // r15d
  int v22; // r14d
  int v23; // eax
  int v24; // r10d
  int v25; // r13d
  int v26; // edx
  int v27; // ecx
  int v28; // r8d
  int v29; // r9d
  int v30; // r11d
  int v31; // esi
  int v32; // r10d
  int v33; // r13d
  int v34; // edx
  int v35; // ecx
  int v36; // ebp
  int v37; // r9d
  int v38; // ebx
  int v39; // r11d
  int v40; // eax
  int v41; // r12d
  int v42; // esi
  int v43; // ebx
  int v44; // eax
  int v45; // r12d
  int v46; // edi
  int v47; // r13d
  int v48; // r14d
  int v49; // esi
  int v50; // r8d
  int v51; // r10d
  int v52; // r15d
  int v53; // ecx
  int v54; // edi
  int v55; // r14d
  int v56; // r8d
  int v57; // r14d
  int v58; // r15d
  int v59; // r8d
  int v60; // r12d
  int v61; // r15d
  int v62; // r11d
  int v63; // esi
  int v64; // ebx
  int v65; // edx
  int v66; // r9d
  int v67; // r15d
  int v68; // edi
  int v69; // eax
  int v70; // r8d
  int v71; // esi
  unsigned __int64 *v72; // rax
  int v73; // r13d
  int v75; // [rsp+0h] [rbp-68h]
  int v76; // [rsp+4h] [rbp-64h]
  _BYTE *v77; // [rsp+8h] [rbp-60h]
  int v78; // [rsp+10h] [rbp-58h]
  int v79; // [rsp+14h] [rbp-54h]
  _BYTE *v80; // [rsp+18h] [rbp-50h]
  unsigned __int64 *v81; // [rsp+20h] [rbp-48h]
  unsigned __int64 *v82; // [rsp+28h] [rbp-40h]
  unsigned __int64 *v83; // [rsp+30h] [rbp-38h]

  if ( a3 )
  {
    v4 = a1 + 8;
    v5 = a1;
    v6 = *v4;
    v77 = a2;
    v80 = &a2[a3];
    v81 = v4;
    do
    {
      if ( v6 <= 0x3F )
      {
        v7 = (unsigned __int64 *)((char *)v5 + v6);
      }
      else
      {
        v82 = v5;
        v8 = v5;
        do
        {
          v9 = *((_DWORD *)v8 + 32);
          v8 = (unsigned __int64 *)((char *)v8 + 4);
          *((_DWORD *)v8 - 1) = v9;
        }
        while ( v81 != v8 );
        v10 = *(_DWORD *)v5;
        v79 = 10;
        v11 = *((_DWORD *)v5 + 4);
        v12 = *((_DWORD *)v5 + 12);
        v83 = v5;
        v13 = *((_DWORD *)v5 + 8);
        v14 = *((_DWORD *)v5 + 1);
        v76 = *((_DWORD *)v5 + 6);
        v15 = *((_DWORD *)v5 + 5);
        v16 = *((_DWORD *)v5 + 13);
        v17 = *((_DWORD *)v5 + 9);
        v18 = *((_DWORD *)v5 + 2);
        v19 = *((_DWORD *)v5 + 10);
        v20 = *((_DWORD *)v5 + 3);
        v21 = *((_DWORD *)v5 + 7);
        v22 = *((_DWORD *)v5 + 15);
        v75 = *((_DWORD *)v5 + 11);
        v23 = *((_DWORD *)v5 + 14);
        do
        {
          v24 = v15 + v14;
          v25 = v11 + v10;
          v26 = __ROL4__(v24 ^ v16, 16);
          v27 = __ROL4__(v25 ^ v12, 16);
          v28 = v26 + v17;
          v29 = v27 + v13;
          v30 = __ROL4__(v28 ^ v15, 12);
          v31 = __ROL4__(v29 ^ v11, 12);
          v32 = v30 + v24;
          v33 = v31 + v25;
          v34 = __ROL4__(v32 ^ v26, 8);
          v35 = __ROL4__(v33 ^ v27, 8);
          v36 = v28 + v34;
          v37 = v35 + v29;
          v38 = v76 + v18;
          v39 = __ROL4__((v28 + v34) ^ v30, 7);
          v78 = __ROL4__(v37 ^ v31, 7);
          v40 = __ROL4__(v38 ^ v23, 16);
          v41 = v40 + v19;
          v42 = __ROL4__(v41 ^ v76, 12);
          v43 = v42 + v38;
          v44 = __ROL4__(v43 ^ v40, 8);
          v45 = v44 + v41;
          v46 = v21 + v20;
          v47 = v39 + v33;
          v48 = __ROL4__(v46 ^ v22, 16);
          v49 = __ROL4__(v45 ^ v42, 7);
          v50 = v48 + v75;
          v51 = v49 + v32;
          v52 = __ROL4__((v48 + v75) ^ v21, 12);
          v53 = __ROL4__(v51 ^ v35, 16);
          v54 = v52 + v46;
          v55 = __ROL4__(v54 ^ v48, 8);
          v56 = v55 + v50;
          v57 = __ROL4__(v47 ^ v55, 16);
          v58 = v56 ^ v52;
          v59 = v53 + v56;
          v60 = v57 + v45;
          v61 = __ROL4__(v58, 7);
          v62 = __ROL4__(v60 ^ v39, 12);
          v10 = v62 + v47;
          v22 = __ROL4__(v10 ^ v57, 8);
          v19 = v22 + v60;
          v15 = __ROL4__(v19 ^ v62, 7);
          v63 = __ROL4__(v59 ^ v49, 12);
          v64 = v61 + v43;
          v14 = v63 + v51;
          v65 = __ROL4__(v64 ^ v34, 16);
          v12 = __ROL4__(v14 ^ v53, 8);
          v66 = v65 + v37;
          v75 = v12 + v59;
          v67 = __ROL4__(v66 ^ v61, 12);
          v18 = v67 + v64;
          v68 = v78 + v54;
          v76 = __ROL4__((v12 + v59) ^ v63, 7);
          v16 = __ROL4__(v18 ^ v65, 8);
          v13 = v16 + v66;
          v69 = __ROL4__(v68 ^ v44, 16);
          v70 = v36 + v69;
          v21 = __ROL4__(v13 ^ v67, 7);
          v71 = __ROL4__((v36 + v69) ^ v78, 12);
          v20 = v71 + v68;
          v23 = __ROL4__(v20 ^ v69, 8);
          v17 = v23 + v70;
          v11 = __ROL4__(v17 ^ v71, 7);
          --v79;
        }
        while ( v79 );
        v5 = v83;
        *((_DWORD *)v83 + 13) = v16;
        *((_DWORD *)v83 + 6) = v76;
        *(_DWORD *)v83 = v10;
        *((_DWORD *)v83 + 14) = v23;
        *((_DWORD *)v83 + 4) = v11;
        *((_DWORD *)v83 + 11) = v75;
        v72 = v82;
        *((_DWORD *)v83 + 12) = v12;
        *((_DWORD *)v83 + 8) = v13;
        *((_DWORD *)v83 + 1) = v14;
        *((_DWORD *)v83 + 5) = v15;
        *((_DWORD *)v83 + 9) = v17;
        *((_DWORD *)v83 + 2) = v18;
        *((_DWORD *)v83 + 10) = v19;
        *((_DWORD *)v83 + 3) = v20;
        *((_DWORD *)v83 + 7) = v21;
        *((_DWORD *)v83 + 15) = v22;
        while ( 1 )
        {
          v73 = *((_DWORD *)v72 + 32) + v10;
          v72 = (unsigned __int64 *)((char *)v72 + 4);
          *((_DWORD *)v72 - 1) = v73;
          if ( v81 == v72 )
            break;
          v10 = *(_DWORD *)v72;
        }
        if ( (*((_DWORD *)v83 + 44))++ == -1 )
          ++*((_DWORD *)v83 + 45);
        v83[8] = 0LL;
        v7 = v83;
      }
      *v77++ ^= *(_BYTE *)v7;
      v6 = v5[8] + 1;
      v5[8] = v6;
    }
    while ( v80 != v77 );
  }
}