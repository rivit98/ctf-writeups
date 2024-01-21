#include <defs.h>


//-------------------------------------------------------------------------
// Function declarations

__int64 (**init_proc())(void);
void sub_1020();
// int puts(const char *s);
// size_t strlen(const char *s);
// int printf(const char *format, ...);
// __int64 __isoc99_scanf(const char *, ...); weak
int __fastcall main(int argc, const char **argv, const char **envp);
void __fastcall __noreturn start(__int64 a1, __int64 a2, void (*a3)(void));
char *sub_11A0();
__int64 sub_11D0(void); // weak
char *sub_1210();
__int64 sub_1260();
int __fastcall print_reg(__m128 _XMM0);
unsigned __int64 __fastcall get_index(__int64 a1, unsigned int a2);
unsigned __int64 generate_key();
void term_proc();
// int __fastcall _libc_start_main(int (__fastcall *main)(int, char **, char **), int argc, char **ubp_av, void (*init)(void), void (*fini)(void), void (*rtld_fini)(void), void *stack_end);
// int __fastcall _cxa_finalize(void *);
// __int64 _gmon_start__(void); weak

//-------------------------------------------------------------------------
// Data declarations

void *_dso_handle = &_dso_handle; // idb
_UNKNOWN flags; // weak
__int64 qword_4065 = 7305454551776980341LL; // weak
char _bss_start; // weak


//----- (0000000000001000) ----------------------------------------------------
__int64 (**init_proc())(void)
{
  __int64 (**result)(void); // rax

  result = &_gmon_start__;
  if ( &_gmon_start__ )
    return (__int64 (**)(void))_gmon_start__();
  return result;
}
// 45BDC0: using guessed type __int64 _gmon_start__(void);

//----- (0000000000001020) ----------------------------------------------------
void sub_1020()
{
  JUMPOUT(0LL);
}
// 1026: control flows out of bounds to 0

//----- (0000000000001080) ----------------------------------------------------
int __fastcall main(int argc, const char **argv, const char **envp)
{
  __m256 v12; // [rsp+0h] [rbp-60h] BYREF
  char v13; // [rsp+20h] [rbp-40h]
  unsigned __int64 v14; // [rsp+38h] [rbp-28h]

  __asm { vpxor   xmm0, xmm0, xmm0 }
  v14 = __readfsqword(0x28u);
  v13 = 0;
  __asm
  {
    vmovdqa xmmword ptr [rsp+60h+var_60], xmm0
    vmovdqa xmmword ptr [rsp+60h+var_60+10h], xmm0
  }
  puts(
    "\n"
    "    ....                              \n"
    "    .###..+########-.                 \n"
    "    ..-#..+#########..-++++-.         \n"
    "       -+..+#########.########-.      \n"
    "       .+- .##########-####+-..       \n"
    "        .#-.-#########+-########+..   \n"
    "         .#.+#-....+##+.#####+--...   \n"
    "          -+.      .+#-###+..         \n"
    "          .++        ......           \n"
    "           .#-.                       \n"
    "            .#-   INSOMNI'HACK        \n"
    "             -#.      FLAG            \n"
    "             .-#.         SYSTEM      \n"
    "               ++.            v.1.0   \n"
    "\n");
  do
  {
    printf("Enter the flag: ");
    __isoc99_scanf("%32s", &v12);
  }
  while ( strlen((const char *)&v12) != 32 );
  generate_key();
  __asm
  {
    vmovdqa ymm1, ymm0
    vpermq  ymm0, [rsp+60h+var_60], 1Bh
    vaesenc ymm0, ymm0, ymm1
    vpcmpeqq ymm0, ymm0, cs:ymmword_22C0
    vpmovmskb eax, ymm0
  }
  if ( _EAX == -1 )
  {
    __asm { vzeroupper }
    printf("\nCongratz you found the correct flag: %32s", (const char *)&v12);
  }
  else
  {
    __asm { vzeroupper }
    printf("\nWrong flag ! Did you try `strings` already ?");
  }
  return 0;
}
// 1070: using guessed type __int64 __isoc99_scanf(const char *, ...);

