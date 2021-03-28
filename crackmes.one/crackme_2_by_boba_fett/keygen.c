#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


uint32_t ascii_sum(const char *name);
char *left(char *name, int i);

void replace_dot_with_comma(char str[33]);

void main(int argc, char** argv){
    if(argc != 2){
        puts("Usage: keygen name");
        return;
    }

    char serial1_str[33];
    char serial2_str[33];
    const char* name = argv[1];
    uint32_t serial1 = ascii_sum(name);
    snprintf(serial1_str, 33, "%u", serial1);
    char *left3 = left(serial1_str, 3);

    uint32_t var_F8 = atoi(name) * 100;
    var_F8 += 15;
    uint32_t var_168 = atoi(left3);
    double serial2 = (double)(((var_F8 * var_168)) - 18) / var_168;

    printf("Name: %s\n", name);
    printf("serial1: %u\n", serial1);
    snprintf(serial2_str, 33, "%.7f", serial2);
    replace_dot_with_comma(serial2_str);
    printf("serial2: %s\n", serial2_str);
    free(left3);
}

void replace_dot_with_comma(char *str) {
    while(*str++){
        if(*str == '.'){
            *str = ',';
            return;
        }
    }
}

char *left(char *name, int i) {
    char *left_str = malloc(i + 1);
    strncpy(left_str, name, i);
    return left_str;
}

uint32_t ascii_sum(const char *name) {
    uint32_t len = strlen(name);
    uint32_t ret = 0;
    for (int i = 0; i < len; ++i) {
        ret += name[i];
    }

    return ret;
}
