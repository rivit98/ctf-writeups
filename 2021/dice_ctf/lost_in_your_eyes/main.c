#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "defs.h"
#include "data.h"

static const int REG1 = 0x1000a;
static const int REG2 = 0x4003; //uint32 reg?
static const int REG3 = 0x10008;
static const int REG4 = 0x10110;
static const int REG5 = 0x10010;
static const int REG6 = 0x8004;
static const int REG7 = 0x10009;
static const int REG8 = 0x1000c;
_DWORD char_array[4] = {40, 41, 38, 39}; // idb
                    //  (    )   &   '


/*

 mem[0,1,2] possibly state 'saving'

 */


uint32 mem_cnt = 0;

void dump_mem(char *mem) {
    char fname[64];
    sprintf(fname, "./mem/%d_m.bin", mem_cnt++);
    FILE *f = fopen(fname, "wb");
    if (!f) {
        printf("file open error: %s", fname);
        return;
    }

    fwrite(mem, 1, 0x10114, f);
    fclose(f);
}

void save_opcode(uint8 opcode) {
    char fname[64];
    sprintf(fname, "./mem/%d_o.bin", mem_cnt);
    FILE *f = fopen(fname, "wb");
    if (!f) {
        printf("file open error: %s", fname);
        return;
    }

    fputc(opcode, f);
    fclose(f);
}

int display_flag() {
    puts("flag!");
    return 0;
}

_QWORD *prepare_data() {
    _QWORD *v0; // rax
    _QWORD *v1; // r12
    _QWORD *result; // rax

    v0 = malloc(0x10114uLL);
    *v0 = 0LL;
    v1 = v0;
    memset(v0 + 1, 0, 0x10000uLL);
    *((_WORD *) v1 + REG6) = 0;
    *((_BYTE *) v1 + REG1) = 0;
    *((_DWORD *) v1 + REG2) = 1;
    memset(v1 + 0x2002, 0, 0x100uLL);
    result = v1;
    *((_BYTE *) v1 + REG4) = 0;
    return result;
}

char sub_558EB89A4420(unsigned __int8 *mem) {
    char result = 0; // al
    int v3; // mem[REG7]
    int v4; // mem[REG3]
    int v5; // mem[REG3] << 8;
    __int64 v6; // (mem[REG3] << 8) + mem[REG7]
    __int64 v7; // rax
    int v9; // edi
    __int64 v10; // rcx
    int v11; // eax
    unsigned __int8 v12; // si
    unsigned __int8 v13; // si

    v3 = mem[REG7];
    v4 = mem[REG3];
    v5 = v4 << 8;
    v6 = (v4 << 8) + v3;

    if (mem[v6 + 8] > 0x29u) // invalid opcode
        return 1;

    switch (mem[v6 + 8]) {
        case 0u:
            break;
        case 1u:
            mem[REG1] = 0;
            break;
        case 2u:
            mem[REG1] = 1;
            break;
        case 3u:
            mem[REG1] = 2;
            break;
        case 4u:
            mem[REG1] = 3;
            break;
        case 5u:
            mem[REG1] = 4;
            break;
        case 6u:
            mem[REG1] = 5;
            break;
        case 7u:
            mem[REG1] = 6;
            break;
        case 8u:
            mem[REG1] = 7;
            break;
        case 9u:
            mem[mem[REG1]] = *mem;
            break;
        case 0xAu:
            mem[mem[REG1]] = mem[1];
            break;
        case 0xBu:
            mem[mem[REG1]] = mem[2];
            break;
        case 0xCu:
            mem[mem[REG1]] = mem[3];
            break;
        case 0xDu:
            mem[mem[REG1]] = mem[4];
            break;
        case 0xEu:
            mem[mem[REG1]] = mem[5];
            break;
        case 0xFu:
            mem[mem[REG1]] = mem[6];
            break;
        case 0x10u:
            mem[mem[REG1]] = mem[7];
            break;
        case 0x11u:
            ++mem[mem[REG1]];
            break;
        case 0x12u:
            --mem[mem[REG1]];
            break;
        case 0x13u:
            mem[mem[REG1]] = mem[6] + mem[7];
            break;
        case 0x14u:
            mem[mem[REG1]] = mem[6] - mem[7];
            break;
        case 0x15u:
            mem[mem[REG1]] = mem[7] * mem[6];
            break;
        case 0x16u:
            mem[mem[REG1]] = mem[6] / mem[7];
            break;
        case 0x17u:
            mem[mem[REG1]] = mem[6] % mem[7];
            break;
        case 0x18u:
            mem[mem[REG1]] = ~mem[mem[REG1]];
            break;
        case 0x19u:
            mem[mem[REG1]] = -mem[mem[REG1]];
            break;
        case 0x1Au:
            mem[mem[REG1]] = mem[7] & mem[6];
            break;
        case 0x1Bu:
            mem[mem[REG1]] = mem[7] | mem[6];
            break;
        case 0x1Cu:
            mem[mem[REG1]] = mem[7] ^ mem[6];
            break;
        case 0x1Du:
            mem[mem[REG1]] = mem[6] == mem[7];
            break;
        case 0x1Eu:
            mem[mem[REG1]] = mem[6] < mem[7];
            break;
        case 0x1Fu:
            v11 = *((_DWORD *) mem + REG2);
            *mem = v4;
            mem[1] = v3;
            mem[2] = v11;
            break;
        case 0x20u:
            if ((mem[mem[REG1]] & 1) == 0) {
                break;
            }
//                return result;
            v10 = *((unsigned int *) mem + REG2);
            if ((_DWORD) v10 == 2) {
                v12 = v4 + 1;
                mem[REG3] = v12;
                v5 = v12 << 8;
                result = mem[v3 + 8 + v5] == char_array[v10];
                break;
            }
            if ((unsigned int) v10 <= 2) {
                if ((_DWORD) v10) { // 1
                    mem[REG7] = v3 + 1;
                    v3 = (unsigned __int8) (v3 + 1);
                } else { // 0
                    v13 = v4 - 1;
                    mem[REG3] = v13;
                    v5 = v13 << 8;
                }
                result = mem[v3 + 8 + v5] == char_array[v10];
                break;

            }
            result = 1;
            if ((_DWORD) v10 == 3) {
                mem[REG7] = v3 - 1;
                v3 = (unsigned __int8) (v3 - 1);
                result = mem[v3 + 8 + v5] == char_array[v10];
                break;

            }
            puts("reg2 not covered");
            break;
        case 0x21u:
            printf("256 * *mem + 8 + mem[1] = 0x%x\n", 256 * *mem + 8 + mem[1]);
            mem[mem[REG1]] = mem[256 * *mem + 8 + mem[1]];
            break;
        case 0x22u:
            mem[256 * *mem + 8 + mem[1]] = mem[mem[REG1]];
            break;
        case 0x23u:
            *((_WORD *) mem + REG6) = *(_WORD *) mem;
            *((_DWORD *) mem + REG2) = mem[2];
            break;
        case 0x24u:
            printf("Podaj znak: ");
            mem[mem[REG1]] = getc(stdin);
            break;
        case 0x25u:
            v7 = mem[REG4];
            mem[REG4] = v7 + 1;
            v9 = mem[mem[REG1]];
            mem[v7 + REG5] = v9;
            putc(v9, stdout);
            break;
        case 0x26u:
            *((_DWORD *) mem + REG2) = 0;
            break;
        case 0x27u:
            *((_DWORD *) mem + REG2) = 1;
            break;
        case 0x28u:
            *((_DWORD *) mem + REG2) = 2;
            break;
        case 0x29u:
            *((_DWORD *) mem + REG2) = 3;
            break;
    }

    if(mem[v6 + 8]){
        save_opcode(mem[v6 + 8]);
        dump_mem((char *) mem);
    }

    return result;
}

