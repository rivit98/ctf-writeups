#include <windows.h>
#include <defs.h>


//-------------------------------------------------------------------------
// Function declarations

_OWORD *prepare_shellcode1();
BOOL __stdcall CryptSetKeyParam_(HCRYPTKEY hKey, DWORD dwParam, const BYTE *pbData, DWORD dwFlags);
__int64 sub_7FF7E5923474();
__int64 __fastcall UserMathErrorFunction(struct _exception *a1);
void sub_7FF7E5923534();
char sub_7FF7E5923544();
void *sub_7FF7E592354C();
void *sub_7FF7E5923554();
void *sub_7FF7E5923584();
void *sub_7FF7E592358C();
void sub_7FF7E5923594();
bool sub_7FF7E59236F0();
void sub_7FF7E59237B0();
void __fastcall sub_7FF7E59237EC();
__int64 sub_7FF7E5923828();
__int64 __fastcall sub_7FF7E5923B0C(PEXCEPTION_RECORD ExceptionRecord, PVOID TargetFrame, __int64 a3, __int64 a4);
// __vcrt_bool __cdecl _vcrt_uninitialize(__vcrt_bool Terminating);
// __int64 __fastcall _DestructExceptionObject(_QWORD, _QWORD); weak
// __int64 __fastcall _AdjustPointer(_QWORD, _QWORD); weak
void *__cdecl memset_(void *, int Val, size_t Size);
__m128i *__fastcall init_sth(context *ctx, unsigned __int8 param2, unsigned __int64 param3);
// __int64 __fastcall NLG_Notify(_QWORD, _QWORD, _QWORD); weak
// __int64 _NLG_Return2(void); weak
// __int64 __fastcall _except_validate_context_record(_QWORD); weak
// __int64 _vcrt_getptd(void); weak
__int64 __fastcall sub_7FF7E5924838(__int64 a1, int a2);
// bool __fastcall __FrameHandler3::ExecutionInCatch(struct _xDISPATCHER_CONTEXT *, const struct _s_FuncInfo *); idb
_QWORD *__fastcall sub_7FF7E592492C(_QWORD *a1, unsigned __int64 *a2, __int64 a3, _QWORD *a4);
// __int64 __fastcall __FrameHandler3::GetRangeOfTrysToCheck(_DWORD, _DWORD, _DWORD, _DWORD, __int64); weak
// void __fastcall __FrameHandler3::UnwindNestedFrames(unsigned __int64 *, struct EHExceptionRecord *, struct _CONTEXT *, unsigned __int64 *, void *, const struct _s_FuncInfo *, int, int, const struct _s_HandlerType *, struct _xDISPATCHER_CONTEXT *, char); idb
// __int64 GetImageBase(void); weak
// __int64 GetThrowImageBase(void); weak
// __int64 __fastcall SetThrowImageBase(_QWORD); weak
// void *__cdecl memmove(void *, const void *Src, size_t Size);
__int64 __fastcall sub_7FF7E5925458(_QWORD *a1, unsigned __int64 *a2, __int64 a3);
__int64 __fastcall sub_7FF7E5925480(_QWORD *a1, unsigned __int64 *a2, __int64 a3);
__int64 __fastcall sub_7FF7E59254B8(_QWORD *a1, unsigned __int64 *a2, __int64 a3, int a4);
__int64 __fastcall sub_7FF7E59254F4(__int64 a1, unsigned __int64 *a2);
__int64 __fastcall sub_7FF7E59254FC(__int64 a1, __int64 a2, unsigned __int64 a3);
__int64 __fastcall sub_7FF7E5925564(__int64 a1, __int64 *a2, int *a3, __int64 a4);
// __int64 __usercall CatchIt<__FrameHandler3>@<rax>(struct EHExceptionRecord *@<rcx>, unsigned __int64 *@<rdx>, struct _s_FuncInfo *, struct _s_HandlerType *, __int64, __int64, int, int, int, char); idb
__int64 __fastcall sub_7FF7E59258F8(struct EHExceptionRecord *a1, unsigned __int64 *a2, struct _CONTEXT *a3, struct _xDISPATCHER_CONTEXT *a4, struct _s_FuncInfo *a5, char a6, int a7, __int64 a8);
// __int64 __usercall FindHandlerForForeignException<__FrameHandler3>@<rax>(struct EHExceptionRecord *@<rcx>, struct _s_FuncInfo *, int, int, int); idb
// __int64 __fastcall TypeMatchHelper<__FrameHandler3>(_QWORD, _QWORD, _QWORD); weak
// __int64 __usercall __InternalCxxFrameHandler<__FrameHandler3>@<rax>(struct EHExceptionRecord *@<rcx>, unsigned __int64 *@<rdx>, struct _s_FuncInfo *, int, int, char); idb
__int64 __fastcall sub_7FF7E592636C(__int64 a1, __int64 a2);
_QWORD *__fastcall sub_7FF7E59263A8(_QWORD *a1);
// static int __stdcall __FrameHandler3::GetHandlerSearchState(unsigned __int64 *, struct _xDISPATCHER_CONTEXT *, const struct _s_FuncInfo *); idb
// unsigned __int8 __fastcall IsInExceptionSpec(struct EHExceptionRecord *, const struct _s_ESTypeList *); idb
// unsigned __int8 __fastcall Is_bad_exception_allowed(const struct _s_ESTypeList *); idb
__int64 __fastcall sub_7FF7E5926B60(__int64 a1, __int64 a2, __int64 a3, unsigned int a4);
// __int64 __fastcall _std_exception_copy(_QWORD); weak
// void __stdcall __noreturn CxxThrowException(void *pExceptionObject, _ThrowInfo *pThrowInfo);
__int64 sub_7FF7E5927728();
void __fastcall sub_7FF7E5927730(int a1);
void __fastcall sub_7FF7E5927758(__int64 a1);
// __int64 __fastcall unknown_libname_14(void *Block); idb
__int64 __fastcall sub_7FF7E5927E10(void **a1);
__int64 __fastcall sub_7FF7E5927E2C(void **a1);
void __fastcall sub_7FF7E592824C(__int64 a1);
int *sub_7FF7E5928334();
void **sub_7FF7E592833C();
__int64 sub_7FF7E592845C();
void *sub_7FF7E5928490();
int __fastcall sub_7FF7E59287E0(_onexit_t Function);
// int __cdecl register_onexit_function(_onexit_table_t *Table, _onexit_t Function);
__vcrt_bool sub_7FF7E592892C();
// void __noreturn terminate(void); weak
// void __cdecl __noreturn abort();
void __fastcall sub_7FF7E5928D80(__int64 a1);
// __int64 __fastcall invalid_parameter_internal(wchar_t *Expression, wchar_t *FunctionName, wchar_t *FileName, unsigned int LineNo, uintptr_t, __crt_cached_ptd_host *); idb
__int64 __fastcall sub_7FF7E5929224(__int64 a1, __int64 *a2);
__int64 __fastcall sub_7FF7E5929258(__int64 a1, __int64 *a2, __int64 a3);
__int64 __fastcall sub_7FF7E5929290(__int64 a1, __int64 *a2);
__int64 __fastcall sub_7FF7E59292C4(__int64 a1, __int64 *a2, __int64 a3);
// __int64 _acrt_update_thread_multibyte_data(void); weak
void __fastcall sub_7FF7E592B9D0(int a1);
void __fastcall sub_7FF7E592BA24(int a1);
void __fastcall sub_7FF7E592BC1C(int a1);
void __fastcall sub_7FF7E592BC44(int a1);
// __int64 _acrt_update_thread_locale_data(void); weak
char sub_7FF7E592CECC();
void __fastcall sub_7FF7E592CFB4(__int64 a1);
void __fastcall sub_7FF7E592D804(__int64 a1);
void __fastcall sub_7FF7E592D810(__int64 a1);
BOOL sub_7FF7E5930BC8();
// __int64 __fastcall __crt_seh_guarded_call<int>::operator()<_lambda_ad8af0d99a0adf03d037d7dffe354bb5_,_lambda_c9ba49e555ba839a7b07aa3fbecb7617_ &,_lambda_2f1ebd5d68526518146ae959c9e734c8_>(_QWORD, _QWORD, _QWORD, _QWORD); weak
__int64 __fastcall sub_7FF7E5930D1C(int a1, __int64 a2);
// __int64 __fastcall IsNonwritableInCurrentImage(_QWORD); weak
_BOOL8 __fastcall sub_7FF7E5931790(__int64 a1);
_QWORD *__fastcall sub_7FF7E59317BC(_QWORD *a1, char a2);
void __cdecl j_j_free(void *Block);
__int64 __fastcall sub_7FF7E5931E7C(__int64 a1, __int64 a2);
bool __fastcall dyn_func(QWORD *a1);

//-------------------------------------------------------------------------
// Data declarations

