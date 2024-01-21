#pragma once

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t   u8;
typedef int8_t    i8;
typedef uint16_t  u16;
typedef int16_t   i16;
typedef uint32_t  u32;
typedef int32_t   i32;
typedef uint64_t  u64;
typedef int64_t   i64;

#define LOG(f_, ...) printf(("[*] " f_), __VA_ARGS__)


#define FAIL(prefix_)       \
    do                      \
    {                       \
        perror(prefix_);    \
        exit(errno);        \
    } while (0)


#define CHECKED_CALL(func)      \
    do                          \
    {                           \
        if((func) < 0)          \
            FAIL(#func);        \
    } while (0)


#define IMPORT_BIN(sect, file, sym) asm (\
".section " #sect "\n"                  /* Change section */\
".balign 8\n"                           /* Word alignment */\
".global " #sym "\n"                    /* Export the object address */\
#sym ":\n"                              /* Define the object label */\
".incbin \"" file "\"\n"                /* Import the file */\
"sizeof_" #sym ": .quad . - " #sym "\n" /* Define the object size */\
".balign 8\n"                           /* Word alignment */\
".section \".text\"\n")                 /* Restore section */

/*
IMPORT_BIN(".rodata", "tar", tar_prog);
extern char tar_prog[];
extern int sizeof_tar_prog;
*/

// https://gist.github.com/ccbrown/9722406
void hexdump(const void* data, size_t size) {
    char ascii[17];
    size_t i, j;
    ascii[16] = '\0';
    for (i = 0; i < size; ++i) {
        printf("%02X ", ((unsigned char*)data)[i]);
        if (((unsigned char*)data)[i] >= ' ' && ((unsigned char*)data)[i] <= '~') {
            ascii[i % 16] = ((unsigned char*)data)[i];
        } else {
            ascii[i % 16] = '.';
        }
        if ((i+1) % 8 == 0 || i+1 == size) {
            printf(" ");
            if ((i+1) % 16 == 0) {
                printf("|  %s \n", ascii);
            } else if (i+1 == size) {
                ascii[(i+1) % 16] = '\0';
                if ((i+1) % 16 <= 8) {
                    printf(" ");
                }
                for (j = (i+1) % 16; j < 16; ++j) {
                    printf("   ");
                }
                printf("|  %s \n", ascii);
            }
        }
    }
}