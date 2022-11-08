#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 30
typedef unsigned int size;

int main(int argc, char **argv){
    char path[512];
    strcpy(path, getenv("soush-cwd"));
    strcat(path, argv[1]);
    FILE *file = fopen(path, "r");
    if(ferror(file)){
        perror("hexcat");
        exit(EXIT_FAILURE);
    }
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