__int64 sub_558EB89A48D0(__int64 a1) {
    unsigned int v1; // eax

    LABEL_1:
    while (!sub_558EB89A4420((unsigned __int8 *) a1)) { //dopóki cos w 0x20 nie zmatchuje
        while (1) {
            v1 = *(_DWORD *) (a1 + (REG2 * 4)); //R8 == R2, state register

            if (v1 == 2) {
                ++*(_BYTE *) (a1 + REG3);
//                save_opcode(0x30);
//                dump_mem((char *) a1);

                goto LABEL_1;
            }
            if (v1 > 2)
                break;
            if (!v1) {
                --*(_BYTE *) (a1 + REG3);
//                save_opcode(0x31);
//                dump_mem((char *) a1);

                goto LABEL_1;
            }

            ++*(_BYTE *) (a1 + REG7);
//            save_opcode(0x32);
//            dump_mem((char *) a1);

            if (sub_558EB89A4420((unsigned __int8 *) a1)) //jesli cos w 0x20 zmatchuje
                return 1LL;
        }

        if (v1 != 3){
            puts("Exit by exceeding 3");
            return 1LL;
        }

        --*(_BYTE *) (a1 + REG7);
//        save_opcode(0x33);
//        dump_mem((char *) a1);
    }


    return 1LL;
}

int main() {
    char *v3; // rax
    unsigned __int64 v4; // rcx
    char *v5; // rbp
    unsigned __int8 v6; // si
    unsigned __int64 v7; // kr00_8
    unsigned __int64 v8; // rax

    v3 = (char *) prepare_data();
    v4 = 0LL;
    v5 = v3;
    do {
        v6 = ida_chars[v4];
        v7 = v4;
        v8 = v4++;
        v5[256 * (v7 / 0x46) + 8 + v8 % 0x46] = v6;
    } while (v4 != 4900);
    save_opcode(0xFF);
    dump_mem(v3);

    sub_558EB89A48D0((__int64) v5);
    save_opcode(0xFF);
    dump_mem(v3);

    if (!strcmp(v5 + 0x10010, ":)\n"))
        display_flag();


    free(v5);
    return 0LL;
}