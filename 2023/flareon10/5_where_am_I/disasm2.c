int start()
{
  char *table; // esi MAPDST
  int new_func_len; // edx
  int v3; // edi
  char *new_func; // esi
  int v5; // ecx

  for ( table = get_ret_addr(); *(_DWORD *)table != 0xD2A3FB95 || *((_WORD *)table + 4) != 0x4433; ++table )
    ;
  decode(table + 16, 8, table);
  new_func_len = *((_DWORD *)table + 4);
  v3 = *((_DWORD *)table + 5);
  new_func = table + 24;
  decode(new_func, new_func_len, table);
  return ((int (__fastcall *)(int))&new_func[v3])(v5);
}

void __fastcall decode(char *data_ptr, int data_len, char *table)
{
  char v3; // al
  char *v4; // edi
  int idx; // ecx
  char *i; // [esp+8h] [ebp-4h]

  idx = 0;
  for ( i = data_ptr; idx < data_len; data_ptr = i )
  {
    v4 = &data_ptr[idx];
    v3 = idx + table[idx % 16] - 10 * ((char)idx / 10) + 0x30;
    ++idx;
    *v4 ^= v3;
  }
}


char *__cdecl get_ret_addr()
{
  char *retaddr; // [esp+4h] [ebp+4h]

  return retaddr;
}
