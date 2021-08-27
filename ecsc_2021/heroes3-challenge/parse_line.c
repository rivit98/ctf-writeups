unsigned int __fastcall sub_46F570(int a1, int a2)
{
  char *v3; // ebp
  char *v5; // edx
  char *v6; // edx
  char *v7; // edx
  const char *v8; // edi
  unsigned int result; // eax

  v3 = (char *)&unk_5D3BE0 + 96 * a1;
  if ( (byte_5FA198 & 1) == 0 )
  {
    byte_5FA198 |= 1u;
    `eh vector constructor iterator'(dword_5F9FB0, 4u, 122, unknown_libname_2, sub_4C2B30);
    atexit(sub_46F8E0);
  }
  v5 = (char *)operator new(strlen(**(const char ***)(a2 + 4)) + 1);
  dword_5F9FB0[a1] = (int)v5;
  strcpy(v5, **(const char ***)(a2 + 4));
  *((_DWORD *)v3 + 5) = dword_5F9FB0[a1];
  if ( (byte_5FA198 & 2) == 0 )
  {
    byte_5FA198 |= 2u;
    `eh vector constructor iterator'(dword_5F9DC8, 4u, 122, unknown_libname_2, sub_4C2B30);
    atexit(sub_46F8C0);
  }
  v6 = (char *)operator new(strlen(*(const char **)(*(_DWORD *)(a2 + 4) + 4)) + 1);
  dword_5F9DC8[a1] = (int)v6;
  strcpy(v6, *(const char **)(*(_DWORD *)(a2 + 4) + 4));
  *((_DWORD *)v3 + 6) = dword_5F9DC8[a1];
  *((_WORD *)v3 + 16) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 8));
  *((_WORD *)v3 + 17) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 12));
  *((_WORD *)v3 + 18) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 16));
  *((_WORD *)v3 + 19) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 20));
  *((_WORD *)v3 + 20) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 24));
  *((_WORD *)v3 + 21) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 28));
  *((_WORD *)v3 + 22) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 32));
  *((_WORD *)v3 + 23) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 36));
  *((_WORD *)v3 + 24) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 40));
  *((_DWORD *)v3 + 13) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 44));
  *((_WORD *)v3 + 28) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 48));
  *((_DWORD *)v3 + 15) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 52));
  *((_DWORD *)v3 + 16) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 56));
  *((_DWORD *)v3 + 17) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 60));
  *((_DWORD *)v3 + 18) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 64));
  *((_DWORD *)v3 + 19) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 68));
  *((_DWORD *)v3 + 20) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 72));
  *((_DWORD *)v3 + 21) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 76));
  *((_DWORD *)v3 + 22) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 80));
  *((_DWORD *)v3 + 23) = atoi(*(const char **)(*(_DWORD *)(a2 + 4) + 84));
  if ( (byte_5FA198 & 4) == 0 )
  {
    byte_5FA198 |= 4u;
    `eh vector constructor iterator'(dword_5F9BE0, 4u, 122, unknown_libname_2, sub_4C2B30);
    atexit(sub_46F8A0);
  }
  v7 = (char *)operator new(strlen(*(const char **)(*(_DWORD *)(a2 + 4) + 88)) + 1);
  dword_5F9BE0[a1] = (int)v7;
  v8 = *(const char **)(*(_DWORD *)(a2 + 4) + 88);
  result = strlen(v8) + 1;
  qmemcpy(v7, v8, result);
  *((_DWORD *)v3 + 7) = dword_5F9BE0[a1];
  return result;
}
