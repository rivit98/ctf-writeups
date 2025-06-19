#include <defs.h>


//-------------------------------------------------------------------------
// Function declarations

__int64 (**init_proc())(void);
void sub_1020();
// void free(void *ptr);
// int printf(const char *format, ...);
// ssize_t read(int fd, void *buf, size_t nbytes);
// __int64 __isoc23_scanf(const char *, ...); weak
// void *calloc(size_t nmemb, size_t size);
// void *memcpy(void *dest, const void *src, size_t n);
// int setvbuf(FILE *stream, char *buf, int modes, size_t n);
// void perror(const char *s);
void __fastcall __noreturn start(__int64 a1, __int64 a2, void (*a3)(void));
FILE **sub_10F0();
__int64 sub_1120(void); // weak
FILE **sub_1160();
__int64 sub_11B0();
unsigned __int64 init();
__int64 __fastcall expand(VM **vm, Mem **mem);
int __fastcall main(int argc, const char **argv, const char **envp);
void term_proc();
// int _libc_start_main(int (*main)(int, char **, char **), int argc, char **ubp_av, void (*init)(void), void (*fini)(void), void (*rtld_fini)(void), void *stack_end);
// int _cxa_finalize(void *);
// __int64 _gmon_start__(void); weak

//-------------------------------------------------------------------------
// Data declarations

void *_dso_handle = &_dso_handle; // idb
FILE *_bss_start; // idb
FILE *stdin; // idb
char byte_4028; // weak


//----- (0000000000001000) ----------------------------------------------------
__int64 (**init_proc())(void)
{
  __int64 (**result)(void); // rax

  result = &_gmon_start__;
  if ( &_gmon_start__ )
    return (__int64 (**)(void))_gmon_start__();
  return result;
}
// 4098: using guessed type __int64 _gmon_start__(void);

//----- (0000000000001020) ----------------------------------------------------
void sub_1020()
{
  JUMPOUT(0LL);
}
// 1026: control flows out of bounds to 0

//----- (00000000000010C0) ----------------------------------------------------
// positive sp value has been detected, the output may be wrong!
void __fastcall __noreturn start(__int64 a1, __int64 a2, void (*a3)(void))
{
  __int64 v3; // rax
  int v4; // esi
  __int64 v5; // [rsp-8h] [rbp-8h] BYREF
  char *retaddr; // [rsp+0h] [rbp+0h] BYREF

  v4 = v5;
  v5 = v3;
  _libc_start_main((int (*)(int, char **, char **))main, v4, &retaddr, 0LL, 0LL, a3, &v5);
  __halt();
}
// 10CA: positive sp value 8 has been found
// 10D1: variable 'v3' is possibly undefined

//----- (00000000000010F0) ----------------------------------------------------
FILE **sub_10F0()
{
  return &_bss_start;
}

//----- (0000000000001120) ----------------------------------------------------
__int64 sub_1120()
{
  return 0LL;
}
// 1120: using guessed type __int64 sub_1120();

//----- (0000000000001160) ----------------------------------------------------
FILE **sub_1160()
{
  FILE **result; // rax

  if ( !byte_4028 )
  {
    if ( &_cxa_finalize )
      _cxa_finalize(_dso_handle);
    result = sub_10F0();
    byte_4028 = 1;
  }
  return result;
}
// 4028: using guessed type char byte_4028;

//----- (00000000000011B0) ----------------------------------------------------
// attributes: thunk
__int64 sub_11B0()
{
  return sub_1120();
}
// 1120: using guessed type __int64 sub_1120(void);

//----- (00000000000011B9) ----------------------------------------------------
unsigned __int64 init()
{
  unsigned __int64 v1; // [rsp+8h] [rbp-8h]

  v1 = __readfsqword(0x28u);
  setvbuf(stdin, 0LL, 2, 0LL);
  setvbuf(_bss_start, 0LL, 2, 0LL);
  return v1 - __readfsqword(0x28u);
}

