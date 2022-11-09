#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv){
    if(mkdir(argv[1], S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0)
        perror("mkdir");
}