char sub_46F410()
{
  int v0; // eax
  int v1; // ebx
  int v3; // eax
  int v4; // edi
  int v5; // esi
  int v6; // esi
  int v7; // ebp
  int v8; // esi
  int v9; // ebp
  int v10; // esi
  int v11; // ebp
  int v12; // esi
  int v13; // ebp
  int v14; // esi
  int v15; // ebp
  int v16; // esi
  int v17; // ebp
  int v18; // esi
  int v19; // ebp
  int v20; // esi
  int v21; // ebp
  int v22; // esi
  int v23; // ebp

  v0 = sub_50A1A0(aCrtraitsTxt);
  v1 = v0;
  if ( !v0 )
    return 0;
  v3 = *(_DWORD *)(v0 + 32);
  if ( v3 && (int)((*(_DWORD *)(v1 + 36) - v3) & 0xFFFFFFFC) >= 604 )
  {
    v4 = 0;
    v5 = 2;
    do
      sub_46F570(v4++, *(_DWORD *)(*(_DWORD *)(v1 + 32) + 4 * v5++));
    while ( v4 < 14 );
    v6 = v5 + 3;
    v7 = 14;
    do
    {
      sub_46F570(v4++, *(_DWORD *)(*(_DWORD *)(v1 + 32) + 4 * v6++));
      --v7;
    }
    while ( v7 );
    v8 = v6 + 3;
    v9 = 14;
    do
    {
      sub_46F570(v4++, *(_DWORD *)(*(_DWORD *)(v1 + 32) + 4 * v8++));
      --v9;
    }
    while ( v9 );
    v10 = v8 + 3;
    v11 = 14;
    do
    {
      sub_46F570(v4++, *(_DWORD *)(*(_DWORD *)(v1 + 32) + 4 * v10++));
      --v11;
    }
    while ( v11 );
    v12 = v10 + 3;
    v13 = 14;
    do
    {
      sub_46F570(v4++, *(_DWORD *)(*(_DWORD *)(v1 + 32) + 4 * v12++));
      --v13;
    }
    while ( v13 );
    v14 = v12 + 3;
    v15 = 14;
    do
    {
      sub_46F570(v4++, *(_DWORD *)(*(_DWORD *)(v1 + 32) + 4 * v14++));
      --v15;
    }
    while ( v15 );
    v16 = v14 + 3;
    v17 = 14;
    do
    {
      sub_46F570(v4++, *(_DWORD *)(*(_DWORD *)(v1 + 32) + 4 * v16++));
      --v17;
    }
    while ( v17 );
    v18 = v16 + 3;
    v19 = 14;
    do
    {
      sub_46F570(v4++, *(_DWORD *)(*(_DWORD *)(v1 + 32) + 4 * v18++));
      --v19;
    }
    while ( v19 );
    v20 = v18 + 3;
    v21 = 6;
    do
    {
      sub_46F570(v4++, *(_DWORD *)(*(_DWORD *)(v1 + 32) + 4 * v20++));
      --v21;
    }
    while ( v21 );
    v22 = 4 * (v20 + 3);
    v23 = 4;
    do
    {
      sub_46F570(v4++, *(_DWORD *)(v22 + *(_DWORD *)(v1 + 32)));
      v22 += 4;
      --v23;
    }
    while ( v23 );
    sub_50AFF0(v1);
    return 1;
  }
  else
  {
    sub_50AFF0(v1);
    return 0;
  }
}
