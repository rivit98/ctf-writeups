char __thiscall sub_402090(char *this, _DWORD *a2, int a3, int a4, int a5, int a6)
{
  int Error; // eax
  int v8; // eax
  _DWORD *v10; // eax
  int Window; // eax
  int v12; // eax
  int v13; // eax
  int Renderer; // eax
  int v15; // esi
  int v16; // eax
  int v17; // esi
  _DWORD *v18; // esi
  int v19; // esi
  int v20; // [esp-28h] [ebp-2Ch]

  if ( SDL_Init(32) || IMG_Init(2) == -1 || TTF_Init() == -1 )
  {
    Error = SDL_GetError(sub_4011F0);
    v8 = sub_401000(std::cerr, Error);
    std::ostream::operator<<(v8);
    *this = 0;
    return 0;
  }
  else
  {
    v10 = a2;
    if ( a2[5] >= 0x10u )
      v10 = (_DWORD *)*a2;
    Window = SDL_CreateWindow(v10, a3, a4, a5, a6, 0);
    *((_DWORD *)this + 1) = Window;
    if ( Window && (Renderer = SDL_CreateRenderer(Window, -1, 0), (*((_DWORD *)this + 2) = Renderer) != 0) )
    {
      SDL_SetRenderDrawColor(Renderer, 50, 50, 150, 255);
      *(_WORD *)this = 1;
      *((_DWORD *)this + 89) = 0;
      SDL_DisplayString((void **)this + 68, &unk_40426C, 0);
      this[345] = 0;
      SDL_DisplayString((void **)this + 74, &unk_40426C, 0);
      strcpy(this + 92, "gimme flag pls?");
      *((_DWORD *)this + 90) = 0xFFFFFF;
      *((_DWORD *)this + 91) = TTF_OpenFont("assets/OpenSans_regular.ttf", 12);
      v15 = IMG_Load("assets/ball_paint.png");
      *((_DWORD *)this + 27) = SDL_CreateTextureFromSurface(*((_DWORD *)this + 2), v15);
      SDL_FreeSurface(v15);
      v16 = TTF_OpenFont("assets/NotoSans_Regular.ttf", 12);
      v20 = *((_DWORD *)this + 90);
      *((_DWORD *)this + 92) = v16;
      v17 = TTF_RenderText_Solid(v16, "Press arrow keys to shake the ball", v20);
      *((_DWORD *)this + 28) = SDL_CreateTextureFromSurface(*((_DWORD *)this + 2), v17);
      SDL_FreeSurface(v17);
      v18 = this + 224;
      SDL_DisplayString((void **)this + 56, "Start typing your question (max. 75 characters): ", 0x31u);
      SDL_DisplayString((void **)this + 62, &unk_40426C, 0);
      if ( *((_DWORD *)this + 61) >= 0x10u )
        v18 = (_DWORD *)*v18;
      v19 = TTF_RenderText_Solid(*((_DWORD *)this + 92), v18, *((_DWORD *)this + 90));
      *((_DWORD *)this + 29) = SDL_CreateTextureFromSurface(*((_DWORD *)this + 2), v19);
      SDL_FreeSurface(v19);
      this[344] = 1;
      SDL_StartTextInput();
      return 1;
    }
    else
    {
      v12 = SDL_GetError(sub_4011F0);
      v13 = sub_401000(std::cerr, v12);
      std::ostream::operator<<(v13);
      return 0;
    }
  }
}