//----- (0000000000001170) ----------------------------------------------------
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
// 117A: positive sp value 8 has been found
// 1181: variable 'v3' is possibly undefined

//----- (00000000000011A0) ----------------------------------------------------
char *sub_11A0()
{
  return &_bss_start;
}
// 45BD70: using guessed type char _bss_start;

//----- (00000000000011D0) ----------------------------------------------------
__int64 sub_11D0()
{
  return 0LL;
}
// 11D0: using guessed type __int64 sub_11D0();

//----- (0000000000001210) ----------------------------------------------------
char *sub_1210()
{
  char *result; // rax

  if ( !_bss_start )
  {
    if ( &_cxa_finalize )
      _cxa_finalize(_dso_handle);
    result = sub_11A0();
    _bss_start = 1;
  }
  return result;
}
// 45BD70: using guessed type char _bss_start;

//----- (0000000000001260) ----------------------------------------------------
// attributes: thunk
__int64 sub_1260()
{
  return sub_11D0();
}
// 11D0: using guessed type __int64 sub_11D0(void);

//----- (0000000000001270) ----------------------------------------------------
int __fastcall print_reg(__m128 _XMM0)
{
  __asm
  {
    vextracti128 xmm1, ymm0, 1
    vpextrq rdx, xmm0, 1
    vmovq   rsi, xmm0
    vmovq   rcx, xmm1
    vpextrq r8, xmm1, 1
    vzeroupper
  }
  return printf("%lx %lx %lx %lx\n", _RSI, _RDX, _RCX, _R8);
}

//----- (00000000000012A0) ----------------------------------------------------
unsigned __int64 __fastcall get_index(__int64 a1, unsigned int a2)
{
  return *(_QWORD *)(a1 + a2) % 0x21B10uLL;
}

//----- (00000000000012D0) ----------------------------------------------------
unsigned __int64 generate_key()
{
  unsigned __int64 result; // rax

  _R8 = &flags;
  _R11 = (char *)&flags + 32 * (qword_4065 % 0x21B10uLL);
  __asm
  {
    vmovdqu ymm0, ymmword ptr [r11]
    vpermd  ymm0, ymm0, ymmword ptr [r10]
  }
  _R9 = (char *)&flags + 32 * (*(_QWORD *)((char *)&flags + 32 * (*(_QWORD *)(_R11 + 5) % 0x21B10uLL) + 5) % 0x21B10uLL);
  __asm
  {
    vmovdqu ymm1, ymmword ptr [r9]
    vpshufb ymm1, ymm1, ymm0
  }
  _RDI = (char *)&flags + 32 * (*(_QWORD *)(_R9 + 5) % 0x21B10uLL);
  __asm
  {
    vmovdqu ymm2, ymmword ptr [rdi]
    vpermd  ymm2, ymm2, ymmword ptr [rsi]
  }
  result = 0xF325E7208F6B5B55LL * *(_QWORD *)((char *)&flags + 32 * (*(_QWORD *)(_RDI + 5) % 0x21B10uLL) + 5);
  _RSI = 32 * (*(_QWORD *)((char *)&flags + 32 * (*(_QWORD *)(_RDI + 5) % 0x21B10uLL) + 5) % 0x21B10uLL);
  __asm
  {
    vmovdqu ymm0, ymmword ptr [r8+rsi]
    vpshufb ymm0, ymm0, ymm2
    vpxor   ymm0, ymm0, ymm1
  }
  return result;
}
// 4065: using guessed type __int64 qword_4065;

//----- (00000000000013C8) ----------------------------------------------------
void term_proc()
{
  ;
}

// nfuncs=25 queued=12 decompiled=12 lumina nreq=0 worse=0 better=0
// ALL OK, 12 function(s) have been successfully decompiled
