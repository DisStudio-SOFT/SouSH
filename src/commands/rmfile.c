#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv){
    if(access(argv[1], F_OK))
        perror("rm");
    remove(argv[1]);
}