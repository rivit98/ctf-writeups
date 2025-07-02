#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(){ 
    srand(0x7b);
    for(int i = 0; i < 30; i++) {
        int a = (uint16_t)rand() | (rand() << 16);
        printf("%x\n", a);
    }
}