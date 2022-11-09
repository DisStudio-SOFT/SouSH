#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include "libs/memory.h"
#define SOUSH_VERSION "0.1.7 DEV"
typedef unsigned long size;

char input[512];
char cwd[512];
char username[64];
char path[512];
char *sigerr[] = {
    NULL, 
    NULL, 
    "SIGINT",
    NULL,
    NULL,
    NULL,
    "SIGABRT",
    NULL,
    NULL,
    "SIGKILL",
    "SIGBUS",
    NULL,
    NULL,
    NULL,
    NULL,
    "SIGTERM",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    "SIGSTOP"};
int exitstatus = 0;

void launch(char **words){
    if(!strcmp(words[0], "cd")){
        if(!strcmp(words[1], ".."))
            for(size pos = strlen(cwd)-2; pos > 0 && cwd[pos] != '/'; pos--)
                cwd[pos] = 0;
        else{
            strcat(cwd, "/");
            strcat(cwd, words[1]);
            if(words[1][strlen(words[1])-1] != '/')
                strcat(cwd, "/");
        }
        chdir(cwd);
        return;
    } else if(!strcmp(words[0], "exit"))
        exit(0);
    pid_t pid = 0, wpid = 0;
    int status = 0;
    pid = fork();

    if(pid == 0){
        signal(SIGINT, SIG_DFL);
        memset(path, 0, sizeof(path));
        strcpy(path, "/bin/soush-files/");
        strcat(path, words[0]);
        if(execv(path, words) == -1){
            if(execvp(words[0], words) == -1){
                perror("soush");
            }
        }
        exit(EXIT_SUCCESS);
    } else if (pid < 0) {
        perror("soush");
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        exitstatus = status;
        if(status == 2)
            printf("\n");
    }
}

void mainloop(){
    memset(input, 0, sizeof(input));
    fgets(input, sizeof(input), stdin);
    input[strlen(input)-1] = 0;
    if(input[0] == 0 || input[0] == ' ')
        return;
    
    char *words[128];
    memset(words, 0, sizeof(words) / sizeof(char*));
    size wordspos = 0;
    char *word = strtok(input, " ");
    while(word != NULL){
        words[wordspos++] = word;
        word = strtok(NULL, " ");
    }
    words[wordspos] = NULL;

    launch(words);
}

int main(int argc, char **argv){
    getcwd(cwd, sizeof(cwd));
    getlogin_r(username, sizeof(username));
    setenv("soush-version", SOUSH_VERSION, 1);
    while(1){
        signal(SIGINT, SIG_IGN);
        printf("\x1b[0m[\x1b[32m%s\x1b[0m] \x1b[36m%s%s%s%s\x1b[0m # ", username, cwd, (exitstatus > 0) ? " \x1b[0m[\x1b[31m\x1b[1m" : "", (exitstatus > 0) ? sigerr[exitstatus] : "", (exitstatus > 0) ? "\x1b[0m]" : "");
        exitstatus = 0;
        mainloop();
    }
}