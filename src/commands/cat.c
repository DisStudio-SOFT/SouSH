#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    while((ch = fgetc(file)) != EOF)
        printf("%c", ch);
    printf("\n");
}