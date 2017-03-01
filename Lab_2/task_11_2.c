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
    int fd, result;
    size_t size;
    char resstring[14];
    char name[]="aaa.fifo";
    string message;
    cout << message;
    (void)umask(0);
    char mes[321];
    if((fd = open(name, O_RDONLY)) < 0){
        printf("Can\'t open FIFO for reading\n");
        exit(-1);
    }
    size = read(fd, mes, 321);
    if(size < 0){
        cout << "No message.";
        exit(-1);
    }
    cout << "Message received!\n\n";
    cout << mes << "\n";
    close (fd);
    return 0;
}
