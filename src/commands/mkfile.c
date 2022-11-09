#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
    if(!access(argv[1], F_OK)){
        printf("Are you sure you want to overwrite the file?\n");
        printf("[Y/n]");
        char ch = getchar();
        if(ch == 'n' || ch == 'N')
            exit(EXIT_FAILURE);
    }
    FILE *file = fopen(argv[1], "w");
    fprintf(file, "\n ");
}