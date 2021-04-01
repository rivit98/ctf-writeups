//----- (0000000000400807) ----------------------------------------------------
int __cdecl main(int argc, const char **argv, const char **envp)
{
  char *v3; // rax
  char v5; // [rsp+1Fh] [rbp-A1h] BYREF
  int v6; // [rsp+20h] [rbp-A0h] BYREF
  int i; // [rsp+24h] [rbp-9Ch]
  char *v8; // [rsp+28h] [rbp-98h]
  char *dest; // [rsp+30h] [rbp-90h]
  FILE *stream; // [rsp+38h] [rbp-88h]
  char *v11; // [rsp+40h] [rbp-80h]
  const char *v12; // [rsp+48h] [rbp-78h]
  char src[32]; // [rsp+50h] [rbp-70h] BYREF
  char s[72]; // [rsp+70h] [rbp-50h] BYREF
  unsigned __int64 v15; // [rsp+B8h] [rbp-8h]

  v15 = __readfsqword(0x28u);
  setbuf(_bss_start, 0LL);
  stream = fopen("flag.txt", "r");
  fgets(s, 64, stream);
  strcpy(src, "this is a random string.");
  v8 = 0LL;
  for ( i = 0; i <= 6; ++i )
  {
    dest = (char *)malloc(0x80uLL);
    if ( !v8 )
      v8 = dest;
    v3 = dest;
    *(_QWORD *)dest = 0x73746172676E6F43LL;
    strcpy(v3 + 8, "! Your flag is: ");
    strcat(dest, s);
  }
  v11 = (char *)malloc(0x80uLL);
  strcpy(v11, "Sorry! This won't help you: ");
  strcat(v11, src);
  free(dest);
  free(v11);
  v6 = 0;
  v5 = 0;
  puts("You may edit one byte in the program.");
  printf("Address: ");
  __isoc99_scanf("%d", &v6);
  printf("Value: ");
  __isoc99_scanf(" %c", &v5);
  v8[v6] = v5;
  v12 = (const char *)malloc(0x80uLL);
  puts(v12 + 16);
  return 0;
}