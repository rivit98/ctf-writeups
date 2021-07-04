/*
 * gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04)
 * g++ -o chal chal.cpp
*/

#include <iostream>
#include <random>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

#ifndef FLAG
#define FLAG_HINT "Hint do innego zadania."
// flaga zadania Stary Hazardzista
#define FLAG_EASY "BABAJAGA{123456}"
// flaga zadania Stary Hazardzista Kontratakuje
#define FLAG_HARD "BABAJAGA{654321}"
#endif

const int name_length = 18;
const int flag_length = 18;

char * name;
char * flag;

void solved() {
    printf(FLAG_EASY);
    printf(FLAG_HINT);
}

int main() {
    name = (char*) malloc(name_length);
    flag = (char*) malloc(flag_length);
    strcpy(flag, FLAG_HARD);

    setbuf(stdout, NULL);
    printf("What's your name? ");
    scanf("%s", name);

    char seed_sequence[name_length + flag_length];
    memcpy(seed_sequence, name, name_length);
    memcpy(seed_sequence+name_length, flag, flag_length);

    std::seed_seq seedseq (seed_sequence, seed_sequence + name_length + flag_length);
    std::mt19937 generator (seedseq);

    int numbers[1000];
    for (int i = 0; i < 1000; i++) {
        numbers[i] = generator() % 1000;
    }

    printf("%s, let's play a little game. My first number is %d. You have to guess next 999 numbers consecutively, all of them 0 to 999.\n", name, numbers[0]);
    int iterator = 1;
    int answer;

    while(iterator < 1000){
        printf("[%d/999] Guess number: ", iterator);
        scanf("%d", &answer);
        if (answer == numbers[iterator]) {
            printf("Good one!\n");
        }
        else{
            printf("Not this time!\n");
            break;
        }
        if (iterator == 999) {
            solved();
            break;
        }
        iterator++;
    }
    fclose(stdout);
    return(0);
}
