
//----- (0000000140001290) ----------------------------------------------------
int __cdecl main(int argc, const char **argv, const char **envp)
{
  int v3; // ebx
  void **v4; // rdx
  void *v5; // rcx
  int v6; // esi
  unsigned __int64 v7; // r10
  char v8; // dl
  void **v9; // rdi
  void **v10; // r14
  void **v11; // r14
  unsigned int v12; // ecx
  char *v13; // r9
  unsigned int v14; // ecx
  unsigned __int64 v15; // r8
  unsigned __int64 v16; // rax
  void **v17; // rdx
  __int64 *v18; // rax
  void **v19; // rdx
  void *v20; // rcx
  void *v21; // rcx
  unsigned __int64 v22; // rcx
  unsigned __int64 v23; // r9
  int v24; // esi
  unsigned __int64 v25; // r8
  void *v26; // rdx
  void *v27; // r8
  unsigned int v28; // esi
  void **v29; // rdx
  __int64 *v30; // rax
  void *v31; // rcx
  size_t v32; // rdi
  unsigned __int64 v33; // r15
  unsigned __int64 v34; // r8
  void *v35; // rdx
  void *v36; // r8
  void **v37; // rdx
  char *v38; // rsi
  void **v39; // rcx
  char *v40; // r14
  size_t v41; // r8
  size_t v42; // r13
  __int64 v43; // r12
  char *v44; // rax
  char *v45; // rax
  void **v46; // rdx
  __int64 *v47; // rax
  void *v48; // rcx
  void **v49; // rdx
  __int64 *v50; // rax
  void *v51; // rcx
  void *v52; // rcx
  void *Buf2[2]; // [rsp+20h] [rbp-E0h] BYREF
  size_t Size; // [rsp+30h] [rbp-D0h]
  unsigned __int64 v56; // [rsp+38h] [rbp-C8h]
  void *Block[2]; // [rsp+40h] [rbp-C0h] BYREF
  unsigned __int64 v58; // [rsp+50h] [rbp-B0h]
  unsigned __int64 v59; // [rsp+58h] [rbp-A8h]
  unsigned int v60; // [rsp+60h] [rbp-A0h]
  void *v61[2]; // [rsp+70h] [rbp-90h] BYREF
  __int64 v62; // [rsp+80h] [rbp-80h]
  unsigned __int64 v63; // [rsp+88h] [rbp-78h]
  __int64 v64[32]; // [rsp+90h] [rbp-70h] BYREF
  void *Src[2]; // [rsp+190h] [rbp+90h]
  char v66[3]; // [rsp+1A5h] [rbp+A5h] BYREF

  v3 = 0;
  v60 = 0;
  v61[0] = 0i64;
  v62 = 0i64;
  v63 = 15i64;
  Block[0] = 0i64;
  v58 = 0i64;
  v59 = 15i64;
  sub_1400022C0(Block, "Enter serial: ", 0xEui64);
  v4 = Block;
  if ( v59 >= 0x10 )
    v4 = (void **)Block[0];
  sub_140002910(std::cout, (__int64)v4, v58);
  if ( v59 >= 0x10 )
  {
    v5 = Block[0];
    if ( v59 + 1 >= 0x1000 )
    {
      v5 = (void *)*((_QWORD *)Block[0] - 1);
      if ( (unsigned __int64)(Block[0] - v5 - 8) > 0x1F )
        invalid_parameter_noinfo_noreturn();
    }
    j_j_free(v5);
  }
  sub_140002720(std::cin, v61);
  memset(v64, 0, 0xF8ui64);
  v64[0] = (__int64)&unk_140004660;
  v64[2] = (__int64)&unk_1400045A8;
  std::ios::ios(&v64[19]);
  v6 = 1;
  v60 = 1;
  std::iostream::basic_iostream<char>(v64, &v64[3], 0i64);
  *(__int64 *)((char *)v64 + *(int *)(v64[0] + 4)) = (__int64)&std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::`vftable';
  *(_DWORD *)((char *)&v63 + *(int *)(v64[0] + 4) + 4) = *(_DWORD *)(v64[0] + 4) - 152;
  std::streambuf::streambuf(&v64[3]);
  v64[3] = (__int64)&std::stringbuf::`vftable';
  v7 = 0i64;
  v64[16] = 0i64;
  v8 = 0;
  LODWORD(v64[17]) = 0;
  v9 = v61;
  if ( v63 >= 0x10 )
    v9 = (void **)v61[0];
  v10 = v61;
  if ( v63 >= 0x10 )
    v10 = (void **)v61[0];
  v11 = (void **)((char *)v10 + v62);
  if ( v9 != v11 )
  {
    do
    {
      Buf2[0] = 0i64;
      Size = 0i64;
      v56 = 15i64;
      sub_1400022C0(Buf2, " ", 1ui64);
      v12 = 16 * *(char *)v9;
      v13 = v66;
      if ( (*(char *)v9 & 0x8000000) != 0 )
      {
        v14 = -16 * *(char *)v9;
        do
        {
          *--v13 = v14 % 0xA + 48;
          v14 /= 0xAu;
        }
        while ( v14 );
        *--v13 = 45;
      }
      else
      {
        do
        {
          *--v13 = v12 % 0xA + 48;
          v12 /= 0xAu;
        }
        while ( v12 );
      }
      Block[0] = 0i64;
      v15 = 0i64;
      v58 = 0i64;
      v16 = 15i64;
      v59 = 15i64;
      if ( v13 != v66 )
      {
        sub_1400022C0(Block, v13, v66 - v13);
        v16 = v59;
        v15 = v58;
      }
      v6 |= 6u;
      v17 = Block;
      if ( v16 >= 0x10 )
        v17 = (void **)Block[0];
      v18 = sub_140002910(&v64[2], (__int64)v17, v15);
      v19 = Buf2;
      if ( v56 >= 0x10 )
        v19 = (void **)Buf2[0];
      sub_140002910(v18, (__int64)v19, Size);
      if ( v59 >= 0x10 )
      {
        v20 = Block[0];
        if ( v59 + 1 >= 0x1000 )
        {
          v20 = (void *)*((_QWORD *)Block[0] - 1);
          if ( (unsigned __int64)(Block[0] - v20 - 8) > 0x1F )
            invalid_parameter_noinfo_noreturn();
        }
        j_j_free(v20);
      }
      v58 = 0i64;
      v59 = 15i64;
      LOBYTE(Block[0]) = 0;
      if ( v56 >= 0x10 )
      {
        v21 = Buf2[0];
        if ( v56 + 1 >= 0x1000 )
        {
          v21 = (void *)*((_QWORD *)Buf2[0] - 1);
          if ( (unsigned __int64)(Buf2[0] - v21 - 8) > 0x1F )
            invalid_parameter_noinfo_noreturn();
        }
        j_j_free(v21);
      }
      v9 = (void **)((char *)v9 + 1);
    }
    while ( v9 != v11 );
    v8 = v64[17];
    v7 = v64[16];
  }
  Buf2[0] = 0i64;
  v22 = 0i64;
  Size = 0i64;
  v23 = 15i64;
  v56 = 15i64;
  v24 = v6 | 0x10;
  v60 = v24;
  *(_OWORD *)Src = 0i64;
  if ( (v8 & 0x22) == 2 || (v25 = *(_QWORD *)v64[11]) == 0 )
  {
    if ( (v8 & 4) != 0 || !*(_QWORD *)v64[10] )
    {
      v27 = Src[1];
      v26 = Src[0];
    }
    else
    {
      v26 = *(void **)v64[6];
      v27 = (void *)(*(_QWORD *)v64[10] + *(int *)v64[13] - *(_QWORD *)v64[6]);
    }
  }
  else
  {
    v26 = *(void **)v64[7];
    if ( v25 < v7 )
      v25 = v7;
    v27 = (void *)(v25 - (_QWORD)v26);
  }
  if ( v26 )
  {
    sub_1400022C0(Buf2, v26, (size_t)v27);
    v23 = v56;
    v22 = Size;
  }
  v28 = v24 & 0xFFFFFFE7 | 8;
  v29 = Buf2;
  if ( v23 >= 0x10 )
    v29 = (void **)Buf2[0];
  v30 = sub_140002910(std::cout, (__int64)v29, v22);
  std::ostream::operator<<(v30, sub_140002560);
  if ( v56 >= 0x10 )
  {
    v31 = Buf2[0];
    if ( v56 + 1 >= 0x1000 )
    {
      v31 = (void *)*((_QWORD *)Buf2[0] - 1);
      if ( (unsigned __int64)(Buf2[0] - v31 - 8) > 0x1F )
        invalid_parameter_noinfo_noreturn();
    }
    j_j_free(v31);
  }
  Buf2[0] = 0i64;
  Size = 0i64;
  v56 = 15i64;
  sub_1400022C0(
    Buf2,
    "1584 1776 1824 1584 1856 1632 1968 1664 768 1728 784 784 784 784 784 1520 1840 1664 784 784 784 784 784 784 816 816 "
    "816 816 816 816 1856 1856 1856 1856 1856 1520 784 1856 1952 1520 1584 688 688 528 2000 ",
    0xCBui64);
  Block[0] = 0i64;
  v32 = 0i64;
  v58 = 0i64;
  v33 = 15i64;
  v59 = 15i64;
  v60 = v28 | 0x40;
  *(_OWORD *)Src = 0i64;
  if ( (v64[17] & 0x22) == 2 || (v34 = *(_QWORD *)v64[11]) == 0 )
  {
    if ( (v64[17] & 4) != 0 || !*(_QWORD *)v64[10] )
    {
      v36 = Src[1];
      v35 = Src[0];
    }
    else
    {
      v35 = *(void **)v64[6];
      v36 = (void *)(*(_QWORD *)v64[10] + *(int *)v64[13] - *(_QWORD *)v64[6]);
    }
  }
  else
  {
    v35 = *(void **)v64[7];
    if ( v34 < v64[16] )
      v34 = v64[16];
    v36 = (void *)(v34 - (_QWORD)v35);
  }
  if ( v35 )
  {
    sub_1400022C0(Block, v35, (size_t)v36);
    v33 = v59;
    v32 = v58;
  }
  v37 = Buf2;
  v38 = (char *)Buf2[0];
  if ( v56 >= 0x10 )
    v37 = (void **)Buf2[0];
  v39 = Block;
  v40 = (char *)Block[0];
  if ( v33 >= 0x10 )
    v39 = (void **)Block[0];
  v41 = v32;
  v42 = Size;
  if ( Size < v32 )
    v41 = Size;
  LODWORD(v43) = memcmp(v39, v37, v41);
  if ( !(_DWORD)v43 )
  {
    if ( v32 >= v42 )
      v43 = v32 > v42;
    else
      LODWORD(v43) = -1;
  }
  if ( v33 >= 0x10 )
  {
    v44 = v40;
    if ( v33 + 1 >= 0x1000 )
    {
      v40 = (char *)*((_QWORD *)v40 - 1);
      if ( (unsigned __int64)(v44 - v40 - 8) > 0x1F )
        invalid_parameter_noinfo_noreturn();
    }
    j_j_free(v40);
  }
  if ( v56 >= 0x10 )
  {
    v45 = v38;
    if ( v56 + 1 >= 0x1000 )
    {
      v38 = (char *)*((_QWORD *)v38 - 1);
      if ( (unsigned __int64)(v45 - v38 - 8) > 0x1F )
        invalid_parameter_noinfo_noreturn();
    }
    j_j_free(v38);
  }
  Buf2[0] = 0i64;
  Size = 0i64;
  v56 = 15i64;
  if ( (_DWORD)v43 )
  {
    sub_1400022C0(Buf2, "Try again, son!", 0xFui64);
    v49 = Buf2;
    if ( v56 >= 0x10 )
      v49 = (void **)Buf2[0];
    v50 = sub_140002910(std::cout, (__int64)v49, Size);
    std::ostream::operator<<(v50, sub_140002560);
    if ( v56 >= 0x10 )
    {
      v51 = Buf2[0];
      if ( v56 + 1 >= 0x1000 )
      {
        v51 = (void *)*((_QWORD *)Buf2[0] - 1);
        if ( (unsigned __int64)(Buf2[0] - v51 - 8) > 0x1F )
          invalid_parameter_noinfo_noreturn();
      }
      j_j_free(v51);
    }
    std::istream::get(std::cin);
    v3 = 1;
  }
  else
  {
    sub_1400022C0(Buf2, "Congratulations!", 0x10ui64);
    v46 = Buf2;
    if ( v56 >= 0x10 )
      v46 = (void **)Buf2[0];
    v47 = sub_140002910(std::cout, (__int64)v46, Size);
    std::ostream::operator<<(v47, sub_140002560);
    if ( v56 >= 0x10 )
    {
      v48 = Buf2[0];
      if ( v56 + 1 >= 0x1000 )
      {
        v48 = (void *)*((_QWORD *)Buf2[0] - 1);
        if ( (unsigned __int64)(Buf2[0] - v48 - 8) > 0x1F )
          invalid_parameter_noinfo_noreturn();
      }
      j_j_free(v48);
    }
  }
  *(__int64 *)((char *)v64 + *(int *)(v64[0] + 4)) = (__int64)&std::basic_stringstream<char,std::char_traits<char>,std::allocator<char>>::`vftable';
  *(_DWORD *)((char *)&v63 + *(int *)(v64[0] + 4) + 4) = *(_DWORD *)(v64[0] + 4) - 152;
  sub_140002060((__int64)&v64[3]);
  std::iostream::~basic_iostream<char,std::char_traits<char>>(&v64[4]);
  std::ios::~ios<char,std::char_traits<char>>(&v64[19]);
  if ( v63 >= 0x10 )
  {
    v52 = v61[0];
    if ( v63 + 1 >= 0x1000 )
    {
      v52 = (void *)*((_QWORD *)v61[0] - 1);
      if ( (unsigned __int64)(v61[0] - v52 - 8) > 0x1F )
        invalid_parameter_noinfo_noreturn();
    }
    j_j_free(v52);
  }
  return v3;
}
