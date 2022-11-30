int __cdecl main(int argc, const char **argv, const char **envp)
{
  FILE *v4; // rbx

  setbuf(_bss_start, 0LL);
  printf(
    "We are currently in need of a new house for our restaurant.\n"
    "Can you help us build it?\n"
    "Here is your foundation: %lx\n",
    _bss_start);
  if ( read(0, _bss_start, 0xE0uLL) != 0xE0 )
    return -1;
  v4 = _bss_start;
  v4->__pad2 = calloc(1uLL, 0xE8uLL); // wide data
  puts(byte_207C);
  return 0;
}
