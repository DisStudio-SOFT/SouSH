#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <signal.h>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#define SOUSH_VERSION "0.1.7.2 DEV"
typedef unsigned long size;

char *username;
char cwd[1024];
int exitstatus = 0;

void launch(char **words){
    if(!strcmp(words[0], "cd")){
        if(!strcmp(words[1], ".."))
            for(size pos = strlen(cwd)-2; pos > 0 && cwd[pos] != '/'; pos--)
                cwd[pos] = 0;
        else if(!strcmp(words[1], ".")){}
        else{
            if(cwd[strlen(cwd)-1] != '/')
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
        std::string path = "";
        path += "/bin/soush-files/";
        path += words[0];
        if(execv(path.c_str(), words) == -1){
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

void parser(std::string str){
    if(str[0] == ' ' || str.size() == 0)
        return;
    std::vector<char> chars(str.begin(), str.end());
    bool strskip = 0;
    std::string word = "";
    std::vector<std::string> words;
    for(char ch : chars){
        if(ch == '\'' || ch == '"'){
            strskip = !strskip;
            continue;
        }
        if(ch == ' ' && !strskip){
            words.push_back(word);
            word = "";
            continue;
        }
        word += ch;
    }
    std::vector<char*> cwords;
    for(auto &word : words)
        cwords.push_back(&word.front());
    cwords[cwords.size()] = NULL;
    launch(cwords.data());
    printf("\x1b[0m");
}

int main(int argc, char **argv){
    getcwd(cwd, sizeof(cwd));
    cwd[strlen(cwd)] = '/';
    username = getlogin();
    setenv("soush-version", SOUSH_VERSION, 1);
    while(true){
        signal(SIGINT, SIG_IGN);
        std::string input;
        printf("{%s} :%s ", username, cwd);
        if(exitstatus != 0)
            printf("[%s] ", strsignal(exitstatus));
        printf("# ");
        std::getline(std::cin, input);
        input += ' ';
        exitstatus = 0;
        parser(input);
    }
}