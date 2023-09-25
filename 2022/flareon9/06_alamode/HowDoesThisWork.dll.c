typedef unsigned char   undefined;

typedef unsigned long long    GUID;
typedef unsigned int    ImageBaseOffset32;
typedef unsigned char    bool;
typedef unsigned char    byte;
typedef unsigned int    dword;
float10
typedef unsigned long long    qword;
typedef unsigned char    uchar;
typedef unsigned int    uint;
typedef unsigned long    ulong;
typedef unsigned long long    ulonglong;
typedef unsigned char    undefined1;
typedef unsigned short    undefined2;
typedef unsigned int    undefined4;
typedef unsigned long long    undefined8;
typedef unsigned short    ushort;
typedef short    wchar_t;
typedef unsigned short    word;
typedef struct _s_HandlerType _s_HandlerType, *P_s_HandlerType;

typedef struct TypeDescriptor TypeDescriptor, *PTypeDescriptor;

typedef int ptrdiff_t;

struct TypeDescriptor {
    void * pVFTable;
    void * spare;
    char name[0];
};

struct _s_HandlerType {
    uint adjectives;
    struct TypeDescriptor * pType;
    ptrdiff_t dispCatchObj;
    void * addressOfHandler;
};

typedef struct _s_FuncInfo _s_FuncInfo, *P_s_FuncInfo;

typedef int __ehstate_t;

typedef struct _s_UnwindMapEntry _s_UnwindMapEntry, *P_s_UnwindMapEntry;

typedef struct _s_UnwindMapEntry UnwindMapEntry;

typedef struct _s_TryBlockMapEntry _s_TryBlockMapEntry, *P_s_TryBlockMapEntry;

typedef struct _s_TryBlockMapEntry TryBlockMapEntry;

typedef struct _s_ESTypeList _s_ESTypeList, *P_s_ESTypeList;

typedef struct _s_ESTypeList ESTypeList;

typedef struct _s_HandlerType HandlerType;

struct _s_FuncInfo {
    uint magicNumber_and_bbtFlags;
    __ehstate_t maxState;
    UnwindMapEntry * pUnwindMap;
    uint nTryBlocks;
    TryBlockMapEntry * pTryBlockMap;
    uint nIPMapEntries;
    void * pIPToStateMap;
    ESTypeList * pESTypeList;
    int EHFlags;
};

struct _s_UnwindMapEntry {
    __ehstate_t toState;
    void (* action)(void);
};

struct _s_ESTypeList {
    int nCount;
    HandlerType * pTypeArray;
};

struct _s_TryBlockMapEntry {
    __ehstate_t tryLow;
    __ehstate_t tryHigh;
    __ehstate_t catchHigh;
    int nCatches;
    HandlerType * pHandlerArray;
};

typedef struct _s__RTTIBaseClassDescriptor _s__RTTIBaseClassDescriptor, *P_s__RTTIBaseClassDescriptor;

typedef struct PMD PMD, *PPMD;

typedef struct _s__RTTIClassHierarchyDescriptor _s__RTTIClassHierarchyDescriptor, *P_s__RTTIClassHierarchyDescriptor;

typedef struct _s__RTTIClassHierarchyDescriptor RTTIClassHierarchyDescriptor;

typedef struct _s__RTTIBaseClassDescriptor RTTIBaseClassDescriptor;

struct PMD {
    ptrdiff_t mdisp;
    ptrdiff_t pdisp;
    ptrdiff_t vdisp;
};

struct _s__RTTIBaseClassDescriptor {
    struct TypeDescriptor * pTypeDescriptor; // ref to TypeDescriptor (RTTI 0) for class
    dword numContainedBases; // count of extended classes in BaseClassArray (RTTI 2)
    struct PMD where; // member displacement structure
    dword attributes; // bit flags
    RTTIClassHierarchyDescriptor * pClassHierarchyDescriptor; // ref to ClassHierarchyDescriptor (RTTI 3) for class
};

struct _s__RTTIClassHierarchyDescriptor {
    dword signature;
    dword attributes; // bit flags
    dword numBaseClasses; // number of base classes (i.e. rtti1Count)
    RTTIBaseClassDescriptor * * pBaseClassArray; // ref to BaseClassArray (RTTI 2)
};

typedef unsigned short    wchar16;
typedef struct type_info type_info, *Ptype_info;

struct type_info { // PlaceHolder Class Structure
};

typedef struct _s__RTTICompleteObjectLocator _s__RTTICompleteObjectLocator, *P_s__RTTICompleteObjectLocator;

typedef struct _s__RTTICompleteObjectLocator RTTICompleteObjectLocator;

struct _s__RTTICompleteObjectLocator {
    dword signature;
    dword offset; // offset of vbtable within class
    dword cdOffset; // constructor displacement offset
    struct TypeDescriptor * pTypeDescriptor; // ref to TypeDescriptor (RTTI 0) for class
    RTTIClassHierarchyDescriptor * pClassDescriptor; // ref to ClassHierarchyDescriptor (RTTI 3)
};

typedef struct _s_FuncInfo FuncInfo;

typedef struct _cpinfo _cpinfo, *P_cpinfo;

typedef uint UINT;

typedef uchar BYTE;

struct _cpinfo {
    UINT MaxCharSize;
    BYTE DefaultChar[2];
    BYTE LeadByte[12];
};

typedef struct _cpinfo * LPCPINFO;

typedef struct _OVERLAPPED _OVERLAPPED, *P_OVERLAPPED;

typedef ulong ULONG_PTR;

typedef union _union_518 _union_518, *P_union_518;

typedef void * HANDLE;

typedef struct _struct_519 _struct_519, *P_struct_519;

typedef void * PVOID;

typedef ulong DWORD;

struct _struct_519 {
    DWORD Offset;
    DWORD OffsetHigh;
};

union _union_518 {
    struct _struct_519 s;
    PVOID Pointer;
};

struct _OVERLAPPED {
    ULONG_PTR Internal;
    ULONG_PTR InternalHigh;
    union _union_518 u;
    HANDLE hEvent;
};

typedef struct _SECURITY_ATTRIBUTES _SECURITY_ATTRIBUTES, *P_SECURITY_ATTRIBUTES;

typedef void * LPVOID;

typedef int BOOL;

struct _SECURITY_ATTRIBUTES {
    DWORD nLength;
    LPVOID lpSecurityDescriptor;
    BOOL bInheritHandle;
};

typedef enum _FINDEX_INFO_LEVELS {
    FindExInfoStandard=0,
    FindExInfoBasic=1,
    FindExInfoMaxInfoLevel=2
} _FINDEX_INFO_LEVELS;

typedef struct _STARTUPINFOW _STARTUPINFOW, *P_STARTUPINFOW;

typedef wchar_t WCHAR;

typedef WCHAR * LPWSTR;

typedef ushort WORD;

typedef BYTE * LPBYTE;

struct _STARTUPINFOW {
    DWORD cb;
    LPWSTR lpReserved;
    LPWSTR lpDesktop;
    LPWSTR lpTitle;
    DWORD dwX;
    DWORD dwY;
    DWORD dwXSize;
    DWORD dwYSize;
    DWORD dwXCountChars;
    DWORD dwYCountChars;
    DWORD dwFillAttribute;
    DWORD dwFlags;
    WORD wShowWindow;
    WORD cbReserved2;
    LPBYTE lpReserved2;
    HANDLE hStdInput;
    HANDLE hStdOutput;
    HANDLE hStdError;
};

typedef struct _STARTUPINFOW * LPSTARTUPINFOW;

typedef struct _WIN32_FIND_DATAW _WIN32_FIND_DATAW, *P_WIN32_FIND_DATAW;

typedef struct _WIN32_FIND_DATAW * LPWIN32_FIND_DATAW;

typedef struct _FILETIME _FILETIME, *P_FILETIME;

typedef struct _FILETIME FILETIME;

struct _FILETIME {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
};

struct _WIN32_FIND_DATAW {
    DWORD dwFileAttributes;
    FILETIME ftCreationTime;
    FILETIME ftLastAccessTime;
    FILETIME ftLastWriteTime;
    DWORD nFileSizeHigh;
    DWORD nFileSizeLow;
    DWORD dwReserved0;
    DWORD dwReserved1;
    WCHAR cFileName[260];
    WCHAR cAlternateFileName[14];
};

typedef struct _OVERLAPPED * LPOVERLAPPED;

typedef enum _FINDEX_SEARCH_OPS {
    FindExSearchNameMatch=0,
    FindExSearchLimitToDirectories=1,
    FindExSearchLimitToDevices=2,
    FindExSearchMaxSearchOp=3
} _FINDEX_SEARCH_OPS;

typedef enum _FINDEX_SEARCH_OPS FINDEX_SEARCH_OPS;

typedef struct _SECURITY_ATTRIBUTES * LPSECURITY_ATTRIBUTES;

typedef enum _FINDEX_INFO_LEVELS FINDEX_INFO_LEVELS;

typedef struct _RTL_CRITICAL_SECTION _RTL_CRITICAL_SECTION, *P_RTL_CRITICAL_SECTION;

typedef struct _RTL_CRITICAL_SECTION * PRTL_CRITICAL_SECTION;

typedef PRTL_CRITICAL_SECTION LPCRITICAL_SECTION;

typedef struct _RTL_CRITICAL_SECTION_DEBUG _RTL_CRITICAL_SECTION_DEBUG, *P_RTL_CRITICAL_SECTION_DEBUG;

typedef struct _RTL_CRITICAL_SECTION_DEBUG * PRTL_CRITICAL_SECTION_DEBUG;

typedef long LONG;

typedef struct _LIST_ENTRY _LIST_ENTRY, *P_LIST_ENTRY;

typedef struct _LIST_ENTRY LIST_ENTRY;

struct _RTL_CRITICAL_SECTION {
    PRTL_CRITICAL_SECTION_DEBUG DebugInfo;
    LONG LockCount;
    LONG RecursionCount;
    HANDLE OwningThread;
    HANDLE LockSemaphore;
    ULONG_PTR SpinCount;
};

struct _LIST_ENTRY {
    struct _LIST_ENTRY * Flink;
    struct _LIST_ENTRY * Blink;
};

struct _RTL_CRITICAL_SECTION_DEBUG {
    WORD Type;
    WORD CreatorBackTraceIndex;
    struct _RTL_CRITICAL_SECTION * CriticalSection;
    LIST_ENTRY ProcessLocksList;
    DWORD EntryCount;
    DWORD ContentionCount;
    DWORD Flags;
    WORD CreatorBackTraceIndexHigh;
    WORD SpareWORD;
};

typedef struct _EXCEPTION_POINTERS _EXCEPTION_POINTERS, *P_EXCEPTION_POINTERS;

typedef LONG (* PTOP_LEVEL_EXCEPTION_FILTER)(struct _EXCEPTION_POINTERS *);

typedef struct _EXCEPTION_RECORD _EXCEPTION_RECORD, *P_EXCEPTION_RECORD;

typedef struct _EXCEPTION_RECORD EXCEPTION_RECORD;

typedef EXCEPTION_RECORD * PEXCEPTION_RECORD;

typedef struct _CONTEXT _CONTEXT, *P_CONTEXT;

typedef struct _CONTEXT CONTEXT;

typedef CONTEXT * PCONTEXT;

typedef struct _FLOATING_SAVE_AREA _FLOATING_SAVE_AREA, *P_FLOATING_SAVE_AREA;

typedef struct _FLOATING_SAVE_AREA FLOATING_SAVE_AREA;

struct _FLOATING_SAVE_AREA {
    DWORD ControlWord;
    DWORD StatusWord;
    DWORD TagWord;
    DWORD ErrorOffset;
    DWORD ErrorSelector;
    DWORD DataOffset;
    DWORD DataSelector;
    BYTE RegisterArea[80];
    DWORD Cr0NpxState;
};

struct _CONTEXT {
    DWORD ContextFlags;
    DWORD Dr0;
    DWORD Dr1;
    DWORD Dr2;
    DWORD Dr3;
    DWORD Dr6;
    DWORD Dr7;
    FLOATING_SAVE_AREA FloatSave;
    DWORD SegGs;
    DWORD SegFs;
    DWORD SegEs;
    DWORD SegDs;
    DWORD Edi;
    DWORD Esi;
    DWORD Ebx;
    DWORD Edx;
    DWORD Ecx;
    DWORD Eax;
    DWORD Ebp;
    DWORD Eip;
    DWORD SegCs;
    DWORD EFlags;
    DWORD Esp;
    DWORD SegSs;
    BYTE ExtendedRegisters[512];
};

struct _EXCEPTION_RECORD {
    DWORD ExceptionCode;
    DWORD ExceptionFlags;
    struct _EXCEPTION_RECORD * ExceptionRecord;
    PVOID ExceptionAddress;
    DWORD NumberParameters;
    ULONG_PTR ExceptionInformation[15];
};

struct _EXCEPTION_POINTERS {
    PEXCEPTION_RECORD ExceptionRecord;
    PCONTEXT ContextRecord;
};

typedef PTOP_LEVEL_EXCEPTION_FILTER LPTOP_LEVEL_EXCEPTION_FILTER;

typedef struct _iobuf _iobuf, *P_iobuf;

struct _iobuf {
    char * _ptr;
    int _cnt;
    char * _base;
    int _flag;
    int _file;
    int _charbuf;
    int _bufsiz;
    char * _tmpfname;
};

typedef struct _iobuf FILE;

typedef uint uintptr_t;

typedef struct lconv lconv, *Plconv;

struct lconv {
    char * decimal_point;
    char * thousands_sep;
    char * grouping;
    char * int_curr_symbol;
    char * currency_symbol;
    char * mon_decimal_point;
    char * mon_thousands_sep;
    char * mon_grouping;
    char * positive_sign;
    char * negative_sign;
    char int_frac_digits;
    char frac_digits;
    char p_cs_precedes;
    char p_sep_by_space;
    char n_cs_precedes;
    char n_sep_by_space;
    char p_sign_posn;
    char n_sign_posn;
    wchar_t * _W_decimal_point;
    wchar_t * _W_thousands_sep;
    wchar_t * _W_int_curr_symbol;
    wchar_t * _W_currency_symbol;
    wchar_t * _W_mon_decimal_point;
    wchar_t * _W_mon_thousands_sep;
    wchar_t * _W_positive_sign;
    wchar_t * _W_negative_sign;
};

typedef ushort wint_t;

typedef struct threadlocaleinfostruct threadlocaleinfostruct, *Pthreadlocaleinfostruct;

typedef struct threadlocaleinfostruct * pthreadlocinfo;

typedef struct localerefcount localerefcount, *Plocalerefcount;

typedef struct localerefcount locrefcount;

typedef struct __lc_time_data __lc_time_data, *P__lc_time_data;

struct localerefcount {
    char * locale;
    wchar_t * wlocale;
    int * refcount;
    int * wrefcount;
};

struct threadlocaleinfostruct {
    int refcount;
    uint lc_codepage;
    uint lc_collate_cp;
    uint lc_time_cp;
    locrefcount lc_category[6];
    int lc_clike;
    int mb_cur_max;
    int * lconv_intl_refcount;
    int * lconv_num_refcount;
    int * lconv_mon_refcount;
    struct lconv * lconv;
    int * ctype1_refcount;
    ushort * ctype1;
    ushort * pctype;
    uchar * pclmap;
    uchar * pcumap;
    struct __lc_time_data * lc_time_curr;
    wchar_t * locale_name[6];
};

struct __lc_time_data {
    char * wday_abbr[7];
    char * wday[7];
    char * month_abbr[12];
    char * month[12];
    char * ampm[2];
    char * ww_sdatefmt;
    char * ww_ldatefmt;
    char * ww_timefmt;
    int ww_caltype;
    int refcount;
    wchar_t * _W_wday_abbr[7];
    wchar_t * _W_wday[7];
    wchar_t * _W_month_abbr[12];
    wchar_t * _W_month[12];
    wchar_t * _W_ampm[2];
    wchar_t * _W_ww_sdatefmt;
    wchar_t * _W_ww_ldatefmt;
    wchar_t * _W_ww_timefmt;
    wchar_t * _W_ww_locale_name;
};

typedef uint size_t;

typedef int errno_t;

typedef struct localeinfo_struct localeinfo_struct, *Plocaleinfo_struct;

typedef struct threadmbcinfostruct threadmbcinfostruct, *Pthreadmbcinfostruct;

typedef struct threadmbcinfostruct * pthreadmbcinfo;

struct threadmbcinfostruct {
    int refcount;
    int mbcodepage;
    int ismbcodepage;
    ushort mbulinfo[6];
    uchar mbctype[257];
    uchar mbcasemap[256];
    wchar_t * mblocalename;
};

struct localeinfo_struct {
    pthreadlocinfo locinfo;
    pthreadmbcinfo mbcinfo;
};

typedef struct localeinfo_struct * _locale_t;

typedef size_t rsize_t;

typedef struct exception exception, *Pexception;

struct exception { // PlaceHolder Class Structure
};

typedef struct _IMAGE_SECTION_HEADER _IMAGE_SECTION_HEADER, *P_IMAGE_SECTION_HEADER;

typedef union _union_226 _union_226, *P_union_226;

union _union_226 {
    DWORD PhysicalAddress;
    DWORD VirtualSize;
};

struct _IMAGE_SECTION_HEADER {
    BYTE Name[8];
    union _union_226 Misc;
    DWORD VirtualAddress;
    DWORD SizeOfRawData;
    DWORD PointerToRawData;
    DWORD PointerToRelocations;
    DWORD PointerToLinenumbers;
    WORD NumberOfRelocations;
    WORD NumberOfLinenumbers;
    DWORD Characteristics;
};

typedef union _SLIST_HEADER _SLIST_HEADER, *P_SLIST_HEADER;

typedef double ULONGLONG;

typedef struct _struct_299 _struct_299, *P_struct_299;

typedef struct _SINGLE_LIST_ENTRY _SINGLE_LIST_ENTRY, *P_SINGLE_LIST_ENTRY;

typedef struct _SINGLE_LIST_ENTRY SINGLE_LIST_ENTRY;

struct _SINGLE_LIST_ENTRY {
    struct _SINGLE_LIST_ENTRY * Next;
};

struct _struct_299 {
    SINGLE_LIST_ENTRY Next;
    WORD Depth;
    WORD Sequence;
};

union _SLIST_HEADER {
    ULONGLONG Alignment;
    struct _struct_299 s;
};

typedef char CHAR;

typedef CHAR * LPCSTR;

typedef struct _SINGLE_LIST_ENTRY * PSINGLE_LIST_ENTRY;

typedef CHAR * LPSTR;

typedef union _LARGE_INTEGER _LARGE_INTEGER, *P_LARGE_INTEGER;

typedef struct _struct_19 _struct_19, *P_struct_19;

typedef struct _struct_20 _struct_20, *P_struct_20;

typedef double LONGLONG;

struct _struct_20 {
    DWORD LowPart;
    LONG HighPart;
};

struct _struct_19 {
    DWORD LowPart;
    LONG HighPart;
};

union _LARGE_INTEGER {
    struct _struct_19 s;
    struct _struct_20 u;
    LONGLONG QuadPart;
};

typedef union _LARGE_INTEGER LARGE_INTEGER;

typedef struct _IMAGE_SECTION_HEADER * PIMAGE_SECTION_HEADER;

typedef WCHAR * LPWCH;

typedef WCHAR * LPCWSTR;

typedef union _SLIST_HEADER * PSLIST_HEADER;

typedef LARGE_INTEGER * PLARGE_INTEGER;

typedef DWORD LCID;

typedef struct IMAGE_DOS_HEADER IMAGE_DOS_HEADER, *PIMAGE_DOS_HEADER;

struct IMAGE_DOS_HEADER {
    char e_magic[2]; // Magic number
    word e_cblp; // Bytes of last page
    word e_cp; // Pages in file
    word e_crlc; // Relocations
    word e_cparhdr; // Size of header in paragraphs
    word e_minalloc; // Minimum extra paragraphs needed
    word e_maxalloc; // Maximum extra paragraphs needed
    word e_ss; // Initial (relative) SS value
    word e_sp; // Initial SP value
    word e_csum; // Checksum
    word e_ip; // Initial IP value
    word e_cs; // Initial (relative) CS value
    word e_lfarlc; // File address of relocation table
    word e_ovno; // Overlay number
    word e_res[4][4]; // Reserved words
    word e_oemid; // OEM identifier (for e_oeminfo)
    word e_oeminfo; // OEM information; e_oemid specific
    word e_res2[10][10]; // Reserved words
    dword e_lfanew; // File address of new exe header
    byte e_program[64]; // Actual DOS program
};

typedef ULONG_PTR DWORD_PTR;

typedef ULONG_PTR SIZE_T;

typedef DWORD * LPDWORD;

typedef struct HINSTANCE__ HINSTANCE__, *PHINSTANCE__;

typedef struct HINSTANCE__ * HINSTANCE;

struct HINSTANCE__ {
    int unused;
};

typedef HINSTANCE HMODULE;

typedef struct _FILETIME * LPFILETIME;

typedef int (* FARPROC)(void);

typedef WORD * LPWORD;

typedef BOOL * LPBOOL;

typedef BYTE * PBYTE;

typedef void * LPCVOID;

typedef struct IMAGE_OPTIONAL_HEADER32 IMAGE_OPTIONAL_HEADER32, *PIMAGE_OPTIONAL_HEADER32;

typedef struct IMAGE_DATA_DIRECTORY IMAGE_DATA_DIRECTORY, *PIMAGE_DATA_DIRECTORY;

struct IMAGE_DATA_DIRECTORY {
    ImageBaseOffset32 VirtualAddress;
    dword Size;
};

struct IMAGE_OPTIONAL_HEADER32 {
    word Magic;
    byte MajorLinkerVersion;
    byte MinorLinkerVersion;
    dword SizeOfCode;
    dword SizeOfInitializedData;
    dword SizeOfUninitializedData;
    ImageBaseOffset32 AddressOfEntryPoint;
    ImageBaseOffset32 BaseOfCode;
    ImageBaseOffset32 BaseOfData;
    pointer32 ImageBase;
    dword SectionAlignment;
    dword FileAlignment;
    word MajorOperatingSystemVersion;
    word MinorOperatingSystemVersion;
    word MajorImageVersion;
    word MinorImageVersion;
    word MajorSubsystemVersion;
    word MinorSubsystemVersion;
    dword Win32VersionValue;
    dword SizeOfImage;
    dword SizeOfHeaders;
    dword CheckSum;
    word Subsystem;
    word DllCharacteristics;
    dword SizeOfStackReserve;
    dword SizeOfStackCommit;
    dword SizeOfHeapReserve;
    dword SizeOfHeapCommit;
    dword LoaderFlags;
    dword NumberOfRvaAndSizes;
    struct IMAGE_DATA_DIRECTORY DataDirectory[16];
};

typedef struct IMAGE_LOAD_CONFIG_CODE_INTEGRITY IMAGE_LOAD_CONFIG_CODE_INTEGRITY, *PIMAGE_LOAD_CONFIG_CODE_INTEGRITY;

struct IMAGE_LOAD_CONFIG_CODE_INTEGRITY {
    word Flags;
    word Catalog;
    dword CatalogOffset;
    dword Reserved;
};

typedef struct IMAGE_DEBUG_DIRECTORY IMAGE_DEBUG_DIRECTORY, *PIMAGE_DEBUG_DIRECTORY;

struct IMAGE_DEBUG_DIRECTORY {
    dword Characteristics;
    dword TimeDateStamp;
    word MajorVersion;
    word MinorVersion;
    dword Type;
    dword SizeOfData;
    dword AddressOfRawData;
    dword PointerToRawData;
};

typedef struct IMAGE_FILE_HEADER IMAGE_FILE_HEADER, *PIMAGE_FILE_HEADER;

struct IMAGE_FILE_HEADER {
    word Machine; // 332
    word NumberOfSections;
    dword TimeDateStamp;
    dword PointerToSymbolTable;
    dword NumberOfSymbols;
    word SizeOfOptionalHeader;
    word Characteristics;
};

typedef struct IMAGE_NT_HEADERS32 IMAGE_NT_HEADERS32, *PIMAGE_NT_HEADERS32;

struct IMAGE_NT_HEADERS32 {
    char Signature[4];
    struct IMAGE_FILE_HEADER FileHeader;
    struct IMAGE_OPTIONAL_HEADER32 OptionalHeader;
};

typedef struct IMAGE_SECTION_HEADER IMAGE_SECTION_HEADER, *PIMAGE_SECTION_HEADER;

typedef union Misc Misc, *PMisc;

typedef enum SectionFlags {
    IMAGE_SCN_TYPE_NO_PAD=8,
    IMAGE_SCN_RESERVED_0001=16,
    IMAGE_SCN_CNT_CODE=32,
    IMAGE_SCN_CNT_INITIALIZED_DATA=64,
    IMAGE_SCN_CNT_UNINITIALIZED_DATA=128,
    IMAGE_SCN_LNK_OTHER=256,
    IMAGE_SCN_LNK_INFO=512,
    IMAGE_SCN_RESERVED_0040=1024,
    IMAGE_SCN_LNK_REMOVE=2048,
    IMAGE_SCN_LNK_COMDAT=4096,
    IMAGE_SCN_GPREL=32768,
    IMAGE_SCN_MEM_16BIT=131072,
    IMAGE_SCN_MEM_PURGEABLE=131072,
    IMAGE_SCN_MEM_LOCKED=262144,
    IMAGE_SCN_MEM_PRELOAD=524288,
    IMAGE_SCN_ALIGN_1BYTES=1048576,
    IMAGE_SCN_ALIGN_2BYTES=2097152,
    IMAGE_SCN_ALIGN_4BYTES=3145728,
    IMAGE_SCN_ALIGN_8BYTES=4194304,
    IMAGE_SCN_ALIGN_16BYTES=5242880,
    IMAGE_SCN_ALIGN_32BYTES=6291456,
    IMAGE_SCN_ALIGN_64BYTES=7340032,
    IMAGE_SCN_ALIGN_128BYTES=8388608,
    IMAGE_SCN_ALIGN_256BYTES=9437184,
    IMAGE_SCN_ALIGN_512BYTES=10485760,
    IMAGE_SCN_ALIGN_1024BYTES=11534336,
    IMAGE_SCN_ALIGN_2048BYTES=12582912,
    IMAGE_SCN_ALIGN_4096BYTES=13631488,
    IMAGE_SCN_ALIGN_8192BYTES=14680064,
    IMAGE_SCN_LNK_NRELOC_OVFL=16777216,
    IMAGE_SCN_MEM_DISCARDABLE=33554432,
    IMAGE_SCN_MEM_NOT_CACHED=67108864,
    IMAGE_SCN_MEM_NOT_PAGED=134217728,
    IMAGE_SCN_MEM_SHARED=268435456,
    IMAGE_SCN_MEM_EXECUTE=536870912,
    IMAGE_SCN_MEM_READ=1073741824,
    IMAGE_SCN_MEM_WRITE=2147483648
} SectionFlags;

union Misc {
    dword PhysicalAddress;
    dword VirtualSize;
};

struct IMAGE_SECTION_HEADER {
    char Name[8];
    union Misc Misc;
    ImageBaseOffset32 VirtualAddress;
    dword SizeOfRawData;
    dword PointerToRawData;
    dword PointerToRelocations;
    dword PointerToLinenumbers;
    word NumberOfRelocations;
    word NumberOfLinenumbers;
    enum SectionFlags Characteristics;
};

typedef struct IMAGE_COR20_HEADER IMAGE_COR20_HEADER, *PIMAGE_COR20_HEADER;

typedef struct CLI_METADATA_DIRECTORY CLI_METADATA_DIRECTORY, *PCLI_METADATA_DIRECTORY;

typedef enum COR20_Flags {
    COMIMAGE_FLAGS_ILONLY=1,
    COMIMAGE_FLAGS_32BITREQUIRED=2,
    COMIMAGE_FLAGS_IL_LIBRARY=4,
    COMIMAGE_FLAGS_STRONGNAMESIGNED=8,
    COMIMAGE_FLAGS_NATIVE_ENTRYPOINT=16,
    COMIMAGE_FLAGS_TRACKDEBUGDATA=65536
} COR20_Flags;

typedef struct IMAGE_DATA_DIRECTORY.conflict IMAGE_DATA_DIRECTORY.conflict, *PIMAGE_DATA_DIRECTORY.conflict;

struct CLI_METADATA_DIRECTORY {
    dword VirtualAddress;
    dword Size;
};

struct IMAGE_DATA_DIRECTORY.conflict {
    dword VirtualAddress;
    dword Size;
};

struct IMAGE_COR20_HEADER {
    dword cb; // Size of the structure
    word MajorRuntimeVersion; // Version of CLR Runtime
    word MinorRuntimeVersion;
    struct CLI_METADATA_DIRECTORY MetaData; // RVA and size of MetaData
    enum COR20_Flags Flags;
    dword EntryPointToken; // This is a metadata token if not a valid RVA
    struct IMAGE_DATA_DIRECTORY.conflict Resources;
    struct IMAGE_DATA_DIRECTORY.conflict StrongNameSignature;
    struct IMAGE_DATA_DIRECTORY.conflict CodeManagerTable; // Should be 0
    struct IMAGE_DATA_DIRECTORY.conflict VTableFixups;
    struct IMAGE_DATA_DIRECTORY.conflict ExportAddressTableJumps; // Should be 0
    struct IMAGE_DATA_DIRECTORY.conflict ManagedNativeHeader; // 0 unless this is a native image
};

typedef enum IMAGE_GUARD_FLAGS {
    IMAGE_GUARD_CF_INSTRUMENTED=256,
    IMAGE_GUARD_CFW_INSTRUMENTED=512,
    IMAGE_GUARD_CF_FUNCTION_TABLE_PRESENT=1024,
    IMAGE_GUARD_SECURITY_COOKIE_UNUSED=2048,
    IMAGE_GUARD_PROTECT_DELAYLOAD_IAT=4096,
    IMAGE_GUARD_DELAYLOAD_IAT_IN_ITS_OWN_SECTION=8192,
    IMAGE_GUARD_CF_EXPORT_SUPPRESSION_INFO_PRESENT=16384,
    IMAGE_GUARD_CF_ENABLE_EXPORT_SUPPRESSION=32768,
    IMAGE_GUARD_CF_LONGJUMP_TABLE_PRESENT=65536,
    IMAGE_GUARD_RF_INSTRUMENTED=131072,
    IMAGE_GUARD_RF_ENABLE=262144,
    IMAGE_GUARD_RF_STRICT=524288,
    IMAGE_GUARD_CF_FUNCTION_TABLE_SIZE_MASK_1=268435456,
    IMAGE_GUARD_CF_FUNCTION_TABLE_SIZE_MASK_2=536870912,
    IMAGE_GUARD_CF_FUNCTION_TABLE_SIZE_MASK_4=1073741824,
    IMAGE_GUARD_CF_FUNCTION_TABLE_SIZE_MASK_8=2147483648
} IMAGE_GUARD_FLAGS;

typedef struct IMAGE_LOAD_CONFIG_DIRECTORY32 IMAGE_LOAD_CONFIG_DIRECTORY32, *PIMAGE_LOAD_CONFIG_DIRECTORY32;

struct IMAGE_LOAD_CONFIG_DIRECTORY32 {
    dword Size;
    dword TimeDateStamp;
    word MajorVersion;
    word MinorVersion;
    dword GlobalFlagsClear;
    dword GlobalFlagsSet;
    dword CriticalSectionDefaultTimeout;
    dword DeCommitFreeBlockThreshold;
    dword DeCommitTotalFreeThreshold;
    pointer32 LockPrefixTable;
    dword MaximumAllocationSize;
    dword VirtualMemoryThreshold;
    dword ProcessHeapFlags;
    dword ProcessAffinityMask;
    word CsdVersion;
    word DependentLoadFlags;
    pointer32 EditList;
    pointer32 SecurityCookie;
    pointer32 SEHandlerTable;
    dword SEHandlerCount;
    pointer32 GuardCFCCheckFunctionPointer;
    pointer32 GuardCFDispatchFunctionPointer;
    pointer32 GuardCFFunctionTable;
    dword GuardCFFunctionCount;
    enum IMAGE_GUARD_FLAGS GuardFlags;
    struct IMAGE_LOAD_CONFIG_CODE_INTEGRITY CodeIntegrity;
    pointer32 GuardAddressTakenIatEntryTable;
    dword GuardAddressTakenIatEntryCount;
    pointer32 GuardLongJumpTargetTable;
    dword GuardLongJumpTargetCount;
    pointer32 DynamicValueRelocTable;
    pointer32 CHPEMetadataPointer;
    pointer32 GuardRFFailureRoutine;
    pointer32 GuardRFFailureRoutineFunctionPointer;
    dword DynamicValueRelocTableOffset;
    word DynamicValueRelocTableSection;
    word Reserved1;
    pointer32 GuardRFVerifyStackPointerFunctionPointer;
    dword HotPatchTableOffset;
    dword Reserved2;
    dword Reserved3;
};

typedef struct CLI_METADATA_HEADER CLI_METADATA_HEADER, *PCLI_METADATA_HEADER;

typedef struct CLI_Stream_Header_#~ CLI_Stream_Header_#~, *PCLI_Stream_Header_#~;

typedef struct CLI_Stream_Header_#Strings CLI_Stream_Header_#Strings, *PCLI_Stream_Header_#Strings;

typedef struct CLI_Stream_Header_#US CLI_Stream_Header_#US, *PCLI_Stream_Header_#US;

typedef struct CLI_Stream_Header_#GUID CLI_Stream_Header_#GUID, *PCLI_Stream_Header_#GUID;

typedef struct CLI_Stream_Header_#Blob CLI_Stream_Header_#Blob, *PCLI_Stream_Header_#Blob;

struct CLI_Stream_Header_#Blob {
    dword offset;
    dword size;
    char name[8];
};

struct CLI_Stream_Header_#GUID {
    dword offset;
    dword size;
    char name[8];
};

struct CLI_Stream_Header_#~ {
    dword offset;
    dword size;
    char name[4];
};

struct CLI_Stream_Header_#US {
    dword offset;
    dword size;
    char name[4];
};

struct CLI_Stream_Header_#Strings {
    dword offset;
    dword size;
    char name[12];
};

struct CLI_METADATA_HEADER {
    dword Signature; // must be 0x424a5342
    word MajorVersion;
    word MinorVersion;
    dword Reserved; // should be 0
    dword VersionLength;
    char Version[12];
    word Flags; // should be 0
    word StreamsCount; // number of stream headers to follow
    struct CLI_Stream_Header_#~ #~;
    struct CLI_Stream_Header_#Strings #Strings;
    struct CLI_Stream_Header_#US #US;
    struct CLI_Stream_Header_#GUID #GUID;
    struct CLI_Stream_Header_#Blob #Blob;
};

typedef struct ValueType.conflict ValueType.conflict, *PValueType.conflict;

typedef enum TypeCode {
    ELEMENT_TYPE_END=0,
    ELEMENT_TYPE_VOID=1,
    ELEMENT_TYPE_BOOLEAN=2,
    ELEMENT_TYPE_CHAR=3,
    ELEMENT_TYPE_I1=4,
    ELEMENT_TYPE_U1=5,
    ELEMENT_TYPE_I2=6,
    ELEMENT_TYPE_U2=7,
    ELEMENT_TYPE_I4=8,
    ELEMENT_TYPE_U4=9,
    ELEMENT_TYPE_I8=10,
    ELEMENT_TYPE_U8=11,
    ELEMENT_TYPE_R4=12,
    ELEMENT_TYPE_R8=13,
    ELEMENT_TYPE_STRING=14,
    ELEMENT_TYPE_PTR=15,
    ELEMENT_TYPE_BYREF=16,
    ELEMENT_TYPE_VALUETYPE=17,
    ELEMENT_TYPE_CLASS=18,
    ELEMENT_TYPE_VAR=19,
    ELEMENT_TYPE_ARRAY=20,
    ELEMENT_TYPE_GENERICINST=21,
    ELEMENT_TYPE_TYPEDBYREF=22,
    ELEMENT_TYPE_I=24,
    ELEMENT_TYPE_U=25,
    ELEMENT_TYPE_FNPTR=27,
    ELEMENT_TYPE_OBJECT=28,
    ELEMENT_TYPE_SZARRAY=29,
    ELEMENT_TYPE_MVAR=30,
    ELEMENT_TYPE_CMOD_REQD=31,
    ELEMENT_TYPE_CMOD_OPT=32,
    ELEMENT_TYPE_INTERNAL=33,
    ELEMENT_TYPE_MAX=34,
    ELEMENT_TYPE_MODIFIER=64,
    ELEMENT_TYPE_SENTINEL=65,
    ELEMENT_TYPE_PINNED=69
} TypeCode;

struct ValueType.conflict {
    enum TypeCode ValueType; // ValueType
    byte TypeDefOrRefEncoded; // TypeRef: Row 0xb
};

typedef struct ValueType ValueType, *PValueType;

struct ValueType {
    enum TypeCode ValueType; // ValueType
    byte TypeDefOrRefEncoded; // TypeRef: Row 0x9
};

typedef struct Class Class, *PClass;

struct Class {
    enum TypeCode Class; // Class
    byte Type; // TypeDefOrRefOrSpecEncoded
};

typedef struct SzArray SzArray, *PSzArray;

struct SzArray {
    enum TypeCode TypeCode; // SzArray
    enum TypeCode Type; // type or void
};

typedef struct Blob_MethodRefSig_77 Blob_MethodRefSig_77, *PBlob_MethodRefSig_77;

typedef struct MethodRefSig_77 MethodRefSig_77, *PMethodRefSig_77;

typedef struct Type_72020 Type_72020, *PType_72020;

typedef struct Type_72021 Type_72021, *PType_72021;

typedef struct Type_72023 Type_72023, *PType_72023;

typedef struct Type_72024 Type_72024, *PType_72024;

typedef struct Type_72025 Type_72025, *PType_72025;

typedef struct Type_72027 Type_72027, *PType_72027;

struct Type_72027 {
    enum TypeCode ELEMENT_TYPE_I4;
};

struct Type_72021 {
    struct SzArray ELEMENT_TYPE_SZARRAY;
};

struct Type_72025 {
    struct SzArray ELEMENT_TYPE_SZARRAY;
};

struct Type_72020 {
    enum TypeCode ELEMENT_TYPE_I4;
};

struct Type_72023 {
    enum TypeCode ELEMENT_TYPE_I4;
};

struct Type_72024 {
    enum TypeCode ELEMENT_TYPE_I4;
};

struct MethodRefSig_77 {
    byte Flags; // ORed VARARG/GENERIC/HASTHIS/EXPLICITTHIS
    byte ParamCount; // Number of parameter types to follow RetType
    struct Type_72020 RetType;
    struct Type_72021 Param0;
    struct Type_72023 Param1;
    struct Type_72024 Param2;
    struct Type_72025 Param3;
    struct Type_72027 Param4;
};

struct Blob_MethodRefSig_77 {
    byte Size; // coded integer - blob size
    struct MethodRefSig_77 MethodRefSig; // Type info for imported method return and params
};

typedef struct Blob_Generic_41 Blob_Generic_41, *PBlob_Generic_41;

struct Blob_Generic_41 {
    byte Size; // coded integer - blob size
    byte Generic[7]; // Undefined blob contents
};

typedef struct Blob_Generic_49 Blob_Generic_49, *PBlob_Generic_49;

struct Blob_Generic_49 {
    byte Size; // coded integer - blob size
    byte Generic[5]; // Undefined blob contents
};

typedef struct Blob_Generic_88 Blob_Generic_88, *PBlob_Generic_88;

struct Blob_Generic_88 {
    byte Size; // coded integer - blob size
    byte Generic[7]; // Undefined blob contents
};

typedef struct Blob_MethodRefSig_29 Blob_MethodRefSig_29, *PBlob_MethodRefSig_29;

typedef struct MethodRefSig_29 MethodRefSig_29, *PMethodRefSig_29;

typedef struct Type_71972 Type_71972, *PType_71972;

typedef struct Type_71973 Type_71973, *PType_71973;

typedef struct Type_71974 Type_71974, *PType_71974;

struct Type_71972 {
    enum TypeCode ELEMENT_TYPE_STRING;
};

struct Type_71974 {
    enum TypeCode ELEMENT_TYPE_STRING;
};

struct Type_71973 {
    enum TypeCode ELEMENT_TYPE_STRING;
};

struct MethodRefSig_29 {
    byte Flags; // ORed VARARG/GENERIC/HASTHIS/EXPLICITTHIS
    byte ParamCount; // Number of parameter types to follow RetType
    struct Type_71972 RetType;
    struct Type_71973 Param0;
    struct Type_71974 Param1;
};

struct Blob_MethodRefSig_29 {
    byte Size; // coded integer - blob size
    struct MethodRefSig_29 MethodRefSig; // Type info for imported method return and params
};

typedef struct Blob_MethodRefSig_69 Blob_MethodRefSig_69, *PBlob_MethodRefSig_69;

typedef struct MethodRefSig_69 MethodRefSig_69, *PMethodRefSig_69;

typedef struct Type_72012 Type_72012, *PType_72012;

typedef struct Type_72013 Type_72013, *PType_72013;

typedef struct Type_72015 Type_72015, *PType_72015;

typedef struct Type_72016 Type_72016, *PType_72016;

struct Type_72016 {
    enum TypeCode ELEMENT_TYPE_I4;
};

struct Type_72015 {
    enum TypeCode ELEMENT_TYPE_I4;
};

struct Type_72012 {
    enum TypeCode ELEMENT_TYPE_I4;
};

struct Type_72013 {
    struct SzArray ELEMENT_TYPE_SZARRAY;
};

struct MethodRefSig_69 {
    byte Flags; // ORed VARARG/GENERIC/HASTHIS/EXPLICITTHIS
    byte ParamCount; // Number of parameter types to follow RetType
    struct Type_72012 RetType;
    struct Type_72013 Param0;
    struct Type_72015 Param1;
    struct Type_72016 Param2;
};

struct Blob_MethodRefSig_69 {
    byte Size; // coded integer - blob size
    struct MethodRefSig_69 MethodRefSig; // Type info for imported method return and params
};

typedef struct Blob_MethodRefSig_24 Blob_MethodRefSig_24, *PBlob_MethodRefSig_24;

typedef struct MethodRefSig_24 MethodRefSig_24, *PMethodRefSig_24;

typedef struct Type_71967 Type_71967, *PType_71967;

struct Type_71967 {
    struct Class ELEMENT_TYPE_CLASS;
};

struct MethodRefSig_24 {
    byte Flags; // ORed VARARG/GENERIC/HASTHIS/EXPLICITTHIS
    byte ParamCount; // Number of parameter types to follow RetType
    struct Type_71967 RetType;
};

struct Blob_MethodRefSig_24 {
    byte Size; // coded integer - blob size
    struct MethodRefSig_24 MethodRefSig; // Type info for imported method return and params
};

typedef struct Blob_Generic_96 Blob_Generic_96, *PBlob_Generic_96;

struct Blob_Generic_96 {
    byte Size; // coded integer - blob size
    byte Generic[18]; // Undefined blob contents
};

typedef struct Blob_MethodRefSig_61 Blob_MethodRefSig_61, *PBlob_MethodRefSig_61;

typedef struct MethodRefSig_61 MethodRefSig_61, *PMethodRefSig_61;

typedef struct Type_72004 Type_72004, *PType_72004;

typedef struct Type_72005 Type_72005, *PType_72005;

typedef struct Type_72007 Type_72007, *PType_72007;

typedef struct Type_72008 Type_72008, *PType_72008;

struct Type_72008 {
    enum TypeCode ELEMENT_TYPE_I4;
};

struct Type_72007 {
    enum TypeCode ELEMENT_TYPE_I4;
};

struct Type_72005 {
    struct SzArray ELEMENT_TYPE_SZARRAY;
};

struct Type_72004 {
    enum TypeCode ELEMENT_TYPE_VOID;
};

struct MethodRefSig_61 {
    byte Flags; // ORed VARARG/GENERIC/HASTHIS/EXPLICITTHIS
    byte ParamCount; // Number of parameter types to follow RetType
    struct Type_72004 RetType;
    struct Type_72005 Param0;
    struct Type_72007 Param1;
    struct Type_72008 Param2;
};

struct Blob_MethodRefSig_61 {
    byte Size; // coded integer - blob size
    struct MethodRefSig_61 MethodRefSig; // Type info for imported method return and params
};

typedef struct Blob_Generic_15 Blob_Generic_15, *PBlob_Generic_15;

struct Blob_Generic_15 {
    byte Size; // coded integer - blob size
    byte Generic[3]; // Undefined blob contents
};

typedef struct Blob_Generic_10 Blob_Generic_10, *PBlob_Generic_10;

struct Blob_Generic_10 {
    byte Size; // coded integer - blob size
    byte Generic[4]; // Undefined blob contents
};

typedef struct Blob_Generic_55 Blob_Generic_55, *PBlob_Generic_55;

struct Blob_Generic_55 {
    byte Size; // coded integer - blob size
    byte Generic[5]; // Undefined blob contents
};

typedef struct Blob_Generic_19 Blob_Generic_19, *PBlob_Generic_19;

struct Blob_Generic_19 {
    byte Size; // coded integer - blob size
    byte Generic[4]; // Undefined blob contents
};

typedef struct Blob_MethodRefSig_19 Blob_MethodRefSig_19, *PBlob_MethodRefSig_19;

typedef struct MethodRefSig_19 MethodRefSig_19, *PMethodRefSig_19;

typedef struct Type_71962 Type_71962, *PType_71962;

struct Type_71962 {
    struct Class ELEMENT_TYPE_CLASS;
};

struct MethodRefSig_19 {
    byte Flags; // ORed VARARG/GENERIC/HASTHIS/EXPLICITTHIS
    byte ParamCount; // Number of parameter types to follow RetType
    struct Type_71962 RetType;
};

struct Blob_MethodRefSig_19 {
    byte Size; // coded integer - blob size
    struct MethodRefSig_19 MethodRefSig; // Type info for imported method return and params
};

typedef struct Blob_MethodRefSig_15 Blob_MethodRefSig_15, *PBlob_MethodRefSig_15;

typedef struct MethodRefSig_15 MethodRefSig_15, *PMethodRefSig_15;

typedef struct Type_71958 Type_71958, *PType_71958;

struct Type_71958 {
    enum TypeCode ELEMENT_TYPE_VOID;
};

struct MethodRefSig_15 {
    byte Flags; // ORed VARARG/GENERIC/HASTHIS/EXPLICITTHIS
    byte ParamCount; // Number of parameter types to follow RetType
    struct Type_71958 RetType;
};

struct Blob_MethodRefSig_15 {
    byte Size; // coded integer - blob size
    struct MethodRefSig_15 MethodRefSig; // Type info for imported method return and params
};

typedef struct Blob_Generic_61 Blob_Generic_61, *PBlob_Generic_61;

struct Blob_Generic_61 {
    byte Size; // coded integer - blob size
    byte Generic[7]; // Undefined blob contents
};

typedef struct Blob_MethodRefSig_55 Blob_MethodRefSig_55, *PBlob_MethodRefSig_55;

typedef struct MethodRefSig_55 MethodRefSig_55, *PMethodRefSig_55;

typedef struct Type_71998 Type_71998, *PType_71998;

typedef struct Type_71999 Type_71999, *PType_71999;

typedef struct Type_72000 Type_72000, *PType_72000;

struct Type_72000 {
    enum TypeCode ELEMENT_TYPE_I4;
};

struct Type_71998 {
    enum TypeCode ELEMENT_TYPE_I4;
};

struct Type_71999 {
    enum TypeCode ELEMENT_TYPE_I4;
};

struct MethodRefSig_55 {
    byte Flags; // ORed VARARG/GENERIC/HASTHIS/EXPLICITTHIS
    byte ParamCount; // Number of parameter types to follow RetType
    struct Type_71998 RetType;
    struct Type_71999 Param0;
    struct Type_72000 Param1;
};

struct Blob_MethodRefSig_55 {
    byte Size; // coded integer - blob size
    struct MethodRefSig_55 MethodRefSig; // Type info for imported method return and params
};

typedef struct Blob_Generic_69 Blob_Generic_69, *PBlob_Generic_69;

struct Blob_Generic_69 {
    byte Size; // coded integer - blob size
    byte Generic[7]; // Undefined blob contents
};

typedef struct Blob_Generic_24 Blob_Generic_24, *PBlob_Generic_24;

struct Blob_Generic_24 {
    byte Size; // coded integer - blob size
    byte Generic[4]; // Undefined blob contents
};

typedef struct Blob_Generic_29 Blob_Generic_29, *PBlob_Generic_29;

struct Blob_Generic_29 {
    byte Size; // coded integer - blob size
    byte Generic[5]; // Undefined blob contents
};

typedef struct Blob_LocalVarSig_96 Blob_LocalVarSig_96, *PBlob_LocalVarSig_96;

typedef struct LocalVarSig_96 LocalVarSig_96, *PLocalVarSig_96;

typedef struct Type_72039 Type_72039, *PType_72039;

typedef struct Type_72041 Type_72041, *PType_72041;

typedef struct Type_72043 Type_72043, *PType_72043;

typedef struct Type_72044 Type_72044, *PType_72044;

typedef struct Type_72046 Type_72046, *PType_72046;

typedef struct Type_72048 Type_72048, *PType_72048;

typedef struct Type_72049 Type_72049, *PType_72049;

typedef struct Type_72050 Type_72050, *PType_72050;

typedef struct Type_72051 Type_72051, *PType_72051;

typedef struct Type_72053 Type_72053, *PType_72053;

struct Type_72049 {
    enum TypeCode ELEMENT_TYPE_I4;
};

struct Type_72048 {
    enum TypeCode ELEMENT_TYPE_STRING;
};

struct Type_72039 {
    struct Class ELEMENT_TYPE_CLASS;
};

struct Type_72044 {
    struct SzArray ELEMENT_TYPE_SZARRAY;
};

struct Type_72046 {
    struct SzArray ELEMENT_TYPE_SZARRAY;
};

struct Type_72043 {
    enum TypeCode ELEMENT_TYPE_STRING;
};

struct Type_72051 {
    struct Class ELEMENT_TYPE_CLASS;
};

struct Type_72053 {
    struct Class ELEMENT_TYPE_CLASS;
};

struct Type_72041 {
    struct SzArray ELEMENT_TYPE_SZARRAY;
};

struct Type_72050 {
    enum TypeCode ELEMENT_TYPE_I4;
};

struct LocalVarSig_96 {
    byte LOCAL_SIG; // Magic (0x07)
    byte Count; // Number of types to follow
    struct Type_72039 Type;
    struct Type_72041 Type;
    struct Type_72043 Type;
    struct Type_72044 Type;
    struct Type_72046 Type;
    struct Type_72048 Type;
    struct Type_72049 Type;
    struct Type_72050 Type;
    struct Type_72051 Type;
    struct Type_72053 Type;
};

struct Blob_LocalVarSig_96 {
    byte Size; // coded integer - blob size
    struct LocalVarSig_96 LocalVarSig; // Contains signature for function locals
};

typedef struct Blob_MethodRefSig_49 Blob_MethodRefSig_49, *PBlob_MethodRefSig_49;

typedef struct MethodRefSig_49 MethodRefSig_49, *PMethodRefSig_49;

typedef struct Type_71992 Type_71992, *PType_71992;

typedef struct Type_71993 Type_71993, *PType_71993;

struct Type_71993 {
    struct ValueType.conflict ELEMENT_TYPE_VALUETYPE;
};

struct Type_71992 {
    enum TypeCode ELEMENT_TYPE_VOID;
};

struct MethodRefSig_49 {
    byte Flags; // ORed VARARG/GENERIC/HASTHIS/EXPLICITTHIS
    byte ParamCount; // Number of parameter types to follow RetType
    struct Type_71992 RetType;
    struct Type_71993 Param0;
};

struct Blob_MethodRefSig_49 {
    byte Size; // coded integer - blob size
    struct MethodRefSig_49 MethodRefSig; // Type info for imported method return and params
};

typedef struct Blob_MethodRefSig_88 Blob_MethodRefSig_88, *PBlob_MethodRefSig_88;

typedef struct MethodRefSig_88 MethodRefSig_88, *PMethodRefSig_88;

typedef struct Type_72031 Type_72031, *PType_72031;

typedef struct Type_72032 Type_72032, *PType_72032;

typedef struct Type_72034 Type_72034, *PType_72034;

typedef struct Type_72035 Type_72035, *PType_72035;

struct Type_72032 {
    struct SzArray ELEMENT_TYPE_SZARRAY;
};

struct Type_72034 {
    enum TypeCode ELEMENT_TYPE_I4;
};

struct Type_72031 {
    enum TypeCode ELEMENT_TYPE_VOID;
};

struct Type_72035 {
    enum TypeCode ELEMENT_TYPE_I4;
};

struct MethodRefSig_88 {
    byte Flags; // ORed VARARG/GENERIC/HASTHIS/EXPLICITTHIS
    byte ParamCount; // Number of parameter types to follow RetType
    struct Type_72031 RetType;
    struct Type_72032 Param0;
    struct Type_72034 Param1;
    struct Type_72035 Param2;
};

struct Blob_MethodRefSig_88 {
    byte Size; // coded integer - blob size
    struct MethodRefSig_88 MethodRefSig; // Type info for imported method return and params
};

typedef struct Blob_MethodRefSig_41 Blob_MethodRefSig_41, *PBlob_MethodRefSig_41;

typedef struct MethodRefSig_41 MethodRefSig_41, *PMethodRefSig_41;

typedef struct Type_71984 Type_71984, *PType_71984;

typedef struct Type_71985 Type_71985, *PType_71985;

typedef struct Type_71986 Type_71986, *PType_71986;

typedef struct Type_71987 Type_71987, *PType_71987;

struct Type_71985 {
    enum TypeCode ELEMENT_TYPE_STRING;
};

struct Type_71984 {
    enum TypeCode ELEMENT_TYPE_VOID;
};

struct Type_71987 {
    struct ValueType ELEMENT_TYPE_VALUETYPE;
};

struct Type_71986 {
    enum TypeCode ELEMENT_TYPE_STRING;
};

struct MethodRefSig_41 {
    byte Flags; // ORed VARARG/GENERIC/HASTHIS/EXPLICITTHIS
    byte ParamCount; // Number of parameter types to follow RetType
    struct Type_71984 RetType;
    struct Type_71985 Param0;
    struct Type_71986 Param1;
    struct Type_71987 Param2;
};

struct Blob_MethodRefSig_41 {
    byte Size; // coded integer - blob size
    struct MethodRefSig_41 MethodRefSig; // Type info for imported method return and params
};

typedef struct Blob_Generic_35 Blob_Generic_35, *PBlob_Generic_35;

struct Blob_Generic_35 {
    byte Size; // coded integer - blob size
    byte Generic[5]; // Undefined blob contents
};

typedef struct Blob_MethodDefSig_10 Blob_MethodDefSig_10, *PBlob_MethodDefSig_10;

typedef struct MethodDefSig_10 MethodDefSig_10, *PMethodDefSig_10;

typedef struct Type_71953 Type_71953, *PType_71953;

typedef struct Type_71954 Type_71954, *PType_71954;

struct Type_71953 {
    enum TypeCode ELEMENT_TYPE_STRING;
};

struct Type_71954 {
    enum TypeCode ELEMENT_TYPE_STRING;
};

struct MethodDefSig_10 {
    byte Flags; // ORed VARARG/GENERIC/HASTHIS/EXPLICITTHIS
    byte Count; // Number of parameter types to follow RetType
    struct Type_71953 RetType;
    struct Type_71954 Param0;
};

struct Blob_MethodDefSig_10 {
    byte Size; // coded integer - blob size
    struct MethodDefSig_10 MethodDefSig; // Type info for method return and params
};

typedef struct Blob_Generic_77 Blob_Generic_77, *PBlob_Generic_77;

struct Blob_Generic_77 {
    byte Size; // coded integer - blob size
    byte Generic[10]; // Undefined blob contents
};

typedef struct Blob_MethodDefSig_15 Blob_MethodDefSig_15, *PBlob_MethodDefSig_15;

typedef struct MethodDefSig_15 MethodDefSig_15, *PMethodDefSig_15;

struct MethodDefSig_15 {
    byte Flags; // ORed VARARG/GENERIC/HASTHIS/EXPLICITTHIS
    byte Count; // Number of parameter types to follow RetType
    struct Type_71958 RetType;
};

struct Blob_MethodDefSig_15 {
    byte Size; // coded integer - blob size
    struct MethodDefSig_15 MethodDefSig; // Type info for method return and params
};

typedef struct Blob_Generic_1 Blob_Generic_1, *PBlob_Generic_1;

struct Blob_Generic_1 {
    byte Size; // coded integer - blob size
    byte Generic[8]; // Undefined blob contents
};

typedef struct Blob_MethodRefSig_35 Blob_MethodRefSig_35, *PBlob_MethodRefSig_35;

typedef struct MethodRefSig_35 MethodRefSig_35, *PMethodRefSig_35;

typedef struct Type_71978 Type_71978, *PType_71978;

typedef struct Type_71980 Type_71980, *PType_71980;

struct Type_71980 {
    enum TypeCode ELEMENT_TYPE_STRING;
};

struct Type_71978 {
    struct SzArray ELEMENT_TYPE_SZARRAY;
};

struct MethodRefSig_35 {
    byte Flags; // ORed VARARG/GENERIC/HASTHIS/EXPLICITTHIS
    byte ParamCount; // Number of parameter types to follow RetType
    struct Type_71978 RetType;
    struct Type_71980 Param0;
};

struct Blob_MethodRefSig_35 {
    byte Size; // coded integer - blob size
    struct MethodRefSig_35 MethodRefSig; // Type info for imported method return and params
};

typedef struct ParamRow ParamRow, *PParamRow;

typedef enum ParamAttributes {
    In=1,
    Out=2,
    Optional=16,
    HasDefault=4096,
    HasFieldMarshal=8192,
    Unused=53216
} ParamAttributes;

struct ParamRow {
    enum ParamAttributes Flags; // bitmask of type ParamAttributes
    word Sequence; // constant
    word Name; // index into String heap
};

typedef struct AssemblyRef Row AssemblyRef Row, *PAssemblyRef Row;

typedef enum AssemblyFlags {
    PublicKey=1,
    Retargetable=256,
    DisableJITcompileOptimizer=16384,
    EnableJITcompileTracking=32768
} AssemblyFlags;

struct AssemblyRef Row {
    word MajorVersion;
    word MinorVersion;
    word BuildNumber;
    word RevisionNumber;
    enum AssemblyFlags Flags; // Bitmask of type AssemblyFlags
    word PublicKeyOrToken; // Public Key or token identifying the author of the assembly.
    word Name; // index into String heap
    word Culture; // index into String heap
    word HashValue; // index into Blob heap
};

typedef struct TypeRef Row TypeRef Row, *PTypeRef Row;

struct TypeRef Row {
    word ResolutionScope;
    word TypeName;
    word TypeNamespace;
};

typedef struct TypeDef Row TypeDef Row, *PTypeDef Row;

typedef enum TypeAttributes {
    Visibility_NotPublic=0,
    Visibility_Public=1,
    Visibility_NestedPublic=2,
    Visibility_NestedPrivate=3,
    Visibility_NestedFamily=4,
    Visibility_NestedAssembly=5,
    Visibility_NestedFamANDAssem=6,
    Visibility_NestedFamORAssem=7,
    SequentialLayout=8,
    ExplicitLayout=16,
    Interface=32,
    Abstract=128,
    Sealed=256,
    SpecialName=1024,
    RTSpecialName=2048,
    Import=4096,
    Serializable=8192,
    UnicodeClass=65536,
    AutoClass=131072,
    CustomFormatClass=196608,
    HasSecurity=262144,
    BeforeFieldInit=1048576,
    IsTypeForwarder=2097152,
    CustomStringFormatMask=12582912
} TypeAttributes;

struct TypeDef Row {
    enum TypeAttributes Flags; // see CorTypeAttr
    word TypeName; // index into String heap
    word TypeNamespace; // index into String heap
    word Extends; // index: coded TypeDefOrRef
    word FieldList; // index into Field table
    word MethodList; // index into MethodDef table
};

typedef struct StandAloneSig Row StandAloneSig Row, *PStandAloneSig Row;

struct StandAloneSig Row {
    word Signature;
};

typedef struct MethodDef Row MethodDef Row, *PMethodDef Row;

typedef enum MethodImplAttributes {
    CodeType_IL=0,
    CodeType_Native=1,
    CodeType_OPTIL=2,
    CodeType_Runtime=3,
    Unmanaged=4,
    NoInlining=8,
    ForwardRef=16,
    Synchronized=32,
    NoOptimization=64,
    PreserveSig=128,
    InternalCall=4096,
    MaxMethodImplVal=65535
} MethodImplAttributes;

typedef enum MethodAttributes {
    MAccess_CompilerControlled=0,
    MAccess_Private=1,
    MAccess_FamANDAssem=2,
    MAccess_Assem=3,
    MAccess_Family=4,
    MAccess_FamORAssem=5,
    MAccess_Public=6,
    UnmanagedExport=8,
    Static=16,
    Final=32,
    Virtual=64,
    HideBySig=128,
    VtableLayout_NewSlot=256,
    Strict=512,
    Abstract=1024,
    SpecialName=2048,
    RTSpecialName=4096,
    PInvokeImpl=8192,
    HasSecurity=16384,
    RequireSecObject=32768
} MethodAttributes;

struct MethodDef Row {
    dword RVA;
    enum MethodImplAttributes ImplFlags; // Bitmask of type MethodImplAttributes
    enum MethodAttributes Flags; // Bitmask of type MethodAttribute
    word Name; // index into String heap
    word Signature; // index into Blob heap
    word ParamList; // index into Param table
};

typedef struct MemberRef Row MemberRef Row, *PMemberRef Row;

struct MemberRef Row {
    word Class; // index-MemberRefParent coded
    word Name; // index into String heap
    word Signature; // index into Blob heap
};

typedef struct Assembly Table Assembly Table, *PAssembly Table;

typedef enum AssemblyHash {
    None=0,
    Reserved (MD5)=32771,
    SHA1=32772
} AssemblyHash;

struct Assembly Table {
    enum AssemblyHash HashAlg; // Type of hash present
    word MajorVersion;
    word MinorVersion;
    word BuildNumber;
    word RevisionNumber;
    enum AssemblyFlags Flags; // Bitmask of type AssemblyFlags
    word PublicKey; // index into Blob heap
    word Name; // index into String heap
    word Culture; // index into String heap
};

typedef struct Module Row Module Row, *PModule Row;

struct Module Row {
    word Generation; // reserved, shall be 0
    word Name; // index into String heap
    word MvId; // used to distinguish between versions of same module
    word EncId; // reserved, shall be 0
    word EncBaseId; // reserved, shall be 0
};

typedef struct #US #US, *P#US;

struct #US {
    byte Reserved; // Always 0
    byte Next string size;
    byte Extra byte; // 0x01 if string contains non-ASCII
    byte Next string size;
    wchar16 [3][1];
    byte Extra byte; // 0x01 if string contains non-ASCII
    byte Next string size;
    wchar16 [7][1];
    byte Extra byte; // 0x01 if string contains non-ASCII
    byte Next string size;
    wchar16 [b][7];
    byte Extra byte; // 0x01 if string contains non-ASCII
};

typedef struct #GUID #GUID, *P#GUID;

struct #GUID {
    GUID [0];
};

typedef struct #Strings #Strings, *P#Strings;

struct #Strings {
    char [0][1];
    char [1][9];
    char [a][5];
    char [f][8];
    char [17][9];
    char [20][12];
    char [2c][7];
    char [33][7];
    char [3a][8];
    char [42][12];
    char [4e][13];
    char [5b][22];
    char [71][16];
    char [81][9];
    char [8a][5];
    char [8f][5];
    char [94][7];
    char [9b][14];
    char [a9][11];
    char [b4][21];
    char [c9][5];
    char [ce][7];
    char [d5][10];
    char [df][12];
    char [eb][8];
    char [f3][9];
    char [fc][6];
    char [102][9];
    char [10b][11];
    char [116][7];
    char [11d][9];
    char [126][8];
    char [12e][13];
    char [13b][4];
    char [13f][6];
    char [145][5];
    char [14a][9];
    char [153][8];
    char [15b][12];
    char [167][16];
    char [177][1];
};

typedef struct #~ #~, *P#~;

struct #~ {
    dword Reserved; // Always 0
    byte MajorVersion;
    byte MinorVersion;
    byte HeapSizes; // Bit vector for heap sizes
    byte Reserved; // Always 1
    qword Valid; // Bit vector of present tables
    qword Sorted; // Bit vector of sorted tables
    dword Rows[9]; // # of rows for each corresponding present table
    struct Module Row Module; // CLI Metadata Table: Module
    struct TypeRef Row TypeRef[14]; // CLI Metadata Table: TypeRef
    struct TypeDef Row TypeDef[2]; // CLI Metadata Table: TypeDef
    struct MethodDef Row MethodDef[2]; // CLI Metadata Table: MethodDef
    struct ParamRow Param[1]; // CLI Metadata Table: Param
    struct MemberRef Row MemberRef[15]; // CLI Metadata Table: MemberRef
    struct StandAloneSig Row StandAloneSig[1]; // CLI Metadata Table: StandAloneSig
    struct Assembly Table Assembly; // CLI Metadata Table: Assembly
    struct AssemblyRef Row AssemblyRef[2]; // CLI Metadata Table: AssemblyRef
};

typedef struct #Blob #Blob, *P#Blob;

struct #Blob {
    byte Reserved; // Always 0
    struct Blob_Generic_1 [1];
    struct Blob_MethodDefSig_10 MethodDefSig_10; // Type info for method return and params
    struct Blob_MethodRefSig_15 MethodRefSig_15; // Type info for imported method return and params
    struct Blob_MethodRefSig_19 MethodRefSig_19; // Type info for imported method return and params
    struct Blob_MethodRefSig_24 MethodRefSig_24; // Type info for imported method return and params
    struct Blob_MethodRefSig_29 MethodRefSig_29; // Type info for imported method return and params
    struct Blob_MethodRefSig_35 MethodRefSig_35; // Type info for imported method return and params
    struct Blob_MethodRefSig_41 MethodRefSig_41; // Type info for imported method return and params
    struct Blob_MethodRefSig_49 MethodRefSig_49; // Type info for imported method return and params
    struct Blob_MethodRefSig_55 MethodRefSig_55; // Type info for imported method return and params
    struct Blob_MethodRefSig_61 MethodRefSig_61; // Type info for imported method return and params
    struct Blob_MethodRefSig_69 MethodRefSig_69; // Type info for imported method return and params
    struct Blob_MethodRefSig_77 MethodRefSig_77; // Type info for imported method return and params
    struct Blob_MethodRefSig_88 MethodRefSig_88; // Type info for imported method return and params
    struct Blob_LocalVarSig_96 LocalVarSig_96; // Contains signature for function locals
};

typedef struct MethodDefHdr_Fat MethodDefHdr_Fat, *PMethodDefHdr_Fat;

struct MethodDefHdr_Fat {
    word Size+Flags; // L.S. Bits 0:3 Size of hdr in bytes, Bits 4:15 Flags
    word MaxStack; // Maximum number of items on the operand stack
    dword CodeSize; // Size of actual method body in bytes
    dword LocalVarSigTok; // Signature for the local variables of the method. 0 means no locals. References standalone signature in Metadata tables, which references #Blob heap.
};

typedef struct <lambda_3e16ef9562a7dcce91392c22ab16ea36> <lambda_3e16ef9562a7dcce91392c22ab16ea36>, *P<lambda_3e16ef9562a7dcce91392c22ab16ea36>;

struct <lambda_3e16ef9562a7dcce91392c22ab16ea36> { // PlaceHolder Structure
};

typedef struct <lambda_2cc53f568c5a2bb6f192f930a45d44ea> <lambda_2cc53f568c5a2bb6f192f930a45d44ea>, *P<lambda_2cc53f568c5a2bb6f192f930a45d44ea>;

struct <lambda_2cc53f568c5a2bb6f192f930a45d44ea> { // PlaceHolder Structure
};

typedef struct EHExceptionRecord EHExceptionRecord, *PEHExceptionRecord;

struct EHExceptionRecord { // PlaceHolder Structure
};

typedef struct <lambda_c2ffc0b7726aa6be21d5f0026187e748> <lambda_c2ffc0b7726aa6be21d5f0026187e748>, *P<lambda_c2ffc0b7726aa6be21d5f0026187e748>;

struct <lambda_c2ffc0b7726aa6be21d5f0026187e748> { // PlaceHolder Structure
};

typedef struct <lambda_b8d4b9c228a6ecc3f80208dbb4b4a104> <lambda_b8d4b9c228a6ecc3f80208dbb4b4a104>, *P<lambda_b8d4b9c228a6ecc3f80208dbb4b4a104>;

struct <lambda_b8d4b9c228a6ecc3f80208dbb4b4a104> { // PlaceHolder Structure
};

typedef struct __crt_signal_action_t __crt_signal_action_t, *P__crt_signal_action_t;

struct __crt_signal_action_t { // PlaceHolder Structure
};

typedef struct __crt_locale_data __crt_locale_data, *P__crt_locale_data;

struct __crt_locale_data { // PlaceHolder Structure
};

typedef struct <lambda_fb385d3da700c9147fc39e65dd577a8c> <lambda_fb385d3da700c9147fc39e65dd577a8c>, *P<lambda_fb385d3da700c9147fc39e65dd577a8c>;

struct <lambda_fb385d3da700c9147fc39e65dd577a8c> { // PlaceHolder Structure
};

typedef struct <lambda_a7e850c220f1c8d1e6efeecdedd162c6> <lambda_a7e850c220f1c8d1e6efeecdedd162c6>, *P<lambda_a7e850c220f1c8d1e6efeecdedd162c6>;

struct <lambda_a7e850c220f1c8d1e6efeecdedd162c6> { // PlaceHolder Structure
};

typedef struct <lambda_ab61a845afdef5b7c387490eaf3616ee> <lambda_ab61a845afdef5b7c387490eaf3616ee>, *P<lambda_ab61a845afdef5b7c387490eaf3616ee>;

struct <lambda_ab61a845afdef5b7c387490eaf3616ee> { // PlaceHolder Structure
};

typedef struct <lambda_62f6974d9771e494a5ea317cc32e971c> <lambda_62f6974d9771e494a5ea317cc32e971c>, *P<lambda_62f6974d9771e494a5ea317cc32e971c>;

struct <lambda_62f6974d9771e494a5ea317cc32e971c> { // PlaceHolder Structure
};

typedef struct <lambda_207f2d024fc103971653565357d6cd41> <lambda_207f2d024fc103971653565357d6cd41>, *P<lambda_207f2d024fc103971653565357d6cd41>;

struct <lambda_207f2d024fc103971653565357d6cd41> { // PlaceHolder Structure
};

typedef struct <lambda_f03950bc5685219e0bcd2087efbe011e> <lambda_f03950bc5685219e0bcd2087efbe011e>, *P<lambda_f03950bc5685219e0bcd2087efbe011e>;

struct <lambda_f03950bc5685219e0bcd2087efbe011e> { // PlaceHolder Structure
};

typedef struct <lambda_ae742caa10f662c28703da3d2ea5e57e> <lambda_ae742caa10f662c28703da3d2ea5e57e>, *P<lambda_ae742caa10f662c28703da3d2ea5e57e>;

struct <lambda_ae742caa10f662c28703da3d2ea5e57e> { // PlaceHolder Structure
};

typedef struct <lambda_ceb1ee4838e85a9d631eb091e2fbe199> <lambda_ceb1ee4838e85a9d631eb091e2fbe199>, *P<lambda_ceb1ee4838e85a9d631eb091e2fbe199>;

struct <lambda_ceb1ee4838e85a9d631eb091e2fbe199> { // PlaceHolder Structure
};

typedef struct <lambda_6affb1475c98b40b75cdec977db92e3c> <lambda_6affb1475c98b40b75cdec977db92e3c>, *P<lambda_6affb1475c98b40b75cdec977db92e3c>;

struct <lambda_6affb1475c98b40b75cdec977db92e3c> { // PlaceHolder Structure
};

typedef struct __crt_seh_guarded_call<void> __crt_seh_guarded_call<void>, *P__crt_seh_guarded_call<void>;

struct __crt_seh_guarded_call<void> { // PlaceHolder Structure
};

typedef struct <lambda_38edbb1296d33220d7e4dd0ed76b244a> <lambda_38edbb1296d33220d7e4dd0ed76b244a>, *P<lambda_38edbb1296d33220d7e4dd0ed76b244a>;

struct <lambda_38edbb1296d33220d7e4dd0ed76b244a> { // PlaceHolder Structure
};

typedef struct __crt_win32_buffer<wchar_t,struct___crt_win32_buffer_internal_dynamic_resizing> __crt_win32_buffer<wchar_t,struct___crt_win32_buffer_internal_dynamic_resizing>, *P__crt_win32_buffer<wchar_t,struct___crt_win32_buffer_internal_dynamic_resizing>;

struct __crt_win32_buffer<wchar_t,struct___crt_win32_buffer_internal_dynamic_resizing> { // PlaceHolder Structure
};

typedef struct <lambda_15ade71b0218206bbe3333a0c9b79046> <lambda_15ade71b0218206bbe3333a0c9b79046>, *P<lambda_15ade71b0218206bbe3333a0c9b79046>;

struct <lambda_15ade71b0218206bbe3333a0c9b79046> { // PlaceHolder Structure
};

typedef struct __crt_win32_buffer_empty_debug_info __crt_win32_buffer_empty_debug_info, *P__crt_win32_buffer_empty_debug_info;

struct __crt_win32_buffer_empty_debug_info { // PlaceHolder Structure
};

typedef struct _s_CatchableType _s_CatchableType, *P_s_CatchableType;

struct _s_CatchableType { // PlaceHolder Structure
};

typedef struct <lambda_44731a7d0e6d81c3e6aa82d741081786> <lambda_44731a7d0e6d81c3e6aa82d741081786>, *P<lambda_44731a7d0e6d81c3e6aa82d741081786>;

struct <lambda_44731a7d0e6d81c3e6aa82d741081786> { // PlaceHolder Structure
};

typedef struct <lambda_4b292cb8dd18144e164572427af410ab> <lambda_4b292cb8dd18144e164572427af410ab>, *P<lambda_4b292cb8dd18144e164572427af410ab>;

struct <lambda_4b292cb8dd18144e164572427af410ab> { // PlaceHolder Structure
};

typedef struct __crt_stdio_stream __crt_stdio_stream, *P__crt_stdio_stream;

struct __crt_stdio_stream { // PlaceHolder Structure
};

typedef struct <lambda_69a2805e680e0e292e8ba93315fe43a8> <lambda_69a2805e680e0e292e8ba93315fe43a8>, *P<lambda_69a2805e680e0e292e8ba93315fe43a8>;

struct <lambda_69a2805e680e0e292e8ba93315fe43a8> { // PlaceHolder Structure
};

typedef struct __crt_multibyte_data __crt_multibyte_data, *P__crt_multibyte_data;

struct __crt_multibyte_data { // PlaceHolder Structure
};

typedef struct void_(__cdecl**)(int) void_(__cdecl**)(int), *Pvoid_(__cdecl**)(int);

struct void_(__cdecl**)(int) { // PlaceHolder Structure
};

typedef struct __crt_seh_guarded_call<int> __crt_seh_guarded_call<int>, *P__crt_seh_guarded_call<int>;

struct __crt_seh_guarded_call<int> { // PlaceHolder Structure
};

typedef struct <lambda_da44e0f8b0f19ba52fefafb335991732> <lambda_da44e0f8b0f19ba52fefafb335991732>, *P<lambda_da44e0f8b0f19ba52fefafb335991732>;

struct <lambda_da44e0f8b0f19ba52fefafb335991732> { // PlaceHolder Structure
};

typedef struct <lambda_5ce1d447e08cb34b2473517608e21441> <lambda_5ce1d447e08cb34b2473517608e21441>, *P<lambda_5ce1d447e08cb34b2473517608e21441>;

struct <lambda_5ce1d447e08cb34b2473517608e21441> { // PlaceHolder Structure
};

typedef struct <lambda_af42a3ee9806e9a7305d451646e05244> <lambda_af42a3ee9806e9a7305d451646e05244>, *P<lambda_af42a3ee9806e9a7305d451646e05244>;

struct <lambda_af42a3ee9806e9a7305d451646e05244> { // PlaceHolder Structure
};

typedef struct __acrt_ptd __acrt_ptd, *P__acrt_ptd;

struct __acrt_ptd { // PlaceHolder Structure
};

typedef struct <lambda_03fcd07e894ec930e3f35da366ca99d6> <lambda_03fcd07e894ec930e3f35da366ca99d6>, *P<lambda_03fcd07e894ec930e3f35da366ca99d6>;

struct <lambda_03fcd07e894ec930e3f35da366ca99d6> { // PlaceHolder Structure
};

typedef struct __crt_seh_guarded_call<void_(__cdecl*)(int)> __crt_seh_guarded_call<void_(__cdecl*)(int)>, *P__crt_seh_guarded_call<void_(__cdecl*)(int)>;

struct __crt_seh_guarded_call<void_(__cdecl*)(int)> { // PlaceHolder Structure
};

typedef struct <lambda_e25ca0880e6ef98be67edffd8c599615> <lambda_e25ca0880e6ef98be67edffd8c599615>, *P<lambda_e25ca0880e6ef98be67edffd8c599615>;

struct <lambda_e25ca0880e6ef98be67edffd8c599615> { // PlaceHolder Structure
};

typedef struct EHRegistrationNode EHRegistrationNode, *PEHRegistrationNode;

struct EHRegistrationNode { // PlaceHolder Structure
};

typedef struct <lambda_cd08b5d6af4937fe54fc07d0c9bf6b37> <lambda_cd08b5d6af4937fe54fc07d0c9bf6b37>, *P<lambda_cd08b5d6af4937fe54fc07d0c9bf6b37>;

struct <lambda_cd08b5d6af4937fe54fc07d0c9bf6b37> { // PlaceHolder Structure
};

typedef struct <lambda_e5124f882df8998aaf41531e079ba474> <lambda_e5124f882df8998aaf41531e079ba474>, *P<lambda_e5124f882df8998aaf41531e079ba474>;

struct <lambda_e5124f882df8998aaf41531e079ba474> { // PlaceHolder Structure
};

typedef struct <lambda_cbab9ec6f41b0180b23cc171c22676b0> <lambda_cbab9ec6f41b0180b23cc171c22676b0>, *P<lambda_cbab9ec6f41b0180b23cc171c22676b0>;

struct <lambda_cbab9ec6f41b0180b23cc171c22676b0> { // PlaceHolder Structure
};

typedef struct <lambda_46720907175c18b6c9d2717bc0d2d362> <lambda_46720907175c18b6c9d2717bc0d2d362>, *P<lambda_46720907175c18b6c9d2717bc0d2d362>;

struct <lambda_46720907175c18b6c9d2717bc0d2d362> { // PlaceHolder Structure
};

typedef enum _EXCEPTION_DISPOSITION {
} _EXCEPTION_DISPOSITION;

typedef struct <lambda_9048902d66e8d99359bc9897bbb930a8> <lambda_9048902d66e8d99359bc9897bbb930a8>, *P<lambda_9048902d66e8d99359bc9897bbb930a8>;

struct <lambda_9048902d66e8d99359bc9897bbb930a8> { // PlaceHolder Structure
};


// WARNING! conflicting data type names: /Demangler/wchar_t - /wchar_t

typedef struct <lambda_608742c3c92a14382c1684fc64f96c88> <lambda_608742c3c92a14382c1684fc64f96c88>, *P<lambda_608742c3c92a14382c1684fc64f96c88>;

struct <lambda_608742c3c92a14382c1684fc64f96c88> { // PlaceHolder Structure
};

typedef enum module_id {
} module_id;

typedef struct pair<class___FrameHandler3::TryBlockMap::iterator,class___FrameHandler3::TryBlockMap::iterator> pair<class___FrameHandler3::TryBlockMap::iterator,class___FrameHandler3::TryBlockMap::iterator>, *Ppair<class___FrameHandler3::TryBlockMap::iterator,class___FrameHandler3::TryBlockMap::iterator>;

struct pair<class___FrameHandler3::TryBlockMap::iterator,class___FrameHandler3::TryBlockMap::iterator> { // PlaceHolder Structure
};

typedef struct TryBlockMap TryBlockMap, *PTryBlockMap;

struct TryBlockMap { // PlaceHolder Structure
};

typedef struct argument_list<char> argument_list<char>, *Pargument_list<char>;

struct argument_list<char> { // PlaceHolder Structure
};

typedef enum function_id {
} function_id;

typedef struct write_result write_result, *Pwrite_result;

struct write_result { // PlaceHolder Structure
};




bool __cdecl check_password(undefined4 param_1,undefined4 *param_2)

{
    int password_ok;
    undefined *puVar1;
    uint local_40c [0x102];
    
    FUN_100011ef(local_40c,&first_scramble,0x8);
    FUN_10001187(local_40c,&second_scramble,0x9);
    password_ok = (*lstrcmpA_f)(&second_scramble,param_1);
    if (password_ok == 0x0) {
        puVar1 = &flag;
        FUN_10001187(local_40c,&flag,0x1f);
        *param_2 = 0x1f;
    }
    else {
        *param_2 = 0x15;
        puVar1 = (undefined *)xor_with_17(&auth_failed,(int)&global_buffer2);
    }
    (*DAT_10015a20)(param_1,puVar1);
    return password_ok == 0x0;
}



undefined4 pipe_communicate(void)

{
    int hFile;
    int iVar1;
    undefined4 uVar2;
    undefined4 uVar3;
    undefined4 uVar4;
    undefined4 uVar5;
    undefined4 uVar6;
    undefined4 uVar7;
    undefined4 uVar8;
    undefined lpBuffer [0x40];
    int lpNumberOfBytesWritten;
    undefined4 nNumberOfBytesToWrite;
    int local_8;
    
    _memset(lpBuffer,0x0,0x40);
    (*GetProcessHeap_f)();
    uVar8 = 0x0;
    uVar7 = 0x0;
    uVar6 = 0x40;
    uVar5 = 0x40;
    uVar4 = 0xff;
    uVar3 = 0x6;
    uVar2 = 0x3;
    hFile = xor_with_17((byte *)pipe_name,(int)&global_buffer2);
    hFile = (*CreateNamedPipeA_f)(hFile,uVar2,uVar3,uVar4,uVar5,uVar6,uVar7,uVar8);
    if (hFile != -0x1) {
        iVar1 = (*ConnectNamedPipe_f)(hFile,0x0);
        if (iVar1 == 0x0) {
            (*GetLastError_f)();
        }
        iVar1 = (*ReadFile_f)(hFile,lpBuffer,0x40,&local_8,0x0);
        if ((iVar1 == 0x0) || (local_8 == 0x0)) {
            (*GetLastError_f)();
        }
        else {
            (*FlushFileBuffers_f)(hFile);
            lpBuffer[local_8] = 0x0;
            check_password(lpBuffer,&nNumberOfBytesToWrite);
            (*WriteFile_f)(hFile,lpBuffer,nNumberOfBytesToWrite,&lpNumberOfBytesWritten,0x0);
        }
        (*FlushFileBuffers_f)(hFile);
        (*DisconnectNamedPipe_f)(hFile);
        (*CloseHandle_f)(hFile);
    }
    return 0x0;
}



undefined4 FUN_10001163(undefined4 param_1,int param_2)

{
    if (param_2 == 0x1) {
        setup();
        (*CreateThread_f)(0x0,0x0,pipe_communicate,0x0,0x0,0x0);
    }
    return 0x1;
}



// WARNING: Could not reconcile some variable overlaps

void __cdecl FUN_10001187(uint *param_1,byte *param_2,int param_3)

{
    uint uVar1;
    uint uVar2;
    char cVar3;
    uint uVar4;
    int iVar5;
    uint local_4;
    
    iVar5 = 0x0;
    local_4 = param_1[0x1];
    uVar4 = *param_1;
    if (0x0 < param_3) {
        do {
            uVar4 = (uint)(byte)((char)uVar4 + 0x1);
            uVar1 = param_1[uVar4 + 0x2];
            cVar3 = (char)uVar1;
            local_4 = (uint)(byte)(cVar3 + (char)local_4);
            uVar2 = param_1[local_4 + 0x2];
            param_1[uVar4 + 0x2] = uVar2;
            param_1[local_4 + 0x2] = uVar1;
            param_2[iVar5] = param_2[iVar5] ^ *(byte *)(param_1 + (byte)(cVar3 + (char)uVar2) + 0x2);
            iVar5 = iVar5 + 0x1;
        } while (iVar5 < param_3);
    }
    *param_1 = uVar4;
    param_1[0x1] = local_4;
    return;
}



void __cdecl FUN_100011ef(uint *out,char *data,int data_len)

{
    int iVar1;
    uint *puVar2;
    uint uVar3;
    uint idx4;
    int iVar4;
    int idx;
    
    iVar4 = 0x0;
    idx4 = 0x0;
    *out = 0x0;
    out[0x1] = 0x0;
    do {
        puVar2 = out + idx4 + 0x2;
        *puVar2 = idx4;
        puVar2[0x1] = idx4 + 0x1;
        puVar2[0x2] = idx4 + 0x2;
        puVar2[0x3] = idx4 + 0x3;
        idx4 = idx4 + 0x4;
    } while ((int)idx4 < 0x100);
    idx4 = 0x0;
    idx = 0x0;
    do {
        uVar3 = out[idx + 0x2];
        idx4 = (uint)(byte)(data[iVar4] + (char)idx4 + (char)uVar3);
        out[idx + 0x2] = out[idx4 + 0x2];
        iVar1 = iVar4 + 0x1;
        out[idx4 + 0x2] = uVar3;
        idx = idx + 0x1;
        iVar4 = 0x0;
        if (iVar1 < data_len) {
            iVar4 = iVar1;
        }
    } while (idx < 0x100);
    return;
}



int __cdecl resolve_symbol(int param_1,undefined4 param_2)

{
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    int iVar5;
    uint uVar6;
    
    uVar6 = 0x0;
    if ((*(int *)(*(int *)(param_1 + 0x3c) + 0x7c + param_1) != 0x0) && (iVar1 = *(int *)(*(int *)(param_1 + 0x3c) + 0x78 + param_1), iVar1 != 0x0)) {
        iVar2 = *(int *)(param_1 + 0x24 + iVar1);
        iVar3 = *(int *)(param_1 + 0x20 + iVar1);
        iVar4 = *(int *)(param_1 + 0x1c + iVar1);
        do {
            iVar5 = (*DAT_10015a1c)(*(int *)(iVar3 + param_1 + uVar6 * 0x4) + param_1,param_2);
            if (iVar5 == 0x0) {
                return *(int *)(iVar4 + param_1 + (uint)*(ushort *)(iVar2 + param_1 + uVar6 * 0x2) * 0x4) + param_1;
            }
            uVar6 = uVar6 + 0x1;
        } while (uVar6 <= *(int *)(param_1 + 0x18 + iVar1) - 0x1U);
    }
    return 0x0;
}



undefined4 FUN_100012db(void)

{
    int in_FS_OFFSET;
    
    return *(undefined4 *)(**(int **)**(undefined4 **)(*(int *)(*(int *)(in_FS_OFFSET + 0x30) + 0xc) + 0x14) + 0x10);
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void setup(void)

{
    int iVar1;
    int iVar2;
    
    _DAT_10015a18 = FUN_10001426;
    DAT_10015a1c = FUN_10001451;
    DAT_10015a20 = FUN_10001493;
    iVar1 = FUN_100012db();
    iVar2 = xor_with_17(&CloseHandle,(int)&global_buffer);
    CloseHandle_f = resolve_symbol(iVar1,iVar2);
    iVar2 = xor_with_17((byte *)ConnectNamedPipe,(int)&global_buffer);
    ConnectNamedPipe_f = resolve_symbol(iVar1,iVar2);
    iVar2 = xor_with_17((byte *)CreateNamedPipeA,(int)&global_buffer);
    CreateNamedPipeA_f = resolve_symbol(iVar1,iVar2);
    iVar2 = xor_with_17(&CreateThread,(int)&global_buffer);
    CreateThread_f = resolve_symbol(iVar1,iVar2);
    iVar2 = xor_with_17((byte *)DisconnectNamedPipe,(int)&global_buffer);
    DisconnectNamedPipe_f = resolve_symbol(iVar1,iVar2);
    iVar2 = xor_with_17(&FlushFileBuffers,(int)&global_buffer);
    FlushFileBuffers_f = resolve_symbol(iVar1,iVar2);
    iVar2 = xor_with_17((byte *)GetLastError,(int)&global_buffer);
    GetLastError_f = resolve_symbol(iVar1,iVar2);
    iVar2 = xor_with_17((byte *)GetProcessHeap,(int)&global_buffer);
    GetProcessHeap_f = resolve_symbol(iVar1,iVar2);
    iVar2 = xor_with_17((byte *)lstrcmpA,(int)&global_buffer);
    lstrcmpA_f = resolve_symbol(iVar1,iVar2);
    iVar2 = xor_with_17((byte *)ReadFile,(int)&global_buffer);
    ReadFile_f = resolve_symbol(iVar1,iVar2);
    iVar2 = xor_with_17((byte *)WriteFile,(int)&global_buffer);
    WriteFile_f = resolve_symbol(iVar1,iVar2);
    return;
}



void * FUN_10001426(void *param_1,int param_2,size_t param_3)

{
    if (param_1 == NULL) {
        param_1 = NULL;
    }
    else if (param_3 != 0x0) {
        _memset(param_1,param_2,param_3);
    }
    return param_1;
}



undefined4 FUN_10001451(char *param_1,int param_2)

{
    int iVar1;
    undefined4 uVar2;
    char *pcVar3;
    
    iVar1 = 0x0;
    if (*param_1 != '\0') {
        pcVar3 = param_1;
        do {
            if (pcVar3[param_2 - (int)param_1] == '\0') break;
            if (*pcVar3 != pcVar3[param_2 - (int)param_1]) goto LAB_1000148a;
            iVar1 = iVar1 + 0x1;
            pcVar3 = pcVar3 + 0x1;
        } while (*pcVar3 != '\0');
    }
    if ((param_1[iVar1] == '\0') && (*(char *)(iVar1 + param_2) == '\0')) {
        uVar2 = 0x0;
    }
    else {
LAB_1000148a:
        uVar2 = 0x1;
    }
    return uVar2;
}



void FUN_10001493(int param_1,char *param_2)

{
    char cVar1;
    int iVar2;
    
    iVar2 = param_1 - (int)param_2;
    do {
        cVar1 = *param_2;
        param_2[iVar2] = cVar1;
        param_2 = param_2 + 0x1;
    } while (cVar1 != '\0');
    return;
}



int __cdecl xor_with_17(byte *what,int dest)

{
    byte bVar1;
    int iVar2;
    int iVar3;
    
    iVar2 = 0x0;
    bVar1 = *what;
    if (bVar1 != 0x0) {
        iVar3 = dest - (int)what;
        do {
            iVar2 = iVar2 + 0x1;
            what[iVar3] = bVar1 ^ 0x17;
            what = what + 0x1;
            bVar1 = *what;
        } while (bVar1 != 0x0);
    }
    *(undefined *)(iVar2 + dest) = 0x0;
    return dest;
}



// Library Function - Single Match
//  int __stdcall dllmain_crt_dispatch(struct HINSTANCE__ * const,unsigned long,void * const)
// 
// Library: Visual Studio 2019 Release

int dllmain_crt_dispatch(HINSTANCE__ *param_1,ulong param_2,void *param_3)

{
    uint uVar1;
    
    if (param_2 == 0x0) {
        uVar1 = dllmain_crt_process_detach(param_3 != NULL);
    }
    else if (param_2 == 0x1) {
        uVar1 = dllmain_crt_process_attach(param_1,param_3);
    }
    else {
        if (param_2 == 0x2) {
            uVar1 = ___scrt_dllmain_crt_thread_attach();
        }
        else {
            if (param_2 != 0x3) {
                return 0x1;
            }
            uVar1 = ___scrt_dllmain_crt_thread_detach();
        }
        uVar1 = uVar1 & 0xff;
    }
    return uVar1;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// Library Function - Single Match
//  int __cdecl dllmain_crt_process_attach(struct HINSTANCE__ * const,void * const)
// 
// Library: Visual Studio 2019 Release

int __cdecl dllmain_crt_process_attach(HINSTANCE__ *param_1,void *param_2)

{
    code *pcVar1;
    bool bVar2;
    undefined4 uVar3;
    uint uVar4;
    int iVar5;
    code **ppcVar6;
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    uVar3 = ___scrt_initialize_crt(0x0);
    if ((char)uVar3 != '\0') {
        ___scrt_acquire_startup_lock();
        bVar2 = true;
        if (_DAT_10015ab0 != 0x0) {
            FUN_10001bf4(0x7);
            pcVar1 = (code *)swi(0x3);
            iVar5 = (*pcVar1)();
            return iVar5;
        }
        _DAT_10015ab0 = 0x1;
        uVar4 = ___scrt_dllmain_before_initialize_c();
        if ((char)uVar4 != '\0') {
            __RTC_Initialize();
            FUN_100018d5();
            ___scrt_initialize_default_local_stdio_options();
            iVar5 = __initterm_e((undefined **)&DAT_1000e11c,(undefined **)&DAT_1000e12c);
            if (iVar5 == 0x0) {
                uVar3 = ___scrt_dllmain_after_initialize_c();
                if ((char)uVar3 != '\0') {
                    FUN_10004440((undefined **)&DAT_1000e114,(undefined **)&DAT_1000e118);
                    _DAT_10015ab0 = 0x2;
                    bVar2 = false;
                }
            }
        }
        FUN_10001610();
        if (!bVar2) {
            ppcVar6 = (code **)FUN_10001bee();
            if (*ppcVar6 != NULL) {
                uVar3 = ___scrt_is_nonwritable_in_current_image((int)ppcVar6);
                if ((char)uVar3 != '\0') {
                    uVar3 = 0x2;
                    pcVar1 = *ppcVar6;
                    _guard_check_icall();
                    (*pcVar1)(param_1,uVar3,param_2);
                }
            }
            DAT_10015a90 = DAT_10015a90 + 0x1;
            iVar5 = 0x1;
            goto LAB_1000161c;
        }
    }
    iVar5 = 0x0;
LAB_1000161c:
    *in_FS_OFFSET = local_14;
    return iVar5;
}



void FUN_10001610(void)

{
    int unaff_EBP;
    
    ___scrt_release_startup_lock((char)*(undefined4 *)(unaff_EBP + -0x1d));
    return;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// Library Function - Single Match
//  int __cdecl dllmain_crt_process_detach(bool)
// 
// Library: Visual Studio 2019 Release

int __cdecl dllmain_crt_process_detach(bool param_1)

{
    code *pcVar1;
    uint uVar2;
    int iVar3;
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    if (DAT_10015a90 < 0x1) {
        uVar2 = 0x0;
    }
    else {
        DAT_10015a90 = DAT_10015a90 + -0x1;
        ___scrt_acquire_startup_lock();
        if (_DAT_10015ab0 != 0x2) {
            FUN_10001bf4(0x7);
            pcVar1 = (code *)swi(0x3);
            iVar3 = (*pcVar1)();
            return iVar3;
        }
        FUN_10001a25();
        __scrt_uninitialize_type_info();
        __RTC_Terminate();
        _DAT_10015ab0 = 0x0;
        FUN_100016c9();
        uVar2 = ___scrt_uninitialize_crt(param_1,'\0');
        uVar2 = -(uint)((uVar2 & 0xff) != 0x0) & 0x1;
        FUN_100016d6();
    }
    *in_FS_OFFSET = local_14;
    return uVar2;
}



void FUN_100016c9(void)

{
    int unaff_EBP;
    
    ___scrt_release_startup_lock((char)*(undefined4 *)(unaff_EBP + -0x20));
    return;
}



void FUN_100016d6(void)

{
    FUN_10001a48();
    return;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  int __cdecl dllmain_dispatch(struct HINSTANCE__ * const,unsigned long,void * const)
// 
// Library: Visual Studio 2019 Release

int __cdecl dllmain_dispatch(HINSTANCE__ *param_1,ulong param_2,void *param_3)

{
    int iVar1;
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    if ((param_2 == 0x0) && (DAT_10015a90 < 0x1)) {
        iVar1 = 0x0;
    }
    else if (((param_2 != 0x1) && (param_2 != 0x2)) || ((iVar1 = dllmain_raw(param_1,param_2,param_3), iVar1 != 0x0 && (iVar1 = dllmain_crt_dispatch(param_1,param_2,param_3), iVar1 != 0x0)))) {
        iVar1 = FUN_10001163(param_1,param_2);
        if ((param_2 == 0x1) && (iVar1 == 0x0)) {
            FUN_10001163(param_1,0x0);
            dllmain_crt_process_detach(param_3 != NULL);
            dllmain_raw(param_1,0x0,param_3);
        }
        if (((param_2 == 0x0) || (param_2 == 0x3)) && (iVar1 = dllmain_crt_dispatch(param_1,param_2,param_3), iVar1 != 0x0)) {
            iVar1 = dllmain_raw(param_1,param_2,param_3);
        }
    }
    *in_FS_OFFSET = local_14;
    return iVar1;
}



// WARNING: Removing unreachable block (ram,0x10001802)
// Library Function - Single Match
//  int __stdcall dllmain_raw(struct HINSTANCE__ * const,unsigned long,void * const)
// 
// Library: Visual Studio 2019 Release

int dllmain_raw(HINSTANCE__ *param_1,ulong param_2,void *param_3)

{
    return 0x1;
}



// Library Function - Single Match
//  __DllMainCRTStartup@12
// 
// Library: Visual Studio 2019 Release

void __DllMainCRTStartup_12(HINSTANCE__ *param_1,ulong param_2,void *param_3)

{
    if (param_2 == 0x1) {
        ___security_init_cookie();
    }
    dllmain_dispatch(param_1,param_2,param_3);
    return;
}



// Library Function - Single Match
//  ___get_entropy
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

uint ___get_entropy(void)

{
    DWORD DVar1;
    uint local_18;
    uint local_14;
    _FILETIME local_10;
    uint local_8;
    
    local_10.dwLowDateTime = 0x0;
    local_10.dwHighDateTime = 0x0;
    GetSystemTimeAsFileTime(&local_10);
    local_8 = local_10.dwHighDateTime ^ local_10.dwLowDateTime;
    DVar1 = GetCurrentThreadId();
    local_8 = local_8 ^ DVar1;
    DVar1 = GetCurrentProcessId();
    local_8 = local_8 ^ DVar1;
    QueryPerformanceCounter((LARGE_INTEGER *)&local_18);
    return local_14 ^ local_18 ^ local_8 ^ (uint)&local_8;
}



// Library Function - Single Match
//  ___security_init_cookie
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl ___security_init_cookie(void)

{
    if ((DAT_10015124 == 0xbb40e64e) || ((DAT_10015124 & 0xffff0000) == 0x0)) {
        DAT_10015124 = ___get_entropy();
        if (DAT_10015124 == 0xbb40e64e) {
            DAT_10015124 = 0xbb40e64f;
        }
        else if ((DAT_10015124 & 0xffff0000) == 0x0) {
            DAT_10015124 = DAT_10015124 | (DAT_10015124 | 0x4711) << 0x10;
        }
    }
    DAT_10015120 = ~DAT_10015124;
    return;
}



void FUN_100018d5(void)

{
    InitializeSListHead((PSLIST_HEADER)&DAT_10015a98);
    return;
}



// Library Function - Single Match
//  void __cdecl __scrt_uninitialize_type_info(void)
// 
// Library: Visual Studio 2019 Release

void __cdecl __scrt_uninitialize_type_info(void)

{
    ___std_type_info_destroy_list((PSLIST_HEADER)&DAT_10015a98);
    return;
}



undefined * FUN_100018ed(void)

{
    return &DAT_10015aa0;
}



undefined * FUN_100018f3(void)

{
    return &DAT_10015aa8;
}



// Library Function - Single Match
//  ___scrt_initialize_default_local_stdio_options
// 
// Library: Visual Studio 2019 Release

void ___scrt_initialize_default_local_stdio_options(void)

{
    uint *puVar1;
    
    puVar1 = (uint *)FUN_100018ed();
    *puVar1 = *puVar1 | 0x24;
    puVar1[0x1] = puVar1[0x1];
    puVar1 = (uint *)FUN_100018f3();
    *puVar1 = *puVar1 | 0x2;
    puVar1[0x1] = puVar1[0x1];
    return;
}



// Library Function - Single Match
//  struct _IMAGE_SECTION_HEADER * __cdecl find_pe_section(unsigned char * const,unsigned int)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

_IMAGE_SECTION_HEADER * __cdecl find_pe_section(uchar *param_1,uint param_2)

{
    int iVar1;
    _IMAGE_SECTION_HEADER *p_Var2;
    _IMAGE_SECTION_HEADER *p_Var3;
    
    iVar1 = *(int *)(param_1 + 0x3c);
    p_Var2 = (_IMAGE_SECTION_HEADER *)(param_1 + (uint)*(ushort *)(param_1 + iVar1 + 0x14) + iVar1 + 0x18);
    p_Var3 = p_Var2 + *(ushort *)(param_1 + iVar1 + 0x6);
    while( true ) {
        if (p_Var2 == p_Var3) {
            return NULL;
        }
        if ((p_Var2->VirtualAddress <= param_2) && (param_2 < p_Var2->Misc + p_Var2->VirtualAddress)) break;
        p_Var2 = p_Var2 + 0x1;
    }
    return p_Var2;
}



// Library Function - Single Match
//  ___scrt_acquire_startup_lock
// 
// Library: Visual Studio 2019 Release

uint ___scrt_acquire_startup_lock(void)

{
    uint uVar1;
    uint uVar2;
    bool bVar3;
    undefined3 extraout_var;
    uint uVar4;
    int in_FS_OFFSET;
    
    bVar3 = ___scrt_is_ucrt_dll_in_use();
    uVar4 = CONCAT31(extraout_var,bVar3);
    if (uVar4 != 0x0) {
        uVar1 = *(uint *)(*(int *)(in_FS_OFFSET + 0x18) + 0x4);
        while( true ) {
            uVar4 = 0x0;
            LOCK();
            uVar2 = uVar1;
            if (DAT_10015ab4 != 0x0) {
                uVar4 = DAT_10015ab4;
                uVar2 = DAT_10015ab4;
            }
            DAT_10015ab4 = uVar2;
            if (uVar4 == 0x0) break;
            if (uVar1 == uVar4) {
                return CONCAT31((int3)(uVar4 >> 0x8),0x1);
            }
        }
    }
    return uVar4 & 0xffffff00;
}



// Library Function - Single Match
//  ___scrt_dllmain_after_initialize_c
// 
// Library: Visual Studio 2019 Release

undefined4 ___scrt_dllmain_after_initialize_c(void)

{
    bool bVar1;
    undefined3 extraout_var;
    undefined4 uVar2;
    int iVar3;
    uint uVar4;
    
    bVar1 = ___scrt_is_ucrt_dll_in_use();
    if (CONCAT31(extraout_var,bVar1) == 0x0) {
        iVar3 = FUN_10001f89();
        uVar4 = FUN_10004c21(iVar3);
        if (uVar4 != 0x0) {
            return uVar4 & 0xffffff00;
        }
        uVar2 = thunk_FUN_10004c2c();
    }
    else {
        uVar2 = FUN_10001db8();
    }
    return CONCAT31((int3)((uint)uVar2 >> 0x8),0x1);
}



// Library Function - Single Match
//  ___scrt_dllmain_before_initialize_c
// 
// Library: Visual Studio 2019 Release

uint ___scrt_dllmain_before_initialize_c(void)

{
    uint uVar1;
    
    uVar1 = ___scrt_initialize_onexit_tables(0x0);
    return uVar1 & 0xffffff00 | (uint)((char)uVar1 != '\0');
}



// Library Function - Single Match
//  ___scrt_dllmain_crt_thread_attach
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

uint ___scrt_dllmain_crt_thread_attach(void)

{
    uint uVar1;
    
    uVar1 = ___vcrt_thread_attach();
    if ((char)uVar1 != '\0') {
        uVar1 = FUN_100050ee();
        if ((char)uVar1 != '\0') {
            return CONCAT31((int3)(uVar1 >> 0x8),0x1);
        }
        uVar1 = ___vcrt_thread_detach();
    }
    return uVar1 & 0xffffff00;
}



// Library Function - Single Match
//  ___scrt_dllmain_crt_thread_detach
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

undefined ___scrt_dllmain_crt_thread_detach(void)

{
    FUN_100050f9();
    ___vcrt_thread_detach();
    return 0x1;
}



// Library Function - Single Match
//  ___scrt_dllmain_exception_filter
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl ___scrt_dllmain_exception_filter(undefined4 param_1,int param_2,undefined4 param_3,undefined *param_4,int param_5,uint *param_6)

{
    bool bVar1;
    undefined3 extraout_var;
    int iVar2;
    
    bVar1 = ___scrt_is_ucrt_dll_in_use();
    iVar2 = CONCAT31(extraout_var,bVar1);
    if ((iVar2 == 0x0) && (param_2 == 0x1)) {
        _guard_check_icall();
        (*(code *)param_4)(param_1,iVar2,param_3);
    }
    __seh_filter_dll(param_5,param_6);
    return;
}



void FUN_10001a25(void)

{
    bool bVar1;
    undefined3 extraout_var;
    int iVar2;
    
    bVar1 = ___scrt_is_ucrt_dll_in_use();
    if (CONCAT31(extraout_var,bVar1) != 0x0) {
        FUN_10004f58(0xbc);
        return;
    }
    iVar2 = FUN_1000491a();
    if (iVar2 != 0x0) {
        return;
    }
    FUN_10004737(0x0,0x0,0x1);
    return;
}



undefined4 FUN_10001a48(void)

{
    undefined4 uVar1;
    
    ___acrt_uninitialize_critical(0x0);
    uVar1 = ___vcrt_uninitialize_ptd();
    return CONCAT31((int3)((uint)uVar1 >> 0x8),0x1);
}



// Library Function - Single Match
//  ___scrt_initialize_crt
// 
// Library: Visual Studio 2019 Release

uint __cdecl ___scrt_initialize_crt(int param_1)

{
    uint uVar1;
    undefined4 uVar2;
    
    if (param_1 == 0x0) {
        DAT_10015ab8 = 0x1;
    }
    FUN_10001db8();
    uVar1 = ___vcrt_initialize();
    if ((char)uVar1 != '\0') {
        uVar2 = ___acrt_initialize();
        if ((char)uVar2 != '\0') {
            return CONCAT31((int3)((uint)uVar2 >> 0x8),0x1);
        }
        uVar1 = ___vcrt_uninitialize('\0');
    }
    return uVar1 & 0xffffff00;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// Library Function - Single Match
//  ___scrt_initialize_onexit_tables
// 
// Library: Visual Studio 2019 Release

undefined4 __cdecl ___scrt_initialize_onexit_tables(int param_1)

{
    code *pcVar1;
    bool bVar2;
    undefined4 in_EAX;
    undefined3 extraout_var;
    uint uVar3;
    undefined4 uVar4;
    
    if (DAT_10015ab9 != '\0') {
        return CONCAT31((int3)((uint)in_EAX >> 0x8),0x1);
    }
    if ((param_1 != 0x0) && (param_1 != 0x1)) {
        FUN_10001bf4(0x5);
        pcVar1 = (code *)swi(0x3);
        uVar4 = (*pcVar1)();
        return uVar4;
    }
    bVar2 = ___scrt_is_ucrt_dll_in_use();
    uVar3 = CONCAT31(extraout_var,bVar2);
    if ((uVar3 == 0x0) || (param_1 != 0x0)) {
        _DAT_10015abc = 0xffffffff;
        _DAT_10015ac0 = 0xffffffff;
        _DAT_10015ac4 = 0xffffffff;
        _DAT_10015ac8 = 0xffffffff;
        _DAT_10015acc = 0xffffffff;
        _DAT_10015ad0 = 0xffffffff;
LAB_10001b01:
        DAT_10015ab9 = '\x01';
        uVar3 = CONCAT31((int3)(uVar3 >> 0x8),0x1);
    }
    else {
        uVar3 = __initialize_onexit_table((int *)&DAT_10015abc);
        if (uVar3 == 0x0) {
            uVar3 = __initialize_onexit_table((int *)&DAT_10015ac8);
            if (uVar3 == 0x0) goto LAB_10001b01;
        }
        uVar3 = uVar3 & 0xffffff00;
    }
    return uVar3;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  ___scrt_is_nonwritable_in_current_image
// 
// Library: Visual Studio 2019 Release

uint __cdecl ___scrt_is_nonwritable_in_current_image(int param_1)

{
    _IMAGE_SECTION_HEADER *p_Var1;
    uint uVar2;
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    p_Var1 = find_pe_section((uchar *)&IMAGE_DOS_HEADER_10000000,param_1 + 0xf0000000);
    if ((p_Var1 == NULL) || ((int)p_Var1->Characteristics < 0x0)) {
        uVar2 = (uint)p_Var1 & 0xffffff00;
    }
    else {
        uVar2 = CONCAT31((int3)((uint)p_Var1 >> 0x8),0x1);
    }
    *in_FS_OFFSET = local_14;
    return uVar2;
}



// Library Function - Single Match
//  ___scrt_release_startup_lock
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

int __cdecl ___scrt_release_startup_lock(char param_1)

{
    int iVar1;
    bool bVar2;
    undefined3 extraout_var;
    int iVar3;
    
    bVar2 = ___scrt_is_ucrt_dll_in_use();
    iVar1 = DAT_10015ab4;
    iVar3 = CONCAT31(extraout_var,bVar2);
    if ((iVar3 != 0x0) && (param_1 == '\0')) {
        DAT_10015ab4 = 0x0;
        iVar3 = iVar1;
    }
    return iVar3;
}



// Library Function - Single Match
//  ___scrt_uninitialize_crt
// 
// Library: Visual Studio 2019 Release

undefined4 __cdecl ___scrt_uninitialize_crt(char param_1,char param_2)

{
    undefined4 in_EAX;
    
    if ((DAT_10015ab8 == '\0') || (param_2 == '\0')) {
        ___acrt_uninitialize(param_1);
        in_EAX = ___vcrt_uninitialize(param_1);
    }
    return CONCAT31((int3)((uint)in_EAX >> 0x8),0x1);
}



undefined * FUN_10001bee(void)

{
    return &DAT_100164b0;
}



void FUN_10001bf4(undefined4 param_1)

{
    code *pcVar1;
    BOOL BVar2;
    LONG LVar3;
    undefined4 local_328 [0x27];
    EXCEPTION_RECORD local_5c;
    _EXCEPTION_POINTERS local_c;
    
    BVar2 = IsProcessorFeaturePresent(0x17);
    if (BVar2 != 0x0) {
        pcVar1 = (code *)swi(0x29);
        (*pcVar1)();
    }
    FUN_10001d0f();
    _memset(local_328,0x0,0x2cc);
    local_328[0] = 0x10001;
    _memset(&local_5c,0x0,0x50);
    local_5c.ExceptionCode = 0x40000015;
    local_5c.ExceptionFlags = 0x1;
    BVar2 = IsDebuggerPresent();
    local_c.ExceptionRecord = &local_5c;
    local_c.ContextRecord = (PCONTEXT)local_328;
    SetUnhandledExceptionFilter(NULL);
    LVar3 = UnhandledExceptionFilter(&local_c);
    if ((LVar3 == 0x0) && (BVar2 != 0x1)) {
        FUN_10001d0f();
    }
    return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void FUN_10001d0f(void)

{
    _DAT_10015ad4 = 0x0;
    return;
}



// WARNING: Removing unreachable block (ram,0x10001d27)
// WARNING: Removing unreachable block (ram,0x10001d28)
// WARNING: Removing unreachable block (ram,0x10001d2e)
// WARNING: Removing unreachable block (ram,0x10001d38)
// WARNING: Removing unreachable block (ram,0x10001d3f)
// Library Function - Single Match
//  __RTC_Initialize
// 
// Library: Visual Studio 2019 Release

void __RTC_Initialize(void)

{
    return;
}



// WARNING: Removing unreachable block (ram,0x10001d53)
// WARNING: Removing unreachable block (ram,0x10001d54)
// WARNING: Removing unreachable block (ram,0x10001d5a)
// WARNING: Removing unreachable block (ram,0x10001d64)
// WARNING: Removing unreachable block (ram,0x10001d6b)
// Library Function - Single Match
//  __RTC_Terminate
// 
// Library: Visual Studio 2019 Release

void __RTC_Terminate(void)

{
    return;
}



// WARNING: This is an inlined function
// WARNING: Unable to track spacebase fully for stack
// WARNING: Variable defined which should be unmapped: param_2
// Library Function - Single Match
//  __SEH_prolog4
// 
// Library: Visual Studio

void __cdecl __SEH_prolog4(undefined4 param_1,int param_2)

{
    int iVar1;
    undefined4 unaff_EBX;
    undefined4 unaff_ESI;
    undefined4 unaff_EDI;
    int *in_FS_OFFSET;
    undefined4 unaff_retaddr;
    uint auStack28 [0x5];
    undefined local_8 [0x8];
    
    iVar1 = -param_2;
    *(undefined4 *)((int)auStack28 + iVar1 + 0x10) = unaff_EBX;
    *(undefined4 *)((int)auStack28 + iVar1 + 0xc) = unaff_ESI;
    *(undefined4 *)((int)auStack28 + iVar1 + 0x8) = unaff_EDI;
    *(uint *)((int)auStack28 + iVar1 + 0x4) = DAT_10015124 ^ (uint)&param_2;
    *(undefined4 *)((int)auStack28 + iVar1) = unaff_retaddr;
    *in_FS_OFFSET = (int)local_8;
    return;
}



void _guard_check_icall(void)

{
    return;
}



// WARNING: Removing unreachable block (ram,0x10001e26)
// WARNING: Removing unreachable block (ram,0x10001deb)
// WARNING: Removing unreachable block (ram,0x10001e9d)
// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined4 FUN_10001db8(void)

{
    int *piVar1;
    uint *puVar2;
    int iVar3;
    BOOL BVar4;
    uint uVar5;
    uint uVar6;
    uint uVar7;
    uint in_XCR0;
    
    _DAT_10015adc = 0x0;
    DAT_10015128 = DAT_10015128 | 0x1;
    BVar4 = IsProcessorFeaturePresent(0xa);
    uVar5 = DAT_10015128;
    if (BVar4 != 0x0) {
        piVar1 = (int *)cpuid_basic_info(0x0);
        puVar2 = (uint *)cpuid_Version_info(0x1);
        uVar6 = puVar2[0x3];
        if (((piVar1[0x1] ^ 0x756e6547U | piVar1[0x3] ^ 0x6c65746eU | piVar1[0x2] ^ 0x49656e69U) == 0x0) &&
           (((((uVar5 = *puVar2 & 0xfff3ff0, uVar5 == 0x106c0 || (uVar5 == 0x20660)) || (uVar5 == 0x20670)) || ((uVar5 == 0x30650 || (uVar5 == 0x30660)))) || (uVar5 == 0x30670)))) {
            DAT_10015ae0 = DAT_10015ae0 | 0x1;
        }
        if (*piVar1 < 0x7) {
            uVar7 = 0x0;
        }
        else {
            iVar3 = cpuid_Extended_Feature_Enumeration_info(0x7);
            uVar7 = *(uint *)(iVar3 + 0x4);
            if ((uVar7 & 0x200) != 0x0) {
                DAT_10015ae0 = DAT_10015ae0 | 0x2;
            }
        }
        _DAT_10015adc = 0x1;
        uVar5 = DAT_10015128 | 0x2;
        if ((uVar6 & 0x100000) != 0x0) {
            uVar5 = DAT_10015128 | 0x6;
            _DAT_10015adc = 0x2;
            if ((((uVar6 & 0x8000000) != 0x0) && ((uVar6 & 0x10000000) != 0x0)) && ((in_XCR0 & 0x6) == 0x6)) {
                _DAT_10015adc = 0x3;
                uVar5 = DAT_10015128 | 0xe;
                if ((uVar7 & 0x20) != 0x0) {
                    _DAT_10015adc = 0x5;
                    uVar5 = DAT_10015128 | 0x2e;
                    if (((uVar7 & 0xd0030000) == 0xd0030000) && ((in_XCR0 & 0xe0) == 0xe0)) {
                        DAT_10015128 = DAT_10015128 | 0x6e;
                        _DAT_10015adc = 0x6;
                        uVar5 = DAT_10015128;
                    }
                }
            }
        }
    }
    DAT_10015128 = uVar5;
    return 0x0;
}



undefined4 FUN_10001f89(void)

{
    return 0x1;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// Library Function - Single Match
//  ___scrt_is_ucrt_dll_in_use
// 
// Library: Visual Studio 2019 Release

bool ___scrt_is_ucrt_dll_in_use(void)

{
    return _DAT_100164ac != 0x0;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void __fastcall FUN_10001f99(int param_1,undefined param_2,undefined param_3)

{
    code *pcVar1;
    undefined4 uVar2;
    undefined4 uVar3;
    uint uVar4;
    undefined4 extraout_ECX;
    undefined4 extraout_ECX_00;
    undefined4 uVar5;
    undefined4 extraout_EDX;
    undefined4 unaff_EBX;
    undefined4 unaff_EBP;
    undefined4 unaff_ESI;
    undefined4 unaff_EDI;
    undefined2 in_ES;
    undefined2 in_CS;
    undefined2 in_SS;
    undefined2 in_DS;
    undefined2 in_FS;
    undefined2 in_GS;
    byte bVar6;
    byte bVar7;
    byte in_AF;
    byte bVar8;
    byte bVar9;
    byte in_TF;
    byte in_IF;
    byte bVar10;
    byte in_NT;
    byte in_AC;
    byte in_VIF;
    byte in_VIP;
    byte in_ID;
    undefined8 uVar11;
    undefined4 unaff_retaddr;
    
    if (param_1 == DAT_10015124) {
        return;
    }
    uVar4 = IsProcessorFeaturePresent(0x17);
    uVar11 = CONCAT44(extraout_EDX,uVar4);
    bVar6 = 0x0;
    bVar10 = 0x0;
    bVar9 = (int)uVar4 < 0x0;
    bVar8 = uVar4 == 0x0;
    bVar7 = (POPCOUNT(uVar4 & 0xff) & 0x1U) == 0x0;
    uVar5 = extraout_ECX;
    uVar2 = unaff_retaddr;
    uVar3 = unaff_EBP;
    if (!(bool)bVar8) {
        pcVar1 = (code *)swi(0x29);
        uVar11 = (*pcVar1)();
        uVar5 = extraout_ECX_00;
        uVar2 = unaff_retaddr;
        uVar3 = unaff_EBP;
    }
    _DAT_10015bec = uVar3;
    _DAT_10015af4 = uVar2;
    _DAT_10015bf8 =
         (uint)(in_NT & 0x1) * 0x4000 | (uint)(bVar10 & 0x1) * 0x800 | (uint)(in_IF & 0x1) * 0x200 | (uint)(in_TF & 0x1) * 0x100 | (uint)(bVar9 & 0x1) * 0x80 | (uint)(bVar8 & 0x1) * 0x40 |
         (uint)(in_AF & 0x1) * 0x10 | (uint)(bVar7 & 0x1) * 0x4 | (uint)(bVar6 & 0x1) | (uint)(in_ID & 0x1) * 0x200000 | (uint)(in_VIP & 0x1) * 0x100000 | (uint)(in_VIF & 0x1) * 0x80000 |
         (uint)(in_AC & 0x1) * 0x40000;
    _DAT_10015bfc = &param_3;
    _DAT_10015b38 = 0x10001;
    _DAT_10015ae8 = 0xc0000409;
    _DAT_10015aec = 0x1;
    _DAT_10015af8 = 0x1;
    _DAT_10015afc = 0x2;
    _DAT_10015bc4 = in_GS;
    _DAT_10015bc8 = in_FS;
    _DAT_10015bcc = in_ES;
    _DAT_10015bd0 = in_DS;
    _DAT_10015bd4 = unaff_EDI;
    _DAT_10015bd8 = unaff_ESI;
    _DAT_10015bdc = unaff_EBX;
    _DAT_10015be4 = uVar5;
    DAT_10015bf0 = _DAT_10015af4;
    _DAT_10015bf4 = in_CS;
    _DAT_10015c00 = in_SS;
    FUN_10001fa7((_EXCEPTION_POINTERS *)&PTR_DAT_1000e164);
    _DAT_10015be0 = (undefined4)((ulonglong)uVar11 >> 0x20);
    _DAT_10015be8 = (undefined4)uVar11;
    return;
}



void __cdecl FUN_10001fa7(_EXCEPTION_POINTERS *param_1)

{
    HANDLE hProcess;
    UINT uExitCode;
    
    SetUnhandledExceptionFilter(NULL);
    UnhandledExceptionFilter(param_1);
    uExitCode = 0xc0000409;
    hProcess = GetCurrentProcess();
    TerminateProcess(hProcess,uExitCode);
    return;
}



// Library Function - Single Match
//  _memset
// 
// Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual Studio 2019 Release

void * __cdecl _memset(void *_Dst,int _Val,size_t _Size)

{
    int iVar1;
    undefined *puVar2;
    int *piVar3;
    
    if (_Size == 0x0) {
        return _Dst;
    }
    iVar1 = (_Val & 0xffU) * 0x1010101;
    piVar3 = (int *)_Dst;
    if (0x20 < _Size) {
        if (0x7f < _Size) {
            puVar2 = (undefined *)_Dst;
            if ((DAT_10015ae0 >> 0x1 & 0x1) != 0x0) {
                for (; _Size != 0x0; _Size = _Size - 0x1) {
                    *puVar2 = (char)iVar1;
                    puVar2 = puVar2 + 0x1;
                }
                return _Dst;
            }
            if ((DAT_10015128 >> 0x1 & 0x1) == 0x0) goto joined_r0x100021db;
            *(int *)_Dst = iVar1;
            *(int *)((int)_Dst + 0x4) = iVar1;
            *(int *)((int)_Dst + 0x8) = iVar1;
            *(int *)((int)_Dst + 0xc) = iVar1;
            piVar3 = (int *)((int)_Dst + 0x10U & 0xfffffff0);
            _Size = (int)_Dst + (_Size - (int)piVar3);
            if (0x80 < _Size) {
                do {
                    *piVar3 = iVar1;
                    piVar3[0x1] = iVar1;
                    piVar3[0x2] = iVar1;
                    piVar3[0x3] = iVar1;
                    piVar3[0x4] = iVar1;
                    piVar3[0x5] = iVar1;
                    piVar3[0x6] = iVar1;
                    piVar3[0x7] = iVar1;
                    piVar3[0x8] = iVar1;
                    piVar3[0x9] = iVar1;
                    piVar3[0xa] = iVar1;
                    piVar3[0xb] = iVar1;
                    piVar3[0xc] = iVar1;
                    piVar3[0xd] = iVar1;
                    piVar3[0xe] = iVar1;
                    piVar3[0xf] = iVar1;
                    piVar3[0x10] = iVar1;
                    piVar3[0x11] = iVar1;
                    piVar3[0x12] = iVar1;
                    piVar3[0x13] = iVar1;
                    piVar3[0x14] = iVar1;
                    piVar3[0x15] = iVar1;
                    piVar3[0x16] = iVar1;
                    piVar3[0x17] = iVar1;
                    piVar3[0x18] = iVar1;
                    piVar3[0x19] = iVar1;
                    piVar3[0x1a] = iVar1;
                    piVar3[0x1b] = iVar1;
                    piVar3[0x1c] = iVar1;
                    piVar3[0x1d] = iVar1;
                    piVar3[0x1e] = iVar1;
                    piVar3[0x1f] = iVar1;
                    piVar3 = piVar3 + 0x20;
                    _Size = _Size - 0x80;
                } while ((_Size & 0xffffff00) != 0x0);
                goto LAB_100021a0;
            }
        }
        if ((DAT_10015128 >> 0x1 & 0x1) != 0x0) {
LAB_100021a0:
            if (0x1f < _Size) {
                do {
                    *piVar3 = iVar1;
                    piVar3[0x1] = iVar1;
                    piVar3[0x2] = iVar1;
                    piVar3[0x3] = iVar1;
                    piVar3[0x4] = iVar1;
                    piVar3[0x5] = iVar1;
                    piVar3[0x6] = iVar1;
                    piVar3[0x7] = iVar1;
                    piVar3 = piVar3 + 0x8;
                    _Size = _Size - 0x20;
                } while (0x1f < _Size);
                if ((_Size & 0x1f) == 0x0) {
                    return _Dst;
                }
            }
            piVar3 = (int *)((int)piVar3 + (_Size - 0x20));
            *piVar3 = iVar1;
            piVar3[0x1] = iVar1;
            piVar3[0x2] = iVar1;
            piVar3[0x3] = iVar1;
            piVar3[0x4] = iVar1;
            piVar3[0x5] = iVar1;
            piVar3[0x6] = iVar1;
            piVar3[0x7] = iVar1;
            return _Dst;
        }
    }
joined_r0x100021db:
    for (; (_Size & 0x3) != 0x0; _Size = _Size - 0x1) {
        *(char *)piVar3 = (char)iVar1;
        piVar3 = (int *)((int)piVar3 + 0x1);
    }
    if ((_Size & 0x4) != 0x0) {
        *piVar3 = iVar1;
        piVar3 = piVar3 + 0x1;
        _Size = _Size - 0x4;
    }
    for (; (_Size & 0xfffffff8) != 0x0; _Size = _Size - 0x8) {
        *piVar3 = iVar1;
        piVar3[0x1] = iVar1;
        piVar3 = piVar3 + 0x2;
    }
    return _Dst;
}



// Library Function - Single Match
//  _ValidateLocalCookies
// 
// Library: Visual Studio 2019 Release

void __cdecl _ValidateLocalCookies(int *param_1,int param_2)

{
    undefined in_DL;
    undefined extraout_DL;
    undefined1 unaff_DI;
    
    if (*param_1 != -0x2) {
        FUN_10001f99(param_1[0x1] + param_2 ^ *(uint *)(*param_1 + param_2),in_DL,unaff_DI);
        in_DL = extraout_DL;
    }
    FUN_10001f99(param_1[0x3] + param_2 ^ *(uint *)(param_1[0x2] + param_2),in_DL,param_1._0_1_);
    return;
}



// Library Function - Single Match
//  __except_handler4
// 
// Library: Visual Studio 2019 Release

undefined4 __cdecl __except_handler4(PEXCEPTION_RECORD param_1,PVOID param_2,int param_3)

{
    uint uVar1;
    code *pcVar2;
    DWORD DVar3;
    int iVar4;
    BOOL BVar5;
    undefined4 uVar6;
    int iVar7;
    uint uVar8;
    PEXCEPTION_RECORD pEVar9;
    PEXCEPTION_RECORD local_20;
    int local_1c;
    int *local_18;
    int local_14;
    undefined4 local_10;
    int *local_c;
    char local_5;
    
    local_5 = '\0';
    local_10 = 0x1;
    DVar3 = __filter_x86_sse2_floating_point_exception_default(param_1->ExceptionCode);
    param_1->ExceptionCode = DVar3;
    iVar7 = (int)param_2 + 0x10;
    local_c = (int *)(*(uint *)((int)param_2 + 0x8) ^ DAT_10015124);
    local_14 = iVar7;
    _ValidateLocalCookies(local_c,iVar7);
    ___except_validate_context_record(param_3);
    uVar8 = *(uint *)((int)param_2 + 0xc);
    if ((*(byte *)&param_1->ExceptionFlags & 0x66) == 0x0) {
        local_20 = param_1;
        local_1c = param_3;
        *(PEXCEPTION_RECORD **)((int)param_2 + -0x4) = &local_20;
        if (uVar8 == 0xfffffffe) {
            return local_10;
        }
        do {
            iVar4 = uVar8 * 0x3 + 0x4;
            uVar1 = local_c[iVar4];
            local_18 = local_c + iVar4;
            if ((undefined *)local_18[0x1] != NULL) {
                iVar4 = __EH4_CallFilterFunc_8((undefined *)local_18[0x1]);
                local_5 = '\x01';
                if (iVar4 < 0x0) {
                    local_10 = 0x0;
                    goto LAB_10002334;
                }
                if (0x0 < iVar4) {
                    if ((param_1->ExceptionCode == 0xe06d7363) && (BVar5 = __IsNonwritableInCurrentImage((PBYTE)&PTR____DestructExceptionObject_1000e16c), BVar5 != 0x0)) {
                        pEVar9 = param_1;
                        _guard_check_icall();
                        ___DestructExceptionObject((int *)pEVar9);
                        iVar7 = local_14;
                    }
                    __EH4_GlobalUnwind2_8(param_2,param_1);
                    if (*(uint *)((int)param_2 + 0xc) != uVar8) {
                        __EH4_LocalUnwind_16((int)param_2,uVar8,iVar7,&DAT_10015124);
                    }
                    *(uint *)((int)param_2 + 0xc) = uVar1;
                    _ValidateLocalCookies(local_c,iVar7);
                    __EH4_TransferToHandler_8((undefined *)local_18[0x2]);
                    pcVar2 = (code *)swi(0x3);
                    uVar6 = (*pcVar2)();
                    return uVar6;
                }
            }
            uVar8 = uVar1;
        } while (uVar1 != 0xfffffffe);
        if (local_5 == '\0') {
            return local_10;
        }
    }
    else {
        if (uVar8 == 0xfffffffe) {
            return local_10;
        }
        __EH4_LocalUnwind_16((int)param_2,0xfffffffe,iVar7,&DAT_10015124);
    }
LAB_10002334:
    _ValidateLocalCookies(local_c,iVar7);
    return local_10;
}



// Library Function - Single Match
//  ___std_type_info_compare
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

uint __cdecl ___std_type_info_compare(int param_1,int param_2)

{
    byte bVar1;
    byte *pbVar2;
    byte *pbVar3;
    bool bVar4;
    
    if (param_1 != param_2) {
        pbVar3 = (byte *)(param_2 + 0x5);
        pbVar2 = (byte *)(param_1 + 0x5);
        do {
            bVar1 = *pbVar2;
            bVar4 = bVar1 < *pbVar3;
            if (bVar1 != *pbVar3) {
LAB_10002403:
                return -(uint)bVar4 | 0x1;
            }
            if (bVar1 == 0x0) {
                return 0x0;
            }
            bVar1 = pbVar2[0x1];
            bVar4 = bVar1 < pbVar3[0x1];
            if (bVar1 != pbVar3[0x1]) goto LAB_10002403;
            pbVar2 = pbVar2 + 0x2;
            pbVar3 = pbVar3 + 0x2;
        } while (bVar1 != 0x0);
    }
    return 0x0;
}



// Library Function - Single Match
//  ___std_type_info_destroy_list
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl ___std_type_info_destroy_list(PSLIST_HEADER param_1)

{
    _SINGLE_LIST_ENTRY _Var1;
    _SINGLE_LIST_ENTRY _Var2;
    
    _Var2 = (_SINGLE_LIST_ENTRY)InterlockedFlushSList(param_1);
    while (_Var2 != (_SINGLE_LIST_ENTRY)0x0) {
        _Var1 = *(_SINGLE_LIST_ENTRY *)_Var2;
        FUN_1000517f((LPVOID)_Var2);
        _Var2 = _Var1;
    }
    return;
}



// Library Function - Single Match
//  ___vcrt_initialize
// 
// Library: Visual Studio 2019 Release

uint ___vcrt_initialize(void)

{
    uint uVar1;
    undefined4 uVar2;
    
    uVar1 = ___vcrt_initialize_locks();
    if ((char)uVar1 != '\0') {
        uVar2 = ___vcrt_initialize_ptd();
        if ((char)uVar2 != '\0') {
            return CONCAT31((int3)((uint)uVar2 >> 0x8),0x1);
        }
        uVar1 = ___vcrt_uninitialize_locks();
    }
    return uVar1 & 0xffffff00;
}



// Library Function - Single Match
//  ___vcrt_thread_attach
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

uint ___vcrt_thread_attach(void)

{
    LPVOID pvVar1;
    
    pvVar1 = ___vcrt_getptd_noexit();
    return (uint)pvVar1 & 0xffffff00 | (uint)(pvVar1 != NULL);
}



// Library Function - Single Match
//  ___vcrt_thread_detach
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

undefined ___vcrt_thread_detach(void)

{
    ___vcrt_freeptd(NULL);
    return 0x1;
}



// Library Function - Single Match
//  ___vcrt_uninitialize
// 
// Library: Visual Studio 2019 Release

undefined4 __cdecl ___vcrt_uninitialize(char param_1)

{
    undefined4 in_EAX;
    
    if (param_1 == '\0') {
        ___vcrt_uninitialize_ptd();
        in_EAX = ___vcrt_uninitialize_locks();
    }
    return CONCAT31((int3)((uint)in_EAX >> 0x8),0x1);
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  ___DestructExceptionObject
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl ___DestructExceptionObject(int *param_1)

{
    byte *pbVar1;
    code *pcVar2;
    undefined4 *in_FS_OFFSET;
    int *piVar3;
    undefined4 local_14;
    
    if ((((param_1 != NULL) && (*param_1 == -0x1f928c9d)) && (param_1[0x4] == 0x3)) &&
       ((((param_1[0x5] == 0x19930520 || (param_1[0x5] == 0x19930521)) || (param_1[0x5] == 0x19930522)) && (pbVar1 = (byte *)param_1[0x7], pbVar1 != NULL)))) {
        if (*(void **)(pbVar1 + 0x4) == NULL) {
            if (((*pbVar1 & 0x10) != 0x0) && (piVar3 = *(int **)param_1[0x6], piVar3 != NULL)) {
                pcVar2 = *(code **)(*piVar3 + 0x8);
                _guard_check_icall();
                (*pcVar2)(piVar3);
            }
        }
        else {
            _CallMemberFunction0((void *)param_1[0x6],*(void **)(pbVar1 + 0x4));
        }
    }
    *in_FS_OFFSET = local_14;
    return;
}



// Library Function - Single Match
//  void __stdcall _CallMemberFunction0(void * const,void * const)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void _CallMemberFunction0(void *param_1,void *param_2)

{
    (*(code *)param_2)();
    return;
}



// Library Function - Single Match
//  unsigned long __cdecl _FilterSetCurrentException(struct _EXCEPTION_POINTERS *,unsigned char)
// 
// Library: Visual Studio 2019 Release

ulong __cdecl _FilterSetCurrentException(_EXCEPTION_POINTERS *param_1,uchar param_2)

{
    PEXCEPTION_RECORD pEVar1;
    PCONTEXT pCVar2;
    code *pcVar3;
    int iVar4;
    ulong uVar5;
    
    if ((((param_2 != '\0') && (pEVar1 = param_1->ExceptionRecord, pEVar1->ExceptionCode == 0xe06d7363)) && (pEVar1->NumberParameters == 0x3)) &&
       (((pEVar1->ExceptionInformation[0x0] == 0x19930520 || (pEVar1->ExceptionInformation[0x0] == 0x19930521)) || (pEVar1->ExceptionInformation[0x0] == 0x19930522)))) {
        iVar4 = ___vcrt_getptd();
        *(PEXCEPTION_RECORD *)(iVar4 + 0x10) = pEVar1;
        pCVar2 = param_1->ContextRecord;
        iVar4 = ___vcrt_getptd();
        *(PCONTEXT *)(iVar4 + 0x14) = pCVar2;
        _terminate();
        pcVar3 = (code *)swi(0x3);
        uVar5 = (*pcVar3)();
        return uVar5;
    }
    return 0x0;
}



// Library Function - Single Match
//  __IsExceptionObjectToBeDestroyed
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

undefined4 __cdecl __IsExceptionObjectToBeDestroyed(int param_1)

{
    int *piVar1;
    int iVar2;
    
    iVar2 = ___vcrt_getptd();
    piVar1 = *(int **)(iVar2 + 0x24);
    while( true ) {
        if (piVar1 == NULL) {
            return 0x1;
        }
        if (*piVar1 == param_1) break;
        piVar1 = (int *)piVar1[0x1];
    }
    return 0x0;
}



// Library Function - Single Match
//  ___AdjustPointer
// 
// Library: Visual Studio 2019 Release

int __cdecl ___AdjustPointer(int param_1,int *param_2)

{
    int iVar1;
    int iVar2;
    
    iVar1 = param_2[0x1];
    iVar2 = *param_2 + param_1;
    if (-0x1 < iVar1) {
        iVar2 = iVar2 + *(int *)(*(int *)(iVar1 + param_1) + param_2[0x2]) + iVar1;
    }
    return iVar2;
}



// Library Function - Single Match
//  ___FrameUnwindFilter
// 
// Library: Visual Studio 2019 Release

undefined4 __cdecl ___FrameUnwindFilter(int **param_1)

{
    int *piVar1;
    code *pcVar2;
    int iVar3;
    undefined4 uVar4;
    
    piVar1 = *param_1;
    if ((*piVar1 == -0x1fbcbcae) || (*piVar1 == -0x1fbcb0b3)) {
        iVar3 = ___vcrt_getptd();
        if (0x0 < *(int *)(iVar3 + 0x18)) {
            iVar3 = ___vcrt_getptd();
            *(int *)(iVar3 + 0x18) = *(int *)(iVar3 + 0x18) + -0x1;
        }
    }
    else if (*piVar1 == -0x1f928c9d) {
        iVar3 = ___vcrt_getptd();
        *(int **)(iVar3 + 0x10) = piVar1;
        piVar1 = param_1[0x1];
        iVar3 = ___vcrt_getptd();
        *(int **)(iVar3 + 0x14) = piVar1;
        _terminate();
        pcVar2 = (code *)swi(0x3);
        uVar4 = (*pcVar2)();
        return uVar4;
    }
    return 0x0;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4

void Unwind_10002628(void)

{
    code *pcVar1;
    __acrt_ptd *p_Var2;
    
    p_Var2 = FUN_10005827();
    pcVar1 = *(code **)(p_Var2 + 0xc);
    if (pcVar1 != NULL) {
        _guard_check_icall();
        (*pcVar1)();
    }
    _abort();
    pcVar1 = (code *)swi(0x3);
    (*pcVar1)();
    return;
}



void __cdecl FUN_10002630(uint *param_1,int param_2,uint param_3)

{
    undefined4 *puVar1;
    uint uVar2;
    undefined4 *in_FS_OFFSET;
    undefined4 uStack40;
    undefined *puStack36;
    uint local_20;
    uint uStack28;
    int iStack24;
    uint *puStack20;
    
    puStack20 = param_1;
    iStack24 = param_2;
    uStack28 = param_3;
    puStack36 = &LAB_100026d0;
    uStack40 = *in_FS_OFFSET;
    local_20 = DAT_10015124 ^ (uint)&uStack40;
    *in_FS_OFFSET = &uStack40;
    while( true ) {
        uVar2 = *(uint *)(param_2 + 0xc);
        if ((uVar2 == 0xfffffffe) || ((param_3 != 0xfffffffe && (uVar2 <= param_3)))) break;
        puVar1 = (undefined4 *)((*(uint *)(param_2 + 0x8) ^ *param_1) + 0x10 + uVar2 * 0xc);
        *(undefined4 *)(param_2 + 0xc) = *puVar1;
        if (puVar1[0x1] == 0x0) {
            __NLG_Notify(0x101);
            FUN_100029b0();
        }
    }
    *in_FS_OFFSET = uStack40;
    return;
}



// Library Function - Single Match
//  @_EH4_CallFilterFunc@8
// 
// Library: Visual Studio 2019 Release

void __fastcall __EH4_CallFilterFunc_8(undefined *param_1)

{
    (*(code *)param_1)();
    return;
}



// Library Function - Single Match
//  @_EH4_TransferToHandler@8
// 
// Library: Visual Studio 2019 Release

void __fastcall __EH4_TransferToHandler_8(undefined *UNRECOVERED_JUMPTABLE)

{
    __NLG_Notify(0x1);
                    // WARNING: Could not recover jumptable at 0x10002757. Too many branches
                    // WARNING: Treating indirect jump as call
    (*(code *)UNRECOVERED_JUMPTABLE)();
    return;
}



// Library Function - Single Match
//  @_EH4_GlobalUnwind2@8
// 
// Library: Visual Studio 2019 Release

void __fastcall __EH4_GlobalUnwind2_8(PVOID param_1,PEXCEPTION_RECORD param_2)

{
    RtlUnwind(param_1,(PVOID)0x10002775,param_2,NULL);
    return;
}



// Library Function - Single Match
//  @_EH4_LocalUnwind@16
// 
// Library: Visual Studio 2019 Release

void __fastcall __EH4_LocalUnwind_16(int param_1,uint param_2,undefined4 param_3,uint *param_4)

{
    FUN_10002630(param_4,param_1,param_2);
    return;
}



// WARNING: Removing unreachable block (ram,0x100027a6)
// WARNING: Removing unreachable block (ram,0x100027bb)
// WARNING: Removing unreachable block (ram,0x100027c0)
// Library Function - Single Match
//  ___except_validate_context_record
// 
// Library: Visual Studio 2019 Release

void __cdecl ___except_validate_context_record(int param_1)

{
    return;
}



// Library Function - Single Match
//  ___vcrt_freefls@4
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

void ___vcrt_freefls_4(undefined *param_1)

{
    if ((param_1 != NULL) && (param_1 != &DAT_10015e44)) {
        FUN_1000517f(param_1);
    }
    return;
}



// Library Function - Single Match
//  ___vcrt_freeptd
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl ___vcrt_freeptd(undefined *param_1)

{
    if (DAT_10015130 != 0xffffffff) {
        if (param_1 == NULL) {
            param_1 = (undefined *)___vcrt_FlsGetValue(DAT_10015130);
        }
        ___vcrt_FlsSetValue(DAT_10015130,NULL);
        ___vcrt_freefls_4(param_1);
    }
    return;
}



// Library Function - Single Match
//  ___vcrt_getptd
// 
// Library: Visual Studio 2019 Release

void ___vcrt_getptd(void)

{
    code *pcVar1;
    LPVOID pvVar2;
    int iVar3;
    BOOL BVar4;
    
    pvVar2 = ___vcrt_getptd_noexit();
    if (pvVar2 != NULL) {
        return;
    }
    iVar3 = ___acrt_get_sigabrt_handler();
    if (iVar3 != 0x0) {
        _raise(0x16);
    }
    if ((DAT_10015150 & 0x2) != 0x0) {
        BVar4 = IsProcessorFeaturePresent(0x17);
        if (BVar4 != 0x0) {
            pcVar1 = (code *)swi(0x29);
            (*pcVar1)();
        }
        ___acrt_call_reportfault(0x3,0x40000015,0x1);
    }
    __exit(0x3);
    pcVar1 = (code *)swi(0x3);
    (*pcVar1)();
    return;
}



// Library Function - Single Match
//  ___vcrt_getptd_noexit
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

LPVOID ___vcrt_getptd_noexit(void)

{
    DWORD dwErrCode;
    LPVOID pvVar1;
    int iVar2;
    LPVOID pvVar3;
    LPVOID pvVar4;
    
    if (DAT_10015130 == 0xffffffff) {
        return NULL;
    }
    dwErrCode = GetLastError();
    pvVar1 = (LPVOID)___vcrt_FlsGetValue(DAT_10015130);
    if (pvVar1 == (LPVOID)0xffffffff) {
LAB_10002867:
        pvVar1 = NULL;
        goto LAB_100028ad;
    }
    if (pvVar1 != NULL) goto LAB_100028ad;
    iVar2 = ___vcrt_FlsSetValue(DAT_10015130,(LPVOID)0xffffffff);
    if (iVar2 == 0x0) goto LAB_10002867;
    pvVar3 = (LPVOID)FUN_10005478(0x1,0x28);
    if (pvVar3 == NULL) {
LAB_1000288f:
        ___vcrt_FlsSetValue(DAT_10015130,NULL);
        pvVar1 = NULL;
        pvVar4 = pvVar3;
    }
    else {
        iVar2 = ___vcrt_FlsSetValue(DAT_10015130,pvVar3);
        if (iVar2 == 0x0) goto LAB_1000288f;
        pvVar4 = NULL;
        pvVar1 = pvVar3;
    }
    FUN_1000517f(pvVar4);
LAB_100028ad:
    SetLastError(dwErrCode);
    return pvVar1;
}



// Library Function - Single Match
//  ___vcrt_initialize_ptd
// 
// Library: Visual Studio 2019 Release

uint ___vcrt_initialize_ptd(void)

{
    uint uVar1;
    int iVar2;
    
    uVar1 = ___vcrt_FlsAlloc(___vcrt_freefls_4);
    DAT_10015130 = uVar1;
    if (uVar1 != 0xffffffff) {
        iVar2 = ___vcrt_FlsSetValue(uVar1,&DAT_10015e44);
        if (iVar2 != 0x0) {
            return CONCAT31((int3)((uint)iVar2 >> 0x8),0x1);
        }
        uVar1 = ___vcrt_uninitialize_ptd();
    }
    return uVar1 & 0xffffff00;
}



// Library Function - Single Match
//  ___vcrt_uninitialize_ptd
// 
// Library: Visual Studio 2019 Release

undefined4 ___vcrt_uninitialize_ptd(void)

{
    DWORD DVar1;
    
    DVar1 = DAT_10015130;
    if (DAT_10015130 != 0xffffffff) {
        DVar1 = ___vcrt_FlsFree(DAT_10015130);
        DAT_10015130 = 0xffffffff;
    }
    return CONCAT31((int3)(DVar1 >> 0x8),0x1);
}



// Library Function - Single Match
//  ___vcrt_initialize_locks
// 
// Library: Visual Studio 2019 Release

undefined4 ___vcrt_initialize_locks(void)

{
    int iVar1;
    uint uVar2;
    LPCRITICAL_SECTION p_Var3;
    
    p_Var3 = (LPCRITICAL_SECTION)&DAT_10015e6c;
    uVar2 = 0x0;
    do {
        iVar1 = ___vcrt_InitializeCriticalSectionEx(p_Var3,0xfa0,0x0);
        if (iVar1 == 0x0) {
            uVar2 = ___vcrt_uninitialize_locks();
            return uVar2 & 0xffffff00;
        }
        DAT_10015e84 = DAT_10015e84 + 0x1;
        uVar2 = uVar2 + 0x18;
        p_Var3 = p_Var3 + 0x1;
    } while (uVar2 < 0x18);
    return CONCAT31((int3)((uint)iVar1 >> 0x8),0x1);
}



// Library Function - Single Match
//  ___vcrt_uninitialize_locks
// 
// Library: Visual Studio 2019 Release

undefined4 ___vcrt_uninitialize_locks(void)

{
    undefined4 in_EAX;
    undefined4 extraout_EAX;
    int iVar1;
    LPCRITICAL_SECTION lpCriticalSection;
    
    if (DAT_10015e84 != 0x0) {
        lpCriticalSection = (LPCRITICAL_SECTION)(&DAT_10015e54 + DAT_10015e84 * 0x18);
        iVar1 = DAT_10015e84;
        do {
            DeleteCriticalSection(lpCriticalSection);
            DAT_10015e84 = DAT_10015e84 + -0x1;
            lpCriticalSection = lpCriticalSection + -0x1;
            iVar1 = iVar1 + -0x1;
            in_EAX = extraout_EAX;
        } while (iVar1 != 0x0);
    }
    return CONCAT31((int3)((uint)in_EAX >> 0x8),0x1);
}



undefined4 __fastcall FUN_10002980(undefined4 param_1)

{
    undefined4 in_EAX;
    undefined4 unaff_EBP;
    
    DAT_10015144 = in_EAX;
    DAT_10015148 = param_1;
    DAT_1001514c = unaff_EBP;
    return in_EAX;
}



// Library Function - Single Match
//  __NLG_Notify
// 
// Library: Visual Studio

void __NLG_Notify(ulong param_1)

{
    undefined4 in_EAX;
    undefined4 unaff_EBP;
    
    DAT_10015144 = in_EAX;
    DAT_10015148 = param_1;
    DAT_1001514c = unaff_EBP;
    return;
}



void FUN_100029b0(void)

{
    code *in_EAX;
    
    (*in_EAX)();
    return;
}



// Library Function - Single Match
//  public: static struct std::pair<class __FrameHandler3::TryBlockMap::iterator,class __FrameHandler3::TryBlockMap::iterator> __cdecl __FrameHandler3::GetRangeOfTrysToCheck(class
// __FrameHandler3::TryBlockMap &,int,void *,struct _s_FuncInfo const *,int)
// 
// Library: Visual Studio 2019 Release

pair_class___FrameHandler3__TryBlockMap__iterator_class___FrameHandler3__TryBlockMap__iterator_ __cdecl
__FrameHandler3::GetRangeOfTrysToCheck(TryBlockMap *param_1,int param_2,void *param_3,_s_FuncInfo *param_4,int param_5)

{
    uint uVar1;
    code *pcVar2;
    pair_class___FrameHandler3__TryBlockMap__iterator_class___FrameHandler3__TryBlockMap__iterator_ pVar3;
    int *piVar4;
    uint uVar5;
    uint uVar6;
    int in_stack_00000018;
    uint local_8;
    
    uVar1 = *(uint *)(param_5 + 0xc);
    uVar5 = uVar1;
    uVar6 = uVar1;
    if (-0x1 < in_stack_00000018) {
        piVar4 = (int *)(uVar1 * 0x14 + *(int *)(param_5 + 0x10) + 0x8);
        local_8 = uVar1;
        do {
            if (uVar5 == 0xffffffff) goto LAB_10002a1d;
            uVar5 = uVar5 - 0x1;
            if (((piVar4[-0x6] < (int)param_3) && ((int)param_3 <= piVar4[-0x5])) || (uVar5 == 0xffffffff)) {
                in_stack_00000018 = in_stack_00000018 + -0x1;
                uVar6 = local_8;
                local_8 = uVar5;
            }
            piVar4 = piVar4 + -0x5;
        } while (-0x1 < in_stack_00000018);
    }
    if ((uVar6 <= uVar1) && (uVar5 + 0x1 <= uVar6)) {
        *(uint *)(param_1 + 0xc) = uVar6;
        *(int *)param_1 = param_2;
        *(uint *)(param_1 + 0x4) = uVar5 + 0x1;
        *(int *)(param_1 + 0x8) = param_2;
        return SUB41(param_1,0x0);
    }
LAB_10002a1d:
    _abort();
    pcVar2 = (code *)swi(0x3);
    pVar3 = (pair_class___FrameHandler3__TryBlockMap__iterator_class___FrameHandler3__TryBlockMap__iterator_)(*pcVar2)();
    return pVar3;
}



undefined4 __cdecl FUN_10002a23(undefined4 param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5)

{
    undefined4 uVar1;
    int **in_FS_OFFSET;
    int *local_1c;
    code *local_18;
    uint local_14;
    undefined4 local_10;
    undefined4 local_c;
    int local_8;
    
    local_14 = (uint)&local_1c ^ DAT_10015124;
    local_10 = param_2;
    local_8 = param_4 + 0x1;
    local_18 = __CatchGuardHandler;
    local_c = param_1;
    local_1c = *in_FS_OFFSET;
    *in_FS_OFFSET = (int *)&local_1c;
    uVar1 = __CallSettingFrame_12(param_3,param_1,param_5);
    *in_FS_OFFSET = local_1c;
    return uVar1;
}



undefined4 __cdecl FUN_10002a80(int *param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
    int iVar1;
    int *in_FS_OFFSET;
    undefined4 *local_44;
    code *local_40;
    uint local_3c;
    undefined4 local_38;
    undefined4 *local_34;
    undefined4 local_30;
    undefined4 local_2c;
    undefined *local_28;
    undefined *local_24;
    int local_20;
    int *local_1c;
    undefined4 local_18;
    code *local_14;
    code *local_10;
    undefined4 local_c;
    code *local_8;
    
    local_24 = &stack0xfffffffc;
    local_28 = &stack0xffffffb8;
    if (param_1 == (int *)0x123) {
        *param_2 = 0x10002b4a;
        local_c = 0x1;
    }
    else {
        local_40 = __TranslatorGuardHandler;
        local_3c = DAT_10015124 ^ (uint)&local_44;
        local_38 = param_5;
        local_34 = param_2;
        local_30 = param_6;
        local_2c = param_7;
        local_20 = 0x0;
        local_44 = (undefined4 *)*in_FS_OFFSET;
        *in_FS_OFFSET = (int)&local_44;
        iVar1 = __filter_x86_sse2_floating_point_exception_default(*param_1);
        *param_1 = iVar1;
        local_c = 0x1;
        local_1c = param_1;
        local_18 = param_3;
        iVar1 = ___vcrt_getptd();
        local_8 = *(code **)(iVar1 + 0x8);
        local_10 = _guard_check_icall;
        _guard_check_icall();
        local_14 = local_8;
        (*local_8)(*param_1,&local_1c);
        local_c = 0x0;
        if (local_20 == 0x0) {
            *in_FS_OFFSET = (int)local_44;
        }
        else {
            *local_44 = *(undefined4 *)*in_FS_OFFSET;
            *in_FS_OFFSET = (int)local_44;
        }
    }
    return local_c;
}



// Library Function - Single Match
//  void __stdcall _JumpToContinuation(void *,struct EHRegistrationNode *)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void _JumpToContinuation(void *param_1,EHRegistrationNode *param_2)

{
    undefined4 *in_FS_OFFSET;
    
    *in_FS_OFFSET = *(undefined4 *)*in_FS_OFFSET;
                    // WARNING: Could not recover jumptable at 0x10002b9f. Too many branches
                    // WARNING: Treating indirect jump as call
    (*(code *)param_1)();
    return;
}



// Library Function - Single Match
//  void __stdcall _UnwindNestedFrames(struct EHRegistrationNode *,struct EHExceptionRecord *)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void _UnwindNestedFrames(EHRegistrationNode *param_1,EHExceptionRecord *param_2)

{
    undefined4 *puVar1;
    undefined4 *in_FS_OFFSET;
    
    puVar1 = (undefined4 *)*in_FS_OFFSET;
    RtlUnwind(param_1,(PVOID)0x10002bd0,(PEXCEPTION_RECORD)param_2,NULL);
    *(uint *)(param_2 + 0x4) = *(uint *)(param_2 + 0x4) & 0xfffffffd;
    *puVar1 = *in_FS_OFFSET;
    *in_FS_OFFSET = puVar1;
    return;
}



// Library Function - Single Match
//  __CatchGuardHandler
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl __CatchGuardHandler(EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3)

{
    undefined in_DL;
    undefined1 unaff_SI;
    
    FUN_10001f99(*(uint *)(param_2 + 0x8) ^ (uint)param_2,in_DL,unaff_SI);
    __InternalCxxFrameHandler_class___FrameHandler3_(param_1,*(EHRegistrationNode **)(param_2 + 0x10),param_3,NULL,*(_s_FuncInfo **)(param_2 + 0xc),*(int *)(param_2 + 0x14),param_2,'\0');
    return;
}



// Library Function - Single Match
//  __CreateFrameInfo
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

undefined4 * __cdecl __CreateFrameInfo(undefined4 *param_1,undefined4 param_2)

{
    int iVar1;
    
    *param_1 = param_2;
    iVar1 = ___vcrt_getptd();
    param_1[0x1] = *(undefined4 *)(iVar1 + 0x24);
    iVar1 = ___vcrt_getptd();
    *(undefined4 **)(iVar1 + 0x24) = param_1;
    return param_1;
}



// Library Function - Single Match
//  __FindAndUnlinkFrame
// 
// Library: Visual Studio 2019 Release

void __cdecl __FindAndUnlinkFrame(int param_1)

{
    undefined4 uVar1;
    code *pcVar2;
    int iVar3;
    int *piVar4;
    
    iVar3 = ___vcrt_getptd();
    if (param_1 == *(int *)(iVar3 + 0x24)) {
        uVar1 = *(undefined4 *)(param_1 + 0x4);
        iVar3 = ___vcrt_getptd();
        *(undefined4 *)(iVar3 + 0x24) = uVar1;
    }
    else {
        iVar3 = ___vcrt_getptd();
        iVar3 = *(int *)(iVar3 + 0x24);
        do {
            piVar4 = (int *)(iVar3 + 0x4);
            iVar3 = *piVar4;
            if (iVar3 == 0x0) {
                _abort();
                pcVar2 = (code *)swi(0x3);
                (*pcVar2)();
                return;
            }
        } while (param_1 != iVar3);
        *piVar4 = *(int *)(param_1 + 0x4);
    }
    return;
}



// Library Function - Single Match
//  __TranslatorGuardHandler
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

undefined4 __cdecl __TranslatorGuardHandler(EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3)

{
    undefined4 uVar1;
    undefined in_DL;
    undefined1 unaff_BL;
    code *local_8;
    
    FUN_10001f99(*(uint *)(param_2 + 0x8) ^ (uint)param_2,in_DL,unaff_BL);
    if ((*(uint *)(param_1 + 0x4) & 0x66) != 0x0) {
        *(undefined4 *)(param_2 + 0x24) = 0x1;
        return 0x1;
    }
    __InternalCxxFrameHandler_class___FrameHandler3_
              (param_1,*(EHRegistrationNode **)(param_2 + 0x10),param_3,NULL,*(_s_FuncInfo **)(param_2 + 0xc),*(int *)(param_2 + 0x14),*(EHRegistrationNode **)(param_2 + 0x18),'\x01');
    if (*(int *)(param_2 + 0x24) == 0x0) {
        _UnwindNestedFrames(param_2,param_1);
    }
    FUN_10002a80((int *)0x123,&local_8,0x0,0x0,0x0,0x0,0x0);
                    // WARNING: Could not recover jumptable at 0x10002d2b. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar1 = (*local_8)();
    return uVar1;
}



// Library Function - Multiple Matches With Different Base Names
//  ___CxxFrameHandler
//  ___CxxFrameHandler2
//  ___CxxFrameHandler3
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

_EXCEPTION_DISPOSITION __cdecl FID_conflict____CxxFrameHandler3(EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3,void *param_4)

{
    _s_FuncInfo *in_EAX;
    _EXCEPTION_DISPOSITION _Var1;
    
    _Var1 = __InternalCxxFrameHandler_class___FrameHandler3_(param_1,param_2,param_3,param_4,in_EAX,0x0,NULL,'\0');
    return _Var1;
}



// Library Function - Multiple Matches With Different Base Names
//  _memcpy
//  _memmove
// 
// Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual Studio 2019 Release

void * __cdecl FID_conflict__memcpy(void *_Dst,void *_Src,size_t _Size)

{
    undefined8 uVar1;
    undefined auVar2 [0x20];
    undefined auVar3 [0x20];
    undefined4 uVar4;
    undefined4 uVar5;
    undefined4 uVar6;
    undefined4 uVar7;
    undefined4 uVar8;
    undefined4 uVar9;
    undefined4 uVar10;
    undefined4 uVar11;
    undefined4 uVar12;
    undefined4 uVar13;
    undefined4 uVar14;
    undefined4 uVar15;
    undefined4 uVar16;
    undefined4 uVar17;
    undefined4 uVar18;
    undefined4 uVar19;
    undefined4 uVar20;
    undefined4 uVar21;
    undefined4 uVar22;
    undefined4 uVar23;
    undefined4 uVar24;
    undefined4 uVar25;
    undefined4 uVar26;
    undefined4 uVar27;
    undefined4 uVar28;
    undefined4 uVar29;
    undefined4 uVar30;
    undefined4 uVar31;
    int iVar32;
    undefined8 *puVar33;
    void *pvVar34;
    uint uVar35;
    size_t sVar36;
    uint uVar37;
    int iVar38;
    undefined8 *puVar39;
    undefined4 *puVar40;
    undefined *puVar41;
    undefined4 *puVar42;
    undefined4 *puVar43;
    undefined4 *puVar44;
    undefined4 uVar45;
    undefined4 uVar46;
    undefined4 uVar47;
    
    if ((_Src < _Dst) && (_Dst < (void *)(_Size + (int)_Src))) {
        puVar42 = (undefined4 *)((int)_Src + _Size);
        puVar43 = (undefined4 *)((int)_Dst + _Size);
        if (0x1f < _Size) {
            if ((DAT_10015128 >> 0x1 & 0x1) == 0x0) {
                if (((uint)puVar43 & 0x3) != 0x0) {
                    uVar35 = (uint)puVar43 & 0x3;
                    _Size = _Size - uVar35;
                    do {
                        *(undefined *)((int)puVar43 - 0x1) = *(undefined *)((int)puVar42 + -0x1);
                        puVar42 = (undefined4 *)((int)puVar42 + -0x1);
                        puVar43 = (undefined4 *)((int)puVar43 - 0x1);
                        uVar35 = uVar35 - 0x1;
                    } while (uVar35 != 0x0);
                }
                if (0x1f < _Size) {
                    uVar35 = _Size >> 0x2;
                    while( true ) {
                        if (uVar35 == 0x0) break;
                        uVar35 = uVar35 - 0x1;
                        puVar43[-0x1] = puVar42[-0x1];
                        puVar42 = puVar42 + -0x1;
                        puVar43 = puVar43 + -0x1;
                    }
                    switch(_Size & 0x3) {
                    case 0x0:
                        return _Dst;
                    case 0x1:
                        *(undefined *)((int)puVar43 - 0x1) = *(undefined *)((int)puVar42 + -0x1);
                        return _Dst;
                    case 0x2:
                        *(undefined *)((int)puVar43 - 0x1) = *(undefined *)((int)puVar42 + -0x1);
                        *(undefined *)((int)puVar43 - 0x2) = *(undefined *)((int)puVar42 + -0x2);
                        return _Dst;
                    case 0x3:
                        *(undefined *)((int)puVar43 - 0x1) = *(undefined *)((int)puVar42 + -0x1);
                        *(undefined *)((int)puVar43 - 0x2) = *(undefined *)((int)puVar42 + -0x2);
                        *(undefined *)((int)puVar43 - 0x3) = *(undefined *)((int)puVar42 + -0x3);
                        return _Dst;
                    }
                }
            }
            else {
                while (puVar40 = puVar42, puVar44 = puVar43, ((uint)puVar43 & 0xf) != 0x0) {
                    _Size = _Size - 0x1;
                    puVar42 = (undefined4 *)((int)puVar42 + -0x1);
                    puVar43 = (undefined4 *)((int)puVar43 + -0x1);
                    *(undefined *)puVar43 = *(undefined *)puVar42;
                }
                do {
                    puVar42 = puVar40;
                    puVar43 = puVar44;
                    if (_Size < 0x80) break;
                    puVar42 = puVar40 + -0x20;
                    puVar43 = puVar44 + -0x20;
                    uVar45 = puVar40[-0x1f];
                    uVar46 = puVar40[-0x1e];
                    uVar47 = puVar40[-0x1d];
                    uVar4 = puVar40[-0x1c];
                    uVar5 = puVar40[-0x1b];
                    uVar6 = puVar40[-0x1a];
                    uVar7 = puVar40[-0x19];
                    uVar8 = puVar40[-0x18];
                    uVar9 = puVar40[-0x17];
                    uVar10 = puVar40[-0x16];
                    uVar11 = puVar40[-0x15];
                    uVar12 = puVar40[-0x14];
                    uVar13 = puVar40[-0x13];
                    uVar14 = puVar40[-0x12];
                    uVar15 = puVar40[-0x11];
                    uVar16 = puVar40[-0x10];
                    uVar17 = puVar40[-0xf];
                    uVar18 = puVar40[-0xe];
                    uVar19 = puVar40[-0xd];
                    uVar20 = puVar40[-0xc];
                    uVar21 = puVar40[-0xb];
                    uVar22 = puVar40[-0xa];
                    uVar23 = puVar40[-0x9];
                    uVar24 = puVar40[-0x8];
                    uVar25 = puVar40[-0x7];
                    uVar26 = puVar40[-0x6];
                    uVar27 = puVar40[-0x5];
                    uVar28 = puVar40[-0x4];
                    uVar29 = puVar40[-0x3];
                    uVar30 = puVar40[-0x2];
                    uVar31 = puVar40[-0x1];
                    *puVar43 = *puVar42;
                    puVar44[-0x1f] = uVar45;
                    puVar44[-0x1e] = uVar46;
                    puVar44[-0x1d] = uVar47;
                    puVar44[-0x1c] = uVar4;
                    puVar44[-0x1b] = uVar5;
                    puVar44[-0x1a] = uVar6;
                    puVar44[-0x19] = uVar7;
                    puVar44[-0x18] = uVar8;
                    puVar44[-0x17] = uVar9;
                    puVar44[-0x16] = uVar10;
                    puVar44[-0x15] = uVar11;
                    puVar44[-0x14] = uVar12;
                    puVar44[-0x13] = uVar13;
                    puVar44[-0x12] = uVar14;
                    puVar44[-0x11] = uVar15;
                    puVar44[-0x10] = uVar16;
                    puVar44[-0xf] = uVar17;
                    puVar44[-0xe] = uVar18;
                    puVar44[-0xd] = uVar19;
                    puVar44[-0xc] = uVar20;
                    puVar44[-0xb] = uVar21;
                    puVar44[-0xa] = uVar22;
                    puVar44[-0x9] = uVar23;
                    puVar44[-0x8] = uVar24;
                    puVar44[-0x7] = uVar25;
                    puVar44[-0x6] = uVar26;
                    puVar44[-0x5] = uVar27;
                    puVar44[-0x4] = uVar28;
                    puVar44[-0x3] = uVar29;
                    puVar44[-0x2] = uVar30;
                    puVar44[-0x1] = uVar31;
                    _Size = _Size - 0x80;
                    puVar40 = puVar42;
                    puVar44 = puVar43;
                } while ((_Size & 0xffffff80) != 0x0);
                puVar40 = puVar42;
                puVar44 = puVar43;
                if (0x1f < _Size) {
                    do {
                        puVar42 = puVar40 + -0x8;
                        puVar43 = puVar44 + -0x8;
                        uVar45 = puVar40[-0x7];
                        uVar46 = puVar40[-0x6];
                        uVar47 = puVar40[-0x5];
                        uVar4 = puVar40[-0x4];
                        uVar5 = puVar40[-0x3];
                        uVar6 = puVar40[-0x2];
                        uVar7 = puVar40[-0x1];
                        *puVar43 = *puVar42;
                        puVar44[-0x7] = uVar45;
                        puVar44[-0x6] = uVar46;
                        puVar44[-0x5] = uVar47;
                        puVar44[-0x4] = uVar4;
                        puVar44[-0x3] = uVar5;
                        puVar44[-0x2] = uVar6;
                        puVar44[-0x1] = uVar7;
                        _Size = _Size - 0x20;
                        puVar40 = puVar42;
                        puVar44 = puVar43;
                    } while ((_Size & 0xffffffe0) != 0x0);
                }
            }
        }
        for (; (_Size & 0xfffffffc) != 0x0; _Size = _Size - 0x4) {
            puVar43 = puVar43 + -0x1;
            puVar42 = puVar42 + -0x1;
            *puVar43 = *puVar42;
        }
        for (; _Size != 0x0; _Size = _Size - 0x1) {
            puVar43 = (undefined4 *)((int)puVar43 - 0x1);
            puVar42 = (undefined4 *)((int)puVar42 + -0x1);
            *(undefined *)puVar43 = *(undefined *)puVar42;
        }
        return _Dst;
    }
    sVar36 = _Size;
    puVar42 = (undefined4 *)_Dst;
    if (_Size < 0x20) goto LAB_1000326b;
    if (_Size < 0x80) {
        if ((DAT_10015128 >> 0x1 & 0x1) != 0x0) {
LAB_1000323d:
            if (sVar36 == 0x0) {
                return _Dst;
            }
            for (uVar35 = sVar36 >> 0x5; uVar35 != 0x0; uVar35 = uVar35 - 0x1) {
                    // WARNING: Load size is inaccurate
                uVar45 = *(undefined4 *)((int)_Src + 0x4);
                uVar46 = *(undefined4 *)((int)_Src + 0x8);
                uVar47 = *(undefined4 *)((int)_Src + 0xc);
                uVar4 = *(undefined4 *)((int)_Src + 0x10);
                uVar5 = *(undefined4 *)((int)_Src + 0x14);
                uVar6 = *(undefined4 *)((int)_Src + 0x18);
                uVar7 = *(undefined4 *)((int)_Src + 0x1c);
                *puVar42 = *_Src;
                puVar42[0x1] = uVar45;
                puVar42[0x2] = uVar46;
                puVar42[0x3] = uVar47;
                puVar42[0x4] = uVar4;
                puVar42[0x5] = uVar5;
                puVar42[0x6] = uVar6;
                puVar42[0x7] = uVar7;
                _Src = (void *)((int)_Src + 0x20);
                puVar42 = puVar42 + 0x8;
            }
            goto LAB_1000326b;
        }
LAB_10002f97:
        uVar35 = (uint)_Dst & 0x3;
        while (uVar35 != 0x0) {
                    // WARNING: Load size is inaccurate
            *(undefined *)puVar42 = *_Src;
            _Size = _Size - 0x1;
            _Src = (void *)((int)_Src + 0x1);
            puVar42 = (undefined4 *)((int)puVar42 + 0x1);
            uVar35 = (uint)puVar42 & 0x3;
        }
    }
    else {
        puVar41 = (undefined *)_Dst;
        if ((DAT_10015ae0 >> 0x1 & 0x1) != 0x0) {
                    // WARNING: Load size is inaccurate
            for (; _Size != 0x0; _Size = _Size - 0x1) {
                *puVar41 = *_Src;
                _Src = (undefined *)((int)_Src + 0x1);
                puVar41 = puVar41 + 0x1;
            }
            return _Dst;
        }
        if (((((uint)_Dst ^ (uint)_Src) & 0xf) == 0x0) && ((DAT_10015128 >> 0x1 & 0x1) != 0x0)) {
            if (((uint)_Src & 0xf) != 0x0) {
                uVar37 = 0x10 - ((uint)_Src & 0xf);
                _Size = _Size - uVar37;
                for (uVar35 = uVar37 & 0x3; uVar35 != 0x0; uVar35 = uVar35 - 0x1) {
                    // WARNING: Load size is inaccurate
                    *(undefined *)puVar42 = *_Src;
                    _Src = (void *)((int)_Src + 0x1);
                    puVar42 = (undefined4 *)((int)puVar42 + 0x1);
                }
                for (uVar37 = uVar37 >> 0x2; uVar37 != 0x0; uVar37 = uVar37 - 0x1) {
                    // WARNING: Load size is inaccurate
                    *puVar42 = *_Src;
                    _Src = (void *)((int)_Src + 0x4);
                    puVar42 = puVar42 + 0x1;
                }
            }
            sVar36 = _Size & 0x7f;
            for (uVar35 = _Size >> 0x7; uVar35 != 0x0; uVar35 = uVar35 - 0x1) {
                    // WARNING: Load size is inaccurate
                uVar45 = *(undefined4 *)((int)_Src + 0x4);
                uVar46 = *(undefined4 *)((int)_Src + 0x8);
                uVar47 = *(undefined4 *)((int)_Src + 0xc);
                uVar4 = *(undefined4 *)((int)_Src + 0x10);
                uVar5 = *(undefined4 *)((int)_Src + 0x14);
                uVar6 = *(undefined4 *)((int)_Src + 0x18);
                uVar7 = *(undefined4 *)((int)_Src + 0x1c);
                uVar8 = *(undefined4 *)((int)_Src + 0x20);
                uVar9 = *(undefined4 *)((int)_Src + 0x24);
                uVar10 = *(undefined4 *)((int)_Src + 0x28);
                uVar11 = *(undefined4 *)((int)_Src + 0x2c);
                uVar12 = *(undefined4 *)((int)_Src + 0x30);
                uVar13 = *(undefined4 *)((int)_Src + 0x34);
                uVar14 = *(undefined4 *)((int)_Src + 0x38);
                uVar15 = *(undefined4 *)((int)_Src + 0x3c);
                *puVar42 = *_Src;
                puVar42[0x1] = uVar45;
                puVar42[0x2] = uVar46;
                puVar42[0x3] = uVar47;
                puVar42[0x4] = uVar4;
                puVar42[0x5] = uVar5;
                puVar42[0x6] = uVar6;
                puVar42[0x7] = uVar7;
                puVar42[0x8] = uVar8;
                puVar42[0x9] = uVar9;
                puVar42[0xa] = uVar10;
                puVar42[0xb] = uVar11;
                puVar42[0xc] = uVar12;
                puVar42[0xd] = uVar13;
                puVar42[0xe] = uVar14;
                puVar42[0xf] = uVar15;
                uVar45 = *(undefined4 *)((int)_Src + 0x44);
                uVar46 = *(undefined4 *)((int)_Src + 0x48);
                uVar47 = *(undefined4 *)((int)_Src + 0x4c);
                uVar4 = *(undefined4 *)((int)_Src + 0x50);
                uVar5 = *(undefined4 *)((int)_Src + 0x54);
                uVar6 = *(undefined4 *)((int)_Src + 0x58);
                uVar7 = *(undefined4 *)((int)_Src + 0x5c);
                uVar8 = *(undefined4 *)((int)_Src + 0x60);
                uVar9 = *(undefined4 *)((int)_Src + 0x64);
                uVar10 = *(undefined4 *)((int)_Src + 0x68);
                uVar11 = *(undefined4 *)((int)_Src + 0x6c);
                uVar12 = *(undefined4 *)((int)_Src + 0x70);
                uVar13 = *(undefined4 *)((int)_Src + 0x74);
                uVar14 = *(undefined4 *)((int)_Src + 0x78);
                uVar15 = *(undefined4 *)((int)_Src + 0x7c);
                puVar42[0x10] = *(undefined4 *)((int)_Src + 0x40);
                puVar42[0x11] = uVar45;
                puVar42[0x12] = uVar46;
                puVar42[0x13] = uVar47;
                puVar42[0x14] = uVar4;
                puVar42[0x15] = uVar5;
                puVar42[0x16] = uVar6;
                puVar42[0x17] = uVar7;
                puVar42[0x18] = uVar8;
                puVar42[0x19] = uVar9;
                puVar42[0x1a] = uVar10;
                puVar42[0x1b] = uVar11;
                puVar42[0x1c] = uVar12;
                puVar42[0x1d] = uVar13;
                puVar42[0x1e] = uVar14;
                puVar42[0x1f] = uVar15;
                _Src = (void *)((int)_Src + 0x80);
                puVar42 = puVar42 + 0x20;
            }
            goto LAB_1000323d;
        }
        if (((DAT_10015ae0 & 0x1) == 0x0) || (((uint)_Dst & 0x3) != 0x0)) goto LAB_10002f97;
        if (((uint)_Src & 0x3) == 0x0) {
            if (((uint)_Dst >> 0x2 & 0x1) != 0x0) {
                    // WARNING: Load size is inaccurate
                uVar45 = *_Src;
                _Size = _Size - 0x4;
                _Src = (void *)((int)_Src + 0x4);
                *(undefined4 *)_Dst = uVar45;
                _Dst = (void *)((int)_Dst + 0x4);
            }
            if (((uint)_Dst >> 0x3 & 0x1) != 0x0) {
                    // WARNING: Load size is inaccurate
                uVar1 = *_Src;
                _Size = _Size - 0x8;
                _Src = (void *)((int)_Src + 0x8);
                *(undefined8 *)_Dst = uVar1;
                _Dst = (void *)((int)_Dst + 0x8);
            }
            if (((uint)_Src & 0x7) == 0x0) {
                    // WARNING: Load size is inaccurate
                puVar33 = (undefined8 *)((int)_Src + -0x8);
                uVar45 = *_Src;
                uVar46 = *(undefined4 *)((int)_Src + 0x4);
                do {
                    puVar39 = puVar33;
                    uVar5 = *(undefined4 *)(puVar39 + 0x4);
                    uVar6 = *(undefined4 *)((int)puVar39 + 0x24);
                    _Size = _Size - 0x30;
                    auVar2 = *(undefined (*) [0x20])(puVar39 + 0x2);
                    uVar47 = *(undefined4 *)(puVar39 + 0x7);
                    uVar4 = *(undefined4 *)((int)puVar39 + 0x3c);
                    auVar3 = *(undefined (*) [0x20])(puVar39 + 0x4);
                    *(undefined4 *)((int)_Dst + 0x8) = uVar45;
                    *(undefined4 *)((int)_Dst + 0xc) = uVar46;
                    *(undefined4 *)((int)_Dst + 0x10) = uVar5;
                    *(undefined4 *)((int)_Dst + 0x14) = uVar6;
                    *(undefined (*) [0x10])((int)_Dst + 0x10) = SUB3216(auVar2 >> 0x40,0x0);
                    *(undefined (*) [0x10])((int)_Dst + 0x20) = SUB3216(auVar3 >> 0x40,0x0);
                    _Dst = (void *)((int)_Dst + 0x30);
                    puVar33 = puVar39 + 0x6;
                    uVar45 = uVar47;
                    uVar46 = uVar4;
                } while (0x2f < _Size);
                puVar39 = puVar39 + 0x7;
            }
            else if (((uint)_Src >> 0x3 & 0x1) == 0x0) {
                    // WARNING: Load size is inaccurate
                iVar32 = (int)_Src + -0x4;
                uVar45 = *_Src;
                uVar46 = *(undefined4 *)((int)_Src + 0x4);
                uVar47 = *(undefined4 *)((int)_Src + 0x8);
                do {
                    iVar38 = iVar32;
                    uVar7 = *(undefined4 *)(iVar38 + 0x20);
                    _Size = _Size - 0x30;
                    auVar2 = *(undefined (*) [0x20])(iVar38 + 0x10);
                    uVar4 = *(undefined4 *)(iVar38 + 0x34);
                    uVar5 = *(undefined4 *)(iVar38 + 0x38);
                    uVar6 = *(undefined4 *)(iVar38 + 0x3c);
                    auVar3 = *(undefined (*) [0x20])(iVar38 + 0x20);
                    *(undefined4 *)((int)_Dst + 0x4) = uVar45;
                    *(undefined4 *)((int)_Dst + 0x8) = uVar46;
                    *(undefined4 *)((int)_Dst + 0xc) = uVar47;
                    *(undefined4 *)((int)_Dst + 0x10) = uVar7;
                    *(undefined (*) [0x10])((int)_Dst + 0x10) = SUB3216(auVar2 >> 0x20,0x0);
                    *(undefined (*) [0x10])((int)_Dst + 0x20) = SUB3216(auVar3 >> 0x20,0x0);
                    _Dst = (void *)((int)_Dst + 0x30);
                    iVar32 = iVar38 + 0x30;
                    uVar45 = uVar4;
                    uVar46 = uVar5;
                    uVar47 = uVar6;
                } while (0x2f < _Size);
                puVar39 = (undefined8 *)(iVar38 + 0x34);
            }
            else {
                    // WARNING: Load size is inaccurate
                iVar32 = (int)_Src + -0xc;
                uVar45 = *_Src;
                do {
                    iVar38 = iVar32;
                    uVar47 = *(undefined4 *)(iVar38 + 0x20);
                    uVar4 = *(undefined4 *)(iVar38 + 0x24);
                    uVar5 = *(undefined4 *)(iVar38 + 0x28);
                    _Size = _Size - 0x30;
                    auVar2 = *(undefined (*) [0x20])(iVar38 + 0x10);
                    uVar46 = *(undefined4 *)(iVar38 + 0x3c);
                    auVar3 = *(undefined (*) [0x20])(iVar38 + 0x20);
                    *(undefined4 *)((int)_Dst + 0xc) = uVar45;
                    *(undefined4 *)((int)_Dst + 0x10) = uVar47;
                    *(undefined4 *)((int)_Dst + 0x14) = uVar4;
                    *(undefined4 *)((int)_Dst + 0x18) = uVar5;
                    *(undefined (*) [0x10])((int)_Dst + 0x10) = SUB3216(auVar2 >> 0x60,0x0);
                    *(undefined (*) [0x10])((int)_Dst + 0x20) = SUB3216(auVar3 >> 0x60,0x0);
                    _Dst = (void *)((int)_Dst + 0x30);
                    iVar32 = iVar38 + 0x30;
                    uVar45 = uVar46;
                } while (0x2f < _Size);
                puVar39 = (undefined8 *)(iVar38 + 0x3c);
            }
            for (; 0xf < _Size; _Size = _Size - 0x10) {
                uVar45 = *(undefined4 *)puVar39;
                uVar46 = *(undefined4 *)((int)puVar39 + 0x4);
                uVar47 = *(undefined4 *)(puVar39 + 0x1);
                uVar4 = *(undefined4 *)((int)puVar39 + 0xc);
                puVar39 = puVar39 + 0x2;
                *(undefined4 *)_Dst = uVar45;
                *(undefined4 *)((int)_Dst + 0x4) = uVar46;
                *(undefined4 *)((int)_Dst + 0x8) = uVar47;
                *(undefined4 *)((int)_Dst + 0xc) = uVar4;
                _Dst = (void *)((int)_Dst + 0x10);
            }
            if ((_Size >> 0x2 & 0x1) != 0x0) {
                uVar45 = *(undefined4 *)puVar39;
                _Size = _Size - 0x4;
                puVar39 = (undefined8 *)((int)puVar39 + 0x4);
                *(undefined4 *)_Dst = uVar45;
                _Dst = (void *)((int)_Dst + 0x4);
            }
            if ((_Size >> 0x3 & 0x1) != 0x0) {
                _Size = _Size - 0x8;
                *(undefined8 *)_Dst = *puVar39;
            }
                    // WARNING: Could not recover jumptable at 0x10002f95. Too many branches
                    // WARNING: Treating indirect jump as call
            pvVar34 = (void *)(*(code *)(&switchD_10002fc5::switchdataD_10002fd4)[_Size])();
            return pvVar34;
        }
    }
    sVar36 = _Size;
    if (0x1f < _Size) {
                    // WARNING: Load size is inaccurate
        for (uVar35 = _Size >> 0x2; uVar35 != 0x0; uVar35 = uVar35 - 0x1) {
            *puVar42 = *_Src;
            _Src = (undefined4 *)((int)_Src + 0x4);
            puVar42 = puVar42 + 0x1;
        }
        switch(_Size & 0x3) {
        case 0x0:
            return _Dst;
        case 0x1:
                    // WARNING: Load size is inaccurate
            *(undefined *)puVar42 = *_Src;
            return _Dst;
        case 0x2:
                    // WARNING: Load size is inaccurate
            *(undefined *)puVar42 = *_Src;
            *(undefined *)((int)puVar42 + 0x1) = *(undefined *)((int)_Src + 0x1);
            return _Dst;
        case 0x3:
                    // WARNING: Load size is inaccurate
            *(undefined *)puVar42 = *_Src;
            *(undefined *)((int)puVar42 + 0x1) = *(undefined *)((int)_Src + 0x1);
            *(undefined *)((int)puVar42 + 0x2) = *(undefined *)((int)_Src + 0x2);
            return _Dst;
        }
    }
LAB_1000326b:
    if ((sVar36 & 0x1f) != 0x0) {
        for (uVar35 = (sVar36 & 0x1f) >> 0x2; uVar35 != 0x0; uVar35 = uVar35 - 0x1) {
                    // WARNING: Load size is inaccurate
            *puVar42 = *_Src;
            puVar42 = puVar42 + 0x1;
            _Src = (void *)((int)_Src + 0x4);
        }
        for (uVar35 = sVar36 & 0x3; uVar35 != 0x0; uVar35 = uVar35 - 0x1) {
                    // WARNING: Load size is inaccurate
            *(undefined *)puVar42 = *_Src;
            _Src = (void *)((int)_Src + 0x1);
            puVar42 = (undefined4 *)((int)puVar42 + 0x1);
        }
    }
    return _Dst;
}



// Library Function - Single Match
//  struct HINSTANCE__ * __cdecl try_get_first_available_module(enum `anonymous namespace'::module_id const * const,enum `anonymous namespace'::module_id const * const)
// 
// Library: Visual Studio 2019 Release

HINSTANCE__ * __cdecl try_get_first_available_module(module_id *param_1,module_id *param_2)

{
    HINSTANCE__ **ppHVar1;
    HINSTANCE__ *pHVar2;
    LPCWSTR lpLibFileName;
    HMODULE hLibModule;
    DWORD DVar3;
    int iVar4;
    
    do {
        if (param_1 == param_2) {
            return NULL;
        }
        ppHVar1 = (HINSTANCE__ **)(&DAT_10015e88 + *param_1 * 0x4);
        pHVar2 = *ppHVar1;
        if (pHVar2 == NULL) {
            lpLibFileName = (LPCWSTR)(&PTR_u_api_ms_win_core_fibers_l1_1_1_1000eb10)[*param_1];
            hLibModule = LoadLibraryExW(lpLibFileName,NULL,0x800);
            if ((hLibModule != NULL) ||
               (((DVar3 = GetLastError(), DVar3 == 0x57 && (iVar4 = _wcsncmp(lpLibFileName,L"api-ms-",0x7), iVar4 != 0x0)) && (hLibModule = LoadLibraryExW(lpLibFileName,NULL,0x0), hLibModule != NULL))
               )) {
                pHVar2 = *ppHVar1;
                *ppHVar1 = hLibModule;
                if (pHVar2 == NULL) {
                    return hLibModule;
                }
                FreeLibrary(hLibModule);
                return hLibModule;
            }
            *ppHVar1 = (HINSTANCE__ *)0xffffffff;
        }
        else if (pHVar2 != (HINSTANCE__ *)0xffffffff) {
            return pHVar2;
        }
        param_1 = param_1 + 0x1;
    } while( true );
}



// Library Function - Single Match
//  void * __cdecl try_get_function(enum `anonymous namespace'::function_id,char const * const,enum A0x9d0f8d90::module_id const * const,enum A0x9d0f8d90::module_id const * const)
// 
// Library: Visual Studio 2019 Release

void * __cdecl try_get_function(function_id param_1,char *param_2,module_id *param_3,module_id *param_4)

{
    FARPROC *ppFVar1;
    HINSTANCE__ *hModule;
    FARPROC pFVar2;
    
    ppFVar1 = (FARPROC *)(&DAT_10015e94 + param_1 * 0x4);
    pFVar2 = *ppFVar1;
    if (pFVar2 != (FARPROC)0xffffffff) {
        if (pFVar2 != NULL) {
            return pFVar2;
        }
        hModule = try_get_first_available_module(param_3,param_4);
        if ((hModule != NULL) && (pFVar2 = GetProcAddress(hModule,param_2), pFVar2 != NULL)) {
            *ppFVar1 = pFVar2;
            return pFVar2;
        }
        *ppFVar1 = (FARPROC)0xffffffff;
    }
    return NULL;
}



// Library Function - Single Match
//  ___vcrt_FlsAlloc
// 
// Library: Visual Studio 2019 Release

void __cdecl ___vcrt_FlsAlloc(undefined4 param_1)

{
    code *pcVar1;
    
    pcVar1 = (code *)try_get_function(0x0,"FlsAlloc",(module_id *)&DAT_1000ebb8,(module_id *)"FlsAlloc");
    if (pcVar1 != NULL) {
        _guard_check_icall();
        (*pcVar1)(param_1);
        return;
    }
                    // WARNING: Could not recover jumptable at 0x100033fc. Too many branches
                    // WARNING: Treating indirect jump as call
    TlsAlloc();
    return;
}



// Library Function - Single Match
//  ___vcrt_FlsFree
// 
// Library: Visual Studio 2019 Release

void __cdecl ___vcrt_FlsFree(DWORD param_1)

{
    code *pcVar1;
    
    pcVar1 = (code *)try_get_function(0x1,"FlsFree",(module_id *)&DAT_1000ebcc,(module_id *)"FlsFree");
    if (pcVar1 == NULL) {
        TlsFree(param_1);
    }
    else {
        _guard_check_icall();
        (*pcVar1)();
    }
    return;
}



// Library Function - Single Match
//  ___vcrt_FlsGetValue
// 
// Library: Visual Studio 2019 Release

void __cdecl ___vcrt_FlsGetValue(DWORD param_1)

{
    code *pcVar1;
    
    pcVar1 = (code *)try_get_function(0x2,"FlsGetValue",(module_id *)&DAT_1000ebdc,(module_id *)"FlsGetValue");
    if (pcVar1 == NULL) {
        TlsGetValue(param_1);
    }
    else {
        _guard_check_icall();
        (*pcVar1)();
    }
    return;
}



// Library Function - Single Match
//  ___vcrt_FlsSetValue
// 
// Library: Visual Studio 2019 Release

void __cdecl ___vcrt_FlsSetValue(DWORD param_1,LPVOID param_2)

{
    code *pcVar1;
    
    pcVar1 = (code *)try_get_function(0x3,"FlsSetValue",(module_id *)&DAT_1000ebf0,(module_id *)"FlsSetValue");
    if (pcVar1 == NULL) {
        TlsSetValue(param_1,param_2);
    }
    else {
        _guard_check_icall();
        (*pcVar1)();
    }
    return;
}



// Library Function - Single Match
//  ___vcrt_InitializeCriticalSectionEx
// 
// Library: Visual Studio 2019 Release

void __cdecl ___vcrt_InitializeCriticalSectionEx(LPCRITICAL_SECTION param_1,DWORD param_2,undefined4 param_3)

{
    code *pcVar1;
    
    pcVar1 = (code *)try_get_function(0x4,"InitializeCriticalSectionEx",(module_id *)&DAT_1000ec04,(module_id *)"InitializeCriticalSectionEx");
    if (pcVar1 == NULL) {
        InitializeCriticalSectionAndSpinCount(param_1,param_2);
    }
    else {
        _guard_check_icall();
        (*pcVar1)(param_1,param_2,param_3);
    }
    return;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  int __cdecl BuildCatchObjectHelperInternal<class __FrameHandler3>(struct EHExceptionRecord *,void *,struct _s_HandlerType const *,struct _s_CatchableType const *)
// 
// Library: Visual Studio 2019 Release

int __cdecl BuildCatchObjectHelperInternal_class___FrameHandler3_(EHExceptionRecord *param_1,void *param_2,_s_HandlerType *param_3,_s_CatchableType *param_4)

{
    uint uVar1;
    code *pcVar2;
    int iVar3;
    void *_Src;
    int iVar4;
    undefined4 *in_FS_OFFSET;
    size_t _Size;
    undefined4 local_14;
    
    pcVar2 = DAT_10015e04;
    iVar4 = 0x0;
    if (((param_3->pType == NULL) || (*(char *)&param_3->pType[0x1].pVFTable == '\0')) || ((param_3->dispCatchObj == 0x0 && (-0x1 < (int)param_3->adjectives)))) {
        iVar4 = 0x0;
        goto LAB_10003625;
    }
    uVar1 = param_3->adjectives;
    if (-0x1 < (int)uVar1) {
        param_2 = (void *)((int)param_2 + param_3->dispCatchObj + 0xc);
    }
    if ((((char)uVar1 < '\0') && (((byte)*param_4 & 0x10) != 0x0)) && (DAT_10015e04 != NULL)) {
        _guard_check_icall();
        iVar3 = (*pcVar2)();
LAB_10003574:
        if ((iVar3 == 0x0) || ((int *)param_2 == NULL)) {
LAB_10003635:
            _abort();
            pcVar2 = (code *)swi(0x3);
            iVar4 = (*pcVar2)();
            return iVar4;
        }
        *(int *)param_2 = iVar3;
    }
    else {
        if ((uVar1 & 0x8) != 0x0) {
            iVar3 = *(int *)(param_1 + 0x18);
            goto LAB_10003574;
        }
        if (((byte)*param_4 & 0x1) == 0x0) {
            iVar3 = *(int *)(param_1 + 0x18);
            if (*(int *)(param_4 + 0x18) == 0x0) {
                if ((iVar3 != 0x0) && ((int *)param_2 != NULL)) {
                    _Size = *(size_t *)(param_4 + 0x14);
                    _Src = (void *)___AdjustPointer(iVar3,(int *)(param_4 + 0x8));
                    FID_conflict__memcpy(param_2,_Src,_Size);
                    goto LAB_10003625;
                }
                goto LAB_10003635;
            }
            if ((iVar3 == 0x0) || ((int *)param_2 == NULL)) goto LAB_10003635;
            iVar4 = (((byte)*param_4 & 0x4) != 0x0) + 0x1;
            goto LAB_10003625;
        }
        if ((*(int *)(param_1 + 0x18) == 0x0) || ((int *)param_2 == NULL)) goto LAB_10003635;
        FID_conflict__memcpy(param_2,*(void **)(param_1 + 0x18),*(size_t *)(param_4 + 0x14));
                    // WARNING: Load size is inaccurate
        if ((*(int *)(param_4 + 0x14) != 0x4) || (*param_2 == 0x0)) goto LAB_10003625;
                    // WARNING: Load size is inaccurate
        iVar3 = *param_2;
    }
    iVar3 = ___AdjustPointer(iVar3,(int *)(param_4 + 0x8));
    *(int *)param_2 = iVar3;
LAB_10003625:
    *in_FS_OFFSET = local_14;
    return iVar4;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  void __cdecl BuildCatchObjectInternal<class __FrameHandler3>(struct EHExceptionRecord *,void *,struct _s_HandlerType const *,struct _s_CatchableType const *)
// 
// Library: Visual Studio 2019 Release

void __cdecl BuildCatchObjectInternal_class___FrameHandler3_(EHExceptionRecord *param_1,void *param_2,_s_HandlerType *param_3,_s_CatchableType *param_4)

{
    int iVar1;
    void *pvVar2;
    void *pvVar3;
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    pvVar3 = param_2;
    if (-0x1 < (int)param_3->adjectives) {
        pvVar3 = (void *)((int)param_2 + param_3->dispCatchObj + 0xc);
    }
    iVar1 = BuildCatchObjectHelperInternal_class___FrameHandler3_(param_1,param_2,param_3,param_4);
    if (iVar1 == 0x1) {
        pvVar2 = (void *)___AdjustPointer(*(int *)(param_1 + 0x18),(int *)(param_4 + 0x8));
        _CallMemberFunction1(pvVar3,*(void **)(param_4 + 0x18),pvVar2);
    }
    else if (iVar1 == 0x2) {
        pvVar2 = (void *)___AdjustPointer(*(int *)(param_1 + 0x18),(int *)(param_4 + 0x8));
        _CallMemberFunction2(pvVar3,*(void **)(param_4 + 0x18),pvVar2,0x1);
    }
    *in_FS_OFFSET = local_14;
    return;
}



// Library Function - Single Match
//  void __cdecl CatchIt<class __FrameHandler3>(struct EHExceptionRecord *,struct EHRegistrationNode *,struct _CONTEXT *,void *,struct _s_FuncInfo const *,struct _s_HandlerType const *,struct
// _s_CatchableType const *,struct _s_TryBlockMapEntry const *,int,struct EHRegistrationNode *,unsigned char,unsigned char)
// 
// Library: Visual Studio 2019 Release

void __cdecl
CatchIt_class___FrameHandler3_
          (EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3,void *param_4,_s_FuncInfo *param_5,_s_HandlerType *param_6,_s_CatchableType *param_7,_s_TryBlockMapEntry *param_8,
          int param_9,EHRegistrationNode *param_10,uchar param_11,uchar param_12)

{
    void *pvVar1;
    
    if (param_7 != NULL) {
        BuildCatchObjectInternal_class___FrameHandler3_(param_1,param_2,param_6,param_7);
    }
    if (param_10 == NULL) {
        param_10 = param_2;
    }
    _UnwindNestedFrames(param_10,param_1);
    __FrameHandler3::FrameUnwindToState(param_2,param_4,param_5,param_8->tryLow);
    __FrameHandler3::SetState(param_2,param_5,param_8->tryHigh + 0x1);
    pvVar1 = CallCatchBlock(param_1,param_2,param_3,param_5,param_6->addressOfHandler,param_9,0x100);
    if (pvVar1 != NULL) {
        _JumpToContinuation(pvVar1,param_2);
    }
    return;
}



// WARNING: Could not reconcile some variable overlaps

void __cdecl FUN_10003754(int *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3,_s_FuncInfo *param_4,_s_FuncInfo *param_5,uchar param_6,int param_7,EHRegistrationNode *param_8)

{
    code *pcVar1;
    _s_FuncInfo *p_Var2;
    void *pvVar3;
    uchar uVar4;
    bool bVar5;
    int iVar6;
    undefined4 uVar7;
    __ehstate_t *p_Var8;
    int iVar9;
    _s_TryBlockMapEntry *p_Var10;
    _s_CatchableType **pp_Var11;
    _s_TryBlockMapEntry local_68;
    _s_HandlerType local_54;
    int *local_44;
    _s_FuncInfo *local_40 [0x2];
    _s_FuncInfo *local_38;
    _s_FuncInfo *local_34;
    undefined4 local_30;
    int *local_2c;
    int local_28;
    _s_CatchableType **local_24;
    int local_20;
    undefined4 local_1c;
    HandlerType *local_18;
    int local_14;
    _s_FuncInfo *local_10;
    void *local_c;
    _CONTEXT *local_8;
    
    local_14 = 0x0;
    local_1c = local_1c & 0xffffff00;
    local_c = (void *)__FrameHandler3::GetCurrentState(param_2,param_4,param_5);
    if (((int)local_c < -0x1) || (param_5->maxState <= (int)local_c)) goto LAB_10003af8;
    if (((*param_1 != -0x1f928c9d) || (param_1[0x4] != 0x3)) || ((((param_1[0x5] != 0x19930520 && (param_1[0x5] != 0x19930521)) && (param_1[0x5] != 0x19930522)) || (param_1[0x7] != 0x0)))) {
        local_8 = param_3;
        goto LAB_100038a2;
    }
    iVar6 = ___vcrt_getptd();
    if (*(int *)(iVar6 + 0x10) == 0x0) {
        return;
    }
    iVar6 = ___vcrt_getptd();
    param_1 = *(int **)(iVar6 + 0x10);
    iVar6 = ___vcrt_getptd();
    local_1c = CONCAT31(local_1c._1_3_,0x1);
    local_8 = *(_CONTEXT **)(iVar6 + 0x14);
    if ((param_1 == NULL) ||
       ((((*param_1 == -0x1f928c9d && (param_1[0x4] == 0x3)) && ((param_1[0x5] == 0x19930520 || ((param_1[0x5] == 0x19930521 || (param_1[0x5] == 0x19930522)))))) && (param_1[0x7] == 0x0))))
    goto LAB_10003af8;
    iVar6 = ___vcrt_getptd();
    if (*(int *)(iVar6 + 0x1c) == 0x0) {
LAB_100038a2:
        local_34 = param_5;
        local_30 = 0x0;
        if (((*param_1 == -0x1f928c9d) && (param_1[0x4] == 0x3)) && ((param_1[0x5] == 0x19930520 || ((param_1[0x5] == 0x19930521 || (param_1[0x5] == 0x19930522)))))) {
            if (param_5->nTryBlocks != 0x0) {
                __FrameHandler3::GetRangeOfTrysToCheck((TryBlockMap *)&local_44,(int)&local_34,local_c,param_4,(int)param_5);
                local_2c = local_44;
                local_10 = local_40[0];
                if (local_40[0] < local_38) {
                    local_20 = (int)local_40[0] * 0x14;
                    do {
                        pvVar3 = local_c;
                        p_Var8 = (__ehstate_t *)(*(int *)(*local_2c + 0x10) + local_20);
                        p_Var10 = &local_68;
                        local_10 = local_40[0];
                        for (iVar6 = 0x5; iVar6 != 0x0; iVar6 = iVar6 + -0x1) {
                            p_Var10->tryLow = *p_Var8;
                            p_Var8 = p_Var8 + 0x1;
                            p_Var10 = (_s_TryBlockMapEntry *)&p_Var10->tryHigh;
                        }
                        if (((local_68.tryLow <= (int)pvVar3) && ((int)pvVar3 <= local_68.tryHigh)) && (local_14 = 0x0, local_68.nCatches != 0x0)) {
                            iVar6 = **(int **)(param_1[0x7] + 0xc);
                            local_24 = (_s_CatchableType **)(*(int **)(param_1[0x7] + 0xc) + 0x1);
                            local_18 = local_68.pHandlerArray;
                            local_28 = iVar6;
                            do {
                                local_54.adjectives = local_18->adjectives;
                                local_54.pType = local_18->pType;
                                local_54.dispCatchObj = local_18->dispCatchObj;
                                local_54.addressOfHandler = local_18->addressOfHandler;
                                iVar9 = iVar6;
                                pp_Var11 = local_24;
                                local_40[0] = local_10;
                                for (; local_10 = local_40[0], 0x0 < iVar9; iVar9 = iVar9 + -0x1) {
                                    iVar6 = TypeMatchHelper__((byte *)&local_54,(byte *)*pp_Var11,(byte *)param_1[0x7]);
                                    if (iVar6 != 0x0) {
                                        CatchIt_class___FrameHandler3_
                                                  ((EHExceptionRecord *)param_1,param_2,local_8,param_4,param_5,&local_54,*pp_Var11,&local_68,param_7,param_8,(uchar)local_1c,param_6);
                                        local_40[0] = local_10;
                                        goto LAB_100039de;
                                    }
                                    pp_Var11 = pp_Var11 + 0x1;
                                    iVar6 = local_28;
                                    local_40[0] = local_10;
                                }
                                local_14 = local_14 + 0x1;
                                local_18 = local_18 + 0x1;
                            } while (local_14 != local_68.nCatches);
                        }
LAB_100039de:
                        local_40[0] = (_s_FuncInfo *)((int)&local_40[0]->magicNumber_and_bbtFlags + 0x1);
                        local_20 = local_20 + 0x14;
                        local_10 = local_40[0];
                    } while (local_40[0] < local_38);
                }
            }
            if (param_6 != '\0') {
                ___DestructExceptionObject(param_1);
            }
            if ((0x19930520 < (param_5->magicNumber_and_bbtFlags & 0x1fffffff)) && ((param_5->pESTypeList != NULL || ((((uint)param_5->EHFlags >> 0x2 & 0x1) != 0x0 && (param_7 == 0x0)))))) {
                if (((uint)param_5->EHFlags >> 0x2 & 0x1) != 0x0) {
                    iVar6 = ___vcrt_getptd();
                    *(int **)(iVar6 + 0x10) = param_1;
                    iVar6 = ___vcrt_getptd();
                    *(_CONTEXT **)(iVar6 + 0x14) = local_8;
                    goto LAB_10003a97;
                }
                uVar4 = IsInExceptionSpec((EHExceptionRecord *)param_1,param_5->pESTypeList);
                if (uVar4 == '\0') goto LAB_10003abc;
            }
        }
        else if (param_5->nTryBlocks != 0x0) {
            if (param_6 != '\0') goto LAB_10003af8;
            FindHandlerForForeignException_class___FrameHandler3_((EHExceptionRecord *)param_1,param_2,local_8,param_4,param_5,(int)local_c,param_7,param_8);
        }
        iVar6 = ___vcrt_getptd();
        if (*(int *)(iVar6 + 0x1c) == 0x0) {
            return;
        }
    }
    else {
        iVar6 = ___vcrt_getptd();
        local_10 = *(_s_FuncInfo **)(iVar6 + 0x1c);
        iVar6 = ___vcrt_getptd();
        *(undefined4 *)(iVar6 + 0x1c) = 0x0;
        uVar4 = IsInExceptionSpec((EHExceptionRecord *)param_1,(_s_ESTypeList *)local_10);
        p_Var2 = local_10;
        if (uVar4 != '\0') goto LAB_100038a2;
        param_8 = NULL;
        param_5 = p_Var2;
        if (0x0 < (int)local_10->magicNumber_and_bbtFlags) {
            do {
                bVar5 = type_info::operator__(*(type_info **)(param_8 + p_Var2->maxState + 0x4),(type_info *)&class_std__bad_exception_RTTI_Type_Descriptor);
                if (bVar5) goto LAB_10003a9c;
                param_8 = param_8 + 0x10;
                local_14 = local_14 + 0x1;
            } while (local_14 < (int)p_Var2->magicNumber_and_bbtFlags);
        }
LAB_10003a97:
        _terminate();
LAB_10003a9c:
        ___DestructExceptionObject(param_1);
        FUN_10003ddf(local_40);
        __CxxThrowException_8((int *)local_40,&DAT_100136cc);
LAB_10003abc:
        iVar6 = ___vcrt_getptd();
        *(int **)(iVar6 + 0x10) = param_1;
        iVar6 = ___vcrt_getptd();
        *(_CONTEXT **)(iVar6 + 0x14) = local_8;
        if (param_8 == NULL) {
            param_8 = param_2;
        }
        _UnwindNestedFrames(param_8,(EHExceptionRecord *)param_1);
        __FrameHandler3::FrameUnwindToEmptyState(param_2,param_4,param_5);
        uVar7 = FUN_1000428a((int)param_5);
        FUN_10004044(uVar7);
    }
LAB_10003af8:
    _abort();
    pcVar1 = (code *)swi(0x3);
    (*pcVar1)();
    return;
}



// Library Function - Single Match
//  void __cdecl FindHandlerForForeignException<class __FrameHandler3>(struct EHExceptionRecord *,struct EHRegistrationNode *,struct _CONTEXT *,void *,struct _s_FuncInfo const *,int,int,struct
// EHRegistrationNode *)
// 
// Library: Visual Studio 2019 Release

void __cdecl
FindHandlerForForeignException_class___FrameHandler3_
          (EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3,void *param_4,_s_FuncInfo *param_5,int param_6,int param_7,EHRegistrationNode *param_8)

{
    code *pcVar1;
    int iVar2;
    PVOID pvVar3;
    _s_HandlerType *p_Var4;
    __ehstate_t *p_Var5;
    _s_TryBlockMapEntry *p_Var6;
    _s_TryBlockMapEntry local_3c;
    int *local_28;
    uint local_24;
    uint local_1c;
    _s_FuncInfo *local_18;
    undefined4 local_14;
    int *local_10;
    int local_c;
    uint local_8;
    
    if (*(int *)param_1 != -0x7ffffffd) {
        iVar2 = ___vcrt_getptd();
        if (*(int *)(iVar2 + 0x8) != 0x0) {
            pvVar3 = EncodePointer(NULL);
            iVar2 = ___vcrt_getptd();
            if ((((*(PVOID *)(iVar2 + 0x8) != pvVar3) && (*(int *)param_1 != -0x1fbcb0b3)) && (*(int *)param_1 != -0x1fbcbcae)) &&
               (iVar2 = FUN_10002a80((int *)param_1,(undefined4 *)param_2,param_3,param_4,param_5,param_7,param_8), iVar2 != 0x0)) {
                return;
            }
        }
        local_18 = param_5;
        local_14 = 0x0;
        if (param_5->nTryBlocks == 0x0) {
            _abort();
            pcVar1 = (code *)swi(0x3);
            (*pcVar1)();
            return;
        }
        __FrameHandler3::GetRangeOfTrysToCheck((TryBlockMap *)&local_28,(int)&local_18,(void *)param_6,(_s_FuncInfo *)param_4,(int)param_5);
        local_10 = local_28;
        if (local_24 < local_1c) {
            local_c = local_24 * 0x14;
            do {
                p_Var5 = (__ehstate_t *)(*(int *)(*local_10 + 0x10) + local_c);
                p_Var6 = &local_3c;
                local_8 = local_24;
                for (iVar2 = 0x5; iVar2 != 0x0; iVar2 = iVar2 + -0x1) {
                    p_Var6->tryLow = *p_Var5;
                    p_Var5 = p_Var5 + 0x1;
                    p_Var6 = (_s_TryBlockMapEntry *)&p_Var6->tryHigh;
                }
                if ((local_3c.tryLow <= param_6) && (param_6 <= local_3c.tryHigh)) {
                    p_Var4 = local_3c.pHandlerArray + local_3c.nCatches + -0x1;
                    if (((p_Var4->pType == NULL) || (*(char *)&p_Var4->pType[0x1].pVFTable == '\0')) && ((*(byte *)&p_Var4->adjectives & 0x40) == 0x0)) {
                        CatchIt_class___FrameHandler3_(param_1,param_2,param_3,param_4,param_5,p_Var4,NULL,&local_3c,param_7,param_8,'\x01','\0');
                        local_24 = local_8;
                    }
                }
                local_24 = local_24 + 0x1;
                local_c = local_c + 0x14;
            } while (local_24 < local_1c);
        }
    }
    return;
}



// Library Function - Multiple Matches With Same Base Name
//  int __cdecl TypeMatchHelper<struct _s_HandlerType const >(struct _s_HandlerType const *,struct _s_CatchableType const *,struct _s_ThrowInfo const *)
//  int __cdecl TypeMatchHelper<class __FrameHandler3>(struct _s_HandlerType const *,struct _s_CatchableType const *,struct _s_ThrowInfo const *)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

undefined4 __cdecl TypeMatchHelper__(byte *param_1,byte *param_2,byte *param_3)

{
    byte bVar1;
    int iVar2;
    byte *pbVar3;
    uint uVar4;
    byte *pbVar5;
    undefined4 uVar6;
    bool bVar7;
    
    iVar2 = *(int *)(param_1 + 0x4);
    if (((iVar2 == 0x0) || (pbVar5 = (byte *)(iVar2 + 0x8), *pbVar5 == 0x0)) || (((*param_1 & 0x80) != 0x0 && ((*param_2 & 0x10) != 0x0)))) {
        uVar6 = 0x1;
    }
    else {
        uVar6 = 0x0;
        if (iVar2 != *(int *)(param_2 + 0x4)) {
            pbVar3 = (byte *)(*(int *)(param_2 + 0x4) + 0x8);
            do {
                bVar1 = *pbVar5;
                bVar7 = bVar1 < *pbVar3;
                if (bVar1 != *pbVar3) {
LAB_10003c85:
                    uVar4 = -(uint)bVar7 | 0x1;
                    goto LAB_10003c8a;
                }
                if (bVar1 == 0x0) break;
                bVar1 = pbVar5[0x1];
                bVar7 = bVar1 < pbVar3[0x1];
                if (bVar1 != pbVar3[0x1]) goto LAB_10003c85;
                pbVar5 = pbVar5 + 0x2;
                pbVar3 = pbVar3 + 0x2;
            } while (bVar1 != 0x0);
            uVar4 = 0x0;
LAB_10003c8a:
            if (uVar4 != 0x0) {
                return 0x0;
            }
        }
        if ((((*param_2 & 0x2) == 0x0) || ((*param_1 & 0x8) != 0x0)) && ((((*param_3 & 0x1) == 0x0 || ((*param_1 & 0x1) != 0x0)) && (((*param_3 & 0x2) == 0x0 || ((*param_1 & 0x2) != 0x0)))))) {
            uVar6 = 0x1;
        }
    }
    return uVar6;
}



// Library Function - Single Match
//  enum _EXCEPTION_DISPOSITION __cdecl __InternalCxxFrameHandler<class __FrameHandler3>(struct EHExceptionRecord *,struct EHRegistrationNode *,struct _CONTEXT *,void *,struct _s_FuncInfo const
// *,int,struct EHRegistrationNode *,unsigned char)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

_EXCEPTION_DISPOSITION __cdecl
__InternalCxxFrameHandler_class___FrameHandler3_
          (EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3,void *param_4,_s_FuncInfo *param_5,int param_6,EHRegistrationNode *param_7,uchar param_8)

{
    code *pcVar1;
    int iVar2;
    uint uVar3;
    _EXCEPTION_DISPOSITION _Var4;
    
    ___except_validate_context_record((int)param_3);
    iVar2 = ___vcrt_getptd();
    if ((((*(int *)(iVar2 + 0x20) != 0x0) || (*(int *)param_1 == -0x1f928c9d)) || (*(int *)param_1 == -0x7fffffda)) ||
       (((param_5->magicNumber_and_bbtFlags & 0x1fffffff) < 0x19930522 || ((*(byte *)&param_5->EHFlags & 0x1) == 0x0)))) {
        if (((byte)param_1[0x4] & 0x66) == 0x0) {
            if (((param_5->nTryBlocks != 0x0) || ((uVar3 = param_5->magicNumber_and_bbtFlags & 0x1fffffff, 0x19930520 < uVar3 && (param_5->pESTypeList != NULL)))) ||
               ((0x19930521 < uVar3 && (((uint)param_5->EHFlags >> 0x2 & 0x1) != 0x0)))) {
                if ((((*(int *)param_1 == -0x1f928c9d) && (0x2 < *(uint *)(param_1 + 0x10))) && (0x19930522 < *(uint *)(param_1 + 0x14))) &&
                   (pcVar1 = *(code **)(*(int *)(param_1 + 0x1c) + 0x8), pcVar1 != NULL)) {
                    uVar3 = (uint)param_8;
                    _guard_check_icall();
                    _Var4 = (*pcVar1)(param_1,param_2,param_3,param_4,param_5,param_6,param_7,uVar3);
                    return _Var4;
                }
                FUN_10003754((int *)param_1,param_2,param_3,(_s_FuncInfo *)param_4,param_5,param_8,param_6,param_7);
            }
        }
        else if ((param_5->maxState != 0x0) && (param_6 == 0x0)) {
            __FrameHandler3::FrameUnwindToEmptyState(param_2,param_4,param_5);
        }
    }
    return 0x1;
}



undefined4 * __thiscall FUN_10003dc4(void *this,exception *param_1)

{
    std::exception::exception((exception *)this,param_1);
    *(undefined ***)this = std::bad_exception::vftable;
    return (undefined4 *)this;
}



undefined4 * __fastcall FUN_10003ddf(undefined4 *param_1)

{
    param_1[0x1] = 0x0;
    param_1[0x2] = 0x0;
    param_1[0x1] = "bad exception";
    *param_1 = std::bad_exception::vftable;
    return param_1;
}



// Library Function - Single Match
//  public: __thiscall std::exception::exception(class std::exception const &)
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

exception * __thiscall std::exception::exception(exception *this,exception *param_1)

{
    *(undefined ***)this = vftable;
    *(char **)(this + 0x4) = NULL;
    *(undefined4 *)(this + 0x8) = 0x0;
    ___std_exception_copy((char **)(param_1 + 0x4),(char **)(this + 0x4));
    return this;
}



// Library Function - Single Match
//  public: bool __thiscall type_info::operator==(class type_info const &)const 
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

bool __thiscall type_info::operator__(type_info *this,type_info *param_1)

{
    uint uVar1;
    
    uVar1 = ___std_type_info_compare((int)(this + 0x4),(int)(param_1 + 0x4));
    return (bool)('\x01' - (uVar1 != 0x0));
}



undefined4 * __thiscall FUN_10003e53(void *this,byte param_1)

{
    *(undefined ***)this = std::exception::vftable;
    ___std_exception_destroy((LPVOID *)((int)this + 0x4));
    if ((param_1 & 0x1) != 0x0) {
        FUN_1000cf80(this);
    }
    return (undefined4 *)this;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  void * __cdecl CallCatchBlock(struct EHExceptionRecord *,struct EHRegistrationNode *,struct _CONTEXT *,struct _s_FuncInfo const *,void *,int,unsigned long)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void * __cdecl CallCatchBlock(EHExceptionRecord *param_1,EHRegistrationNode *param_2,_CONTEXT *param_3,_s_FuncInfo *param_4,void *param_5,int param_6,ulong param_7)

{
    int iVar1;
    void *pvVar2;
    undefined4 *in_FS_OFFSET;
    undefined4 local_50 [0x2];
    undefined4 local_48;
    undefined4 local_44;
    undefined4 local_40;
    undefined4 local_3c;
    undefined4 *local_38;
    undefined4 local_34;
    void *local_20;
    undefined4 local_14;
    undefined4 uStack12;
    undefined *local_8;
    
    local_8 = &DAT_10013610;
    uStack12 = 0x10003e8c;
    local_20 = param_5;
    local_44 = 0x0;
    local_34 = *(undefined4 *)(param_2 + -0x4);
    local_38 = __CreateFrameInfo(local_50,*(undefined4 *)(param_1 + 0x18));
    iVar1 = ___vcrt_getptd();
    local_3c = *(undefined4 *)(iVar1 + 0x10);
    iVar1 = ___vcrt_getptd();
    local_40 = *(undefined4 *)(iVar1 + 0x14);
    iVar1 = ___vcrt_getptd();
    *(EHExceptionRecord **)(iVar1 + 0x10) = param_1;
    iVar1 = ___vcrt_getptd();
    *(_CONTEXT **)(iVar1 + 0x14) = param_3;
    local_48 = 0x1;
    local_8 = (undefined *)0x1;
    pvVar2 = (void *)FUN_10002a23(param_2,param_4,param_5,param_6,param_7);
    local_8 = (undefined *)0xfffffffe;
    local_48 = 0x0;
    local_20 = pvVar2;
    FUN_10003fc8();
    *in_FS_OFFSET = local_14;
    return pvVar2;
}



void FUN_10003fc8(void)

{
    int iVar1;
    int unaff_EBX;
    int unaff_EBP;
    int *unaff_EDI;
    
    *(undefined4 *)(*(int *)(unaff_EBP + 0xc) + -0x4) = *(undefined4 *)(unaff_EBP + -0x30);
    __FindAndUnlinkFrame(*(int *)(unaff_EBP + -0x34));
    iVar1 = ___vcrt_getptd();
    *(undefined4 *)(iVar1 + 0x10) = *(undefined4 *)(unaff_EBP + -0x38);
    iVar1 = ___vcrt_getptd();
    *(undefined4 *)(iVar1 + 0x14) = *(undefined4 *)(unaff_EBP + -0x3c);
    if ((((*unaff_EDI == -0x1f928c9d) && (unaff_EDI[0x4] == 0x3)) && ((unaff_EDI[0x5] == 0x19930520 || ((unaff_EDI[0x5] == 0x19930521 || (unaff_EDI[0x5] == 0x19930522)))))) &&
       ((*(int *)(unaff_EBP + -0x40) == 0x0 && (unaff_EBX != 0x0)))) {
        iVar1 = __IsExceptionObjectToBeDestroyed(unaff_EDI[0x6]);
        if (iVar1 != 0x0) {
            ___DestructExceptionObject(unaff_EDI);
        }
    }
    return;
}



// WARNING: Function: __EH_prolog3_catch replaced with injection: EH_prolog3

void FUN_10004044(undefined4 param_1)

{
    code *pcVar1;
    int iVar2;
    
    iVar2 = ___vcrt_getptd();
    if (*(int *)(iVar2 + 0x1c) == 0x0) {
        _unexpected();
        iVar2 = ___vcrt_getptd();
        *(undefined4 *)(iVar2 + 0x1c) = param_1;
        __CxxThrowException_8(NULL,NULL);
    }
    _abort();
    pcVar1 = (code *)swi(0x3);
    (*pcVar1)();
    return;
}



void Catch_All_10004064(void)

{
    code *pcVar1;
    int iVar2;
    int unaff_EBP;
    
    iVar2 = ___vcrt_getptd();
    *(undefined4 *)(iVar2 + 0x1c) = *(undefined4 *)(unaff_EBP + 0x8);
    __CxxThrowException_8(NULL,NULL);
    _abort();
    pcVar1 = (code *)swi(0x3);
    (*pcVar1)();
    return;
}



// Library Function - Single Match
//  int __cdecl ExFilterRethrow(struct _EXCEPTION_POINTERS *)
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

int __cdecl ExFilterRethrow(_EXCEPTION_POINTERS *param_1)

{
    PEXCEPTION_RECORD pEVar1;
    int iVar2;
    
    pEVar1 = param_1->ExceptionRecord;
    if ((((pEVar1->ExceptionCode == 0xe06d7363) && (pEVar1->NumberParameters == 0x3)) &&
        ((pEVar1->ExceptionInformation[0x0] == 0x19930520 || ((pEVar1->ExceptionInformation[0x0] == 0x19930521 || (pEVar1->ExceptionInformation[0x0] == 0x19930522)))))) &&
       (pEVar1->ExceptionInformation[0x2] == 0x0)) {
        iVar2 = ___vcrt_getptd();
        *(undefined4 *)(iVar2 + 0x20) = 0x1;
        return 0x1;
    }
    return 0x0;
}



// Library Function - Single Match
//  public: static void __cdecl __FrameHandler3::FrameUnwindToEmptyState(struct EHRegistrationNode *,void *,struct _s_FuncInfo const *)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl __FrameHandler3::FrameUnwindToEmptyState(EHRegistrationNode *param_1,void *param_2,_s_FuncInfo *param_3)

{
    FrameUnwindToState(param_1,param_2,param_3,-0x1);
    return;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  public: static void __cdecl __FrameHandler3::FrameUnwindToState(struct EHRegistrationNode *,void *,struct _s_FuncInfo const *,int)
// 
// Library: Visual Studio 2019 Release

void __cdecl __FrameHandler3::FrameUnwindToState(EHRegistrationNode *param_1,void *param_2,_s_FuncInfo *param_3,int param_4)

{
    code *pcVar1;
    int iVar2;
    int iVar3;
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    iVar2 = GetCurrentState(param_1,param_2,param_3);
    iVar3 = ___vcrt_getptd();
    *(int *)(iVar3 + 0x18) = *(int *)(iVar3 + 0x18) + 0x1;
    while (iVar3 = iVar2, iVar3 != param_4) {
        if ((iVar3 < 0x0) || (param_3->maxState <= iVar3)) goto LAB_100041c7;
        iVar2 = param_3->pUnwindMap[iVar3].toState;
        if (param_3->pUnwindMap[iVar3].action != NULL) {
            SetState(param_1,param_3,iVar2);
            __CallSettingFrame_12(param_3->pUnwindMap[iVar3].action,param_1,0x103);
        }
    }
    FUN_100041b3();
    if (iVar3 == param_4) {
        SetState(param_1,param_3,iVar3);
        *in_FS_OFFSET = local_14;
        return;
    }
LAB_100041c7:
    _abort();
    pcVar1 = (code *)swi(0x3);
    (*pcVar1)();
    return;
}



void FUN_100041b3(void)

{
    int iVar1;
    
    iVar1 = ___vcrt_getptd();
    if (0x0 < *(int *)(iVar1 + 0x18)) {
        iVar1 = ___vcrt_getptd();
        *(int *)(iVar1 + 0x18) = *(int *)(iVar1 + 0x18) + -0x1;
    }
    return;
}



// Library Function - Single Match
//  unsigned char __cdecl IsInExceptionSpec(struct EHExceptionRecord *,struct _s_ESTypeList const *)
// 
// Library: Visual Studio 2019 Release

uchar __cdecl IsInExceptionSpec(EHExceptionRecord *param_1,_s_ESTypeList *param_2)

{
    byte **ppbVar1;
    byte *pbVar2;
    HandlerType *pHVar3;
    code *pcVar4;
    uchar uVar5;
    int iVar6;
    byte **ppbVar7;
    int iVar8;
    byte *local_c;
    int local_8;
    
    if (param_2 == NULL) {
        _abort();
        pcVar4 = (code *)swi(0x3);
        uVar5 = (*pcVar4)();
        return uVar5;
    }
    iVar8 = param_2->nCount;
    uVar5 = '\0';
    if (0x0 < iVar8) {
        local_8 = 0x0;
        ppbVar1 = *(byte ***)(*(int *)(param_1 + 0x1c) + 0xc);
        pbVar2 = *ppbVar1;
        uVar5 = '\0';
        do {
            if (0x0 < (int)pbVar2) {
                pHVar3 = param_2->pTypeArray;
                local_c = pbVar2;
                ppbVar7 = ppbVar1;
                do {
                    ppbVar7 = ppbVar7 + 0x1;
                    iVar6 = TypeMatchHelper__((byte *)((int)&pHVar3->adjectives + local_8),*ppbVar7,*(byte **)(param_1 + 0x1c));
                    if (iVar6 != 0x0) {
                        uVar5 = '\x01';
                        break;
                    }
                    local_c = local_c + -0x1;
                } while (0x0 < (int)local_c);
            }
            local_8 = local_8 + 0x10;
            iVar8 = iVar8 + -0x1;
        } while (iVar8 != 0x0);
    }
    return uVar5;
}



// Library Function - Single Match
//  void __stdcall _CallMemberFunction1(void * const,void * const,void * const)
// 
// Library: Visual Studio 2019 Release

void _CallMemberFunction1(void *param_1,void *param_2,void *param_3)

{
    (*(code *)param_2)(param_3);
    return;
}



// Library Function - Single Match
//  void __stdcall _CallMemberFunction2(void * const,void * const,void * const,int)
// 
// Library: Visual Studio 2019 Release

void _CallMemberFunction2(void *param_1,void *param_2,void *param_3,int param_4)

{
    (*(code *)param_2)(param_3,param_4);
    return;
}



undefined4 __cdecl FUN_1000428a(int param_1)

{
    return *(undefined4 *)(param_1 + 0x1c);
}



char * __fastcall FUN_10004295(int param_1)

{
    char *pcVar1;
    
    pcVar1 = *(char **)(param_1 + 0x4);
    if (pcVar1 == NULL) {
        pcVar1 = "Unknown exception";
    }
    return pcVar1;
}



// WARNING: Restarted to delay deadcode elimination for space: stack
// Library Function - Single Match
//  __CallSettingFrame@12
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void __CallSettingFrame_12(undefined4 param_1,undefined4 param_2,int param_3)

{
    code *pcVar1;
    
    pcVar1 = (code *)FUN_10002980(param_3);
    (*pcVar1)();
    if (param_3 == 0x100) {
        param_3 = 0x2;
    }
    FUN_10002980(param_3);
    return;
}



// Library Function - Single Match
//  _unexpected
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void _unexpected(void)

{
    code *pcVar1;
    int iVar2;
    
    iVar2 = ___vcrt_getptd();
    pcVar1 = *(code **)(iVar2 + 0x4);
    if (pcVar1 != NULL) {
        _guard_check_icall();
        (*pcVar1)();
    }
    _terminate();
    pcVar1 = (code *)swi(0x3);
    (*pcVar1)();
    return;
}



// Library Function - Single Match
//  public: static int __cdecl __FrameHandler3::GetCurrentState(struct EHRegistrationNode *,void *,struct _s_FuncInfo const *)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

int __cdecl __FrameHandler3::GetCurrentState(EHRegistrationNode *param_1,void *param_2,_s_FuncInfo *param_3)

{
    if (param_3->maxState < 0x81) {
        return (int)(char)param_1[0x8];
    }
    return *(int *)(param_1 + 0x8);
}



// Library Function - Single Match
//  public: static void __cdecl __FrameHandler3::SetState(struct EHRegistrationNode *,struct _s_FuncInfo const *,int)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl __FrameHandler3::SetState(EHRegistrationNode *param_1,_s_FuncInfo *param_2,int param_3)

{
    *(int *)(param_1 + 0x8) = param_3;
    return;
}



// Library Function - Single Match
//  ___std_exception_copy
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl ___std_exception_copy(char **param_1,char **param_2)

{
    char *pcVar1;
    char cVar2;
    char *pcVar3;
    char *pcVar4;
    char *pcVar5;
    
    if ((*(char *)(param_1 + 0x1) == '\0') || (pcVar4 = *param_1, pcVar4 == NULL)) {
        *param_2 = *param_1;
        *(undefined *)(param_2 + 0x1) = 0x0;
    }
    else {
        pcVar1 = pcVar4 + 0x1;
        do {
            cVar2 = *pcVar4;
            pcVar4 = pcVar4 + 0x1;
        } while (cVar2 != '\0');
        pcVar3 = (char *)FUN_1000519a((size_t)(pcVar4 + (0x1 - (int)pcVar1)));
        pcVar5 = pcVar3;
        if (pcVar3 != NULL) {
            FUN_100051a5(pcVar3,(int)(pcVar4 + (0x1 - (int)pcVar1)),(int)*param_1);
            pcVar5 = NULL;
            *param_2 = pcVar3;
            *(undefined *)(param_2 + 0x1) = 0x1;
        }
        FUN_1000517f(pcVar5);
    }
    return;
}



// Library Function - Single Match
//  ___std_exception_destroy
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl ___std_exception_destroy(LPVOID *param_1)

{
    if (*(char *)(param_1 + 0x1) != '\0') {
        FUN_1000517f(*param_1);
    }
    *param_1 = NULL;
    *(undefined *)(param_1 + 0x1) = 0x0;
    return;
}



// Library Function - Single Match
//  __CxxThrowException@8
// 
// Library: Visual Studio 2019 Release

void __CxxThrowException_8(int *param_1,byte *param_2)

{
    code *pcVar1;
    int *piVar2;
    ULONG_PTR local_10;
    int *local_c;
    byte *local_8;
    
    local_10 = 0x19930520;
    if (param_2 != NULL) {
        if ((*param_2 & 0x10) != 0x0) {
            piVar2 = (int *)(*param_1 + -0x4);
            pcVar1 = *(code **)(*piVar2 + 0x20);
            param_2 = *(byte **)(*piVar2 + 0x18);
            _guard_check_icall();
            (*pcVar1)(piVar2);
            if (param_2 == NULL) goto LAB_1000440d;
        }
        if ((*param_2 & 0x8) != 0x0) {
            local_10 = 0x1994000;
        }
    }
LAB_1000440d:
    local_c = param_1;
    local_8 = param_2;
    RaiseException(0xe06d7363,0x1,0x3,&local_10);
    return;
}



void __cdecl FUN_10004440(undefined **param_1,undefined **param_2)

{
    code *pcVar1;
    
    if (param_1 != param_2) {
        do {
            pcVar1 = (code *)*param_1;
            if (pcVar1 != NULL) {
                _guard_check_icall();
                (*pcVar1)();
            }
            param_1 = (code **)param_1 + 0x1;
        } while (param_1 != param_2);
    }
    return;
}



// Library Function - Single Match
//  __initterm_e
// 
// Library: Visual Studio 2019 Release

int __cdecl __initterm_e(undefined **param_1,undefined **param_2)

{
    code *pcVar1;
    int iVar2;
    
    do {
        if (param_1 == param_2) {
            return 0x0;
        }
        pcVar1 = (code *)*param_1;
        if (pcVar1 != NULL) {
            _guard_check_icall();
            iVar2 = (*pcVar1)();
            if (iVar2 != 0x0) {
                return iVar2;
            }
        }
        param_1 = (code **)param_1 + 0x1;
    } while( true );
}



// Library Function - Single Match
//  __seh_filter_dll
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

undefined4 __cdecl __seh_filter_dll(int param_1,uint *param_2)

{
    undefined4 uVar1;
    
    if (param_1 != -0x1f928c9d) {
        return 0x0;
    }
    uVar1 = FUN_100044b9(0xe06d7363,param_2);
    return uVar1;
}



undefined4 __cdecl FUN_100044b9(uint param_1,uint *param_2)

{
    uint *puVar1;
    code *pcVar2;
    uint *puVar3;
    uint **ppuVar4;
    uint *puVar5;
    uint *puVar6;
    undefined4 uVar7;
    uint uVar8;
    
    ppuVar4 = (uint **)FUN_10005978();
    if (ppuVar4 != NULL) {
        puVar1 = *ppuVar4;
        for (puVar6 = puVar1; puVar6 != puVar1 + 0x24; puVar6 = puVar6 + 0x3) {
            if (*puVar6 == param_1) {
                if (puVar6 == NULL) {
                    return 0x0;
                }
                pcVar2 = (code *)puVar6[0x2];
                if (pcVar2 == NULL) {
                    return 0x0;
                }
                if (pcVar2 == (code *)0x5) {
                    puVar6[0x2] = 0x0;
                    return 0x1;
                }
                if (pcVar2 != (code *)0x1) {
                    puVar3 = ppuVar4[0x1];
                    ppuVar4[0x1] = param_2;
                    if (puVar6[0x1] == 0x8) {
                        for (puVar5 = puVar1 + 0x9; puVar5 != puVar1 + 0x24; puVar5 = puVar5 + 0x3) {
                            puVar5[0x2] = 0x0;
                        }
                        puVar1 = ppuVar4[0x2];
                        puVar5 = puVar1;
                        if (*puVar6 < 0xc0000092) {
                            if (*puVar6 == 0xc0000091) {
                                puVar5 = (uint *)0x84;
                            }
                            else if (*puVar6 == 0xc000008d) {
                                puVar5 = (uint *)0x82;
                            }
                            else if (*puVar6 == 0xc000008e) {
                                puVar5 = (uint *)0x83;
                            }
                            else if (*puVar6 == 0xc000008f) {
                                puVar5 = (uint *)0x86;
                            }
                            else {
                                if (*puVar6 != 0xc0000090) goto LAB_100045cd;
                                puVar5 = (uint *)0x81;
                            }
LAB_100045ca:
                            ppuVar4[0x2] = puVar5;
                        }
                        else {
                            if (*puVar6 == 0xc0000092) {
                                puVar5 = (uint *)0x8a;
                                goto LAB_100045ca;
                            }
                            if (*puVar6 == 0xc0000093) {
                                puVar5 = (uint *)0x85;
                                goto LAB_100045ca;
                            }
                            if (*puVar6 == 0xc00002b4) {
                                puVar5 = (uint *)0x8e;
                                goto LAB_100045ca;
                            }
                            if (*puVar6 == 0xc00002b5) {
                                puVar5 = (uint *)0x8d;
                                goto LAB_100045ca;
                            }
                        }
LAB_100045cd:
                        uVar7 = 0x8;
                        _guard_check_icall();
                        (*pcVar2)(uVar7,puVar5);
                        ppuVar4[0x2] = puVar1;
                    }
                    else {
                        puVar6[0x2] = 0x0;
                        uVar8 = puVar6[0x1];
                        _guard_check_icall();
                        (*pcVar2)(uVar8);
                    }
                    ppuVar4[0x1] = puVar3;
                }
                return 0xffffffff;
            }
        }
    }
    return 0x0;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Multiple Matches With Same Base Name
//  public: void __thiscall __crt_seh_guarded_call<void>::operator()<class <lambda_03b1d95aef87969028cfba75ccab2455>,class <lambda_6e4b09c48022b2350581041d5f6b0c4c>&,class
// <lambda_22bdf7517842c4b3e53723af5aa32b9e>>(class <lambda_03b1d95aef87969028cfba75ccab2455>&&,class <lambda_6e4b09c48022b2350581041d5f6b0c4c>&,class <lambda_22bdf7517842c4b3e53723af5aa32b9e>&&)
//  public: void __thiscall __crt_seh_guarded_call<void>::operator()<class <lambda_4fdada1b837b2abbf20876fac97688ad>,class <lambda_b57350f2640456a0859d250846f69caf>&,class
// <lambda_eed5e4f92b5b7d55fa22c48c484aaa54>>(class <lambda_4fdada1b837b2abbf20876fac97688ad>&&,class <lambda_b57350f2640456a0859d250846f69caf>&,class <lambda_eed5e4f92b5b7d55fa22c48c484aaa54>&&)
//  public: void __thiscall __crt_seh_guarded_call<void>::operator()<class <lambda_ceb1ee4838e85a9d631eb091e2fbe199>,class <lambda_ae742caa10f662c28703da3d2ea5e57e>&,class
// <lambda_cd08b5d6af4937fe54fc07d0c9bf6b37>>(class <lambda_ceb1ee4838e85a9d631eb091e2fbe199>&&,class <lambda_ae742caa10f662c28703da3d2ea5e57e>&,class <lambda_cd08b5d6af4937fe54fc07d0c9bf6b37>&&)
// 
// Library: Visual Studio 2019 Release

void operator____(int *param_1,int **param_2)

{
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    ___acrt_lock(*param_1);
    FUN_1000464c(param_2);
    FUN_10004640();
    *in_FS_OFFSET = local_14;
    return;
}



void FUN_10004640(void)

{
    int unaff_EBP;
    
    ___acrt_unlock(**(int **)(unaff_EBP + 0x10));
    return;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4

void __fastcall FUN_1000464c(int **param_1)

{
    byte bVar1;
    uint uVar2;
    undefined4 *in_FS_OFFSET;
    undefined4 uVar3;
    undefined4 uVar4;
    undefined uVar5;
    undefined4 uVar6;
    undefined4 local_14;
    
    if (DAT_10015eb4 != '\0') goto LAB_10004703;
    DAT_10015eac = 0x1;
    if (**param_1 == 0x0) {
        bVar1 = (byte)DAT_10015124 & 0x1f;
        if (DAT_10015eb0 != DAT_10015124) {
            uVar2 = DAT_10015124 ^ DAT_10015eb0;
            uVar6 = 0x0;
            uVar4 = 0x0;
            uVar3 = 0x0;
            _guard_check_icall();
            (*(code *)(uVar2 >> bVar1 | uVar2 << 0x20 - bVar1))(uVar3,uVar4,uVar6);
        }
        uVar5 = 0xd0;
LAB_100046ba:
        FUN_10004f58(uVar5);
    }
    else if (**param_1 == 0x1) {
        uVar5 = 0xdc;
        goto LAB_100046ba;
    }
    if (**param_1 == 0x0) {
        FUN_10004440((undefined **)&DAT_1000e130,(undefined **)&DAT_1000e140);
    }
    FUN_10004440((undefined **)&DAT_1000e144,(undefined **)&DAT_1000e148);
    if (*param_1[0x1] == 0x0) {
        DAT_10015eb4 = '\x01';
        *(undefined *)param_1[0x2] = 0x1;
    }
LAB_10004703:
    *in_FS_OFFSET = local_14;
    return;
}



void __cdecl FUN_10004737(UINT param_1,undefined4 param_2,int param_3)

{
    code *pcVar1;
    uint uVar2;
    int **in_FS_OFFSET;
    int *local_28;
    int *local_24;
    undefined *local_20;
    int local_1c;
    undefined4 local_18;
    undefined local_11;
    int *local_10;
    undefined *puStack12;
    undefined4 local_8;
    
    local_8 = 0xffffffff;
    puStack12 = &LAB_1000d18f;
    local_10 = *in_FS_OFFSET;
    *in_FS_OFFSET = (int *)&local_10;
    if (param_3 == 0x0) {
        uVar2 = FUN_100047ff();
        if ((char)uVar2 != '\0') {
            FUN_10004864(param_1);
        }
    }
    local_28 = &param_2;
    local_11 = 0x0;
    local_24 = &param_3;
    local_20 = &local_11;
    local_8 = 0x0;
    local_18 = 0x2;
    local_1c = 0x2;
    operator____(&local_1c,&local_28);
    if (param_3 != 0x0) {
        *in_FS_OFFSET = local_10;
        return;
    }
    FUN_100047ce(param_1);
    pcVar1 = (code *)swi(0x3);
    (*pcVar1)();
    return;
}



void FUN_100047ce(UINT param_1)

{
    undefined4 uVar1;
    HANDLE hProcess;
    UINT uExitCode;
    
    uVar1 = FUN_10004842();
    if ((char)uVar1 != '\0') {
        uExitCode = param_1;
        hProcess = GetCurrentProcess();
        TerminateProcess(hProcess,uExitCode);
    }
    FUN_10004864(param_1);
                    // WARNING: Subroutine does not return
    ExitProcess(param_1);
}



uint FUN_100047ff(void)

{
    HMODULE pHVar1;
    int *piVar2;
    
    pHVar1 = GetModuleHandleW(NULL);
    if ((((pHVar1 != NULL) && (*(short *)&pHVar1->unused == 0x5a4d)) && (piVar2 = (int *)((int)&pHVar1->unused + pHVar1[0xf].unused), *piVar2 == 0x4550)) &&
       (((pHVar1 = (HMODULE)0x10b, *(short *)(piVar2 + 0x6) == 0x10b && (0xe < (uint)piVar2[0x1d])) && (piVar2[0x3a] != 0x0)))) {
        return 0x101;
    }
    return (uint)pHVar1 & 0xffffff00;
}



undefined4 FUN_10004842(void)

{
    int iVar1;
    uint3 uVar2;
    int in_FS_OFFSET;
    
    iVar1 = ___acrt_get_process_end_policy();
    uVar2 = (uint3)((uint)iVar1 >> 0x8);
    if ((iVar1 != 0x1) && ((*(uint *)(*(int *)(in_FS_OFFSET + 0x30) + 0x68) >> 0x8 & 0x1) == 0x0)) {
        return CONCAT31(uVar2,0x1);
    }
    return (uint)uVar2 << 0x8;
}



void __cdecl FUN_10004864(undefined4 param_1)

{
    uint uVar1;
    BOOL BVar2;
    FARPROC pFVar3;
    int **in_FS_OFFSET;
    HMODULE local_14;
    int *local_10;
    undefined *puStack12;
    undefined4 uStack8;
    
    uStack8 = 0xffffffff;
    puStack12 = &LAB_1000d1ac;
    local_10 = *in_FS_OFFSET;
    uVar1 = DAT_10015124 ^ (uint)&stack0xfffffffc;
    *in_FS_OFFSET = (int *)&local_10;
    local_14 = NULL;
    BVar2 = GetModuleHandleExW(0x0,L"mscoree.dll",&local_14);
    if (BVar2 != 0x0) {
        pFVar3 = GetProcAddress(local_14,"CorExitProcess");
        if (pFVar3 != NULL) {
            _guard_check_icall();
            (*pFVar3)(param_1,uVar1);
        }
    }
    if (local_14 != NULL) {
        FreeLibrary(local_14);
    }
    *in_FS_OFFSET = local_10;
    return;
}



void __cdecl FUN_100048e6(undefined4 param_1)

{
    DAT_10015eb0 = param_1;
    return;
}



// Library Function - Single Match
//  __exit
// 
// Library: Visual Studio 2019 Release

void __cdecl __exit(int _Code)

{
    FUN_10004737(_Code,0x2,0x0);
    return;
}



undefined4 FUN_1000491a(void)

{
    return DAT_10015eac;
}



// Library Function - Single Match
//  void __cdecl parse_command_line<char>(char *,char * *,char *,unsigned int *,unsigned int *)
// 
// Library: Visual Studio 2019 Release

void __cdecl parse_command_line_char_(char *param_1,char **param_2,char *param_3,uint *param_4,uint *param_5)

{
    char cVar1;
    uint uVar2;
    int iVar3;
    bool bVar4;
    bool bVar5;
    char *pcVar6;
    
    *param_5 = 0x0;
    *param_4 = 0x1;
    if (param_2 != NULL) {
        *param_2 = param_3;
        param_2 = param_2 + 0x1;
    }
    bVar4 = false;
    bVar5 = false;
    do {
        if (*param_1 == '\"') {
            bVar5 = !bVar4;
            cVar1 = '\"';
            pcVar6 = param_1 + 0x1;
            bVar4 = bVar5;
        }
        else {
            *param_5 = *param_5 + 0x1;
            if (param_3 != NULL) {
                *param_3 = *param_1;
                param_3 = param_3 + 0x1;
            }
            cVar1 = *param_1;
            pcVar6 = param_1 + 0x1;
            iVar3 = __ismbblead((int)cVar1);
            if (iVar3 != 0x0) {
                *param_5 = *param_5 + 0x1;
                if (param_3 != NULL) {
                    *param_3 = *pcVar6;
                    param_3 = param_3 + 0x1;
                }
                pcVar6 = param_1 + 0x2;
            }
            if (cVar1 == '\0') {
                pcVar6 = pcVar6 + -0x1;
                goto LAB_10004aee;
            }
        }
        param_1 = pcVar6;
    } while ((bVar5) || ((cVar1 != ' ' && (cVar1 != '\t'))));
    if (param_3 != NULL) {
        param_3[-0x1] = '\0';
    }
LAB_10004aee:
    bVar5 = false;
    while (cVar1 = *pcVar6, cVar1 != '\0') {
        while ((cVar1 == ' ' || (cVar1 == '\t'))) {
            pcVar6 = pcVar6 + 0x1;
            cVar1 = *pcVar6;
        }
        if (cVar1 == '\0') break;
        if (param_2 != NULL) {
            *param_2 = param_3;
            param_2 = param_2 + 0x1;
        }
        *param_4 = *param_4 + 0x1;
        while( true ) {
            bVar4 = true;
            uVar2 = 0x0;
            for (; *pcVar6 == '\\'; pcVar6 = pcVar6 + 0x1) {
                uVar2 = uVar2 + 0x1;
            }
            if (*pcVar6 == '\"') {
                if ((uVar2 & 0x1) == 0x0) {
                    if ((bVar5) && (pcVar6[0x1] == '\"')) {
                        pcVar6 = pcVar6 + 0x1;
                    }
                    else {
                        bVar4 = false;
                        bVar5 = !bVar5;
                    }
                }
                uVar2 = uVar2 >> 0x1;
            }
            while (uVar2 != 0x0) {
                uVar2 = uVar2 - 0x1;
                if (param_3 != NULL) {
                    *param_3 = '\\';
                    param_3 = param_3 + 0x1;
                }
                *param_5 = *param_5 + 0x1;
            }
            cVar1 = *pcVar6;
            if ((cVar1 == '\0') || ((!bVar5 && ((cVar1 == ' ' || (cVar1 == '\t')))))) break;
            if (bVar4) {
                if (param_3 != NULL) {
                    *param_3 = cVar1;
                    param_3 = param_3 + 0x1;
                    cVar1 = *pcVar6;
                }
                iVar3 = __ismbblead((int)cVar1);
                if (iVar3 != 0x0) {
                    pcVar6 = pcVar6 + 0x1;
                    *param_5 = *param_5 + 0x1;
                    if (param_3 != NULL) {
                        *param_3 = *pcVar6;
                        param_3 = param_3 + 0x1;
                    }
                }
                *param_5 = *param_5 + 0x1;
            }
            pcVar6 = pcVar6 + 0x1;
        }
        if (param_3 != NULL) {
            *param_3 = '\0';
            param_3 = param_3 + 0x1;
        }
        *param_5 = *param_5 + 0x1;
    }
    if (param_2 != NULL) {
        *param_2 = NULL;
    }
    *param_4 = *param_4 + 0x1;
    return;
}



// Library Function - Single Match
//  ___acrt_allocate_buffer_for_argv
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

LPVOID __cdecl ___acrt_allocate_buffer_for_argv(uint param_1,uint param_2,uint param_3)

{
    LPVOID pvVar1;
    
    if ((param_1 < 0x3fffffff) && (param_2 < (uint)(0xffffffff / (ulonglong)param_3))) {
        if (param_2 * param_3 < ~(param_1 * 0x4)) {
            pvVar1 = __calloc_base(param_1 * 0x4 + param_2 * param_3,0x1);
            FUN_10005f59(NULL);
            return pvVar1;
        }
    }
    return NULL;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

int __cdecl FUN_10004c21(int param_1)

{
    uchar *puVar1;
    uchar **ppuVar2;
    int iVar3;
    undefined4 *puVar4;
    uchar **ppuVar5;
    char *pcVar6;
    uint local_10;
    uchar **local_c;
    uint local_8;
    
    if (param_1 == 0x0) {
        iVar3 = 0x0;
    }
    else if ((param_1 == 0x2) || (param_1 == 0x1)) {
        ___acrt_initialize_multibyte();
        ___acrt_GetModuleFileNameA(NULL,&DAT_10015eb8,0x104);
        _DAT_10016154 = &DAT_10015eb8;
        if ((DAT_10016164 == NULL) || (pcVar6 = DAT_10016164, *DAT_10016164 == '\0')) {
            pcVar6 = &DAT_10015eb8;
        }
        local_8 = 0x0;
        local_10 = 0x0;
        parse_command_line_char_(pcVar6,NULL,NULL,&local_8,&local_10);
        ppuVar5 = (uchar **)___acrt_allocate_buffer_for_argv(local_8,local_10,0x1);
        if (ppuVar5 == NULL) {
            puVar4 = (undefined4 *)FUN_10005ee9();
            iVar3 = 0xc;
            *puVar4 = 0xc;
        }
        else {
            parse_command_line_char_(pcVar6,(char **)ppuVar5,(char *)(ppuVar5 + local_8),&local_8,&local_10);
            if (param_1 != 0x1) {
                local_c = NULL;
                iVar3 = FUN_1000683c(ppuVar5,&local_c);
                ppuVar2 = local_c;
                if (iVar3 == 0x0) {
                    _DAT_10016158 = 0x0;
                    puVar1 = *local_c;
                    while (puVar1 != NULL) {
                        local_c = local_c + 0x1;
                        _DAT_10016158 = _DAT_10016158 + 0x1;
                        puVar1 = *local_c;
                    }
                    local_c = NULL;
                    _DAT_1001615c = ppuVar2;
                    FUN_10005f59(NULL);
                    iVar3 = 0x0;
                }
                else {
                    FUN_10005f59(local_c);
                }
                local_c = NULL;
                FUN_10005f59(ppuVar5);
                return iVar3;
            }
            _DAT_10016158 = local_8 - 0x1;
            iVar3 = 0x0;
            _DAT_1001615c = ppuVar5;
        }
        FUN_10005f59(NULL);
    }
    else {
        puVar4 = (undefined4 *)FUN_10005ee9();
        iVar3 = 0x16;
        *puVar4 = 0x16;
        FUN_10005e08();
    }
    return iVar3;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined4 FUN_10004c2c(void)

{
    LPWCH pWVar1;
    char **ppcVar2;
    undefined4 uVar3;
    
    if (_DAT_10015fc0 != NULL) {
        return 0x0;
    }
    ___acrt_initialize_multibyte();
    pWVar1 = FUN_10007437();
    if (pWVar1 == NULL) {
        FUN_10005f59(NULL);
        return 0xffffffff;
    }
    ppcVar2 = FUN_10004c86((char *)pWVar1);
    if (ppcVar2 == NULL) {
        uVar3 = 0xffffffff;
    }
    else {
        uVar3 = 0x0;
        _DAT_10015fc0 = ppcVar2;
        DAT_10015fcc = ppcVar2;
    }
    FUN_10005f59(NULL);
    FUN_10005f59(pWVar1);
    return uVar3;
}



char ** __cdecl FUN_10004c86(char *param_1)

{
    code *pcVar1;
    char cVar2;
    char **ppcVar3;
    char *pcVar4;
    char *pcVar5;
    int iVar6;
    char **local_8;
    
    iVar6 = 0x0;
    cVar2 = *param_1;
    pcVar5 = param_1;
    while (cVar2 != '\0') {
        if (cVar2 != '=') {
            iVar6 = iVar6 + 0x1;
        }
        do {
            cVar2 = *pcVar5;
            pcVar5 = pcVar5 + 0x1;
        } while (cVar2 != '\0');
        cVar2 = *pcVar5;
    }
    ppcVar3 = (char **)__calloc_base(iVar6 + 0x1,0x4);
    local_8 = ppcVar3;
    if (ppcVar3 == NULL) {
        FUN_10005f59(NULL);
        ppcVar3 = NULL;
    }
    else {
        for (; *param_1 != '\0'; param_1 = param_1 + (int)pcVar5) {
            pcVar5 = param_1;
            do {
                cVar2 = *pcVar5;
                pcVar5 = pcVar5 + 0x1;
            } while (cVar2 != '\0');
            pcVar5 = pcVar5 + (0x1 - (int)(param_1 + 0x1));
            if (*param_1 != '=') {
                pcVar4 = (char *)__calloc_base((uint)pcVar5,0x1);
                if (pcVar4 == NULL) {
                    free_environment__(ppcVar3);
                    FUN_10005f59(NULL);
                    FUN_10005f59(NULL);
                    return NULL;
                }
                iVar6 = FUN_100051a5(pcVar4,(int)pcVar5,(int)param_1);
                if (iVar6 != 0x0) {
                    __invoke_watson(NULL,NULL,NULL,0x0,0x0);
                    pcVar1 = (code *)swi(0x3);
                    ppcVar3 = (char **)(*pcVar1)();
                    return ppcVar3;
                }
                *local_8 = pcVar4;
                local_8 = local_8 + 0x1;
                FUN_10005f59(NULL);
            }
        }
        FUN_10005f59(NULL);
    }
    return ppcVar3;
}



// Library Function - Multiple Matches With Same Base Name
//  void __cdecl free_environment<char>(char * * const)
//  void __cdecl free_environment<wchar_t>(wchar_t * * const)
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl free_environment__(LPVOID *param_1)

{
    LPVOID pvVar1;
    LPVOID *ppvVar2;
    
    if (param_1 != NULL) {
        pvVar1 = *param_1;
        ppvVar2 = param_1;
        while (pvVar1 != NULL) {
            FUN_10005f59(pvVar1);
            ppvVar2 = ppvVar2 + 0x1;
            pvVar1 = *ppvVar2;
        }
        FUN_10005f59(param_1);
    }
    return;
}



// Library Function - Multiple Matches With Same Base Name
//  void __cdecl uninitialize_environment_internal<char>(char * * &)
//  void __cdecl uninitialize_environment_internal<wchar_t>(wchar_t * * &)
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl uninitialize_environment_internal__(undefined4 *param_1)

{
    if ((LPVOID *)*param_1 != DAT_10015fcc) {
        free_environment__((LPVOID *)*param_1);
    }
    return;
}



// Library Function - Multiple Matches With Same Base Name
//  void __cdecl uninitialize_environment_internal<char>(char * * &)
//  void __cdecl uninitialize_environment_internal<wchar_t>(wchar_t * * &)
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl uninitialize_environment_internal__(undefined4 *param_1)

{
    if ((LPVOID *)*param_1 != DAT_10015fc8) {
        free_environment__((LPVOID *)*param_1);
    }
    return;
}



// WARNING: Function: __EH_prolog3 replaced with injection: EH_prolog3
// WARNING: Function: __EH_epilog3 replaced with injection: EH_epilog3

void FUN_10004dcd(void)

{
    uninitialize_environment_internal__((undefined4 *)&DAT_10015fc0);
    uninitialize_environment_internal__((undefined4 *)&DAT_10015fc4);
    free_environment__(DAT_10015fcc);
    free_environment__(DAT_10015fc8);
    return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

undefined4 thunk_FUN_10004c2c(void)

{
    LPWCH pWVar1;
    char **ppcVar2;
    undefined4 uVar3;
    
    if (_DAT_10015fc0 != NULL) {
        return 0x0;
    }
    ___acrt_initialize_multibyte();
    pWVar1 = FUN_10007437();
    if (pWVar1 == NULL) {
        FUN_10005f59(NULL);
        return 0xffffffff;
    }
    ppcVar2 = FUN_10004c86((char *)pWVar1);
    if (ppcVar2 == NULL) {
        uVar3 = 0xffffffff;
    }
    else {
        uVar3 = 0x0;
        _DAT_10015fc0 = ppcVar2;
        DAT_10015fcc = ppcVar2;
    }
    FUN_10005f59(NULL);
    FUN_10005f59(pWVar1);
    return uVar3;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  public: int __thiscall __crt_seh_guarded_call<int>::operator()<class <lambda_69a2805e680e0e292e8ba93315fe43a8>,class <lambda_f03950bc5685219e0bcd2087efbe011e>&,class
// <lambda_03fcd07e894ec930e3f35da366ca99d6>>(class <lambda_69a2805e680e0e292e8ba93315fe43a8>&&,class <lambda_f03950bc5685219e0bcd2087efbe011e>&,class <lambda_03fcd07e894ec930e3f35da366ca99d6>&&)
// 
// Library: Visual Studio 2019 Release

int __thiscall
__crt_seh_guarded_call<int>::operator___class__lambda_69a2805e680e0e292e8ba93315fe43a8__class__lambda_f03950bc5685219e0bcd2087efbe011e___class__lambda_03fcd07e894ec930e3f35da366ca99d6___
          (__crt_seh_guarded_call_int_ *this,_lambda_69a2805e680e0e292e8ba93315fe43a8_ *param_1,_lambda_f03950bc5685219e0bcd2087efbe011e_ *param_2,_lambda_03fcd07e894ec930e3f35da366ca99d6_ *param_3)

{
    int iVar1;
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    ___acrt_lock(*(int *)param_1);
    iVar1 = <lambda_f03950bc5685219e0bcd2087efbe011e>::operator__(param_2);
    FUN_10004e72();
    *in_FS_OFFSET = local_14;
    return iVar1;
}



void FUN_10004e72(void)

{
    int unaff_EBP;
    
    ___acrt_unlock(**(int **)(unaff_EBP + 0x10));
    return;
}



// Library Function - Single Match
//  public: int __thiscall <lambda_f03950bc5685219e0bcd2087efbe011e>::operator()(void)const 
// 
// Library: Visual Studio 2019 Release

int __thiscall <lambda_f03950bc5685219e0bcd2087efbe011e>::operator__(_lambda_f03950bc5685219e0bcd2087efbe011e_ *this)

{
    uint uVar1;
    int iVar2;
    uint uVar3;
    uint *puVar4;
    sbyte sVar5;
    uint uVar6;
    uint *puVar7;
    uint *puVar8;
    uint *puVar9;
    uint *puVar10;
    
    uVar1 = DAT_10015124;
    puVar9 = **(uint ***)this;
    if (puVar9 == NULL) {
        iVar2 = -0x1;
    }
    else {
        uVar6 = DAT_10015124 & 0x1f;
        sVar5 = (sbyte)uVar6;
        puVar8 = (uint *)((*puVar9 ^ DAT_10015124) >> sVar5 | (*puVar9 ^ DAT_10015124) << 0x20 - sVar5);
        puVar9 = (uint *)((puVar9[0x1] ^ DAT_10015124) >> sVar5 | (puVar9[0x1] ^ DAT_10015124) << 0x20 - sVar5);
        if ((puVar8 != NULL) && (uVar3 = DAT_10015124, puVar10 = puVar9, puVar8 != (uint *)0xffffffff)) {
            while (puVar9 = puVar9 + -0x1, puVar8 <= puVar9) {
                if (*puVar9 != uVar1) {
                    uVar3 = *puVar9 ^ uVar3;
                    *puVar9 = uVar1;
                    _guard_check_icall();
                    (*(code *)(uVar3 >> (sbyte)uVar6 | uVar3 << 0x20 - (sbyte)uVar6))();
                    uVar6 = DAT_10015124 & 0x1f;
                    uVar3 = ***(uint ***)this ^ DAT_10015124;
                    sVar5 = (sbyte)uVar6;
                    puVar7 = (uint *)(uVar3 >> sVar5 | uVar3 << 0x20 - sVar5);
                    uVar3 = (**(uint ***)this)[0x1] ^ DAT_10015124;
                    puVar4 = (uint *)(uVar3 >> sVar5 | uVar3 << 0x20 - sVar5);
                    uVar3 = DAT_10015124;
                    if ((puVar7 != puVar8) || (puVar4 != puVar10)) {
                        puVar9 = puVar4;
                        puVar10 = puVar4;
                        puVar8 = puVar7;
                    }
                }
            }
            if (puVar8 != (uint *)0xffffffff) {
                FUN_10005f59(puVar8);
                uVar3 = DAT_10015124;
            }
            ***(uint ***)this = uVar3;
            *(uint *)(**(int **)this + 0x4) = uVar3;
            *(uint *)(**(int **)this + 0x8) = uVar3;
        }
        iVar2 = 0x0;
    }
    return iVar2;
}



// WARNING: Function: __EH_prolog3 replaced with injection: EH_prolog3
// WARNING: Function: __EH_epilog3 replaced with injection: EH_epilog3

void FUN_10004f58(undefined param_1)

{
    undefined4 local_20;
    undefined1 *local_1c;
    undefined4 local_18;
    __crt_seh_guarded_call_int_ local_11 [0x9];
    undefined4 local_8;
    undefined4 uStack4;
    
    uStack4 = 0x10;
    local_1c = &param_1;
    local_8 = 0x0;
    local_18 = 0x2;
    local_20 = 0x2;
    __crt_seh_guarded_call<int>::operator___class__lambda_69a2805e680e0e292e8ba93315fe43a8__class__lambda_f03950bc5685219e0bcd2087efbe011e___class__lambda_03fcd07e894ec930e3f35da366ca99d6___
              (local_11,(_lambda_69a2805e680e0e292e8ba93315fe43a8_ *)&local_20,(_lambda_f03950bc5685219e0bcd2087efbe011e_ *)&local_1c,(_lambda_03fcd07e894ec930e3f35da366ca99d6_ *)&local_18);
    return;
}



// Library Function - Single Match
//  __initialize_onexit_table
// 
// Library: Visual Studio 2019 Release

undefined4 __cdecl __initialize_onexit_table(int *param_1)

{
    int iVar1;
    
    iVar1 = DAT_10015124;
    if (param_1 == NULL) {
        return 0xffffffff;
    }
    if (*param_1 == param_1[0x2]) {
        *param_1 = DAT_10015124;
        param_1[0x1] = iVar1;
        param_1[0x2] = iVar1;
    }
    return 0x0;
}



// Library Function - Single Match
//  _uninitialize_allocated_memory
// 
// Library: Visual Studio 2019 Release

undefined _uninitialize_allocated_memory(void)

{
    _lambda_af42a3ee9806e9a7305d451646e05244_ local_5;
    
    <lambda_af42a3ee9806e9a7305d451646e05244>::operator__(&local_5,(__crt_multibyte_data **)&DAT_10016148);
    return 0x1;
}



// Library Function - Single Match
//  void * __cdecl __crt_fast_encode_pointer<void *>(void * const)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void * __cdecl __crt_fast_encode_pointer_void__(void *param_1)

{
    byte bVar1;
    
    bVar1 = 0x20 - ((byte)DAT_10015124 & 0x1f) & 0x1f;
    return (void *)(((uint)param_1 >> bVar1 | (int)param_1 << 0x20 - bVar1) ^ DAT_10015124);
}



// Library Function - Single Match
//  public: void __thiscall <lambda_af42a3ee9806e9a7305d451646e05244>::operator()(struct __crt_multibyte_data * &)const 
// 
// Library: Visual Studio 2019 Release

void __thiscall <lambda_af42a3ee9806e9a7305d451646e05244>::operator__(_lambda_af42a3ee9806e9a7305d451646e05244_ *this,__crt_multibyte_data **param_1)

{
    int iVar1;
    
    LOCK();
    iVar1 = *(int *)*param_1 + -0x1;
    *(int *)*param_1 = iVar1;
    if ((iVar1 == 0x0) && (*param_1 != (__crt_multibyte_data *)&DAT_10015170)) {
        FUN_10005f59(*param_1);
        *param_1 = (__crt_multibyte_data *)&DAT_10015170;
    }
    return;
}



// Library Function - Single Match
//  ___acrt_initialize
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void ___acrt_initialize(void)

{
    ___acrt_execute_initializers(&PTR_LAB_1000ed30,(undefined **)&DAT_1000edb0);
    return;
}



uint FUN_100050ee(void)

{
    __acrt_ptd *p_Var1;
    
    p_Var1 = FUN_10005978();
    return (uint)p_Var1 & 0xffffff00 | (uint)(p_Var1 != NULL);
}



undefined FUN_100050f9(void)

{
    ___acrt_freeptd();
    return 0x1;
}



// Library Function - Single Match
//  ___acrt_uninitialize
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

undefined4 __cdecl ___acrt_uninitialize(char param_1)

{
    int in_EAX;
    undefined4 uVar1;
    
    if (param_1 != '\0') {
        if (DAT_10016474 != 0x0) {
            in_EAX = __flushall();
        }
        return CONCAT31((int3)((uint)in_EAX >> 0x8),0x1);
    }
    uVar1 = ___acrt_execute_uninitializers((int)&PTR_LAB_1000ed30,(int)&DAT_1000edb0);
    return uVar1;
}



// Library Function - Single Match
//  ___acrt_uninitialize_critical
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

undefined4 ___acrt_uninitialize_critical(undefined4 param_1)

{
    undefined4 uVar1;
    
    uVar1 = ___acrt_uninitialize_ptd();
    return CONCAT31((int3)((uint)uVar1 >> 0x8),0x1);
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  _terminate
// 
// Library: Visual Studio 2019 Release

void _terminate(void)

{
    code *pcVar1;
    __acrt_ptd *p_Var2;
    
    p_Var2 = FUN_10005827();
    pcVar1 = *(code **)(p_Var2 + 0xc);
    if (pcVar1 != NULL) {
        _guard_check_icall();
        (*pcVar1)();
    }
    _abort();
    pcVar1 = (code *)swi(0x3);
    (*pcVar1)();
    return;
}



void __cdecl FUN_1000517f(LPVOID param_1)

{
    FUN_10005f59(param_1);
    return;
}



void FUN_1000519a(size_t param_1)

{
    __malloc_base(param_1);
    return;
}



undefined4 __cdecl FUN_100051a5(char *param_1,int param_2,int param_3)

{
    char cVar1;
    undefined4 *puVar2;
    char *pcVar3;
    undefined4 uStack16;
    
    if ((param_1 != NULL) && (param_2 != 0x0)) {
        if (param_3 != 0x0) {
            pcVar3 = param_1;
            do {
                cVar1 = pcVar3[param_3 - (int)param_1];
                *pcVar3 = cVar1;
                pcVar3 = pcVar3 + 0x1;
                if (cVar1 == '\0') {
                    return 0x0;
                }
                param_2 = param_2 + -0x1;
            } while (param_2 != 0x0);
            *param_1 = '\0';
            puVar2 = (undefined4 *)FUN_10005ee9();
            uStack16 = 0x22;
            goto LAB_100051cb;
        }
        *param_1 = '\0';
    }
    puVar2 = (undefined4 *)FUN_10005ee9();
    uStack16 = 0x16;
LAB_100051cb:
    *puVar2 = uStack16;
    FUN_10005e08();
    return uStack16;
}



// Library Function - Single Match
//  _abort
// 
// Library: Visual Studio 2019 Release

void __cdecl _abort(void)

{
    code *pcVar1;
    int iVar2;
    BOOL BVar3;
    
    iVar2 = ___acrt_get_sigabrt_handler();
    if (iVar2 != 0x0) {
        _raise(0x16);
    }
    if ((DAT_10015150 & 0x2) != 0x0) {
        BVar3 = IsProcessorFeaturePresent(0x17);
        if (BVar3 != 0x0) {
            pcVar1 = (code *)swi(0x29);
            (*pcVar1)();
        }
        ___acrt_call_reportfault(0x3,0x40000015,0x1);
    }
    __exit(0x3);
    pcVar1 = (code *)swi(0x3);
    (*pcVar1)();
    return;
}



undefined4 * __thiscall FUN_10005250(void *this,undefined4 *param_1)

{
    undefined4 uVar1;
    undefined *puVar2;
    undefined *puVar3;
    
    *(undefined *)((int)this + 0x14) = 0x0;
    *(undefined4 *)this = 0x0;
    *(undefined *)((int)this + 0x8) = 0x0;
    *(undefined *)((int)this + 0x1c) = 0x0;
    *(undefined *)((int)this + 0x24) = 0x0;
    puVar3 = PTR_DAT_1001574c;
    puVar2 = PTR_PTR_DAT_10015748;
    if (param_1 != NULL) {
        uVar1 = param_1[0x1];
        *(undefined4 *)((int)this + 0xc) = *param_1;
        *(undefined *)((int)this + 0x14) = 0x1;
        *(undefined4 *)((int)this + 0x10) = uVar1;
        return (undefined4 *)this;
    }
    if (DAT_10016488 == 0x0) {
        *(undefined *)((int)this + 0x14) = 0x1;
        *(undefined **)((int)this + 0x10) = puVar3;
        *(undefined **)((int)this + 0xc) = puVar2;
    }
    return (undefined4 *)this;
}



void __fastcall FUN_100052b0(__acrt_ptd **param_1)

{
    __acrt_ptd *p_Var1;
    __acrt_ptd *p_Var2;
    
    if (*(char *)(param_1 + 0x5) == '\x02') {
        *(uint *)(*param_1 + 0x350) = *(uint *)(*param_1 + 0x350) & 0xfffffffd;
    }
    if (*(char *)(param_1 + 0x7) != '\0') {
        p_Var1 = param_1[0x6];
        p_Var2 = FUN_10005340(param_1);
        *(__acrt_ptd **)(p_Var2 + 0x10) = p_Var1;
    }
    if (*(char *)(param_1 + 0x9) != '\0') {
        p_Var1 = param_1[0x8];
        p_Var2 = FUN_10005340(param_1);
        *(__acrt_ptd **)(p_Var2 + 0x14) = p_Var1;
    }
    return;
}



__acrt_ptd * __fastcall FUN_100052f0(__acrt_ptd **param_1)

{
    __acrt_ptd *p_Var1;
    __acrt_ptd **local_8;
    
    local_8 = param_1;
    local_8 = (__acrt_ptd **)GetLastError();
    if (*(char *)(param_1 + 0x2) == '\0') {
        param_1[0x1] = NULL;
        p_Var1 = NULL;
        *(undefined *)(param_1 + 0x2) = 0x1;
    }
    else {
        p_Var1 = param_1[0x1];
    }
    p_Var1 = FUN_10005a29(&local_8,(int)p_Var1);
    *param_1 = p_Var1;
    SetLastError((DWORD)local_8);
    return p_Var1;
}



__acrt_ptd * __fastcall FUN_10005340(__acrt_ptd **param_1)

{
    code *pcVar1;
    __acrt_ptd *p_Var2;
    __acrt_ptd **local_8;
    
    if (*param_1 == NULL) {
        local_8 = param_1;
        local_8 = (__acrt_ptd **)GetLastError();
        if (*(char *)(param_1 + 0x2) == '\0') {
            param_1[0x1] = NULL;
            p_Var2 = NULL;
            *(undefined *)(param_1 + 0x2) = 0x1;
        }
        else {
            p_Var2 = param_1[0x1];
        }
        p_Var2 = FUN_10005a29(&local_8,(int)p_Var2);
        *param_1 = p_Var2;
        SetLastError((DWORD)local_8);
        if (p_Var2 == NULL) {
            _abort();
            pcVar1 = (code *)swi(0x3);
            p_Var2 = (__acrt_ptd *)(*pcVar1)();
            return p_Var2;
        }
    }
    return *param_1;
}



void __fastcall FUN_100053a0(__acrt_ptd **param_1)

{
    __acrt_ptd *p_Var1;
    
    p_Var1 = FUN_10005340(param_1);
    param_1[0x3] = *(__acrt_ptd **)(p_Var1 + 0x4c);
    param_1[0x4] = *(__acrt_ptd **)(p_Var1 + 0x48);
    FUN_10008469((int)p_Var1,(int *)(param_1 + 0x3),(int)param_1[0x1]);
    FUN_100084c7((int)p_Var1,(int *)(param_1 + 0x4),(int)param_1[0x1]);
    if ((*(uint *)(p_Var1 + 0x350) & 0x2) == 0x0) {
        *(uint *)(p_Var1 + 0x350) = *(uint *)(p_Var1 + 0x350) | 0x2;
        *(undefined *)(param_1 + 0x5) = 0x2;
    }
    return;
}



void FUN_10005478(uint param_1,uint param_2)

{
    __calloc_base(param_1,param_2);
    return;
}



// Library Function - Single Match
//  _wcsncmp
// 
// Library: Visual Studio 2019 Release

int __cdecl _wcsncmp(wchar_t *_Str1,wchar_t *_Str2,size_t _MaxCount)

{
    if (_MaxCount != 0x0) {
        for (; ((_MaxCount = _MaxCount - 0x1, _MaxCount != 0x0 && (*_Str1 != L'\0')) && (*_Str1 == *_Str2)); _Str1 = _Str1 + 0x1) {
            _Str2 = _Str2 + 0x1;
        }
        return (uint)(ushort)*_Str1 - (uint)(ushort)*_Str2;
    }
    return _MaxCount;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  public: void __thiscall __crt_seh_guarded_call<void>::operator()<class <lambda_15ade71b0218206bbe3333a0c9b79046>,class <lambda_da44e0f8b0f19ba52fefafb335991732>&,class
// <lambda_207f2d024fc103971653565357d6cd41>>(class <lambda_15ade71b0218206bbe3333a0c9b79046>&&,class <lambda_da44e0f8b0f19ba52fefafb335991732>&,class <lambda_207f2d024fc103971653565357d6cd41>&&)
// 
// Library: Visual Studio 2019 Release

void __thiscall
__crt_seh_guarded_call<void>::operator___class__lambda_15ade71b0218206bbe3333a0c9b79046__class__lambda_da44e0f8b0f19ba52fefafb335991732___class__lambda_207f2d024fc103971653565357d6cd41___
          (__crt_seh_guarded_call_void_ *this,_lambda_15ade71b0218206bbe3333a0c9b79046_ *param_1,_lambda_da44e0f8b0f19ba52fefafb335991732_ *param_2,_lambda_207f2d024fc103971653565357d6cd41_ *param_3)

{
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    ___acrt_lock(*(int *)param_1);
    LOCK();
    **(int **)(**(int **)param_2 + 0x48) = **(int **)(**(int **)param_2 + 0x48) + 0x1;
    FUN_10005503();
    *in_FS_OFFSET = local_14;
    return;
}



void FUN_10005503(void)

{
    int unaff_EBP;
    
    ___acrt_unlock(**(int **)(unaff_EBP + 0x10));
    return;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  public: void __thiscall __crt_seh_guarded_call<void>::operator()<class <lambda_38edbb1296d33220d7e4dd0ed76b244a>,class <lambda_5ce1d447e08cb34b2473517608e21441>&,class
// <lambda_fb385d3da700c9147fc39e65dd577a8c>>(class <lambda_38edbb1296d33220d7e4dd0ed76b244a>&&,class <lambda_5ce1d447e08cb34b2473517608e21441>&,class <lambda_fb385d3da700c9147fc39e65dd577a8c>&&)
// 
// Library: Visual Studio 2019 Release

void __thiscall
__crt_seh_guarded_call<void>::operator___class__lambda_38edbb1296d33220d7e4dd0ed76b244a__class__lambda_5ce1d447e08cb34b2473517608e21441___class__lambda_fb385d3da700c9147fc39e65dd577a8c___
          (__crt_seh_guarded_call_void_ *this,_lambda_38edbb1296d33220d7e4dd0ed76b244a_ *param_1,_lambda_5ce1d447e08cb34b2473517608e21441_ *param_2,_lambda_fb385d3da700c9147fc39e65dd577a8c_ *param_3)

{
    int *piVar1;
    int iVar2;
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    ___acrt_lock(*(int *)param_1);
    piVar1 = *(int **)(**(int **)param_2 + 0x48);
    if (piVar1 != NULL) {
        LOCK();
        iVar2 = *piVar1;
        *piVar1 = iVar2 + -0x1;
        if ((iVar2 + -0x1 == 0x0) && (piVar1 != (int *)&DAT_10015170)) {
            FUN_10005f59(piVar1);
        }
    }
    FUN_1000556e();
    *in_FS_OFFSET = local_14;
    return;
}



void FUN_1000556e(void)

{
    int unaff_EBP;
    
    ___acrt_unlock(**(int **)(unaff_EBP + 0x10));
    return;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  public: void __thiscall __crt_seh_guarded_call<void>::operator()<class <lambda_6affb1475c98b40b75cdec977db92e3c>,class <lambda_b8d4b9c228a6ecc3f80208dbb4b4a104>&,class
// <lambda_608742c3c92a14382c1684fc64f96c88>>(class <lambda_6affb1475c98b40b75cdec977db92e3c>&&,class <lambda_b8d4b9c228a6ecc3f80208dbb4b4a104>&,class <lambda_608742c3c92a14382c1684fc64f96c88>&&)
// 
// Library: Visual Studio 2019 Release

void __thiscall
__crt_seh_guarded_call<void>::operator___class__lambda_6affb1475c98b40b75cdec977db92e3c__class__lambda_b8d4b9c228a6ecc3f80208dbb4b4a104___class__lambda_608742c3c92a14382c1684fc64f96c88___
          (__crt_seh_guarded_call_void_ *this,_lambda_6affb1475c98b40b75cdec977db92e3c_ *param_1,_lambda_b8d4b9c228a6ecc3f80208dbb4b4a104_ *param_2,_lambda_608742c3c92a14382c1684fc64f96c88_ *param_3)

{
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    ___acrt_lock(*(int *)param_1);
    replace_current_thread_locale_nolock(**(__acrt_ptd ***)param_2,NULL);
    FUN_100055c3();
    *in_FS_OFFSET = local_14;
    return;
}



void FUN_100055c3(void)

{
    int unaff_EBP;
    
    ___acrt_unlock(**(int **)(unaff_EBP + 0x10));
    return;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  public: void __thiscall __crt_seh_guarded_call<void>::operator()<class <lambda_a7e850c220f1c8d1e6efeecdedd162c6>,class <lambda_46720907175c18b6c9d2717bc0d2d362>&,class
// <lambda_9048902d66e8d99359bc9897bbb930a8>>(class <lambda_a7e850c220f1c8d1e6efeecdedd162c6>&&,class <lambda_46720907175c18b6c9d2717bc0d2d362>&,class <lambda_9048902d66e8d99359bc9897bbb930a8>&&)
// 
// Library: Visual Studio 2019 Release

void __thiscall
__crt_seh_guarded_call<void>::operator___class__lambda_a7e850c220f1c8d1e6efeecdedd162c6__class__lambda_46720907175c18b6c9d2717bc0d2d362___class__lambda_9048902d66e8d99359bc9897bbb930a8___
          (__crt_seh_guarded_call_void_ *this,_lambda_a7e850c220f1c8d1e6efeecdedd162c6_ *param_1,_lambda_46720907175c18b6c9d2717bc0d2d362_ *param_2,_lambda_9048902d66e8d99359bc9897bbb930a8_ *param_3)

{
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    ___acrt_lock(*(int *)param_1);
    replace_current_thread_locale_nolock(**(__acrt_ptd ***)param_2,*(__crt_locale_data **)**(undefined4 **)(param_2 + 0x4));
    FUN_1000561d();
    *in_FS_OFFSET = local_14;
    return;
}



void FUN_1000561d(void)

{
    int unaff_EBP;
    
    ___acrt_unlock(**(int **)(unaff_EBP + 0x10));
    return;
}



// Library Function - Single Match
//  void __cdecl construct_ptd(struct __acrt_ptd * const,struct __crt_locale_data * * const)
// 
// Library: Visual Studio 2019 Release

void __cdecl construct_ptd(__acrt_ptd *param_1,__crt_locale_data **param_2)

{
    undefined4 local_18;
    __acrt_ptd **local_14;
    __acrt_ptd **local_10;
    __crt_locale_data ***local_c;
    __crt_seh_guarded_call_void_ local_5;
    
    *(undefined4 *)(param_1 + 0x18) = 0x1;
    *(undefined **)param_1 = &DAT_1000ec68;
    *(undefined4 *)(param_1 + 0x350) = 0x1;
    *(undefined **)(param_1 + 0x48) = &DAT_10015170;
    *(undefined2 *)(param_1 + 0x6c) = 0x43;
    *(undefined2 *)(param_1 + 0x172) = 0x43;
    *(undefined4 *)(param_1 + 0x34c) = 0x0;
    local_14 = &param_1;
    local_c = (__crt_locale_data ***)0x5;
    local_18 = 0x5;
    __crt_seh_guarded_call<void>::operator___class__lambda_15ade71b0218206bbe3333a0c9b79046__class__lambda_da44e0f8b0f19ba52fefafb335991732___class__lambda_207f2d024fc103971653565357d6cd41___
              (&local_5,(_lambda_15ade71b0218206bbe3333a0c9b79046_ *)&local_18,(_lambda_da44e0f8b0f19ba52fefafb335991732_ *)&local_14,(_lambda_207f2d024fc103971653565357d6cd41_ *)&local_c);
    local_10 = &param_1;
    local_c = &param_2;
    local_18 = 0x4;
    local_14 = (__acrt_ptd **)0x4;
    __crt_seh_guarded_call<void>::operator___class__lambda_a7e850c220f1c8d1e6efeecdedd162c6__class__lambda_46720907175c18b6c9d2717bc0d2d362___class__lambda_9048902d66e8d99359bc9897bbb930a8___
              (&local_5,(_lambda_a7e850c220f1c8d1e6efeecdedd162c6_ *)&local_14,(_lambda_46720907175c18b6c9d2717bc0d2d362_ *)&local_10,(_lambda_9048902d66e8d99359bc9897bbb930a8_ *)&local_18);
    return;
}



// Library Function - Single Match
//  void __stdcall destroy_fls(void *)
// 
// Library: Visual Studio 2019 Release

void destroy_fls(void *param_1)

{
    if (param_1 != NULL) {
        destroy_ptd((__acrt_ptd *)param_1);
        FUN_10005f59(param_1);
    }
    return;
}



// Library Function - Single Match
//  void __cdecl destroy_ptd(struct __acrt_ptd * const)
// 
// Library: Visual Studio 2019 Release

void __cdecl destroy_ptd(__acrt_ptd *param_1)

{
    undefined4 local_14;
    __acrt_ptd **local_10;
    undefined4 local_c;
    __crt_seh_guarded_call_void_ local_5;
    
    if (*(undefined **)param_1 != &DAT_1000ec68) {
        FUN_10005f59(*(undefined **)param_1);
    }
    FUN_10005f59(*(LPVOID *)(param_1 + 0x3c));
    FUN_10005f59(*(LPVOID *)(param_1 + 0x30));
    FUN_10005f59(*(LPVOID *)(param_1 + 0x34));
    FUN_10005f59(*(LPVOID *)(param_1 + 0x38));
    FUN_10005f59(*(LPVOID *)(param_1 + 0x28));
    FUN_10005f59(*(LPVOID *)(param_1 + 0x2c));
    FUN_10005f59(*(LPVOID *)(param_1 + 0x40));
    FUN_10005f59(*(LPVOID *)(param_1 + 0x44));
    FUN_10005f59(*(LPVOID *)(param_1 + 0x360));
    local_10 = &param_1;
    local_c = 0x5;
    local_14 = 0x5;
    __crt_seh_guarded_call<void>::operator___class__lambda_38edbb1296d33220d7e4dd0ed76b244a__class__lambda_5ce1d447e08cb34b2473517608e21441___class__lambda_fb385d3da700c9147fc39e65dd577a8c___
              (&local_5,(_lambda_38edbb1296d33220d7e4dd0ed76b244a_ *)&local_14,(_lambda_5ce1d447e08cb34b2473517608e21441_ *)&local_10,(_lambda_fb385d3da700c9147fc39e65dd577a8c_ *)&local_c);
    local_10 = &param_1;
    local_14 = 0x4;
    local_c = 0x4;
    __crt_seh_guarded_call<void>::operator___class__lambda_6affb1475c98b40b75cdec977db92e3c__class__lambda_b8d4b9c228a6ecc3f80208dbb4b4a104___class__lambda_608742c3c92a14382c1684fc64f96c88___
              (&local_5,(_lambda_6affb1475c98b40b75cdec977db92e3c_ *)&local_c,(_lambda_b8d4b9c228a6ecc3f80208dbb4b4a104_ *)&local_10,(_lambda_608742c3c92a14382c1684fc64f96c88_ *)&local_14);
    return;
}



// Library Function - Single Match
//  void __cdecl replace_current_thread_locale_nolock(struct __acrt_ptd * const,struct __crt_locale_data * const)
// 
// Library: Visual Studio 2019 Release

void __cdecl replace_current_thread_locale_nolock(__acrt_ptd *param_1,__crt_locale_data *param_2)

{
    undefined **ppuVar1;
    
    if (*(int *)(param_1 + 0x4c) != 0x0) {
        ___acrt_release_locale_ref(*(int *)(param_1 + 0x4c));
        ppuVar1 = *(undefined ***)(param_1 + 0x4c);
        if (((ppuVar1 != DAT_1001646c) && (ppuVar1 != &PTR_DAT_10015690)) && (ppuVar1[0x3] == NULL)) {
            ___acrt_free_locale((int)ppuVar1);
        }
    }
    *(__crt_locale_data **)(param_1 + 0x4c) = param_2;
    if (param_2 != NULL) {
        ___acrt_add_locale_ref((int)param_2);
    }
    return;
}



// Library Function - Single Match
//  ___acrt_freeptd
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void ___acrt_freeptd(void)

{
    void *pvVar1;
    
    if ((DAT_10015160 != 0xffffffff) && (pvVar1 = (void *)___acrt_FlsGetValue_4(DAT_10015160), pvVar1 != NULL)) {
        ___acrt_FlsSetValue_8(DAT_10015160,NULL);
        destroy_fls(pvVar1);
    }
    return;
}



__acrt_ptd * FUN_10005827(void)

{
    code *pcVar1;
    DWORD dwErrCode;
    uint uVar2;
    int iVar3;
    __acrt_ptd *p_Var4;
    __acrt_ptd *p_Var5;
    
    dwErrCode = GetLastError();
    if ((DAT_10015160 == 0xffffffff) || (uVar2 = ___acrt_FlsGetValue_4(DAT_10015160), uVar2 == 0x0)) {
        iVar3 = ___acrt_FlsSetValue_8(DAT_10015160,(LPVOID)0xffffffff);
        if (iVar3 == 0x0) {
            p_Var4 = NULL;
        }
        else {
            p_Var4 = (__acrt_ptd *)__calloc_base(0x1,0x364);
            if (p_Var4 == NULL) {
                ___acrt_FlsSetValue_8(DAT_10015160,NULL);
                p_Var5 = NULL;
            }
            else {
                iVar3 = ___acrt_FlsSetValue_8(DAT_10015160,p_Var4);
                if (iVar3 != 0x0) {
                    construct_ptd(p_Var4,(__crt_locale_data **)&DAT_1001646c);
                    FUN_10005f59(NULL);
                    goto LAB_100058cc;
                }
                ___acrt_FlsSetValue_8(DAT_10015160,NULL);
                p_Var5 = p_Var4;
            }
            p_Var4 = NULL;
            FUN_10005f59(p_Var5);
        }
    }
    else {
        p_Var4 = (__acrt_ptd *)(-(uint)(uVar2 != 0xffffffff) & uVar2);
    }
LAB_100058cc:
    SetLastError(dwErrCode);
    if (p_Var4 == NULL) {
        _abort();
        pcVar1 = (code *)swi(0x3);
        p_Var4 = (__acrt_ptd *)(*pcVar1)();
        return p_Var4;
    }
    return p_Var4;
}



__acrt_ptd * FUN_100058e2(void)

{
    code *pcVar1;
    __acrt_ptd *p_Var2;
    int iVar3;
    
    if ((DAT_10015160 == 0xffffffff) || (p_Var2 = (__acrt_ptd *)___acrt_FlsGetValue_4(DAT_10015160), p_Var2 == NULL)) {
        iVar3 = ___acrt_FlsSetValue_8(DAT_10015160,(LPVOID)0xffffffff);
        if (iVar3 != 0x0) {
            p_Var2 = (__acrt_ptd *)__calloc_base(0x1,0x364);
            if (p_Var2 == NULL) {
                ___acrt_FlsSetValue_8(DAT_10015160,NULL);
            }
            else {
                iVar3 = ___acrt_FlsSetValue_8(DAT_10015160,p_Var2);
                if (iVar3 != 0x0) {
                    construct_ptd(p_Var2,(__crt_locale_data **)&DAT_1001646c);
                    FUN_10005f59(NULL);
                    return p_Var2;
                }
                ___acrt_FlsSetValue_8(DAT_10015160,NULL);
            }
            FUN_10005f59(p_Var2);
        }
    }
    else if (p_Var2 != (__acrt_ptd *)0xffffffff) {
        return p_Var2;
    }
    _abort();
    pcVar1 = (code *)swi(0x3);
    p_Var2 = (__acrt_ptd *)(*pcVar1)();
    return p_Var2;
}



__acrt_ptd * FUN_10005978(void)

{
    DWORD dwErrCode;
    uint uVar1;
    int iVar2;
    __acrt_ptd *p_Var3;
    __acrt_ptd *p_Var4;
    
    dwErrCode = GetLastError();
    if ((DAT_10015160 == 0xffffffff) || (uVar1 = ___acrt_FlsGetValue_4(DAT_10015160), uVar1 == 0x0)) {
        iVar2 = ___acrt_FlsSetValue_8(DAT_10015160,(LPVOID)0xffffffff);
        if (iVar2 == 0x0) {
            p_Var3 = NULL;
        }
        else {
            p_Var3 = (__acrt_ptd *)__calloc_base(0x1,0x364);
            if (p_Var3 == NULL) {
                ___acrt_FlsSetValue_8(DAT_10015160,NULL);
                p_Var4 = NULL;
            }
            else {
                iVar2 = ___acrt_FlsSetValue_8(DAT_10015160,p_Var3);
                if (iVar2 != 0x0) {
                    construct_ptd(p_Var3,(__crt_locale_data **)&DAT_1001646c);
                    FUN_10005f59(NULL);
                    goto LAB_10005a1d;
                }
                ___acrt_FlsSetValue_8(DAT_10015160,NULL);
                p_Var4 = p_Var3;
            }
            p_Var3 = NULL;
            FUN_10005f59(p_Var4);
        }
    }
    else {
        p_Var3 = (__acrt_ptd *)(-(uint)(uVar1 != 0xffffffff) & uVar1);
    }
LAB_10005a1d:
    SetLastError(dwErrCode);
    return p_Var3;
}



__acrt_ptd * __cdecl FUN_10005a29(undefined4 param_1,int param_2)

{
    __acrt_ptd *p_Var1;
    int iVar2;
    __acrt_ptd *p_Var3;
    
    p_Var3 = NULL;
    if ((DAT_10015160 == 0xffffffff) || (p_Var1 = (__acrt_ptd *)___acrt_FlsGetValue_4(DAT_10015160), p_Var1 == NULL)) {
        iVar2 = ___acrt_FlsSetValue_8(DAT_10015160,(LPVOID)0xffffffff);
        if (iVar2 == 0x0) {
            return NULL;
        }
        p_Var1 = (__acrt_ptd *)__calloc_base(0x1,0x364);
        if (p_Var1 == NULL) {
            ___acrt_FlsSetValue_8(DAT_10015160,NULL);
            p_Var1 = NULL;
        }
        else {
            iVar2 = ___acrt_FlsSetValue_8(DAT_10015160,p_Var1);
            if (iVar2 != 0x0) {
                construct_ptd(p_Var1,(__crt_locale_data **)&DAT_1001646c);
                FUN_10005f59(NULL);
                goto LAB_10005abd;
            }
            ___acrt_FlsSetValue_8(DAT_10015160,NULL);
        }
        FUN_10005f59(p_Var1);
    }
    else {
        if (p_Var1 == (__acrt_ptd *)0xffffffff) {
            return NULL;
        }
LAB_10005abd:
        p_Var3 = p_Var1 + param_2 * 0x364;
    }
    return p_Var3;
}



// Library Function - Single Match
//  ___acrt_uninitialize_ptd
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

undefined4 ___acrt_uninitialize_ptd(void)

{
    DWORD DVar1;
    
    DVar1 = DAT_10015160;
    if (DAT_10015160 != 0xffffffff) {
        DVar1 = ___acrt_FlsFree_4(DAT_10015160);
        DAT_10015160 = 0xffffffff;
    }
    return CONCAT31((int3)(DVar1 >> 0x8),0x1);
}



// Library Function - Single Match
//  ___acrt_lock
// 
// Library: Visual Studio 2019 Release

void __cdecl ___acrt_lock(int param_1)

{
    EnterCriticalSection((LPCRITICAL_SECTION)(&DAT_10015fe8 + param_1 * 0x18));
    return;
}



undefined4 FUN_10005b6a(void)

{
    undefined4 in_EAX;
    undefined4 extraout_EAX;
    int iVar1;
    LPCRITICAL_SECTION lpCriticalSection;
    
    if (DAT_10016138 != 0x0) {
        lpCriticalSection = (LPCRITICAL_SECTION)(&DAT_10015fd0 + DAT_10016138 * 0x18);
        iVar1 = DAT_10016138;
        do {
            DeleteCriticalSection(lpCriticalSection);
            DAT_10016138 = DAT_10016138 + -0x1;
            lpCriticalSection = lpCriticalSection + -0x1;
            iVar1 = iVar1 + -0x1;
            in_EAX = extraout_EAX;
        } while (iVar1 != 0x0);
    }
    return CONCAT31((int3)((uint)in_EAX >> 0x8),0x1);
}



// Library Function - Single Match
//  ___acrt_unlock
// 
// Library: Visual Studio 2019 Release

void __cdecl ___acrt_unlock(int param_1)

{
    LeaveCriticalSection((LPCRITICAL_SECTION)(&DAT_10015fe8 + param_1 * 0x18));
    return;
}



// Library Function - Single Match
//  ___acrt_get_process_end_policy
// 
// Library: Visual Studio 2019 Release

undefined4 ___acrt_get_process_end_policy(void)

{
    int in_FS_OFFSET;
    int local_8;
    
    local_8 = 0x0;
    if ((-0x1 < *(int *)(*(int *)(*(int *)(in_FS_OFFSET + 0x30) + 0x10) + 0x8)) && (___acrt_AppPolicyGetProcessTerminationMethodInternal_4(&local_8), local_8 == 0x1)) {
        return 0x0;
    }
    return 0x1;
}



undefined4 __fastcall FUN_10005be3(int param_1)

{
    DWORD dwErrCode;
    
    if (*(char *)(param_1 + 0x8) == '\0') {
        dwErrCode = GetLastError();
        *(undefined4 *)(param_1 + 0x4) = 0x0;
        *(undefined *)(param_1 + 0x8) = 0x1;
        SetLastError(dwErrCode);
        return 0x0;
    }
    return *(undefined4 *)(param_1 + 0x4);
}



// Library Function - Single Match
//  ___acrt_call_reportfault
// 
// Library: Visual Studio 2019 Release

void __cdecl ___acrt_call_reportfault(int param_1,DWORD param_2,DWORD param_3)

{
    uint uVar1;
    BOOL BVar2;
    LONG LVar3;
    undefined extraout_DL;
    undefined extraout_DL_00;
    undefined uVar4;
    undefined uVar5;
    DWORD local_324;
    DWORD local_320;
    undefined4 local_2d4 [0x27];
    
    uVar1 = DAT_10015124 ^ (uint)&stack0xfffffffc;
    if (param_1 != -0x1) {
        FUN_10001d0f();
    }
    _memset(&local_324,0x0,0x50);
    _memset(local_2d4,0x0,0x2cc);
    uVar5 = SUB41(&local_324,0x0);
    local_2d4[0] = 0x10001;
    local_324 = param_2;
    local_320 = param_3;
    BVar2 = IsDebuggerPresent();
    SetUnhandledExceptionFilter(NULL);
    LVar3 = UnhandledExceptionFilter((_EXCEPTION_POINTERS *)&stack0xfffffcd4);
    uVar4 = extraout_DL;
    if (((LVar3 == 0x0) && (BVar2 == 0x0)) && (param_1 != -0x1)) {
        FUN_10001d0f();
        uVar4 = extraout_DL_00;
    }
    FUN_10001f99(uVar1 ^ (uint)&stack0xfffffffc,uVar4,uVar5);
    return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void __cdecl FUN_10005d45(undefined4 param_1)

{
    _DAT_1001613c = param_1;
    return;
}



void __cdecl FUN_10005d54(wchar_t *param_1,wchar_t *param_2,wchar_t *param_3,uint param_4,uintptr_t param_5)

{
    __acrt_ptd *local_2c [0xa];
    
    FUN_10005250(local_2c,NULL);
    FUN_10005d8b(param_1,param_2,param_3,param_4,param_5,local_2c);
    FUN_100052b0(local_2c);
    return;
}



void __cdecl FUN_10005d8b(wchar_t *param_1,wchar_t *param_2,wchar_t *param_3,uint param_4,uintptr_t param_5,__acrt_ptd **param_6)

{
    __acrt_ptd *p_Var1;
    int iVar2;
    byte bVar3;
    code *pcVar4;
    
    p_Var1 = *param_6;
    if (((p_Var1 == NULL) && (p_Var1 = FUN_100052f0(param_6), p_Var1 == NULL)) || (pcVar4 = *(code **)(p_Var1 + 0x35c), pcVar4 == NULL)) {
        iVar2 = FUN_10005be3((int)param_6);
        bVar3 = (byte)DAT_10015124 & 0x1f;
        pcVar4 = (code *)((*(uint *)(&DAT_1001613c + iVar2 * 0x4) ^ DAT_10015124) >> bVar3 | (*(uint *)(&DAT_1001613c + iVar2 * 0x4) ^ DAT_10015124) << 0x20 - bVar3);
        if (pcVar4 == NULL) {
            __invoke_watson(param_1,param_2,param_3,param_4,param_5);
            pcVar4 = (code *)swi(0x3);
            (*pcVar4)();
            return;
        }
    }
    _guard_check_icall();
    (*pcVar4)(param_1,param_2,param_3,param_4,param_5);
    return;
}



void FUN_10005e08(void)

{
    FUN_10005d54(NULL,NULL,NULL,0x0,0x0);
    return;
}



// Library Function - Single Match
//  __invoke_watson
// 
// Library: Visual Studio 2019 Release

void __cdecl __invoke_watson(wchar_t *param_1,wchar_t *param_2,wchar_t *param_3,uint param_4,uintptr_t param_5)

{
    code *pcVar1;
    BOOL BVar2;
    HANDLE hProcess;
    UINT uExitCode;
    
    BVar2 = IsProcessorFeaturePresent(0x17);
    if (BVar2 != 0x0) {
        pcVar1 = (code *)swi(0x29);
        (*pcVar1)();
    }
    ___acrt_call_reportfault(0x2,0xc0000417,0x1);
    uExitCode = 0xc0000417;
    hProcess = GetCurrentProcess();
    TerminateProcess(hProcess,uExitCode);
    return;
}



// Library Function - Multiple Matches With Different Base Names
//  ___acrt_errno_from_os_error
//  __get_errno_from_oserr
// 
// Libraries: Visual Studio 2012 Release, Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

int __cdecl FID_conflict____acrt_errno_from_os_error(ulong param_1)

{
    uint uVar1;
    
    uVar1 = 0x0;
    do {
        if (param_1 == (&DAT_1000edb0)[uVar1 * 0x2]) {
            return (&DAT_1000edb4)[uVar1 * 0x2];
        }
        uVar1 = uVar1 + 0x1;
    } while (uVar1 < 0x2d);
    if (param_1 - 0x13 < 0x12) {
        return 0xd;
    }
    return (-(uint)(0xe < param_1 - 0xbc) & 0xe) + 0x8;
}



// Library Function - Single Match
//  ___acrt_errno_map_os_error
// 
// Library: Visual Studio 2019 Release

void __cdecl ___acrt_errno_map_os_error(ulong param_1)

{
    ulong *puVar1;
    int iVar2;
    int *piVar3;
    
    puVar1 = (ulong *)FUN_10005ed6();
    *puVar1 = param_1;
    iVar2 = FID_conflict____acrt_errno_from_os_error(param_1);
    piVar3 = (int *)FUN_10005ee9();
    *piVar3 = iVar2;
    return;
}



void __cdecl FUN_10005eb2(ulong param_1,int param_2)

{
    int iVar1;
    
    *(undefined *)(param_2 + 0x24) = 0x1;
    *(ulong *)(param_2 + 0x20) = param_1;
    iVar1 = FID_conflict____acrt_errno_from_os_error(param_1);
    *(undefined *)(param_2 + 0x1c) = 0x1;
    *(int *)(param_2 + 0x18) = iVar1;
    return;
}



__acrt_ptd * FUN_10005ed6(void)

{
    __acrt_ptd *p_Var1;
    
    p_Var1 = FUN_10005978();
    if (p_Var1 == NULL) {
        return (__acrt_ptd *)&DAT_10015168;
    }
    return p_Var1 + 0x14;
}



__acrt_ptd * FUN_10005ee9(void)

{
    __acrt_ptd *p_Var1;
    
    p_Var1 = FUN_10005978();
    if (p_Var1 == NULL) {
        return (__acrt_ptd *)&DAT_10015164;
    }
    return p_Var1 + 0x10;
}



// Library Function - Single Match
//  __calloc_base
// 
// Library: Visual Studio 2019 Release

LPVOID __cdecl __calloc_base(uint param_1,uint param_2)

{
    int iVar1;
    LPVOID pvVar2;
    undefined4 *puVar3;
    size_t dwBytes;
    
    if ((param_1 == 0x0) || (param_2 <= 0xffffffe0 / param_1)) {
        dwBytes = param_1 * param_2;
        if (dwBytes == 0x0) {
            dwBytes = 0x1;
        }
        do {
            pvVar2 = HeapAlloc(DAT_10016248,0x8,dwBytes);
            if (pvVar2 != NULL) {
                return pvVar2;
            }
            iVar1 = FUN_10008a8c();
        } while ((iVar1 != 0x0) && (iVar1 = __callnewh(dwBytes), iVar1 != 0x0));
    }
    puVar3 = (undefined4 *)FUN_10005ee9();
    *puVar3 = 0xc;
    return NULL;
}



void __cdecl FUN_10005f59(LPVOID param_1)

{
    BOOL BVar1;
    DWORD DVar2;
    int iVar3;
    int *piVar4;
    
    if (param_1 != NULL) {
        BVar1 = HeapFree(DAT_10016248,0x0,param_1);
        if (BVar1 == 0x0) {
            DVar2 = GetLastError();
            iVar3 = FID_conflict____acrt_errno_from_os_error(DVar2);
            piVar4 = (int *)FUN_10005ee9();
            *piVar4 = iVar3;
        }
    }
    return;
}



uint __cdecl FUN_10005f93(uint param_1,uint param_2)

{
    if (param_2 >= param_1 && param_2 != param_1) {
        return 0xffffffff;
    }
    return (uint)(param_2 < param_1);
}



// Library Function - Single Match
//  int __cdecl __acrt_convert_wcs_mbs_cp<char,wchar_t,class <lambda_62f6974d9771e494a5ea317cc32e971c>,struct __crt_win32_buffer_internal_dynamic_resizing>(char const * const,class
// __crt_win32_buffer<wchar_t,struct __crt_win32_buffer_internal_dynamic_resizing>&,class <lambda_62f6974d9771e494a5ea317cc32e971c> const &,unsigned int)
// 
// Library: Visual Studio 2019 Release

int __cdecl
__acrt_convert_wcs_mbs_cp_char_wchar_t_class__lambda_62f6974d9771e494a5ea317cc32e971c__struct___crt_win32_buffer_internal_dynamic_resizing_
          (char *param_1,__crt_win32_buffer_wchar_t_struct___crt_win32_buffer_internal_dynamic_resizing_ *param_2,_lambda_62f6974d9771e494a5ea317cc32e971c_ *param_3,uint param_4)

{
    int iVar1;
    uint uVar2;
    DWORD DVar3;
    int *piVar4;
    
    if (param_1 == NULL) {
        __crt_win32_buffer<wchar_t,struct___crt_win32_buffer_internal_dynamic_resizing>::_deallocate(param_2);
        *(undefined4 *)(param_2 + 0x8) = 0x0;
        *(undefined4 *)(param_2 + 0xc) = 0x0;
    }
    else {
        if (*param_1 != '\0') {
            uVar2 = ___acrt_MultiByteToWideChar(param_4,0x9,param_1,-0x1,NULL,0x0);
            if (uVar2 != 0x0) {
                if ((*(uint *)(param_2 + 0xc) <= uVar2 && uVar2 != *(uint *)(param_2 + 0xc)) &&
                   (iVar1 = __crt_win32_buffer<wchar_t,struct___crt_win32_buffer_internal_dynamic_resizing>::allocate(param_2,uVar2), iVar1 != 0x0)) {
                    return iVar1;
                }
                iVar1 = ___acrt_MultiByteToWideChar(param_4,0x9,param_1,-0x1,*(LPWSTR *)(param_2 + 0x8),*(int *)(param_2 + 0xc));
                if (iVar1 != 0x0) {
                    *(int *)(param_2 + 0x10) = iVar1 + -0x1;
                    return 0x0;
                }
            }
            DVar3 = GetLastError();
            ___acrt_errno_map_os_error(DVar3);
            piVar4 = (int *)FUN_10005ee9();
            return *piVar4;
        }
        if ((*(int *)(param_2 + 0xc) == 0x0) && (iVar1 = __crt_win32_buffer<wchar_t,struct___crt_win32_buffer_internal_dynamic_resizing>::allocate(param_2,0x1), iVar1 != 0x0)) {
            return iVar1;
        }
        **(undefined2 **)(param_2 + 0x8) = 0x0;
    }
    *(undefined4 *)(param_2 + 0x10) = 0x0;
    return 0x0;
}



int __cdecl FUN_1000605d(LPCWSTR param_1,__crt_win32_buffer_wchar_t_struct___crt_win32_buffer_internal_dynamic_resizing_ *param_2,undefined4 param_3,uint param_4)

{
    int iVar1;
    uint uVar2;
    DWORD DVar3;
    int *piVar4;
    
    if (param_1 == NULL) {
        __crt_win32_buffer<wchar_t,struct___crt_win32_buffer_internal_dynamic_resizing>::_deallocate(param_2);
        *(undefined4 *)(param_2 + 0x8) = 0x0;
        *(undefined4 *)(param_2 + 0xc) = 0x0;
    }
    else {
        if (*param_1 != L'\0') {
            uVar2 = ___acrt_WideCharToMultiByte(param_4,0x0,param_1,-0x1,NULL,0x0,0x0,NULL);
            if (uVar2 == 0x0) {
                DVar3 = GetLastError();
                ___acrt_errno_map_os_error(DVar3);
                piVar4 = (int *)FUN_10005ee9();
                return *piVar4;
            }
            if ((*(uint *)(param_2 + 0xc) <= uVar2 && uVar2 != *(uint *)(param_2 + 0xc)) && (iVar1 = allocate(param_2,uVar2), iVar1 != 0x0)) {
                return iVar1;
            }
            iVar1 = FID_conflict_operator__(param_4,param_1,*(LPSTR *)(param_2 + 0x8),*(int *)(param_2 + 0xc));
            if (iVar1 == 0x0) {
                DVar3 = GetLastError();
                ___acrt_errno_map_os_error(DVar3);
                piVar4 = (int *)FUN_10005ee9();
                return *piVar4;
            }
            *(int *)(param_2 + 0x10) = iVar1 + -0x1;
            return 0x0;
        }
        if ((*(int *)(param_2 + 0xc) == 0x0) && (iVar1 = allocate(param_2,0x1), iVar1 != 0x0)) {
            return iVar1;
        }
        **(undefined **)(param_2 + 0x8) = 0x0;
    }
    *(undefined4 *)(param_2 + 0x10) = 0x0;
    return 0x0;
}



// Library Function - Single Match
//  int __cdecl __acrt_mbs_to_wcs_cp<struct __crt_win32_buffer_internal_dynamic_resizing>(char const * const,class __crt_win32_buffer<wchar_t,struct
// __crt_win32_buffer_internal_dynamic_resizing>&,unsigned int)
// 
// Libraries: Visual Studio 2019 Debug, Visual Studio 2019 Release

int __cdecl
__acrt_mbs_to_wcs_cp_struct___crt_win32_buffer_internal_dynamic_resizing_(char *param_1,__crt_win32_buffer_wchar_t_struct___crt_win32_buffer_internal_dynamic_resizing_ *param_2,uint param_3)

{
    int iVar1;
    _lambda_62f6974d9771e494a5ea317cc32e971c_ local_5;
    
    iVar1 = __acrt_convert_wcs_mbs_cp_char_wchar_t_class__lambda_62f6974d9771e494a5ea317cc32e971c__struct___crt_win32_buffer_internal_dynamic_resizing_(param_1,param_2,&local_5,param_3);
    return iVar1;
}



// Library Function - Single Match
//  int __cdecl copy_and_add_argument_to_buffer<char>(char const * const,char const * const,unsigned int,class `anonymous namespace'::argument_list<char>&)
// 
// Library: Visual Studio 2019 Release

int __cdecl copy_and_add_argument_to_buffer_char_(char *param_1,char *param_2,uint param_3,argument_list_char_ *param_4)

{
    char cVar1;
    code *pcVar2;
    int iVar3;
    char *pcVar4;
    char *pcVar5;
    char *pcVar6;
    
    pcVar5 = param_1;
    do {
        cVar1 = *pcVar5;
        pcVar5 = pcVar5 + 0x1;
    } while (cVar1 != '\0');
    pcVar5 = pcVar5 + (0x1 - (int)(param_1 + 0x1));
    if ((char *)~param_3 < pcVar5) {
        iVar3 = 0xc;
    }
    else {
        pcVar6 = pcVar5 + param_3 + 0x1;
        pcVar4 = (char *)__calloc_base((uint)pcVar6,0x1);
        if (param_3 != 0x0) {
            iVar3 = FUN_10009045(pcVar4,(int)pcVar6,(int)param_2,param_3);
            if (iVar3 != 0x0) goto LAB_10006361;
        }
        iVar3 = FUN_10009045(pcVar4 + param_3,(int)pcVar6 - param_3,(int)param_1,(int)pcVar5);
        if (iVar3 != 0x0) {
LAB_10006361:
            __invoke_watson(NULL,NULL,NULL,0x0,0x0);
            pcVar2 = (code *)swi(0x3);
            iVar3 = (*pcVar2)();
            return iVar3;
        }
        iVar3 = `anonymous_namespace'::argument_list<char>::expand_if_necessary(param_4);
        if (iVar3 == 0x0) {
            **(char ***)(param_4 + 0x4) = pcVar4;
            iVar3 = 0x0;
            *(int *)(param_4 + 0x4) = *(int *)(param_4 + 0x4) + 0x4;
        }
        else {
            FUN_10005f59(pcVar4);
        }
        FUN_10005f59(NULL);
    }
    return iVar3;
}



void __cdecl FUN_1000636e(uchar *param_1,uchar *param_2,int *param_3)

{
    uchar uVar1;
    byte bVar2;
    uint uVar3;
    int iVar4;
    HANDLE hFindFile;
    int iVar5;
    char *pcVar6;
    BOOL BVar7;
    undefined extraout_DL;
    undefined extraout_DL_00;
    undefined extraout_DL_01;
    undefined extraout_DL_02;
    undefined extraout_DL_03;
    undefined extraout_DL_04;
    undefined extraout_DL_05;
    undefined uVar8;
    undefined uVar9;
    int in_stack_fffffd64;
    undefined4 local_290;
    undefined4 local_28c;
    LPVOID local_288;
    undefined4 local_284;
    undefined4 local_280;
    char local_27c;
    undefined4 local_278;
    undefined4 local_274;
    LPVOID local_270;
    undefined4 local_26c;
    undefined4 local_268;
    char local_264;
    int *local_260;
    uchar local_259;
    _WIN32_FIND_DATAW local_258;
    uint local_8;
    
    local_8 = DAT_10015124 ^ (uint)&stack0xfffffffc;
    local_260 = param_3;
    if (param_2 != param_1) {
        do {
            uVar1 = *param_2;
            if (((uVar1 == '/') || (uVar1 == '\\')) || (uVar1 == ':')) break;
            param_2 = __mbsdec(param_1,param_2);
        } while (param_2 != param_1);
    }
    uVar9 = (undefined)in_stack_fffffd64;
    local_259 = *param_2;
    if ((local_259 == ':') && (param_2 != param_1 + 0x1)) {
        copy_and_add_argument_to_buffer_char_((char *)param_1,NULL,0x0,(argument_list_char_ *)local_260);
        uVar8 = extraout_DL;
    }
    else {
        if (((local_259 == '/') || (local_259 == '\\')) || (bVar2 = 0x0, local_259 == ':')) {
            bVar2 = 0x1;
        }
        local_290 = 0x0;
        local_28c = 0x0;
        local_288 = NULL;
        local_284 = 0x0;
        local_280 = 0x0;
        local_27c = '\0';
        uVar3 = __acrt_get_utf8_acp_compatibility_codepage();
        iVar4 = __acrt_mbs_to_wcs_cp_struct___crt_win32_buffer_internal_dynamic_resizing_
                          ((char *)param_1,(__crt_win32_buffer_wchar_t_struct___crt_win32_buffer_internal_dynamic_resizing_ *)&local_290,uVar3);
        hFindFile = FindFirstFileExW((LPCWSTR)(~-(uint)(iVar4 != 0x0) & (uint)local_288),FindExInfoStandard,&local_258,FindExSearchNameMatch,NULL,0x0);
        uVar9 = (undefined)in_stack_fffffd64;
        if (hFindFile == (HANDLE)0xffffffff) {
            copy_and_add_argument_to_buffer_char_((char *)param_1,NULL,0x0,(argument_list_char_ *)local_260);
            uVar8 = extraout_DL_00;
            if (local_27c != '\0') {
                FUN_10005f59(local_288);
                uVar8 = extraout_DL_01;
            }
        }
        else {
            iVar4 = local_260[0x1] - *local_260 >> 0x2;
            do {
                local_278 = 0x0;
                local_274 = 0x0;
                local_270 = NULL;
                local_26c = 0x0;
                local_268 = 0x0;
                local_264 = '\0';
                uVar3 = __acrt_get_utf8_acp_compatibility_codepage();
                iVar5 = FUN_1000605d(local_258.cFileName,(__crt_win32_buffer_wchar_t_struct___crt_win32_buffer_internal_dynamic_resizing_ *)&local_278,&local_259,uVar3);
                pcVar6 = (char *)(~-(uint)(iVar5 != 0x0) & (uint)local_270);
                if (((*pcVar6 != '.') || ((pcVar6[0x1] != '\0' && ((pcVar6[0x1] != '.' || (pcVar6[0x2] != '\0')))))) &&
                   (in_stack_fffffd64 = copy_and_add_argument_to_buffer_char_(pcVar6,(char *)param_1,-(uint)bVar2 & (uint)(param_2 + (0x1 - (int)param_1)),(argument_list_char_ *)local_260),
                   in_stack_fffffd64 != 0x0)) {
                    if (local_264 != '\0') {
                        FUN_10005f59(local_270);
                    }
                    uVar9 = (undefined)in_stack_fffffd64;
                    FindClose(hFindFile);
                    uVar8 = extraout_DL_04;
                    if (local_27c != '\0') {
                        FUN_10005f59(local_288);
                        uVar8 = extraout_DL_05;
                    }
                    goto LAB_100065e5;
                }
                if (local_264 != '\0') {
                    FUN_10005f59(local_270);
                }
                BVar7 = FindNextFileW(hFindFile,&local_258);
                uVar9 = (undefined)in_stack_fffffd64;
            } while (BVar7 != 0x0);
            iVar5 = local_260[0x1] - *local_260 >> 0x2;
            if (iVar4 != iVar5) {
                _qsort((void *)(*local_260 + iVar4 * 0x4),iVar5 - iVar4,0x4,FUN_10005f93);
            }
            FindClose(hFindFile);
            uVar8 = extraout_DL_02;
            if (local_27c != '\0') {
                FUN_10005f59(local_288);
                uVar8 = extraout_DL_03;
            }
        }
    }
LAB_100065e5:
    FUN_10001f99(local_8 ^ (uint)&stack0xfffffffc,uVar8,uVar9);
    return;
}



__acrt_ptd ** __thiscall FUN_100065f3(void *this,__acrt_ptd **param_1)

{
    __acrt_ptd **pp_Var1;
    uint uVar2;
    __acrt_ptd *p_Var3;
    __acrt_ptd *p_Var4;
    
    *(undefined *)((int)this + 0xc) = 0x0;
    pp_Var1 = (__acrt_ptd **)((int)this + 0x4);
    if (param_1 == NULL) {
        p_Var3 = (__acrt_ptd *)PTR_PTR_DAT_10015748;
        p_Var4 = (__acrt_ptd *)PTR_DAT_1001574c;
        if (DAT_10016488 != 0x0) {
            p_Var3 = FUN_10005827();
            *(__acrt_ptd **)this = p_Var3;
            *pp_Var1 = *(__acrt_ptd **)(p_Var3 + 0x4c);
            *(int *)((int)this + 0x8) = *(int *)(p_Var3 + 0x48);
            ___acrt_update_locale_info((int)p_Var3,(int *)pp_Var1);
                    // WARNING: Load size is inaccurate
            FUN_1000849a(*this,(int *)((int)this + 0x8));
                    // WARNING: Load size is inaccurate
            uVar2 = *(uint *)(*this + 0x350);
            if ((uVar2 & 0x2) != 0x0) {
                return (__acrt_ptd **)this;
            }
            *(uint *)(*this + 0x350) = uVar2 | 0x2;
            *(undefined *)((int)this + 0xc) = 0x1;
            return (__acrt_ptd **)this;
        }
    }
    else {
        p_Var3 = *param_1;
        p_Var4 = param_1[0x1];
    }
    *pp_Var1 = p_Var3;
    *(__acrt_ptd **)((int)this + 0x8) = p_Var4;
    return (__acrt_ptd **)this;
}



void __fastcall FUN_10006675(int *param_1)

{
    LPVOID *ppvVar1;
    
    ppvVar1 = (LPVOID *)*param_1;
    if (ppvVar1 != (LPVOID *)param_1[0x1]) {
        do {
            FUN_10005f59(*ppvVar1);
            ppvVar1 = ppvVar1 + 0x1;
        } while (ppvVar1 != (LPVOID *)param_1[0x1]);
        ppvVar1 = (LPVOID *)*param_1;
    }
    FUN_10005f59(ppvVar1);
    return;
}



// Library Function - Multiple Matches With Different Base Names
//  public: int __thiscall <lambda_0fec1a7b3f42a53036604e18c2d5e07e>::operator()(unsigned int,wchar_t const * const,char * const,unsigned int)const 
//  public: int __thiscall <lambda_28bda7af82a03b66c1cb3803a755f95d>::operator()(unsigned int,wchar_t const * const,char * const,unsigned int)const 
//  public: int __thiscall <lambda_fecc33a432ccb74a901dff60d61ca385>::operator()(unsigned int,wchar_t const * const,char * const,unsigned int)const 
// 
// Library: Visual Studio 2019 Release

void FID_conflict_operator__(uint param_1,LPCWSTR param_2,LPSTR param_3,int param_4)

{
    ___acrt_WideCharToMultiByte(param_1,0x0,param_2,-0x1,param_3,param_4,0x0,NULL);
    return;
}



// Library Function - Single Match
//  unsigned int __cdecl __acrt_get_utf8_acp_compatibility_codepage(void)
// 
// Library: Visual Studio 2019 Release

uint __cdecl __acrt_get_utf8_acp_compatibility_codepage(void)

{
    int iVar1;
    uint uVar2;
    int local_14;
    int local_10;
    char local_8;
    
    FUN_100065f3(&local_14,NULL);
    uVar2 = 0xfde9;
    if (*(int *)(local_10 + 0x8) != 0xfde9) {
        iVar1 = ___acrt_AreFileApisANSI_0();
        uVar2 = 0x0;
        if (iVar1 == 0x0) {
            uVar2 = 0x1;
        }
    }
    if (local_8 != '\0') {
        *(uint *)(local_14 + 0x350) = *(uint *)(local_14 + 0x350) & 0xfffffffd;
    }
    return uVar2;
}



// Library Function - Single Match
//  private: void __thiscall __crt_win32_buffer<wchar_t,struct __crt_win32_buffer_internal_dynamic_resizing>::_deallocate(void)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void __thiscall __crt_win32_buffer<wchar_t,struct___crt_win32_buffer_internal_dynamic_resizing>::_deallocate(__crt_win32_buffer_wchar_t_struct___crt_win32_buffer_internal_dynamic_resizing_ *this)

{
    if (this[0x14] != (__crt_win32_buffer_wchar_t_struct___crt_win32_buffer_internal_dynamic_resizing_)0x0) {
        FUN_10005f59(*(LPVOID *)(this + 0x8));
        this[0x14] = (__crt_win32_buffer_wchar_t_struct___crt_win32_buffer_internal_dynamic_resizing_)0x0;
    }
    return;
}



// Library Function - Multiple Matches With Same Base Name
//  public: int __thiscall __crt_win32_buffer<char,struct __crt_win32_buffer_internal_dynamic_resizing>::allocate(unsigned int)
//  public: int __thiscall __crt_win32_buffer<char,struct __crt_win32_buffer_public_dynamic_resizing>::allocate(unsigned int)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

int __thiscall allocate(void *this,uint param_1)

{
    int iVar1;
    
    __crt_win32_buffer<wchar_t,struct___crt_win32_buffer_internal_dynamic_resizing>::_deallocate((__crt_win32_buffer_wchar_t_struct___crt_win32_buffer_internal_dynamic_resizing_ *)this);
    iVar1 = __crt_win32_buffer_internal_dynamic_resizing::allocate((void **)((int)this + 0x8),param_1,(__crt_win32_buffer_empty_debug_info *)this);
    if (iVar1 == 0x0) {
        *(undefined *)((int)this + 0x14) = 0x1;
        iVar1 = 0x0;
        *(uint *)((int)this + 0xc) = param_1;
    }
    else {
        *(undefined4 *)((int)this + 0xc) = 0x0;
        *(undefined *)((int)this + 0x14) = 0x0;
    }
    return iVar1;
}



// Library Function - Single Match
//  public: int __thiscall __crt_win32_buffer<wchar_t,struct __crt_win32_buffer_internal_dynamic_resizing>::allocate(unsigned int)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

int __thiscall
__crt_win32_buffer<wchar_t,struct___crt_win32_buffer_internal_dynamic_resizing>::allocate(__crt_win32_buffer_wchar_t_struct___crt_win32_buffer_internal_dynamic_resizing_ *this,uint param_1)

{
    int iVar1;
    
    _deallocate(this);
    iVar1 = __crt_win32_buffer_internal_dynamic_resizing::allocate((void **)(this + 0x8),param_1 * 0x2,(__crt_win32_buffer_empty_debug_info *)this);
    if (iVar1 == 0x0) {
        this[0x14] = (__crt_win32_buffer_wchar_t_struct___crt_win32_buffer_internal_dynamic_resizing_)0x1;
        iVar1 = 0x0;
        *(uint *)(this + 0xc) = param_1;
    }
    else {
        *(undefined4 *)(this + 0xc) = 0x0;
        this[0x14] = (__crt_win32_buffer_wchar_t_struct___crt_win32_buffer_internal_dynamic_resizing_)0x0;
    }
    return iVar1;
}



// Library Function - Single Match
//  public: static int __cdecl __crt_win32_buffer_internal_dynamic_resizing::allocate(void * * const,unsigned int,class __crt_win32_buffer_empty_debug_info const &)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

int __cdecl __crt_win32_buffer_internal_dynamic_resizing::allocate(void **param_1,uint param_2,__crt_win32_buffer_empty_debug_info *param_3)

{
    LPVOID pvVar1;
    
    pvVar1 = __malloc_base(param_2);
    *param_1 = pvVar1;
    return (-(uint)(pvVar1 != NULL) & 0xfffffff4) + 0xc;
}



// Library Function - Single Match
//  private: int __thiscall `anonymous namespace'::argument_list<char>::expand_if_necessary(void)
// 
// Library: Visual Studio 2019 Release

int __thiscall `anonymous_namespace'::argument_list<char>::expand_if_necessary(argument_list_char_ *this)

{
    int iVar1;
    LPVOID pvVar2;
    uint uVar3;
    
    if (*(int *)(this + 0x4) == *(int *)(this + 0x8)) {
        if (*(int *)this == 0x0) {
            pvVar2 = __calloc_base(0x4,0x4);
            *(LPVOID *)this = pvVar2;
            FUN_10005f59(NULL);
            iVar1 = *(int *)this;
            if (iVar1 != 0x0) {
                *(int *)(this + 0x4) = iVar1;
                *(int *)(this + 0x8) = iVar1 + 0x10;
                goto LAB_100067c3;
            }
        }
        else {
            uVar3 = *(int *)(this + 0x8) - *(int *)this >> 0x2;
            if (uVar3 < 0x80000000) {
                pvVar2 = __recalloc_base(*(void **)this,uVar3 * 0x2,0x4);
                if (pvVar2 == NULL) {
                    iVar1 = 0xc;
                }
                else {
                    *(LPVOID *)this = pvVar2;
                    *(LPVOID *)(this + 0x4) = (LPVOID)((int)pvVar2 + uVar3 * 0x4);
                    *(LPVOID *)(this + 0x8) = (LPVOID)((int)pvVar2 + uVar3 * 0x8);
                    iVar1 = 0x0;
                }
                FUN_10005f59(NULL);
                return iVar1;
            }
        }
        iVar1 = 0xc;
    }
    else {
LAB_100067c3:
        iVar1 = 0x0;
    }
    return iVar1;
}



int __cdecl FUN_1000683c(uchar **param_1,LPVOID *param_2)

{
    char cVar1;
    code *pcVar2;
    undefined4 *puVar3;
    uchar *puVar4;
    LPVOID pvVar5;
    char *pcVar6;
    uint uVar7;
    int iVar8;
    char **ppcVar9;
    char **ppcVar10;
    char **local_24;
    char **local_20;
    undefined4 local_1c;
    int local_18;
    char *local_14;
    char *local_10;
    char *local_c;
    undefined4 local_8;
    
    if (param_2 == NULL) {
        puVar3 = (undefined4 *)FUN_10005ee9();
        iVar8 = 0x16;
        *puVar3 = 0x16;
        FUN_10005e08();
    }
    else {
        *param_2 = NULL;
        local_1c = 0x0;
        local_20 = NULL;
        local_24 = NULL;
        puVar4 = *param_1;
        ppcVar10 = local_24;
        while (local_24 = ppcVar10, puVar4 != NULL) {
            local_8 = (char *)CONCAT13((char)((uint)local_8 >> 0x18),0x3f2a);
            puVar4 = (uchar *)_strpbrk((char *)puVar4,(char *)&local_8);
            if (puVar4 == NULL) {
                iVar8 = copy_and_add_argument_to_buffer_char_((char *)*param_1,NULL,0x0,(argument_list_char_ *)&local_24);
            }
            else {
                iVar8 = FUN_1000636e(*param_1,puVar4,(int *)&local_24);
            }
            if (iVar8 != 0x0) goto LAB_10006227;
            param_1 = param_1 + 0x1;
            ppcVar10 = local_24;
            puVar4 = *param_1;
        }
        uVar7 = ((int)local_20 - (int)ppcVar10 >> 0x2) + 0x1;
        local_c = NULL;
        for (ppcVar9 = ppcVar10; ppcVar9 != local_20; ppcVar9 = ppcVar9 + 0x1) {
            pcVar6 = *ppcVar9;
            local_10 = pcVar6 + 0x1;
            do {
                cVar1 = *pcVar6;
                pcVar6 = pcVar6 + 0x1;
            } while (cVar1 != '\0');
            local_c = pcVar6 + (int)(local_c + (0x1 - (int)local_10));
        }
        pvVar5 = ___acrt_allocate_buffer_for_argv(uVar7,(uint)local_c,0x1);
        ppcVar9 = local_20;
        if (pvVar5 == NULL) {
            FUN_10005f59(NULL);
            iVar8 = -0x1;
LAB_10006227:
            FUN_10006675((int *)&local_24);
        }
        else {
            local_8 = (char *)((int)pvVar5 + uVar7 * 0x4);
            local_14 = local_8;
            if (ppcVar10 != local_20) {
                local_18 = (int)pvVar5 - (int)ppcVar10;
                do {
                    local_10 = *ppcVar10;
                    pcVar6 = local_10 + 0x1;
                    do {
                        cVar1 = *local_10;
                        local_10 = local_10 + 0x1;
                    } while (cVar1 != '\0');
                    local_10 = local_10 + (0x1 - (int)pcVar6);
                    iVar8 = FUN_10009045(local_8,(int)(local_14 + ((int)local_c - (int)local_8)),(int)*ppcVar10,(int)local_10);
                    if (iVar8 != 0x0) {
                        __invoke_watson(NULL,NULL,NULL,0x0,0x0);
                        pcVar2 = (code *)swi(0x3);
                        iVar8 = (*pcVar2)();
                        return iVar8;
                    }
                    *(char **)(local_18 + (int)ppcVar10) = local_8;
                    ppcVar10 = ppcVar10 + 0x1;
                    local_8 = local_8 + (int)local_10;
                } while (ppcVar10 != ppcVar9);
            }
            *param_2 = pvVar5;
            FUN_10005f59(NULL);
            FUN_10006675((int *)&local_24);
            iVar8 = 0x0;
        }
    }
    return iVar8;
}



int __cdecl FUN_10006847(LPCWSTR param_1,int param_2,undefined4 param_3,uint param_4)

{
    int iVar1;
    uint uVar2;
    DWORD DVar3;
    int *piVar4;
    
    if (param_1 == NULL) {
        FUN_10006930(param_2);
        iVar1 = 0x0;
    }
    else if (*param_1 == L'\0') {
        if ((*(int *)(param_2 + 0xc) != 0x0) || (iVar1 = allocate(param_2), iVar1 == 0x0)) {
            **(undefined **)(param_2 + 0x8) = 0x0;
            iVar1 = 0x0;
            *(undefined4 *)(param_2 + 0x10) = 0x0;
        }
    }
    else {
        uVar2 = ___acrt_WideCharToMultiByte(param_4,0x0,param_1,-0x1,NULL,0x0,0x0,NULL);
        if (uVar2 == 0x0) {
            DVar3 = GetLastError();
            ___acrt_errno_map_os_error(DVar3);
            piVar4 = (int *)FUN_10005ee9();
            iVar1 = *piVar4;
        }
        else if ((uVar2 < *(uint *)(param_2 + 0xc) || uVar2 == *(uint *)(param_2 + 0xc)) || (iVar1 = allocate(param_2), iVar1 == 0x0)) {
            iVar1 = FID_conflict_operator__(param_4,param_1,*(LPSTR *)(param_2 + 0x8),*(int *)(param_2 + 0xc));
            if (iVar1 == 0x0) {
                DVar3 = GetLastError();
                ___acrt_errno_map_os_error(DVar3);
                piVar4 = (int *)FUN_10005ee9();
                iVar1 = *piVar4;
            }
            else {
                *(int *)(param_2 + 0x10) = iVar1 + -0x1;
                iVar1 = 0x0;
            }
        }
    }
    return iVar1;
}



// Library Function - Multiple Matches With Same Base Name
//  public: int __thiscall __crt_win32_buffer<char,struct __crt_win32_buffer_no_resizing>::allocate(unsigned int)
//  public: int __thiscall __crt_win32_buffer<wchar_t,struct __crt_win32_buffer_no_resizing>::allocate(unsigned int)
// 
// Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual Studio 2019 Release

undefined4 __fastcall allocate(int param_1)

{
    undefined4 *puVar1;
    
    if (*(char *)(param_1 + 0x14) != '\0') {
        *(undefined *)(param_1 + 0x14) = 0x0;
    }
    puVar1 = (undefined4 *)FUN_10005ee9();
    *puVar1 = 0x22;
    *(undefined4 *)(param_1 + 0xc) = 0x0;
    *(undefined *)(param_1 + 0x14) = 0x0;
    return 0x22;
}



void __fastcall FUN_10006930(int param_1)

{
    if (*(char *)(param_1 + 0x14) != '\0') {
        *(undefined *)(param_1 + 0x14) = 0x0;
    }
    *(undefined4 *)(param_1 + 0x8) = 0x0;
    *(undefined4 *)(param_1 + 0xc) = 0x0;
    *(undefined4 *)(param_1 + 0x10) = 0x0;
    return;
}



// Library Function - Single Match
//  ___acrt_GetModuleFileNameA
// 
// Library: Visual Studio 2019 Release

void __cdecl ___acrt_GetModuleFileNameA(HMODULE param_1,undefined4 param_2,undefined4 param_3)

{
    DWORD DVar1;
    uint uVar2;
    undefined extraout_DL;
    undefined extraout_DL_00;
    undefined uVar3;
    undefined in_stack_fffffdd0;
    undefined local_215;
    WCHAR local_214 [0x106];
    uint local_8;
    
    local_8 = DAT_10015124 ^ (uint)&stack0xfffffffc;
    DVar1 = GetModuleFileNameW(param_1,local_214,0x105);
    if (DVar1 == 0x0) {
        DVar1 = GetLastError();
        ___acrt_errno_map_os_error(DVar1);
        uVar3 = extraout_DL;
    }
    else {
        in_stack_fffffdd0 = (undefined)param_2;
        uVar2 = __acrt_get_utf8_acp_compatibility_codepage();
        FUN_10006847(local_214,(int)&stack0xfffffdd0,&local_215,uVar2);
        uVar3 = extraout_DL_00;
    }
    FUN_10001f99(local_8 ^ (uint)&stack0xfffffffc,uVar3,in_stack_fffffdd0);
    return;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  public: void __thiscall __crt_seh_guarded_call<void>::operator()<class <lambda_ceb1ee4838e85a9d631eb091e2fbe199>,class <lambda_ae742caa10f662c28703da3d2ea5e57e>&,class
// <lambda_cd08b5d6af4937fe54fc07d0c9bf6b37>>(class <lambda_ceb1ee4838e85a9d631eb091e2fbe199>&&,class <lambda_ae742caa10f662c28703da3d2ea5e57e>&,class <lambda_cd08b5d6af4937fe54fc07d0c9bf6b37>&&)
// 
// Library: Visual Studio 2019 Release

void __thiscall
__crt_seh_guarded_call<void>::operator___class__lambda_ceb1ee4838e85a9d631eb091e2fbe199__class__lambda_ae742caa10f662c28703da3d2ea5e57e___class__lambda_cd08b5d6af4937fe54fc07d0c9bf6b37___
          (__crt_seh_guarded_call_void_ *this,_lambda_ceb1ee4838e85a9d631eb091e2fbe199_ *param_1,_lambda_ae742caa10f662c28703da3d2ea5e57e_ *param_2,_lambda_cd08b5d6af4937fe54fc07d0c9bf6b37_ *param_3)

{
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    ___acrt_lock(*(int *)param_1);
    <lambda_ae742caa10f662c28703da3d2ea5e57e>::operator__(param_2);
    FUN_10006a26();
    *in_FS_OFFSET = local_14;
    return;
}



void FUN_10006a26(void)

{
    int unaff_EBP;
    
    ___acrt_unlock(**(int **)(unaff_EBP + 0x10));
    return;
}



// Library Function - Single Match
//  public: void __thiscall <lambda_ae742caa10f662c28703da3d2ea5e57e>::operator()(void)const 
// 
// Library: Visual Studio 2019 Release

void __thiscall <lambda_ae742caa10f662c28703da3d2ea5e57e>::operator__(_lambda_ae742caa10f662c28703da3d2ea5e57e_ *this)

{
    int iVar1;
    
    _memcpy_s(DAT_10016140,0x101,(void *)(*(int *)(**(int **)this + 0x48) + 0x18),0x101);
    _memcpy_s(DAT_10016144,0x100,(void *)(*(int *)(**(int **)this + 0x48) + 0x119),0x100);
    LOCK();
    iVar1 = **(int **)**(undefined4 **)(this + 0x4) + -0x1;
    **(int **)**(undefined4 **)(this + 0x4) = iVar1;
    if ((iVar1 == 0x0) && (*(undefined **)(LPVOID *)**(undefined4 **)(this + 0x4) != &DAT_10015170)) {
        FUN_10005f59(*(LPVOID *)**(undefined4 **)(this + 0x4));
    }
    *(undefined4 *)**(undefined4 **)(this + 0x4) = *(undefined4 *)(**(int **)this + 0x48);
    LOCK();
    **(int **)(**(int **)this + 0x48) = **(int **)(**(int **)this + 0x48) + 0x1;
    return;
}



// Library Function - Single Match
//  wchar_t const * __cdecl CPtoLocaleName(int)
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

wchar_t * __cdecl CPtoLocaleName(int param_1)

{
    if (param_1 == 0x3a4) {
        return (wchar_t *)L"ja-JP";
    }
    if (param_1 == 0x3a8) {
        return (wchar_t *)L"zh-CN";
    }
    if (param_1 == 0x3b5) {
        return (wchar_t *)L"ko-KR";
    }
    if (param_1 != 0x3b6) {
        return NULL;
    }
    return (wchar_t *)L"zh-TW";
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// Library Function - Single Match
//  int __cdecl getSystemCP(int)
// 
// Library: Visual Studio 2019 Release

int __cdecl getSystemCP(int param_1)

{
    int local_14;
    int local_10;
    char local_8;
    
    FUN_100065f3(&local_14,NULL);
    _DAT_1001614c = 0x0;
    if (param_1 == -0x2) {
        _DAT_1001614c = 0x1;
        param_1 = GetOEMCP();
    }
    else if (param_1 == -0x3) {
        _DAT_1001614c = 0x1;
        param_1 = GetACP();
    }
    else if (param_1 == -0x4) {
        _DAT_1001614c = 0x1;
        param_1 = *(UINT *)(local_10 + 0x8);
    }
    if (local_8 != '\0') {
        *(uint *)(local_14 + 0x350) = *(uint *)(local_14 + 0x350) & 0xfffffffd;
    }
    return param_1;
}



void __cdecl FUN_10006b64(int param_1)

{
    int iVar1;
    int iVar2;
    
    iVar2 = 0x0;
    _memset((void *)(param_1 + 0x18),0x0,0x101);
    *(undefined4 *)(param_1 + 0x4) = 0x0;
    *(undefined4 *)(param_1 + 0x8) = 0x0;
    *(undefined4 *)(param_1 + 0x21c) = 0x0;
    *(undefined4 *)(param_1 + 0xc) = 0x0;
    iVar1 = 0x0;
    *(undefined4 *)(param_1 + 0x10) = 0x0;
    *(undefined4 *)(param_1 + 0x14) = 0x0;
    do {
        *(undefined1 *)(param_1 + 0x18 + iVar1) = (&DAT_10015188)[iVar1];
        iVar1 = iVar1 + 0x1;
    } while (iVar1 < 0x101);
    do {
        *(undefined1 *)(param_1 + 0x119 + iVar2) = (&DAT_10015289)[iVar2];
        iVar2 = iVar2 + 0x1;
    } while (iVar2 < 0x100);
    return;
}



void __cdecl FUN_10006bc7(int param_1)

{
    char cVar1;
    byte bVar2;
    BOOL BVar3;
    uint uVar4;
    BYTE *pBVar5;
    byte *pbVar6;
    int iVar7;
    int in_stack_fffff8dc;
    _cpinfo local_71c;
    WORD local_708 [0x200];
    WCHAR local_308 [0x80];
    WCHAR local_208 [0x80];
    CHAR local_108 [0x100];
    uint local_8;
    
    local_8 = DAT_10015124 ^ (uint)&stack0xfffffffc;
    if ((*(int *)(param_1 + 0x4) == 0xfde9) || (BVar3 = GetCPInfo(*(UINT *)(param_1 + 0x4),&local_71c), BVar3 == 0x0)) {
        pbVar6 = (byte *)(param_1 + 0x19);
        in_stack_fffff8dc = -0x5a - param_1;
        iVar7 = -0x19 - param_1;
        do {
            if (pbVar6 + in_stack_fffff8dc < (byte *)0x1a) {
                *pbVar6 = *pbVar6 | 0x10;
                cVar1 = (char)pbVar6 + ' ';
LAB_10006d4a:
                bVar2 = cVar1 + (char)iVar7;
            }
            else {
                if (pbVar6 + (-0x7a - param_1) < (byte *)0x1a) {
                    *pbVar6 = *pbVar6 | 0x20;
                    cVar1 = (char)pbVar6 + -0x20;
                    goto LAB_10006d4a;
                }
                bVar2 = 0x0;
            }
            pbVar6[0x100] = bVar2;
            pbVar6 = pbVar6 + 0x1;
        } while (pbVar6 + iVar7 < (byte *)0x100);
    }
    else {
        uVar4 = 0x0;
        do {
            local_108[uVar4] = (CHAR)uVar4;
            uVar4 = uVar4 + 0x1;
        } while (uVar4 < 0x100);
        pBVar5 = local_71c.LeadByte;
        local_108[0] = ' ';
        while (local_71c.LeadByte[0] != 0x0) {
            bVar2 = pBVar5[0x1];
            for (uVar4 = (uint)local_71c.LeadByte[0]; (uVar4 <= bVar2 && (uVar4 < 0x100)); uVar4 = uVar4 + 0x1) {
                local_108[uVar4] = ' ';
            }
            pBVar5 = pBVar5 + 0x2;
            local_71c.LeadByte[0] = *pBVar5;
        }
        FUN_10009134(NULL,0x1,local_108,0x100,local_708,*(uint *)(param_1 + 0x4),0x0);
        ___acrt_LCMapStringA(NULL,*(ushort **)(param_1 + 0x21c),0x100,local_108,0x100,local_208,0x100,*(uint *)(param_1 + 0x4),0x0);
        ___acrt_LCMapStringA(NULL,*(ushort **)(param_1 + 0x21c),0x200,local_108,0x100,local_308,0x100,*(uint *)(param_1 + 0x4),0x0);
        pbVar6 = (byte *)(param_1 + 0x19);
        iVar7 = 0x0;
        do {
            if ((local_708[iVar7] & 0x1) == 0x0) {
                if ((local_708[iVar7] & 0x2) == 0x0) {
                    bVar2 = 0x0;
                }
                else {
                    *pbVar6 = *pbVar6 | 0x20;
                    bVar2 = *(byte *)((int)local_308 + iVar7);
                }
            }
            else {
                *pbVar6 = *pbVar6 | 0x10;
                bVar2 = *(byte *)((int)local_208 + iVar7);
            }
            pbVar6[0x100] = bVar2;
            iVar7 = iVar7 + 0x1;
            pbVar6 = pbVar6 + 0x1;
        } while (pbVar6 + (-0x19 - param_1) < (byte *)0x100);
    }
    FUN_10001f99(local_8 ^ (uint)&stack0xfffffffc,(char)iVar7,(char)in_stack_fffff8dc);
    return;
}



int __cdecl FUN_10006d73(int param_1,char param_2,__acrt_ptd *param_3,__crt_multibyte_data **param_4)

{
    int *piVar1;
    int iVar2;
    undefined4 *puVar3;
    int iVar4;
    undefined4 *puVar5;
    undefined4 *puVar6;
    undefined4 local_248 [0x89];
    __acrt_ptd **local_24;
    __crt_multibyte_data ***local_20;
    int local_1c;
    __crt_seh_guarded_call_void_ local_15;
    undefined4 *local_14;
    
    update_thread_multibyte_data_internal(param_3,param_4);
    local_1c = getSystemCP(param_1);
    if (local_1c == *(int *)(*(int *)(param_3 + 0x48) + 0x4)) {
        iVar2 = 0x0;
    }
    else {
        puVar3 = (undefined4 *)__malloc_base(0x220);
        iVar2 = local_1c;
        local_14 = puVar3;
        if (puVar3 == NULL) {
            FUN_10005f59(NULL);
            iVar2 = -0x1;
        }
        else {
            puVar5 = *(undefined4 **)(param_3 + 0x48);
            puVar6 = local_248;
            for (iVar4 = 0x88; iVar4 != 0x0; iVar4 = iVar4 + -0x1) {
                *puVar6 = *puVar5;
                puVar5 = puVar5 + 0x1;
                puVar6 = puVar6 + 0x1;
            }
            puVar5 = local_248;
            puVar6 = puVar3;
            for (iVar4 = 0x88; iVar4 != 0x0; iVar4 = iVar4 + -0x1) {
                *puVar6 = *puVar5;
                puVar5 = puVar5 + 0x1;
                puVar6 = puVar6 + 0x1;
            }
            *puVar3 = 0x0;
            iVar2 = FUN_10006fc3(iVar2,(int)puVar3);
            if (iVar2 == -0x1) {
                puVar3 = (undefined4 *)FUN_10005ee9();
                *puVar3 = 0x16;
                FUN_10005f59(local_14);
                iVar2 = -0x1;
            }
            else {
                if (param_2 == '\0') {
                    FUN_100086c0();
                }
                piVar1 = *(int **)(param_3 + 0x48);
                LOCK();
                iVar4 = *piVar1;
                *piVar1 = *piVar1 + -0x1;
                if ((iVar4 == 0x1) && (*(undefined **)(param_3 + 0x48) != &DAT_10015170)) {
                    FUN_10005f59(*(LPVOID *)(param_3 + 0x48));
                }
                *local_14 = 0x1;
                *(undefined4 **)(param_3 + 0x48) = local_14;
                if ((*(uint *)(param_3 + 0x350) & DAT_10015800) == 0x0) {
                    local_24 = &param_3;
                    local_20 = &param_4;
                    local_1c = 0x5;
                    local_14 = (undefined4 *)0x5;
                    __crt_seh_guarded_call<void>::
                    operator___class__lambda_ceb1ee4838e85a9d631eb091e2fbe199__class__lambda_ae742caa10f662c28703da3d2ea5e57e___class__lambda_cd08b5d6af4937fe54fc07d0c9bf6b37___
                              (&local_15,(_lambda_ceb1ee4838e85a9d631eb091e2fbe199_ *)&local_14,(_lambda_ae742caa10f662c28703da3d2ea5e57e_ *)&local_24,
                               (_lambda_cd08b5d6af4937fe54fc07d0c9bf6b37_ *)&local_1c);
                    if (param_2 != '\0') {
                        PTR_DAT_1001574c = *param_4;
                    }
                }
                FUN_10005f59(NULL);
            }
        }
    }
    return iVar2;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  struct __crt_multibyte_data * __cdecl update_thread_multibyte_data_internal(struct __acrt_ptd * const,struct __crt_multibyte_data * * const)
// 
// Library: Visual Studio 2019 Release

__crt_multibyte_data * __cdecl update_thread_multibyte_data_internal(__acrt_ptd *param_1,__crt_multibyte_data **param_2)

{
    int iVar1;
    code *pcVar2;
    __crt_multibyte_data *p_Var3;
    int *piVar4;
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    if (((*(uint *)(param_1 + 0x350) & DAT_10015800) == 0x0) || (*(int *)(param_1 + 0x4c) == 0x0)) {
        ___acrt_lock(0x5);
        piVar4 = *(int **)(param_1 + 0x48);
        if (piVar4 != (int *)*param_2) {
            if (piVar4 != NULL) {
                LOCK();
                iVar1 = *piVar4;
                *piVar4 = iVar1 + -0x1;
                if ((iVar1 + -0x1 == 0x0) && (piVar4 != (int *)&DAT_10015170)) {
                    FUN_10005f59(piVar4);
                }
            }
            piVar4 = (int *)*param_2;
            *(int **)(param_1 + 0x48) = piVar4;
            LOCK();
            *piVar4 = *piVar4 + 0x1;
        }
        FUN_10006f47();
    }
    else {
        piVar4 = *(int **)(param_1 + 0x48);
    }
    if (piVar4 != NULL) {
        *in_FS_OFFSET = local_14;
        return (__crt_multibyte_data *)piVar4;
    }
    _abort();
    pcVar2 = (code *)swi(0x3);
    p_Var3 = (__crt_multibyte_data *)(*pcVar2)();
    return p_Var3;
}



void FUN_10006f47(void)

{
    ___acrt_unlock(0x5);
    return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// Library Function - Single Match
//  ___acrt_initialize_multibyte
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

undefined4 ___acrt_initialize_multibyte(void)

{
    int in_EAX;
    __acrt_ptd *p_Var1;
    
    if (DAT_10016150 == '\0') {
        _DAT_10016148 = &DAT_10015170;
        DAT_10016144 = &DAT_10015498;
        DAT_10016140 = &DAT_10015390;
        p_Var1 = FUN_100058e2();
        in_EAX = FUN_10006d73(-0x3,'\x01',p_Var1,(__crt_multibyte_data **)&DAT_10016148);
        DAT_10016150 = '\x01';
    }
    return CONCAT31((int3)((uint)in_EAX >> 0x8),0x1);
}



void FUN_10006fb0(void)

{
    __acrt_ptd *p_Var1;
    
    p_Var1 = FUN_10005827();
    update_thread_multibyte_data_internal(p_Var1,(__crt_multibyte_data **)&DAT_10016148);
    return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void __cdecl FUN_10006fc3(int param_1,int param_2)

{
    byte bVar1;
    undefined2 uVar2;
    uint uVar3;
    uint uVar4;
    BOOL BVar5;
    BYTE *pBVar6;
    wchar_t *pwVar7;
    int iVar8;
    byte *pbVar9;
    undefined2 *puVar10;
    undefined extraout_DL;
    undefined extraout_DL_00;
    undefined extraout_DL_01;
    undefined extraout_DL_02;
    undefined extraout_DL_03;
    undefined uVar11;
    byte *pbVar12;
    undefined2 *puVar13;
    byte *pbVar14;
    uint uVar15;
    undefined uVar16;
    int in_stack_ffffffd8;
    int local_20;
    _cpinfo local_1c;
    uint local_8;
    
    local_8 = DAT_10015124 ^ (uint)&stack0xfffffffc;
    uVar3 = getSystemCP(param_1);
    uVar16 = (undefined)in_stack_ffffffd8;
    if (uVar3 != 0x0) {
        uVar15 = 0x0;
        uVar4 = 0x0;
        local_20 = 0x0;
LAB_10006ffa:
        if (*(uint *)((int)&DAT_100155a0 + uVar4) != uVar3) goto code_r0x10007006;
        _memset((void *)(param_2 + 0x18),0x0,0x101);
        in_stack_ffffffd8 = local_20 * 0x30;
        pbVar12 = &DAT_100155b0 + in_stack_ffffffd8;
        do {
            bVar1 = *pbVar12;
            pbVar9 = pbVar12;
            while ((bVar1 != 0x0 && (pbVar9[0x1] != 0x0))) {
                uVar4 = (uint)*pbVar9;
                if (uVar4 <= pbVar9[0x1]) {
                    pbVar14 = (byte *)(param_2 + 0x19 + uVar4);
                    do {
                        if (0xff < uVar4) break;
                        *pbVar14 = *pbVar14 | (&DAT_10015598)[uVar15];
                        uVar4 = uVar4 + 0x1;
                        pbVar14 = pbVar14 + 0x1;
                    } while (uVar4 <= pbVar9[0x1]);
                }
                pbVar9 = pbVar9 + 0x2;
                bVar1 = *pbVar9;
            }
            uVar15 = uVar15 + 0x1;
            pbVar12 = pbVar12 + 0x8;
        } while (uVar15 < 0x4);
        *(uint *)(param_2 + 0x4) = uVar3;
        *(undefined4 *)(param_2 + 0x8) = 0x1;
        pwVar7 = CPtoLocaleName(uVar3);
        *(wchar_t **)(param_2 + 0x21c) = pwVar7;
        puVar10 = (undefined2 *)(param_2 + 0xc);
        puVar13 = (undefined2 *)(&DAT_100155a4 + in_stack_ffffffd8);
        iVar8 = 0x6;
        do {
            uVar2 = *puVar13;
            puVar13 = puVar13 + 0x1;
            *puVar10 = uVar2;
            puVar10 = puVar10 + 0x1;
            iVar8 = iVar8 + -0x1;
        } while (iVar8 != 0x0);
        goto LAB_10007056;
    }
LAB_100071b3:
    FUN_10006b64(param_2);
    uVar11 = extraout_DL_03;
LAB_100071bc:
    FUN_10001f99(local_8 ^ (uint)&stack0xfffffffc,uVar11,uVar16);
    return;
code_r0x10007006:
    local_20 = local_20 + 0x1;
    uVar4 = uVar4 + 0x30;
    if (0xef < uVar4) goto code_r0x10007014;
    goto LAB_10006ffa;
code_r0x10007014:
    uVar11 = extraout_DL;
    if (uVar3 == 0xfde8) goto LAB_100071bc;
    BVar5 = IsValidCodePage(uVar3 & 0xffff);
    uVar16 = (undefined)in_stack_ffffffd8;
    uVar11 = extraout_DL_00;
    if (BVar5 == 0x0) goto LAB_100071bc;
    if (uVar3 == 0xfde9) {
        *(undefined4 *)(param_2 + 0x4) = 0xfde9;
        *(undefined4 *)(param_2 + 0x21c) = 0x0;
        *(undefined4 *)(param_2 + 0x18) = 0x0;
        *(undefined2 *)(param_2 + 0x1c) = 0x0;
    }
    else {
        BVar5 = GetCPInfo(uVar3,&local_1c);
        uVar16 = (undefined)in_stack_ffffffd8;
        if (BVar5 == 0x0) {
            uVar11 = extraout_DL_02;
            if (_DAT_1001614c == 0x0) goto LAB_100071bc;
            goto LAB_100071b3;
        }
        _memset((void *)(param_2 + 0x18),0x0,0x101);
        *(uint *)(param_2 + 0x4) = uVar3;
        *(undefined4 *)(param_2 + 0x21c) = 0x0;
        if (local_1c.MaxCharSize == 0x2) {
            pBVar6 = local_1c.LeadByte;
            while ((local_1c.LeadByte[0] != 0x0 && (bVar1 = pBVar6[0x1], bVar1 != 0x0))) {
                uVar3 = (uint)*pBVar6;
                if (uVar3 <= bVar1) {
                    pbVar12 = (byte *)(param_2 + 0x19 + uVar3);
                    iVar8 = (bVar1 - uVar3) + 0x1;
                    do {
                        *pbVar12 = *pbVar12 | 0x4;
                        pbVar12 = pbVar12 + 0x1;
                        iVar8 = iVar8 + -0x1;
                    } while (iVar8 != 0x0);
                }
                pBVar6 = pBVar6 + 0x2;
                local_1c.LeadByte[0] = *pBVar6;
            }
            pbVar12 = (byte *)(param_2 + 0x1a);
            iVar8 = 0xfe;
            do {
                *pbVar12 = *pbVar12 | 0x8;
                pbVar12 = pbVar12 + 0x1;
                iVar8 = iVar8 + -0x1;
            } while (iVar8 != 0x0);
            pwVar7 = CPtoLocaleName(*(int *)(param_2 + 0x4));
            *(wchar_t **)(param_2 + 0x21c) = pwVar7;
            uVar15 = 0x1;
        }
    }
    *(uint *)(param_2 + 0x8) = uVar15;
    *(undefined4 *)(param_2 + 0xc) = 0x0;
    *(undefined4 *)(param_2 + 0x10) = 0x0;
    *(undefined4 *)(param_2 + 0x14) = 0x0;
LAB_10007056:
    uVar16 = (undefined)in_stack_ffffffd8;
    FUN_10006bc7(param_2);
    uVar11 = extraout_DL_01;
    goto LAB_100071bc;
}



// Library Function - Single Match
//  _memcpy_s
// 
// Libraries: Visual Studio 2012, Visual Studio 2015, Visual Studio 2017, Visual Studio 2019

errno_t __cdecl _memcpy_s(void *_Dst,rsize_t _DstSize,void *_Src,rsize_t _MaxCount)

{
    errno_t eVar1;
    undefined4 *puVar2;
    errno_t *peVar3;
    
    if (_MaxCount == 0x0) {
        eVar1 = 0x0;
    }
    else if (_Dst == NULL) {
        puVar2 = (undefined4 *)FUN_10005ee9();
        eVar1 = 0x16;
        *puVar2 = 0x16;
        FUN_10005e08();
    }
    else if ((_Src == NULL) || (_DstSize < _MaxCount)) {
        _memset(_Dst,0x0,_DstSize);
        if (_Src == NULL) {
            peVar3 = (errno_t *)FUN_10005ee9();
            eVar1 = 0x16;
        }
        else {
            if (_MaxCount <= _DstSize) {
                return 0x16;
            }
            peVar3 = (errno_t *)FUN_10005ee9();
            eVar1 = 0x22;
        }
        *peVar3 = eVar1;
        FUN_10005e08();
    }
    else {
        FID_conflict__memcpy(_Dst,_Src,_MaxCount);
        eVar1 = 0x0;
    }
    return eVar1;
}



undefined4 __cdecl FUN_1000724c(__acrt_ptd **param_1,byte param_2,uint param_3,byte param_4)

{
    undefined4 uVar1;
    int local_14;
    int *local_10;
    int local_c;
    char local_8;
    
    FUN_100065f3(&local_14,param_1);
    if (((*(byte *)(local_c + 0x19 + (uint)param_2) & param_4) == 0x0) && ((param_3 == 0x0 || ((param_3 & *(ushort *)(*local_10 + (uint)param_2 * 0x2)) == 0x0)))) {
        uVar1 = 0x0;
    }
    else {
        uVar1 = 0x1;
    }
    if (local_8 != '\0') {
        *(uint *)(local_14 + 0x350) = *(uint *)(local_14 + 0x350) & 0xfffffffd;
    }
    return uVar1;
}



// Library Function - Single Match
//  __ismbblead
// 
// Library: Visual Studio 2019 Release

int __cdecl __ismbblead(uint _C)

{
    int iVar1;
    
    iVar1 = FUN_1000724c(NULL,(byte)_C,0x0,0x4);
    return iVar1;
}



// Library Function - Single Match
//  ___acrt_MultiByteToWideChar
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl ___acrt_MultiByteToWideChar(uint param_1,DWORD param_2,LPCSTR param_3,int param_4,LPWSTR param_5,int param_6)

{
    if (param_1 < 0xc436) {
        if (((param_1 != 0xc435) && (param_1 != 0x2a)) && ((param_1 < 0xc42c || (((0xc42e < param_1 && (param_1 != 0xc431)) && (param_1 != 0xc433)))))) goto LAB_1000732f;
LAB_10007345:
        param_2 = 0x0;
    }
    else {
        if (param_1 != 0xd698) {
            if (param_1 < 0xdeaa) goto LAB_1000732f;
            if ((param_1 < 0xdeb4) || (param_1 == 0xfde8)) goto LAB_10007345;
            if (param_1 != 0xfde9) goto LAB_1000732f;
        }
        param_2 = param_2 & 0x8;
    }
LAB_1000732f:
    MultiByteToWideChar(param_1,param_2,param_3,param_4,param_5,param_6);
    return;
}



// Library Function - Single Match
//  ___acrt_WideCharToMultiByte
// 
// Library: Visual Studio 2019 Release

void __cdecl ___acrt_WideCharToMultiByte(uint param_1,uint param_2,LPCWSTR param_3,int param_4,LPSTR param_5,int param_6,uint param_7,undefined4 *param_8)

{
    bool bVar1;
    DWORD dwFlags;
    bool bVar2;
    
    if ((param_1 == 0xfde8) || (param_1 == 0xfde9)) {
        bVar1 = true;
    }
    else {
        bVar1 = false;
    }
    if (param_1 < 0xc436) {
        if ((param_1 != 0xc435) && (param_1 != 0x2a)) {
            if (param_1 < 0xc42c) {
LAB_100073b3:
                dwFlags = param_2 & 0xffffff7f;
                goto LAB_100073c0;
            }
            if ((0xc42e < param_1) && (param_1 != 0xc431)) {
                bVar2 = param_1 == 0xc433;
LAB_100073b1:
                if (!bVar2) goto LAB_100073b3;
            }
        }
    }
    else if (param_1 != 0xd698) {
        if (param_1 < 0xdeaa) goto LAB_100073b3;
        if ((0xdeb3 < param_1) && (param_1 != 0xfde8)) {
            bVar2 = param_1 == 0xfde9;
            goto LAB_100073b1;
        }
    }
    dwFlags = 0x0;
LAB_100073c0:
    if ((bVar1) && (param_8 != NULL)) {
        *param_8 = 0x0;
    }
    WideCharToMultiByte(param_1,dwFlags,param_3,param_4,param_5,param_6,(LPCSTR)(~-(uint)bVar1 & param_7),(LPBOOL)(~-(uint)bVar1 & (uint)param_8));
    return;
}



// Library Function - Single Match
//  wchar_t const * __cdecl find_end_of_double_null_terminated_sequence(wchar_t const * const)
// 
// Libraries: Visual Studio 2015, Visual Studio 2017, Visual Studio 2019

wchar_t * __cdecl find_end_of_double_null_terminated_sequence(wchar_t *param_1)

{
    short sVar1;
    short *psVar2;
    
    sVar1 = *(short *)param_1;
    while (sVar1 != 0x0) {
        psVar2 = (short *)param_1;
        do {
            sVar1 = *psVar2;
            psVar2 = psVar2 + 0x1;
        } while (sVar1 != 0x0);
        param_1 = (wchar_t *)((int)param_1 + (((int)psVar2 - (int)((int)param_1 + 0x2) >> 0x1) + 0x1) * 0x2);
        sVar1 = *(short *)param_1;
    }
    return (wchar_t *)(short *)((int)param_1 + 0x2);
}



LPWCH FUN_10007437(void)

{
    LPWCH pWVar1;
    wchar_t *pwVar2;
    int iVar3;
    size_t sVar4;
    LPWCH pWVar5;
    
    pWVar1 = GetEnvironmentStringsW();
    pWVar5 = pWVar1;
    if (pWVar1 != NULL) {
        pwVar2 = find_end_of_double_null_terminated_sequence((wchar_t *)pWVar1);
        iVar3 = (int)pwVar2 - (int)pWVar1 >> 0x1;
        sVar4 = ___acrt_WideCharToMultiByte(0x0,0x0,pWVar1,iVar3,NULL,0x0,0x0,NULL);
        if (sVar4 == 0x0) {
            FreeEnvironmentStringsW(pWVar1);
            pWVar5 = NULL;
        }
        else {
            pWVar5 = (LPWCH)__malloc_base(sVar4);
            if (pWVar5 == NULL) {
                FUN_10005f59(NULL);
                FreeEnvironmentStringsW(pWVar1);
                pWVar5 = NULL;
            }
            else {
                iVar3 = ___acrt_WideCharToMultiByte(0x0,0x0,pWVar1,iVar3,(LPSTR)pWVar5,sVar4,0x0,NULL);
                if (iVar3 == 0x0) {
                    FUN_10005f59(pWVar5);
                    pWVar5 = NULL;
                }
                else {
                    FUN_10005f59(NULL);
                }
                FreeEnvironmentStringsW(pWVar1);
            }
        }
    }
    return pWVar5;
}



// Library Function - Single Match
//  __recalloc_base
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

LPVOID __cdecl __recalloc_base(void *param_1,uint param_2,uint param_3)

{
    undefined4 *puVar1;
    LPVOID pvVar2;
    size_t sVar3;
    uint uVar4;
    
    if ((param_2 == 0x0) || (param_3 <= 0xffffffe0 / param_2)) {
        if (param_1 == NULL) {
            sVar3 = 0x0;
        }
        else {
            sVar3 = FID_conflict___msize_base(param_1);
        }
        uVar4 = param_2 * param_3;
        pvVar2 = __realloc_base(param_1,uVar4);
        if ((pvVar2 != NULL) && (sVar3 < uVar4)) {
            _memset((void *)((int)pvVar2 + sVar3),0x0,uVar4 - sVar3);
        }
    }
    else {
        puVar1 = (undefined4 *)FUN_10005ee9();
        *puVar1 = 0xc;
        pvVar2 = NULL;
    }
    return pvVar2;
}



// Library Function - Single Match
//  int (__stdcall*__cdecl try_get_AreFileApisANSI(void))(void)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

FuncDef11 * __cdecl try_get_AreFileApisANSI(void)

{
    FuncDef11 *pFVar1;
    
    pFVar1 = (FuncDef11 *)try_get_function(0x0,"AreFileApisANSI",(module_id *)&DAT_1000f40c,(module_id *)"AreFileApisANSI");
    return pFVar1;
}



// Library Function - Multiple Matches With Different Base Names
//  int (__stdcall*__cdecl try_get_CompareStringEx(void))(wchar_t const *,unsigned long,wchar_t const *,int,wchar_t const *,int,struct _nlsversioninfo *,void *,long)
//  int (__stdcall*__cdecl try_get_LCMapStringEx(void))(wchar_t const *,unsigned long,wchar_t const *,int,wchar_t *,int,struct _nlsversioninfo *,void *,long)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void FID_conflict_try_get_LCMapStringEx(void)

{
    try_get_function(0x10,"LCMapStringEx",(module_id *)&DAT_1000f428,(module_id *)"LCMapStringEx");
    return;
}



// Library Function - Single Match
//  unsigned long (__stdcall*__cdecl try_get_LocaleNameToLCID(void))(wchar_t const *,unsigned long)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

FuncDef12 * __cdecl try_get_LocaleNameToLCID(void)

{
    FuncDef12 *pFVar1;
    
    pFVar1 = (FuncDef12 *)try_get_function(0x12,"LocaleNameToLCID",(module_id *)&DAT_1000f440,(module_id *)"LocaleNameToLCID");
    return pFVar1;
}



HMODULE __cdecl FUN_10007592(int *param_1,int *param_2)

{
    int iVar1;
    LPCWSTR lpLibFileName;
    HMODULE pHVar2;
    HMODULE pHVar3;
    DWORD DVar4;
    int iVar5;
    
    do {
        if (param_1 == param_2) {
            return NULL;
        }
        iVar1 = *param_1;
        pHVar3 = (HMODULE)(&DAT_10016170)[iVar1];
        if (pHVar3 == NULL) {
            lpLibFileName = (LPCWSTR)(&PTR_u_api_ms_win_core_datetime_l1_1_1_1000ef58)[iVar1];
            pHVar3 = LoadLibraryExW(lpLibFileName,NULL,0x800);
            if ((pHVar3 != NULL) ||
               ((((DVar4 = GetLastError(), DVar4 == 0x57 && (iVar5 = _wcsncmp(lpLibFileName,L"api-ms-",0x7), iVar5 != 0x0)) && (iVar5 = _wcsncmp(lpLibFileName,L"ext-ms-",0x7), iVar5 != 0x0)) &&
                (pHVar3 = LoadLibraryExW(lpLibFileName,NULL,0x0), pHVar3 != NULL)))) {
                pHVar2 = (HMODULE)(&DAT_10016170)[iVar1];
                (&DAT_10016170)[iVar1] = pHVar3;
                if (pHVar2 == NULL) {
                    return pHVar3;
                }
                FreeLibrary(pHVar3);
                return pHVar3;
            }
            (&DAT_10016170)[iVar1] = 0xffffffff;
        }
        else if (pHVar3 != (HMODULE)0xffffffff) {
            return pHVar3;
        }
        param_1 = param_1 + 0x1;
    } while( true );
}



// Library Function - Single Match
//  void * __cdecl try_get_function(enum `anonymous namespace'::function_id,char const * const,enum A0x391cf84c::module_id const * const,enum A0x391cf84c::module_id const * const)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void * __cdecl try_get_function(function_id param_1,char *param_2,module_id *param_3,module_id *param_4)

{
    void **ppvVar1;
    HMODULE hModule;
    void *pvVar2;
    byte bVar3;
    FARPROC pFVar4;
    
    ppvVar1 = (void **)(&DAT_100161c0 + param_1);
    bVar3 = (byte)DAT_10015124 & 0x1f;
    pFVar4 = (FARPROC)((DAT_10015124 ^ (uint)*ppvVar1) >> bVar3 | (DAT_10015124 ^ (uint)*ppvVar1) << 0x20 - bVar3);
    if (pFVar4 == (FARPROC)0xffffffff) {
        pFVar4 = NULL;
    }
    else if (pFVar4 == NULL) {
        hModule = FUN_10007592((int *)param_3,(int *)param_4);
        if ((hModule == NULL) || (pFVar4 = GetProcAddress(hModule,param_2), pFVar4 == NULL)) {
            bVar3 = 0x20 - ((byte)DAT_10015124 & 0x1f) & 0x1f;
            *ppvVar1 = (void *)((0xffffffffU >> bVar3 | -0x1 << 0x20 - bVar3) ^ DAT_10015124);
            pFVar4 = NULL;
        }
        else {
            pvVar2 = __crt_fast_encode_pointer_void__(pFVar4);
            *ppvVar1 = pvVar2;
        }
    }
    return pFVar4;
}



// Library Function - Single Match
//  ___acrt_AppPolicyGetProcessTerminationMethodInternal@4
// 
// Library: Visual Studio 2019 Release

undefined4 ___acrt_AppPolicyGetProcessTerminationMethodInternal_4(undefined4 param_1)

{
    code *pcVar1;
    undefined4 uVar2;
    
    pcVar1 = (code *)try_get_function(0x18,"AppPolicyGetProcessTerminationMethod",(module_id *)&DAT_1000f45c,(module_id *)"AppPolicyGetProcessTerminationMethod");
    if (pcVar1 == NULL) {
        uVar2 = 0xc0000225;
    }
    else {
        uVar2 = 0xfffffffa;
        _guard_check_icall();
        uVar2 = (*pcVar1)(uVar2,param_1);
    }
    return uVar2;
}



// Library Function - Single Match
//  ___acrt_AreFileApisANSI@0
// 
// Library: Visual Studio 2019 Release

int ___acrt_AreFileApisANSI_0(void)

{
    FuncDef11 *pFVar1;
    int iVar2;
    
    pFVar1 = try_get_AreFileApisANSI();
    if (pFVar1 != NULL) {
        _guard_check_icall();
        iVar2 = (*pFVar1)();
        return iVar2;
    }
    return 0x1;
}



// Library Function - Single Match
//  ___acrt_FlsAlloc@4
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void ___acrt_FlsAlloc_4(undefined4 param_1)

{
    code *pcVar1;
    
    pcVar1 = (code *)try_get_function(0x1e,"FlsAlloc",(module_id *)&DAT_1000f488,(module_id *)&DAT_1000f490);
    if (pcVar1 == NULL) {
        TlsAlloc();
    }
    else {
        _guard_check_icall();
        (*pcVar1)(param_1);
    }
    return;
}



// Library Function - Single Match
//  ___acrt_FlsFree@4
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void ___acrt_FlsFree_4(DWORD param_1)

{
    code *pcVar1;
    
    pcVar1 = (code *)try_get_function(0x1f,"FlsFree",(module_id *)&DAT_1000f490,(module_id *)&DAT_1000f498);
    if (pcVar1 != NULL) {
        _guard_check_icall();
        (*pcVar1)(param_1);
        return;
    }
                    // WARNING: Could not recover jumptable at 0x100077b7. Too many branches
                    // WARNING: Treating indirect jump as call
    TlsFree(param_1);
    return;
}



// Library Function - Single Match
//  ___acrt_FlsGetValue@4
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void ___acrt_FlsGetValue_4(DWORD param_1)

{
    code *pcVar1;
    
    pcVar1 = (code *)try_get_function(0x20,"FlsGetValue",(module_id *)&DAT_1000f498,(module_id *)&DAT_1000f4a0);
    if (pcVar1 != NULL) {
        _guard_check_icall();
        (*pcVar1)(param_1);
        return;
    }
                    // WARNING: Could not recover jumptable at 0x100077f6. Too many branches
                    // WARNING: Treating indirect jump as call
    TlsGetValue(param_1);
    return;
}



// Library Function - Single Match
//  ___acrt_FlsSetValue@8
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void ___acrt_FlsSetValue_8(DWORD param_1,LPVOID param_2)

{
    code *pcVar1;
    
    pcVar1 = (code *)try_get_function(0x21,"FlsSetValue",(module_id *)&DAT_1000f4a0,(module_id *)&PTR_DAT_1000f4a8);
    if (pcVar1 != NULL) {
        _guard_check_icall();
        (*pcVar1)(param_1,param_2);
        return;
    }
                    // WARNING: Could not recover jumptable at 0x10007838. Too many branches
                    // WARNING: Treating indirect jump as call
    TlsSetValue(param_1,param_2);
    return;
}



// Library Function - Single Match
//  ___acrt_InitializeCriticalSectionEx@12
// 
// Library: Visual Studio 2019 Release

void ___acrt_InitializeCriticalSectionEx_12(LPCRITICAL_SECTION param_1,DWORD param_2,undefined4 param_3)

{
    code *pcVar1;
    
    pcVar1 = (code *)try_get_function(0xe,"InitializeCriticalSectionEx",(module_id *)&DAT_1000f420,(module_id *)&DAT_1000f428);
    if (pcVar1 == NULL) {
        InitializeCriticalSectionAndSpinCount(param_1,param_2);
    }
    else {
        _guard_check_icall();
        (*pcVar1)(param_1,param_2,param_3);
    }
    return;
}



// Library Function - Multiple Matches With Different Base Names
//  ___acrt_CompareStringEx@36
//  ___acrt_LCMapStringEx@36
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void FID_conflict____acrt_CompareStringEx_36(ushort *param_1,DWORD param_2,LPCWSTR param_3,int param_4,LPWSTR param_5,int param_6,undefined4 param_7,undefined4 param_8,undefined4 param_9)

{
    code *pcVar1;
    LCID Locale;
    
    pcVar1 = (code *)FID_conflict_try_get_LCMapStringEx();
    if (pcVar1 == NULL) {
        Locale = ___acrt_LocaleNameToLCID_8(param_1,0x0);
        LCMapStringW(Locale,param_2,param_3,param_4,param_5,param_6);
    }
    else {
        _guard_check_icall();
        (*pcVar1)(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    }
    return;
}



// Library Function - Single Match
//  ___acrt_LocaleNameToLCID@8
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void ___acrt_LocaleNameToLCID_8(ushort *param_1,ulong param_2)

{
    FuncDef12 *pFVar1;
    
    pFVar1 = try_get_LocaleNameToLCID();
    if (pFVar1 == NULL) {
        ___acrt_DownlevelLocaleNameToLCID(param_1);
    }
    else {
        _guard_check_icall();
        (*pFVar1)((wchar_t *)param_1,param_2);
    }
    return;
}



// Library Function - Single Match
//  ___acrt_uninitialize_winapi_thunks
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

undefined __cdecl ___acrt_uninitialize_winapi_thunks(char param_1)

{
    HMODULE *ppHVar1;
    
    if (param_1 == '\0') {
        ppHVar1 = (HMODULE *)&DAT_10016170;
        do {
            if (*ppHVar1 != NULL) {
                if (*ppHVar1 != (HMODULE)0xffffffff) {
                    FreeLibrary(*ppHVar1);
                }
                *ppHVar1 = NULL;
            }
            ppHVar1 = ppHVar1 + 0x1;
        } while (ppHVar1 != (HMODULE *)&DAT_100161c0);
    }
    return 0x1;
}



// Library Function - Single Match
//  void __cdecl initialize_inherited_file_handles_nolock(void)
// 
// Library: Visual Studio 2019 Release

void __cdecl initialize_inherited_file_handles_nolock(void)

{
    byte bVar1;
    HANDLE hFile;
    DWORD DVar2;
    int iVar3;
    uint uVar4;
    uint uVar5;
    _STARTUPINFOW local_4c;
    HANDLE *local_8;
    
    GetStartupInfoW(&local_4c);
    if ((local_4c.cbReserved2 != 0x0) && ((uint *)local_4c.lpReserved2 != NULL)) {
        uVar4 = *(uint *)local_4c.lpReserved2;
        local_8 = (HANDLE *)((int)local_4c.lpReserved2 + uVar4 + 0x4);
        if (0x1fff < (int)uVar4) {
            uVar4 = 0x2000;
        }
        ___acrt_lowio_ensure_fh_exists(uVar4);
        if ((int)DAT_10016450 < (int)uVar4) {
            uVar4 = DAT_10016450;
        }
        uVar5 = 0x0;
        if (uVar4 != 0x0) {
            do {
                hFile = *local_8;
                if ((((hFile != (HANDLE)0xffffffff) && (hFile != (HANDLE)0xfffffffe)) && (bVar1 = *(byte *)(uVar5 + 0x4 + (int)local_4c.lpReserved2), (bVar1 & 0x1) != 0x0)) &&
                   (((bVar1 & 0x8) != 0x0 || (DVar2 = GetFileType(hFile), DVar2 != 0x0)))) {
                    iVar3 = (uVar5 & 0x3f) * 0x38 + (&DAT_10016250)[(int)uVar5 >> 0x6];
                    *(HANDLE *)(iVar3 + 0x18) = *local_8;
                    *(undefined *)(iVar3 + 0x28) = *(undefined *)(uVar5 + 0x4 + (int)local_4c.lpReserved2);
                }
                uVar5 = uVar5 + 0x1;
                local_8 = local_8 + 0x1;
            } while (uVar5 != uVar4);
        }
    }
    return;
}



void FUN_10007a32(void)

{
    HANDLE hFile;
    int iVar1;
    uint uVar2;
    DWORD DVar3;
    
    uVar2 = 0x0;
    do {
        iVar1 = (uVar2 & 0x3f) * 0x38 + (&DAT_10016250)[(int)uVar2 >> 0x6];
        if ((*(int *)(iVar1 + 0x18) == -0x1) || (*(int *)(iVar1 + 0x18) == -0x2)) {
            *(undefined *)(iVar1 + 0x28) = 0x81;
            if (uVar2 == 0x0) {
                DVar3 = 0xfffffff6;
            }
            else if (uVar2 == 0x1) {
                DVar3 = 0xfffffff5;
            }
            else {
                DVar3 = 0xfffffff4;
            }
            hFile = GetStdHandle(DVar3);
            if ((hFile != (HANDLE)0xffffffff) && (hFile != NULL)) {
                DVar3 = GetFileType(hFile);
                if (DVar3 != 0x0) {
                    *(HANDLE *)(iVar1 + 0x18) = hFile;
                    if ((DVar3 & 0xff) == 0x2) {
                        *(byte *)(iVar1 + 0x28) = *(byte *)(iVar1 + 0x28) | 0x40;
                    }
                    else if ((DVar3 & 0xff) == 0x3) {
                        *(byte *)(iVar1 + 0x28) = *(byte *)(iVar1 + 0x28) | 0x8;
                    }
                    goto LAB_10007ad4;
                }
            }
            *(byte *)(iVar1 + 0x28) = *(byte *)(iVar1 + 0x28) | 0x40;
            *(undefined4 *)(iVar1 + 0x18) = 0xfffffffe;
            if (DAT_10016474 != 0x0) {
                *(undefined4 *)(*(int *)(DAT_10016474 + uVar2 * 0x4) + 0x10) = 0xfffffffe;
            }
        }
        else {
            *(byte *)(iVar1 + 0x28) = *(byte *)(iVar1 + 0x28) | 0x80;
        }
LAB_10007ad4:
        uVar2 = uVar2 + 0x1;
        if (uVar2 == 0x3) {
            return;
        }
    } while( true );
}



void FUN_10007b39(void)

{
    ___acrt_unlock(0x7);
    return;
}



// Library Function - Single Match
//  ___acrt_execute_initializers
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

undefined4 __cdecl ___acrt_execute_initializers(undefined **param_1,undefined **param_2)

{
    code *pcVar1;
    code **in_EAX;
    code **ppcVar2;
    undefined4 uVar3;
    
    ppcVar2 = (code **)param_1;
    if (param_1 != param_2) {
        do {
            pcVar1 = *ppcVar2;
            if (pcVar1 != NULL) {
                _guard_check_icall();
                in_EAX = (code **)(*pcVar1)();
                if ((char)in_EAX == '\0') break;
            }
            ppcVar2 = ppcVar2 + 0x2;
        } while (ppcVar2 != (code **)param_2);
        if (ppcVar2 != (code **)param_2) {
            if (ppcVar2 != (code **)param_1) {
                ppcVar2 = ppcVar2 + -0x1;
                do {
                    if ((ppcVar2[-0x1] != NULL) && (pcVar1 = *ppcVar2, pcVar1 != NULL)) {
                        uVar3 = 0x0;
                        _guard_check_icall();
                        (*pcVar1)(uVar3);
                    }
                    in_EAX = ppcVar2 + -0x1;
                    ppcVar2 = ppcVar2 + -0x2;
                } while (in_EAX != (code **)param_1);
            }
            return (uint)in_EAX & 0xffffff00;
        }
    }
    return CONCAT31((int3)((uint)in_EAX >> 0x8),0x1);
}



// Library Function - Single Match
//  ___acrt_execute_uninitializers
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

undefined __cdecl ___acrt_execute_uninitializers(int param_1,int param_2)

{
    code *pcVar1;
    undefined4 uVar2;
    
    if (param_1 != param_2) {
        do {
            pcVar1 = *(code **)(param_2 + -0x4);
            if (pcVar1 != NULL) {
                uVar2 = 0x0;
                _guard_check_icall();
                (*pcVar1)(uVar2);
            }
            param_2 = param_2 + -0x8;
        } while (param_2 != param_1);
    }
    return 0x1;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void __cdecl FUN_10007c07(undefined4 param_1)

{
    _DAT_10016454 = param_1;
    return;
}



// Library Function - Single Match
//  __callnewh
// 
// Library: Visual Studio 2019 Release

int __cdecl __callnewh(size_t _Size)

{
    code *pcVar1;
    int iVar2;
    
    pcVar1 = (code *)__query_new_handler();
    if (pcVar1 != NULL) {
        _guard_check_icall();
        iVar2 = (*pcVar1)(_Size);
        if (iVar2 != 0x0) {
            return 0x1;
        }
    }
    return 0x0;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// Library Function - Single Match
//  __query_new_handler
// 
// Library: Visual Studio 2019 Release

uint __query_new_handler(void)

{
    byte bVar1;
    uint uVar2;
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    ___acrt_lock(0x0);
    bVar1 = (byte)DAT_10015124 & 0x1f;
    uVar2 = DAT_10015124 ^ _DAT_10016454;
    FUN_10007c96();
    *in_FS_OFFSET = local_14;
    return uVar2 >> bVar1 | uVar2 << 0x20 - bVar1;
}



void FUN_10007c96(void)

{
    ___acrt_unlock(0x0);
    return;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// Library Function - Single Match
//  public: void (__cdecl*__thiscall __crt_seh_guarded_call<void (__cdecl*)(int)>::operator()<class <lambda_cbab9ec6f41b0180b23cc171c22676b0>,class <lambda_44731a7d0e6d81c3e6aa82d741081786>&,class
// <lambda_4b292cb8dd18144e164572427af410ab>>(class <lambda_cbab9ec6f41b0180b23cc171c22676b0>&&,class <lambda_44731a7d0e6d81c3e6aa82d741081786>&,class
// <lambda_4b292cb8dd18144e164572427af410ab>&&))(int)
// 
// Library: Visual Studio 2019 Release

FuncDef13 * __thiscall
__crt_seh_guarded_call<void_(__cdecl*)(int)>::
operator___class__lambda_cbab9ec6f41b0180b23cc171c22676b0__class__lambda_44731a7d0e6d81c3e6aa82d741081786___class__lambda_4b292cb8dd18144e164572427af410ab___
          (__crt_seh_guarded_call_void____cdecl___int__ *this,_lambda_cbab9ec6f41b0180b23cc171c22676b0_ *param_1,_lambda_44731a7d0e6d81c3e6aa82d741081786_ *param_2,
          _lambda_4b292cb8dd18144e164572427af410ab_ *param_3)

{
    byte bVar1;
    uint uVar2;
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    ___acrt_lock(*(int *)param_1);
    bVar1 = (byte)DAT_10015124 & 0x1f;
    uVar2 = DAT_10015124 ^ _DAT_10016460;
    FUN_10007cf7();
    *in_FS_OFFSET = local_14;
    return (FuncDef13 *)(uVar2 >> bVar1 | uVar2 << 0x20 - bVar1);
}



void FUN_10007cf7(void)

{
    int unaff_EBP;
    
    ___acrt_unlock(**(int **)(unaff_EBP + 0x10));
    return;
}



// Library Function - Single Match
//  void (__cdecl** __cdecl get_global_action_nolock(int))(int)
// 
// Library: Visual Studio 2019 Release

void____cdecl____int_ * __cdecl get_global_action_nolock(int param_1)

{
    if (param_1 == 0x2) {
        return (void____cdecl____int_ *)&DAT_10016458;
    }
    if (param_1 != 0x6) {
        if (param_1 == 0xf) {
            return (void____cdecl____int_ *)&DAT_10016464;
        }
        if (param_1 == 0x15) {
            return (void____cdecl____int_ *)&DAT_1001645c;
        }
        if (param_1 != 0x16) {
            return NULL;
        }
    }
    return (void____cdecl____int_ *)&DAT_10016460;
}



// Library Function - Single Match
//  struct __crt_signal_action_t * __cdecl siglookup(int,struct __crt_signal_action_t * const)
// 
// Library: Visual Studio 2019 Release

__crt_signal_action_t * __cdecl siglookup(int param_1,__crt_signal_action_t *param_2)

{
    __crt_signal_action_t *p_Var1;
    
    p_Var1 = param_2 + 0x90;
    if (param_2 != p_Var1) {
        do {
            if (*(int *)(param_2 + 0x4) == param_1) {
                return param_2;
            }
            param_2 = param_2 + 0xc;
        } while (param_2 != p_Var1);
    }
    return NULL;
}



// Library Function - Single Match
//  ___acrt_get_sigabrt_handler
// 
// Library: Visual Studio 2019 Release

void ___acrt_get_sigabrt_handler(void)

{
    undefined4 local_10;
    undefined4 local_c;
    __crt_seh_guarded_call_void____cdecl___int__ local_5;
    
    local_c = 0x3;
    local_10 = 0x3;
    __crt_seh_guarded_call<void_(__cdecl*)(int)>::
    operator___class__lambda_cbab9ec6f41b0180b23cc171c22676b0__class__lambda_44731a7d0e6d81c3e6aa82d741081786___class__lambda_4b292cb8dd18144e164572427af410ab___
              (&local_5,(_lambda_cbab9ec6f41b0180b23cc171c22676b0_ *)&local_10,(_lambda_44731a7d0e6d81c3e6aa82d741081786_ *)&local_5,(_lambda_4b292cb8dd18144e164572427af410ab_ *)&local_c);
    return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void __cdecl FUN_10007d94(undefined4 param_1)

{
    _DAT_10016458 = param_1;
    _DAT_1001645c = param_1;
    _DAT_10016460 = param_1;
    _DAT_10016464 = param_1;
    return;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  _raise
// 
// Library: Visual Studio 2019 Release

int __cdecl _raise(int _SigNum)

{
    code **ppcVar1;
    __crt_signal_action_t *p_Var2;
    undefined4 *puVar3;
    __acrt_ptd *p_Var4;
    int iVar5;
    char extraout_CL;
    byte bVar6;
    char cVar7;
    __crt_signal_action_t *p_Var8;
    code *pcVar9;
    undefined4 *in_FS_OFFSET;
    undefined4 uVar10;
    undefined4 uVar11;
    undefined4 local_34;
    __crt_signal_action_t *local_30;
    __crt_signal_action_t **local_24;
    char local_1d;
    undefined4 local_14;
    
    local_24 = NULL;
    local_34 = 0x0;
    local_1d = '\x01';
    if (0x8 < _SigNum) {
        if (_SigNum == 0xb) goto LAB_10007e0e;
        if ((_SigNum == 0xf) || ((0x14 < _SigNum && (_SigNum < 0x17)))) goto LAB_10007e01;
LAB_10007e32:
        puVar3 = (undefined4 *)FUN_10005ee9();
        *puVar3 = 0x16;
        FUN_10005e08();
LAB_10007e1c:
        iVar5 = -0x1;
        goto LAB_10007f81;
    }
    if (_SigNum == 0x8) {
LAB_10007e0e:
        local_24 = (__crt_signal_action_t **)FUN_10005978();
        if (local_24 == NULL) goto LAB_10007e1c;
        p_Var2 = siglookup(_SigNum,*local_24);
        if (p_Var2 == NULL) goto LAB_10007e32;
        ppcVar1 = (code **)(p_Var2 + 0x8);
        cVar7 = '\0';
        local_1d = '\0';
    }
    else {
        if (_SigNum != 0x2) {
            if (_SigNum == 0x4) goto LAB_10007e0e;
            if (_SigNum != 0x6) goto LAB_10007e32;
        }
LAB_10007e01:
        ppcVar1 = (code **)get_global_action_nolock(_SigNum);
        cVar7 = extraout_CL;
    }
    local_30 = NULL;
    if (cVar7 != '\0') {
        ___acrt_lock(0x3);
        cVar7 = local_1d;
    }
    pcVar9 = *ppcVar1;
    if (cVar7 != '\0') {
        bVar6 = (byte)DAT_10015124 & 0x1f;
        pcVar9 = (code *)(((uint)pcVar9 ^ (uint)DAT_10015124) >> bVar6 | ((uint)pcVar9 ^ (uint)DAT_10015124) << 0x20 - bVar6);
        cVar7 = local_1d;
    }
    if (pcVar9 != (code *)0x1) {
        if (pcVar9 == NULL) {
            if (cVar7 != '\0') {
                ___acrt_unlock(0x3);
            }
            __exit(0x3);
            pcVar9 = (code *)swi(0x3);
            iVar5 = (*pcVar9)();
            return iVar5;
        }
        if (((_SigNum == 0x8) || (_SigNum == 0xb)) || (_SigNum == 0x4)) {
            local_30 = local_24[0x1];
            local_24[0x1] = NULL;
            if (_SigNum == 0x8) {
                p_Var4 = FUN_10005827();
                local_34 = *(undefined4 *)(p_Var4 + 0x8);
                p_Var4 = FUN_10005827();
                *(undefined4 *)(p_Var4 + 0x8) = 0x8c;
                goto LAB_10007ed6;
            }
        }
        else {
LAB_10007ed6:
            if (_SigNum == 0x8) {
                p_Var2 = *local_24;
                for (p_Var8 = p_Var2 + 0x24; p_Var8 != p_Var2 + 0x90; p_Var8 = p_Var8 + 0xc) {
                    *(undefined4 *)(p_Var8 + 0x8) = 0x0;
                }
                goto LAB_10007f09;
            }
        }
        *ppcVar1 = DAT_10015124;
    }
LAB_10007f09:
    FUN_10007f3e();
    if (pcVar9 != (code *)0x1) {
        if (_SigNum == 0x8) {
            p_Var4 = FUN_10005827();
            uVar11 = *(undefined4 *)(p_Var4 + 0x8);
            uVar10 = 0x8;
            _guard_check_icall();
            (*pcVar9)(uVar10,uVar11);
        }
        else {
            iVar5 = _SigNum;
            _guard_check_icall();
            (*pcVar9)(iVar5);
            if ((_SigNum != 0xb) && (_SigNum != 0x4)) goto LAB_10007f7f;
        }
        local_24[0x1] = local_30;
        if (_SigNum == 0x8) {
            p_Var4 = FUN_10005827();
            *(undefined4 *)(p_Var4 + 0x8) = local_34;
        }
    }
LAB_10007f7f:
    iVar5 = 0x0;
LAB_10007f81:
    *in_FS_OFFSET = local_14;
    return iVar5;
}



void FUN_10007f3e(void)

{
    int unaff_EBP;
    
    if (*(char *)(unaff_EBP + -0x19) != '\0') {
        ___acrt_unlock(0x3);
    }
    return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// Library Function - Single Match
//  ___acrt_has_user_matherr
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

uint ___acrt_has_user_matherr(void)

{
    uint uVar1;
    byte bVar2;
    
    bVar2 = (byte)DAT_10015124 & 0x1f;
    uVar1 = (DAT_10015124 ^ _DAT_10016468) >> bVar2 | (DAT_10015124 ^ _DAT_10016468) << 0x20 - bVar2;
    return uVar1 & 0xffffff00 | (uint)(uVar1 != 0x0);
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void __cdecl FUN_10007fbd(undefined4 param_1)

{
    _DAT_10016468 = param_1;
    return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// Library Function - Single Match
//  ___acrt_invoke_user_matherr
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

undefined4 __cdecl ___acrt_invoke_user_matherr(undefined4 param_1)

{
    undefined4 uVar1;
    byte bVar2;
    code *pcVar3;
    
    bVar2 = (byte)DAT_10015124 & 0x1f;
    pcVar3 = (code *)((DAT_10015124 ^ _DAT_10016468) >> bVar2 | (DAT_10015124 ^ _DAT_10016468) << 0x20 - bVar2);
    if (pcVar3 == NULL) {
        uVar1 = 0x0;
    }
    else {
        _guard_check_icall();
        uVar1 = (*pcVar3)(param_1);
    }
    return uVar1;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4

void FUN_10007ffe(int *param_1,int **param_2)

{
    bool bVar1;
    int iVar2;
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    FUN_100083c6(*param_1);
    bVar1 = common_flush_all_should_try_to_flush_stream(SUB41(**param_2,0x0),param_2[0x1]);
    if ((bVar1) && ((*(char *)param_2[0x2] != '\0' || ((*(uint *)(**param_2 + 0xc) >> 0x1 & 0x1) != 0x0)))) {
        iVar2 = FUN_10008244((FILE *)**param_2);
        if (iVar2 == -0x1) {
            *param_2[0x3] = -0x1;
        }
        else {
            *param_2[0x1] = *param_2[0x1] + 0x1;
        }
    }
    FUN_1000807e();
    *in_FS_OFFSET = local_14;
    return;
}



void FUN_1000807e(void)

{
    int unaff_EBP;
    
    __unlock_file(**(FILE ***)(unaff_EBP + 0x10));
    return;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  public: void __thiscall __crt_seh_guarded_call<void>::operator()<class <lambda_2cc53f568c5a2bb6f192f930a45d44ea>,class <lambda_ab61a845afdef5b7c387490eaf3616ee>&,class
// <lambda_c2ffc0b7726aa6be21d5f0026187e748>>(class <lambda_2cc53f568c5a2bb6f192f930a45d44ea>&&,class <lambda_ab61a845afdef5b7c387490eaf3616ee>&,class <lambda_c2ffc0b7726aa6be21d5f0026187e748>&&)
// 
// Library: Visual Studio 2019 Release

void __thiscall
__crt_seh_guarded_call<void>::operator___class__lambda_2cc53f568c5a2bb6f192f930a45d44ea__class__lambda_ab61a845afdef5b7c387490eaf3616ee___class__lambda_c2ffc0b7726aa6be21d5f0026187e748___
          (__crt_seh_guarded_call_void_ *this,_lambda_2cc53f568c5a2bb6f192f930a45d44ea_ *param_1,_lambda_ab61a845afdef5b7c387490eaf3616ee_ *param_2,_lambda_c2ffc0b7726aa6be21d5f0026187e748_ *param_3)

{
    int *piVar1;
    bool bVar2;
    int *piVar3;
    undefined4 *in_FS_OFFSET;
    int *local_40;
    undefined4 local_3c;
    undefined4 local_38;
    undefined4 local_34;
    int *local_30;
    int local_2c;
    int local_28;
    int local_24 [0x4];
    undefined4 local_14;
    undefined4 uStack12;
    undefined *local_8;
    
    local_8 = &DAT_100139b0;
    uStack12 = 0x10008096;
    ___acrt_lock(*(int *)param_1);
    local_8 = NULL;
    piVar1 = DAT_10016474 + DAT_10016470;
    for (piVar3 = DAT_10016474; local_30 = piVar3, piVar3 != piVar1; piVar3 = piVar3 + 0x1) {
        local_24[0] = *piVar3;
        bVar2 = common_flush_all_should_try_to_flush_stream(SUB41(local_24[0],0x0),*(int **)param_2);
        if (bVar2) {
            local_34 = *(undefined4 *)(param_2 + 0x8);
            local_38 = *(undefined4 *)(param_2 + 0x4);
            local_3c = *(undefined4 *)param_2;
            local_40 = local_24;
            local_28 = local_24[0];
            local_2c = local_24[0];
            FUN_10007ffe(&local_2c,&local_40);
        }
    }
    local_8 = (undefined *)0xfffffffe;
    FUN_1000812a();
    *in_FS_OFFSET = local_14;
    return;
}



void FUN_1000812a(void)

{
    int unaff_EBP;
    
    ___acrt_unlock(**(int **)(unaff_EBP + 0x10));
    return;
}



// Library Function - Single Match
//  int __cdecl common_flush_all(bool)
// 
// Library: Visual Studio 2019 Release

int __cdecl common_flush_all(bool param_1)

{
    int *local_24;
    bool *local_20;
    int *local_1c;
    undefined4 local_18;
    undefined4 local_14;
    int local_10;
    int local_c;
    __crt_seh_guarded_call_void_ local_5;
    
    local_c = 0x0;
    local_24 = &local_c;
    local_10 = 0x0;
    local_20 = &param_1;
    local_1c = &local_10;
    local_14 = 0x8;
    local_18 = 0x8;
    __crt_seh_guarded_call<void>::operator___class__lambda_2cc53f568c5a2bb6f192f930a45d44ea__class__lambda_ab61a845afdef5b7c387490eaf3616ee___class__lambda_c2ffc0b7726aa6be21d5f0026187e748___
              (&local_5,(_lambda_2cc53f568c5a2bb6f192f930a45d44ea_ *)&local_18,(_lambda_ab61a845afdef5b7c387490eaf3616ee_ *)&local_24,(_lambda_c2ffc0b7726aa6be21d5f0026187e748_ *)&local_14);
    if (param_1 == false) {
        local_c = local_10;
    }
    return local_c;
}



// Library Function - Single Match
//  bool __cdecl common_flush_all_should_try_to_flush_stream(class __crt_stdio_stream,int * const)
// 
// Library: Visual Studio 2019 Release

bool __cdecl common_flush_all_should_try_to_flush_stream(__crt_stdio_stream param_1,int *param_2)

{
    bool bVar1;
    undefined3 in_stack_00000005;
    
    if ((_param_1 != 0x0) && ((*(uint *)(_param_1 + 0xc) >> 0xd & 0x1) != 0x0)) {
        bVar1 = is_stream_flushable_or_commitable(*(uint *)(_param_1 + 0xc));
        if (bVar1) {
            return true;
        }
        *param_2 = *param_2 + 0x1;
    }
    return false;
}



// Library Function - Single Match
//  bool __cdecl is_stream_flushable_or_commitable(long)
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

bool __cdecl is_stream_flushable_or_commitable(long param_1)

{
    if (((((byte)param_1 & 0x3) != 0x2) || ((param_1 & 0xc0U) == 0x0)) && ((param_1 & 0x800U) == 0x0)) {
        return false;
    }
    return true;
}



undefined4 __cdecl FUN_100081db(FILE *param_1,__acrt_ptd **param_2)

{
    int *piVar1;
    byte *pbVar2;
    char *pcVar3;
    uint uVar4;
    uint uVar5;
    
    piVar1 = &param_1->_flag;
    if ((((byte)*piVar1 & 0x3) == 0x2) && ((*piVar1 & 0xc0U) != 0x0)) {
        pbVar2 = (byte *)param_1->_cnt;
        uVar5 = (int)param_1->_ptr - (int)pbVar2;
        param_1->_ptr = (char *)pbVar2;
        param_1->_base = NULL;
        if (0x0 < (int)uVar5) {
            pcVar3 = (char *)__fileno(param_1);
            uVar4 = FUN_1000a117(pcVar3,pbVar2,uVar5,param_2);
            if (uVar5 != uVar4) {
                LOCK();
                *piVar1 = *piVar1 | 0x10;
                return 0xffffffff;
            }
            if (((uint)*piVar1 >> 0x2 & 0x1) != 0x0) {
                LOCK();
                *piVar1 = *piVar1 & 0xfffffffd;
            }
        }
    }
    return 0x0;
}



int __cdecl FUN_10008244(FILE *param_1)

{
    int iVar1;
    int iVar2;
    __acrt_ptd *local_2c [0xa];
    
    iVar2 = 0x0;
    FUN_10005250(local_2c,NULL);
    if (param_1 == NULL) {
        iVar2 = common_flush_all(false);
        goto LAB_1000829b;
    }
    iVar1 = FUN_100081db(param_1,local_2c);
    if (iVar1 == 0x0) {
        if (((uint)param_1->_flag >> 0xb & 0x1) == 0x0) goto LAB_1000829b;
        iVar1 = __fileno(param_1);
        iVar1 = __commit(iVar1);
        if (iVar1 == 0x0) goto LAB_1000829b;
    }
    iVar2 = -0x1;
LAB_1000829b:
    FUN_100052b0(local_2c);
    return iVar2;
}



// Library Function - Single Match
//  __flushall
// 
// Library: Visual Studio 2019 Release

int __cdecl __flushall(void)

{
    int iVar1;
    
    iVar1 = common_flush_all(true);
    return iVar1;
}



void __cdecl FUN_100083c6(int param_1)

{
    EnterCriticalSection((LPCRITICAL_SECTION)(param_1 + 0x20));
    return;
}



// Library Function - Single Match
//  __unlock_file
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl __unlock_file(FILE *_File)

{
    LeaveCriticalSection((LPCRITICAL_SECTION)(_File + 0x1));
    return;
}



// Library Function - Single Match
//  __malloc_base
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

LPVOID __cdecl __malloc_base(size_t param_1)

{
    int iVar1;
    LPVOID pvVar2;
    undefined4 *puVar3;
    
    if (param_1 < 0xffffffe1) {
        if (param_1 == 0x0) {
            param_1 = 0x1;
        }
        do {
            pvVar2 = HeapAlloc(DAT_10016248,0x0,param_1);
            if (pvVar2 != NULL) {
                return pvVar2;
            }
            iVar1 = FUN_10008a8c();
        } while ((iVar1 != 0x0) && (iVar1 = __callnewh(param_1), iVar1 != 0x0));
    }
    puVar3 = (undefined4 *)FUN_10005ee9();
    *puVar3 = 0xc;
    return NULL;
}



// Library Function - Single Match
//  ___acrt_update_locale_info
// 
// Library: Visual Studio 2019 Release

void __cdecl ___acrt_update_locale_info(int param_1,int *param_2)

{
    undefined **ppuVar1;
    
    if ((*param_2 != DAT_1001646c) && ((*(uint *)(param_1 + 0x350) & DAT_10015800) == 0x0)) {
        ppuVar1 = ___acrt_update_thread_locale_data();
        *param_2 = (int)ppuVar1;
    }
    return;
}



void __cdecl FUN_10008469(int param_1,int *param_2,int param_3)

{
    undefined **ppuVar1;
    
    if ((*param_2 != (&DAT_1001646c)[param_3]) && ((*(uint *)(param_1 + 0x350) & DAT_10015800) == 0x0)) {
        ppuVar1 = ___acrt_update_thread_locale_data();
        *param_2 = (int)ppuVar1;
    }
    return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void __cdecl FUN_1000849a(int param_1,int *param_2)

{
    int iVar1;
    
    if ((*param_2 != _DAT_10016148) && ((*(uint *)(param_1 + 0x350) & DAT_10015800) == 0x0)) {
        iVar1 = FUN_10006fb0();
        *param_2 = iVar1;
    }
    return;
}



void __cdecl FUN_100084c7(int param_1,int *param_2,int param_3)

{
    int iVar1;
    
    if ((*param_2 != *(int *)(&DAT_10016148 + param_3 * 0x4)) && ((*(uint *)(param_1 + 0x350) & DAT_10015800) == 0x0)) {
        iVar1 = FUN_10006fb0();
        *param_2 = iVar1;
    }
    return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

uint __cdecl FUN_100084f8(LPWSTR param_1,byte *param_2,uint param_3,__acrt_ptd **param_4)

{
    int *piVar1;
    uint uVar2;
    int iVar3;
    
    if ((param_2 == NULL) || (param_3 == 0x0)) {
        _DAT_10016480 = 0x0;
        _DAT_10016484 = 0x0;
    }
    else {
        if (*param_2 != 0x0) {
            if (*(char *)(param_4 + 0x5) == '\0') {
                FUN_100053a0(param_4);
            }
            piVar1 = (int *)param_4[0x3];
            uVar2 = piVar1[0x2];
            if (uVar2 == 0xfde9) {
                uVar2 = FUN_1000a599(param_1,param_2,param_3,(byte **)&DAT_10016480,(int)param_4);
                if (-0x1 < (int)uVar2) {
                    return uVar2;
                }
            }
            else {
                if (piVar1[0x2a] == 0x0) {
                    if (param_1 != NULL) {
                        *param_1 = (ushort)*param_2;
                    }
                    return 0x1;
                }
                if (*(short *)(*piVar1 + (uint)*param_2 * 0x2) < 0x0) {
                    iVar3 = *(int *)(param_4[0x3] + 0x4);
                    if ((((0x1 < iVar3) && (iVar3 <= (int)param_3)) && (iVar3 = ___acrt_MultiByteToWideChar(uVar2,0x9,(LPCSTR)param_2,iVar3,param_1,(uint)(param_1 != NULL)), iVar3 != 0x0)) ||
                       ((*(uint *)(param_4[0x3] + 0x4) <= param_3 && (param_2[0x1] != 0x0)))) {
                        return *(uint *)(param_4[0x3] + 0x4);
                    }
                }
                else {
                    iVar3 = ___acrt_MultiByteToWideChar(uVar2,0x9,(LPCSTR)param_2,0x1,param_1,(uint)(param_1 != NULL));
                    if (iVar3 != 0x0) {
                        return 0x1;
                    }
                }
                *(undefined *)(param_4 + 0x7) = 0x1;
                param_4[0x6] = (__acrt_ptd *)0x2a;
            }
            return 0xffffffff;
        }
        if (param_1 != NULL) {
            *param_1 = L'\0';
        }
    }
    return 0x0;
}



// Library Function - Single Match
//  __fileno
// 
// Library: Visual Studio

int __cdecl __fileno(FILE *_File)

{
    undefined4 *puVar1;
    
    if (_File == NULL) {
        puVar1 = (undefined4 *)FUN_10005ee9();
        *puVar1 = 0x16;
        FUN_10005e08();
        return -0x1;
    }
    return _File->_file;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  public: void __thiscall __crt_seh_guarded_call<void>::operator()<class <lambda_e5124f882df8998aaf41531e079ba474>,class <lambda_3e16ef9562a7dcce91392c22ab16ea36>&,class
// <lambda_e25ca0880e6ef98be67edffd8c599615>>(class <lambda_e5124f882df8998aaf41531e079ba474>&&,class <lambda_3e16ef9562a7dcce91392c22ab16ea36>&,class <lambda_e25ca0880e6ef98be67edffd8c599615>&&)
// 
// Library: Visual Studio 2019 Release

void __thiscall
__crt_seh_guarded_call<void>::operator___class__lambda_e5124f882df8998aaf41531e079ba474__class__lambda_3e16ef9562a7dcce91392c22ab16ea36___class__lambda_e25ca0880e6ef98be67edffd8c599615___
          (__crt_seh_guarded_call_void_ *this,_lambda_e5124f882df8998aaf41531e079ba474_ *param_1,_lambda_3e16ef9562a7dcce91392c22ab16ea36_ *param_2,_lambda_e25ca0880e6ef98be67edffd8c599615_ *param_3)

{
    undefined **ppuVar1;
    int *piVar2;
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    ___acrt_lock(*(int *)param_1);
    for (piVar2 = &DAT_1001646c; piVar2 != &DAT_10016470; piVar2 = piVar2 + 0x1) {
        if ((undefined **)*piVar2 != &PTR_DAT_10015690) {
            ppuVar1 = __updatetlocinfoEx_nolock(piVar2,&PTR_DAT_10015690);
            *piVar2 = (int)ppuVar1;
        }
    }
    FUN_100086b4();
    *in_FS_OFFSET = local_14;
    return;
}



void FUN_100086b4(void)

{
    int unaff_EBP;
    
    ___acrt_unlock(**(int **)(unaff_EBP + 0x10));
    return;
}



undefined4 FUN_100086c0(void)

{
    undefined4 uVar1;
    
    uVar1 = DAT_10016488;
    DAT_10016488 = 0x1;
    return uVar1;
}



// Library Function - Single Match
//  ___acrt_uninitialize_locale
// 
// Library: Visual Studio 2019 Release

void ___acrt_uninitialize_locale(void)

{
    undefined4 local_10;
    undefined4 local_c;
    __crt_seh_guarded_call_void_ local_5;
    
    local_c = 0x4;
    local_10 = 0x4;
    __crt_seh_guarded_call<void>::operator___class__lambda_e5124f882df8998aaf41531e079ba474__class__lambda_3e16ef9562a7dcce91392c22ab16ea36___class__lambda_e25ca0880e6ef98be67edffd8c599615___
              (&local_5,(_lambda_e5124f882df8998aaf41531e079ba474_ *)&local_10,(_lambda_3e16ef9562a7dcce91392c22ab16ea36_ *)&local_5,(_lambda_e25ca0880e6ef98be67edffd8c599615_ *)&local_c);
    return;
}



// Library Function - Single Match
//  ___acrt_add_locale_ref
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl ___acrt_add_locale_ref(int param_1)

{
    int *piVar1;
    int **ppiVar2;
    int iVar3;
    
    LOCK();
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 0x1;
    piVar1 = *(int **)(param_1 + 0x7c);
    if (piVar1 != NULL) {
        LOCK();
        *piVar1 = *piVar1 + 0x1;
    }
    piVar1 = *(int **)(param_1 + 0x84);
    if (piVar1 != NULL) {
        LOCK();
        *piVar1 = *piVar1 + 0x1;
    }
    piVar1 = *(int **)(param_1 + 0x80);
    if (piVar1 != NULL) {
        LOCK();
        *piVar1 = *piVar1 + 0x1;
    }
    piVar1 = *(int **)(param_1 + 0x8c);
    if (piVar1 != NULL) {
        LOCK();
        *piVar1 = *piVar1 + 0x1;
    }
    ppiVar2 = (int **)(param_1 + 0x28);
    iVar3 = 0x6;
    do {
        if ((ppiVar2[-0x2] != (int *)&DAT_10015750) && (piVar1 = *ppiVar2, piVar1 != NULL)) {
            LOCK();
            *piVar1 = *piVar1 + 0x1;
        }
        if ((ppiVar2[-0x3] != NULL) && (piVar1 = ppiVar2[-0x1], piVar1 != NULL)) {
            LOCK();
            *piVar1 = *piVar1 + 0x1;
        }
        ppiVar2 = ppiVar2 + 0x4;
        iVar3 = iVar3 + -0x1;
    } while (iVar3 != 0x0);
    ___acrt_locale_add_lc_time_reference(*(undefined ***)(param_1 + 0x9c));
    return;
}



// Library Function - Single Match
//  ___acrt_free_locale
// 
// Library: Visual Studio 2019 Release

void __cdecl ___acrt_free_locale(int param_1)

{
    int *piVar1;
    LPVOID *ppvVar2;
    int **ppiVar3;
    int local_8;
    
    if ((((*(undefined ***)(param_1 + 0x88) != NULL) && (*(undefined ***)(param_1 + 0x88) != &PTR_DAT_10015808)) && (*(int **)(param_1 + 0x7c) != NULL)) && (**(int **)(param_1 + 0x7c) == 0x0)) {
        piVar1 = *(int **)(param_1 + 0x84);
        if ((piVar1 != NULL) && (*piVar1 == 0x0)) {
            FUN_10005f59(piVar1);
            ___acrt_locale_free_monetary(*(int *)(param_1 + 0x88));
        }
        piVar1 = *(int **)(param_1 + 0x80);
        if ((piVar1 != NULL) && (*piVar1 == 0x0)) {
            FUN_10005f59(piVar1);
            ___acrt_locale_free_numeric(*(int **)(param_1 + 0x88));
        }
        FUN_10005f59(*(LPVOID *)(param_1 + 0x7c));
        FUN_10005f59(*(LPVOID *)(param_1 + 0x88));
    }
    if ((*(int **)(param_1 + 0x8c) != NULL) && (**(int **)(param_1 + 0x8c) == 0x0)) {
        FUN_10005f59((LPVOID)(*(int *)(param_1 + 0x90) + -0xfe));
        FUN_10005f59((LPVOID)(*(int *)(param_1 + 0x94) + -0x80));
        FUN_10005f59((LPVOID)(*(int *)(param_1 + 0x98) + -0x80));
        FUN_10005f59(*(LPVOID *)(param_1 + 0x8c));
    }
    ___acrt_locale_free_lc_time_if_unreferenced(*(undefined ***)(param_1 + 0x9c));
    ppvVar2 = (LPVOID *)(param_1 + 0xa0);
    local_8 = 0x6;
    ppiVar3 = (int **)(param_1 + 0x28);
    do {
        if (((ppiVar3[-0x2] != (int *)&DAT_10015750) && (piVar1 = *ppiVar3, piVar1 != NULL)) && (*piVar1 == 0x0)) {
            FUN_10005f59(piVar1);
            FUN_10005f59(*ppvVar2);
        }
        if (((ppiVar3[-0x3] != NULL) && (piVar1 = ppiVar3[-0x1], piVar1 != NULL)) && (*piVar1 == 0x0)) {
            FUN_10005f59(piVar1);
        }
        ppvVar2 = ppvVar2 + 0x1;
        ppiVar3 = ppiVar3 + 0x4;
        local_8 = local_8 + -0x1;
    } while (local_8 != 0x0);
    FUN_10005f59((LPVOID)param_1);
    return;
}



// Library Function - Single Match
//  ___acrt_locale_add_lc_time_reference
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

undefined * __cdecl ___acrt_locale_add_lc_time_reference(undefined **param_1)

{
    undefined **ppuVar1;
    undefined *puVar2;
    
    if ((param_1 != NULL) && (param_1 != &PTR_DAT_1000f4a8)) {
        LOCK();
        ppuVar1 = param_1 + 0x2c;
        puVar2 = *ppuVar1;
        *ppuVar1 = *ppuVar1 + 0x1;
        return puVar2 + 0x1;
    }
    return (undefined *)0x7fffffff;
}



// Library Function - Single Match
//  ___acrt_locale_free_lc_time_if_unreferenced
// 
// Library: Visual Studio 2019 Release

void __cdecl ___acrt_locale_free_lc_time_if_unreferenced(undefined **param_1)

{
    if (((param_1 != NULL) && (param_1 != &PTR_DAT_1000f4a8)) && (param_1[0x2c] == NULL)) {
        ___acrt_locale_free_time(param_1);
        FUN_10005f59(param_1);
    }
    return;
}



// Library Function - Single Match
//  ___acrt_locale_release_lc_time_reference
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

undefined * __cdecl ___acrt_locale_release_lc_time_reference(undefined **param_1)

{
    undefined **ppuVar1;
    undefined *puVar2;
    
    if ((param_1 != NULL) && (param_1 != &PTR_DAT_1000f4a8)) {
        LOCK();
        ppuVar1 = param_1 + 0x2c;
        puVar2 = *ppuVar1;
        *ppuVar1 = *ppuVar1 + -0x1;
        return puVar2 + -0x1;
    }
    return (undefined *)0x7fffffff;
}



// Library Function - Single Match
//  ___acrt_release_locale_ref
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl ___acrt_release_locale_ref(int param_1)

{
    int *piVar1;
    int **ppiVar2;
    int iVar3;
    
    if (param_1 != 0x0) {
        LOCK();
        *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + -0x1;
        piVar1 = *(int **)(param_1 + 0x7c);
        if (piVar1 != NULL) {
            LOCK();
            *piVar1 = *piVar1 + -0x1;
        }
        piVar1 = *(int **)(param_1 + 0x84);
        if (piVar1 != NULL) {
            LOCK();
            *piVar1 = *piVar1 + -0x1;
        }
        piVar1 = *(int **)(param_1 + 0x80);
        if (piVar1 != NULL) {
            LOCK();
            *piVar1 = *piVar1 + -0x1;
        }
        piVar1 = *(int **)(param_1 + 0x8c);
        if (piVar1 != NULL) {
            LOCK();
            *piVar1 = *piVar1 + -0x1;
        }
        ppiVar2 = (int **)(param_1 + 0x28);
        iVar3 = 0x6;
        do {
            if ((ppiVar2[-0x2] != (int *)&DAT_10015750) && (piVar1 = *ppiVar2, piVar1 != NULL)) {
                LOCK();
                *piVar1 = *piVar1 + -0x1;
            }
            if ((ppiVar2[-0x3] != NULL) && (piVar1 = ppiVar2[-0x1], piVar1 != NULL)) {
                LOCK();
                *piVar1 = *piVar1 + -0x1;
            }
            ppiVar2 = ppiVar2 + 0x4;
            iVar3 = iVar3 + -0x1;
        } while (iVar3 != 0x0);
        ___acrt_locale_release_lc_time_reference(*(undefined ***)(param_1 + 0x9c));
    }
    return;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  ___acrt_update_thread_locale_data
// 
// Library: Visual Studio 2019 Release

undefined ** ___acrt_update_thread_locale_data(void)

{
    code *pcVar1;
    __acrt_ptd *p_Var2;
    undefined **ppuVar3;
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    p_Var2 = FUN_10005827();
    if (((*(uint *)(p_Var2 + 0x350) & DAT_10015800) == 0x0) || (ppuVar3 = *(undefined ***)(p_Var2 + 0x4c), ppuVar3 == NULL)) {
        ___acrt_lock(0x4);
        ppuVar3 = __updatetlocinfoEx_nolock((int *)(p_Var2 + 0x4c),DAT_1001646c);
        FUN_10008a1b();
        if (ppuVar3 == NULL) {
            _abort();
            pcVar1 = (code *)swi(0x3);
            ppuVar3 = (undefined **)(*pcVar1)();
            return ppuVar3;
        }
    }
    *in_FS_OFFSET = local_14;
    return ppuVar3;
}



void FUN_10008a1b(void)

{
    ___acrt_unlock(0x4);
    return;
}



// Library Function - Single Match
//  __updatetlocinfoEx_nolock
// 
// Library: Visual Studio 2019 Release

undefined ** __cdecl __updatetlocinfoEx_nolock(int *param_1,undefined **param_2)

{
    undefined **ppuVar1;
    
    if ((param_2 == NULL) || (param_1 == NULL)) {
        param_2 = NULL;
    }
    else {
        ppuVar1 = (undefined **)*param_1;
        if (ppuVar1 != param_2) {
            *param_1 = (int)param_2;
            ___acrt_add_locale_ref((int)param_2);
            if (((ppuVar1 != NULL) && (___acrt_release_locale_ref((int)ppuVar1), ppuVar1[0x3] == NULL)) && (ppuVar1 != &PTR_DAT_10015690)) {
                ___acrt_free_locale((int)ppuVar1);
            }
        }
    }
    return param_2;
}



undefined4 FUN_10008a8c(void)

{
    return DAT_1001648c;
}



// Library Function - Single Match
//  _qsort
// 
// Library: Visual Studio 2019 Release

void __cdecl _qsort(void *_Base,size_t _NumOfElements,size_t _SizeOfElements,_PtFuncCompare *_PtFuncCompare)

{
    undefined uVar1;
    undefined4 *puVar2;
    uint uVar3;
    int iVar4;
    int iVar5;
    undefined in_DL;
    undefined extraout_DL;
    undefined *puVar6;
    undefined *puVar7;
    size_t sVar8;
    undefined *puVar9;
    undefined *puVar10;
    int in_stack_fffffee4;
    undefined *local_110;
    undefined *local_108;
    undefined *local_100;
    undefined *local_fc;
    undefined4 auStack248 [0x1e];
    undefined4 auStack128 [0x1e];
    uint local_8;
    
    local_8 = DAT_10015124 ^ (uint)&stack0xfffffffc;
    local_108 = (undefined *)_Base;
    if ((((_Base == NULL) && (_NumOfElements != 0x0)) || (_SizeOfElements == 0x0)) || (_PtFuncCompare == NULL)) {
        puVar2 = (undefined4 *)FUN_10005ee9();
        *puVar2 = 0x16;
        FUN_10005e08();
        in_DL = extraout_DL;
    }
    else {
        in_stack_fffffee4 = 0x0;
        if (0x1 < _NumOfElements) {
            local_fc = (undefined *)((_NumOfElements - 0x1) * _SizeOfElements + (int)_Base);
LAB_10008b22:
            while( true ) {
                uVar3 = (uint)((int)local_fc - (int)local_108) / _SizeOfElements + 0x1;
                if (uVar3 < 0x9) break;
                iVar4 = (uVar3 >> 0x1) * _SizeOfElements;
                puVar7 = local_108 + iVar4;
                puVar9 = local_108;
                puVar6 = puVar7;
                _guard_check_icall();
                iVar5 = (*_PtFuncCompare)(puVar9,puVar6);
                if ((0x0 < iVar5) && (sVar8 = _SizeOfElements, puVar9 = puVar7, local_108 != puVar7)) {
                    do {
                        uVar1 = puVar9[-iVar4];
                        puVar9[-iVar4] = *puVar9;
                        *puVar9 = uVar1;
                        sVar8 = sVar8 - 0x1;
                        puVar9 = puVar9 + 0x1;
                    } while (sVar8 != 0x0);
                }
                puVar9 = local_108;
                puVar6 = local_fc;
                _guard_check_icall();
                iVar4 = (*_PtFuncCompare)(puVar9,puVar6);
                if ((0x0 < iVar4) && (sVar8 = _SizeOfElements, puVar9 = local_fc, local_108 != local_fc)) {
                    do {
                        puVar6 = puVar9 + 0x1;
                        uVar1 = puVar6[(int)(local_108 + (-0x1 - (int)local_fc))];
                        puVar6[(int)(local_108 + (-0x1 - (int)local_fc))] = *puVar9;
                        *puVar9 = uVar1;
                        sVar8 = sVar8 - 0x1;
                        puVar9 = puVar6;
                    } while (sVar8 != 0x0);
                }
                puVar9 = puVar7;
                puVar6 = local_fc;
                _guard_check_icall();
                iVar4 = (*_PtFuncCompare)(puVar9,puVar6);
                local_110 = local_108;
                local_100 = local_fc;
                if ((0x0 < iVar4) && (sVar8 = _SizeOfElements, puVar9 = local_fc, puVar7 != local_fc)) {
                    do {
                        puVar6 = puVar9 + 0x1;
                        uVar1 = puVar6[(int)(puVar7 + (-0x1 - (int)local_fc))];
                        puVar6[(int)(puVar7 + (-0x1 - (int)local_fc))] = *puVar9;
                        *puVar9 = uVar1;
                        sVar8 = sVar8 - 0x1;
                        puVar9 = puVar6;
                    } while (sVar8 != 0x0);
                }
LAB_10008d33:
                if (local_110 < puVar7) {
                    do {
                        local_110 = local_110 + _SizeOfElements;
                        if (puVar7 <= local_110) goto LAB_10008d80;
                        puVar9 = local_110;
                        puVar6 = puVar7;
                        _guard_check_icall();
                        iVar4 = (*_PtFuncCompare)(puVar9,puVar6);
                        puVar9 = local_100;
                    } while (iVar4 < 0x1);
                }
                else {
LAB_10008d80:
                    do {
                        local_110 = local_110 + _SizeOfElements;
                        puVar9 = local_100;
                        if (local_fc < local_110) break;
                        puVar9 = local_110;
                        puVar6 = puVar7;
                        _guard_check_icall();
                        iVar4 = (*_PtFuncCompare)(puVar9,puVar6);
                        puVar9 = local_100;
                    } while (iVar4 < 0x1);
                }
                do {
                    local_100 = puVar9;
                    puVar9 = local_100 + -_SizeOfElements;
                    if (puVar9 <= puVar7) break;
                    puVar6 = puVar9;
                    puVar10 = puVar7;
                    _guard_check_icall();
                    iVar4 = (*_PtFuncCompare)(puVar6,puVar10);
                } while (0x0 < iVar4);
                if (local_110 <= puVar9) {
                    puVar6 = puVar9;
                    sVar8 = _SizeOfElements;
                    if (puVar9 != local_110) {
                        do {
                            puVar10 = puVar6 + 0x1;
                            uVar1 = puVar10[(int)(local_110 + (-0x1 - (int)puVar9))];
                            puVar10[(int)(local_110 + (-0x1 - (int)puVar9))] = *puVar6;
                            *puVar6 = uVar1;
                            sVar8 = sVar8 - 0x1;
                            puVar6 = puVar10;
                        } while (sVar8 != 0x0);
                    }
                    local_100 = puVar9;
                    if (puVar7 == puVar9) {
                        puVar7 = local_110;
                    }
                    goto LAB_10008d33;
                }
                if (puVar7 < local_100) {
                    do {
                        local_100 = local_100 + -_SizeOfElements;
                        if (local_100 <= puVar7) goto LAB_10008ea0;
                        puVar9 = local_100;
                        puVar6 = puVar7;
                        _guard_check_icall();
                        iVar4 = (*_PtFuncCompare)(puVar9,puVar6);
                    } while (iVar4 == 0x0);
                }
                else {
LAB_10008ea0:
                    do {
                        local_100 = local_100 + -_SizeOfElements;
                        if (local_100 <= local_108) break;
                        puVar9 = local_100;
                        puVar6 = puVar7;
                        _guard_check_icall();
                        iVar4 = (*_PtFuncCompare)(puVar9,puVar6);
                    } while (iVar4 == 0x0);
                }
                puVar7 = local_fc;
                if ((int)local_100 - (int)local_108 < (int)local_fc - (int)local_110) goto LAB_10008f2a;
                if (local_108 < local_100) {
                    auStack128[in_stack_fffffee4] = local_108;
                    auStack248[in_stack_fffffee4] = local_100;
                    in_stack_fffffee4 = in_stack_fffffee4 + 0x1;
                }
                local_108 = local_110;
                if (local_fc <= local_110) goto LAB_10008f63;
            }
            puVar7 = (undefined *)((uint)((int)local_fc - (int)local_108) % _SizeOfElements);
            if (local_108 < local_fc) {
                puVar7 = local_108 + _SizeOfElements;
                puVar9 = puVar7;
                local_100 = local_108;
                do {
                    for (; puVar9 <= local_fc; puVar9 = puVar9 + _SizeOfElements) {
                        puVar6 = puVar9;
                        puVar10 = local_100;
                        _guard_check_icall();
                        iVar4 = (*_PtFuncCompare)(puVar6,puVar10);
                        if (0x0 < iVar4) {
                            local_100 = puVar9;
                        }
                    }
                    if (local_100 != local_fc) {
                        puVar9 = local_fc;
                        sVar8 = _SizeOfElements;
                        do {
                            uVar1 = puVar9[(int)local_100 - (int)local_fc];
                            (puVar9 + 0x1)[((int)local_100 - (int)local_fc) + -0x1] = *puVar9;
                            *puVar9 = uVar1;
                            sVar8 = sVar8 - 0x1;
                            puVar9 = puVar9 + 0x1;
                        } while (sVar8 != 0x0);
                    }
                    local_fc = local_fc + -_SizeOfElements;
                    puVar9 = puVar7;
                    local_100 = local_108;
                } while (local_108 < local_fc);
            }
            goto LAB_10008f63;
        }
    }
LAB_10008aee:
    FUN_10001f99(local_8 ^ (uint)&stack0xfffffffc,in_DL,(char)in_stack_fffffee4);
    return;
LAB_10008f2a:
    if (local_110 < local_fc) {
        auStack128[in_stack_fffffee4] = local_110;
        auStack248[in_stack_fffffee4] = local_fc;
        in_stack_fffffee4 = in_stack_fffffee4 + 0x1;
    }
    local_fc = local_100;
    if (local_100 <= local_108) {
LAB_10008f63:
        in_DL = SUB41(puVar7,0x0);
        in_stack_fffffee4 = in_stack_fffffee4 + -0x1;
        if (-0x1 < in_stack_fffffee4) {
            local_108 = (undefined *)auStack128[in_stack_fffffee4];
            local_fc = (undefined *)auStack248[in_stack_fffffee4];
            goto LAB_10008b22;
        }
        goto LAB_10008aee;
    }
    goto LAB_10008b22;
}



undefined4 __cdecl FUN_10009045(char *param_1,int param_2,int param_3,int param_4)

{
    char cVar1;
    undefined4 *puVar2;
    char *pcVar3;
    int iVar4;
    undefined4 uStack24;
    int local_8;
    
    if (param_4 == 0x0) {
        if (param_1 == NULL) {
            if (param_2 == 0x0) {
                return 0x0;
            }
        }
        else {
LAB_10008fc7:
            if (param_2 != 0x0) {
                if (param_4 == 0x0) {
                    *param_1 = '\0';
                    return 0x0;
                }
                if (param_3 != 0x0) {
                    local_8 = param_4;
                    pcVar3 = param_1;
                    iVar4 = param_2;
                    if (param_4 == -0x1) {
                        do {
                            cVar1 = pcVar3[param_3 - (int)param_1];
                            *pcVar3 = cVar1;
                            pcVar3 = pcVar3 + 0x1;
                            if (cVar1 == '\0') {
                                return 0x0;
                            }
                            iVar4 = iVar4 + -0x1;
                        } while (iVar4 != 0x0);
                    }
                    else {
                        do {
                            cVar1 = pcVar3[param_3 - (int)param_1];
                            *pcVar3 = cVar1;
                            pcVar3 = pcVar3 + 0x1;
                            if (cVar1 == '\0') {
                                return 0x0;
                            }
                            iVar4 = iVar4 + -0x1;
                        } while ((iVar4 != 0x0) && (local_8 = local_8 + -0x1, local_8 != 0x0));
                        if (local_8 == 0x0) {
                            *pcVar3 = '\0';
                        }
                    }
                    if (iVar4 != 0x0) {
                        return 0x0;
                    }
                    if (param_4 == -0x1) {
                        param_1[param_2 + -0x1] = '\0';
                        return 0x50;
                    }
                    *param_1 = '\0';
                    puVar2 = (undefined4 *)FUN_10005ee9();
                    uStack24 = 0x22;
                    goto LAB_10008fb4;
                }
                *param_1 = '\0';
            }
        }
    }
    else if (param_1 != NULL) goto LAB_10008fc7;
    puVar2 = (undefined4 *)FUN_10005ee9();
    uStack24 = 0x16;
LAB_10008fb4:
    *puVar2 = uStack24;
    FUN_10005e08();
    return uStack24;
}



// Library Function - Single Match
//  _strpbrk
// 
// Library: Visual Studio

char * __cdecl _strpbrk(char *_Str,char *_Control)

{
    byte bVar1;
    char *pcVar2;
    byte *pbVar3;
    undefined4 uStack40;
    undefined4 uStack36;
    undefined4 uStack32;
    undefined4 uStack28;
    undefined4 uStack24;
    undefined4 uStack20;
    undefined4 uStack16;
    undefined4 uStack12;
    
    uStack12 = 0x0;
    uStack16 = 0x0;
    uStack20 = 0x0;
    uStack24 = 0x0;
    uStack28 = 0x0;
    uStack32 = 0x0;
    uStack36 = 0x0;
    uStack40 = 0x0;
    for (; bVar1 = *_Control, bVar1 != 0x0; _Control = (char *)((byte *)_Control + 0x1)) {
        pbVar3 = (byte *)((int)&uStack40 + ((int)(uint)bVar1 >> 0x3));
        *pbVar3 = *pbVar3 | '\x01' << (bVar1 & 0x7);
    }
    do {
        pbVar3 = (byte *)_Str;
        pcVar2 = (char *)(uint)*pbVar3;
        if (*pbVar3 == 0x0) {
            return pcVar2;
        }
        _Str = (char *)(pbVar3 + 0x1);
    } while ((*(byte *)((int)&uStack40 + ((int)pcVar2 >> 0x3)) >> ((uint)pcVar2 & 0x7) & 0x1) == 0x0);
    return (char *)pbVar3;
}



// Library Function - Single Match
//  __mbsdec
// 
// Library: Visual Studio 2019 Release

uchar * __cdecl __mbsdec(uchar *_Start,uchar *_Pos)

{
    uchar *puVar1;
    
    puVar1 = __mbsdec_l(_Start,_Pos,NULL);
    return puVar1;
}



// Library Function - Single Match
//  __mbsdec_l
// 
// Library: Visual Studio 2019 Release

uchar * __cdecl __mbsdec_l(uchar *_Start,uchar *_Pos,_locale_t _Locale)

{
    undefined4 *puVar1;
    byte *pbVar2;
    int local_14 [0x2];
    int local_c;
    char local_8;
    
    if (_Start == NULL) {
        puVar1 = (undefined4 *)FUN_10005ee9();
        *puVar1 = 0x16;
        FUN_10005e08();
        return NULL;
    }
    if (_Pos == NULL) {
        puVar1 = (undefined4 *)FUN_10005ee9();
        *puVar1 = 0x16;
        FUN_10005e08();
    }
    else if (_Start < _Pos) {
        FUN_100065f3(local_14,(__acrt_ptd **)_Locale);
        pbVar2 = _Pos + -0x1;
        if (*(int *)(local_c + 0x8) != 0x0) {
            do {
                pbVar2 = pbVar2 + -0x1;
                if (pbVar2 < _Start) break;
            } while ((*(byte *)(*pbVar2 + 0x19 + local_c) & 0x4) != 0x0);
            pbVar2 = _Pos + (-0x1 - ((int)_Pos - (int)pbVar2 & 0x1U));
        }
        if (local_8 == '\0') {
            return pbVar2;
        }
        *(uint *)(local_14[0] + 0x350) = *(uint *)(local_14[0] + 0x350) & 0xfffffffd;
        return pbVar2;
    }
    return NULL;
}



// WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe

void __cdecl FUN_10009134(__acrt_ptd **param_1,DWORD param_2,LPCSTR param_3,int param_4,LPWORD param_5,uint param_6,int param_7)

{
    uint _Size;
    uint uVar1;
    int iVar2;
    uint uVar3;
    undefined4 *lpSrcStr;
    undefined extraout_DL;
    undefined extraout_DL_00;
    undefined uVar4;
    undefined4 *puVar5;
    int in_stack_ffffffe0;
    int local_1c;
    char local_14;
    
    uVar1 = DAT_10015124 ^ (uint)&stack0xfffffffc;
    FUN_100065f3(&stack0xffffffe0,param_1);
    if (param_6 == 0x0) {
        param_6 = *(uint *)(local_1c + 0x8);
    }
    iVar2 = ___acrt_MultiByteToWideChar(param_6,(uint)(param_7 != 0x0) * 0x8 + 0x1,param_3,param_4,NULL,0x0);
    uVar4 = extraout_DL;
    if (iVar2 == 0x0) goto LAB_10009219;
    _Size = iVar2 * 0x2;
    uVar3 = -(uint)(_Size < _Size + 0x8) & _Size + 0x8;
    if (uVar3 == 0x0) {
        lpSrcStr = NULL;
    }
    else {
        if (uVar3 < 0x401) {
            puVar5 = (undefined4 *)&stack0xffffffd4;
            lpSrcStr = (undefined4 *)&stack0xffffffd4;
            if (&stack0x00000000 != (undefined *)0x2c) {
LAB_100091cc:
                lpSrcStr = puVar5 + 0x2;
            }
        }
        else {
            lpSrcStr = (undefined4 *)__malloc_base(uVar3);
            if (lpSrcStr != NULL) {
                *lpSrcStr = 0xdddd;
                puVar5 = lpSrcStr;
                goto LAB_100091cc;
            }
        }
        if (lpSrcStr != NULL) {
            _memset(lpSrcStr,0x0,_Size);
            iVar2 = ___acrt_MultiByteToWideChar(param_6,0x1,param_3,param_4,(LPWSTR)lpSrcStr,iVar2);
            if (iVar2 != 0x0) {
                GetStringTypeW(param_2,(LPCWSTR)lpSrcStr,iVar2,param_5);
            }
        }
    }
    FUN_1000923d((int)lpSrcStr);
    uVar4 = extraout_DL_00;
LAB_10009219:
    if (local_14 != '\0') {
        *(uint *)(in_stack_ffffffe0 + 0x350) = *(uint *)(in_stack_ffffffe0 + 0x350) & 0xfffffffd;
    }
    FUN_10001f99(uVar1 ^ (uint)&stack0xfffffffc,uVar4,(char)in_stack_ffffffe0);
    return;
}



void __cdecl FUN_1000923d(int param_1)

{
    if ((param_1 != 0x0) && (*(int *)(param_1 + -0x8) == 0xdddd)) {
        FUN_10005f59((int *)(param_1 + -0x8));
    }
    return;
}



// WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe

void __cdecl FUN_1000925d(int *param_1,ushort *param_2,uint param_3,char *param_4,int param_5,LPWSTR param_6,int param_7,uint param_8,int param_9)

{
    uint uVar1;
    int iVar2;
    uint uVar3;
    undefined4 *puVar4;
    int iVar5;
    undefined4 *puVar6;
    int iVar7;
    undefined extraout_DL;
    undefined extraout_DL_00;
    undefined uVar8;
    undefined4 *puVar9;
    
    uVar1 = DAT_10015124 ^ (uint)&stack0xfffffffc;
    iVar5 = param_5;
    if (0x0 < param_5) {
        iVar2 = ___strncnt(param_4,param_5);
        iVar5 = iVar2 + 0x1;
        if (param_5 <= iVar2) {
            iVar5 = iVar2;
        }
    }
    if (param_8 == 0x0) {
        param_8 = *(uint *)(*param_1 + 0x8);
    }
    iVar2 = ___acrt_MultiByteToWideChar(param_8,(uint)(param_9 != 0x0) * 0x8 + 0x1,param_4,iVar5,NULL,0x0);
    uVar8 = extraout_DL;
    if (iVar2 == 0x0) goto LAB_10009439;
    uVar3 = iVar2 * 0x2 + 0x8;
    uVar3 = -(uint)((uint)(iVar2 * 0x2) < uVar3) & uVar3;
    if (uVar3 == 0x0) {
        puVar4 = NULL;
    }
    else {
        if (uVar3 < 0x401) {
            puVar6 = (undefined4 *)&stack0xffffffe8;
            puVar4 = (undefined4 *)&stack0xffffffe8;
            iVar7 = iVar2;
            if (&stack0x00000000 != (undefined *)0x18) {
LAB_1000930a:
                puVar4 = puVar6 + 0x2;
                iVar7 = iVar2;
            }
        }
        else {
            puVar4 = (undefined4 *)__malloc_base(uVar3);
            iVar7 = iVar2;
            if (puVar4 != NULL) {
                *puVar4 = 0xdddd;
                puVar6 = puVar4;
                goto LAB_1000930a;
            }
        }
        iVar2 = iVar7;
        if (((puVar4 != NULL) && (iVar5 = ___acrt_MultiByteToWideChar(param_8,0x1,param_4,iVar5,(LPWSTR)puVar4,iVar7), iVar2 = iVar7, iVar5 != 0x0)) &&
           (iVar5 = FID_conflict____acrt_CompareStringEx_36(param_2,param_3,(LPCWSTR)puVar4,iVar7,NULL,0x0,0x0,0x0,0x0), iVar5 != 0x0)) {
            if ((param_3 & 0x400) == 0x0) {
                uVar3 = iVar5 * 0x2 + 0x8;
                uVar3 = -(uint)((uint)(iVar5 * 0x2) < uVar3) & uVar3;
                if (uVar3 == 0x0) {
                    puVar6 = NULL;
                }
                else if (uVar3 < 0x401) {
                    puVar9 = (undefined4 *)&stack0xffffffe8;
                    puVar6 = (undefined4 *)&stack0xffffffe8;
                    if (&stack0x00000000 != (undefined *)0x18) {
LAB_100093cb:
                        puVar6 = puVar9 + 0x2;
                        if ((puVar6 != NULL) && (iVar7 = FID_conflict____acrt_CompareStringEx_36(param_2,param_3,(LPCWSTR)puVar4,iVar2,(LPWSTR)puVar6,iVar5,0x0,0x0,0x0), iVar7 != 0x0)) {
                            if (param_7 == 0x0) {
                                param_7 = 0x0;
                                param_6 = NULL;
                            }
                            iVar5 = ___acrt_WideCharToMultiByte(param_8,0x0,(LPCWSTR)puVar6,iVar5,(LPSTR)param_6,param_7,0x0,NULL);
                            if (iVar5 != 0x0) {
                                FUN_1000923d((int)puVar6);
                                goto LAB_10009430;
                            }
                        }
                    }
                }
                else {
                    puVar6 = (undefined4 *)__malloc_base(uVar3);
                    if (puVar6 != NULL) {
                        *puVar6 = 0xdddd;
                        puVar9 = puVar6;
                        goto LAB_100093cb;
                    }
                }
                FUN_1000923d((int)puVar6);
            }
            else if ((param_7 != 0x0) && (iVar5 <= param_7)) {
                FID_conflict____acrt_CompareStringEx_36(param_2,param_3,(LPCWSTR)puVar4,iVar7,param_6,param_7,0x0,0x0,0x0);
            }
        }
    }
LAB_10009430:
    FUN_1000923d((int)puVar4);
    uVar8 = extraout_DL_00;
LAB_10009439:
    FUN_10001f99(uVar1 ^ (uint)&stack0xfffffffc,uVar8,(char)iVar2);
    return;
}



// Library Function - Single Match
//  ___acrt_LCMapStringA
// 
// Library: Visual Studio 2019 Release

void __cdecl ___acrt_LCMapStringA(__acrt_ptd **param_1,ushort *param_2,uint param_3,char *param_4,int param_5,LPWSTR param_6,int param_7,uint param_8,int param_9)

{
    int local_14;
    int local_10 [0x2];
    char local_8;
    
    FUN_100065f3(&local_14,param_1);
    FUN_1000925d(local_10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    if (local_8 != '\0') {
        *(uint *)(local_14 + 0x350) = *(uint *)(local_14 + 0x350) & 0xfffffffd;
    }
    return;
}



// Library Function - Multiple Matches With Different Base Names
//  __msize
//  __msize_base
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

size_t __cdecl FID_conflict___msize_base(void *_Memory)

{
    undefined4 *puVar1;
    SIZE_T SVar2;
    
    if (_Memory == NULL) {
        puVar1 = (undefined4 *)FUN_10005ee9();
        *puVar1 = 0x16;
        FUN_10005e08();
        return 0xffffffff;
    }
    SVar2 = HeapSize(DAT_10016248,0x0,_Memory);
    return SVar2;
}



// Library Function - Single Match
//  __realloc_base
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

LPVOID __cdecl __realloc_base(LPVOID param_1,uint param_2)

{
    LPVOID pvVar1;
    undefined4 *puVar2;
    int iVar3;
    
    if (param_1 == NULL) {
        pvVar1 = __malloc_base(param_2);
    }
    else {
        if (param_2 == 0x0) {
            FUN_10005f59(param_1);
        }
        else {
            if (param_2 < 0xffffffe1) {
                do {
                    pvVar1 = HeapReAlloc(DAT_10016248,0x0,param_1,param_2);
                    if (pvVar1 != NULL) {
                        return pvVar1;
                    }
                    iVar3 = FUN_10008a8c();
                } while ((iVar3 != 0x0) && (iVar3 = __callnewh(param_2), iVar3 != 0x0));
            }
            puVar2 = (undefined4 *)FUN_10005ee9();
            *puVar2 = 0xc;
        }
        pvVar1 = NULL;
    }
    return pvVar1;
}



// Library Function - Multiple Matches With Different Base Names
//  int __cdecl GetTableIndexFromLocaleName(wchar_t const *)
//  int __cdecl ATL::_AtlGetTableIndexFromLocaleName(wchar_t const *)
//  _GetTableIndexFromLocaleName
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

undefined4 __cdecl FID_conflict_GetTableIndexFromLocaleName(ushort *param_1)

{
    int iVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    
    iVar4 = 0x0;
    iVar2 = 0xe3;
    do {
        iVar3 = (iVar2 + iVar4) / 0x2;
        iVar1 = FUN_1000a970(param_1,*(ushort **)(&UNK_10011090 + iVar3 * 0x8),0x55);
        if (iVar1 == 0x0) {
            return *(undefined4 *)(&UNK_10011094 + iVar3 * 0x8);
        }
        if (iVar1 < 0x0) {
            iVar2 = iVar3 + -0x1;
        }
        else {
            iVar4 = iVar3 + 0x1;
        }
    } while (iVar4 <= iVar2);
    return 0xffffffff;
}



// Library Function - Single Match
//  ___acrt_DownlevelLocaleNameToLCID
// 
// Library: Visual Studio 2019 Release

undefined4 __cdecl ___acrt_DownlevelLocaleNameToLCID(ushort *param_1)

{
    uint uVar1;
    
    if (param_1 != NULL) {
        uVar1 = FID_conflict_GetTableIndexFromLocaleName(param_1);
        if ((-0x1 < (int)uVar1) && (uVar1 < 0xe4)) {
            return *(undefined4 *)(&DAT_1000ff68 + uVar1 * 0x8);
        }
    }
    return 0x0;
}



// Library Function - Single Match
//  ___acrt_lowio_create_handle_array
// 
// Library: Visual Studio 2019 Release

undefined4 * ___acrt_lowio_create_handle_array(void)

{
    undefined4 *puVar1;
    undefined4 *puVar2;
    undefined4 *puVar3;
    
    puVar2 = (undefined4 *)__calloc_base(0x40,0x38);
    if (puVar2 == NULL) {
        puVar2 = NULL;
    }
    else if (puVar2 != puVar2 + 0x380) {
        puVar3 = puVar2 + 0x8;
        do {
            ___acrt_InitializeCriticalSectionEx_12((LPCRITICAL_SECTION)(puVar3 + -0x8),0xfa0,0x0);
            puVar3[-0x2] = 0xffffffff;
            *(byte *)((int)puVar3 + 0xd) = *(byte *)((int)puVar3 + 0xd) & 0xf8;
            *puVar3 = 0x0;
            puVar3[0x1] = 0x0;
            puVar1 = puVar3 + 0x6;
            puVar3[0x2] = 0xa0a0000;
            *(undefined *)(puVar3 + 0x3) = 0xa;
            *(undefined4 *)((int)puVar3 + 0xe) = 0x0;
            *(undefined *)((int)puVar3 + 0x12) = 0x0;
            puVar3 = puVar3 + 0xe;
        } while (puVar1 != puVar2 + 0x380);
    }
    FUN_10005f59(NULL);
    return puVar2;
}



// Library Function - Single Match
//  ___acrt_lowio_destroy_handle_array
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl ___acrt_lowio_destroy_handle_array(LPCRITICAL_SECTION param_1)

{
    LPCRITICAL_SECTION lpCriticalSection;
    
    if (param_1 != NULL) {
        lpCriticalSection = param_1;
        if (param_1 != (LPCRITICAL_SECTION)&param_1[0x95].RecursionCount) {
            do {
                DeleteCriticalSection(lpCriticalSection);
                lpCriticalSection = (LPCRITICAL_SECTION)&lpCriticalSection[0x2].RecursionCount;
            } while (lpCriticalSection != (LPCRITICAL_SECTION)&param_1[0x95].RecursionCount);
        }
        FUN_10005f59(param_1);
    }
    return;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4
// Library Function - Single Match
//  ___acrt_lowio_ensure_fh_exists
// 
// Library: Visual Studio 2019 Release

undefined4 __cdecl ___acrt_lowio_ensure_fh_exists(uint param_1)

{
    undefined4 *puVar1;
    int iVar2;
    undefined4 uVar3;
    int iVar4;
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    if (param_1 < 0x2000) {
        uVar3 = 0x0;
        ___acrt_lock(0x7);
        iVar4 = 0x0;
        iVar2 = DAT_10016450;
        while (iVar2 <= (int)param_1) {
            if ((&DAT_10016250)[iVar4] == 0x0) {
                puVar1 = ___acrt_lowio_create_handle_array();
                (&DAT_10016250)[iVar4] = puVar1;
                if (puVar1 == NULL) {
                    uVar3 = 0xc;
                    break;
                }
                iVar2 = DAT_10016450 + 0x40;
                DAT_10016450 = iVar2;
            }
            iVar4 = iVar4 + 0x1;
        }
        FUN_10009700();
    }
    else {
        puVar1 = (undefined4 *)FUN_10005ee9();
        uVar3 = 0x9;
        *puVar1 = 0x9;
        FUN_10005e08();
    }
    *in_FS_OFFSET = local_14;
    return uVar3;
}



void FUN_10009700(void)

{
    ___acrt_unlock(0x7);
    return;
}



void __cdecl FUN_10009709(uint param_1)

{
    EnterCriticalSection((LPCRITICAL_SECTION)((param_1 & 0x3f) * 0x38 + (&DAT_10016250)[(int)param_1 >> 0x6]));
    return;
}



// Library Function - Single Match
//  ___acrt_lowio_unlock_fh
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl ___acrt_lowio_unlock_fh(uint param_1)

{
    LeaveCriticalSection((LPCRITICAL_SECTION)((param_1 & 0x3f) * 0x38 + (&DAT_10016250)[(int)param_1 >> 0x6]));
    return;
}



undefined4 __cdecl FUN_1000974f(uint param_1)

{
    int iVar1;
    undefined4 *puVar2;
    int iVar3;
    DWORD nStdHandle;
    
    if ((-0x1 < (int)param_1) && (param_1 < DAT_10016450)) {
        iVar3 = (param_1 & 0x3f) * 0x38;
        if (((*(byte *)(iVar3 + 0x28 + (&DAT_10016250)[param_1 >> 0x6]) & 0x1) != 0x0) && (*(int *)(iVar3 + 0x18 + (&DAT_10016250)[param_1 >> 0x6]) != -0x1)) {
            iVar1 = FUN_1000a9bf();
            if (iVar1 == 0x1) {
                if (param_1 == 0x0) {
                    nStdHandle = 0xfffffff6;
                }
                else if (param_1 == 0x1) {
                    nStdHandle = 0xfffffff5;
                }
                else {
                    if (param_1 != 0x2) goto LAB_100097b5;
                    nStdHandle = 0xfffffff4;
                }
                SetStdHandle(nStdHandle,NULL);
            }
LAB_100097b5:
            *(undefined4 *)(iVar3 + 0x18 + (&DAT_10016250)[param_1 >> 0x6]) = 0xffffffff;
            return 0x0;
        }
    }
    puVar2 = (undefined4 *)FUN_10005ee9();
    *puVar2 = 0x9;
    puVar2 = (undefined4 *)FUN_10005ed6();
    *puVar2 = 0x0;
    return 0xffffffff;
}



undefined4 __cdecl FUN_100097e0(uint param_1)

{
    undefined4 *puVar1;
    int iVar2;
    
    if (param_1 == 0xfffffffe) {
        puVar1 = (undefined4 *)FUN_10005ed6();
        *puVar1 = 0x0;
        puVar1 = (undefined4 *)FUN_10005ee9();
        *puVar1 = 0x9;
    }
    else {
        if ((-0x1 < (int)param_1) && (param_1 < DAT_10016450)) {
            iVar2 = (param_1 & 0x3f) * 0x38;
            if ((*(byte *)((&DAT_10016250)[param_1 >> 0x6] + 0x28 + iVar2) & 0x1) != 0x0) {
                return *(undefined4 *)((&DAT_10016250)[param_1 >> 0x6] + 0x18 + iVar2);
            }
        }
        puVar1 = (undefined4 *)FUN_10005ed6();
        *puVar1 = 0x0;
        puVar1 = (undefined4 *)FUN_10005ee9();
        *puVar1 = 0x9;
        FUN_10005e08();
    }
    return 0xffffffff;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4

undefined4 FUN_1000984a(uint *param_1,uint **param_2)

{
    uint uVar1;
    HANDLE hFile;
    BOOL BVar2;
    DWORD DVar3;
    DWORD *pDVar4;
    undefined4 *puVar5;
    undefined4 uVar6;
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    uVar6 = 0x0;
    FUN_10009709(*param_1);
    uVar1 = **param_2;
    if ((*(byte *)((&DAT_10016250)[(int)uVar1 >> 0x6] + 0x28 + (uVar1 & 0x3f) * 0x38) & 0x1) != 0x0) {
        hFile = (HANDLE)FUN_100097e0(uVar1);
        BVar2 = FlushFileBuffers(hFile);
        if (BVar2 != 0x0) goto LAB_100098ba;
        DVar3 = GetLastError();
        pDVar4 = (DWORD *)FUN_10005ed6();
        *pDVar4 = DVar3;
    }
    puVar5 = (undefined4 *)FUN_10005ee9();
    *puVar5 = 0x9;
    uVar6 = 0xffffffff;
LAB_100098ba:
    FUN_100098e0();
    *in_FS_OFFSET = local_14;
    return uVar6;
}



void FUN_100098e0(void)

{
    int unaff_EBP;
    
    ___acrt_lowio_unlock_fh(**(uint **)(unaff_EBP + 0x10));
    return;
}



// Library Function - Single Match
//  __commit
// 
// Library: Visual Studio 2019 Release

int __cdecl __commit(int _FileHandle)

{
    undefined4 *puVar1;
    int iVar2;
    uint local_14;
    uint *local_10;
    int local_c;
    
    if (_FileHandle == -0x2) {
        puVar1 = (undefined4 *)FUN_10005ee9();
        *puVar1 = 0x9;
    }
    else {
        if (((-0x1 < _FileHandle) && ((uint)_FileHandle < DAT_10016450)) && ((*(byte *)((&DAT_10016250)[_FileHandle >> 0x6] + 0x28 + (_FileHandle & 0x3fU) * 0x38) & 0x1) != 0x0)) {
            local_10 = (uint *)&_FileHandle;
            local_c = _FileHandle;
            local_14 = _FileHandle;
            iVar2 = FUN_1000984a(&local_14,&local_10);
            return iVar2;
        }
        puVar1 = (undefined4 *)FUN_10005ee9();
        *puVar1 = 0x9;
        FUN_10005e08();
    }
    return -0x1;
}



void __cdecl FUN_10009969(DWORD *param_1,uint param_2,byte *param_3,int param_4,__acrt_ptd **param_5)

{
    byte *pbVar1;
    BOOL BVar2;
    DWORD DVar3;
    byte *pbVar4;
    int iVar5;
    undefined4 extraout_EDX;
    undefined4 extraout_EDX_00;
    undefined4 extraout_EDX_01;
    undefined4 extraout_EDX_02;
    undefined4 extraout_EDX_03;
    undefined4 extraout_EDX_04;
    int iVar6;
    int iVar7;
    int **in_FS_OFFSET;
    undefined8 uVar8;
    uint uVar9;
    undefined uVar10;
    undefined4 in_stack_ffffff7c;
    undefined4 local_7c;
    undefined4 local_78;
    UINT local_74;
    byte *local_70;
    int local_6c;
    HANDLE local_68;
    byte *local_64;
    byte *local_60;
    undefined2 local_5c [0x2];
    byte *local_58;
    int local_54;
    byte *local_50;
    byte *local_4c;
    int local_48;
    undefined4 local_44;
    __acrt_ptd **local_40;
    byte *local_3c;
    byte local_35;
    byte *local_34;
    uint local_30;
    CHAR local_2c [0x8];
    byte local_24;
    byte local_23;
    byte local_1c [0x8];
    uint local_14;
    int *local_10;
    undefined *puStack12;
    undefined4 uStack8;
    
    uStack8 = 0xffffffff;
    puStack12 = &LAB_1000d203;
    local_10 = *in_FS_OFFSET;
    local_14 = DAT_10015124 ^ (uint)&stack0xfffffffc;
    *in_FS_OFFSET = (int *)&local_10;
    local_48 = (param_2 & 0x3f) * 0x38;
    local_54 = (int)param_2 >> 0x6;
    local_64 = param_3;
    local_40 = param_5;
    local_68 = *(HANDLE *)((&DAT_10016250)[local_54] + 0x18 + local_48);
    local_58 = param_3 + param_4;
    local_74 = GetConsoleOutputCP();
    if (*(char *)(param_5 + 0x5) == '\0') {
        FUN_100053a0(param_5);
    }
    uVar8 = CONCAT44(local_64,local_3c);
    uVar10 = (undefined)in_stack_ffffff7c;
    local_6c = *(int *)(param_5[0x3] + 0x8);
    *param_1 = 0x0;
    param_1[0x1] = 0x0;
    param_1[0x2] = 0x0;
    local_34 = local_64;
    if (local_58 <= local_64) {
LAB_10009d1a:
        local_3c = (byte *)uVar8;
        *in_FS_OFFSET = local_10;
        FUN_10001f99(local_14 ^ (uint)&stack0xfffffffc,(char)((ulonglong)uVar8 >> 0x20),uVar10);
        return;
    }
    iVar6 = 0x0;
    local_4c = NULL;
    iVar7 = local_48;
LAB_10009a0e:
    uVar10 = (undefined)in_stack_ffffff7c;
    local_35 = *local_34;
    local_44 = 0x0;
    local_30 = 0x1;
    local_50 = (byte *)(&DAT_10016250)[local_54];
    if (local_6c == 0xfde9) {
        local_30 = 0x0;
        pbVar4 = local_50 + iVar7 + 0x2e;
        do {
            if (*pbVar4 == 0x0) break;
            local_30 = local_30 + 0x1;
            pbVar4 = pbVar4 + 0x1;
        } while ((int)local_30 < 0x5);
        iVar7 = (int)local_58 - (int)local_34;
        pbVar4 = local_34;
        if (local_30 == 0x0) {
            local_50 = (byte *)((char)(&DAT_10015860)[*local_34] + 0x1);
            if (iVar7 < (int)local_50) {
                if (0x0 < iVar7) {
                    do {
                        *(byte *)((&DAT_10016250)[local_54] + local_48 + 0x2e + iVar6) = local_34[iVar6];
                        iVar6 = iVar6 + 0x1;
                    } while (iVar6 < iVar7);
                }
                goto LAB_10009ccb;
            }
            in_stack_ffffff7c = 0x0;
            local_30 = (local_50 == (byte *)0x4) + 0x1;
            local_3c = local_34;
            iVar7 = FUN_1000a5dc(&stack0xffffff7c,(ushort *)&local_44,&local_3c,local_30,(byte **)&stack0xffffff7c,(int)local_40);
            uVar8 = CONCAT44(extraout_EDX_00,local_3c);
            uVar10 = (undefined)in_stack_ffffff7c;
            if (iVar7 == -0x1) goto LAB_10009d1a;
            local_34 = local_34 + (int)local_50;
            iVar7 = local_48;
        }
        else {
            local_50 = local_50 + local_48 + 0x2e;
            local_3c = (byte *)((int)(char)(&DAT_10015860)[*local_50] + 0x1);
            local_4c = local_3c + -local_30;
            if (iVar7 < (int)local_4c) {
                if (0x0 < iVar7) {
                    do {
                        pbVar1 = local_34 + iVar6;
                        pbVar4 = (byte *)((&DAT_10016250)[local_54] + local_48 + iVar6);
                        iVar6 = iVar6 + 0x1;
                        pbVar4[local_30 + 0x2e] = *pbVar1;
                    } while (iVar6 < iVar7);
                }
LAB_10009ccb:
                uVar8 = CONCAT44(pbVar4,local_3c);
                param_1[0x1] = param_1[0x1] + iVar7;
                goto LAB_10009d1a;
            }
            iVar7 = 0x0;
            pbVar4 = local_50;
            do {
                local_1c[iVar7] = *pbVar4;
                iVar7 = iVar7 + 0x1;
                pbVar4 = pbVar4 + 0x1;
            } while (iVar7 < (int)local_30);
            if (0x0 < (int)local_4c) {
                FID_conflict__memcpy(local_1c + local_30,local_34,(size_t)local_4c);
            }
            iVar7 = local_48;
            iVar5 = 0x0;
            do {
                *(undefined *)((&DAT_10016250)[local_54] + local_48 + 0x2e + iVar5) = 0x0;
                iVar5 = iVar5 + 0x1;
            } while (iVar5 < (int)local_30);
            local_70 = local_1c;
            local_7c = 0x0;
            local_78 = 0x0;
            local_30 = (local_3c == (byte *)0x4) + 0x1;
            iVar5 = FUN_1000a5dc(&local_7c,(ushort *)&local_44,&local_70,local_30,(byte **)&local_7c,(int)local_40);
            uVar8 = CONCAT44(extraout_EDX,local_3c);
            uVar10 = (undefined)in_stack_ffffff7c;
            if (iVar5 == -0x1) goto LAB_10009d1a;
            local_34 = local_34 + (int)local_4c;
        }
        pbVar4 = local_34 + -0x1;
    }
    else {
        if ((local_50[iVar7 + 0x2d] & 0x4) == 0x0) {
            if (*(short *)(*(int *)local_40[0x3] + (uint)*local_34 * 0x2) < 0x0) {
                local_3c = local_34 + 0x1;
                uVar8 = CONCAT44(local_34,local_3c);
                if (local_3c < local_58) {
                    uVar9 = FUN_100084f8((LPWSTR)&local_44,local_34,0x2,local_40);
                    uVar8 = CONCAT44(extraout_EDX_01,local_3c);
                    uVar10 = (undefined)in_stack_ffffff7c;
                    pbVar4 = local_3c;
                    if (uVar9 != 0xffffffff) goto LAB_10009bf0;
                }
                else {
                    local_50[iVar7 + 0x2e] = *local_34;
                    pbVar4 = (byte *)((&DAT_10016250)[local_54] + 0x2d + iVar7);
                    *pbVar4 = *pbVar4 | 0x4;
                    param_1[0x1] = (DWORD)(local_4c + 0x1);
                }
                goto LAB_10009d1a;
            }
            uVar9 = 0x1;
            pbVar4 = local_34;
        }
        else {
            local_24 = local_50[iVar7 + 0x2e];
            local_23 = *local_34;
            local_50[iVar7 + 0x2d] = local_50[iVar7 + 0x2d] & 0xfb;
            uVar9 = 0x2;
            pbVar4 = &local_24;
        }
        uVar9 = FUN_100084f8((LPWSTR)&local_44,pbVar4,uVar9,local_40);
        uVar8 = CONCAT44(extraout_EDX_02,local_3c);
        uVar10 = (undefined)in_stack_ffffff7c;
        pbVar4 = local_34;
        if (uVar9 == 0xffffffff) goto LAB_10009d1a;
    }
LAB_10009bf0:
    local_34 = pbVar4 + 0x1;
    uVar8 = ___acrt_WideCharToMultiByte(local_74,0x0,(LPCWSTR)&local_44,local_30,local_2c,0x5,0x0,NULL);
    local_3c = (byte *)uVar8;
    uVar10 = (undefined)in_stack_ffffff7c;
    if (local_3c == NULL) goto LAB_10009d1a;
    BVar2 = WriteFile(local_68,local_2c,(DWORD)local_3c,(LPDWORD)&local_60,NULL);
    uVar8 = CONCAT44(local_34,local_3c);
    uVar10 = (undefined)in_stack_ffffff7c;
    if (BVar2 == 0x0) {
LAB_10009d12:
        DVar3 = GetLastError();
        uVar8 = CONCAT44(extraout_EDX_04,local_3c);
        *param_1 = DVar3;
        goto LAB_10009d1a;
    }
    local_4c = local_34 + (param_1[0x2] - (int)local_64);
    param_1[0x1] = (DWORD)local_4c;
    if (local_60 < local_3c) goto LAB_10009d1a;
    if (local_35 == 0xa) {
        local_5c[0] = 0xd;
        BVar2 = WriteFile(local_68,local_5c,0x1,(LPDWORD)&local_60,NULL);
        uVar8 = CONCAT44(extraout_EDX_03,local_3c);
        uVar10 = (undefined)in_stack_ffffff7c;
        if (BVar2 == 0x0) goto LAB_10009d12;
        if (local_60 == NULL) goto LAB_10009d1a;
        param_1[0x2] = param_1[0x2] + 0x1;
        param_1[0x1] = param_1[0x1] + 0x1;
        local_4c = (byte *)param_1[0x1];
    }
    uVar8 = CONCAT44(local_34,local_3c);
    uVar10 = (undefined)in_stack_ffffff7c;
    if (local_58 <= local_34) goto LAB_10009d1a;
    goto LAB_10009a0e;
}



// Library Function - Single Match
//  struct `anonymous namespace'::write_result __cdecl write_double_translated_unicode_nolock(char const * const,unsigned int)
// 
// Library: Visual Studio 2019 Release

write_result __cdecl write_double_translated_unicode_nolock(char *param_1,uint param_2)

{
    wchar_t _WCh;
    wchar_t wVar1;
    wint_t wVar2;
    wchar_t *pwVar3;
    DWORD DVar4;
    int in_stack_0000000c;
    
    *(undefined4 *)param_1 = 0x0;
    *(undefined4 *)(param_1 + 0x4) = 0x0;
    *(undefined4 *)(param_1 + 0x8) = 0x0;
    pwVar3 = (wchar_t *)(in_stack_0000000c + param_2);
    if (param_2 < pwVar3) {
        do {
            _WCh = *(wchar_t *)param_2;
            wVar1 = __putwch_nolock(_WCh);
            if (wVar1 != _WCh) {
LAB_10009d94:
                DVar4 = GetLastError();
                *(DWORD *)param_1 = DVar4;
                break;
            }
            *(int *)(param_1 + 0x4) = *(int *)(param_1 + 0x4) + 0x2;
            if (_WCh == L'\n') {
                wVar2 = __putwch_nolock(L'\r');
                if (wVar2 != 0xd) goto LAB_10009d94;
                *(int *)(param_1 + 0x4) = *(int *)(param_1 + 0x4) + 0x1;
                *(int *)(param_1 + 0x8) = *(int *)(param_1 + 0x8) + 0x1;
            }
            param_2 = param_2 + 0x2;
        } while (param_2 < pwVar3);
    }
    return SUB41(param_1,0x0);
}



uint __cdecl FUN_10009da3(uint param_1,__acrt_ptd **param_2)

{
    byte bVar1;
    undefined3 extraout_var;
    uint uVar2;
    int iVar3;
    int iVar4;
    DWORD local_8;
    
    bVar1 = FUN_1000a50a(param_1);
    uVar2 = CONCAT31(extraout_var,bVar1);
    if (uVar2 != 0x0) {
        iVar4 = (int)param_1 >> 0x6;
        iVar3 = (param_1 & 0x3f) * 0x38;
        uVar2 = (&DAT_10016250)[iVar4];
        if (*(char *)(uVar2 + 0x28 + iVar3) < '\0') {
            if (*(char *)(param_2 + 0x5) == '\0') {
                FUN_100053a0(param_2);
            }
            if (((*(int *)(param_2[0x3] + 0xa8) != 0x0) || (uVar2 = (&DAT_10016250)[iVar4], *(char *)(uVar2 + 0x29 + iVar3) != '\0')) &&
               (uVar2 = GetConsoleMode(*(HANDLE *)((&DAT_10016250)[iVar4] + 0x18 + iVar3),&local_8), uVar2 != 0x0)) {
                return CONCAT31((int3)(uVar2 >> 0x8),0x1);
            }
        }
    }
    return uVar2 & 0xffffff00;
}



// WARNING: Function: __alloca_probe replaced with injection: alloca_probe
// WARNING: Type propagation algorithm not settling
// Library Function - Single Match
//  struct `anonymous namespace'::write_result __cdecl write_text_ansi_nolock(int,char const * const,unsigned int)
// 
// Library: Visual Studio 2019 Release

write_result __cdecl write_text_ansi_nolock(int param_1,char *param_2,uint param_3)

{
    char cVar1;
    char *hFile;
    write_result wVar2;
    BOOL BVar3;
    DWORD DVar4;
    char *pcVar5;
    char *extraout_EDX;
    char *extraout_EDX_00;
    char *pcVar6;
    char *pcVar7;
    int in_stack_00000010;
    char *local_140c;
    char local_1408 [0x1400];
    uint local_8;
    
    local_8 = DAT_10015124 ^ (uint)&stack0xfffffffc;
    hFile = *(char **)((&DAT_10016250)[(int)param_2 >> 0x6] + 0x18 + ((uint)param_2 & 0x3f) * 0x38);
    pcVar5 = (char *)(in_stack_00000010 + param_3);
    *(undefined4 *)param_1 = 0x0;
    *(undefined4 *)(param_1 + 0x4) = 0x0;
    *(undefined4 *)(param_1 + 0x8) = 0x0;
    pcVar6 = pcVar5;
    local_140c = hFile;
    if (pcVar5 <= param_3) {
LAB_10009eeb:
        wVar2 = (write_result)FUN_10001f99(local_8 ^ (uint)&stack0xfffffffc,(char)pcVar6,(char)pcVar5);
        return wVar2;
    }
    do {
        pcVar7 = local_1408;
        do {
            if (pcVar5 <= param_3) break;
            cVar1 = *(char *)param_3;
            param_3 = param_3 + 0x1;
            if (cVar1 == '\n') {
                *(int *)(param_1 + 0x8) = *(int *)(param_1 + 0x8) + 0x1;
                *pcVar7 = '\r';
                pcVar7 = pcVar7 + 0x1;
            }
            *pcVar7 = cVar1;
            pcVar7 = pcVar7 + 0x1;
        } while (pcVar7 < local_1408 + 0x13ff);
        BVar3 = WriteFile(hFile,local_1408,(DWORD)(pcVar7 + -(int)local_1408),(LPDWORD)&local_140c,NULL);
        if (BVar3 == 0x0) {
            DVar4 = GetLastError();
            *(DWORD *)param_1 = DVar4;
            pcVar6 = extraout_EDX_00;
            goto LAB_10009eeb;
        }
        *(int *)(param_1 + 0x4) = *(int *)(param_1 + 0x4) + (int)local_140c;
        pcVar6 = extraout_EDX;
        if ((local_140c < pcVar7 + -(int)local_1408) || (pcVar6 = pcVar5, pcVar5 <= param_3)) goto LAB_10009eeb;
    } while( true );
}



// WARNING: Function: __alloca_probe replaced with injection: alloca_probe
// Library Function - Single Match
//  struct `anonymous namespace'::write_result __cdecl write_text_utf16le_nolock(int,char const * const,unsigned int)
// 
// Library: Visual Studio 2019 Release

write_result __cdecl write_text_utf16le_nolock(int param_1,char *param_2,uint param_3)

{
    short sVar1;
    write_result wVar2;
    BOOL BVar3;
    DWORD DVar4;
    short *extraout_EDX;
    short *extraout_EDX_00;
    short *psVar5;
    short *psVar6;
    int in_stack_00000010;
    short *psVar7;
    uint local_1410;
    HANDLE local_140c;
    short local_1408 [0xa00];
    uint local_8;
    
    local_8 = DAT_10015124 ^ (uint)&stack0xfffffffc;
    local_140c = *(HANDLE *)((&DAT_10016250)[(int)param_2 >> 0x6] + 0x18 + ((uint)param_2 & 0x3f) * 0x38);
    *(undefined4 *)param_1 = 0x0;
    *(undefined4 *)(param_1 + 0x4) = 0x0;
    *(undefined4 *)(param_1 + 0x8) = 0x0;
    psVar7 = (short *)(in_stack_00000010 + param_3);
    do {
        psVar5 = psVar7;
        psVar7 = psVar5;
        if (psVar5 <= param_3) break;
        psVar6 = local_1408;
        do {
            if (psVar5 <= param_3) break;
            sVar1 = *(short *)param_3;
            param_3 = param_3 + 0x2;
            if (sVar1 == 0xa) {
                *(int *)(param_1 + 0x8) = *(int *)(param_1 + 0x8) + 0x2;
                *psVar6 = 0xd;
                psVar6 = psVar6 + 0x1;
            }
            *psVar6 = sVar1;
            psVar6 = psVar6 + 0x1;
        } while (psVar6 < local_1408 + 0x9ff);
        BVar3 = WriteFile(local_140c,local_1408,(int)psVar6 - (int)local_1408,&local_1410,NULL);
        if (BVar3 == 0x0) {
            DVar4 = GetLastError();
            *(DWORD *)param_1 = DVar4;
            psVar5 = extraout_EDX_00;
            break;
        }
        *(int *)(param_1 + 0x4) = *(int *)(param_1 + 0x4) + local_1410;
        psVar5 = extraout_EDX;
    } while ((uint)((int)psVar6 - (int)local_1408) <= local_1410);
    wVar2 = (write_result)FUN_10001f99(local_8 ^ (uint)&stack0xfffffffc,(char)psVar5,(char)psVar7);
    return wVar2;
}



// WARNING: Function: __alloca_probe replaced with injection: alloca_probe
// Library Function - Single Match
//  struct `anonymous namespace'::write_result __cdecl write_text_utf8_nolock(int,char const * const,unsigned int)
// 
// Library: Visual Studio 2019 Release

write_result __cdecl write_text_utf8_nolock(int param_1,char *param_2,uint param_3)

{
    WCHAR WVar1;
    write_result wVar2;
    WCHAR *pWVar3;
    BOOL BVar4;
    DWORD DVar5;
    undefined4 extraout_EDX;
    uint uVar6;
    uint extraout_EDX_00;
    uint uVar7;
    WCHAR *pWVar8;
    undefined8 uVar9;
    int in_stack_00000010;
    undefined in_stack_ffffebe4;
    DWORD local_1418;
    HANDLE local_1414;
    WCHAR *local_1410;
    CHAR local_140c [0xd58];
    WCHAR local_6b4 [0x356];
    uint local_8;
    
    local_8 = DAT_10015124 ^ (uint)&stack0xfffffffc;
    local_1414 = *(HANDLE *)((&DAT_10016250)[(int)param_2 >> 0x6] + 0x18 + ((uint)param_2 & 0x3f) * 0x38);
    local_1410 = (WCHAR *)(in_stack_00000010 + param_3);
    *(undefined4 *)param_1 = 0x0;
    *(undefined4 *)(param_1 + 0x4) = 0x0;
    *(undefined4 *)(param_1 + 0x8) = 0x0;
    uVar6 = param_3;
    pWVar8 = (WCHAR *)param_3;
    if (param_3 < local_1410) {
        do {
            pWVar3 = local_6b4;
            do {
                if (local_1410 <= pWVar8) break;
                WVar1 = *pWVar8;
                pWVar8 = pWVar8 + 0x1;
                if (WVar1 == L'\n') {
                    *pWVar3 = L'\r';
                    pWVar3 = pWVar3 + 0x1;
                }
                *pWVar3 = WVar1;
                pWVar3 = pWVar3 + 0x1;
            } while (pWVar3 < local_6b4 + 0x354);
            uVar9 = ___acrt_WideCharToMultiByte(0xfde9,0x0,local_6b4,(int)pWVar3 - (int)local_6b4 >> 0x1,local_140c,0xd55,0x0,NULL);
            uVar6 = (uint)uVar9;
            if (uVar6 == 0x0) {
LAB_1000a0fe:
                in_stack_ffffebe4 = (undefined)uVar6;
                DVar5 = GetLastError();
                *(DWORD *)param_1 = DVar5;
                uVar6 = extraout_EDX_00;
                break;
            }
            uVar7 = 0x0;
            if (uVar6 != 0x0) {
                do {
                    BVar4 = WriteFile(local_1414,local_140c + uVar7,uVar6 - uVar7,&local_1418,NULL);
                    uVar9 = CONCAT44(extraout_EDX,uVar6);
                    if (BVar4 == 0x0) goto LAB_1000a0fe;
                    uVar7 = uVar7 + local_1418;
                } while (uVar7 < uVar6);
            }
            uVar6 = (uint)((ulonglong)uVar9 >> 0x20);
            in_stack_ffffebe4 = (undefined)uVar9;
            *(uint *)(param_1 + 0x4) = (int)pWVar8 - param_3;
        } while (pWVar8 < local_1410);
    }
    wVar2 = (write_result)FUN_10001f99(local_8 ^ (uint)&stack0xfffffffc,(char)uVar6,in_stack_ffffebe4);
    return wVar2;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4

int __cdecl FUN_1000a117(char *param_1,byte *param_2,uint param_3,__acrt_ptd **param_4)

{
    int iVar1;
    int iVar2;
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    if (param_1 == (char *)0xfffffffe) {
        *(undefined *)(param_4 + 0x9) = 0x1;
        param_4[0x8] = NULL;
        *(undefined *)(param_4 + 0x7) = 0x1;
        param_4[0x6] = (__acrt_ptd *)0x9;
    }
    else {
        if ((-0x1 < (int)param_1) && (param_1 < DAT_10016450)) {
            iVar2 = ((uint)param_1 & 0x3f) * 0x38;
            if ((*(byte *)(iVar2 + 0x28 + (&DAT_10016250)[(uint)param_1 >> 0x6]) & 0x1) != 0x0) {
                FUN_10009709((uint)param_1);
                iVar1 = -0x1;
                if ((*(byte *)(iVar2 + 0x28 + (&DAT_10016250)[(uint)param_1 >> 0x6]) & 0x1) == 0x0) {
                    *(undefined *)(param_4 + 0x7) = 0x1;
                    param_4[0x6] = (__acrt_ptd *)0x9;
                    *(undefined *)(param_4 + 0x9) = 0x1;
                    param_4[0x8] = NULL;
                }
                else {
                    iVar1 = FUN_1000a21f(param_1,param_2,param_3,param_4);
                }
                FUN_1000a1df();
                goto LAB_1000a20f;
            }
        }
        *(undefined *)(param_4 + 0x9) = 0x1;
        param_4[0x8] = NULL;
        *(undefined *)(param_4 + 0x7) = 0x1;
        param_4[0x6] = (__acrt_ptd *)0x9;
        FUN_10005d8b(NULL,NULL,NULL,0x0,0x0,param_4);
    }
    iVar1 = -0x1;
LAB_1000a20f:
    *in_FS_OFFSET = local_14;
    return iVar1;
}



void FUN_1000a1df(void)

{
    uint unaff_ESI;
    
    ___acrt_lowio_unlock_fh(unaff_ESI);
    return;
}



int __cdecl FUN_1000a21f(char *param_1,byte *param_2,uint param_3,__acrt_ptd **param_4)

{
    write_result wVar1;
    undefined4 uVar2;
    undefined3 extraout_var;
    ulong *puVar3;
    undefined3 extraout_var_00;
    undefined3 extraout_var_01;
    undefined3 extraout_var_02;
    BOOL BVar4;
    DWORD local_30;
    DWORD local_2c;
    undefined4 uStack40;
    ulong local_24;
    ulong local_20;
    ulong local_1c;
    int local_18;
    int local_14;
    uint local_10;
    byte *local_c;
    char local_5;
    
    local_c = param_2;
    local_10 = param_3;
    if (param_3 == 0x0) {
        return 0x0;
    }
    if (param_2 == NULL) {
LAB_1000a248:
        *(undefined *)(param_4 + 0x9) = 0x1;
        param_4[0x8] = NULL;
        *(undefined *)(param_4 + 0x7) = 0x1;
        param_4[0x6] = (__acrt_ptd *)0x16;
        FUN_10005d8b(NULL,NULL,NULL,0x0,0x0,param_4);
        return -0x1;
    }
    local_14 = (int)param_1 >> 0x6;
    local_18 = ((uint)param_1 & 0x3f) * 0x38;
    local_5 = *(char *)(local_18 + 0x29 + (&DAT_10016250)[local_14]);
    if (((local_5 == '\x02') || (local_5 == '\x01')) && ((~param_3 & 0x1) == 0x0)) goto LAB_1000a248;
    if ((*(byte *)(local_18 + 0x28 + (&DAT_10016250)[local_14]) & 0x20) != 0x0) {
        FUN_1000aa48((uint)param_1,0x0,0x0,0x2,(int)param_4);
    }
    uVar2 = FUN_10009da3((uint)param_1,param_4);
    if ((char)uVar2 == '\0') {
        if (*(char *)(local_18 + 0x28 + (&DAT_10016250)[local_14]) < '\0') {
            if (local_5 == '\0') {
                wVar1 = write_text_ansi_nolock((int)&local_30,param_1,(uint)local_c);
                puVar3 = (ulong *)CONCAT31(extraout_var_02,wVar1);
            }
            else if (local_5 == '\x01') {
                wVar1 = write_text_utf8_nolock((int)&local_30,param_1,(uint)local_c);
                puVar3 = (ulong *)CONCAT31(extraout_var_01,wVar1);
            }
            else {
                if (local_5 != '\x02') goto LAB_1000a3e0;
                wVar1 = write_text_utf16le_nolock((int)&local_30,param_1,(uint)local_c);
                puVar3 = (ulong *)CONCAT31(extraout_var_00,wVar1);
            }
        }
        else {
            local_30 = 0x0;
            local_2c = 0x0;
            uStack40 = 0x0;
            BVar4 = WriteFile(*(HANDLE *)(local_18 + 0x18 + (&DAT_10016250)[local_14]),local_c,local_10,&local_2c,NULL);
            if (BVar4 == 0x0) {
                local_30 = GetLastError();
            }
            puVar3 = &local_30;
        }
    }
    else if (local_5 == '\0') {
        puVar3 = (ulong *)FUN_10009969(&local_30,(uint)param_1,local_c,local_10,param_4);
    }
    else {
        if (0x1 < (byte)(local_5 - 0x1U)) goto LAB_1000a3e0;
        wVar1 = write_double_translated_unicode_nolock((char *)&local_30,(uint)local_c);
        puVar3 = (ulong *)CONCAT31(extraout_var,wVar1);
    }
    local_24 = *puVar3;
    local_20 = puVar3[0x1];
    local_1c = puVar3[0x2];
    if (local_20 != 0x0) {
        return local_20 - local_1c;
    }
    if (local_24 != 0x0) {
        if (local_24 == 0x5) {
            *(undefined *)(param_4 + 0x7) = 0x1;
            param_4[0x6] = (__acrt_ptd *)0x9;
            *(undefined *)(param_4 + 0x9) = 0x1;
            param_4[0x8] = (__acrt_ptd *)0x5;
            return -0x1;
        }
        FUN_10005eb2(local_24,(int)param_4);
        return -0x1;
    }
LAB_1000a3e0:
    if (((*(byte *)(local_18 + 0x28 + (&DAT_10016250)[local_14]) & 0x40) != 0x0) && (*local_c == 0x1a)) {
        return 0x0;
    }
    *(undefined *)(param_4 + 0x7) = 0x1;
    param_4[0x6] = (__acrt_ptd *)0x1c;
    *(undefined *)(param_4 + 0x9) = 0x1;
    param_4[0x8] = NULL;
    return -0x1;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4

int FUN_1000a41f(void)

{
    int iVar1;
    int iVar2;
    undefined4 *in_FS_OFFSET;
    int local_20;
    undefined4 local_14;
    
    local_20 = 0x0;
    ___acrt_lock(0x8);
    for (iVar2 = 0x3; iVar2 != DAT_10016470; iVar2 = iVar2 + 0x1) {
        iVar1 = *(int *)(DAT_10016474 + iVar2 * 0x4);
        if (iVar1 != 0x0) {
            if ((*(uint *)(iVar1 + 0xc) >> 0xd & 0x1) != 0x0) {
                iVar1 = FUN_1000abbd(*(FILE **)(DAT_10016474 + iVar2 * 0x4));
                if (iVar1 != -0x1) {
                    local_20 = local_20 + 0x1;
                }
            }
            DeleteCriticalSection((LPCRITICAL_SECTION)(*(int *)(DAT_10016474 + iVar2 * 0x4) + 0x20));
            FUN_10005f59(*(LPVOID *)(DAT_10016474 + iVar2 * 0x4));
            *(undefined4 *)(DAT_10016474 + iVar2 * 0x4) = 0x0;
        }
    }
    FUN_1000a4c1();
    *in_FS_OFFSET = local_14;
    return local_20;
}



void FUN_1000a4c1(void)

{
    ___acrt_unlock(0x8);
    return;
}



// Library Function - Single Match
//  ___acrt_stdio_free_buffer_nolock
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl ___acrt_stdio_free_buffer_nolock(undefined4 *param_1)

{
    uint *puVar1;
    
    puVar1 = param_1 + 0x3;
    if (((*puVar1 >> 0xd & 0x1) != 0x0) && ((*puVar1 >> 0x6 & 0x1) != 0x0)) {
        FUN_10005f59((LPVOID)param_1[0x1]);
        LOCK();
        *puVar1 = *puVar1 & 0xfffffebf;
        param_1[0x1] = 0x0;
        *param_1 = 0x0;
        param_1[0x2] = 0x0;
    }
    return;
}



byte __cdecl FUN_1000a50a(uint param_1)

{
    undefined4 *puVar1;
    
    if (param_1 == 0xfffffffe) {
        puVar1 = (undefined4 *)FUN_10005ee9();
        *puVar1 = 0x9;
    }
    else {
        if ((-0x1 < (int)param_1) && (param_1 < DAT_10016450)) {
            return *(byte *)((&DAT_10016250)[param_1 >> 0x6] + 0x28 + (param_1 & 0x3f) * 0x38) & 0x40;
        }
        puVar1 = (undefined4 *)FUN_10005ee9();
        *puVar1 = 0x9;
        FUN_10005e08();
    }
    return 0x0;
}



// Library Function - Single Match
//  _fegetround
// 
// Library: Visual Studio 2019 Release

void _fegetround(void)

{
    uint uVar1;
    
    uVar1 = ___acrt_fenv_get_control();
    ___acrt_fenv_get_common_round_control(uVar1);
    return;
}



char FUN_1000a56d(char *param_1)

{
    char cVar1;
    
    if (*param_1 == '\0') {
        cVar1 = '\x01';
    }
    else if (param_1[0x1] == '\0') {
        cVar1 = '\x02';
    }
    else {
        cVar1 = (param_1[0x2] != '\0') + '\x03';
    }
    return cVar1;
}



uint __cdecl FUN_1000a599(undefined2 *param_1,byte *param_2,uint param_3,byte **param_4,int param_5)

{
    uint uVar1;
    uint local_8;
    
    uVar1 = FUN_1000b052((uint)&local_8,param_2,param_3,param_4,param_5);
    if (uVar1 < 0x5) {
        if (0xffff < local_8) {
            local_8 = 0xfffd;
        }
        if (param_1 != NULL) {
            *param_1 = (short)local_8;
        }
    }
    return uVar1;
}



int __thiscall FUN_1000a5dc(void *this,ushort *param_1,byte **param_2,uint param_3,byte **param_4,int param_5)

{
    char cVar1;
    undefined3 extraout_var;
    int iVar2;
    uint uVar3;
    undefined3 extraout_var_01;
    void *pvVar4;
    ushort *puVar5;
    int iVar6;
    byte *pbVar7;
    void *local_c;
    void *pvStack8;
    undefined3 extraout_var_00;
    
    pbVar7 = *param_2;
    local_c = this;
    pvStack8 = this;
    if (param_1 == NULL) {
        iVar2 = 0x0;
        cVar1 = FUN_1000a56d((char *)pbVar7);
        uVar3 = CONCAT31(extraout_var_00,cVar1);
        while (iVar6 = FUN_1000b052(0x0,pbVar7,uVar3,param_4,param_5), iVar6 != -0x1) {
            if (iVar6 == 0x0) {
                return iVar2;
            }
            if (iVar6 == 0x4) {
                iVar2 = iVar2 + 0x1;
            }
            pbVar7 = pbVar7 + iVar6;
            iVar2 = iVar2 + 0x1;
            cVar1 = FUN_1000a56d((char *)pbVar7);
            uVar3 = CONCAT31(extraout_var_01,cVar1);
        }
        *(undefined *)(param_5 + 0x1c) = 0x1;
        *(undefined4 *)(param_5 + 0x18) = 0x2a;
    }
    else {
        puVar5 = param_1;
        if (param_3 != 0x0) {
            do {
                cVar1 = FUN_1000a56d((char *)pbVar7);
                iVar2 = FUN_1000b052((uint)&local_c,pbVar7,CONCAT31(extraout_var,cVar1),param_4,param_5);
                if (iVar2 == -0x1) {
                    *param_2 = pbVar7;
                    *(undefined *)(param_5 + 0x1c) = 0x1;
                    *(undefined4 *)(param_5 + 0x18) = 0x2a;
                    return -0x1;
                }
                if (iVar2 == 0x0) {
                    pbVar7 = NULL;
                    *puVar5 = 0x0;
                    break;
                }
                pvVar4 = local_c;
                if ((void *)0xffff < local_c) {
                    if (param_3 < 0x2) break;
                    local_c = (void *)((int)local_c + -0x10000);
                    param_3 = param_3 - 0x1;
                    *puVar5 = (ushort)((uint)local_c >> 0xa) | 0xd800;
                    puVar5 = puVar5 + 0x1;
                    pvVar4 = (void *)((uint)local_c & 0x3ff | 0xdc00);
                }
                *puVar5 = (ushort)pvVar4;
                pbVar7 = pbVar7 + iVar2;
                puVar5 = puVar5 + 0x1;
                param_3 = param_3 - 0x1;
            } while (param_3 != 0x0);
        }
        iVar6 = (int)puVar5 - (int)param_1 >> 0x1;
        *param_2 = pbVar7;
    }
    return iVar6;
}



// Library Function - Single Match
//  ___acrt_locale_free_monetary
// 
// Library: Visual Studio 2019 Release

void __cdecl ___acrt_locale_free_monetary(int param_1)

{
    if (param_1 != 0x0) {
        if (*(undefined **)(param_1 + 0xc) != PTR_DAT_10015814) {
            FUN_10005f59(*(undefined **)(param_1 + 0xc));
        }
        if (*(undefined **)(param_1 + 0x10) != PTR_DAT_10015818) {
            FUN_10005f59(*(undefined **)(param_1 + 0x10));
        }
        if (*(undefined **)(param_1 + 0x14) != PTR_DAT_1001581c) {
            FUN_10005f59(*(undefined **)(param_1 + 0x14));
        }
        if (*(undefined **)(param_1 + 0x18) != PTR_DAT_10015820) {
            FUN_10005f59(*(undefined **)(param_1 + 0x18));
        }
        if (*(undefined **)(param_1 + 0x1c) != PTR_DAT_10015824) {
            FUN_10005f59(*(undefined **)(param_1 + 0x1c));
        }
        if (*(undefined **)(param_1 + 0x20) != PTR_DAT_10015828) {
            FUN_10005f59(*(undefined **)(param_1 + 0x20));
        }
        if (*(undefined **)(param_1 + 0x24) != PTR_DAT_1001582c) {
            FUN_10005f59(*(undefined **)(param_1 + 0x24));
        }
        if (*(undefined **)(param_1 + 0x38) != PTR_DAT_10015840) {
            FUN_10005f59(*(undefined **)(param_1 + 0x38));
        }
        if (*(undefined **)(param_1 + 0x3c) != PTR_DAT_10015844) {
            FUN_10005f59(*(undefined **)(param_1 + 0x3c));
        }
        if (*(undefined **)(param_1 + 0x40) != PTR_DAT_10015848) {
            FUN_10005f59(*(undefined **)(param_1 + 0x40));
        }
        if (*(undefined **)(param_1 + 0x44) != PTR_DAT_1001584c) {
            FUN_10005f59(*(undefined **)(param_1 + 0x44));
        }
        if (*(undefined **)(param_1 + 0x48) != PTR_DAT_10015850) {
            FUN_10005f59(*(undefined **)(param_1 + 0x48));
        }
        if (*(undefined **)(param_1 + 0x4c) != PTR_DAT_10015854) {
            FUN_10005f59(*(undefined **)(param_1 + 0x4c));
        }
    }
    return;
}



// Library Function - Single Match
//  ___acrt_locale_free_numeric
// 
// Library: Visual Studio 2019 Release

void __cdecl ___acrt_locale_free_numeric(int *param_1)

{
    if (param_1 != NULL) {
        if ((undefined *)*param_1 != PTR_DAT_10015808) {
            FUN_10005f59((undefined *)*param_1);
        }
        if ((undefined *)param_1[0x1] != PTR_DAT_1001580c) {
            FUN_10005f59((undefined *)param_1[0x1]);
        }
        if ((undefined *)param_1[0x2] != PTR_DAT_10015810) {
            FUN_10005f59((undefined *)param_1[0x2]);
        }
        if ((undefined *)param_1[0xc] != PTR_DAT_10015838) {
            FUN_10005f59((undefined *)param_1[0xc]);
        }
        if ((undefined *)param_1[0xd] != PTR_DAT_1001583c) {
            FUN_10005f59((undefined *)param_1[0xd]);
        }
    }
    return;
}



void __cdecl FUN_1000a84b(undefined4 *param_1,int param_2)

{
    LPVOID *ppvVar1;
    
    ppvVar1 = (LPVOID *)(param_1 + param_2);
    for (; (LPVOID *)param_1 != ppvVar1; param_1 = (LPVOID *)param_1 + 0x1) {
        FUN_10005f59((LPVOID)*param_1);
    }
    return;
}



// Library Function - Single Match
//  ___acrt_locale_free_time
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl ___acrt_locale_free_time(undefined4 *param_1)

{
    if (param_1 != NULL) {
        FUN_1000a84b(param_1,0x7);
        FUN_1000a84b(param_1 + 0x7,0x7);
        FUN_1000a84b(param_1 + 0xe,0xc);
        FUN_1000a84b(param_1 + 0x1a,0xc);
        FUN_1000a84b(param_1 + 0x26,0x2);
        FUN_10005f59((LPVOID)param_1[0x28]);
        FUN_10005f59((LPVOID)param_1[0x29]);
        FUN_10005f59((LPVOID)param_1[0x2a]);
        FUN_1000a84b(param_1 + 0x2d,0x7);
        FUN_1000a84b(param_1 + 0x34,0x7);
        FUN_1000a84b(param_1 + 0x3b,0xc);
        FUN_1000a84b(param_1 + 0x47,0xc);
        FUN_1000a84b(param_1 + 0x53,0x2);
        FUN_10005f59((LPVOID)param_1[0x55]);
        FUN_10005f59((LPVOID)param_1[0x56]);
        FUN_10005f59((LPVOID)param_1[0x57]);
        FUN_10005f59((LPVOID)param_1[0x58]);
    }
    return;
}



// Library Function - Single Match
//  ___strncnt
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl ___strncnt(char *param_1,int param_2)

{
    char cVar1;
    int iVar2;
    
    iVar2 = 0x0;
    cVar1 = *param_1;
    while ((cVar1 != '\0' && (iVar2 != param_2))) {
        iVar2 = iVar2 + 0x1;
        cVar1 = param_1[iVar2];
    }
    return;
}



int __cdecl FUN_1000a970(ushort *param_1,ushort *param_2,int param_3)

{
    uint uVar1;
    uint uVar2;
    
    if (param_3 != 0x0) {
        do {
            uVar1 = (uint)*param_1;
            param_1 = param_1 + 0x1;
            if (uVar1 - 0x41 < 0x1a) {
                uVar1 = uVar1 + 0x20;
            }
            uVar2 = (uint)*param_2;
            param_2 = param_2 + 0x1;
            if (uVar2 - 0x41 < 0x1a) {
                uVar2 = uVar2 + 0x20;
            }
        } while (((uVar1 - uVar2 == 0x0) && (uVar1 != 0x0)) && (param_3 = param_3 + -0x1, param_3 != 0x0));
        return uVar1 - uVar2;
    }
    return 0x0;
}



undefined4 FUN_1000a9bf(void)

{
    return DAT_10016498;
}



undefined8 __cdecl FUN_1000a9c5(uint param_1,undefined4 param_2,undefined4 param_3,DWORD param_4,int param_5)

{
    byte *pbVar1;
    HANDLE hFile;
    BOOL BVar2;
    DWORD DVar3;
    uint local_c;
    uint local_8;
    
    hFile = (HANDLE)FUN_100097e0(param_1);
    if (hFile == (HANDLE)0xffffffff) {
        *(undefined *)(param_5 + 0x1c) = 0x1;
        *(undefined4 *)(param_5 + 0x18) = 0x9;
    }
    else {
        BVar2 = SetFilePointerEx(hFile,CONCAT44(param_3,param_2),(PLARGE_INTEGER)&local_c,param_4);
        if (BVar2 == 0x0) {
            DVar3 = GetLastError();
            FUN_10005eb2(DVar3,param_5);
        }
        else if ((local_c & local_8) != 0xffffffff) {
            pbVar1 = (byte *)((&DAT_10016250)[(int)param_1 >> 0x6] + 0x28 + (param_1 & 0x3f) * 0x38);
            *pbVar1 = *pbVar1 & 0xfd;
            goto LAB_1000aa44;
        }
    }
    local_c = 0xffffffff;
    local_8 = 0xffffffff;
LAB_1000aa44:
    return CONCAT44(local_8,local_c);
}



undefined8 __cdecl FUN_1000aa48(uint param_1,undefined4 param_2,undefined4 param_3,DWORD param_4,int param_5)

{
    undefined8 uVar1;
    
    uVar1 = FUN_1000a9c5(param_1,param_2,param_3,param_4,param_5);
    return uVar1;
}



// Library Function - Single Match
//  __putwch_nolock
// 
// Library: Visual Studio 2019 Release

wint_t __cdecl __putwch_nolock(wchar_t _WCh)

{
    bool bVar1;
    undefined3 extraout_var;
    BOOL BVar2;
    DWORD local_8;
    
    bVar1 = ___dcrt_lowio_ensure_console_output_initialized();
    if (CONCAT31(extraout_var,bVar1) != 0x0) {
        BVar2 = ___dcrt_write_console(&_WCh,0x1,&local_8);
        if (BVar2 != 0x0) {
            return _WCh;
        }
    }
    return 0xffff;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4

undefined4 __cdecl FUN_1000aa98(FILE *param_1,__acrt_ptd **param_2)

{
    undefined4 uVar1;
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    if (param_1 == NULL) {
        *(undefined *)(param_2 + 0x7) = 0x1;
        param_2[0x6] = (__acrt_ptd *)0x16;
        FUN_10005d8b(NULL,NULL,NULL,0x0,0x0,param_2);
    }
    else {
        if (((uint)param_1->_flag >> 0xc & 0x1) == 0x0) {
            FUN_100083c6((int)param_1);
            uVar1 = FUN_1000ab2f(param_1,param_2);
            FUN_1000ab27();
            goto LAB_1000ab11;
        }
        __acrt_stdio_free_stream(SUB41(param_1,0x0));
    }
    uVar1 = 0xffffffff;
LAB_1000ab11:
    *in_FS_OFFSET = local_14;
    return uVar1;
}



void FUN_1000ab27(void)

{
    FILE *unaff_ESI;
    
    __unlock_file(unaff_ESI);
    return;
}



undefined4 __cdecl FUN_1000ab2f(FILE *param_1,__acrt_ptd **param_2)

{
    undefined4 uVar1;
    uint uVar2;
    int iVar3;
    
    if (param_1 == NULL) {
        *(undefined *)(param_2 + 0x7) = 0x1;
        param_2[0x6] = (__acrt_ptd *)0x16;
        FUN_10005d8b(NULL,NULL,NULL,0x0,0x0,param_2);
        uVar1 = 0xffffffff;
    }
    else {
        uVar1 = 0xffffffff;
        if (((uint)param_1->_flag >> 0xd & 0x1) != 0x0) {
            uVar1 = FUN_100081db(param_1,param_2);
            ___acrt_stdio_free_buffer_nolock(&param_1->_ptr);
            uVar2 = __fileno(param_1);
            iVar3 = FUN_1000b3ac(uVar2,param_2);
            if (iVar3 < 0x0) {
                uVar1 = 0xffffffff;
            }
            else if (param_1->_tmpfname != NULL) {
                FUN_10005f59(param_1->_tmpfname);
                param_1->_tmpfname = NULL;
            }
        }
        __acrt_stdio_free_stream(SUB41(param_1,0x0));
    }
    return uVar1;
}



undefined4 __cdecl FUN_1000abbd(FILE *param_1)

{
    undefined4 uVar1;
    __acrt_ptd *local_2c [0xa];
    
    FUN_10005250(local_2c,NULL);
    uVar1 = FUN_1000aa98(param_1,local_2c);
    FUN_100052b0(local_2c);
    return uVar1;
}



uint __cdecl FUN_1000ae1d(uint param_1)

{
    ushort uVar1;
    uint uVar2;
    uint uVar3;
    uint uVar4;
    
    uVar4 = 0x0;
    uVar1 = (ushort)param_1 & 0x8040;
    if (uVar1 == 0x8000) {
        uVar3 = 0xc00;
    }
    else if (uVar1 == 0x40) {
        uVar3 = 0x800;
    }
    else {
        uVar3 = 0x400;
        if (uVar1 != 0x8040) {
            uVar3 = 0x0;
        }
    }
    uVar2 = param_1 & 0x6000;
    if (uVar2 != 0x0) {
        if (uVar2 == 0x2000) {
            uVar4 = 0x100;
        }
        else if (uVar2 == 0x4000) {
            uVar4 = 0x200;
        }
        else if (uVar2 == 0x6000) {
            uVar4 = 0x300;
        }
    }
    return (((param_1 & 0x400 | (param_1 >> 0x2 & 0x400 | param_1 & 0x800) >> 0x2) >> 0x2 | param_1 & 0x200) >> 0x3 | param_1 & 0x180) >> 0x3 | uVar3 | uVar4;
}



uint __cdecl FUN_1000aecd(uint param_1)

{
    uint uVar1;
    uint uVar2;
    uint local_8;
    
    local_8 = 0x1000;
    uVar2 = 0x0;
    if ((param_1 & 0x300) == 0x0) {
        local_8 = 0x2000;
    }
    else if ((param_1 & 0x300) != 0x200) {
        local_8 = 0x0;
    }
    uVar1 = param_1 & 0xc00;
    if (uVar1 != 0x0) {
        if (uVar1 == 0x400) {
            uVar2 = 0x100;
        }
        else if (uVar1 == 0x800) {
            uVar2 = 0x200;
        }
        else if (uVar1 == 0xc00) {
            uVar2 = 0x300;
        }
    }
    return (param_1 & 0x4 | (param_1 & 0x2) << 0x3) * 0x2 | ((param_1 >> 0x2 & 0x8 | param_1 & 0x10) >> 0x2 | param_1 & 0x8) >> 0x1 | (param_1 & 0x1) << 0x4 | (param_1 & 0x1000) << 0x2 | local_8 |
           uVar2;
}



// Library Function - Single Match
//  ___acrt_fenv_get_common_round_control
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

uint __cdecl ___acrt_fenv_get_common_round_control(uint param_1)

{
    uint uVar1;
    
    uVar1 = param_1 >> 0xe & 0x300;
    if (uVar1 != (param_1 >> 0x16 & 0x300)) {
        uVar1 = 0xffffffff;
    }
    return uVar1;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// Library Function - Single Match
//  ___acrt_fenv_get_control
// 
// Library: Visual Studio 2019 Release

uint ___acrt_fenv_get_control(void)

{
    uint uVar1;
    uint uVar2;
    int iVar3;
    uint *puVar4;
    uint in_MXCSR;
    ushort in_FPUControlWord;
    uint local_24 [0x8];
    
    puVar4 = local_24;
    for (iVar3 = 0x7; iVar3 != 0x0; iVar3 = iVar3 + -0x1) {
        *puVar4 = 0x0;
        puVar4 = puVar4 + 0x1;
    }
    local_24[0] = local_24[0] & 0xffff0000 | (uint)in_FPUControlWord;
    uVar1 = FUN_1000aecd(in_FPUControlWord & 0x1f3f);
    if (_DAT_10015adc < 0x1) {
        in_MXCSR = 0x0;
    }
    else {
        in_MXCSR = in_MXCSR & 0xffc0;
    }
    uVar2 = FUN_1000ae1d(in_MXCSR);
    return uVar2 | ((((uVar2 & 0x3f) << 0x2 | uVar2 & 0xffffff00) << 0x6 | uVar1 & 0x3f) << 0x2 | uVar1 & 0x300) << 0xe | uVar1;
}



undefined4 __cdecl FUN_1000b01c(undefined4 param_1,undefined4 *param_2)

{
    *param_2 = 0x0;
    param_2[0x1] = 0x0;
    return param_1;
}



undefined4 __cdecl FUN_1000b030(undefined4 *param_1,int param_2)

{
    *param_1 = 0x0;
    param_1[0x1] = 0x0;
    *(undefined *)(param_2 + 0x1c) = 0x1;
    *(undefined4 *)(param_2 + 0x18) = 0x2a;
    return 0xffffffff;
}



void __cdecl FUN_1000b052(uint param_1,byte *param_2,uint param_3,byte **param_4,int param_5)

{
    byte bVar1;
    uint uVar2;
    byte bVar3;
    undefined uVar4;
    undefined extraout_DL;
    undefined extraout_DL_00;
    uint uVar6;
    uint uVar7;
    byte **ppbVar8;
    byte *local_1c;
    byte local_15;
    undefined4 local_14;
    undefined4 local_10;
    undefined4 local_c;
    uint local_8;
    byte *pbVar5;
    
    local_8 = DAT_10015124 ^ (uint)&stack0xfffffffc;
    if (param_4 == NULL) {
        param_4 = (byte **)&DAT_1001649c;
    }
    pbVar5 = (byte *)0x1;
    uVar4 = 0x1;
    if (param_2 == NULL) {
        ppbVar8 = NULL;
        local_1c = &DAT_1000e59a;
        param_3 = 0x1;
LAB_1000b09b:
        if (*(short *)((int)param_4 + 0x6) == 0x0) {
            bVar1 = *local_1c;
            local_1c = local_1c + 0x1;
            if (-0x1 < (char)bVar1) {
                if (ppbVar8 != NULL) {
                    *ppbVar8 = (byte *)(uint)bVar1;
                }
                goto LAB_1000b201;
            }
            if ((bVar1 & 0xe0) == 0xc0) {
                uVar6 = (uint)CONCAT11(0x2,bVar1);
            }
            else if ((bVar1 & 0xf0) == 0xe0) {
                uVar6 = (uint)CONCAT11(0x3,bVar1);
            }
            else {
                if ((bVar1 & 0xf8) != 0xf0) goto LAB_1000b1f6;
                uVar6 = (uint)CONCAT11(0x4,bVar1);
            }
            bVar3 = (byte)(uVar6 >> 0x8);
            local_15 = bVar3;
            pbVar5 = (byte *)((0x1 << (0x7 - bVar3 & 0x1f)) - 0x1U & uVar6 & 0xff);
LAB_1000b140:
            uVar2 = (uint)bVar3;
            if (uVar2 < param_3) {
                param_3 = uVar2;
            }
            uVar7 = (int)local_1c - (int)param_2;
            while (uVar7 < param_3) {
                bVar1 = *local_1c;
                uVar6 = uVar6 & 0xffffff00;
                uVar7 = uVar7 + 0x1;
                local_1c = local_1c + 0x1;
                if ((bVar1 & 0xc0) != 0x80) goto LAB_1000b1f6;
                pbVar5 = (byte *)((int)pbVar5 << 0x6 | bVar1 & 0x3f);
            }
            if (param_3 < uVar2) {
                *(short *)(param_4 + 0x1) = (short)(uVar6 >> 0x8);
                *param_4 = pbVar5;
                *(ushort *)((int)param_4 + 0x6) = (ushort)(byte)(bVar3 - (char)param_3);
                goto LAB_1000b0d6;
            }
            if (((pbVar5 < (byte *)0xd800) || ((byte *)0xdfff < pbVar5)) && (pbVar5 < (byte *)0x110000)) {
                local_14 = 0x80;
                local_10 = 0x800;
                local_c = 0x10000;
                if ((&local_1c)[uVar6 >> 0x8] <= pbVar5) {
                    if (ppbVar8 != NULL) {
                        *ppbVar8 = pbVar5;
                    }
                    FUN_1000b01c(-(uint)(pbVar5 != NULL) & uVar2,param_4);
                    uVar4 = extraout_DL;
                    goto LAB_1000b201;
                }
            }
        }
        else {
            bVar1 = *(byte *)(param_4 + 0x1);
            uVar6 = (uint)bVar1 << 0x8;
            pbVar5 = *param_4;
            bVar3 = *(byte *)((int)param_4 + 0x6);
            if ((((byte)(bVar1 - 0x2) < 0x3) && (bVar3 != 0x0)) && (bVar3 < bVar1)) goto LAB_1000b140;
        }
LAB_1000b1f6:
        FUN_1000b030(param_4,param_5);
        uVar4 = extraout_DL_00;
    }
    else {
        local_1c = param_2;
        ppbVar8 = (byte **)(-(uint)(param_2 != NULL) & param_1);
        if (param_3 != 0x0) goto LAB_1000b09b;
LAB_1000b0d6:
        uVar4 = SUB41(pbVar5,0x0);
    }
LAB_1000b201:
    FUN_10001f99(local_8 ^ (uint)&stack0xfffffffc,uVar4,(char)ppbVar8);
    return;
}



// Library Function - Single Match
//  ___ascii_strnicmp
// 
// Library: Visual Studio

int __cdecl ___ascii_strnicmp(char *_Str1,char *_Str2,size_t _MaxCount)

{
    byte bVar1;
    byte bVar2;
    bool bVar3;
    
    if (_MaxCount != 0x0) {
        do {
            bVar2 = *_Str1;
            bVar1 = *_Str2;
            if ((bVar2 == 0x0) || (bVar1 == 0x0)) break;
            _Str1 = (char *)((byte *)_Str1 + 0x1);
            _Str2 = (char *)((byte *)_Str2 + 0x1);
            if ((0x40 < bVar2) && (bVar2 < 0x5b)) {
                bVar2 = bVar2 + 0x20;
            }
            if ((0x40 < bVar1) && (bVar1 < 0x5b)) {
                bVar1 = bVar1 + 0x20;
            }
            bVar3 = bVar2 < bVar1;
            if (bVar2 != bVar1) goto LAB_1000b261;
            _MaxCount = _MaxCount - 0x1;
        } while (_MaxCount != 0x0);
        _MaxCount = 0x0;
        bVar3 = bVar2 < bVar1;
        if (bVar2 != bVar1) {
LAB_1000b261:
            _MaxCount = 0xffffffff;
            if (!bVar3) {
                _MaxCount = 0x1;
            }
        }
    }
    return _MaxCount;
}



// Library Function - Single Match
//  void __cdecl __dcrt_lowio_initialize_console_output(void)
// 
// Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual Studio 2019 Release

void __cdecl __dcrt_lowio_initialize_console_output(void)

{
    DAT_10015960 = CreateFileW(L"CONOUT$",0x40000000,0x3,NULL,0x3,0x0,NULL);
    return;
}



// Library Function - Single Match
//  ___dcrt_lowio_ensure_console_output_initialized
// 
// Libraries: Visual Studio 2019 Debug, Visual Studio 2019 Release

bool ___dcrt_lowio_ensure_console_output_initialized(void)

{
    if (DAT_10015960 == -0x2) {
        __dcrt_lowio_initialize_console_output();
    }
    return DAT_10015960 != -0x1;
}



// Library Function - Multiple Matches With Different Base Names
//  ___dcrt_terminate_console_input
//  ___dcrt_terminate_console_output
// 
// Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release, Visual Studio 2019 Debug, Visual Studio 2019 Release

void FID_conflict____dcrt_terminate_console_output(void)

{
    if ((DAT_10015960 != (HANDLE)0xffffffff) && (DAT_10015960 != (HANDLE)0xfffffffe)) {
        CloseHandle(DAT_10015960);
    }
    return;
}



// Library Function - Single Match
//  ___dcrt_write_console
// 
// Libraries: Visual Studio 2019 Debug, Visual Studio 2019 Release

BOOL __cdecl ___dcrt_write_console(void *param_1,DWORD param_2,LPDWORD param_3)

{
    BOOL BVar1;
    DWORD DVar2;
    
    BVar1 = WriteConsoleW(DAT_10015960,param_1,param_2,param_3,NULL);
    if (BVar1 == 0x0) {
        DVar2 = GetLastError();
        if (DVar2 == 0x6) {
            FID_conflict____dcrt_terminate_console_output();
            __dcrt_lowio_initialize_console_output();
            BVar1 = WriteConsoleW(DAT_10015960,param_1,param_2,param_3,NULL);
        }
    }
    return BVar1;
}



// WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4

undefined4 FUN_1000b31b(uint *param_1,uint **param_2)

{
    uint uVar1;
    uint *puVar2;
    undefined4 uVar3;
    undefined4 *in_FS_OFFSET;
    undefined4 local_14;
    
    FUN_10009709(*param_1);
    uVar1 = **param_2;
    puVar2 = param_2[0x1];
    if ((*(byte *)((&DAT_10016250)[(int)uVar1 >> 0x6] + 0x28 + (uVar1 & 0x3f) * 0x38) & 0x1) == 0x0) {
        *(undefined *)(puVar2 + 0x7) = 0x1;
        puVar2[0x6] = 0x9;
        uVar3 = 0xffffffff;
    }
    else {
        uVar3 = FUN_1000b44f(uVar1,(int)puVar2);
    }
    FUN_1000b3a0();
    *in_FS_OFFSET = local_14;
    return uVar3;
}



void FUN_1000b3a0(void)

{
    int unaff_EBP;
    
    ___acrt_lowio_unlock_fh(**(uint **)(unaff_EBP + 0x10));
    return;
}



undefined4 __cdecl FUN_1000b3ac(uint param_1,__acrt_ptd **param_2)

{
    undefined4 uVar1;
    uint *local_18;
    __acrt_ptd **local_14;
    uint local_10;
    uint local_c;
    
    if (param_1 == 0xfffffffe) {
        param_2[0x8] = NULL;
        *(undefined *)(param_2 + 0x9) = 0x1;
        *(undefined *)(param_2 + 0x7) = 0x1;
        param_2[0x6] = (__acrt_ptd *)0x9;
    }
    else {
        if (((-0x1 < (int)param_1) && (param_1 < DAT_10016450)) && ((*(byte *)((&DAT_10016250)[(int)param_1 >> 0x6] + 0x28 + (param_1 & 0x3f) * 0x38) & 0x1) != 0x0)) {
            local_18 = &param_1;
            local_c = param_1;
            local_14 = param_2;
            local_10 = param_1;
            uVar1 = FUN_1000b31b(&local_10,&local_18);
            return uVar1;
        }
        *(undefined *)(param_2 + 0x9) = 0x1;
        param_2[0x8] = NULL;
        *(undefined *)(param_2 + 0x7) = 0x1;
        param_2[0x6] = (__acrt_ptd *)0x9;
        FUN_10005d8b(NULL,NULL,NULL,0x0,0x0,param_2);
    }
    return 0xffffffff;
}



undefined4 __cdecl FUN_1000b44f(uint param_1,int param_2)

{
    int iVar1;
    int iVar2;
    HANDLE hObject;
    BOOL BVar3;
    undefined4 uVar4;
    DWORD DVar5;
    
    iVar1 = FUN_100097e0(param_1);
    if (iVar1 != -0x1) {
        if (((param_1 == 0x1) && ((*(byte *)(DAT_10016250 + 0x98) & 0x1) != 0x0)) || ((param_1 == 0x2 && ((*(byte *)(DAT_10016250 + 0x60) & 0x1) != 0x0)))) {
            iVar1 = FUN_100097e0(0x2);
            iVar2 = FUN_100097e0(0x1);
            if (iVar2 == iVar1) goto LAB_1000b465;
        }
        hObject = (HANDLE)FUN_100097e0(param_1);
        BVar3 = CloseHandle(hObject);
        if (BVar3 == 0x0) {
            DVar5 = GetLastError();
            goto LAB_1000b4b7;
        }
    }
LAB_1000b465:
    DVar5 = 0x0;
LAB_1000b4b7:
    FUN_1000974f(param_1);
    *(undefined *)((&DAT_10016250)[(int)param_1 >> 0x6] + 0x28 + (param_1 & 0x3f) * 0x38) = 0x0;
    if (DVar5 == 0x0) {
        uVar4 = 0x0;
    }
    else {
        FUN_10005eb2(DVar5,param_2);
        uVar4 = 0xffffffff;
    }
    return uVar4;
}



// Library Function - Single Match
//  void __cdecl __acrt_stdio_free_stream(class __crt_stdio_stream)
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl __acrt_stdio_free_stream(__crt_stdio_stream param_1)

{
    undefined3 in_stack_00000005;
    
    *_param_1 = 0x0;
    _param_1[0x1] = 0x0;
    _param_1[0x2] = 0x0;
    _param_1[0x4] = 0xffffffff;
    _param_1[0x5] = 0x0;
    _param_1[0x6] = 0x0;
    _param_1[0x7] = 0x0;
    _param_1[0x3] = 0x0;
    return;
}



// Library Function - Single Match
//  __CIlog10_pentium4
// 
// Library: Visual Studio

void __CIlog10_pentium4(void)

{
    float10 in_ST0;
    
    start((double)in_ST0);
    return;
}



// Library Function - Single Match
//  start
// 
// Library: Visual Studio 2019 Release

float10 __cdecl start(double param_1)

{
    uint uVar1;
    uint uVar2;
    uint uVar3;
    int iVar4;
    int iVar5;
    ulonglong uVar6;
    double dVar7;
    undefined in_XMM0 [0x10];
    double dVar8;
    double dVar9;
    double dVar10;
    double dVar11;
    double dVar12;
    double local_c;
    
    iVar4 = 0x0;
    while( true ) {
        uVar6 = SUB168(in_XMM0,0x0);
        uVar2 = (uint)(ushort)(SUB162(in_XMM0 >> 0x30,0x0) >> 0x4);
        dVar7 = (double)(uVar6 & 0xfffffffffffff | 0x3ff0000000000000);
        uVar1 = SUB82(dVar7 + 4398046511103.008,0x0) & 0x7f0;
        dVar9 = (double)(uVar6 & 0xfffff80000000 | 0x3ff0000000000000);
        dVar12 = (double)(uVar6 & 0xfffff80000000 | 0x3ff0000000000000);
        dVar10 = dVar9 * *(double *)(&DAT_10012690 + uVar1) - 0.43359375;
        dVar7 = (dVar7 - dVar9) * *(double *)(&DAT_10012690 + uVar1);
        dVar8 = ((double)(uVar6 & 0xfffffffffffff | 0x3ff0000000000000) - dVar12) * *(double *)(&UNK_10012698 + uVar1);
        dVar9 = dVar7 + dVar10;
        dVar12 = dVar8 + (dVar12 * *(double *)(&UNK_10012698 + uVar1) - 0.43359375);
        uVar3 = uVar2 - 0x1;
        if (uVar3 < 0x7fe) {
            iVar4 = (uVar2 - 0x3ff) + iVar4;
            dVar11 = (double)iVar4;
            iVar5 = 0x0;
            if (uVar1 + iVar4 * 0x400 == 0x0) {
                iVar5 = 0x10;
            }
            return (float10)(((dVar12 * -3.071795256153705 + 1.775881635348345) * dVar12 + -1.155016766740187) * dVar12 * dVar12 +
                             ((dVar9 * 21.53547326284658 + -10.89355785277636) * dVar9 + 5.667600603343536) * dVar9 * dVar9 * dVar9 * dVar9 * dVar9 + dVar9 * 0.001616102407499711 +
                             *(double *)(&UNK_10012288 + uVar1) + dVar11 * 2.836339455104496e-14 + (double)((ulonglong)dVar8 & *(ulonglong *)(&UNK_100120a8 + iVar5)) +
                            *(double *)(&DAT_10012280 + uVar1) + dVar10 + dVar11 * 0.3010299956639528 + (double)((ulonglong)dVar7 & *(ulonglong *)(&DAT_100120a0 + iVar5)));
        }
        local_c = (double)-(ulonglong)(param_1 == 0.0);
        if (SUB82(local_c,0x0) != 0x0) break;
        if (uVar3 != 0xffffffff) {
            if (uVar3 < 0x7ff) {
                local_c = 2.225073858507201e-308;
                if ((double)((ulonglong)param_1 & 0xfffffffffffff | 0x3ff0000000000000) == 1.0) {
                    return (float10)INFINITY;
                }
                iVar4 = 0x3e9;
            }
            else if (((uVar2 & 0x7ff) < 0x7ff) || ((SUB84(param_1,0x0) | (uint)((ulonglong)param_1 >> 0x20) & 0xfffff) == 0x0)) {
                local_c = -NAN;
                iVar4 = 0x9;
            }
            else {
                iVar4 = 0x3e9;
            }
            goto LAB_1000b76a;
        }
        in_XMM0 = CONCAT88(dVar12,param_1 * 4503599627370496.0);
        iVar4 = -0x34;
    }
    local_c = -INFINITY;
    iVar4 = 0x8;
LAB_1000b76a:
    ___libm_error_support(&param_1,&param_1,&local_c,iVar4);
    return (float10)local_c;
}



float10 __fastcall FUN_1000bdd0(undefined4 param_1,int param_2,ushort param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
    float10 in_ST0;
    int local_24;
    undefined4 local_20;
    undefined4 local_1c;
    undefined4 local_18;
    undefined4 local_14;
    undefined4 local_10;
    double local_c;
    
    local_14 = param_7;
    local_10 = param_8;
    local_c = (double)in_ST0;
    local_1c = param_5;
    local_18 = param_6;
    local_20 = param_1;
    __87except(param_2,&local_24,&param_3);
    return (float10)local_c;
}



float10 __fastcall FUN_1000bde7(undefined4 param_1,int param_2,ushort param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6)

{
    float10 in_ST0;
    int local_24;
    undefined4 uStack32;
    undefined4 uStack28;
    undefined4 uStack24;
    double dStack12;
    
    dStack12 = (double)in_ST0;
    uStack28 = param_5;
    uStack24 = param_6;
    uStack32 = param_1;
    __87except(param_2,&local_24,&param_3);
    return (float10)dStack12;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// Library Function - Single Match
//  ___libm_error_support
// 
// Library: Visual Studio 2019 Release

void __cdecl ___libm_error_support(undefined8 *param_1,undefined8 *param_2,undefined8 *param_3,int param_4)

{
    undefined8 uVar1;
    code *pcVar2;
    int iVar3;
    undefined4 *puVar4;
    undefined4 local_24;
    char *local_20;
    undefined8 local_1c;
    undefined8 local_14;
    undefined8 local_c;
    
    if (_DAT_100164a8 == 0x0) {
        pcVar2 = ___acrt_invoke_user_matherr;
    }
    else {
        pcVar2 = (code *)DecodePointer(DAT_100164b4);
    }
    if (0x1a < param_4) {
        if (param_4 != 0x1b) {
            if (param_4 == 0x1c) {
                local_20 = "pow";
            }
            else if (param_4 == 0x31) {
                local_20 = "sqrt";
            }
            else if (param_4 == 0x3a) {
                local_20 = "acos";
            }
            else {
                if (param_4 != 0x3d) {
                    if ((param_4 != 0x3e8) && (param_4 != 0x3e9)) {
                        return;
                    }
                    uVar1 = *param_1;
                    goto LAB_1000bf2b;
                }
                local_20 = "asin";
            }
            goto LAB_1000bf8b;
        }
        local_24 = 0x2;
LAB_1000bfd1:
        local_20 = "pow";
        goto LAB_1000bfd8;
    }
    if (param_4 == 0x1a) {
        uVar1 = 0x3ff0000000000000;
LAB_1000bf2b:
        *param_3 = uVar1;
        return;
    }
    if (0xe < param_4) {
        if (param_4 == 0xf) {
            local_20 = &DAT_10012240;
        }
        else {
            if (param_4 == 0x18) {
                local_24 = 0x3;
                goto LAB_1000bfd1;
            }
            if (param_4 != 0x19) {
                return;
            }
            local_20 = &DAT_10012244;
        }
        local_24 = 0x4;
        local_1c = *param_1;
        local_14 = *param_2;
        puVar4 = &local_24;
        local_c = *param_3;
        _guard_check_icall();
        (*pcVar2)(puVar4);
        goto LAB_1000c00e;
    }
    if (param_4 == 0xe) {
        local_24 = 0x3;
        local_20 = "exp";
    }
    else {
        if (param_4 != 0x2) {
            if (param_4 == 0x3) {
                local_20 = "log";
            }
            else {
                if (param_4 == 0x8) {
                    local_24 = 0x2;
                    local_20 = "log10";
                    goto LAB_1000bfd8;
                }
                if (param_4 != 0x9) {
                    return;
                }
                local_20 = "log10";
            }
LAB_1000bf8b:
            local_24 = 0x1;
            local_1c = *param_1;
            local_14 = *param_2;
            puVar4 = &local_24;
            local_c = *param_3;
            _guard_check_icall();
            iVar3 = (*pcVar2)(puVar4);
            if (iVar3 == 0x0) {
                puVar4 = (undefined4 *)FUN_10005ee9();
                *puVar4 = 0x21;
            }
            goto LAB_1000c00e;
        }
        local_24 = 0x2;
        local_20 = "log";
    }
LAB_1000bfd8:
    local_1c = *param_1;
    local_14 = *param_2;
    puVar4 = &local_24;
    local_c = *param_3;
    _guard_check_icall();
    iVar3 = (*pcVar2)(puVar4);
    if (iVar3 == 0x0) {
        puVar4 = (undefined4 *)FUN_10005ee9();
        *puVar4 = 0x22;
    }
LAB_1000c00e:
    *param_3 = local_c;
    return;
}



// Library Function - Single Match
//  __ceil_default
// 
// Library: Visual Studio 2019 Release

float10 __cdecl __ceil_default(double param_1)

{
    double dVar1;
    uint uVar2;
    int iVar3;
    float10 fVar4;
    uint uVar5;
    undefined4 uVar6;
    undefined4 uVar7;
    
    uVar2 = __ctrlfp(0x1b3f,0xffff);
    if ((param_1._6_2_ & 0x7ff0) == 0x7ff0) {
        iVar3 = __sptype(SUB84(param_1,0x0),(uint)((ulonglong)param_1 >> 0x20));
        if (0x2 < iVar3 - 0x1U) {
            uVar6 = SUB84(param_1 + 1.0,0x0);
            uVar7 = (undefined4)((ulonglong)(param_1 + 1.0) >> 0x20);
            uVar5 = 0x8;
LAB_1000c07f:
            fVar4 = (float10)__except1(uVar5,0xc,param_1,(double)CONCAT44(uVar7,uVar6),uVar2);
            return fVar4;
        }
        __ctrlfp(uVar2,0xffff);
        dVar1 = param_1;
    }
    else {
        fVar4 = __frnd(param_1);
        dVar1 = (double)fVar4;
        if (((float10)param_1 != fVar4) && ((uVar2 & 0x20) == 0x0)) {
            uVar6 = SUB84((double)fVar4,0x0);
            uVar7 = (undefined4)((ulonglong)(double)fVar4 >> 0x20);
            uVar5 = 0x10;
            goto LAB_1000c07f;
        }
        __ctrlfp(uVar2,0xffff);
    }
    return (float10)dVar1;
}



// Library Function - Single Match
//  __clrfp
// 
// Library: Visual Studio 2019 Release

int __clrfp(void)

{
    short in_FPUStatusWord;
    
    return (int)in_FPUStatusWord;
}



// Library Function - Single Match
//  __ctrlfp
// 
// Library: Visual Studio 2019 Release

int __ctrlfp(undefined4 param_1,undefined4 param_2)

{
    short in_FPUControlWord;
    
    return (int)in_FPUControlWord;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// Library Function - Single Match
//  __set_statfp
// 
// Library: Visual Studio 2019 Release

void __set_statfp(uint param_1)

{
    return;
}



// Library Function - Single Match
//  __statfp
// 
// Library: Visual Studio 2019 Release

int __statfp(void)

{
    short in_FPUStatusWord;
    
    return (int)in_FPUStatusWord;
}



// Library Function - Single Match
//  __d_inttype
// 
// Library: Visual Studio 2019 Release

undefined4 __cdecl __d_inttype(double param_1)

{
    uint uVar1;
    float10 fVar2;
    float10 fVar3;
    
    uVar1 = __fpclass(param_1);
    if ((uVar1 & 0x90) == 0x0) {
        fVar2 = __frnd(param_1);
        if ((float10)param_1 == fVar2) {
            fVar2 = (float10)param_1 * (float10)0.5;
            fVar3 = __frnd((double)fVar2);
            if ((float10)(double)fVar2 != fVar3) {
                return 0x1;
            }
            return 0x2;
        }
    }
    return 0x0;
}



// Library Function - Single Match
//  __powhlp
// 
// Library: Visual Studio 2019 Release

undefined4 __cdecl __powhlp(int param_1,int param_2,int param_3,int param_4,undefined8 *param_5)

{
    double dVar1;
    undefined8 uVar2;
    int iVar3;
    
    dVar1 = ABS((double)CONCAT44(param_2,param_1));
    if (param_4 == 0x7ff00000) {
        if (param_3 != 0x0) goto LAB_1000c26c;
        uVar2 = 0x3ff0000000000000;
        if (dVar1 <= 1.0) {
            if ((ushort)((ushort)(1.0 < dVar1) << 0x8 | (ushort)(dVar1 == 1.0) << 0xe) == 0x0) {
                uVar2 = 0x0;
            }
            goto LAB_1000c2fd;
        }
    }
    else {
        if ((param_4 == -0x100000) && (param_3 == 0x0)) {
            if (dVar1 <= 1.0) {
                uVar2 = 0x3ff0000000000000;
                if ((ushort)((ushort)(1.0 < dVar1) << 0x8 | (ushort)(dVar1 == 1.0) << 0xe) == 0x0) {
                    uVar2 = 0x7ff0000000000000;
                }
            }
            else {
                uVar2 = 0x0;
            }
            goto LAB_1000c2fd;
        }
LAB_1000c26c:
        if (param_2 != 0x7ff00000) {
            if (param_2 != -0x100000) {
                return 0x0;
            }
            if (param_1 != 0x0) {
                return 0x0;
            }
            iVar3 = __d_inttype((double)CONCAT44(param_4,param_3));
            uVar2 = 0x0;
            dVar1 = (double)CONCAT44(param_4,param_3);
            if ((ushort)((ushort)(dVar1 < 0.0) << 0x8 | (ushort)(dVar1 == 0.0) << 0xe) == 0x0) {
                uVar2 = 0x7ff0000000000000;
                if (iVar3 == 0x1) {
                    uVar2 = 0xfff0000000000000;
                }
            }
            else if (0.0 <= dVar1) {
                uVar2 = 0x3ff0000000000000;
            }
            else if (iVar3 == 0x1) {
                uVar2 = 0x8000000000000000;
            }
            goto LAB_1000c2fd;
        }
        if (param_1 != 0x0) {
            return 0x0;
        }
        dVar1 = (double)CONCAT44(param_4,param_3);
        if ((ushort)((ushort)(dVar1 < 0.0) << 0x8 | (ushort)(dVar1 == 0.0) << 0xe) != 0x0) {
            uVar2 = 0x0;
            if (0.0 <= dVar1) {
                uVar2 = 0x3ff0000000000000;
            }
            goto LAB_1000c2fd;
        }
    }
    uVar2 = 0x7ff0000000000000;
LAB_1000c2fd:
    *param_5 = uVar2;
    return 0x0;
}



// Library Function - Single Match
//  __87except
// 
// Library: Visual Studio 2019 Release

void __cdecl __87except(int param_1,int *param_2,ushort *param_3)

{
    bool bVar1;
    undefined3 extraout_var;
    int iVar2;
    undefined extraout_DL;
    undefined extraout_DL_00;
    undefined uVar3;
    uint uVar4;
    undefined in_stack_ffffff68;
    uint local_94;
    uint local_90 [0xc];
    undefined8 local_60;
    uint local_50;
    uint local_14;
    
    local_14 = DAT_10015124 ^ (uint)&stack0xfffffff0;
    local_94 = (uint)*param_3;
    iVar2 = *param_2;
    if (iVar2 == 0x1) {
LAB_1000c36b:
        uVar4 = 0x8;
LAB_1000c36d:
        bVar1 = FUN_1000c523(uVar4,(double *)(param_2 + 0x6),local_94);
        if (CONCAT31(extraout_var,bVar1) == 0x0) {
            if (((param_1 == 0x10) || (param_1 == 0x16)) || (param_1 == 0x1d)) {
                local_60 = *(undefined8 *)(param_2 + 0x4);
                local_50 = local_50 & 0xffffffe3 | 0x3;
            }
            else {
                local_50 = local_50 & 0xfffffffe;
            }
            __raise_exc(local_90,&local_94,uVar4,param_1,(undefined8 *)(param_2 + 0x2),(undefined8 *)(param_2 + 0x6));
        }
    }
    else {
        if (iVar2 == 0x2) {
            uVar4 = 0x4;
            goto LAB_1000c36d;
        }
        if (iVar2 == 0x3) {
            uVar4 = 0x11;
            goto LAB_1000c36d;
        }
        if (iVar2 == 0x4) {
            uVar4 = 0x12;
            goto LAB_1000c36d;
        }
        if (iVar2 == 0x5) goto LAB_1000c36b;
        if (iVar2 == 0x8) {
            uVar4 = 0x10;
            goto LAB_1000c36d;
        }
    }
    __ctrlfp(local_94,0xffff);
    if (*param_2 != 0x8) {
        uVar4 = ___acrt_has_user_matherr();
        if ((char)uVar4 != '\0') {
            iVar2 = ___acrt_invoke_user_matherr(param_2);
            uVar3 = extraout_DL;
            if (iVar2 != 0x0) goto LAB_1000c3fa;
        }
    }
    __set_errno_from_matherr(*param_2);
    uVar3 = extraout_DL_00;
LAB_1000c3fa:
    FUN_10001f99(local_14 ^ (uint)&stack0xfffffff0,uVar3,in_stack_ffffff68);
    return;
}



// Library Function - Single Match
//  __frnd
// 
// Library: Visual Studio 2019 Release

float10 __cdecl __frnd(double param_1)

{
    return (float10)ROUND(param_1);
}



// Library Function - Single Match
//  __errcode
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

int __cdecl __errcode(uint param_1)

{
    int iStack8;
    
    if ((param_1 & 0x20) == 0x0) {
        if ((param_1 & 0x8) != 0x0) {
            return 0x1;
        }
        if ((param_1 & 0x4) == 0x0) {
            if ((param_1 & 0x1) == 0x0) {
                return (param_1 & 0x2) * 0x2;
            }
            iStack8 = 0x3;
        }
        else {
            iStack8 = 0x2;
        }
    }
    else {
        iStack8 = 0x5;
    }
    return iStack8;
}



// Library Function - Single Match
//  __except1
// 
// Library: Visual Studio 2019 Release

void __cdecl __except1(uint param_1,int param_2,undefined8 param_3,double param_4,uint param_5)

{
    bool bVar1;
    undefined3 extraout_var;
    int iVar2;
    uint uVar3;
    undefined extraout_DL;
    undefined extraout_DL_00;
    undefined uVar4;
    uint uVar5;
    undefined in_stack_ffffff68;
    uint local_90 [0x10];
    uint local_50;
    uint local_14;
    
    uVar5 = param_5;
    local_14 = DAT_10015124 ^ (uint)&stack0xfffffff0;
    bVar1 = FUN_1000c523(param_1,&param_4,param_5);
    if (CONCAT31(extraout_var,bVar1) == 0x0) {
        local_50 = local_50 & 0xfffffffe;
        __raise_exc_ex(local_90,&param_5,param_1,param_2,&param_3,&param_4,0x0);
        uVar5 = param_5;
    }
    iVar2 = __errcode(param_1);
    uVar3 = ___acrt_has_user_matherr();
    if (((char)uVar3 == '\0') || (iVar2 == 0x0)) {
        __set_errno_from_matherr(iVar2);
        __ctrlfp(uVar5,0xffff);
        uVar4 = extraout_DL_00;
    }
    else {
        FUN_1000cae4(iVar2,param_2,(int)param_3,(int)((ulonglong)param_3 >> 0x20),0x0,0x0,SUB84(param_4,0x0),(int)((ulonglong)param_4 >> 0x20));
        uVar4 = extraout_DL;
    }
    FUN_10001f99(local_14 ^ (uint)&stack0xfffffff0,uVar4,in_stack_ffffff68);
    return;
}



// WARNING: Could not reconcile some variable overlaps

bool __cdecl FUN_1000c523(uint param_1,double *param_2,uint param_3)

{
    double dVar1;
    uint uVar2;
    byte bVar3;
    int iVar4;
    uint extraout_ECX;
    uint uVar5;
    float10 fVar6;
    float10 fVar7;
    uint local_28;
    byte bStack36;
    undefined uStack35;
    ushort uStack34;
    int local_1c;
    uint local_18;
    double local_14;
    uint local_c;
    char local_6;
    byte local_5;
    
    uVar5 = param_1 & 0x1f;
    if (((param_1 & 0x8) != 0x0) && ((param_3 & 0x1) != 0x0)) {
        __set_statfp(0x1);
        uVar5 = param_1 & 0x17;
        goto LAB_1000c77b;
    }
    if ((param_1 & param_3 & 0x4) != 0x0) {
        __set_statfp(0x4);
        uVar5 = param_1 & 0x1b;
        goto LAB_1000c77b;
    }
    if (((param_1 & 0x1) == 0x0) || ((param_3 & 0x8) == 0x0)) {
        if (((param_1 & 0x2) == 0x0) || ((param_3 & 0x10) == 0x0)) goto LAB_1000c77b;
        dVar1 = *param_2;
        uVar5 = param_1 >> 0x4 & 0x1;
        local_c = uVar5;
        if (dVar1 == 0.0) {
LAB_1000c76f:
            __set_statfp(0x10);
        }
        else {
            fVar6 = (float10)__decomp(SUB84(dVar1,0x0),(uint)((ulonglong)dVar1 >> 0x20),&local_1c);
            local_1c = local_1c + -0x600;
            dVar1 = (double)fVar6;
            local_28 = SUB84(dVar1,0x0);
            bStack36 = (byte)((ulonglong)dVar1 >> 0x20);
            uStack35 = (undefined)((ulonglong)dVar1 >> 0x28);
            uStack34 = (ushort)((ulonglong)dVar1 >> 0x30);
            fVar7 = (float10)0x0;
            if (local_1c < -0x432) {
                fVar7 = fVar7 * fVar6;
                uVar5 = 0x1;
            }
            else {
                local_5 = (ushort)((ushort)(fVar7 < fVar6) << 0x8 | (ushort)(fVar7 == fVar6) << 0xe) == 0x0;
                local_18 = extraout_ECX & 0xffffff00;
                local_6 = '\0';
                uStack34 = uStack34 & 0xf | 0x10;
                if (local_1c < -0x3fd) {
                    local_1c = -0x3fd - local_1c;
                    do {
                        local_18 = local_28 & 0x1;
                        if (local_18 != 0x0) {
                            if (uVar5 == 0x0) {
                                uVar5 = 0x1;
                            }
                            local_6 = '\x01';
                        }
                        local_28 = local_28 >> 0x1;
                        if ((bStack36 & 0x1) != 0x0) {
                            local_28 = local_28 | 0x80000000;
                        }
                        uVar2 = CONCAT22(uStack34,CONCAT11(uStack35,bStack36)) >> 0x1;
                        bStack36 = (byte)uVar2;
                        uStack35 = (undefined)(uVar2 >> 0x8);
                        uStack34 = uStack34 >> 0x1;
                        local_1c = local_1c + -0x1;
                        local_c = uVar5;
                    } while (local_1c != 0x0);
                }
                local_14 = (double)CONCAT26(uStack34,CONCAT15(uStack35,CONCAT14(bStack36,local_28)));
                fVar7 = (float10)local_14;
                if ((bool)local_5) {
                    fVar7 = -fVar7;
                    local_14 = (double)fVar7;
                    dVar1 = (double)fVar7;
                    local_28 = SUB84(dVar1,0x0);
                    bStack36 = (byte)((ulonglong)dVar1 >> 0x20);
                    uStack35 = (undefined)((ulonglong)dVar1 >> 0x28);
                    uStack34 = (ushort)((ulonglong)dVar1 >> 0x30);
                }
                if (((char)local_18 != '\0') || (uVar5 = local_c, local_6 != '\0')) {
                    iVar4 = _fegetround();
                    uVar5 = local_c;
                    if (iVar4 == 0x0) {
                        if ((char)local_18 == '\0') goto LAB_1000c75c;
                        if (local_6 == '\0') {
                            bVar3 = (byte)local_28 & 0x1;
                            goto LAB_1000c74b;
                        }
                    }
                    else {
                        bVar3 = local_5;
                        if (iVar4 != 0x100) {
                            if (iVar4 != 0x200) goto LAB_1000c75c;
                            bVar3 = local_5 ^ 0x1;
                        }
LAB_1000c74b:
                        if (bVar3 == 0x0) {
LAB_1000c75c:
                            fVar7 = (float10)local_14;
                            goto LAB_1000c762;
                        }
                    }
                    iVar4 = CONCAT22(uStack34,CONCAT11(uStack35,bStack36)) + (uint)(0xfffffffe < local_28);
                    bStack36 = (byte)iVar4;
                    uStack35 = (undefined)((uint)iVar4 >> 0x8);
                    uStack34 = (ushort)((uint)iVar4 >> 0x10);
                    fVar7 = (float10)(double)CONCAT26(uStack34,CONCAT15(uStack35,CONCAT14(bStack36,local_28 + 0x1)));
                }
            }
LAB_1000c762:
            *param_2 = (double)fVar7;
            if (uVar5 != 0x0) goto LAB_1000c76f;
        }
        uVar5 = param_1 & 0x1d;
        goto LAB_1000c77b;
    }
    __set_statfp(0x8);
    uVar5 = param_3 & 0xc00;
    if (uVar5 == 0x0) {
        if (*param_2 <= 0.0) {
LAB_1000c5fa:
            dVar1 = INFINITY;
            goto LAB_1000c600;
        }
LAB_1000c5f2:
        dVar1 = INFINITY;
LAB_1000c602:
        *param_2 = dVar1;
    }
    else {
        if (uVar5 == 0x400) {
            if (*param_2 <= 0.0) goto LAB_1000c5fa;
            dVar1 = 1.797693134862316e+308;
            goto LAB_1000c602;
        }
        if (uVar5 == 0x800) {
            if (0.0 < *param_2) goto LAB_1000c5f2;
            dVar1 = 1.797693134862316e+308;
LAB_1000c600:
            dVar1 = -dVar1;
            goto LAB_1000c602;
        }
        if (uVar5 == 0xc00) {
            dVar1 = 1.797693134862316e+308;
            if (0.0 < *param_2) goto LAB_1000c602;
            goto LAB_1000c600;
        }
    }
    uVar5 = param_1 & 0x1e;
LAB_1000c77b:
    if (((param_1 & 0x10) != 0x0) && ((param_3 & 0x20) != 0x0)) {
        __set_statfp(0x20);
        uVar5 = uVar5 & 0xffffffef;
    }
    return uVar5 == 0x0;
}



// Library Function - Single Match
//  __raise_exc
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl __raise_exc(uint *param_1,uint *param_2,uint param_3,int param_4,undefined8 *param_5,undefined8 *param_6)

{
    __raise_exc_ex(param_1,param_2,param_3,param_4,param_5,param_6,0x0);
    return;
}



// Library Function - Single Match
//  __raise_exc_ex
// 
// Library: Visual Studio 2019 Release

void __cdecl __raise_exc_ex(uint *param_1,uint *param_2,uint param_3,int param_4,undefined8 *param_5,undefined8 *param_6,int param_7)

{
    uint *puVar1;
    undefined8 *puVar2;
    uint uVar3;
    DWORD dwExceptionCode;
    
    puVar1 = param_2;
    param_1[0x1] = 0x0;
    dwExceptionCode = 0xc000000d;
    param_1[0x2] = 0x0;
    param_1[0x3] = 0x0;
    if ((param_3 & 0x10) != 0x0) {
        dwExceptionCode = 0xc000008f;
        param_1[0x1] = param_1[0x1] | 0x1;
    }
    if ((param_3 & 0x2) != 0x0) {
        dwExceptionCode = 0xc0000093;
        param_1[0x1] = param_1[0x1] | 0x2;
    }
    if ((param_3 & 0x1) != 0x0) {
        dwExceptionCode = 0xc0000091;
        param_1[0x1] = param_1[0x1] | 0x4;
    }
    if ((param_3 & 0x4) != 0x0) {
        dwExceptionCode = 0xc000008e;
        param_1[0x1] = param_1[0x1] | 0x8;
    }
    if ((param_3 & 0x8) != 0x0) {
        dwExceptionCode = 0xc0000090;
        param_1[0x1] = param_1[0x1] | 0x10;
    }
    param_1[0x2] = param_1[0x2] ^ (~(*param_2 << 0x4) ^ param_1[0x2]) & 0x10;
    param_1[0x2] = param_1[0x2] ^ (~(*param_2 * 0x2) ^ param_1[0x2]) & 0x8;
    param_1[0x2] = param_1[0x2] ^ (~(*param_2 >> 0x1) ^ param_1[0x2]) & 0x4;
    param_1[0x2] = param_1[0x2] ^ (~(*param_2 >> 0x3) ^ param_1[0x2]) & 0x2;
    param_1[0x2] = param_1[0x2] ^ (~(*param_2 >> 0x5) ^ param_1[0x2]) & 0x1;
    uVar3 = __statfp();
    puVar2 = param_6;
    if ((uVar3 & 0x1) != 0x0) {
        param_1[0x3] = param_1[0x3] | 0x10;
    }
    if ((uVar3 & 0x4) != 0x0) {
        param_1[0x3] = param_1[0x3] | 0x8;
    }
    if ((uVar3 & 0x8) != 0x0) {
        param_1[0x3] = param_1[0x3] | 0x4;
    }
    if ((uVar3 & 0x10) != 0x0) {
        param_1[0x3] = param_1[0x3] | 0x2;
    }
    if ((uVar3 & 0x20) != 0x0) {
        param_1[0x3] = param_1[0x3] | 0x1;
    }
    uVar3 = *puVar1 & 0xc00;
    if (uVar3 == 0x0) {
        *param_1 = *param_1 & 0xfffffffc;
    }
    else {
        if (uVar3 == 0x400) {
            uVar3 = *param_1 & 0xfffffffd | 0x1;
        }
        else {
            if (uVar3 != 0x800) {
                if (uVar3 == 0xc00) {
                    *param_1 = *param_1 | 0x3;
                }
                goto LAB_1000c921;
            }
            uVar3 = *param_1 & 0xfffffffe | 0x2;
        }
        *param_1 = uVar3;
    }
LAB_1000c921:
    uVar3 = *puVar1 & 0x300;
    if (uVar3 == 0x0) {
        uVar3 = *param_1 & 0xffffffeb | 0x8;
LAB_1000c957:
        *param_1 = uVar3;
    }
    else {
        if (uVar3 == 0x200) {
            uVar3 = *param_1 & 0xffffffe7 | 0x4;
            goto LAB_1000c957;
        }
        if (uVar3 == 0x300) {
            *param_1 = *param_1 & 0xffffffe3;
        }
    }
    *param_1 = *param_1 ^ (param_4 << 0x5 ^ *param_1) & 0x1ffe0;
    param_1[0x8] = param_1[0x8] | 0x1;
    if (param_7 == 0x0) {
        param_1[0x8] = param_1[0x8] & 0xffffffe3 | 0x2;
        *(undefined8 *)(param_1 + 0x4) = *param_5;
        param_1[0x18] = param_1[0x18] | 0x1;
        param_1[0x18] = param_1[0x18] & 0xffffffe3 | 0x2;
        *(undefined8 *)(param_1 + 0x14) = *param_6;
    }
    else {
        param_1[0x8] = param_1[0x8] & 0xffffffe1;
        param_1[0x4] = *(uint *)param_5;
        param_1[0x18] = param_1[0x18] | 0x1;
        param_1[0x18] = param_1[0x18] & 0xffffffe1;
        param_1[0x14] = *(uint *)param_6;
    }
    __clrfp();
    RaiseException(dwExceptionCode,0x0,0x1,(ULONG_PTR *)&param_1);
    uVar3 = param_1[0x2];
    if ((uVar3 & 0x10) != 0x0) {
        *puVar1 = *puVar1 & 0xfffffffe;
        uVar3 = param_1[0x2];
    }
    if ((uVar3 & 0x8) != 0x0) {
        *puVar1 = *puVar1 & 0xfffffffb;
        uVar3 = param_1[0x2];
    }
    if ((uVar3 & 0x4) != 0x0) {
        *puVar1 = *puVar1 & 0xfffffff7;
        uVar3 = param_1[0x2];
    }
    if ((uVar3 & 0x2) != 0x0) {
        *puVar1 = *puVar1 & 0xffffffef;
        uVar3 = param_1[0x2];
    }
    if ((uVar3 & 0x1) != 0x0) {
        *puVar1 = *puVar1 & 0xffffffdf;
    }
    uVar3 = *param_1 & 0x3;
    if (uVar3 == 0x0) {
        *puVar1 = *puVar1 & 0xfffff3ff;
    }
    else {
        if (uVar3 == 0x1) {
            uVar3 = *puVar1 & 0xfffff7ff | 0x400;
        }
        else {
            if (uVar3 != 0x2) {
                if (uVar3 == 0x3) {
                    *puVar1 = *puVar1 | 0xc00;
                }
                goto LAB_1000ca6d;
            }
            uVar3 = *puVar1 & 0xfffffbff | 0x800;
        }
        *puVar1 = uVar3;
    }
LAB_1000ca6d:
    uVar3 = *param_1 >> 0x2 & 0x7;
    if (uVar3 == 0x0) {
        uVar3 = *puVar1 & 0xfffff3ff | 0x300;
    }
    else {
        if (uVar3 != 0x1) {
            if (uVar3 == 0x2) {
                *puVar1 = *puVar1 & 0xfffff3ff;
            }
            goto LAB_1000ca9e;
        }
        uVar3 = *puVar1 & 0xfffff3ff | 0x200;
    }
    *puVar1 = uVar3;
LAB_1000ca9e:
    if (param_7 == 0x0) {
        *puVar2 = *(undefined8 *)(param_1 + 0x14);
    }
    else {
        *(uint *)puVar2 = param_1[0x14];
    }
    return;
}



// Library Function - Single Match
//  __set_errno_from_matherr
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

void __cdecl __set_errno_from_matherr(int param_1)

{
    undefined4 *puVar1;
    
    if (param_1 == 0x1) {
        puVar1 = (undefined4 *)FUN_10005ee9();
        *puVar1 = 0x21;
    }
    else if (param_1 - 0x2U < 0x2) {
        puVar1 = (undefined4 *)FUN_10005ee9();
        *puVar1 = 0x22;
        return;
    }
    return;
}



float10 __cdecl FUN_1000cae4(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
    int iVar1;
    undefined4 in_stack_00000024;
    int local_24;
    undefined *local_20;
    undefined4 local_1c;
    undefined4 local_18;
    undefined4 local_14;
    undefined4 local_10;
    undefined4 local_c;
    undefined4 uStack8;
    
    iVar1 = 0x0;
    do {
        if ((&DAT_10012aa8)[iVar1 * 0x2] == param_2) {
            local_20 = (&PTR_DAT_10012aac)[iVar1 * 0x2];
            if (local_20 != NULL) {
                local_1c = param_3;
                local_18 = param_4;
                local_14 = param_5;
                local_10 = param_6;
                local_c = param_7;
                local_24 = param_1;
                uStack8 = param_8;
                __ctrlfp(in_stack_00000024,0xffff);
                iVar1 = ___acrt_invoke_user_matherr(&local_24);
                if (iVar1 == 0x0) {
                    __set_errno_from_matherr(param_1);
                }
                return (float10)(double)CONCAT44(uStack8,local_c);
            }
            goto LAB_1000cb04;
        }
        iVar1 = iVar1 + 0x1;
    } while (iVar1 < 0x1d);
    local_20 = NULL;
LAB_1000cb04:
    __ctrlfp(in_stack_00000024,0xffff);
    __set_errno_from_matherr(param_1);
    return (float10)(double)CONCAT44(param_8,param_7);
}



// Library Function - Single Match
//  __decomp
// 
// Library: Visual Studio 2019 Release

void __cdecl __decomp(int param_1,uint param_2,int *param_3)

{
    uint uVar1;
    double dVar2;
    int iVar3;
    ushort uVar4;
    
    dVar2 = (double)CONCAT17(param_2._3_1_,CONCAT16(param_2._2_1_,CONCAT24((ushort)param_2,param_1)));
    if (dVar2 == 0.0) {
        iVar3 = 0x0;
    }
    else if (((param_2 & 0x7ff00000) == 0x0) && (((param_2 & 0xfffff) != 0x0 || (param_1 != 0x0)))) {
        iVar3 = -0x3fd;
        if ((param_2 & 0x100000) == 0x0) {
            do {
                uVar1 = param_2 * 0x2;
                param_2._0_2_ = (ushort)uVar1;
                param_2 = uVar1;
                if (param_1 < 0x0) {
                    param_2 = uVar1 | 0x1;
                }
                param_1 = param_1 * 0x2;
                iVar3 = iVar3 + -0x1;
            } while ((uVar1 & 0x100000) == 0x0);
            param_2 = uVar1 & 0xffff0000 | (uint)(ushort)param_2;
        }
        uVar4 = (ushort)(param_2 >> 0x10) & 0xffef;
        param_2._2_1_ = (undefined)uVar4;
        param_2._3_1_ = (byte)(uVar4 >> 0x8);
        if ((ushort)((ushort)(0.0 < dVar2) << 0x8 | (ushort)(dVar2 == 0.0) << 0xe) == 0x0) {
            param_2._3_1_ = param_2._3_1_ | 0x80;
        }
        __set_exp(CONCAT17(param_2._3_1_,CONCAT16(param_2._2_1_,CONCAT24((ushort)param_2,param_1))),0x0);
    }
    else {
        __set_exp((ulonglong)dVar2,0x0);
        iVar3 = (param_2 >> 0x14 & 0x7ff) - 0x3fe;
    }
    *param_3 = iVar3;
    return;
}



// Library Function - Single Match
//  __set_exp
// 
// Library: Visual Studio 2019 Release

float10 __cdecl __set_exp(ulonglong param_1,short param_2)

{
    double local_c;
    
    local_c = (double)(param_1 & 0xffffffffffff | (ulonglong)(ushort)((param_2 + 0x3fe) * 0x10 | param_1._6_2_ & 0x800f) << 0x30);
    return (float10)local_c;
}



// Library Function - Single Match
//  __sptype
// 
// Library: Visual Studio 2019 Release

undefined4 __cdecl __sptype(int param_1,uint param_2)

{
    undefined4 uStack8;
    
    if (param_2 == 0x7ff00000) {
        if (param_1 == 0x0) {
            return 0x1;
        }
    }
    else if ((param_2 == 0xfff00000) && (param_1 == 0x0)) {
        return 0x2;
    }
    if ((param_2._2_2_ & 0x7ff8) == 0x7ff8) {
        uStack8 = 0x3;
    }
    else {
        if (((param_2._2_2_ & 0x7ff8) != 0x7ff0) || (((param_2 & 0x7ffff) == 0x0 && (param_1 == 0x0)))) {
            return 0x0;
        }
        uStack8 = 0x4;
    }
    return uStack8;
}



// Library Function - Single Match
//  __fpclass
// 
// Library: Visual Studio 2019 Release

int __cdecl __fpclass(double _X)

{
    int iVar1;
    
    if ((_X._6_2_ & 0x7ff0) == 0x7ff0) {
        iVar1 = __sptype(_X._0_4_,(uint)((ulonglong)_X >> 0x20));
        if (iVar1 == 0x1) {
            return 0x200;
        }
        if (iVar1 == 0x2) {
            iVar1 = 0x4;
        }
        else {
            if (iVar1 != 0x3) {
                return 0x1;
            }
            iVar1 = 0x2;
        }
        return iVar1;
    }
    if ((((ulonglong)_X & 0x7ff0000000000000) == 0x0) && ((((ulonglong)_X & 0xfffff00000000) != 0x0 || (_X._0_4_ != 0x0)))) {
        return (-(uint)(((ulonglong)_X & 0x8000000000000000) != 0x0) & 0xffffff90) + 0x80;
    }
    if (_X == 0.0) {
        return (-(uint)(((ulonglong)_X & 0x8000000000000000) != 0x0) & 0xffffffe0) + 0x40;
    }
    return (-(uint)(((ulonglong)_X & 0x8000000000000000) != 0x0) & 0xffffff08) + 0x100;
}



// Library Function - Single Match
//  __FindPESection
// 
// Libraries: Visual Studio 2015 Release, Visual Studio 2017 Release, Visual Studio 2019 Release

PIMAGE_SECTION_HEADER __cdecl __FindPESection(PBYTE pImageBase,DWORD_PTR rva)

{
    int iVar1;
    PIMAGE_SECTION_HEADER p_Var2;
    uint uVar3;
    
    uVar3 = 0x0;
    iVar1 = *(int *)(pImageBase + 0x3c);
    p_Var2 = (PIMAGE_SECTION_HEADER)(pImageBase + *(ushort *)(pImageBase + iVar1 + 0x14) + 0x18 + iVar1);
    if (*(ushort *)(pImageBase + iVar1 + 0x6) != 0x0) {
        do {
            if ((p_Var2->VirtualAddress <= rva) && (rva < p_Var2->Misc + p_Var2->VirtualAddress)) {
                return p_Var2;
            }
            uVar3 = uVar3 + 0x1;
            p_Var2 = p_Var2 + 0x1;
        } while (uVar3 < *(ushort *)(pImageBase + iVar1 + 0x6));
    }
    return NULL;
}



// Library Function - Single Match
//  __IsNonwritableInCurrentImage
// 
// Library: Visual Studio 2019 Release

BOOL __cdecl __IsNonwritableInCurrentImage(PBYTE pTarget)

{
    uint uVar1;
    BOOL BVar2;
    PIMAGE_SECTION_HEADER p_Var3;
    int **in_FS_OFFSET;
    int *local_14;
    code *pcStack16;
    uint local_c;
    undefined4 local_8;
    
    pcStack16 = __except_handler4;
    local_14 = *in_FS_OFFSET;
    local_c = DAT_10015124 ^ 0x10013ad0;
    *in_FS_OFFSET = (int *)&local_14;
    local_8 = 0x0;
    BVar2 = __ValidateImageBase((PBYTE)&IMAGE_DOS_HEADER_10000000);
    if (BVar2 != 0x0) {
        p_Var3 = __FindPESection((PBYTE)&IMAGE_DOS_HEADER_10000000,(DWORD_PTR)(pTarget + -0x10000000));
        if (p_Var3 != NULL) {
            uVar1 = p_Var3->Characteristics;
            *in_FS_OFFSET = local_14;
            return ~(uVar1 >> 0x1f) & 0x1;
        }
    }
    *in_FS_OFFSET = local_14;
    return 0x0;
}



// Library Function - Single Match
//  __ValidateImageBase
// 
// Libraries: Visual Studio 2017 Release, Visual Studio 2019 Release

BOOL __cdecl __ValidateImageBase(PBYTE pImageBase)

{
    if (((*(short *)pImageBase == 0x5a4d) && (*(int *)(pImageBase + *(int *)(pImageBase + 0x3c)) == 0x4550)) && (*(short *)((int)(pImageBase + *(int *)(pImageBase + 0x3c)) + 0x18) == 0x10b)) {
        return 0x1;
    }
    return 0x0;
}



undefined4 * __thiscall FUN_1000ced3(void *this,byte param_1)

{
    *(undefined ***)this = type_info::vftable;
    if ((param_1 & 0x1) != 0x0) {
        FUN_1000cf80(this);
    }
    return (undefined4 *)this;
}



// WARNING: This is an inlined function
// Library Function - Single Match
//  __EH_epilog3
// 
// Libraries: Visual Studio 2005, Visual Studio 2008, Visual Studio 2010, Visual Studio 2012

void __EH_epilog3(void)

{
    undefined4 *unaff_EBP;
    undefined4 *in_FS_OFFSET;
    undefined4 unaff_retaddr;
    
    *in_FS_OFFSET = unaff_EBP[-0x3];
    *unaff_EBP = unaff_retaddr;
    return;
}



// WARNING: This is an inlined function
// WARNING: Unable to track spacebase fully for stack
// WARNING: Variable defined which should be unmapped: param_1
// Library Function - Single Match
//  __EH_prolog3
// 
// Libraries: Visual Studio 2005, Visual Studio 2008, Visual Studio 2010, Visual Studio 2012

void __cdecl __EH_prolog3(int param_1)

{
    int iVar1;
    undefined4 unaff_EBX;
    undefined4 unaff_ESI;
    undefined4 unaff_EDI;
    int *in_FS_OFFSET;
    undefined4 unaff_retaddr;
    uint auStack28 [0x5];
    undefined local_8 [0x8];
    
    iVar1 = -param_1;
    *(undefined4 *)((int)auStack28 + iVar1 + 0x10) = unaff_EBX;
    *(undefined4 *)((int)auStack28 + iVar1 + 0xc) = unaff_ESI;
    *(undefined4 *)((int)auStack28 + iVar1 + 0x8) = unaff_EDI;
    *(uint *)((int)auStack28 + iVar1 + 0x4) = DAT_10015124 ^ (uint)&param_1;
    *(undefined4 *)((int)auStack28 + iVar1) = unaff_retaddr;
    *in_FS_OFFSET = (int)local_8;
    return;
}



// WARNING: This is an inlined function
// WARNING: Unable to track spacebase fully for stack
// WARNING: Variable defined which should be unmapped: param_1
// Library Function - Single Match
//  __EH_prolog3_catch
// 
// Libraries: Visual Studio 2005, Visual Studio 2008, Visual Studio 2010, Visual Studio 2012

void __cdecl __EH_prolog3_catch(int param_1)

{
    int iVar1;
    undefined4 unaff_EBX;
    undefined4 unaff_ESI;
    undefined4 unaff_EDI;
    int *in_FS_OFFSET;
    undefined4 unaff_retaddr;
    uint auStack28 [0x5];
    undefined local_8 [0x8];
    
    iVar1 = -param_1;
    *(undefined4 *)((int)auStack28 + iVar1 + 0x10) = unaff_EBX;
    *(undefined4 *)((int)auStack28 + iVar1 + 0xc) = unaff_ESI;
    *(undefined4 *)((int)auStack28 + iVar1 + 0x8) = unaff_EDI;
    *(uint *)((int)auStack28 + iVar1 + 0x4) = DAT_10015124 ^ (uint)&param_1;
    *(undefined4 *)((int)auStack28 + iVar1) = unaff_retaddr;
    *in_FS_OFFSET = (int)local_8;
    return;
}



void __cdecl FUN_1000cf80(LPVOID param_1)

{
    thunk_FUN_1000517f(param_1);
    return;
}



// WARNING: This is an inlined function
// WARNING: Function: __alloca_probe replaced with injection: alloca_probe
// Library Function - Single Match
//  __alloca_probe_16
// 
// Library: Visual Studio

uint __alloca_probe_16(undefined1 param_1)

{
    uint in_EAX;
    uint uVar1;
    
    uVar1 = 0x4 - in_EAX & 0xf;
    return in_EAX + uVar1 | -(uint)CARRY4(in_EAX,uVar1);
}



// WARNING: This is an inlined function
// WARNING: Function: __alloca_probe replaced with injection: alloca_probe
// Library Function - Single Match
//  __alloca_probe_8
// 
// Library: Visual Studio

uint __alloca_probe_8(undefined1 param_1)

{
    uint in_EAX;
    uint uVar1;
    
    uVar1 = 0x4 - in_EAX & 0x7;
    return in_EAX + uVar1 | -(uint)CARRY4(in_EAX,uVar1);
}



// WARNING: This is an inlined function
// Library Function - Single Match
//  __chkstk
// 
// Library: Visual Studio 2019 Release

void __alloca_probe(void)

{
    undefined *in_EAX;
    undefined4 *puVar1;
    undefined4 *puVar2;
    undefined4 unaff_retaddr;
    undefined auStack4 [0x4];
    
    puVar2 = (undefined4 *)((int)&stack0x00000000 - (int)in_EAX & ~-(uint)(&stack0x00000000 < in_EAX));
    for (puVar1 = (undefined4 *)((uint)auStack4 & 0xfffff000); puVar2 < puVar1; puVar1 = puVar1 + -0x400) {
    }
    *puVar2 = unaff_retaddr;
    return;
}



void __cdecl thunk_FUN_1000517f(LPVOID param_1)

{
    FUN_10005f59(param_1);
    return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address
// Library Function - Single Match
//  __filter_x86_sse2_floating_point_exception_default
// 
// Library: Visual Studio 2019 Release

int __cdecl __filter_x86_sse2_floating_point_exception_default(int param_1)

{
    uint uVar1;
    uint in_MXCSR;
    
    if ((_DAT_10015adc < 0x1) || ((param_1 != -0x3ffffd4c && (param_1 != -0x3ffffd4b)))) {
        return param_1;
    }
    uVar1 = in_MXCSR ^ 0x3f;
    if ((uVar1 & 0x81) != 0x0) {
        if ((uVar1 & 0x204) == 0x0) {
            return -0x3fffff72;
        }
        if ((uVar1 & 0x102) != 0x0) {
            if ((uVar1 & 0x408) == 0x0) {
                return -0x3fffff6f;
            }
            if ((uVar1 & 0x810) != 0x0) {
                if ((uVar1 & 0x1020) != 0x0) {
                    return param_1;
                }
                return -0x3fffff71;
            }
            return -0x3fffff6d;
        }
    }
    return -0x3fffff70;
}



void entry(void)

{
                    // WARNING: Could not recover jumptable at 0x1000d16c. Too many branches
                    // WARNING: Treating indirect jump as call
    _CorDllMain();
    return;
}


