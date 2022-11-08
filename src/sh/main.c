#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include "libs/memory.h"
typedef unsigned long size;

char input[512];
char cwd[512];
char username[64];

void launch(char **words){
    pid_t pid = 0, wpid = 0;
    int status = 0;
    pid = fork();

    if(pid == 0){
        if(execvp(words[0], words) == -1){
            perror("soush");
        }
        exit(EXIT_SUCCESS);
    } else if (pid < 0) {
        perror("soush");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

void mainloop(){
    memset(input, 0, sizeof(input));
    fgets(input, sizeof(input), stdin);
    input[strlen(input)-1] = 0;
    
    char **words = cmalloc(0 * sizeof(char*));
    unsigned long wordspos = 0;
    char *word = strtok(input, " ");
    char *line;
    while(word != NULL){
        if(wordspos == 0){
            line = cmalloc(strlen(word) + strlen("soush-files/") + 1 * sizeof(char));
            strcpy(line, "soush-files/");
            strcat(line, word);
        }
        words = crealloc(words, (++wordspos) * sizeof(char*));
        if(wordspos-1 == 0)
            words[wordspos-1] = line;
        else
            words[wordspos-1] = word;
        word = strtok(NULL, " ");
    }
    words[wordspos] = NULL;

    if(!strcmp(words[0], "soush-files/cd")){
        if(!strcmp(words[1], ".."))
            for(size pos = strlen(cwd)-1; pos > 0 && cwd[pos] != '/'; pos--)
                cwd[pos] = 0;
        else{
            strcat(cwd, "/");
            strcat(cwd, words[1]);
            if(words[1][strlen(words[1])-1] != '/')
                strcat(cwd, "/");
        }
    } else 
        launch(words);
    free(word);
    free(words);
}

int main(int argc, char **argv){
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/");
    getlogin_r(username, sizeof(username));;
    while(1){
        setenv("soush-cwd", cwd, 1);
        printf("\x1b[0m{\x1b[32m%s\x1b[0m} \x1b[36m%s \x1b[0m$ ", username, cwd);
        mainloop();
    }
}