#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char cwd[256];

int main(int argc, char **argv){
    printf("\x1b[1m");
    if(argc == 1){
        getcwd(cwd, sizeof(cwd));
        DIR *tdir = opendir(cwd);
        struct dirent *dir;
        while ((dir=readdir(tdir))!=NULL){
            switch(dir->d_type){
                case 8:
                    printf("\x1b[32m");
                    break;
                case 4:
                    printf("\x1b[36m");
                    break;
            }
            printf("%s      ", dir->d_name);
        }
        closedir(tdir);
    }
    printf("\n");
}