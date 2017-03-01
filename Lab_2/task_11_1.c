#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

int main(){
    int fd;
    size_t size;
    char name[]="aaa.fifo";
    string message="\
    I am the bone of my sword\n\
    Steel is my body and fire is my blood\n\
　　I have created over a thousand blades\n\
　　Unaware of Loss\n\
　　Nor aware of gain\n\
　　Withstood pain to create weapons, waiting for one's arrival\n\
　　I have no regrets. This is the only path\n\
　　My whole life was Unlimited Blade Works";
    (void)umask(0);
    if((fd = open(name, O_WRONLY)) < 0){
        printf("Can\'t open FIFO for writting\n");
        exit(-1);
    }
    size = write(fd, message.c_str(), 321);
    if(size != 321){
        cout << "Error occured during message sending.";
        exit(-1);
    }
    cout << "Message sent\n";
    close(fd);
    return 0;
}