// extern BOOL (__stdcall *CryptDecrypt)(HCRYPTKEY hKey, HCRYPTHASH hHash, BOOL Final, DWORD dwFlags, BYTE *pbData, DWORD *pdwDataLen);
// extern BOOL (__stdcall *CryptSetKeyParam)(HCRYPTKEY hKey, DWORD dwParam, const BYTE *pbData, DWORD dwFlags);
// extern BOOL (__stdcall *CloseHandle)(HANDLE hObject);
// extern BOOL (__stdcall *VirtualProtect)(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);
// extern LPVOID (__stdcall *VirtualAlloc)(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
// extern BOOL (__stdcall *QueryPerformanceCounter)(LARGE_INTEGER *lpPerformanceCount);
// extern DWORD (__stdcall *GetCurrentProcessId)();
// extern DWORD (__stdcall *GetCurrentThreadId)();
// extern void (__stdcall *GetSystemTimeAsFileTime)(LPFILETIME lpSystemTimeAsFileTime);
// extern void (__stdcall *InitializeSListHead)(PSLIST_HEADER ListHead);
// extern PRUNTIME_FUNCTION (__stdcall *RtlLookupFunctionEntry)(ULONG64 ControlPc, PULONG64 ImageBase, PUNWIND_HISTORY_TABLE HistoryTable);
// extern HMODULE (__stdcall *GetModuleHandleW)(LPCWSTR lpModuleName);
// extern void (__stdcall *RtlUnwindEx)(PVOID TargetFrame, PVOID TargetIp, PEXCEPTION_RECORD ExceptionRecord, PVOID ReturnValue, PCONTEXT ContextRecord, PUNWIND_HISTORY_TABLE HistoryTable);
// extern void (__stdcall *EnterCriticalSection)(LPCRITICAL_SECTION lpCriticalSection);
// extern void (__stdcall *LeaveCriticalSection)(LPCRITICAL_SECTION lpCriticalSection);
__int64 (__fastcall *off_7FF7E59333E0)() = &_DestructExceptionObject; // weak
void *std::exception::`vftable' = &unknown_libname_3; // weak
void *std::bad_exception::`vftable' = &unknown_libname_3; // weak
void *type_info::`vftable' = &sub_7FF7E59317BC; // weak
void (*qword_7FF7E593B528[2])(void) = { NULL, NULL }; // weak
void (*qword_7FF7E593B538)(void) = NULL; // weak
const _ThrowInfo _TI2_AVbad_exception_std__ = { 0u, 25596, 0, 116144 }; // idb
int dword_7FF7E593E008 = 1; // weak
int dword_7FF7E593E00C = 2; // weak
__int64 qword_7FF7E593E010 = 524288i64; // weak
__int64 qword_7FF7E593E018 = 33554432i64; // weak
__int64 qword_7FF7E593E020 = -47936899621427i64; // weak
uintptr_t _security_cookie = 47936899621426ui64;
int dword_7FF7E593E7B0 = -2; // weak
HANDLE hObject = (HANDLE)0xFFFFFFFFFFFFFFFEi64; // idb
union _SLIST_HEADER stru_7FF7E59698A0 = { { 0ui64, 0ui64 } }; // weak
_UNKNOWN unk_7FF7E59698B0; // weak
_UNKNOWN unk_7FF7E59698B8; // weak
int dword_7FF7E59698C0 = 0; // weak
int dword_7FF7E59698C4 = 0; // weak
__int64 (*qword_7FF7E59698C8)(void) = NULL; // weak
int dword_7FF7E5969A30; // weak
__int64 qword_7FF7E5969A38; // weak
void *qword_7FF7E5969B58; // idb
void *qword_7FF7E5969B60; // idb
__int64 qword_7FF7E5969B70; // weak
int dword_7FF7E5969B88; // weak
void *qword_7FF7E5969B90; // idb
int dword_7FF7E5969BB4; // weak
_UNKNOWN unk_7FF7E5969BB8; // weak
_onexit_table_t stru_7FF7E5969BC0; // idb
__int64 qword_7FF7E5969BF0; // weak
__int64 qword_7FF7E5969BF8[]; // weak
struct __crt_multibyte_data *Block; // idb
_UNKNOWN unk_7FF7E5969C20; // weak
__int64 qword_7FF7E5969E60[128]; // weak
int dword_7FF7E596A260; // weak
HANDLE hHeap; // idb
__int64 qword_7FF7E596A410; // weak
HCRYPTKEY hKey; // idb
_UNKNOWN unk_7FF7E596A9F8; // weak
_UNKNOWN unk_7FF7E596AA00; // weak


//----- (00007FF7E5921000) ----------------------------------------------------
size_t __cdecl strnlen_(const char *String, size_t MaxCount)
{
  if ( String )
    return strnlen(String, MaxCount);
  else
    return 0i64;
}

//----- (00007FF7E5921010) ----------------------------------------------------
BOOL sub_140001010()
{
  return ExitWindowsEx(0, 0xFFFFFFFF);
}

//----- (00007FF7E5921020) ----------------------------------------------------
int __cdecl main(int argc, const char **argv, const char **envp)
{
  const char *param; // rdx MAPDST
  bool is_5th_char_ok; // cl
  int (__fastcall *rwx)(QWORD *); // rdi
  DWORD TickCount; // eax
  const char *param_; // rcx
  __int64 v11; // rdx
  __int64 v12; // r8
  DWORD mem_perms; // [rsp+2Ch] [rbp-D4h]
  __int128 v14; // [rsp+30h] [rbp-D0h]
  QWORD v15[2]; // [rsp+40h] [rbp-C0h] BYREF
  char *v16; // [rsp+50h] [rbp-B0h]
  _BYTE v17[48]; // [rsp+58h] [rbp-A8h]
  char v18[8]; // [rsp+88h] [rbp-78h] BYREF
  _no_idea additional_data; // [rsp+90h] [rbp-70h] BYREF
  context ctx; // [rsp+D0h] [rbp-30h] BYREF
  QWORD v21; // [rsp+5A0h] [rbp+4A0h] BYREF

  if ( argc != 2 )
    return 0;
  param = argv[1];
  mem_perms = param[6];
  if ( *param != '0' )
    logout();
  param = argv[1];
  if ( param[2] + 4 * param[1] != 295 )
  {
    logout();
    return 0;
  }
  HIDWORD(v15[0]) = 'zpiz';
  LOWORD(v15[1]) = 'a';
  v16 = aAzbqcedtexfhgo;
  is_5th_char_ok = param[5] == 'R';
  *(_QWORD *)v17 = '\xCA\xFE\0\0\xCB]';
  *(_QWORD *)&v14 = 0xE685500000000i64;
  *((_QWORD *)&v14 + 1) = mem_perms | 0x4000000000i64;
  strcpy((char *)v15, "R% ");
  v18[2] = is_5th_char_ok;
  strcpy(&v18[3], "fin");
  v18[7] = 0;
  strcpy(v18, "_");
  *(_OWORD *)&v17[8] = v14;
  *(_OWORD *)&v17[0x18] = *(_OWORD *)v15;
  *(_OWORD *)&additional_data.f1 = *(_OWORD *)v17;
  *(_OWORD *)&additional_data.f3 = *(_OWORD *)&v17[16];
  *(__m128d *)additional_data.f5 = _mm_unpacklo_pd(*(__m128d *)&v17[32], (__m128d)(unsigned __int64)aAzbqcedtexfhgo);
  additional_data.f7 = *(_QWORD *)v18;
  if ( !is_5th_char_ok )
    return 0;
  rwx = (int (__fastcall *)(QWORD *))VirtualAlloc(0i64, 0x99ui64, 0x3000u, mem_perms);
  if ( !rwx )
    return additional_data.arg_idx;
  init_sth(&ctx, 0, 0x4A8ui64);
  TickCount = GetTickCount();
  param_ = argv[1];
  ctx.TickCount = TickCount;
  LODWORD(v21) = 0;
  WORD2(v21) = 0;
  LODWORD(v21) = *(_DWORD *)(param_ + 7);
  BYTE4(v21) = param_[11];
  *(_OWORD *)rwx = *(_OWORD *)dyn_func;
  *((_OWORD *)rwx + 1) = *(_OWORD *)((char *)&loc_7FF7E593EA0D + 3);
  *((_OWORD *)rwx + 2) = *(_OWORD *)((char *)&loc_7FF7E593EA1F + 1);
  *((_OWORD *)rwx + 3) = loc_7FF7E593EA30;
  *((_OWORD *)rwx + 4) = loc_7FF7E593EA40;
  *((_OWORD *)rwx + 5) = *(_OWORD *)((char *)&loc_7FF7E593EA4F + 1);
  *((_OWORD *)rwx + 6) = loc_7FF7E593EA60;
  *((_OWORD *)rwx + 7) = *(_OWORD *)((char *)&loc_7FF7E593EA6E + 2);
  *((_OWORD *)rwx + 8) = *(_OWORD *)((char *)&loc_7FF7E593EA7E + 2);
  *((_QWORD *)rwx + 18) = loc_7FF7E593EA90;
  *((_BYTE *)rwx + 152) = locret_7FF7E593EA98;
  *((_BYTE *)rwx + 65) = argv[1][12];
  ((void (__fastcall *)(QWORD *, __int64, __int64))rwx)(&v21, v11, v12);
  strcpy_s(ctx.argv, 0x100ui64, argv[1]);
  ctx.additional_data = &additional_data;
  ctx.GetTickCount = GetTickCount;
  ctx.GetProcAddress = GetProcAddress;
  ctx.LoadLibraryW = LoadLibraryW;
  ctx.GetModuleFileNameW = GetModuleFileNameW;
  ctx.CreateFileW = CreateFileW;
  ctx.ReadFile = ReadFile;
  ctx.WriteFile = WriteFile;
  ctx.Sleep = Sleep;
  ctx.ExitProcess = ExitProcess;
  ctx.VirtualAlloc = VirtualAlloc;
  ctx.free = (void (__stdcall *)(void *))free;
  ctx.GetStdHandle = GetStdHandle;
  ctx.strtol = (__int64 (__stdcall *)())strtol;
  ctx.strnlen_ = (__int64 (__stdcall *)(char *))strnlen_;
  ctx.get_arg = (__int64 (__stdcall *)(BYTE *))get_arg;
  ctx.crypt_sth = (__int64 (__stdcall *)(BYTE *))crypt_sth;
  ctx.CryptSetKeyParam_ = (__int64 (__stdcall *)())CryptSetKeyParam_;
  ctx.open_html = (__int64 (__stdcall *)())open_html;
  ctx.long_func = (__int64 (__stdcall *)(__int64))check_4th_part;
  run_vm(&ctx);
  return additional_data.arg_idx;
}
// 7FF7E5921299: variable 'v11' is possibly undefined
// 7FF7E5921299: variable 'v12' is possibly undefined
// 7FF6A5A3FFFE: using guessed type __int64 (__fastcall *)(_QWORD, _QWORD, _QWORD);

//----- (00007FF7E59213E0) ----------------------------------------------------
__int64 __fastcall run_vm(context *ctx)
{
  char *first_slash; // rax
  void (__stdcall __noreturn **p_ExitProcess)(UINT); // r15
  char *second_slash; // rbx
  int number_between_slashes; // esi
  unsigned __int64 digits_num2; // rdi
  int max_len; // eax MAPDST
  WCHAR *lpWideCharStr; // rax
  WCHAR *v11; // r14
  void (__fastcall *wsprintfW)(char *, WCHAR *, wchar_t *); // r12
  HANDLE fd; // r12
  int v14; // ecx
  int digits_num; // ebx
  __int64 v16; // r8 MAPDST
  _BYTE *number_between_slashes_str; // rax MAPDST
  _BYTE *v20; // r9
  int v21; // ecx
  unsigned __int64 i; // rdx
  int v23; // eax
  __int64 v24; // rcx
  char sth_weekday; // dl
  __m128i v26; // xmm2
  const __m128i *v27; // rax
  __m128i v28; // xmm2
  __m128i v29; // xmm2
  __m128i v30; // xmm0
  _BYTE *v31; // rax
  __int64 v32; // rcx
  __int64 v33; // rdx
  __int64 v34; // r8
  _OWORD *v35; // rax
  char v37[16]; // [rsp+40h] [rbp-C0h] BYREF
  char v38[16]; // [rsp+50h] [rbp-B0h] BYREF
  WCHAR format[8]; // [rsp+60h] [rbp-A0h] BYREF
  wchar_t current_exe_path[296]; // [rsp+70h] [rbp-90h] BYREF
  char bytes_written; // [rsp+2D0h] [rbp+1D0h] BYREF
  char *lpMultiByteStr; // [rsp+2D8h] [rbp+1D8h] MAPDST BYREF
  _OWORD *rwx; // [rsp+2E0h] [rbp+1E0h]
  void *argv; // [rsp+2E8h] [rbp+1E8h]

  argv = strdup(ctx->argv);
  first_slash = strchr((const char *)argv, '/');
  lpMultiByteStr = first_slash;
  p_ExitProcess = &ctx->ExitProcess;
  if ( !first_slash )
  {
    ((void (__fastcall *)(__int64))*p_ExitProcess)(2i64);
    first_slash = lpMultiByteStr;
  }
  lpMultiByteStr = first_slash + 1;
  second_slash = strchr(first_slash + 2, '/');
  if ( !second_slash )
    ((void (__fastcall *)(__int64))*p_ExitProcess)(2i64);
  *second_slash = 0;
  number_between_slashes = strtol(lpMultiByteStr, &lpMultiByteStr, 10);
  ((void (__fastcall *)(_QWORD, wchar_t *, __int64))ctx->GetModuleFileNameW)(0i64, current_exe_path, 260i64);
  *wcsrchr(current_exe_path, '\\') = 0;
  rwx = (_OWORD *)((__int64 (__fastcall *)(const wchar_t *))ctx->LoadLibraryW)(L"user32.dll");
  if ( !rwx )
    ((void (__fastcall *)(__int64))*p_ExitProcess)(2i64);
  digits_num2 = -1i64;
  if ( lpMultiByteStr )
  {
    max_len = MultiByteToWideChar(0xFDE9u, 0, lpMultiByteStr, -1, 0i64, 0);
    if ( max_len )
    {
      lpWideCharStr = (WCHAR *)j__malloc_base(2i64 * max_len);
      v11 = lpWideCharStr;
      if ( lpWideCharStr )
      {
        if ( !MultiByteToWideChar(0xFDE9u, 0, lpMultiByteStr, -1, lpWideCharStr, max_len) )
          free(v11);
      }
    }
  }
  strcpy(v38, "wsprintfW");
  wsprintfW = (void (__fastcall *)(char *, WCHAR *, wchar_t *))((__int64 (__fastcall *)(_OWORD *, char *))ctx->GetProcAddress)(
                                                                 rwx,
                                                                 v38);
  if ( !wsprintfW )
    ((void (__fastcall *)(__int64))*p_ExitProcess)(2i64);
  *(_DWORD *)format = 's\0%';
  *(_DWORD *)&format[2] = '%\0\\';
  *(_DWORD *)&format[4] = 's';
  wsprintfW(ctx->fname, format, current_exe_path);
  fd = (HANDLE)((__int64 (__fastcall *)(char *, __int64, __int64))ctx->CreateFileW)(ctx->fname, 0x40000000i64, 1i64);
  if ( fd == (HANDLE)-1i64 )
    ((void (__fastcall *)(__int64))*p_ExitProcess)(2i64);
  // calculate number length
  v14 = number_between_slashes;
  digits_num = 0;
  // take number duplicate its digits and convert to hex number
  do
  {
    v16 = digits_num++;
    v14 /= 10;
  }
  while ( v14 );
  number_between_slashes_str = j__malloc_base(v16 + 2);
  if ( number_between_slashes_str )
  {
    if ( number_between_slashes )
    {
      v20 = &number_between_slashes_str[v16];
      do
      {
        *v20-- = number_between_slashes % 10 + '0';
        number_between_slashes /= 10;
      }
      while ( number_between_slashes );
    }
    v21 = 0;
    number_between_slashes_str[digits_num] = 0;
    do
      ++digits_num2;
    while ( number_between_slashes_str[digits_num2] );
    for ( i = 0i64; i < digits_num2; v21 = (v23 - '0') | (16 * ((v23 - '0') | (16 * v21))) )
      v23 = (char)number_between_slashes_str[i++];
  }
  else
  {
    v21 = 0;
  }
  duplicated_number = v21;
  tick_cnt = GetTickCount();
  GetLocalTime(&SystemTime);
  v24 = 0xAA0i64;
  sth_weekday = dword_7FF7E593EBC0 + LOBYTE(SystemTime.wDay);
  v26 = _mm_cvtsi32_si128((char)(dword_7FF7E593EBC0 + LOBYTE(SystemTime.wDay)));
  v27 = (const __m128i *)&unk_7FF7E593EBF0;
  v28 = _mm_unpacklo_epi8(v26, v26);
  v29 = _mm_shuffle_epi32(_mm_unpacklo_epi16(v28, v28), 0);
  do
  {
    v30 = _mm_loadu_si128(v27 - 1);
    v27 += 4;
    v27[-5] = _mm_add_epi8(v30, v29);
    v27[-4] = _mm_add_epi8(_mm_loadu_si128(v27 - 4), v29);
    v27[-3] = _mm_add_epi8(v29, _mm_loadu_si128(v27 - 3));
    v27[-2] = _mm_add_epi8(v29, _mm_loadu_si128(v27 - 2));
    --v24;
  }
  while ( v24 );
  v31 = &unk_7FF7E59693E0;
  v32 = 55i64;
  do
  {
    *v31++ += sth_weekday;
    --v32;
  }
  while ( v32 );
  ((void (__fastcall *)(HANDLE, int *, __int64, char *, _QWORD))ctx->WriteFile)(
    fd,
    &duplicated_number,
    0x2A888i64,
    &bytes_written,
    0i64);
  CloseHandle(fd);
  free(argv);
  strcpy(v37, "turnitup");
  ((void (__fastcall *)(char *))ctx->crypt_sth)(v37);
  ((void (__fastcall *)(void (__fastcall *)(), __int64))ctx->CryptSetKeyParam_)(dyn_func2, 176i64);
  rwx = (_OWORD *)((__int64 (__fastcall *)(_QWORD, __int64, __int64, __int64))ctx->VirtualAlloc)(
                    0i64,
                    176i64,
                    12288i64,
                    64i64);
  if ( !rwx )
    ((void (__fastcall *)(_QWORD))*p_ExitProcess)((unsigned int)ctx->additional_data->arg_idx);
  v35 = rwx;
  *rwx = *(_OWORD *)dyn_func2;
  v35[1] = *((_OWORD *)dyn_func2 + 1);
  v35[2] = *((_OWORD *)dyn_func2 + 2);
  v35[3] = *((_OWORD *)dyn_func2 + 3);
  v35[4] = *((_OWORD *)dyn_func2 + 4);
  v35[5] = *((_OWORD *)dyn_func2 + 5);
  v35[6] = *((_OWORD *)dyn_func2 + 6);
  v35[7] = *((_OWORD *)dyn_func2 + 7);
  v35[8] = *((_OWORD *)dyn_func2 + 8);
  v35[9] = *((_OWORD *)dyn_func2 + 9);
  v35[10] = *((_OWORD *)dyn_func2 + 10);
  return ((__int64 (__fastcall *)(context *, __int64, __int64))rwx)(ctx, v33, v34);
}
// 7FF7E5921892: variable 'v33' is possibly undefined
// 7FF7E5921892: variable 'v34' is possibly undefined
// 7FF6A5A3FFFE: using guessed type __int64 (__fastcall *)(_QWORD, _QWORD, _QWORD);
// 7FF7E593A8A0: using guessed type wchar_t aUser32Dll_0[11];
// 7FF7E593EB90: using guessed type int duplicated_number;
// 7FF7E593EBC0: using guessed type int dword_7FF7E593EBC0;
// 7FF7E593EBC4: using guessed type int tick_cnt;

//----- (00007FF7E59218B0) ----------------------------------------------------
__int64 __fastcall check_4th_part(context *ctx)
{
  context *v2; // rbp
  context *v3; // rbx
  int arg_idx; // edx
  char v5; // al
  int byte_selector; // edi
  int i; // ecx
  rsize_t v9; // rbx
  char *segment_between_slashes; // rax MAPDST
  _no_idea *additional_data; // rcx
  unsigned int first_value_in_block; // r12d
  char v13; // al
  context *v14; // rbp
  context *v15; // rbx
  int v16; // ecx
  rsize_t v17; // rbx
  char *v18; // rax MAPDST
  const CHAR *v20; // r14
  int v21; // eax
  int cchWideChar; // ebp
  WCHAR *lpWideCharStr; // rax
  WCHAR *v24; // rbx
  void *fd; // rbp
  unsigned int const1; // r8d
  char *iter; // rdx
  unsigned int v28; // eax
  bool v29; // zf
  uint16_t *v30; // rax
  signed __int64 v31; // rbx
  int v32; // ecx
  int v33; // edx
  __m128i v34; // xmm2
  char *v35; // rax
  __m128i v36; // xmm2
  __int64 v37; // rcx
  __m128i v38; // xmm2
  __m128i v39; // xmm0
  char *v40; // rax
  __int64 v41; // rcx
  HANDLE CurrentProcess; // rax
  void *rw_mem; // rax
  wchar_t abs_path[264]; // [rsp+40h] [rbp-2AAC8h] BYREF
  char data[952]; // [rsp+250h] [rbp-2A8B8h] BYREF
  char v47; // [rsp+2AAA0h] [rbp-68h] BYREF
  int v48; // [rsp+2AB10h] [rbp+8h] BYREF
  LPCCH lpMultiByteStr; // [rsp+2AB18h] [rbp+10h] BYREF

  v2 = ctx;
  v3 = ctx;
  ctx->additional_data->arg_idx = 4;
  arg_idx = ctx->additional_data->arg_idx;
  if ( arg_idx == 1 )
  {
    if ( ctx->argv[0] == 47 )
    {
      do
        v3 = (context *)((char *)v3 + 1);
      while ( v3->argv[0] == 47 );
    }
    v2 = v3;
  }
  v5 = v3->argv[0];
  byte_selector = 0;
  for ( i = 0; v5; v3 = (context *)((char *)v3 + 1) )
  {
    if ( v5 == 47 )
    {
      if ( ++i == arg_idx )
        break;
      for ( ; v3->argv[1] == 47; v3 = (context *)((char *)v3 + 1) )
        ;
      v2 = (context *)&v3->argv[1];
    }
    v5 = v3->argv[1];
  }
  if ( i >= arg_idx )
  {
    v9 = (char *)v3 - (char *)v2;
    segment_between_slashes = (char *)j__malloc_base(v9 + 1);
    if ( segment_between_slashes )
    {
      strncpy_s(segment_between_slashes, v9 + 1, v2->argv, v9);
      segment_between_slashes[v9] = 0;
    }
    else
    {
      segment_between_slashes = 0i64;
    }
  }
  else
  {
    segment_between_slashes = 0i64;
  }
  additional_data = ctx->additional_data;
  lpMultiByteStr = segment_between_slashes;
  first_value_in_block = *segment_between_slashes;
  if ( additional_data->f4[7] != segment_between_slashes[3]
    || additional_data->f4[5] != segment_between_slashes[2]
    || additional_data->f5[0] != segment_between_slashes[5]
    || additional_data->f4[6] != segment_between_slashes[1]
    || additional_data->f4[4] != segment_between_slashes[4] )
  {
    ((void (__fastcall *)(_QWORD))ctx->ExitProcess)((unsigned int)additional_data->arg_idx);
    segment_between_slashes = (char *)lpMultiByteStr;
  }
  strcpy_s(&ctx->data[44], 0x20ui64, segment_between_slashes);
  v13 = ctx->argv[0];
  v14 = ctx;
  v15 = ctx;
  v16 = 0;
  if ( !ctx->argv[0] )
    goto LABEL_33;
  do
  {
    if ( v13 == 47 )
    {
      if ( ++v16 == 2 )
        goto LABEL_31;
      for ( ; v15->argv[1] == 47; v15 = (context *)((char *)v15 + 1) )
        ;
      v14 = (context *)&v15->argv[1];
    }
    v13 = v15->argv[1];
    v15 = (context *)((char *)v15 + 1);
  }
  while ( v13 );
  if ( v16 < 2 )
    goto LABEL_33;
LABEL_31:
  v17 = (char *)v15 - (char *)v14;
  v18 = (char *)j__malloc_base(v17 + 1);
  if ( v18 )
  {
    strncpy_s(v18, v17 + 1, v14->argv, v17);
    v18[v17] = 0;
  }
  else
  {
LABEL_33:
    v18 = 0i64;
  }
  lpMultiByteStr = v18;
  strcpy_s((char *)&ctx->crc_sum + 4, 0x20ui64, v18);
  strtol(lpMultiByteStr, (char **)&lpMultiByteStr, 10);
  v20 = lpMultiByteStr;
  if ( !lpMultiByteStr )
    goto LABEL_39;
  v21 = MultiByteToWideChar(0xFDE9u, 0, lpMultiByteStr, -1, 0i64, 0);
  cchWideChar = v21;
  if ( !v21 )
    goto LABEL_39;
  lpWideCharStr = (WCHAR *)j__malloc_base(2i64 * v21);
  v24 = lpWideCharStr;
  if ( !lpWideCharStr )
    goto LABEL_39;
  if ( !MultiByteToWideChar(0xFDE9u, 0, v20, -1, lpWideCharStr, cchWideChar) )
  {
    free(v24);
LABEL_39:
    v24 = 0i64;
  }
  ((void (__fastcall *)(_QWORD, wchar_t *, __int64))ctx->GetModuleFileNameW)(0i64, abs_path, 260i64);
  *wcsrchr(abs_path, 0x5Cu) = 0;
  fd = (void *)((__int64 (__fastcall *)(char *, __int64, __int64))ctx->CreateFileW)(ctx->fname, 0x80000000i64, 1i64);
  init_sth((context *)data, 0, 0x2A888ui64);
  if ( !((unsigned int (__fastcall *)(void *, char *, __int64, int *, _QWORD))ctx->ReadFile)(
          fd,
          data,
          0x2A888i64,
          &v48,
          0i64)
    || v48 != 0x2A888 )
  {
    ((void (__fastcall *)(_QWORD))ctx->ExitProcess)((unsigned int)ctx->additional_data->arg_idx);
  }
  if ( *(_DWORD *)data != 0x11333377 )
    ((void (__fastcall *)(_QWORD))ctx->ExitProcess)((unsigned int)ctx->additional_data->arg_idx);
  const1 = *(_DWORD *)&data[4];
  for ( iter = &data[8]; ; ++iter )
  {
    v28 = const1 >> (8 * (byte_selector % 4));
    v29 = (unsigned __int8)v28 == (unsigned __int8)*iter;
    *iter ^= v28;
    if ( v29 && !*(iter - 1) )
      break;
    ++byte_selector;
  }
  v30 = (uint16_t *)&data[8];
  v31 = (char *)v24 - &data[8];
  do
  {
    v32 = *(uint16_t *)((char *)v30 + v31);
    v33 = *v30 - v32;
    if ( v33 )
      break;
    ++v30;
  }
  while ( v32 );
  if ( v33 )
    ((void (__fastcall *)(_QWORD))ctx->ExitProcess)((unsigned int)ctx->additional_data->arg_idx);
  if ( ctx->GetTickCount() <= *(_DWORD *)&data[0x34] + 8000 )
    ((void (__fastcall *)(_QWORD))ctx->ExitProcess)((unsigned int)ctx->additional_data->arg_idx);
  v34 = _mm_cvtsi32_si128(first_value_in_block);
  v35 = &data[96];
  v36 = _mm_unpacklo_epi8(v34, v34);
  v37 = 2720i64;
  v38 = _mm_shuffle_epi32(_mm_unpacklo_epi16(v36, v36), 0);
  do
  {
    v39 = _mm_loadu_si128((const __m128i *)v35 - 1);
    v35 += 64;
    *((__m128i *)v35 - 5) = _mm_sub_epi8(v39, v38);
    *((__m128i *)v35 - 4) = _mm_sub_epi8(_mm_loadu_si128((const __m128i *)v35 - 4), v38);
    *((__m128i *)v35 - 3) = _mm_sub_epi8(_mm_loadu_si128((const __m128i *)v35 - 3), v38);
    *((__m128i *)v35 - 2) = _mm_sub_epi8(_mm_loadu_si128((const __m128i *)v35 - 2), v38);
    --v37;
  }
  while ( v37 );
  v40 = &v47;
  v41 = 55i64;
  do
  {
    *v40++ -= first_value_in_block;
    --v41;
  }
  while ( v41 );
  LODWORD(ctx->crc_sum) = *(_DWORD *)&data[56];
  ctx->len_of_sth = 0x2A837i64;
  CurrentProcess = GetCurrentProcess();
  rw_mem = VirtualAllocEx(CurrentProcess, 0i64, 0x2A837ui64, 0x3000u, 4u);
  ctx->rw_mem = (QWORD)rw_mem;
  memmove(rw_mem, &data[0x50], 0x2A837ui64);
  CloseHandle(fd);
  return check_5th_part(ctx);
}
// 7FF7E59218B0: using guessed type context data;

//----- (00007FF7E5921DA0) ----------------------------------------------------
_OWORD *prepare_shellcode1()
{
  _OWORD *v0; // rbx
  __m256i v2; // [rsp+20h] [rbp-29h]
  __int128 v3; // [rsp+40h] [rbp-9h]
  _BYTE v4[48]; // [rsp+50h] [rbp+7h]
  _BYTE v5[18]; // [rsp+80h] [rbp+37h]
  DWORD flOldProtect; // [rsp+B0h] [rbp+67h] BYREF

  *(__int16 *)((char *)&v2.m256i_i16[13] + 1) = -29879;
  *(_DWORD *)&v4[1] = -1958144140;
  *(_DWORD *)&v4[17] = 1237516104;
  *(_DWORD *)&v5[8] = 994162805;
  v2.m256i_i8[29] = -55;
  *(_WORD *)&v4[24] = -3467;
  v2.m256i_i16[6] = 4213;
  v5[17] = -61;
  *(__int16 *)((char *)&v2.m256i_i16[4] + 1) = -1405;
  v2.m256i_i8[11] = 1;
  *(_QWORD *)&v4[9] = 0x28811048AD18B4Di64;
  LODWORD(v3) = 977355243;
  BYTE4(v3) = -61;
  HIDWORD(v3) = 726411381;
  v4[0] = -55;
  *(_WORD *)&v4[6] = 11081;
  v4[8] = -56;
  *(_QWORD *)&v4[40] = 0x1498D49F7740159i64;
  v2.m256i_i16[3] = -19647;
  v2.m256i_i8[8] = 47;
  *(_WORD *)&v4[21] = -5501;
  v4[23] = 1;
  *(__int32 *)((char *)&v2.m256i_i32[5] + 2) = 1947809861;
  *(_DWORD *)&v5[13] = -1070350467;
  v2.m256i_i8[26] = -8;
  *(_DWORD *)((char *)&v3 + 7) = 994165503;
  *(__int32 *)((char *)&v2.m256i_i32[3] + 2) = 1964587076;
  *(_TBYTE *)&v4[26] = 5.6533954693125116868e752;
  *(_DWORD *)&v5[3] = -2080273855;
  v4[5] = -48;
  *(__int16 *)((char *)&v2.m256i_i16[1] + 1) = -29876;
  v2.m256i_i8[5] = -55;
  *(_DWORD *)&v4[36] = 944095743;
  v2.m256i_i16[15] = -11725;
  v5[12] = -46;
  v2.m256i_i16[0] = -29884;
  v2.m256i_i8[2] = -46;
  *(__int16 *)((char *)&v2.m256i_i16[9] + 1) = -183;
  v2.m256i_i8[21] = -63;
  v2.m256i_i8[18] = 8;
  *(_WORD *)v5 = -183;
  v5[2] = -63;
  BYTE11(v3) = -46;
  *(_WORD *)((char *)&v3 + 5) = 14709;
  v5[7] = -64;
  v0 = VirtualAlloc(0i64, 0x72ui64, 0x3000u, 4u);
  *(__m256i *)v0 = v2;
  v0[2] = v3;
  v0[3] = *(_OWORD *)v4;
  v0[4] = *(_OWORD *)&v4[16];
  v0[5] = *(_OWORD *)&v4[32];
  v0[6] = *(_OWORD *)v5;
  *((_WORD *)v0 + 56) = *(_WORD *)&v5[16];
  flOldProtect = 0;
  VirtualProtect(v0, 0x72ui64, 0x40u, &flOldProtect);
  return v0;
}

//----- (00007FF7E5921F80) ----------------------------------------------------
_OWORD *__fastcall prepare_shellcode2(char *arg)
{
  _OWORD *result; // rax
  char v2[160]; // [rsp+20h] [rbp-59h]

  v2[24] = arg[1];
  v2[25] = arg[11];
  v2[41] = arg[4];
  v2[108] = arg[2];
  v2[138] = arg[3];
  v2[146] = *arg;
  *(_QWORD *)v2 = 0x7C894808245C8948i64;
  *(_QWORD *)&v2[8] = 0x4C10245489481824i64;
  *(_QWORD *)&v2[16] = 0xB86374C98548C18Bui64;
  *(_DWORD *)&v2[26] = 962985984;
  *(_DWORD *)&v2[30] = 1213822209;
  *(_DWORD *)&v2[34] = -2126757533;
  *(_WORD *)&v2[38] = 2108;
  v2[40] = 80;
  *(_DWORD *)&v2[42] = 1282736128;
  *(_DWORD *)&v2[46] = 143428420;
  *(_DWORD *)&v2[50] = 136;
  *(_DWORD *)&v2[54] = 1170801484;
  *(_DWORD *)&v2[58] = 1277188491;
  *(_DWORD *)&v2[62] = -919348989;
  *(_DWORD *)&v2[66] = 407451969;
  *(_DWORD *)&v2[70] = -1958661514;
  *(_DWORD *)&v2[74] = -1958180092;
  *(_DWORD *)&v2[78] = 1225794652;
  *(_DWORD *)&v2[82] = 726188035;
  *(_DWORD *)&v2[86] = 268012504;
  *(_DWORD *)&v2[90] = 256118966;
  *(_DWORD *)&v2[94] = 1092097206;
  *(_DWORD *)&v2[98] = 141939243;
  *(_DWORD *)&v2[102] = 1170276168;
  *(_WORD *)&v2[106] = -11643;
  *(_DWORD *)&v2[109] = 1959953899;
  *(_DWORD *)&v2[113] = 1103232789;
  *(_DWORD *)&v2[117] = 1914194235;
  *(_DWORD *)&v2[121] = 1220555726;
  *(_DWORD *)&v2[125] = 136600715;
  *(_DWORD *)&v2[129] = 612141896;
  *(_DWORD *)&v2[133] = -1958624488;
  v2[137] = 73;
  *(_DWORD *)&v2[139] = 264766281;
  *(_WORD *)&v2[143] = 5303;
  v2[145] = 121;
  *(_DWORD *)&v2[147] = 1226590603;
  *(_DWORD *)&v2[151] = 76269571;
  *(_DWORD *)&v2[155] = 0xC0034991;
  v2[159] = 0xEB;
  result = VirtualAlloc(0i64, 0xA1ui64, 0x3000u, 0x40u);
  *result = *(_OWORD *)v2;
  result[1] = *(_OWORD *)&v2[16];
  result[2] = *(_OWORD *)&v2[32];
  result[3] = *(_OWORD *)&v2[48];
  result[4] = *(_OWORD *)&v2[64];
  result[5] = *(_OWORD *)&v2[80];
  result[6] = *(_OWORD *)&v2[96];
  result[7] = *(_OWORD *)&v2[112];
  result[8] = *(_OWORD *)&v2[128];
  result[9] = *(_OWORD *)&v2[144];
  *((_BYTE *)result + 160) = 0xDB;
  return result;
}

//----- (00007FF7E5922170) ----------------------------------------------------
__int64 __fastcall check_5th_part(context *ctx)
{
  void (__fastcall *get_arg)(context *, __int64, char *); // rax
  __int64 (__fastcall *shellcode2)(QWORD, const char *, __int64); // rsi
  _OWORD *shellcode3; // rax
  __int64 v5; // r8
  QWORD kernel32_base; // rax
  __int64 v7; // r8
  void (__fastcall *beep)(__int64, __int64); // rax
  __int64 v9; // r8
  _BYTE v11[100]; // [rsp+20h] [rbp-89h]
  char fifth_arg[100]; // [rsp+90h] [rbp-19h] BYREF

  ctx->additional_data->arg_idx = 5;
  get_arg = (void (__fastcall *)(context *, __int64, char *))prepare_shellcode1();
  memset(fifth_arg, 0, sizeof(fifth_arg));
  get_arg(ctx, 5i64, fifth_arg);
  shellcode2 = (__int64 (__fastcall *)(QWORD, const char *, __int64))prepare_shellcode2(fifth_arg);
  v11[54] = fifth_arg[9];
  v11[99] = fifth_arg[6];
  v11[24] = fifth_arg[5];
  v11[0] = fifth_arg[12];
  v11[80] = fifth_arg[7];
  *(_DWORD *)&v11[25] = 276333414;
  v11[29] = fifth_arg[8];
  *(_DWORD *)&v11[37] = -2090457227;
  *(_DWORD *)&v11[86] = 813335368;
  *(_WORD *)&v11[90] = 29952;
  *(_WORD *)&v11[41] = 3192;
  v11[43] = 51;
  *(_DWORD *)&v11[69] = 1172865894;
  *(_DWORD *)&v11[13] = 542214984;
  *(_WORD *)&v11[93] = -16333;
  *(_WORD *)&v11[52] = 26119;
  *(_WORD *)&v11[55] = 2168;
  v11[57] = 108;
  *(_DWORD *)&v11[17] = 283804488;
  v11[92] = -72;
  *(_WORD *)&v11[96] = -29880;
  v11[98] = 66;
  *(_DWORD *)&v11[82] = 283804488;
  *(_DWORD *)&v11[46] = 175670118;
  *(_WORD *)&v11[50] = 29772;
  *(_DWORD *)&v11[30] = -2090455435;
  *(_WORD *)&v11[21] = -29880;
  v11[23] = 66;
  *(_DWORD *)&v11[73] = 1958839654;
  *(_DWORD *)&v11[1] = 621054792;
  *(_QWORD *)&v11[5] = 0x18488B4800000060i64;
  *(_DWORD *)&v11[64] = 16768953;
  v11[68] = 0;
  *(_WORD *)&v11[78] = -29880;
  v11[81] = 16;
  *(_WORD *)&v11[34] = 3704;
  v11[36] = 50;
  *(_DWORD *)&v11[58] = -1223749003;
  v11[77] = 18;
  *(_WORD *)&v11[44] = 8309;
  v11[95] = -61;
  *(_WORD *)&v11[62] = 2112;
  if ( fifth_arg[0] != fifth_arg[10] )
    ((void (__fastcall *)(_QWORD))ctx->ExitProcess)((unsigned int)ctx->additional_data->arg_idx);
  shellcode3 = VirtualAlloc(0i64, 0x65ui64, 0x3000u, 0x40u);
  *shellcode3 = *(_OWORD *)v11;
  shellcode3[1] = *(_OWORD *)&v11[16];
  shellcode3[2] = *(_OWORD *)&v11[32];
  shellcode3[3] = *(_OWORD *)&v11[48];
  shellcode3[4] = *(_OWORD *)&v11[64];
  shellcode3[5] = *(_OWORD *)&v11[80];
  *((_DWORD *)shellcode3 + 24) = *(_DWORD *)&v11[96];
  *((_BYTE *)shellcode3 + 100) = -61;
  kernel32_base = ((__int64 (__fastcall *)(_QWORD, _OWORD *, __int64))shellcode3)(
                    *(unsigned int *)&v11[96],
                    shellcode3,
                    v5);
  if ( kernel32_base )
  {
    ctx->kernel32_base = kernel32_base;
    beep = (void (__fastcall *)(__int64, __int64))shellcode2(kernel32_base, "Beep", v7);
    if ( beep )
      ((void (__fastcall *)(__int64, __int64, __int64))beep)(750i64, 300i64, v9);
    ctx->find_function_address = (QWORD)shellcode2;
  }
  else
  {
    ((void (__fastcall *)(_QWORD))ctx->ExitProcess)((unsigned int)ctx->additional_data->arg_idx);
  }
  strcpy_s(&ctx->data[0x4C], 0x20ui64, fifth_arg);
  return check_6th_part(ctx);
}
// 7FF7E5922354: variable 'v5' is possibly undefined
// 7FF7E592236C: variable 'v7' is possibly undefined
// 7FF7E592237D: variable 'v9' is possibly undefined
// 7FF6A5A3FFFE: using guessed type __int64 (__fastcall *)(_QWORD, _QWORD, _QWORD);

//----- (00007FF7E59223D0) ----------------------------------------------------
__int64 __fastcall sub_7FF7E59223D0(__int64 key, __int64 a2, __int64 a3, _BYTE *a4, __int64 a5)
{
  int v5; // r11d
  char *v6; // rdx
  int v7; // r10d
  int i; // eax
  int v12; // r8d
  char *v13; // r9
  int v14; // edi
  char *v15; // rcx
  int v16; // r8d
  char *v17; // r9
  int v18; // edi
  char *v19; // rcx
  __int64 v20; // rsi
  int v21; // edx
  int v22; // r8d
  _BYTE *v23; // rdi
  __int64 v24; // rbp
  __int64 v25; // r14
  char *v26; // r9
  int v27; // r10d
  int v28; // edx
  char *v29; // r9
  int v30; // r8d
  char v32[256]; // [rsp+0h] [rbp-108h] BYREF

  v5 = 0;
  v6 = v32;
  v7 = 0;
  for ( i = 0; i < 256; ++i )
    *v6++ = i;
  v12 = 0;
  v13 = v32;
  do
  {
    v14 = (unsigned __int8)*v13;
    v7 = (v14 + *(char *)(v12 % 0xFu + key) + v7) % 256;
    v15 = &v32[v7];
    ++v12;
    *v13++ = *v15;
    *v15 = v14;
  }
  while ( v12 < 256 );
  v16 = 0;
  v17 = v32;
  do
  {
    v18 = (unsigned __int8)*v17;
    v7 = (v18 + *(char *)(v16 % 0xFu + key) + v7) % 256;
    v19 = &v32[v7];
    ++v16;
    *v17++ = *v19;
    *v19 = v18;
  }
  while ( v16 < 256 );
  v20 = a5;
  v21 = 0;
  v22 = 0;
  if ( !a5 )
    return 0i64;
  v23 = a4;
  v24 = a5;
  v25 = a3 - (_QWORD)a4;
  do
  {
    v21 = (v21 + 1) % 256;
    v26 = &v32[v21];
    v27 = (unsigned __int8)*v26;
    v22 = (v27 + v22) % 256;
    *v26 = v32[v22];
    v32[v22] = v27;
    *v23 = v23[v25] ^ v32[(unsigned __int8)(v27 + *v26)];
    ++v23;
    --v24;
  }
  while ( v24 );
  v28 = 0;
  do
  {
    v5 = (v5 + 1) % 256;
    v29 = &v32[v5];
    v30 = (unsigned __int8)*v29;
    v28 = (v30 + v28) % 256;
    *v29 = v32[v28];
    v32[v28] = v30;
    *a4++ ^= v32[(unsigned __int8)(*v29 + v30)];
    --v20;
  }
  while ( v20 );
  return 0i64;
}
// 7FF7E59223D0: using guessed type char var_108[256];

//----- (00007FF7E5922620) ----------------------------------------------------
__int64 __fastcall sub_7FF7E5922620(char *a1, __int64 a2)
{
  unsigned int i; // eax
  char v4; // r9

  for ( i = -1; a2; --a2 )
  {
    v4 = *a1++;
    i = crc_table[(unsigned __int8)(i ^ v4)] ^ (i >> 8);
  }
  return ~i;
}
// 7FF7E593A8C0: using guessed type _DWORD dword_7FF7E593A8C0[256];

//----- (00007FF7E5922670) ----------------------------------------------------
__int64 __fastcall check_7th_part(context *ctx)
{
  __int64 v1; // rsi
  char *arg; // rbx
  __int64 v4; // rdx
  _BYTE *rw_mem; // r8
  QWORD len_of_sth; // r8
  unsigned int v7; // edx
  char *i; // r9
  char v9; // cl
  __int64 v10; // rdx
  __int128 *v11; // rbx
  __int128 *v12; // rax
  __int128 v13; // xmm0
  char key[16]; // [rsp+30h] [rbp-10h] BYREF
  int v16; // [rsp+60h] [rbp+20h]
  __int128 *rwx; // [rsp+60h] [rbp+20h]
  __int16 v18; // [rsp+64h] [rbp+24h]

  v1 = 7i64;
  ctx->additional_data->arg_idx = 7;
  arg = (char *)((__int64 (__fastcall *)(context *, _QWORD))ctx->get_arg)(
                  ctx,
                  (unsigned int)ctx->additional_data->arg_idx);
  v4 = BYTE3(ctx->sth6);
  BYTE1(v16) = ctx->argv[7];
  HIBYTE(v16) = ctx->argv[10];
  LOBYTE(v16) = BYTE3(ctx->sth6);
  BYTE2(v16) = 53;
  if ( v16 != *(_DWORD *)arg
    || (HIBYTE(v18) = BYTE1(ctx->sth6), LOBYTE(v18) = ctx->argv[9], v18 != *((_WORD *)arg + 2))
    || ctx->argv[11] != arg[6] )
  {
    ((void (__fastcall *)(_QWORD))ctx->ExitProcess)((unsigned int)ctx->additional_data->arg_idx);
  }
  rw_mem = (_BYTE *)ctx->rw_mem;
  key[0] = ctx->data[140];
  key[1] = ctx->data[142];
  key[2] = ctx->data[145] - 1;
  key[3] = ctx->data[147];
  key[4] = ctx->data[148];
  key[5] = ctx->data[150];
  key[6] = ctx->data[154];
  key[7] = ctx->data[157];
  key[8] = ctx->data[152];
  key[9] = ctx->data[153];
  key[10] = ctx->data[151];
  key[11] = ctx->data[155];
  key[12] = ctx->data[161];
  key[13] = ctx->data[163];
  key[14] = ctx->data[159];
  sub_7FF7E59223D0((__int64)key, v4, (__int64)rw_mem, rw_mem, ctx->len_of_sth);
  len_of_sth = ctx->len_of_sth;
  v7 = -1;
  for ( i = (char *)ctx->rw_mem; len_of_sth; --len_of_sth )
  {
    v9 = *i++;
    v7 = crc_table[(unsigned __int8)(v7 ^ v9)] ^ (v7 >> 8);
  }
  v10 = ~v7;
  if ( LODWORD(ctx->crc_sum) != (_DWORD)v10 )
    ((void (__fastcall *)(_QWORD, __int64, QWORD, char *))ctx->ExitProcess)(
      (unsigned int)ctx->additional_data->arg_idx,
      v10,
      len_of_sth,
      i);
  ctx->crc32 = (QWORD)crc32;
  ((void (__fastcall *)(__int64))ctx->crypt_sth)((__int64)arg);
  v11 = (__int128 *)&unk_7FF7E5969420;
  ((void (__fastcall *)(void *, __int64))ctx->CryptSetKeyParam_)(&unk_7FF7E5969420, 960i64);
  rwx = (__int128 *)((__int64 (__fastcall *)(_QWORD, __int64, __int64, __int64))ctx->VirtualAlloc)(
                      0i64,
                      960i64,
                      0x3000i64,
                      0x40i64);
  if ( !rwx )
    ((void (__fastcall *)(_QWORD))ctx->ExitProcess)((unsigned int)ctx->additional_data->arg_idx);
  v12 = rwx;
  do
  {
    v12 += 8;
    v13 = *v11;
    v11 += 8;
    *(v12 - 8) = v13;
    *(v12 - 7) = *(v11 - 7);
    *(v12 - 6) = *(v11 - 6);
    *(v12 - 5) = *(v11 - 5);
    *(v12 - 4) = *(v11 - 4);
    *(v12 - 3) = *(v11 - 3);
    *(v12 - 2) = *(v11 - 2);
    *(v12 - 1) = *(v11 - 1);
    --v1;
  }
  while ( v1 );
  *v12 = *v11;
  v12[1] = v11[1];
  v12[2] = v11[2];
  v12[3] = v11[3];
  return ((__int64 (__fastcall *)(context *))rwx)(ctx);
}
// 7FF7E59227B6: variable 'v4' is possibly undefined
// 7FF7E593A8C0: using guessed type _DWORD crc_table[256];

//----- (00007FF7E5922910) ----------------------------------------------------
__int64 __fastcall check_6th_part(context *ctx)
{
  char *arg; // r12
  __int64 provided_length; // rbx
  __int64 part_len; // rcx MAPDST
  char *f6; // r14
  __int64 idx; // r8
  char *iter; // r9
  char *v9; // rax
  __int64 f6_iter; // rcx
  char newc; // dl
  char v12; // dl
  unsigned __int64 v13; // rcx
  char v14; // al
  __int64 v15; // xmm1_8
  char v16; // al
  __int64 v17; // rdi
  QWORD kernel32_base; // rcx
  int (__stdcall *WriteConsoleA)(const char *, char **, int); // rax MAPDST
  char *v21; // r8
  __int64 v22; // r9
  char v23; // dl
  __int64 v24; // rax
  char v26[32]; // [rsp+30h] [rbp-D0h] BYREF
  char v27[16]; // [rsp+50h] [rbp-B0h] BYREF
  char expected[32]; // [rsp+60h] [rbp-A0h] BYREF
  char provided[32]; // [rsp+80h] [rbp-80h] BYREF

  arg = get_arg(ctx, 6);
  strcpy_s(&ctx->data[0x6C], 0x20ui64, arg);
  provided_length = -1i64;
  part_len = -1i64;
  f6 = ctx->additional_data->f6;
  do
    ++part_len;
  while ( arg[part_len] );
  part_len = (int)part_len;
  if ( (int)part_len > 0 )
  {
    idx = 0i64;
    do
    {
      iter = &provided[idx];
      v9 = f6 + 1;
      f6_iter = 0i64;
      newc = provided[idx + arg - provided];
      while ( *v9 != newc )
      {
        ++f6_iter;
        v9 += 2;
        if ( f6_iter >= 0x1A )
          goto LABEL_10;
      }
      newc = f6[2 * f6_iter];
LABEL_10:
      ++idx;
      *iter = newc;
    }
    while ( idx < part_len );
  }
  provided[part_len] = 0;
  v12 = 0;
  qmemcpy(v26, "R\aB", 3);
  v13 = 0i64;
  v26[3] = 1;
  qmemcpy(&v26[4], "J\x1D\\\x19K", 5);
  v26[9] = 31;
  v26[10] = 76;
  v26[11] = 5;
  v26[12] = 75;
  v26[13] = 12;
  v26[14] = 73;
  v26[15] = 7;
  v26[16] = 78;
  v26[17] = 11;
  v26[18] = 94;
  v26[19] = 12;
  v26[20] = 91;
  v26[21] = 30;
  v26[22] = 77;
  v26[23] = 8;
  v26[24] = 70;
  do
  {
    v14 = v12 ^ v26[v13];
    v12 = v26[v13];
    expected[v13++] = v14;
  }
  while ( v13 < 0x19 );
  v15 = *(_QWORD *)&provided[16];
  v16 = provided[24];
  *(_OWORD *)&ctx->data[140] = *(_OWORD *)provided;
  *(_QWORD *)&ctx->data[156] = v15;
  ctx->data[164] = v16;
  if ( !memcmp(provided, expected, 0x19ui64) )
  {
    v17 = ((__int64 (__fastcall *)(__int64))ctx->GetStdHandle)(0xFFFFFFF5i64);
    if ( v17 == -1 )
      ((void (__fastcall *)(_QWORD))ctx->ExitProcess)((unsigned int)ctx->additional_data->arg_idx);
    kernel32_base = ctx->kernel32_base;
    strcpy(v27, "WriteConsoleA");
    WriteConsoleA = (int (__stdcall *)(const char *, char **, int))((__int64 (__fastcall *)(QWORD, char *))ctx->find_function_address)(
                                                                     kernel32_base,
                                                                     v27);
    *(_WORD *)&provided[25] = 10;
    if ( !((unsigned int (__fastcall *)(__int64, char *, __int64))WriteConsoleA)(v17, provided, 26i64) )
      ((void (__fastcall *)(_QWORD))ctx->ExitProcess)((unsigned int)ctx->additional_data->arg_idx);
    ctx->WriteConsoleA = WriteConsoleA;
  }
  do
    ++provided_length;
  while ( provided[provided_length] );
  if ( (int)provided_length > 0i64 )
  {
    v21 = arg;
    v22 = (int)provided_length;
    do
    {
      v23 = v21[provided - arg];
      v24 = 0i64;
      while ( f6[2 * v24] != v23 )
      {
        if ( ++v24 >= 26 )
          goto LABEL_27;
      }
      v23 = f6[2 * v24 + 1];
LABEL_27:
      *v21++ = v23;
      --v22;
    }
    while ( v22 );
  }
  arg[(int)provided_length] = 0;
  return check_7th_part(ctx);
}
// 7FF6A5A3FFFE: using guessed type __int64 (__fastcall *)(_QWORD, _QWORD, _QWORD);
// 7FF7E5922910: using guessed type char expected[32];

//----- (00007FF7E5922C00) ----------------------------------------------------
__int64 __fastcall crypt_sth(BYTE *pbData)
{
  __int64 v2; // r8
  unsigned int v3; // ebx
  DWORD LastError; // eax
  int pbDataa; // [rsp+48h] [rbp+10h] BYREF
  HCRYPTHASH phHash; // [rsp+50h] [rbp+18h] BYREF

  phHash = 0i64;
  if ( !CryptAcquireContextW(&hProv, 0i64, 0i64, 0x18u, 0) && !CryptAcquireContextW(&hProv, 0i64, 0i64, 0x18u, 8u) )
    goto LABEL_12;
  if ( !CryptCreateHash(hProv, 0x800Cu, 0i64, 0, &phHash) )
    goto LABEL_12;
  v2 = -1i64;
  do
    ++v2;
  while ( pbData[v2] );
  if ( !CryptHashData(phHash, pbData, v2, 0)
    || !CryptDeriveKey(hProv, 0x6610u, phHash, 0, &hKey)
    || (pbDataa = 1, (v3 = CryptSetKeyParam(hKey, 4u, (const BYTE *)&pbDataa, 0)) == 0) )
  {
LABEL_12:
    LastError = GetLastError();
    ExitProcess(LastError);
  }
  if ( phHash )
    CryptDestroyHash(phHash);
  return v3;
}

//----- (00007FF7E5922D20) ----------------------------------------------------
BOOL __stdcall CryptSetKeyParam_(HCRYPTKEY hKey, DWORD dwParam, const BYTE *pbData, DWORD dwFlags)
{
  BOOL result; // eax
  BYTE pbDataa[24]; // [rsp+30h] [rbp-18h] BYREF
  DWORD pdwDataLen; // [rsp+60h] [rbp+18h] BYREF

  qmemcpy(pbDataa, "capture_the_flag", 16);
  result = CryptSetKeyParam(::hKey, 1u, pbDataa, 0);
  if ( result )
  {
    pdwDataLen = dwParam;
    return CryptDecrypt(::hKey, 0i64, 1, 0, (BYTE *)hKey, &pdwDataLen);
  }
  return result;
}

//----- (00007FF7E5922DB0) ----------------------------------------------------
__int64 __fastcall open_html(context *ctx, __int64 a2)
{
  HANDLE FileA; // rax
  void *v5; // rbx
  _BYTE *rw_mem; // rdx
  __int64 v7; // r8
  __int64 result; // rax
  QWORD v9; // rdx
  CHAR TempFileName[272]; // [rsp+40h] [rbp-228h] BYREF
  CHAR Buffer[272]; // [rsp+150h] [rbp-118h] BYREF
  DWORD NumberOfBytesWritten; // [rsp+280h] [rbp+18h] BYREF

  if ( !GetTempPathA(0x104u, Buffer) )
    return 0i64;
  if ( !GetTempFileNameA(Buffer, "random", 0, TempFileName) )
    return 0i64;
  strcat_s(TempFileName, 0x104ui64, ".html");
  FileA = CreateFileA(TempFileName, 0x40000000u, 0, 0i64, 2u, 0x80u, 0i64);
  v5 = FileA;
  if ( FileA == (HANDLE)-1i64 )
    return 0i64;
  rw_mem = (_BYTE *)ctx->rw_mem;
  v7 = -1i64;
  do
    ++v7;
  while ( rw_mem[v7] );
  if ( !WriteFile(FileA, rw_mem, v7, &NumberOfBytesWritten, 0i64) )
  {
    CloseHandle(v5);
    return 0i64;
  }
  CloseHandle(v5);
  if ( (int)ShellExecuteA(0i64, "open", TempFileName, 0i64, 0i64, 1) <= 32 )
    return 0i64;
  v9 = ctx->rw_mem;
  result = 1i64;
  *(_WORD *)a2 = *(_WORD *)(v9 + 31);
  *(_BYTE *)(a2 + 2) = *(_BYTE *)(v9 + 33);
  return result;
}

//----- (00007FF7E5922F00) ----------------------------------------------------
char *__fastcall get_arg(context *ctx, int expected_slashes)
{
  char *v2; // rdi
  char *iter; // rbx
  char c; // cl
  int slashes_num; // eax
  rsize_t segment_between_slashes_len; // rbx
  char *v8; // rsi
  char *result; // rax MAPDST

  v2 = (char *)ctx;
  iter = (char *)ctx;
  if ( expected_slashes == 1 )
  {
    if ( ctx->argv[0] == '/' )
    {
      do
        ++iter;
      while ( *iter == '/' );
    }
    v2 = iter;
  }
  c = *iter;
  for ( slashes_num = 0; c; ++iter )
  {
    if ( c == '/' )
    {
      if ( ++slashes_num == expected_slashes )
        break;
      for ( ; iter[1] == '/'; ++iter )
        ;
      v2 = iter + 1;
    }
    c = iter[1];
  }
  if ( slashes_num < expected_slashes )
    return 0i64;
  segment_between_slashes_len = iter - v2;
  result = (char *)j__malloc_base(segment_between_slashes_len + 1);
  v8 = result;
  if ( !result )
    return 0i64;
  strncpy_s(result, segment_between_slashes_len + 1, v2, segment_between_slashes_len);
  result = v8;
  v8[segment_between_slashes_len] = 0;
  return result;
}

//----- (00007FF7E5923474) ----------------------------------------------------
__int64 sub_7FF7E5923474()
{
  uintptr_t v0; // rax
  __int64 result; // rax
  unsigned __int64 v2; // [rsp+20h] [rbp-10h] BYREF
  struct _FILETIME SystemTimeAsFileTime; // [rsp+40h] [rbp+10h] BYREF
  LARGE_INTEGER PerformanceCount; // [rsp+48h] [rbp+18h] BYREF

  v0 = _security_cookie;
  if ( _security_cookie == 0x2B992DDFA232i64 )
  {
    SystemTimeAsFileTime = 0i64;
    GetSystemTimeAsFileTime(&SystemTimeAsFileTime);
    v2 = (unsigned __int64)SystemTimeAsFileTime;
    v2 ^= GetCurrentThreadId();
    v2 ^= GetCurrentProcessId();
    QueryPerformanceCounter(&PerformanceCount);
    v0 = ((unsigned __int64)&v2 ^ v2 ^ PerformanceCount.QuadPart ^ ((unsigned __int64)PerformanceCount.LowPart << 32)) & 0xFFFFFFFFFFFFi64;
    if ( v0 == 0x2B992DDFA232i64 )
      v0 = 0x2B992DDFA233i64;
    _security_cookie = v0;
  }
  result = ~v0;
  qword_7FF7E593E020 = result;
  return result;
}
// 7FF7E593E020: using guessed type __int64 qword_7FF7E593E020;

//----- (00007FF7E5923520) ----------------------------------------------------
__int64 __fastcall UserMathErrorFunction(struct _exception *a1)
{
  return 0i64;
}

//----- (00007FF7E5923534) ----------------------------------------------------
void sub_7FF7E5923534()
{
  InitializeSListHead(&stru_7FF7E59698A0);
}
// 7FF7E59698A0: using guessed type union _SLIST_HEADER stru_7FF7E59698A0;

//----- (00007FF7E5923544) ----------------------------------------------------
char sub_7FF7E5923544()
{
  return 1;
}

//----- (00007FF7E592354C) ----------------------------------------------------
void *sub_7FF7E592354C()
{
  return &unk_7FF7E59698B0;
}

//----- (00007FF7E5923554) ----------------------------------------------------
void *sub_7FF7E5923554()
{
  return &unk_7FF7E59698B8;
}

//----- (00007FF7E5923584) ----------------------------------------------------
void *sub_7FF7E5923584()
{
  return &unk_7FF7E596AA00;
}

//----- (00007FF7E592358C) ----------------------------------------------------
void *sub_7FF7E592358C()
{
  return &unk_7FF7E596A9F8;
}

//----- (00007FF7E5923594) ----------------------------------------------------
void sub_7FF7E5923594()
{
  dword_7FF7E59698C0 = 0;
}
// 7FF7E59698C0: using guessed type int dword_7FF7E59698C0;

//----- (00007FF7E59236F0) ----------------------------------------------------
bool sub_7FF7E59236F0()
{
  HMODULE ModuleHandleW; // rax
  char *v1; // rcx
  bool result; // al

  ModuleHandleW = GetModuleHandleW(0i64);
  result = ModuleHandleW
        && *(_WORD *)ModuleHandleW == 23117
        && (v1 = (char *)ModuleHandleW + *((int *)ModuleHandleW + 15), *(_DWORD *)v1 == 17744)
        && *((_WORD *)v1 + 12) == 523
        && *((_DWORD *)v1 + 33) > 0xEu
        && *((_DWORD *)v1 + 62) != 0;
  return result;
}

//----- (00007FF7E59237B0) ----------------------------------------------------
void sub_7FF7E59237B0()
{
  void (**i)(void); // rbx

  for ( i = qword_7FF7E593B528; i < qword_7FF7E593B528; ++i )
  {
    if ( *i )
      (*i)();
  }
}
// 7FF7E593B528: using guessed type void (*qword_7FF7E593B528[2])(void);

//----- (00007FF7E59237EC) ----------------------------------------------------
void __fastcall sub_7FF7E59237EC()
{
  void (**i)(void); // rbx

  for ( i = &qword_7FF7E593B538; i < &qword_7FF7E593B538; ++i )
  {
    if ( *i )
      (*i)();
  }
}
// 7FF7E593B538: using guessed type void (*qword_7FF7E593B538)(void);

//----- (00007FF7E5923828) ----------------------------------------------------
__int64 sub_7FF7E5923828()
{
  int v5; // r11d
  int v6; // r9d
  int v7; // esi
  int v9; // r10d
  int v14; // edi
  int v15; // eax
  unsigned __int64 v16; // rax
  __int64 v17; // rcx
  int v18; // r8d
  int v23; // eax
  char v25; // [rsp+20h] [rbp+8h]

  _RAX = 0i64;
  __asm { cpuid }
  v5 = 0;
  v6 = _RBX;
  v7 = _RAX;
  _RAX = 1i64;
  v9 = _RCX ^ 0x6C65746E | _RDX ^ 0x49656E69;
  __asm { cpuid }
  v14 = _RCX;
  if ( !(v6 ^ 0x756E6547 | v9)
    && ((qword_7FF7E593E018 = -1i64, v15 = _RAX & 0xFFF3FF0, qword_7FF7E593E010 = 0x8000i64, v15 == 67264)
     || v15 == 132704
     || v15 == 132720
     || (v16 = (unsigned int)(v15 - 198224), (unsigned int)v16 <= 0x20) && (v17 = 0x100010001i64, _bittest64(&v17, v16))) )
  {
    v18 = dword_7FF7E59698C4 | 1;
    dword_7FF7E59698C4 |= 1u;
  }
  else
  {
    v18 = dword_7FF7E59698C4;
  }
  _RAX = 7i64;
  if ( v7 >= 7 )
  {
    __asm { cpuid }
    v5 = _RBX;
    if ( (_RBX & 0x200) != 0 )
      dword_7FF7E59698C4 = v18 | 2;
  }
  dword_7FF7E593E008 = 1;
  dword_7FF7E593E00C = 2;
  if ( (v14 & 0x100000) != 0 )
  {
    dword_7FF7E593E008 = 2;
    dword_7FF7E593E00C = 6;
    if ( (v14 & 0x8000000) != 0 && (v14 & 0x10000000) != 0 )
    {
      __asm { xgetbv }
      v25 = _RAX;
      if ( (_RAX & 6) == 6 )
      {
        v23 = dword_7FF7E593E00C | 8;
        dword_7FF7E593E008 = 3;
        dword_7FF7E593E00C |= 8u;
        if ( (v5 & 0x20) != 0 )
        {
          dword_7FF7E593E008 = 5;
          dword_7FF7E593E00C = v23 | 0x20;
          if ( (v5 & 0xD0030000) == -805109760 && (v25 & 0xE0) == 0xE0 )
          {
            dword_7FF7E593E00C |= 0x40u;
            dword_7FF7E593E008 = 6;
          }
        }
      }
    }
  }
  return 0i64;
}
// 7FF7E593E008: using guessed type int dword_7FF7E593E008;
// 7FF7E593E00C: using guessed type int dword_7FF7E593E00C;
// 7FF7E593E010: using guessed type __int64 qword_7FF7E593E010;
// 7FF7E593E018: using guessed type __int64 qword_7FF7E593E018;
// 7FF7E59698C4: using guessed type int dword_7FF7E59698C4;

//----- (00007FF7E5923B0C) ----------------------------------------------------
__int64 __fastcall sub_7FF7E5923B0C(PEXCEPTION_RECORD ExceptionRecord, PVOID TargetFrame, __int64 a3, __int64 a4)
{
  __int64 v8; // r8
  __int64 v9; // r12
  unsigned int *v10; // rbx
  unsigned __int64 v11; // r14
  unsigned int v12; // edi
  int v13; // eax
  unsigned __int64 v15; // rsi
  __int64 v16; // rcx
  unsigned int i; // r9d
  __int64 v18; // rax
  void (__fastcall *v19)(__int64, PVOID, _QWORD); // r8
  unsigned int v20; // edx
  __int64 v21[2]; // [rsp+30h] [rbp-38h] BYREF

  _except_validate_context_record(a3);
  v9 = *(_QWORD *)(a4 + 8);
  v10 = *(unsigned int **)(a4 + 56);
  v11 = *(_QWORD *)a4 - v9;
  v12 = *(_DWORD *)(a4 + 72);
  if ( (ExceptionRecord->ExceptionFlags & 0x66) != 0 )
  {
    v15 = *(_QWORD *)(a4 + 32) - v9;
    while ( 1 )
    {
      v20 = *v10;
      if ( v12 >= *v10 )
        break;
      v16 = 2i64 * v12;
      if ( v11 >= v10[4 * v12 + 1] && v11 < v10[4 * v12 + 2] )
      {
        if ( (ExceptionRecord->ExceptionFlags & 0x20) != 0 )
        {
          for ( i = 0; i < v20; ++i )
          {
            if ( v15 >= v10[4 * i + 1]
              && v15 < v10[4 * i + 2]
              && v10[4 * i + 4] == v10[4 * v12 + 4]
              && v10[4 * i + 3] == v10[4 * v12 + 3] )
            {
              break;
            }
          }
          if ( i != v20 )
            return 1i64;
        }
        v18 = v10[4 * v12 + 4];
        if ( (_DWORD)v18 )
        {
          if ( v15 == v18 && (ExceptionRecord->ExceptionFlags & 0x20) != 0 )
            return 1i64;
        }
        else
        {
          *(_DWORD *)(a4 + 72) = v12 + 1;
          LOBYTE(v16) = 1;
          v19 = (void (__fastcall *)(__int64, PVOID, _QWORD))(v9 + v10[4 * v12 + 3]);
          v19(v16, TargetFrame, v19);
        }
      }
      ++v12;
    }
  }
  else
  {
    v21[0] = (__int64)ExceptionRecord;
    v21[1] = a3;
    while ( v12 < *v10 )
    {
      if ( v11 >= v10[4 * v12 + 1] && v11 < v10[4 * v12 + 2] && v10[4 * v12 + 4] )
      {
        if ( v10[4 * v12 + 3] == 1 )
          goto LABEL_11;
        v13 = ((__int64 (__fastcall *)(__int64 *, PVOID, __int64))(v9 + v10[4 * v12 + 3]))(v21, TargetFrame, v8);
        if ( v13 < 0 )
          return 0i64;
        if ( v13 > 0 )
        {
LABEL_11:
          if ( ExceptionRecord->ExceptionCode == -529697949 && _DestructExceptionObject )
          {
            if ( (unsigned int)IsNonwritableInCurrentImage(&off_7FF7E59333E0) )
              _DestructExceptionObject(ExceptionRecord, 1i64);
          }
          NLG_Notify(v9 + v10[4 * v12 + 4], TargetFrame, 1i64);
          RtlUnwindEx(
            TargetFrame,
            (PVOID)(v9 + v10[4 * v12 + 4]),
            ExceptionRecord,
            (PVOID)ExceptionRecord->ExceptionCode,
            *(PCONTEXT *)(a4 + 40),
            *(PUNWIND_HISTORY_TABLE *)(a4 + 64));
          _NLG_Return2();
        }
      }
      ++v12;
    }
  }
  return 1i64;
}
// 7FF7E5923BAA: variable 'v8' is possibly undefined
// 7FF6A5A3FFFE: using guessed type __int64 (__fastcall *)(_QWORD, _QWORD, _QWORD);
// 7FF7E5923D70: using guessed type __int64 __fastcall _DestructExceptionObject(_QWORD, _QWORD);
// 7FF7E59242B0: using guessed type __int64 __fastcall NLG_Notify(_QWORD, _QWORD, _QWORD);
// 7FF7E59242E0: using guessed type __int64 _NLG_Return2(void);
// 7FF7E59242E4: using guessed type __int64 __fastcall _except_validate_context_record(_QWORD);
// 7FF7E5931740: using guessed type __int64 __fastcall IsNonwritableInCurrentImage(_QWORD);
// 7FF7E59333E0: using guessed type __int64 (__fastcall *off_7FF7E59333E0)();

//----- (00007FF7E5923EF0) ----------------------------------------------------
void *__cdecl memset_(void *a1, int Val, size_t Size)
{
  void *v3; // r9

  memset(a1, Val, Size);
  return v3;
}
// 7FF7E5923EFB: variable 'v3' is possibly undefined

//----- (00007FF7E5923F10) ----------------------------------------------------
__m128i *__fastcall init_sth(context *ctx, unsigned __int8 param2, unsigned __int64 param3)
{
  __m128i *result; // rax
  __int64 v5; // r11
  __m128i *v6; // rcx
  __m128i v7; // xmm0
  __int64 v9; // r9
  __int64 v14; // r9
  __m128i *v15; // rcx
  unsigned __int64 v16; // r8
  unsigned __int64 v17; // r9

  result = (__m128i *)ctx;
  v5 = 0x101010101010101i64 * param2;
  v6 = (__m128i *)&ctx->argv[param3];
  switch ( param3 )
  {
    case 0ui64:
      return result;
    case 1ui64:
      goto LABEL_5;
    case 2ui64:
      goto LABEL_8;
    case 3ui64:
      goto LABEL_4;
    case 4ui64:
      goto LABEL_12;
    case 5ui64:
      goto LABEL_10;
    case 6ui64:
      goto LABEL_7;
    case 7ui64:
      goto LABEL_3;
    case 8ui64:
      v6[-1].m128i_i64[1] = v5;
      return result;
    case 9ui64:
      *(__int64 *)((char *)v6[-1].m128i_i64 + 7) = v5;
      v6[-1].m128i_i8[15] = param2;
      return result;
    case 0xAui64:
      *(__int64 *)((char *)v6[-1].m128i_i64 + 6) = v5;
      v6[-1].m128i_i16[7] = v5;
      return result;
    case 0xBui64:
      *(__int64 *)((char *)v6[-1].m128i_i64 + 5) = v5;
      *(__int16 *)((char *)&v6[-1].m128i_i16[6] + 1) = v5;
      v6[-1].m128i_i8[15] = param2;
      return result;
    case 0xCui64:
      *(__int64 *)((char *)v6[-1].m128i_i64 + 4) = v5;
LABEL_12:
      v6[-1].m128i_i32[3] = v5;
      return result;
    case 0xDui64:
      *(__int64 *)((char *)v6[-1].m128i_i64 + 3) = v5;
LABEL_10:
      *(__int32 *)((char *)&v6[-1].m128i_i32[2] + 3) = v5;
      v6[-1].m128i_i8[15] = param2;
      return result;
    case 0xEui64:
      *(__int64 *)((char *)v6[-1].m128i_i64 + 2) = v5;
LABEL_7:
      *(__int32 *)((char *)&v6[-1].m128i_i32[2] + 2) = v5;
LABEL_8:
      v6[-1].m128i_i16[7] = v5;
      return result;
    case 0xFui64:
      *(__int64 *)((char *)v6[-1].m128i_i64 + 1) = v5;
LABEL_3:
      *(__int32 *)((char *)&v6[-1].m128i_i32[2] + 1) = v5;
LABEL_4:
      *(__int16 *)((char *)&v6[-1].m128i_i16[6] + 1) = v5;
LABEL_5:
      v6[-1].m128i_i8[15] = param2;
      return result;
    default:
      v7 = _mm_unpacklo_epi64((__m128i)(unsigned __int64)v5, (__m128i)(unsigned __int64)v5);
      if ( param3 <= 0x20 )
      {
        *v6 = v7;
        *(__m128i *)((char *)&v6[-1] + param3) = v7;
        return result;
      }
      if ( (unsigned int)dword_7FF7E593E008 < 3 )
      {
        if ( param3 <= qword_7FF7E593E010 || (dword_7FF7E59698C4 & 2) == 0 )
        {
          v14 = ((unsigned __int8)v6 & 0xF) - 16i64;
          v15 = (__m128i *)((char *)v6 - v14);
          v16 = v14 + param3;
          if ( v16 > 0x80 )
          {
            do
            {
              *v15 = v7;
              v15[1] = v7;
              v15[2] = v7;
              v15[3] = v7;
              v15[4] = v7;
              v15[5] = v7;
              v15[6] = v7;
              v15[7] = v7;
              v15 += 8;
              v16 -= 128i64;
            }
            while ( v16 >= 0x80 );
          }
          v17 = (v16 + 15) & 0xFFFFFFFFFFFFFFF0ui64;
          switch ( v17 >> 4 )
          {
            case 0ui64:
              goto LABEL_60;
            case 1ui64:
              goto LABEL_59;
            case 2ui64:
              goto LABEL_58;
            case 3ui64:
              goto LABEL_57;
            case 4ui64:
              goto LABEL_56;
            case 5ui64:
              goto LABEL_55;
            case 6ui64:
              goto LABEL_54;
            case 7ui64:
              goto LABEL_53;
            case 8ui64:
              *(__m128i *)((char *)&v15[-8] + v17) = v7;
LABEL_53:
              *(__m128i *)((char *)&v15[-7] + v17) = v7;
LABEL_54:
              *(__m128i *)((char *)&v15[-6] + v17) = v7;
LABEL_55:
              *(__m128i *)((char *)&v15[-5] + v17) = v7;
LABEL_56:
              *(__m128i *)((char *)&v15[-4] + v17) = v7;
LABEL_57:
              *(__m128i *)((char *)&v15[-3] + v17) = v7;
LABEL_58:
              *(__m128i *)((char *)&v15[-2] + v17) = v7;
LABEL_59:
              *(__m128i *)((char *)&v15[-1] + v16) = v7;
LABEL_60:
              *result = v7;
              break;
          }
          return result;
        }
        return (__m128i *)memset_(v6, param2, param3);
      }
      if ( param3 > qword_7FF7E593E010 && param3 <= qword_7FF7E593E018 && (dword_7FF7E59698C4 & 2) != 0 )
        return (__m128i *)memset_(v6, param2, param3);
      __asm { vinsertf128 ymm0, ymm0, xmm0, 1 }
      v9 = ((unsigned __int8)v6 & 0x1F) - 32i64;
      _RCX = &v6->m128i_i8[-v9];
      _R8 = v9 + param3;
      if ( _R8 <= 0x100 )
        goto LABEL_26;
      if ( _R8 <= qword_7FF7E593E018 )
      {
        do
        {
          __asm
          {
            vmovdqa ymmword ptr [rcx], ymm0
            vmovdqa ymmword ptr [rcx+20h], ymm0
            vmovdqa ymmword ptr [rcx+40h], ymm0
            vmovdqa ymmword ptr [rcx+60h], ymm0
            vmovdqa ymmword ptr [rcx+80h], ymm0
            vmovdqa ymmword ptr [rcx+0A0h], ymm0
            vmovdqa ymmword ptr [rcx+0C0h], ymm0
            vmovdqa ymmword ptr [rcx+0E0h], ymm0
          }
          _RCX += 256;
          _R8 -= 256i64;
        }
        while ( _R8 >= 0x100 );
LABEL_26:
        _R9 = (_R8 + 31) & 0xFFFFFFFFFFFFFFE0ui64;
        switch ( _R9 >> 5 )
        {
          case 0ui64:
            goto LABEL_35;
          case 1ui64:
            goto LABEL_34;
          case 2ui64:
            goto LABEL_33;
          case 3ui64:
            goto LABEL_32;
          case 4ui64:
            goto LABEL_31;
          case 5ui64:
            goto LABEL_30;
          case 6ui64:
            goto LABEL_29;
          case 7ui64:
            goto LABEL_28;
          case 8ui64:
            __asm { vmovdqu ymmword ptr [rcx+r9-100h], ymm0; jumptable 00007FF7E59240A4 case 8 }
LABEL_28:
            __asm { vmovdqu ymmword ptr [rcx+r9-0E0h], ymm0; jumptable 00007FF7E59240A4 case 7 }
LABEL_29:
            __asm { vmovdqu ymmword ptr [rcx+r9-0C0h], ymm0; jumptable 00007FF7E59240A4 case 6 }
LABEL_30:
            __asm { vmovdqu ymmword ptr [rcx+r9-0A0h], ymm0; jumptable 00007FF7E59240A4 case 5 }
LABEL_31:
            __asm { vmovdqu ymmword ptr [rcx+r9-80h], ymm0; jumptable 00007FF7E59240A4 case 4 }
LABEL_32:
            __asm { vmovdqu ymmword ptr [rcx+r9-60h], ymm0; jumptable 00007FF7E59240A4 case 3 }
LABEL_33:
            __asm { vmovdqu ymmword ptr [rcx+r9-40h], ymm0; jumptable 00007FF7E59240A4 case 2 }
LABEL_34:
            __asm { vmovdqu ymmword ptr [rcx+r8-20h], ymm0; jumptable 00007FF7E59240A4 case 1 }
LABEL_35:
            __asm
            {
              vmovdqu ymmword ptr [rax], ymm0; jumptable 00007FF7E59240A4 case 0
              vzeroupper
            }
            break;
        }
        return result;
      }
      do
      {
        __asm
        {
          vmovntdq ymmword ptr [rcx], ymm0
          vmovntdq ymmword ptr [rcx+20h], ymm0
          vmovntdq ymmword ptr [rcx+40h], ymm0
          vmovntdq ymmword ptr [rcx+60h], ymm0
          vmovntdq ymmword ptr [rcx+80h], ymm0
          vmovntdq ymmword ptr [rcx+0A0h], ymm0
          vmovntdq ymmword ptr [rcx+0C0h], ymm0
          vmovntdq ymmword ptr [rcx+0E0h], ymm0
        }
        _RCX += 256;
        _R8 -= 256i64;
      }
      while ( _R8 >= 0x100 );
      _R9 = (_R8 + 31) & 0xFFFFFFFFFFFFFFE0ui64;
      switch ( _R9 >> 5 )
      {
        case 0ui64:
          goto LABEL_46;
        case 1ui64:
          goto LABEL_45;
        case 2ui64:
          goto LABEL_44;
        case 3ui64:
          goto LABEL_43;
        case 4ui64:
          goto LABEL_42;
        case 5ui64:
          goto LABEL_41;
        case 6ui64:
          goto LABEL_40;
        case 7ui64:
          goto LABEL_39;
        case 8ui64:
          __asm { vmovntdq ymmword ptr [rcx+r9-100h], ymm0; jumptable 00007FF7E5924164 case 8 }
LABEL_39:
          __asm { vmovntdq ymmword ptr [rcx+r9-0E0h], ymm0; jumptable 00007FF7E5924164 case 7 }
LABEL_40:
          __asm { vmovntdq ymmword ptr [rcx+r9-0C0h], ymm0; jumptable 00007FF7E5924164 case 6 }
LABEL_41:
          __asm { vmovntdq ymmword ptr [rcx+r9-0A0h], ymm0; jumptable 00007FF7E5924164 case 5 }
LABEL_42:
          __asm { vmovntdq ymmword ptr [rcx+r9-80h], ymm0; jumptable 00007FF7E5924164 case 4 }
LABEL_43:
          __asm { vmovntdq ymmword ptr [rcx+r9-60h], ymm0; jumptable 00007FF7E5924164 case 3 }
LABEL_44:
          __asm { vmovntdq ymmword ptr [rcx+r9-40h], ymm0; jumptable 00007FF7E5924164 case 2 }
LABEL_45:
          __asm { vmovdqu ymmword ptr [rcx+r8-20h], ymm0; jumptable 00007FF7E5924164 case 1 }
LABEL_46:
          __asm { vmovdqu ymmword ptr [rax], ymm0; jumptable 00007FF7E5924164 case 0 }
          _mm_sfence();
          __asm { vzeroupper }
          break;
      }
      return result;
  }
}
// 7FF7E593E008: using guessed type int dword_7FF7E593E008;
// 7FF7E593E010: using guessed type __int64 qword_7FF7E593E010;
// 7FF7E593E018: using guessed type __int64 qword_7FF7E593E018;
// 7FF7E59698C4: using guessed type int dword_7FF7E59698C4;

//----- (00007FF7E5924838) ----------------------------------------------------
__int64 __fastcall sub_7FF7E5924838(__int64 a1, int a2)
{
  int v2; // edi
  bool i; // zf
  __int64 result; // rax

  v2 = *(_DWORD *)(a1 + 12);
  for ( i = v2 == 0; !i; i = v2 == 0 )
  {
    result = *(_QWORD *)(_vcrt_getptd() + 96) + 20i64 * (unsigned int)--v2 + *(int *)(a1 + 16);
    if ( a2 > *(_DWORD *)(result + 4) && a2 <= *(_DWORD *)(result + 8) )
      return result;
  }
  return 0i64;
}
// 7FF7E592433C: using guessed type __int64 _vcrt_getptd(void);

//----- (00007FF7E592492C) ----------------------------------------------------
_QWORD *__fastcall sub_7FF7E592492C(_QWORD *a1, unsigned __int64 *a2, __int64 a3, _QWORD *a4)
{
  int v4; // esi
  int v9; // ebp
  _DWORD *v10; // rbx
  PRUNTIME_FUNCTION v11; // rax
  __int64 v12; // rcx
  unsigned __int64 v13; // r8
  unsigned int v14; // r9d
  _DWORD *v15; // rdx
  unsigned __int64 ImageBase; // [rsp+50h] [rbp+8h] BYREF

  v4 = *(_DWORD *)(a3 + 12);
  v9 = sub_7FF7E59254F4(a3, a2);
  *a4 = *a1;
  while ( v4 )
  {
    v10 = (_DWORD *)(a2[1] + *(int *)(a3 + 16) + 20i64 * (unsigned int)--v4);
    if ( v9 > v10[1] && v9 <= v10[2] )
    {
      v11 = RtlLookupFunctionEntry(*a2, &ImageBase, 0i64);
      v12 = 0i64;
      v13 = ImageBase + (int)v10[4];
      v14 = v10[3];
      if ( v14 )
      {
        v15 = (_DWORD *)(v13 + 12);
        do
        {
          if ( *v15 == (unsigned __int64)v11->BeginAddress )
            break;
          v12 = (unsigned int)(v12 + 1);
          v15 += 5;
        }
        while ( (unsigned int)v12 < v14 );
      }
      if ( (unsigned int)v12 < v14 )
      {
        *a4 = *(_QWORD *)(*(int *)(v13 + 20 * v12 + 16) + *a1);
        return a4;
      }
    }
  }
  return a4;
}

//----- (00007FF7E5925458) ----------------------------------------------------
__int64 __fastcall sub_7FF7E5925458(_QWORD *a1, unsigned __int64 *a2, __int64 a3)
{
  __int64 result; // rax

  result = *(unsigned int *)(*(int *)(a3 + 28) + *a1);
  if ( (_DWORD)result == -2 )
    return sub_7FF7E59254FC(a3, (__int64)a2, *a2);
  return result;
}

//----- (00007FF7E5925480) ----------------------------------------------------
__int64 __fastcall sub_7FF7E5925480(_QWORD *a1, unsigned __int64 *a2, __int64 a3)
{
  __int64 v4; // rcx
  __int64 v5; // rax
  __int64 v7; // [rsp+40h] [rbp+18h] BYREF

  v4 = *sub_7FF7E592492C(a1, a2, a3, &v7);
  v5 = *(int *)(a3 + 28);
  v7 = v4;
  return *(unsigned int *)(v5 + v4 + 4);
}

//----- (00007FF7E59254B8) ----------------------------------------------------
__int64 __fastcall sub_7FF7E59254B8(_QWORD *a1, unsigned __int64 *a2, __int64 a3, int a4)
{
  __int64 v6; // rcx
  __int64 result; // rax
  __int64 v8; // [rsp+40h] [rbp+18h] BYREF

  v6 = *sub_7FF7E592492C(a1, a2, a3, &v8);
  result = *(int *)(a3 + 28);
  v8 = v6;
  if ( a4 > *(_DWORD *)(result + v6 + 4) )
    *(_DWORD *)(result + v6 + 4) = a4;
  return result;
}

//----- (00007FF7E59254F4) ----------------------------------------------------
__int64 __fastcall sub_7FF7E59254F4(__int64 a1, unsigned __int64 *a2)
{
  return sub_7FF7E59254FC(a1, (__int64)a2, *a2);
}

//----- (00007FF7E59254FC) ----------------------------------------------------
__int64 __fastcall sub_7FF7E59254FC(__int64 a1, __int64 a2, unsigned __int64 a3)
{
  __int64 v4; // r11
  __int64 v5; // r10
  unsigned int v6; // r8d
  __int64 v7; // r9

  if ( !a1 || (v4 = *(int *)(a1 + 24), v5 = *(_QWORD *)(a2 + 8), !(v5 + v4)) )
    abort();
  v6 = *(_DWORD *)(a1 + 20);
  v7 = 0i64;
  if ( !v6 )
    return 0xFFFFFFFFi64;
  do
  {
    if ( a3 < v5 + *(int *)(v4 + 8 * v7 + v5) )
      break;
    v7 = (unsigned int)(v7 + 1);
  }
  while ( (unsigned int)v7 < v6 );
  if ( (_DWORD)v7 )
    return *(unsigned int *)(v5 + 8i64 * (unsigned int)(v7 - 1) + v4 + 4);
  else
    return 0xFFFFFFFFi64;
}

//----- (00007FF7E5925564) ----------------------------------------------------
__int64 __fastcall sub_7FF7E5925564(__int64 a1, __int64 *a2, int *a3, __int64 a4)
{
  unsigned int v8; // edi
  __int64 v9; // r15
  __int64 v10; // rdx
  __int64 v11; // rcx
  __int64 v12; // rax
  __int64 v13; // rcx
  const void *v14; // rdx
  __int64 v15; // rbx
  __int64 v16; // rcx
  size_t v17; // rbx
  const void *v18; // rax
  __int64 v19; // rcx

  v8 = 0;
  if ( a3[1] )
  {
    v9 = a3[1];
    v10 = v9 + GetImageBase();
  }
  else
  {
    v10 = 0i64;
    LODWORD(v9) = 0;
  }
  if ( v10 )
  {
    v11 = (_DWORD)v9 ? a3[1] + GetImageBase() : 0i64;
    if ( *(_BYTE *)(v11 + 16) && (a3[2] || *a3 < 0) )
    {
      if ( *a3 >= 0 )
        a2 = (__int64 *)(*a2 + a3[2]);
      if ( *(char *)a3 < 0 && (*(_BYTE *)a4 & 0x10) != 0 && qword_7FF7E59698C8 )
      {
        v12 = qword_7FF7E59698C8();
        if ( !v12 || !a2 )
          abort();
        *a2 = v12;
        v13 = v12;
      }
      else if ( (*(_BYTE *)a3 & 8) != 0 )
      {
        v13 = *(_QWORD *)(a1 + 40);
        if ( !v13 || !a2 )
          abort();
        *a2 = v13;
      }
      else
      {
        if ( (*(_BYTE *)a4 & 1) == 0 )
        {
          if ( *(_DWORD *)(a4 + 24) )
          {
            v15 = *(int *)(a4 + 24);
            v16 = v15 + GetThrowImageBase();
          }
          else
          {
            v16 = 0i64;
            LODWORD(v15) = 0;
          }
          if ( v16 )
          {
            if ( !*(_QWORD *)(a1 + 40)
              || !a2
              || (!(_DWORD)v15 ? (v19 = 0i64) : (v19 = *(int *)(a4 + 24) + GetThrowImageBase()), !v19) )
            {
              abort();
            }
            return (unsigned int)((*(_BYTE *)a4 & 4) != 0) + 1;
          }
          else
          {
            if ( !*(_QWORD *)(a1 + 40) || !a2 )
              abort();
            v17 = *(int *)(a4 + 20);
            v18 = (const void *)_AdjustPointer(*(_QWORD *)(a1 + 40), a4 + 8);
            memmove(a2, v18, v17);
          }
          return v8;
        }
        v14 = *(const void **)(a1 + 40);
        if ( !v14 || !a2 )
          abort();
        memmove(a2, v14, *(int *)(a4 + 20));
        if ( *(_DWORD *)(a4 + 20) != 8 || !*a2 )
          return v8;
        v13 = *a2;
      }
      *a2 = _AdjustPointer(v13, a4 + 8);
      return v8;
    }
  }
  return 0i64;
}
// 7FF7E5923E14: using guessed type __int64 __fastcall _AdjustPointer(_QWORD, _QWORD);
// 7FF7E5924CCC: using guessed type __int64 GetImageBase(void);
// 7FF7E5924CE0: using guessed type __int64 GetThrowImageBase(void);
// 7FF7E59698C8: using guessed type __int64 (*qword_7FF7E59698C8)(void);

//----- (00007FF7E59258F8) ----------------------------------------------------
__int64 __fastcall sub_7FF7E59258F8(
        struct EHExceptionRecord *a1,
        unsigned __int64 *a2,
        struct _CONTEXT *a3,
        struct _xDISPATCHER_CONTEXT *a4,
        struct _s_FuncInfo *a5,
        char a6,
        int a7,
        __int64 a8)
{
  unsigned __int64 *v8; // r12
  __ehstate_t HandlerSearchState; // eax
  int v12; // r14d
  __int64 result; // rax
  const struct _s_ESTypeList *v14; // r15
  __int64 v15; // rdx
  __int64 v16; // r9
  unsigned int v17; // r13d
  __int64 v18; // rax
  __int64 v19; // r8
  __m128i v20; // xmm0
  __int64 v21; // rcx
  unsigned int v22; // r12d
  __int64 v23; // rdx
  unsigned __int64 v24; // r15
  __int64 ThrowImageBase; // rax
  ThrowInfo *pThrowInfo; // r8
  const struct _s_ESTypeList *v27; // rdx
  unsigned __int64 *v28; // rax
  int v29; // [rsp+50h] [rbp-B0h]
  char v30; // [rsp+60h] [rbp-A0h]
  int v31; // [rsp+64h] [rbp-9Ch]
  int *v33; // [rsp+70h] [rbp-90h]
  __int64 v35; // [rsp+80h] [rbp-80h]
  __int64 v36; // [rsp+88h] [rbp-78h] BYREF
  __int64 v37; // [rsp+90h] [rbp-70h]
  int v38[2]; // [rsp+98h] [rbp-68h]
  __int64 v39[2]; // [rsp+A0h] [rbp-60h] BYREF
  int v40; // [rsp+B0h] [rbp-50h]
  __int64 v41[2]; // [rsp+B8h] [rbp-48h] BYREF
  __m128i v42; // [rsp+C8h] [rbp-38h]
  __m128i v43; // [rsp+D8h] [rbp-28h] BYREF
  unsigned int v44; // [rsp+F0h] [rbp-10h]
  struct _s_HandlerType pExceptionObject; // [rsp+F8h] [rbp-8h] BYREF

  v8 = a2;
  *(_QWORD *)v38 = a8;
  v30 = 0;
  HandlerSearchState = __FrameHandler3::GetHandlerSearchState(a2, a4, a5);
  v12 = HandlerSearchState;
  if ( HandlerSearchState < -1 || HandlerSearchState >= a5->maxState )
    goto LABEL_53;
  if ( a1->ExceptionCode == -529697949
    && a1->NumberParameters == 4
    && a1->params.magicNumber - 429065504 <= 2
    && !a1->params.pThrowInfo )
  {
    result = _vcrt_getptd();
    if ( !*(_QWORD *)(result + 32) )
      return result;
    a1 = *(struct EHExceptionRecord **)(_vcrt_getptd() + 32);
    v30 = 1;
    a3 = *(struct _CONTEXT **)(_vcrt_getptd() + 40);
    SetThrowImageBase(a1->params.pThrowImageBase);
    if ( a1->ExceptionCode == -529697949
      && a1->NumberParameters == 4
      && a1->params.magicNumber - 429065504 <= 2
      && !a1->params.pThrowInfo )
    {
      goto LABEL_53;
    }
    if ( *(_QWORD *)(_vcrt_getptd() + 56) )
    {
      v14 = *(const struct _s_ESTypeList **)(_vcrt_getptd() + 56);
      *(_QWORD *)(_vcrt_getptd() + 56) = 0i64;
      if ( !IsInExceptionSpec(a1, v14) )
      {
        if ( Is_bad_exception_allowed(v14) )
        {
          LOBYTE(v15) = 1;
          _DestructExceptionObject(a1, v15);
          sub_7FF7E59263A8(&pExceptionObject);
          CxxThrowException(&pExceptionObject, (_ThrowInfo *)&_TI2_AVbad_exception_std__);
        }
        terminate();
      }
    }
  }
  v41[1] = a4->ImageBase;
  v41[0] = (__int64)a5;
  if ( a1->ExceptionCode == -529697949 && a1->NumberParameters == 4 && a1->params.magicNumber - 429065504 <= 2 )
  {
    if ( a5->nTryBlocks )
    {
      __FrameHandler3::GetRangeOfTrysToCheck((unsigned int)&v43, (unsigned int)v41, v12, (_DWORD)a4, (__int64)a5);
      v42 = v43;
      if ( _mm_cvtsi128_si32(_mm_srli_si128(v43, 8)) < v44 )
      {
        v16 = v43.m128i_i64[0];
        v17 = v42.m128i_u32[2];
        v35 = v43.m128i_i64[0];
        do
        {
          v18 = *(_QWORD *)(v16 + 8);
          v19 = *(int *)(*(_QWORD *)v42.m128i_i64[0] + 16i64) + 20i64 * v17;
          v20 = *(__m128i *)(v19 + v18);
          v21 = *(int *)(v19 + v18 + 16);
          v40 = *(_DWORD *)(v19 + v18 + 16);
          *(__m128i *)v39 = v20;
          if ( _mm_cvtsi128_si32(v20) <= v12 && v12 <= SHIDWORD(v39[0]) )
          {
            v22 = 0;
            v23 = a4->ImageBase + v21;
            v24 = HIDWORD(v39[1]);
            v37 = v23;
            if ( HIDWORD(v39[1]) )
            {
              while ( 1 )
              {
                pExceptionObject = *(struct _s_HandlerType *)(v23 + 20i64 * v22);
                v33 = (int *)(a1->params.pThrowInfo->pCatchableTypeArray + GetThrowImageBase() + 4);
                v31 = *(_DWORD *)(GetThrowImageBase() + a1->params.pThrowInfo->pCatchableTypeArray);
                if ( v31 > 0 )
                  break;
LABEL_28:
                if ( ++v22 == (_DWORD)v24 )
                {
                  v8 = a2;
                  goto LABEL_33;
                }
                v23 = v37;
              }
              while ( 1 )
              {
                ThrowImageBase = GetThrowImageBase();
                pThrowInfo = a1->params.pThrowInfo;
                v36 = *v33 + ThrowImageBase;
                if ( (unsigned int)TypeMatchHelper<__FrameHandler3>(&pExceptionObject, v36, pThrowInfo) )
                  break;
                ++v33;
                if ( --v31 <= 0 )
                  goto LABEL_28;
              }
              v8 = a2;
              LOBYTE(v29) = v30;
              CatchIt<__FrameHandler3>(a1, a2, a5, &pExceptionObject, v36, (__int64)v39, a7, v38[0], v29, a6);
LABEL_33:
              v16 = v35;
            }
            else
            {
              v8 = a2;
            }
          }
          ++v17;
        }
        while ( v17 < v44 );
      }
    }
    if ( (*(_DWORD *)a5 & 0x1FFFFFFFu) >= 0x19930521
      && (a5->dispESTypeList && a5->dispESTypeList + GetImageBase()
       || (a5->EHFlags & 4) != 0 && !__FrameHandler3::ExecutionInCatch(a4, a5)) )
    {
      if ( (a5->EHFlags & 4) != 0 )
      {
        *(_QWORD *)(_vcrt_getptd() + 32) = a1;
        *(_QWORD *)(_vcrt_getptd() + 40) = a3;
        terminate();
      }
      if ( a5->dispESTypeList )
        v27 = (const struct _s_ESTypeList *)(a5->dispESTypeList + GetImageBase());
      else
        v27 = 0i64;
      if ( !IsInExceptionSpec(a1, v27) )
      {
        v28 = sub_7FF7E592492C(v8, (unsigned __int64 *)a4, (__int64)a5, &v36);
        __FrameHandler3::UnwindNestedFrames(v8, a1, a3, v28, 0i64, a5, -1, -1, 0i64, a4, a6);
      }
    }
  }
  else if ( a5->nTryBlocks )
  {
    if ( a6 )
      goto LABEL_53;
    FindHandlerForForeignException<__FrameHandler3>(a1, a5, v12, a7, a8);
  }
  result = _vcrt_getptd();
  if ( *(_QWORD *)(result + 56) )
LABEL_53:
    abort();
  return result;
}
// 7FF7E5925D85: variable 'v15' is possibly undefined
// 7FF7E5925C21: variable 'v29' is possibly undefined
// 7FF7E5923D70: using guessed type __int64 __fastcall _DestructExceptionObject(_QWORD, _QWORD);
// 7FF7E592433C: using guessed type __int64 _vcrt_getptd(void);
// 7FF7E59249F8: using guessed type __int64 __fastcall __FrameHandler3::GetRangeOfTrysToCheck(_DWORD, _DWORD, _DWORD, _DWORD, __int64);
// 7FF7E5924CCC: using guessed type __int64 GetImageBase(void);
// 7FF7E5924CE0: using guessed type __int64 GetThrowImageBase(void);
// 7FF7E5924D0C: using guessed type __int64 __fastcall SetThrowImageBase(_QWORD);
// 7FF7E5925FEC: using guessed type __int64 __fastcall TypeMatchHelper<__FrameHandler3>(_QWORD, _QWORD, _QWORD);
// 7FF7E5928A1C: using guessed type void __noreturn terminate(void);

//----- (00007FF7E592636C) ----------------------------------------------------
__int64 __fastcall sub_7FF7E592636C(__int64 a1, __int64 a2)
{
  *(_QWORD *)a1 = &std::exception::`vftable';
  *(_OWORD *)(a1 + 8) = 0i64;
  _std_exception_copy(a2 + 8);
  *(_QWORD *)a1 = &std::bad_exception::`vftable';
  return a1;
}
// 7FF7E5926BA8: using guessed type __int64 __fastcall _std_exception_copy(_QWORD);
// 7FF7E59343B0: using guessed type void *std::exception::`vftable';
// 7FF7E59343E0: using guessed type void *std::bad_exception::`vftable';

