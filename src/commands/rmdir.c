#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv){
    if(rmdir(argv[1]) != 0)
        perror("rmdir");
}