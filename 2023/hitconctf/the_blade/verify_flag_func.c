 
__int64 __fastcall seccomp_shell::shell::verify::h898bf5fa26dafbab(__int64 a1, char *flag, __int64 arg_len)
{
  char *v3; // rax
  char *flag_shuffled; // rbx
  __int128 v5; // xmm0
  __int128 v6; // xmm1
  __int128 v7; // xmm2
  int loop_idx; // r13d
  __int64 v9; // rax
  int64_t *v10; // rcx
  unsigned __int64 v11; // rdi
  char v12; // dl
  int64_t v13; // rdi
  char v14; // dl
  __int64 v15; // rax
  int64_t *v16; // rcx
  unsigned __int64 v17; // rdi
  char v18; // dl
  int64_t v19; // rdi
  char v20; // dl
  __int64 v21; // rax
  int64_t *v22; // rcx
  unsigned __int64 v23; // rdi
  char v24; // dl
  int64_t v25; // rdi
  char v26; // dl
  __int64 v27; // rax
  int64_t *v28; // rcx
  unsigned __int64 v29; // rdi
  char v30; // dl
  int64_t v31; // rdi
  char v32; // dl
  __int64 v33; // rax
  int64_t *v34; // rcx
  unsigned __int64 v35; // rdi
  char v36; // dl
  int64_t v37; // rdi
  char v38; // dl
  __int64 v39; // rax
  int64_t *v40; // rcx
  unsigned __int64 v41; // rdi
  char v42; // dl
  int64_t v43; // rdi
  char v44; // dl
  __int64 v45; // rax
  int64_t *v46; // rcx
  unsigned __int64 v47; // rdi
  char v48; // dl
  int64_t v49; // rdi
  char v50; // dl
  __int64 tmp; // r9
  __int64 ridx; // rax
  int64_t *didx; // rcx
  unsigned __int64 v54; // rdi
  char v55; // dl
  int64_t v56; // rdi
  char v57; // dl
  __int64 idx; // rcx
  int c; // edi
  unsigned int v60; // r8d
  __int16 v61; // dx
  unsigned __int16 v62; // tt
  unsigned int v63; // esi
  __int16 v64; // ax
  __int64 v65; // rdx
  void *v66; // r14
  __int64 v67; // rdx
  __int64 v68; // r15
  size_t v69; // rcx
  __int64 v71; // rax
  __int64 v72; // rax
  __int64 v73; // r14
  void **fail; // rax
  __int64 idx4; // rbp
  size_t v77; // rcx
  int v78; // eax
  bool v80; // cc
  __int64 is_part_correct[2]; // [rsp+0h] [rbp-288h] BYREF
  char *packet; // [rsp+10h] [rbp-278h] MAPDST BYREF
  __int64 v83; // [rsp+18h] [rbp-270h]
  unsigned __int64 v84; // [rsp+20h] [rbp-268h]
  int *v85; // [rsp+28h] [rbp-260h] BYREF
  __int64 v86; // [rsp+30h] [rbp-258h]
  char *v87; // [rsp+38h] [rbp-250h]
  __int64 v88; // [rsp+40h] [rbp-248h]
  __int64 v89; // [rsp+48h] [rbp-240h]
  int64_t dest[70]; // [rsp+50h] [rbp-238h] BYREF

  if ( arg_len != 64 )
  {
    _$LT$alloc..boxed..Box$LT$dyn$u20$core..error..Error$GT$$u20$as$u20$core..convert..From$LT$$RF$str$GT$$GT$::from::hc50629fd4c285201();
    return v72;
  }
  v86 = a1;
  _rust_alloc();
  if ( !v3 )
    alloc::alloc::handle_alloc_error::hd36006f171acb99e();
  flag_shuffled = v3;
  v5 = *(_OWORD *)flag;
  v6 = *((_OWORD *)flag + 1);
  v7 = *((_OWORD *)flag + 2);
  *((_OWORD *)v3 + 3) = *((_OWORD *)flag + 3);
  *((_OWORD *)v3 + 2) = v7;
  *((_OWORD *)v3 + 1) = v6;
  *(_OWORD *)v3 = v5;
  v87 = v3;
  v88 = 64LL;
  v89 = 64LL;
  loop_idx = 0;
  do
  {
    ++loop_idx;
    memcpy(dest, "/", 0x200uLL);
    v9 = 64LL;
    v10 = &dest[1];
    do
    {
      v11 = *(v10 - 1);
      if ( v11 >= '@'
        || (v12 = flag_shuffled[v9 - 1],
            flag_shuffled[v9 - 1] = flag_shuffled[v11],
            flag_shuffled[v11] = v12,
            v13 = *v10,
            *v10 > (unsigned __int64)'?') )
      {
PANIC_BOUNDS_CHECK2:
        core::panicking::panic_bounds_check::h7d0e683548e4cb10();
      }
      v14 = flag_shuffled[v9 - 2];
      flag_shuffled[v9 - 2] = flag_shuffled[v13];
      flag_shuffled[v13] = v14;
      v10 += 2;
      v9 -= 2LL;
    }
    while ( v9 );
    memcpy(dest, src, 0x200uLL);
    v15 = 64LL;
    v16 = &dest[1];
    do
    {
      v17 = *(v16 - 1);
      if ( v17 > '?' )
        goto PANIC_BOUNDS_CHECK2;
      v18 = flag_shuffled[v15 - 1];
      flag_shuffled[v15 - 1] = flag_shuffled[v17];
      flag_shuffled[v17] = v18;
      v19 = *v16;
      if ( *v16 > (unsigned __int64)'?' )
        goto PANIC_BOUNDS_CHECK2;
      v20 = flag_shuffled[v15 - 2];
      flag_shuffled[v15 - 2] = flag_shuffled[v19];
      flag_shuffled[v19] = v20;
      v16 += 2;
      v15 -= 2LL;
    }
    while ( v15 );
    memcpy(dest, qword_61F20, 0x200uLL);
    v21 = 64LL;
    v22 = &dest[1];
    do
    {
      v23 = *(v22 - 1);
      if ( v23 > 0x3F )
        goto PANIC_BOUNDS_CHECK2;
      v24 = flag_shuffled[v21 - 1];
      flag_shuffled[v21 - 1] = flag_shuffled[v23];
      flag_shuffled[v23] = v24;
      v25 = *v22;
      if ( (unsigned __int64)*v22 > 0x3F )
        goto PANIC_BOUNDS_CHECK2;
      v26 = flag_shuffled[v21 - 2];
      flag_shuffled[v21 - 2] = flag_shuffled[v25];
      flag_shuffled[v25] = v26;
      v22 += 2;
      v21 -= 2LL;
    }
    while ( v21 );
    memcpy(dest, qword_62120, 0x200uLL);
    v27 = 64LL;
    v28 = &dest[1];
    do
    {
      v29 = *(v28 - 1);
      if ( v29 > 0x3F )
        goto PANIC_BOUNDS_CHECK2;
      v30 = flag_shuffled[v27 - 1];
      flag_shuffled[v27 - 1] = flag_shuffled[v29];
      flag_shuffled[v29] = v30;
      v31 = *v28;
      if ( (unsigned __int64)*v28 > 0x3F )
        goto PANIC_BOUNDS_CHECK2;
      v32 = flag_shuffled[v27 - 2];
      flag_shuffled[v27 - 2] = flag_shuffled[v31];
      flag_shuffled[v31] = v32;
      v28 += 2;
      v27 -= 2LL;
    }
    while ( v27 );
    memcpy(dest, qword_62320, 0x200uLL);
    v33 = 64LL;
    v34 = &dest[1];
    do
    {
      v35 = *(v34 - 1);
      if ( v35 > 0x3F )
        goto PANIC_BOUNDS_CHECK2;
      v36 = flag_shuffled[v33 - 1];
      flag_shuffled[v33 - 1] = flag_shuffled[v35];
      flag_shuffled[v35] = v36;
      v37 = *v34;
      if ( (unsigned __int64)*v34 > 0x3F )
        goto PANIC_BOUNDS_CHECK2;
      v38 = flag_shuffled[v33 - 2];
      flag_shuffled[v33 - 2] = flag_shuffled[v37];
      flag_shuffled[v37] = v38;
      v34 += 2;
      v33 -= 2LL;
    }
    while ( v33 );
    memcpy(dest, qword_62520, 0x200uLL);
    v39 = 64LL;
    v40 = &dest[1];
    do
    {
      v41 = *(v40 - 1);
      if ( v41 > 0x3F )
        goto PANIC_BOUNDS_CHECK2;
      v42 = flag_shuffled[v39 - 1];
      flag_shuffled[v39 - 1] = flag_shuffled[v41];
      flag_shuffled[v41] = v42;
      v43 = *v40;
      if ( (unsigned __int64)*v40 > 0x3F )
        goto PANIC_BOUNDS_CHECK2;
      v44 = flag_shuffled[v39 - 2];
      flag_shuffled[v39 - 2] = flag_shuffled[v43];
      flag_shuffled[v43] = v44;
      v40 += 2;
      v39 -= 2LL;
    }
    while ( v39 );
    memcpy(dest, qword_62720, 0x200uLL);
    v45 = 64LL;
    v46 = &dest[1];
    do
    {
      v47 = *(v46 - 1);
      if ( v47 > 0x3F )
        goto PANIC_BOUNDS_CHECK2;
      v48 = flag_shuffled[v45 - 1];
      flag_shuffled[v45 - 1] = flag_shuffled[v47];
      flag_shuffled[v47] = v48;
      v49 = *v46;
      if ( (unsigned __int64)*v46 > 0x3F )
        goto PANIC_BOUNDS_CHECK2;
      v50 = flag_shuffled[v45 - 2];
      flag_shuffled[v45 - 2] = flag_shuffled[v49];
      flag_shuffled[v49] = v50;
      v46 += 2;
      v45 -= 2LL;
    }
    while ( v45 );
    memcpy(dest, qword_62920, 0x200uLL);
    ridx = 64LL;
    didx = &dest[1];
    do
    {
      v54 = *(didx - 1);
      if ( v54 > 0x3F )
        goto PANIC_BOUNDS_CHECK2;
      v55 = flag_shuffled[ridx - 1];
      flag_shuffled[ridx - 1] = flag_shuffled[v54];
      flag_shuffled[v54] = v55;
      v56 = *didx;
      if ( (unsigned __int64)*didx > 0x3F )
        goto PANIC_BOUNDS_CHECK2;
      v57 = flag_shuffled[ridx - 2];
      flag_shuffled[ridx - 2] = flag_shuffled[v56];
      flag_shuffled[v56] = v57;
      didx += 2;
      ridx -= 2LL;
    }
    while ( ridx );
    idx = 0LL;
    do
    {
      c = (unsigned __int8)flag_shuffled[idx] + 1;
      LOWORD(tmp) = 1;
      LOWORD(ridx) = 0x101;
      v60 = 0;
      do
      {
        v62 = ridx;
        LOWORD(ridx) = (unsigned __int16)ridx / (unsigned __int16)c;
        v61 = v62 % (unsigned __int16)c;
        v63 = tmp;
        tmp = v60 - (_DWORD)tmp * (_DWORD)ridx;
        LODWORD(ridx) = c;
        c = (unsigned __int16)(v62 % (unsigned __int16)c);
        v60 = v63;
      }
      while ( v61 );
      v64 = 0;
      if ( (__int16)v63 > 0 )
        v64 = v63;
      v65 = (unsigned __int16)(v64 + ((__int16)v63 >> 15) - v63) / 0x101u + v63 + ((unsigned __int16)v63 >> 15);
      LOBYTE(v65) = ((unsigned __int16)(v64 + ((__int16)v63 >> 15) - v63) / 0x101u
                   + v63
                   + ((unsigned __int16)v63 >> 15)
                   + 113) ^ 0x89;
      flag_shuffled[idx] = v65;
      ridx = idx + 1;
      idx = ridx;
    }
    while ( ridx != 0x40 );
  }
  while ( loop_idx != 0x100 );
  v66 = (void *)alloc::raw_vec::RawVec$LT$T$C$A$GT$::allocate_in::h9362616e9151d1f3(255LL, 0LL, v65, 0x40LL, v63, tmp);
  v68 = v67;
  memcpy(v66, &weird_buffer, 0xFFuLL);
  packet = (char *)v66;
  v83 = v68;
  v84 = 255LL;
  alloc::vec::Vec$LT$T$C$A$GT$::resize::h7362553f00beaec8(&packet, 255LL, 0LL);
  if ( *(_DWORD *)(v86 + 16) == -1 )
    core::panicking::panic::h65157a6ac7f1357a((__int64)&unk_61075, 43LL);
  v85 = (int *)(v86 + 16);
  *(_OWORD *)dest = xmmword_60010;
  *(_OWORD *)&dest[2] = xmmword_60020;
  *(_OWORD *)&dest[4] = xmmword_60030;
  *(_OWORD *)&dest[6] = xmmword_60040;
  v69 = v84;
  if ( v84 < 0xCD
    || (packet[0xCC] = *flag_shuffled, v69 < 0xE0)
    || (packet[0xDF] = 0xA7, packet[0xCD] = flag_shuffled[1], v69 == 0xE0)
    || (packet[0xE0] = 0x51, packet[0xCE] = flag_shuffled[2], v69 < 0xE2)
    || (packet[0xE1] = 0x68, packet[0xCF] = flag_shuffled[3], v69 == 0xE2) )
  {
PANIC_BOUNDS_CHECK:
    core::panicking::panic_bounds_check::h7d0e683548e4cb10();
  }
  packet[226] = 0x52;
  _$LT$$RF$std..net..tcp..TcpStream$u20$as$u20$std..io..Write$GT$::write::h0bbfc2d1fa700c7a(
    is_part_correct,
    &v85,
    packet,
    v69);
  if ( is_part_correct[0] )
  {
LABEL_50:
    v71 = _$LT$alloc..boxed..Box$LT$dyn$u20$core..error..Error$GT$$u20$as$u20$core..convert..From$LT$E$GT$$GT$::from::ha6d5ca9d25f6de13(is_part_correct[1]);
LABEL_71:
    v73 = v71;
    if ( v83 )
      _rust_dealloc(packet);
    _rust_dealloc(flag_shuffled);
    return v73;
  }
  is_part_correct[0] = 0LL;
  fail = std::io::default_read_exact::h61fb53e2a02eb302((__int64)&v85, (__int64)is_part_correct, 8uLL);
  if ( fail )
  {
LABEL_55:
    v71 = _$LT$alloc..boxed..Box$LT$dyn$u20$core..error..Error$GT$$u20$as$u20$core..convert..From$LT$E$GT$$GT$::from::ha6d5ca9d25f6de13(fail);
    goto LABEL_71;
  }
  if ( !is_part_correct[0] )
  {
LABEL_70:
    _$LT$alloc..boxed..Box$LT$dyn$u20$core..error..Error$GT$$u20$as$u20$core..convert..From$LT$$RF$str$GT$$GT$::from::hc50629fd4c285201();
    goto LABEL_71;
  }
  idx4 = 4LL;
  do
  {
    v77 = v84;
    if ( v84 < 0xCD )
      goto PANIC_BOUNDS_CHECK;
    v78 = *(_DWORD *)((char *)dest + idx4);
    packet[0xCC] = flag_shuffled[idx4];
    if ( v77 < 0xE0 )
      goto PANIC_BOUNDS_CHECK;
    packet[0xDF] = v78;
    packet[0xCD] = flag_shuffled[idx4 + 1];
    if ( v77 == 224 )
      goto PANIC_BOUNDS_CHECK;
    packet[0xE0] = BYTE1(v78);
    packet[206] = flag_shuffled[idx4 + 2];
    if ( v77 < 0xE2 )
      goto PANIC_BOUNDS_CHECK;
    packet[0xE1] = BYTE2(v78);
    packet[207] = flag_shuffled[idx4 + 3];
    if ( v77 == 0xE2 )
      goto PANIC_BOUNDS_CHECK;
    packet[0xE2] = HIBYTE(v78);
    _$LT$$RF$std..net..tcp..TcpStream$u20$as$u20$std..io..Write$GT$::write::h0bbfc2d1fa700c7a(
      is_part_correct,
      &v85,
      packet,
      v77);
    if ( is_part_correct[0] )
      goto LABEL_50;
    is_part_correct[0] = 0LL;
    fail = std::io::default_read_exact::h61fb53e2a02eb302((__int64)&v85, (__int64)is_part_correct, 8uLL);
    if ( fail )
      goto LABEL_55;
    if ( !is_part_correct[0] )
      goto LABEL_70;
    v80 = (unsigned __int64)(idx4 + 1) <= 0x3C;
    idx4 += 4LL;
  }
  while ( v80 );
  if ( v83 )
    _rust_dealloc(packet);
  _rust_dealloc(flag_shuffled);
  return 0LL;
}