_DWORD *__thiscall sub_4024E0(int this)
{
  char v2; // al
  _BYTE *v3; // ebx
  _DWORD *v4; // esi
  _DWORD *v5; // eax
  _DWORD *v6; // eax
  _DWORD *result; // eax
  int v8; // eax
  _DWORD *v9; // ecx
  _DWORD *v10; // ebx
  int TextureFromSurface; // eax
  _BYTE *v12; // ecx
  _DWORD *v13; // ecx
  _DWORD *v14; // ecx
  _DWORD *v15; // ecx
  _DWORD *v16; // ecx
  _DWORD *v17; // ecx
  _DWORD *v18; // ecx
  _DWORD *v19; // ecx
  _DWORD *v20; // ecx
  const char *v21; // ecx
  void *v22; // [esp-18h] [ebp-3Ch]
  int v23; // [esp-14h] [ebp-38h]
  int v24; // [esp-10h] [ebp-34h]
  int v25; // [esp-Ch] [ebp-30h]
  int v26; // [esp-8h] [ebp-2Ch]
  int v27; // [esp-4h] [ebp-28h]
  _DWORD *v28; // [esp+Ch] [ebp-18h]
  _BYTE *v29; // [esp+10h] [ebp-14h]
  _DWORD *v30; // [esp+14h] [ebp-10h]
  _BYTE *v31; // [esp+18h] [ebp-Ch]
  _DWORD *v32; // [esp+1Ch] [ebp-8h]
  char v33; // [esp+23h] [ebp-1h]

  v2 = *(_BYTE *)(this + 356);
  *(_DWORD *)(this + 156) = 400;
  *(_DWORD *)(this + 152) = 450;
  v33 = v2;
  if ( v2
    && (v3 = (_BYTE *)(this + 357), *(_BYTE *)(this + 357))
    && (v31 = (_BYTE *)(this + 358), *(_BYTE *)(this + 358))
    && (v29 = (_BYTE *)(this + 359), *(_BYTE *)(this + 359)) )
  {
    v28 = (_DWORD *)(this + 144);
    v30 = (_DWORD *)(this + 144);
    v4 = (_DWORD *)(this + 272);
    v32 = (_DWORD *)(this + 148);
    v5 = (_DWORD *)(this + 148);
  }
  else
  {
    v30 = (_DWORD *)(this + 144);
    v29 = (_BYTE *)(this + 359);
    v6 = (_DWORD *)(this + 148);
    *(_DWORD *)(this + 144) = 150;
    v28 = (_DWORD *)(this + 144);
    v4 = (_DWORD *)(this + 272);
    *(_DWORD *)(this + 148) = 0;
    v3 = (_BYTE *)(this + 357);
    v31 = (_BYTE *)(this + 358);
    v32 = (_DWORD *)(this + 148);
    if ( !v33 )
      goto LABEL_9;
    v5 = (_DWORD *)(this + 148);
  }
  *v5 -= 20;
  sub_401780(v4, "U", 1u);
  v6 = v32;
LABEL_9:
  if ( *v3 )
  {
    *v6 += 20;
    sub_401780(v4, "D", 1u);
  }
  if ( *v31 )
  {
    *v30 -= 20;
    sub_401780(v4, "L", 1u);
  }
  result = v29;
  if ( *v29 )
  {
    *v28 += 20;
    result = sub_401780(v4, "R", 1u);
  }
  if ( *(_BYTE *)(this + 344) )
  {
    if ( *(_DWORD *)(this + 120) )
    {
      SDL_DestroyTexture(*(_DWORD *)(this + 120));
      *(_DWORD *)(this + 120) = 0;
      *(_DWORD *)(this + 348) = 0;
      *(_DWORD *)(this + 352) = 0;
    }
    v8 = TTF_OpenFont("assets/NotoSans_Regular.ttf", 18);
    v9 = (_DWORD *)(this + 248);
    if ( *(_DWORD *)(this + 268) >= 0x10u )
      v9 = (_DWORD *)*v9;
    result = (_DWORD *)TTF_RenderText_Solid(v8, v9, 7827430);
    v10 = result;
    if ( result )
    {
      TextureFromSurface = SDL_CreateTextureFromSurface(*(_DWORD *)(this + 8), result);
      *(_DWORD *)(this + 120) = TextureFromSurface;
      if ( TextureFromSurface )
      {
        *(_DWORD *)(this + 348) = v10[2];
        *(_DWORD *)(this + 352) = v10[3];
      }
      result = (_DWORD *)SDL_FreeSurface(v10);
    }
  }
  if ( *(_BYTE *)(this + 345) )
  {
    result = (_DWORD *)v4[5];
    v12 = v4;
    if ( (unsigned int)result >= 0x10 )
      v12 = (_BYTE *)*v4;
    if ( *v12 == 'L' )
    {
      v13 = v4;
      if ( (unsigned int)result >= 0x10 )
        v13 = (_DWORD *)*v4;
      if ( *((_BYTE *)v13 + 1) == 'L' )
      {
        v14 = v4;
        if ( (unsigned int)result >= 0x10 )
          v14 = (_DWORD *)*v4;
        if ( *((_BYTE *)v14 + 2) == 'U' )
        {
          v15 = v4;
          if ( (unsigned int)result >= 0x10 )
            v15 = (_DWORD *)*v4;
          if ( *((_BYTE *)v15 + 3) == 'R' )
          {
            v16 = v4;
            if ( (unsigned int)result >= 0x10 )
              v16 = (_DWORD *)*v4;
            if ( *((_BYTE *)v16 + 4) == 'U' )
            {
              v17 = v4;
              if ( (unsigned int)result >= 0x10 )
                v17 = (_DWORD *)*v4;
              if ( *((_BYTE *)v17 + 5) == 'L' )
              {
                v18 = v4;
                if ( (unsigned int)result >= 0x10 )
                  v18 = (_DWORD *)*v4;
                if ( *((_BYTE *)v18 + 6) == 'D' )
                {
                  v19 = v4;
                  if ( (unsigned int)result >= 0x10 )
                    v19 = (_DWORD *)*v4;
                  if ( *((_BYTE *)v19 + 7) == 'U' )
                  {
                    v20 = v4;
                    if ( (unsigned int)result >= 0x10 )
                      v20 = (_DWORD *)*v4;
                    if ( *((_BYTE *)v20 + 8) == 'L' )
                    {
                      v21 = (const char *)(this + 248);
                      if ( *(_DWORD *)(this + 268) >= 0x10u )
                        v21 = *(const char **)v21;
                      result = (_DWORD *)strncmp(v21, (const char *)(this + 92), 0xFu);
                      if ( !result )
                      {
                        sub_401220(v4);
                        return (_DWORD *)sub_401A10(v22, v23, v24, v25, v26, v27);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return result;
}

