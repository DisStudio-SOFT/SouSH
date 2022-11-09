#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
    if(argc == 1){
        printf("CAT - SOUSH %s\n", getenv("soush-version"));
        printf("Arguments:\n");
        printf("    <path> - File path\n");
        printf("\n");
        printf("Description:\n");
        printf("Read and print the file\n");
        exit(EXIT_SUCCESS);
    }
    FILE *file = fopen(argv[1], "r");
    if(access(argv[1], F_OK))
        perror("cat");
    if(ferror(file)){
        perror("hexcat");
        exit(EXIT_FAILURE);
    }
    char ch;
    while((ch = fgetc(file)) != EOF)
        printf("%c", ch);
    printf("\n");
}