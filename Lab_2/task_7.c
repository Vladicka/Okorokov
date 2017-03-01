#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[], char *envp[]){
    int fd[2], result;
    size_t size;
    char resstring[14];
    string str;
    if(pipe(fd) < 0){
        printf("Can\'t create pipe\n");
        exit(-1);
    }
    str=to_string(fd[0]);
    const char *des=str.c_str();
    result = fork();
    if(result <0){
        printf("Can\'t fork child\n");
        exit(-1);
    }
    else if (result > 0) {
        close(fd[0]);
        size = write(fd[1], "Hello, world!", 14);
        if(size != 14){
            printf("Can\'t write all string\n");
            exit(-1);
        }
        close(fd[1]);
        printf("Parent exit\n");
    }
    else {
         execlp("/home/vladicka/OS_security_progs/Lab2/temp_prog", "/home/vladicka/OS_security_progs/Lab2/temp_prog", des);
    }
    return 0;
}
