#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define MAXSIZE 30
typedef unsigned int size;

int main(int argc, char **argv){
    if(argc == 1){
        printf("HEXCAT - SOUSH %s\n", getenv("soush-version"));
        printf("Arguments:\n");
        printf("    <path> - File path\n");
        printf("\n");
        printf("Description:\n");
        printf("Read and print the file in HEX format\n");
        exit(EXIT_SUCCESS);
    }
    FILE *file = fopen(argv[1], "r");
    if(access(argv[1], F_OK))
        perror("hexcat");
    char ch;
    size pos = 0;
    size step = 0;
    printf("0x%-20X", pos);
    char chars[MAXSIZE];
    while((ch = fgetc(file)) != EOF){
        if(step == MAXSIZE){
            step = 0;
            printf("   %s", chars);
            printf("\n");
            printf("0x%-20X", pos);
            memset(chars, 0, sizeof(chars));
            continue;
        }
        if(ch < 0)
            ch = 0;
        if(ch < 16)
            printf("0");
        printf("%X ", ch);
        char ch2[2];
        ch2[0] = ch;
        ch2[1] = 0;
        if(ch < ' ' || ch > '~')
            ch2[0] = '.';
        strcat(chars, ch2);
        step++;
        pos++;
    }
    for(; step < MAXSIZE; step++)
        printf("   ");
    printf("   %s", chars);
    printf("\n");
}