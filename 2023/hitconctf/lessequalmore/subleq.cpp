#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unordered_set>
#include <vector>

std::unordered_set<int64_t> ips;
std::vector<char> known;
int instr_cnt = 0;

int64_t* mem;

int input_idx = 0;
int64_t get_bignum()
{
    char v1;     // [rsp+7h] [rbp-9h]
    printf("getchar\n");
    v1 = getchar();
    return -v1;
}

void op1(int64_t a1, int64_t a2)
{
    int64_t bignum; // [rsp+18h] [rbp-28h]

    if (a1 < 0)
    {
        bignum = get_bignum();
    }
    else
    {
        bignum = mem[a1];
        if(a1 >= 0x10 && a1 < 0xa0){
            printf("read from 0x%lx (0x%lx)\n", a1, mem[a1]);
        }
    }

    if (a2 < 0)
    {
        printf("print %c\n", (char)bignum);
    }
    else
    {
        mem[a2] -= bignum;
//        printf("store [%x]=%x\n", a2, mem[a2]);
    }
}

void print_range(int start, int stop, int newline=false) {
    for (size_t i = start; i < stop; i++){
        int64_t v = mem[i];
        if (v < 0){
            printf("-%llx ", llabs(v));
        }else {
            printf("%llx ", v);
        }
    }
    
    if (newline){
        puts("");
    }
    puts("");
}

int op2(int64_t a1)
{
    return (mem[a1]) <= 0;
}

int run_program()
{
    int pc; // [rsp+Ch] [rbp-4h]

    pc = 0xcf8;
    pc = 0x1082;
    pc = 0;
    while (pc >= 0)
    {
        if(
            0
//            || (pc >= 0x1441 && pc <= 0x1532) // print
            || (pc >= 0x1066 && pc <= 0x1194) // getchar
        ){}
        else{
            printf("pc 0x%x) subleq 0x%lx 0x%lx -> 0x%lx\n", pc, mem[pc], mem[pc+1], mem[pc+2]);
//            print_range(0, 0x10);
//            print_range(0x10, 0x30);
//            print_range(0x30, 0x50);
//            print_range(0x50, 0x70);
//            print_range(0x70, 0x90);
//            puts("");
        }

        if(pc == 0xaa2d){ // store results in memory
//            print_range(0x10, 0x30, true);
        }

        op1(mem[pc], mem[pc + 1]);
        if (op2(mem[pc + 1])){
            pc = (mem[pc + 2]);
//            printf("jump %x\n", pc);
        }
        else
            pc += 3;
    }
}

int read_program(const char *a1)
{
    int i;        // eax
    int v3;       // [rsp+14h] [rbp-Ch]
    FILE *stream; // [rsp+18h] [rbp-8h]

    stream = fopen(a1, "r");
    v3 = 0;
    for (i = feof(stream); !i; i = feof(stream))
        fscanf(stream, "%lld", &mem[v3++]);
    return fclose(stream);
}

int main(int argc, const char **argv, const char **envp)
{
    mem = (int64_t*)malloc(0x80000uLL);
    read_program("./chal.txt");
    run_program();
    
    return 0;
}
