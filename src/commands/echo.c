#include <stdio.h>
typedef unsigned long size;

int main(int argc, char **argv){
    for(size pos = 1; pos < argc; pos++)
        printf("%s ", argv[pos]);
    printf("\n");
}