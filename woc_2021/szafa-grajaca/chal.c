//----- (00000000004011B0) ----------------------------------------------------
void __noreturn admin()
{
  char *envp[2]; // [rsp+10h] [rbp-30h] BYREF
  char *argv[4]; // [rsp+20h] [rbp-20h] BYREF

  argv[0] = "/bin/cat";
  argv[1] = "/flag";
  argv[2] = 0LL;
  envp[0] = "PATH=/usr/local/sbin/:/usr/local/bin:/usr/sbin:/usr/bin:/sbin";
  envp[1] = 0LL;
  execve("/bin/cat", argv, envp);
  exit(0);
}
// 4011B0: using guessed type void __fastcall __noreturn admin();

//----- (0000000000401220) ----------------------------------------------------
int __cdecl main(int argc, const char **argv, const char **envp)
{
  setbuf(_bss_start, 0LL);
  puts("Wybierz opcje:");
  puts("1. Zagraj");
  puts("2. Pokaz liste piosenek");
  puts("3. Wylacz");
  choice();
  return 0;
}

//----- (00000000004012B0) ----------------------------------------------------
__int64 choice()
{
  int v1; // [rsp+34h] [rbp-5Ch] BYREF
  void (__fastcall __noreturn *v2)(); // [rsp+38h] [rbp-58h]
  char *s; // [rsp+40h] [rbp-50h] BYREF
  char *v4; // [rsp+48h] [rbp-48h]
  char *v5; // [rsp+50h] [rbp-40h]
  char *v6; // [rsp+58h] [rbp-38h]
  char s1[8]; // [rsp+68h] [rbp-28h] BYREF
  char v8[16]; // [rsp+70h] [rbp-20h] BYREF
  unsigned __int64 v9; // [rsp+88h] [rbp-8h]

  v9 = __readfsqword(0x28u);
  s = "When the system goes down";
  v4 = "Kill da process";
  v5 = "Smile to the zombie port thats creepin' around";
  v6 = "Abducted by the deamons";
  v1 = 0;
  strcpy(v8, "This is so deep");
  printf("> ");
  gets(s1);
  while ( strcmp(s1, "3") )
  {
    switch ( s1[0] )
    {
      case '1':
        puts("Playing all songs. Shuffled.");
        break;
      case '2':
        puts(s);
        puts(v4);
        puts(v5);
        puts(v6);
        break;
      case '4':
        v2 = admin;
        printf(
          "To jest menu debugowe. Funkcje administratorskie dostepne: %p\n, adres pierwszej piosenki to %p\n",
          admin,
          s);
        printf("Adres ktorej piosenki chcesz sprawdzic?\n");
        __isoc99_scanf("%i", &v1);
        printf("Piosenka zapisana w %p\n", (&s)[v1]);
        printf("Nadpisywanie adresu: ");
        __isoc99_scanf("%p", &(&s)[v1]);
        break;
    }
    printf("> ");
    gets(s1);
  }
  return 0LL;
}