//----- (00007FF7E59263A8) ----------------------------------------------------
_QWORD *__fastcall sub_7FF7E59263A8(_QWORD *a1)
{
  a1[2] = 0i64;
  a1[1] = "bad exception";
  *a1 = &std::bad_exception::`vftable';
  return a1;
}
// 7FF7E59343E0: using guessed type void *std::bad_exception::`vftable';

//----- (00007FF7E5926B60) ----------------------------------------------------
__int64 __fastcall sub_7FF7E5926B60(__int64 a1, __int64 a2, __int64 a3, unsigned int a4)
{
  void (__fastcall *v4)(__int64, __int64, __int64); // rax
  __int64 v5; // rdx
  __int64 v6; // r8
  __int64 v7; // rax

  v4 = (void (__fastcall *)(__int64, __int64, __int64))NLG_Notify(a1, a2, a4);
  v4(a3, v5, v6);
  v7 = _NLG_Return2();
  return NLG_Notify(v7, a2, 2i64);
}
// 7FF7E5926B88: variable 'v5' is possibly undefined
// 7FF7E5926B88: variable 'v6' is possibly undefined
// 7FF6A5A3FFFE: using guessed type __int64 (__fastcall *)(_QWORD, _QWORD, _QWORD);
// 7FF7E59242B0: using guessed type __int64 __fastcall NLG_Notify(_QWORD, _QWORD, _QWORD);
// 7FF7E59242E0: using guessed type __int64 _NLG_Return2(void);

//----- (00007FF7E5927728) ----------------------------------------------------
__int64 sub_7FF7E5927728()
{
  return (unsigned int)dword_7FF7E5969A30;
}
// 7FF7E5969A30: using guessed type int dword_7FF7E5969A30;

//----- (00007FF7E5927730) ----------------------------------------------------
void __fastcall sub_7FF7E5927730(int a1)
{
  dword_7FF7E5969A30 = a1;
}
// 7FF7E5969A30: using guessed type int dword_7FF7E5969A30;

//----- (00007FF7E5927758) ----------------------------------------------------
void __fastcall sub_7FF7E5927758(__int64 a1)
{
  qword_7FF7E5969A38 = a1;
}
// 7FF7E5969A38: using guessed type __int64 qword_7FF7E5969A38;

//----- (00007FF7E5927E10) ----------------------------------------------------
__int64 __fastcall sub_7FF7E5927E10(void **a1)
{
  void *v1; // rcx
  __int64 result; // rax

  v1 = *a1;
  if ( v1 != qword_7FF7E5969B60 )
    return unknown_libname_14(v1);
  return result;
}

//----- (00007FF7E5927E2C) ----------------------------------------------------
__int64 __fastcall sub_7FF7E5927E2C(void **a1)
{
  void *v1; // rcx
  __int64 result; // rax

  v1 = *a1;
  if ( v1 != qword_7FF7E5969B58 )
    return unknown_libname_14(v1);
  return result;
}

//----- (00007FF7E592824C) ----------------------------------------------------
void __fastcall sub_7FF7E592824C(__int64 a1)
{
  qword_7FF7E5969B70 = a1;
}
// 7FF7E5969B70: using guessed type __int64 qword_7FF7E5969B70;

//----- (00007FF7E5928334) ----------------------------------------------------
int *sub_7FF7E5928334()
{
  return &dword_7FF7E5969B88;
}
// 7FF7E5969B88: using guessed type int dword_7FF7E5969B88;

//----- (00007FF7E592833C) ----------------------------------------------------
void **sub_7FF7E592833C()
{
  return &qword_7FF7E5969B90;
}

//----- (00007FF7E592845C) ----------------------------------------------------
__int64 sub_7FF7E592845C()
{
  return (unsigned int)dword_7FF7E5969BB4;
}
// 7FF7E5969BB4: using guessed type int dword_7FF7E5969BB4;

//----- (00007FF7E5928490) ----------------------------------------------------
void *sub_7FF7E5928490()
{
  return &unk_7FF7E5969BB8;
}

//----- (00007FF7E59287E0) ----------------------------------------------------
int __fastcall sub_7FF7E59287E0(_onexit_t Function)
{
  return register_onexit_function(&stru_7FF7E5969BC0, Function);
}

//----- (00007FF7E592892C) ----------------------------------------------------
__vcrt_bool sub_7FF7E592892C()
{
  return _vcrt_uninitialize(0);
}

//----- (00007FF7E5928D80) ----------------------------------------------------
void __fastcall sub_7FF7E5928D80(__int64 a1)
{
  qword_7FF7E5969BF0 = a1;
}
// 7FF7E5969BF0: using guessed type __int64 qword_7FF7E5969BF0;

//----- (00007FF7E5929224) ----------------------------------------------------
__int64 __fastcall sub_7FF7E5929224(__int64 a1, __int64 *a2)
{
  __int64 result; // rax

  result = qword_7FF7E5969BF8;
  if ( *a2 != qword_7FF7E5969BF8 )
  {
    result = *(unsigned int *)(a1 + 936);
    if ( ((unsigned int)result & dword_7FF7E593E7B0) == 0 )
    {
      result = _acrt_update_thread_locale_data();
      *a2 = result;
    }
  }
  return result;
}
// 7FF7E592C7B4: using guessed type __int64 _acrt_update_thread_locale_data(void);
// 7FF7E593E7B0: using guessed type int dword_7FF7E593E7B0;
// 7FF7E5969BF8: using guessed type __int64 qword_7FF7E5969BF8;

//----- (00007FF7E5929258) ----------------------------------------------------
__int64 __fastcall sub_7FF7E5929258(__int64 a1, __int64 *a2, __int64 a3)
{
  __int64 result; // rax

  result = qword_7FF7E5969BF8[a3];
  if ( *a2 != result )
  {
    result = *(unsigned int *)(a1 + 936);
    if ( ((unsigned int)result & dword_7FF7E593E7B0) == 0 )
    {
      result = _acrt_update_thread_locale_data();
      *a2 = result;
    }
  }
  return result;
}
// 7FF7E592C7B4: using guessed type __int64 _acrt_update_thread_locale_data(void);
// 7FF7E593E7B0: using guessed type int dword_7FF7E593E7B0;
// 7FF7E5969BF8: using guessed type __int64 qword_7FF7E5969BF8[];

//----- (00007FF7E5929290) ----------------------------------------------------
__int64 __fastcall sub_7FF7E5929290(__int64 a1, __int64 *a2)
{
  __int64 result; // rax

  result = (__int64)Block;
  if ( (struct __crt_multibyte_data *)*a2 != Block )
  {
    result = *(unsigned int *)(a1 + 936);
    if ( ((unsigned int)result & dword_7FF7E593E7B0) == 0 )
    {
      result = _acrt_update_thread_multibyte_data();
      *a2 = result;
    }
  }
  return result;
}
// 7FF7E592AFC0: using guessed type __int64 _acrt_update_thread_multibyte_data(void);
// 7FF7E593E7B0: using guessed type int dword_7FF7E593E7B0;

//----- (00007FF7E59292C4) ----------------------------------------------------
__int64 __fastcall sub_7FF7E59292C4(__int64 a1, __int64 *a2, __int64 a3)
{
  __int64 result; // rax

  result = (__int64)*(&Block + a3);
  if ( *a2 != result )
  {
    result = *(unsigned int *)(a1 + 936);
    if ( ((unsigned int)result & dword_7FF7E593E7B0) == 0 )
    {
      result = _acrt_update_thread_multibyte_data();
      *a2 = result;
    }
  }
  return result;
}
// 7FF7E592AFC0: using guessed type __int64 _acrt_update_thread_multibyte_data(void);
// 7FF7E593E7B0: using guessed type int dword_7FF7E593E7B0;

//----- (00007FF7E592B9D0) ----------------------------------------------------
void __fastcall sub_7FF7E592B9D0(int a1)
{
  EnterCriticalSection((LPCRITICAL_SECTION)&unk_7FF7E5969C20 + a1);
}

//----- (00007FF7E592BA24) ----------------------------------------------------
void __fastcall sub_7FF7E592BA24(int a1)
{
  LeaveCriticalSection((LPCRITICAL_SECTION)&unk_7FF7E5969C20 + a1);
}

//----- (00007FF7E592BC1C) ----------------------------------------------------
void __fastcall sub_7FF7E592BC1C(int a1)
{
  EnterCriticalSection((LPCRITICAL_SECTION)(qword_7FF7E5969E60[(__int64)a1 >> 6] + 72i64 * (a1 & 0x3F)));
}
// 7FF7E5969E60: using guessed type __int64 qword_7FF7E5969E60[128];

//----- (00007FF7E592BC44) ----------------------------------------------------
void __fastcall sub_7FF7E592BC44(int a1)
{
  LeaveCriticalSection((LPCRITICAL_SECTION)(qword_7FF7E5969E60[(__int64)a1 >> 6] + 72i64 * (a1 & 0x3F)));
}
// 7FF7E5969E60: using guessed type __int64 qword_7FF7E5969E60[128];

//----- (00007FF7E592CECC) ----------------------------------------------------
char sub_7FF7E592CECC()
{
  hHeap = 0i64;
  return 1;
}

//----- (00007FF7E592CFB4) ----------------------------------------------------
void __fastcall sub_7FF7E592CFB4(__int64 a1)
{
  qword_7FF7E596A410 = a1;
}
// 7FF7E596A410: using guessed type __int64 qword_7FF7E596A410;

//----- (00007FF7E592D804) ----------------------------------------------------
void __fastcall sub_7FF7E592D804(__int64 a1)
{
  EnterCriticalSection((LPCRITICAL_SECTION)(a1 + 48));
}

//----- (00007FF7E592D810) ----------------------------------------------------
void __fastcall sub_7FF7E592D810(__int64 a1)
{
  LeaveCriticalSection((LPCRITICAL_SECTION)(a1 + 48));
}

//----- (00007FF7E5930BC8) ----------------------------------------------------
BOOL sub_7FF7E5930BC8()
{
  BOOL result; // eax

  if ( (unsigned __int64)hObject <= 0xFFFFFFFFFFFFFFFDui64 )
    return CloseHandle(hObject);
  return result;
}

//----- (00007FF7E5930D1C) ----------------------------------------------------
__int64 __fastcall sub_7FF7E5930D1C(int a1, __int64 a2)
{
  int v3; // [rsp+30h] [rbp-28h] BYREF
  __int64 v4[4]; // [rsp+38h] [rbp-20h] BYREF
  int v5; // [rsp+60h] [rbp+8h] BYREF
  char v6; // [rsp+70h] [rbp+18h] BYREF
  int v7; // [rsp+78h] [rbp+20h] BYREF

  v5 = a1;
  if ( a1 == -2 )
  {
    *(_BYTE *)(a2 + 56) = 1;
    *(_DWORD *)(a2 + 52) = 0;
    *(_BYTE *)(a2 + 48) = 1;
    *(_DWORD *)(a2 + 44) = 9;
  }
  else
  {
    if ( a1 >= 0
      && a1 < (unsigned int)dword_7FF7E596A260
      && (*(_BYTE *)(qword_7FF7E5969E60[(__int64)a1 >> 6] + 72i64 * (a1 & 0x3F) + 56) & 1) != 0 )
    {
      v4[1] = a2;
      v7 = a1;
      v3 = a1;
      v4[0] = (__int64)&v5;
      return __crt_seh_guarded_call<int>::operator()<_lambda_ad8af0d99a0adf03d037d7dffe354bb5_,_lambda_c9ba49e555ba839a7b07aa3fbecb7617_ &,_lambda_2f1ebd5d68526518146ae959c9e734c8_>(
               &v6,
               &v3,
               v4,
               &v7);
    }
    *(_BYTE *)(a2 + 56) = 1;
    *(_DWORD *)(a2 + 52) = 0;
    *(_BYTE *)(a2 + 48) = 1;
    *(_DWORD *)(a2 + 44) = 9;
    invalid_parameter_internal(0i64, 0i64, 0i64, 0, 0i64, (__crt_cached_ptd_host *)a2);
  }
  return 0xFFFFFFFFi64;
}
// 7FF7E5930CA4: using guessed type __int64 __fastcall __crt_seh_guarded_call<int>::operator()<_lambda_ad8af0d99a0adf03d037d7dffe354bb5_,_lambda_c9ba49e555ba839a7b07aa3fbecb7617_ &,_lambda_2f1ebd5d68526518146ae959c9e734c8_>(_QWORD, _QWORD, _QWORD, _QWORD);
// 7FF7E5969E60: using guessed type __int64 qword_7FF7E5969E60[128];
// 7FF7E596A260: using guessed type int dword_7FF7E596A260;

//----- (00007FF7E5931790) ----------------------------------------------------
_BOOL8 __fastcall sub_7FF7E5931790(__int64 a1)
{
  __int64 v1; // rdx

  if ( *(_WORD *)a1 == 23117 && (v1 = a1 + *(int *)(a1 + 60), *(_DWORD *)v1 == 17744) )
    return *(_WORD *)(v1 + 24) == 523;
  else
    return 0i64;
}

//----- (00007FF7E59317BC) ----------------------------------------------------
_QWORD *__fastcall sub_7FF7E59317BC(_QWORD *a1, char a2)
{
  *a1 = &type_info::`vftable';
  if ( (a2 & 1) != 0 )
    j_j_free(a1);
  return a1;
}
// 7FF7E593A878: using guessed type void *type_info::`vftable';

//----- (00007FF7E5931E7C) ----------------------------------------------------
__int64 __fastcall sub_7FF7E5931E7C(__int64 a1, __int64 a2)
{
  __int64 v3; // rbx
  __int64 v4; // rbx

  *(_QWORD *)(a2 + 80) = a1;
  *(_QWORD *)(a2 + 72) = a1;
  *(_QWORD *)(_vcrt_getptd() + 112) = *(_QWORD *)(a2 + 128);
  v3 = *(_QWORD *)(*(_QWORD *)(a2 + 152) + 8i64);
  *(_QWORD *)(_vcrt_getptd() + 96) = v3;
  v4 = *(_QWORD *)(**(_QWORD **)(a2 + 72) + 56i64);
  *(_QWORD *)(_vcrt_getptd() + 104) = v4;
  __InternalCxxFrameHandler<__FrameHandler3>(
    **(struct EHExceptionRecord ***)(a2 + 72),
    *(unsigned __int64 **)(a2 + 136),
    *(struct _s_FuncInfo **)(a2 + 160),
    0,
    0,
    1);
  *(_QWORD *)(_vcrt_getptd() + 112) = 0i64;
  *(_DWORD *)(a2 + 64) = 1;
  return 1i64;
}
// 7FF7E592433C: using guessed type __int64 _vcrt_getptd(void);

//----- (00007FF7E593EA00) ----------------------------------------------------
bool __fastcall dyn_func(QWORD *a1)
{
  __int64 v1; // rbx
  int *v2; // r10
  int *v3; // r11
  int v4; // r9d
  unsigned int v5; // kr00_4
  char v6; // al
  int v8; // [rsp+0h] [rbp-10h] BYREF
  __int16 v9; // [rsp+4h] [rbp-Ch]
  char v10[8]; // [rsp+28h] [rbp+18h] BYREF

  strcpy(v10, "ten");
  v2 = &v8;
  v3 = &v8;
  v4 = 0;
  v9 = 0;
  v8 = 0x173B1716;
  *(_BYTE *)(v1 - 12) = 'V';
  do
  {
    v5 = v4++;
    v6 = *(_BYTE *)v2;
    v2 = (int *)((char *)v2 + 1);
    *(_BYTE *)v3 = v10[v5 % 3] ^ v6;
    v3 = (int *)((char *)v3 + 1);
  }
  while ( v4 < 5 );
  return strcmp((const char *)&v8, (const char *)a1) == 0;
}
// 7FF7E593EA40: variable 'v1' is possibly undefined

//----- (00007FF7E593EAE0) ----------------------------------------------------
// positive sp value has been detected, the output may be wrong!
void __fastcall dyn_func2()
{
  __asm { xlat }
  JUMPOUT(0x7FF7E593EAE1i64);
}
// 7FF7E593EB82: positive sp value 30 has been found
// 7FF7E593EAE0: control flows out of bounds to 7FF7E593EAE1

// nfuncs=458 queued=76 decompiled=76 lumina nreq=0 worse=0 better=0
// ALL OK, 76 function(s) have been successfully decompiled
