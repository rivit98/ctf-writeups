#include <stdio.h>
#include <stdlib.h>
#define MEM_MAX 0x1000

char g_buf[MEM_MAX];
off_t g_cur;

static void win() {
  system("/bin/sh");
}

size_t getval(const char *msg) {
  size_t val;
  printf("%s", msg);
  if (scanf("%ld%*c", &val) != 1)
    exit(1);
  return val;
}

void do_seek() {
  off_t cur = getval("Position: ");
  if (cur >= MEM_MAX) {
    puts("[-] Invalid offset");
    return;
  }
  g_cur = cur;
  puts("[+] Done");
}

void do_write() {
  int size = getval("Size: ");
  if (g_cur + size > MEM_MAX) {
    puts("[-] Invalid size");
    return;
  }
  printf("Data: ");
  if (fread(g_buf + g_cur, sizeof(char), size, stdin) != size)
    exit(1);
  puts("[+] Done");
}

int main() {
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  puts("1. Seek\n2. Read\n3. Write");
  while (1) {
    switch (getval("> ")) {
      case 1: do_seek(); break;
      case 2: puts("You know what you wrote."); break;
      case 3: do_write(); break;
      default: return 0;
    }
  }
}
