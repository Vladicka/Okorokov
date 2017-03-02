#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[], char *envp[]){
    int p1[2], child, i, k=0, j=0, new_fd, ret_code;
    if(pipe(p1) < 0){
        printf("Can\'t create pipe 1\n");
        exit(-1);
    }
    child = fork();
    for (i=0;i<argc;i++){
        if (*argv[i]!='|'){
            k++;
        }
        else break;
    }
    cout << k;
    char *arg[k];
    char *arg1[argc-k];
    for (j=0;j<k-1;j++){
        arg[j]=argv[j+1];
    }
    for (j=0;j<argc-k;j++){
        arg1[j]=argv[j+k+1];
    }
    if(child <0){
        printf("Can\'t fork child\n");
        exit(-1);
    }
    else if (child > 0) {
        close(p1[1]);
        close(STDIN_FILENO);
        new_fd=dup(p1[0]);
        close(p1[0]);
        execvp(arg1[0], arg1);
        wait(&ret_code);
    }
    else {
        close(p1[0]);
        close(STDOUT_FILENO);
        new_fd=dup(p1[1]);
        close(p1[1]);
        execvp(arg[0], arg);
    }
    return 0;
}