//----- (0000000000001223) ----------------------------------------------------
__int64 __fastcall expand(VM **vm, Mem **mem)
{
  Mem *newmem; // [rsp+18h] [rbp-18h]
  VM *newvm; // [rsp+20h] [rbp-10h]

  newmem = (Mem *)calloc(0x900uLL, 1uLL);
  newvm = (VM *)calloc(0x58uLL, 1uLL);
  if ( newmem == (Mem *)-1LL || newvm == (VM *)-1LL )
  {
    perror("CALLOC FAIL");
    return 1LL;
  }
  else
  {
    memcpy(newmem->stack, (*mem)->stack, 0x800uLL);
    memcpy(newvm, *vm, 0x58uLL);
    newvm->stack_top = (uint8_t *)newmem->stack_top;
    newvm->stack_ptr = &newvm->stack_top[(*vm)->stack_ptr - (*vm)->stack_top];
    newvm->_pc = (uint8_t *)newmem;
    free(*mem);
    free(*vm);
    *mem = newmem;
    *vm = newvm;
    return 0LL;
  }
}

//----- (0000000000001371) ----------------------------------------------------
int __fastcall main(int argc, const char **argv, const char **envp)
{
  int opcode; // eax
  uint8_t *stack_ptr; // rax
  uint8_t *v9; // rax
  char *stack; // rsi
  char *v19; // rsi
  unsigned __int8 v39; // [rsp+Ah] [rbp-36h]
  unsigned __int8 v40; // [rsp+Ah] [rbp-36h]
  unsigned __int8 v41; // [rsp+Ah] [rbp-36h]
  unsigned __int8 v42; // [rsp+Ah] [rbp-36h]
  unsigned __int8 v43; // [rsp+Ah] [rbp-36h]
  unsigned __int8 v44; // [rsp+Ah] [rbp-36h]
  unsigned __int8 v45; // [rsp+Ah] [rbp-36h]
  unsigned __int8 v46; // [rsp+Ah] [rbp-36h]
  unsigned __int8 v47; // [rsp+Ah] [rbp-36h]
  unsigned __int8 v48; // [rsp+Ah] [rbp-36h]
  unsigned __int8 v49; // [rsp+Ah] [rbp-36h]
  unsigned __int8 v50; // [rsp+Ah] [rbp-36h]
  unsigned __int16 bc_size; // [rsp+Ch] [rbp-34h] BYREF
  unsigned __int16 offset; // [rsp+Eh] [rbp-32h]
  int v53; // [rsp+10h] [rbp-30h]
  int v54; // [rsp+14h] [rbp-2Ch]
  Mem *mem; // [rsp+18h] [rbp-28h] BYREF
  VM *vm; // [rsp+20h] [rbp-20h] MAPDST BYREF
  void *dest; // [rsp+28h] [rbp-18h]
  void *src; // [rsp+30h] [rbp-10h]
  unsigned __int64 v59; // [rsp+38h] [rbp-8h]

  v59 = __readfsqword(0x28u);
  init();
  offset = 0;
  bc_size = 257;
  dest = 0LL;
  src = 0LL;
  mem = (Mem *)calloc(0x900uLL, 1uLL);
  vm = (VM *)calloc(0x58uLL, 1uLL);
  if ( mem == (Mem *)-1LL || vm == (VM *)-1LL )
  {
    perror("CALLOC FAIL");
    return 1;
  }
  vm->stack_top = (uint8_t *)mem->stack_top;
  vm->stack_ptr = vm->stack_top;
  vm->_pc = (uint8_t *)mem;
  printf("[ lEn? ] >> ");
  __isoc23_scanf("%hd", &bc_size);
  bc_size = (unsigned __int8)bc_size;
  printf("[ BYTECODE ] >>");
  read(0, mem, bc_size);
  while ( vm->_pc < (uint8_t *)&mem->code[bc_size] )
  {
    opcode = *vm->_pc;
    if ( opcode == 'E' )
    {
      offset = *++vm->_pc;
      vm->_pc = (uint8_t *)&mem->code[offset];
    }
    else if ( *vm->_pc > (unsigned int)'E' )
    {
LABEL_41:
      if ( vm->_pc >= (uint8_t *)&mem->code[bc_size] )
      {
        ++vm->_pc;
      }
      else
      {
        v54 = expand(&vm, &mem);
        if ( v54 == 1 )
        {
          perror("CALLOC FAIL");
          return 1;
        }
        printf("[ lEn? ] >> ");
        __isoc23_scanf("%hd", &bc_size);
        bc_size = (unsigned __int8)bc_size;
        printf("[ BYTECODE ] >>");
        read(0, mem, bc_size);
      }
    }
    else
    {
      switch ( opcode )
      {
        case 'D':
          v50 = *++vm->_pc & 7;
          vm->regs[v50] -= (unsigned __int64)vm->regs[*++vm->_pc & 7];
          ++vm->_pc;
          break;
        case 'C':
          v49 = *++vm->_pc & 7;
          vm->regs[v49] += (unsigned __int64)vm->regs[*++vm->_pc & 7];
          ++vm->_pc;
          break;
        case 'B':
          v48 = *++vm->_pc & 7;
          vm->regs[v48] = (uint8_t *)((__int64)vm->regs[v48] << (__int64)vm->regs[*++vm->_pc & 7]);
          ++vm->_pc;
          break;
        case 'A':
          v47 = *++vm->_pc & 7;
          vm->regs[v47] = (uint8_t *)((unsigned __int64)vm->regs[v47] >> (char)vm->regs[*++vm->_pc & 7]);
          ++vm->_pc;
          break;
        case '@':
          ++vm->_pc;
          vm->regs[*vm->_pc & 7] = (uint8_t *)~(__int64)vm->regs[*vm->_pc & 7];
          ++vm->_pc;
          break;
        case '9':
          v46 = *++vm->_pc & 7;
          vm->regs[v46] = (uint8_t *)((__int64)vm->regs[v46] ^ (__int64)vm->regs[*++vm->_pc & 7]);
          ++vm->_pc;
          break;
        default:
          if ( *vm->_pc > 0x39u )
            goto LABEL_41;
          switch ( opcode )
          {
            case '8':
              v45 = *++vm->_pc & 7;
              vm->regs[v45] = (uint8_t *)((__int64)vm->regs[v45] | (__int64)vm->regs[*++vm->_pc & 7]);
              ++vm->_pc;
              break;
            case '7':
              v44 = *++vm->_pc & 7;
              vm->regs[v44] = (uint8_t *)((__int64)vm->regs[v44] & (__int64)vm->regs[*++vm->_pc & 7]);
              ++vm->_pc;
              break;
            case '6':
              stack = mem->stack;
              dest = &stack[8 * (unsigned __int8)vm->regs[*++vm->_pc & 7]];
              v19 = mem->stack;
              src = &v19[8 * (unsigned __int8)vm->regs[*++vm->_pc & 7]];
              v43 = *++vm->_pc - 1;
              vm->_pc += 2;
              memcpy(dest, src, v43);
              break;
            case '5':
              v42 = *++vm->_pc & 7;
              vm->regs[v42] = *(uint8_t **)++vm->_pc;
              vm->_pc += 8;
              break;
            case '4':
              v41 = *++vm->_pc & 7;
              vm->regs[v41] = vm->regs[*++vm->_pc & 7];
              ++vm->_pc;
              break;
            case '3':
              if ( vm->stack_top >= vm->stack_ptr )
              {
                v40 = *++vm->_pc & 7;
                vm->stack_ptr += 8;
                vm->regs[v40] = *(uint8_t **)vm->stack_ptr;
                ++vm->_pc;
              }
              break;
            case '1':
              if ( vm->stack_ptr >= (uint8_t *)mem->stack )
              {
                v53 = *++vm->_pc;
                stack_ptr = vm->stack_ptr;
                vm->stack_ptr = stack_ptr - 8;
                *(_QWORD *)stack_ptr = v53;
                ++vm->_pc;
              }
              break;
            case '2':
              if ( vm->stack_ptr >= (uint8_t *)mem->stack )
              {
                v39 = *++vm->_pc & 7;
                v9 = vm->stack_ptr;
                vm->stack_ptr = v9 - 8;
                *(_QWORD *)v9 = vm->regs[v39];
                ++vm->_pc;
              }
              break;
            default:
              goto LABEL_41;
          }
          break;
      }
    }
  }
  return 0;
}
// 14CE: conditional instruction was optimized away because eax.4<44u
// 14E0: conditional instruction was optimized away because eax.4<43u
// 14F2: conditional instruction was optimized away because eax.4<42u
// 1504: conditional instruction was optimized away because eax.4<41u
// 1516: conditional instruction was optimized away because eax.4<40u
// 153A: conditional instruction was optimized away because eax.4<38u
// 154C: conditional instruction was optimized away because eax.4<37u
// 155E: conditional instruction was optimized away because eax.4<36u
// 1570: conditional instruction was optimized away because eax.4<35u
// 1582: conditional instruction was optimized away because eax.4<34u
// 1594: conditional instruction was optimized away because eax.4<33u
// 1070: using guessed type __int64 __isoc23_scanf(const char *, ...);

//----- (0000000000001DD8) ----------------------------------------------------
void term_proc()
{
  ;
}
// ALL OK, 11 function(s) have been successfully decompiled
