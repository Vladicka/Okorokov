#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[], char *envp[]){
    int p1[2], p2[2], result;
    size_t size;
    if(pipe(p1) < 0){
        printf("Can\'t create pipe 1\n");
        exit(-1);
    }
    if(pipe(p2) < 0){
        printf("Can\'t create pipe 2\n");
        exit(-1);
    }
    result = fork();
    if(result <0){
        printf("Can\'t fork child\n");
        exit(-1);
    }
    else if (result > 0) {
        char ch_m[20];
        close(p1[0]);
        close(p2[1]);
        cout << "Parent process.\n";
        size = write(p1[1], "Message from parent.", 21);
        if(size != 21){
            printf("Can\'t write all string\n");
            exit(-1);
        }
        close(p1[1]);
        size=read(p2[0], ch_m, 20);
        printf("%s\n", ch_m);
        printf("Parent exit\n");
    }
    else {
        char p_m[21];
        close(p1[1]);
        close(p2[0]);
        cout << "Child process.\n";
        size = write(p2[1], "Message from child.", 20);
        if(size != 20){
            printf("Can\'t write all string\n");
            exit(-1);
        }
        size=read(p1[0], p_m, 21);
        printf("%s\n", p_m);
        printf("Child exit\n");
    }
    return 0;
}
