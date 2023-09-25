#include <stdio.h>
#include <math.h>
#include <string.h>


char check[] = {0x5f, 0x40, 0x5a, 0x15, 0x75, 0x45, 0x62, 0x53, 0x75, 0x46, 0x52, 0x43, 0x5f, 0x75, 0x50, 0x52, 0x75,
                0x5f, 0x5c, 0x4f};
char *ASCII_UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // idb
char *ASCII_LOWER = "abcdefghijklmnopqrstuvwxyz"; // idb

int rot_n(char a1, int a2) {
    if (strchr(ASCII_UPPER, (char) a1))
        return (char) ASCII_UPPER[(a2 + (char) a1 - 65) % 26];
    if (strchr(ASCII_LOWER, (char) a1))
        return (char) ASCII_LOWER[(a2 + (char) a1 - 97) % 26];
    return a1;
}

//----- (0000000000001357) ----------------------------------------------------
int is_prime(int a1) {
    int i; // [rsp+1Ch] [rbp-4h]

    if (a1 <= 1)
        return 0LL;
    for (i = 2; i <= (int) sqrt((double) a1); ++i) {
        if (!(a1 % i))
            return 0LL;
    }
    return 1LL;
}

int main(int argc, const char **argv, const char **envp) {
    int i; // [rsp+8h] [rbp-F8h]
    unsigned int j; // [rsp+Ch] [rbp-F4h]
    char res[0x100];
    memset(res, 0, 0x100);

    for (i = 0; i < 0x14; ++i) {
        for (j = 4 * i; is_prime(j) != 1; ++j);

        for (int c = ' '; c < 0x7f; c++) {
            int after_rot = rot_n(c, j);
            int to_check = check[i] ^ 42;
            if (to_check == after_rot) {
                res[i] = c;
                printf("%d %c\n", i, c);
            }
        }
    }

    puts(res);
}
