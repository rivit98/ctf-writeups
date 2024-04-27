#include <stdio.h>
#include <stdlib.h>

int main(int a, char*argv[]) {
    int seed = atoi(argv[1]);
    srand(seed);

    FILE* f = fopen("./seed_data", "wb");
    if(!f){
        perror("fopen");
        return;
    }

    for (size_t i = 0; i <= 0x3FFFFFF; i++)
    {
        int ptr = rand();
        fwrite(&ptr, sizeof(ptr), 1, f);
    }
    
    fclose(f);
}
