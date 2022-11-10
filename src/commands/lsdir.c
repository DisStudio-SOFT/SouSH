#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char cwd[256];

int main(int argc, char **argv){
    printf("\x1b[1m");
    DIR *tdir;
    if(argc == 1){
        getcwd(cwd, sizeof(cwd));
        tdir = opendir(cwd);
    } else {
        tdir = opendir(argv[1]);
    }
    struct dirent *dir;
    while ((dir=readdir(tdir))!=NULL){
        if(!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
            continue;
        switch(dir->d_type){
            case 8:
                printf("FILE   ");
                break;
            case 4:
                printf("DIR    ");
                break;
        }
        printf("%s\n", dir->d_name);
    }
    closedir(tdir);
}