/* This file was generated by the Hex-Rays decompiler version 7.7.0.220118.
   Copyright (c) 2007-2021 Hex-Rays <info@hex-rays.com>

   Detected compiler: GNU C++
*/

#include <defs.h>


//-------------------------------------------------------------------------
// Function declarations

__int64 (**init_proc())(void);
__int64 __fastcall sub_401020(); // weak
void __fastcall __noreturn start(__int64 a1, __int64 a2, void (*a3)(void));
void *sub_4010F0();
void term_proc();
// int __fastcall _libc_start_main(int (__fastcall *main)(int, char **, char **), int argc, char **ubp_av, void (*init)(void), void (*fini)(void), void (*rtld_fini)(void), void *stack_end);
// __int64 _gmon_start__(void); weak

//-------------------------------------------------------------------------
// Data declarations

_UNKNOWN main;
__int64 (*qword_404010)(void) = NULL; // weak
_UNKNOWN unk_404068; // weak


//----- (0000000000401000) ----------------------------------------------------
__int64 (**init_proc())(void)
{
  __int64 (**result)(void); // rax

  result = &_gmon_start__;
  if ( &_gmon_start__ )
    return (__int64 (**)(void))_gmon_start__();
  return result;
}
// 4041F0: using guessed type __int64 _gmon_start__(void);

//----- (0000000000401020) ----------------------------------------------------
__int64 sub_401020()
{
  return qword_404010();
}
// 401020: using guessed type __int64 __fastcall sub_401020();
// 404010: using guessed type __int64 (*qword_404010)(void);

//----- (00000000004010B0) ----------------------------------------------------
// positive sp value has been detected, the output may be wrong!
void __fastcall __noreturn start(__int64 a1, __int64 a2, void (*a3)(void))
{
  __int64 v3; // rax
  int v4; // esi
  __int64 v5; // [rsp-8h] [rbp-8h] BYREF
  char *retaddr; // [rsp+0h] [rbp+0h] BYREF

  v4 = v5;
  v5 = v3;
  _libc_start_main((int (__fastcall *)(int, char **, char **))main, v4, &retaddr, 0LL, 0LL, a3, &v5);
  __halt();
}
// 4010BA: positive sp value 8 has been found
// 4010C1: variable 'v3' is possibly undefined

//----- (00000000004010F0) ----------------------------------------------------
void *sub_4010F0()
{
  return &unk_404068;
}

//----- (0000000000401160) ----------------------------------------------------
__int64 sub_401160()
{
  __int64 result; // rax

  if ( !byte_4040A8 )
  {
    result = sub_4010F0();
    byte_4040A8 = 1;
  }
  return result;
}
// 4010F0: using guessed type __int64 sub_4010F0(void);
// 401160: using guessed type __int64 __fastcall sub_401160();
// 4040A8: using guessed type char byte_4040A8;

//----- (0000000000401190) ----------------------------------------------------
__int64 __fastcall sub_401190(__int64 a1)
{
  return nullsub_1(a1, 0LL);
}
// 401158: using guessed type __int64 __fastcall nullsub_1(_QWORD, _QWORD);

//----- (0000000000401196) ----------------------------------------------------
unsigned __int64 print_chunk()
{
  unsigned __int8 idx; // [rsp+7h] [rbp-9h] BYREF
  unsigned __int64 v2; // [rsp+8h] [rbp-8h]

  v2 = __readfsqword(0x28u);
  puts("Enter index: ");
  __isoc99_scanf("%hhu", &idx);
  if ( idx <= 0xEu && sizes[2 * idx] )
    printf(
      "Name\n last: %s first: %s middle: %s age: %d\nbio: %s",
      chunks[2 * idx]->lastname,
      chunks[2 * idx]->firstname,
      chunks[2 * idx]->middlename,
      chunks[2 * idx]->age,
      (const char *)&chunks[2 * idx]->bio);
  else
    puts("Invalid index");
  return v2 - __readfsqword(0x28u);
}
// 4010A0: using guessed type __int64 __isoc99_scanf(const char *, ...);
// 4040C8: using guessed type _QWORD sizes[27];

//----- (00000000004012EC) ----------------------------------------------------
unsigned __int64 create()
{
  int v0; // ebx
  unsigned __int8 idx; // [rsp+Fh] [rbp-21h] BYREF
  size_t size; // [rsp+10h] [rbp-20h] BYREF
  unsigned __int64 v4; // [rsp+18h] [rbp-18h]

  v4 = __readfsqword(0x28u);
  puts("Enter index: ");
  __isoc99_scanf("%hhu", &idx);
  puts("Enter size (1032 minimum): ");
  __isoc99_scanf("%lu", &size);
  if ( idx > 0xEu || size <= 1031 || sizes[2 * idx] )
  {
    puts("Error with either index or size...");
  }
  else
  {
    v0 = idx;
    chunks[2 * v0] = (chunk *)malloc(size);
    sizes[2 * idx] = size;
    puts("Successfuly added!");
    puts("Input firstname: ");
    read(0, chunks[2 * idx], 8uLL);
    puts("Input middlename: ");
    read(0, chunks[2 * idx]->middlename, 8uLL);
    puts("Input lastname: ");
    read(0, chunks[2 * idx]->lastname, 8uLL);
    puts("Input age: ");
    __isoc99_scanf("%lu", &chunks[2 * idx]->age);
    puts("Input bio: ");
    read(0, &chunks[2 * idx]->bio, 0x100uLL);
  }
  return v4 - __readfsqword(0x28u);
}
// 4010A0: using guessed type __int64 __isoc99_scanf(const char *, ...);
// 4040C8: using guessed type _QWORD sizes[27];

