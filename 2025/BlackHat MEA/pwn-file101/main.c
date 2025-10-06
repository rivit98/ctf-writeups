#include <stdio.h>

void main() {
  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
  puts("stdout:");
  scanf("%224s", (char*)stdout);
  puts("stderr:");
  scanf("%224s", (char*)stderr);
}
