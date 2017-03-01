#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

int main(){
    pid_t chpid;
    int old_fd, new_fd;
    chpid = fork();
    if (chpid==-1){
        cout << "New process creation failed.";
    }
    else if (chpid ==0){
        (void)umask(0);
        old_fd = open("myfile", O_WRONLY | O_CREAT, 0666);
        if (old_fd < 0){
            printf("Can\'t open file\n");
            exit(1);
        }
        close(STDOUT_FILENO);
        new_fd=dup(old_fd);
        if(new_fd<0){
            exit(2);
        }
        close (old_fd);
        printf("new_fd %i\n",new_fd);
        cout << "Child process.\n";
    }
    else {
        cout << "Parent process.\n";
    }
    cout << "Hello, world!";
}
