//----- (0000000000401190) ----------------------------------------------------
__int64 secret()
{
  char *envp[2]; // [rsp+10h] [rbp-30h] BYREF
  char *argv[4]; // [rsp+20h] [rbp-20h] BYREF

  argv[0] = "/bin/cat";
  argv[1] = "/flag";
  argv[2] = 0LL;
  envp[0] = "PATH=/usr/local/sbin/:/usr/local/bin:/usr/sbin:/usr/bin:/sbin";
  envp[1] = 0LL;
  execve("/bin/cat", argv, envp);
  return 0LL;
}
// 401190: using guessed type __int64 __fastcall secret();

//----- (0000000000401200) ----------------------------------------------------
int __cdecl main(int argc, const char **argv, const char **envp)
{
  setbuf(_bss_start, 0LL);
  puts("Tekst na pudelku: Czy potrawisz odkryc moj sekret??");
  guard();
  puts("...\n");
  return 0;
}

//----- (0000000000401260) ----------------------------------------------------
__int64 guard()
{
  char src[16]; // [rsp+20h] [rbp-20h] BYREF
  char dest[8]; // [rsp+30h] [rbp-10h] BYREF
  unsigned __int64 v3; // [rsp+38h] [rbp-8h]

  v3 = __readfsqword(0x28u);
  gets(src);
  if ( src[0] == 76 && src[1] == 97 && src[2] == 76 && src[3] == 97 && src[4] == 76 && src[5] == 97 && src[6] == 105 )
  {
    strncpy(dest, src, 9uLL);
    printf(
      "\"%s\" *Magiczny dzwiek wydobywa sie z pozytywki, chyba juz wiem jak dobrac sie do sekretu: %p* \n",
      dest,
      secret);
    puts("*Niech zagra jeszcze raz, tym razem odkrywajac wszystkie sekrety*\n");
    gets(dest);
  }
  return 0LL;
}
