LRESULT __stdcall sub_4012C0(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  HDC v4; // eax
  HDC v5; // edi
  HANDLE ProcessHeap; // eax
  int v8; // edi
  unsigned int v9; // esi
  unsigned int v10; // ecx
  int v11; // edi
  int v12; // eax
  int v13; // esi
  HDC DC; // esi
  void *v15; // [esp-4h] [ebp-150h]
  CHAR String[260]; // [esp+8h] [ebp-144h] BYREF
  struct tagPAINTSTRUCT Paint; // [esp+10Ch] [ebp-40h] BYREF

  memset(String, 0, sizeof(String));
  if ( Msg > 0x111 )
  {
    if ( Msg == 512 )
    {
      _snprintf(String, 0x104u, "PixelPoker (%d,%d) - #%d/%d", (__int16)lParam, SHIWORD(lParam), tries, 10);
      SetWindowTextA(hWnd, String);
      return 0;
    }
    if ( Msg != 513 )
      return DefWindowProcW(hWnd, Msg, wParam, lParam);
    v8 = (__int16)lParam;
    if ( tries == 10 )
    {
      MessageBoxA(0, "Womp womp... :(", "Please play again!", 0);
      DestroyWindow(hWnd);
LABEL_30:
      _snprintf(String, 0x104u, "PixelPoker (%d,%d) - #%d/%d", v8, SHIWORD(lParam), tries, 10);
      SetWindowTextA(hWnd, String);
      DC = GetDC(hWnd);
      BitBlt(DC, 0, 0, dword_413280, cy, hdc, 0, 0, 0xCC0020u);
      ReleaseDC(hWnd, DC);
      return 0;
    }
    ++tries;
    v9 = dword_413280;
    if ( (__int16)lParam == dword_412004 % (unsigned int)dword_413280 ) // enter this if to show the flag
    {
      v10 = cy;
      if ( SHIWORD(lParam) == dword_412008 % (unsigned int)cy )
      {
        v11 = 0;
        if ( cy > 0 )
        {
          v12 = dword_413280;
          do
          {
            v13 = 0;
            if ( v12 > 0 )
            {
              do
              {
                sub_4015D0(v13, v11);
                v12 = dword_413280;
                ++v13;
              }
              while ( v13 < dword_413280 );
              v10 = cy;
            }
            ++v11;
          }
          while ( v11 < (int)v10 );
        }
        v8 = (__int16)lParam;
        goto LABEL_30;
      }
      v9 = dword_413280;
    }
    else
    {
      v10 = cy;
    }
    if ( (__int16)lParam < v9 && SHIWORD(lParam) < v10 )
      sub_4015D0((__int16)lParam, SHIWORD(lParam));
    goto LABEL_30;
  }
  if ( Msg == 273 )
  {
    if ( (unsigned __int16)wParam == 104 )
    {
      DialogBoxParamW(hInstance, (LPCWSTR)0x67, hWnd, DialogFunc, 0);
      return 0;
    }
    else if ( (unsigned __int16)wParam == 105 )
    {
      DestroyWindow(hWnd);
      return 0;
    }
    else
    {
      return DefWindowProcW(hWnd, 0x111u, wParam, lParam);
    }
  }
  if ( Msg != 2 )
  {
    if ( Msg == 15 )
    {
      v4 = BeginPaint(hWnd, &Paint);
      v5 = v4;
      if ( byte_412000 )
      {
        hdc = CreateCompatibleDC(v4);
        SelectObject(hdc, h);
        byte_412000 = 0;
      }
      BitBlt(v5, 0, 0, dword_413280, cy, hdc, 0, 0, 0xCC0020u);
      EndPaint(hWnd, &Paint);
      return 0;
    }
    return DefWindowProcW(hWnd, Msg, wParam, lParam);
  }
  DeleteDC(hdc);
  if ( lpMem )
  {
    v15 = lpMem;
    ProcessHeap = GetProcessHeap();
    HeapFree(ProcessHeap, 0, v15);
  }
  PostQuitMessage(0);
  return 0;
}
