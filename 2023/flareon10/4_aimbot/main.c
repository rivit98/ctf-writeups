#include <windows.h>
#include <stdio.h>

int main(int argc)
{
    if(argc > 1){
        HINSTANCE hGetProcIDDLL = LoadLibrary("X:\\flareon10\\4_aimbot\\aimbot.dll");

        if (!hGetProcIDDLL) {
            puts("could not load the dynamic library");
            return EXIT_FAILURE;
        }
    }

  while(1){
    Sleep(0x100);
  }

  return EXIT_SUCCESS;
}