//----- (000000000040155F) ----------------------------------------------------
unsigned __int64 delete()
{
  unsigned __int8 idx; // [rsp+7h] [rbp-9h] BYREF
  unsigned __int64 v2; // [rsp+8h] [rbp-8h]

  v2 = __readfsqword(0x28u);
  printf("Enter index: ");
  __isoc99_scanf("%hhu", &idx);
  if ( idx <= 0xEu && sizes[2 * idx] )
  {
    free(chunks[2 * idx]);
    sizes[2 * idx] = 0LL;
    puts("Successfully Deleted!");
  }
  else
  {
    puts("Either index error or trying to delete something you shouldn't be...");
  }
  return v2 - __readfsqword(0x28u);
}
// 4010A0: using guessed type __int64 __isoc99_scanf(const char *, ...);
// 4040C8: using guessed type _QWORD sizes[27];

//----- (0000000000401646) ----------------------------------------------------
unsigned __int64 edit()
{
  unsigned __int8 idx; // [rsp+7h] [rbp-9h] BYREF
  unsigned __int64 v2; // [rsp+8h] [rbp-8h]

  v2 = __readfsqword(0x28u);
  printf("Enter index: ");
  __isoc99_scanf("%hhu", &idx);
  if ( idx <= 0xEu && sizes[2 * idx] )
  {
    puts("Input firstname: ");
    read(0, chunks[2 * idx], 8uLL);
    puts("Input middlename: ");
    read(0, chunks[2 * idx]->middlename, 8uLL);
    puts("Input lastname: ");
    read(0, chunks[2 * idx]->lastname, 8uLL);
    puts("Input age: ");
    __isoc99_scanf("%lu", &chunks[2 * idx]->age);
    printf("Input bio: (max %d)\n", sizes[2 * idx] - 32LL);
    read(0, &chunks[2 * idx]->bio, sizes[2 * idx] - 0x20LL);
    puts("Successfully edit'd!");
  }
  return v2 - __readfsqword(0x28u);
}
// 4010A0: using guessed type __int64 __isoc99_scanf(const char *, ...);
// 4040C8: using guessed type _QWORD sizes[27];

//----- (0000000000401864) ----------------------------------------------------
unsigned __int64 edit_age()
{
  unsigned __int8 idx; // [rsp+7h] [rbp-9h] BYREF
  unsigned __int64 v2; // [rsp+8h] [rbp-8h]

  v2 = __readfsqword(0x28u);
  printf("Index: ");
  __isoc99_scanf("%hhu", &idx);
  if ( idx > 0xEu )
  {
    puts("Invalid index...");
  }
  else
  {
    printf("new age: ");
    __isoc99_scanf("%lu", &chunks[2 * idx]->age);
    puts("Successfully re-aged!");
  }
  return v2 - __readfsqword(0x28u);
}
// 4010A0: using guessed type __int64 __isoc99_scanf(const char *, ...);

//----- (0000000000401933) ----------------------------------------------------
void __fastcall __noreturn main(int a1, char **a2, char **a3)
{
  __int64 v3; // [rsp+18h] [rbp-38h] BYREF
  __int64 v4[6]; // [rsp+20h] [rbp-30h]

  v4[5] = __readfsqword(0x28u);
  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(stdout, 0LL, 2, 0LL);
  setvbuf(stderr, 0LL, 2, 0LL);
  v4[0] = (__int64)create;
  v4[1] = (__int64)print_chunk;
  v4[2] = (__int64)delete;
  v4[3] = (__int64)edit;
  v4[4] = (__int64)edit_age;
  puts("  ____     _          _ _   ____");
  puts(" / ___|___| |__   ___| | | |___ \\ ");
  puts("| |   / __| '_ \\ / _ \\ | |   __) |");
  puts("| |___\\__ \\ | | |  __/ | |  / __/ ");
  puts(" \\____|___/_| |_|\\___|_|_| |_____|");
  puts(&byte_402293);
  puts("       /\\");
  puts("      {.-}");
  puts("     ;_.-'\\");
  puts("    {    _.}_");
  puts("    \\.-' /  `,");
  puts("     \\  |    /");
  puts("      \\ |  ,/");
  puts("       \\|_/");
  puts(&byte_402293);
  while ( 1 )
  {
    puts("1 Add");
    puts("2 Show");
    puts("3 delete");
    puts("4 edit");
    puts("5 re-age user");
    __isoc99_scanf("%li", &v3);
    if ( v3 > 5 )
      puts("Invalid Choice!");
    else
      ((void (*)(const char *, ...))v4[v3 - 1])("%li", &v3);
  }
}
// 4010A0: using guessed type __int64 __isoc99_scanf(const char *, ...);

//----- (0000000000401B5C) ----------------------------------------------------
void term_proc()
{
  ;
}

// nfuncs=32 queued=13 decompiled=13 lumina nreq=0 worse=0 better=0
// ALL OK, 13 function(s) have been successfully decompiled