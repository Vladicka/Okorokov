#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(){
    int r_fd, w_fd;
    size_t r_s, w_s;
    char *ch;
    (void)umask(0);
    if((r_fd = open("task_1_src", O_RDONLY)) < 0){
        cout << "Can't open file with source code.\n";
        exit(-1);
    }
    if ((w_fd = creat("temp1", 0666))<0){
        cout << "Can't create new file.\n";
        exit(-1);
    }
    r_s=read(r_fd, ch, 1);
    if (r_s<0){
        cout << "Reading error.\n";
        exit(-1);
    }
    while(r_s!=0){
        w_s=write(w_fd, ch, 1);
        if (w_s < 1){
            cout << "Writing error.\n";
            exit(-1);
        }
        r_s=read(r_fd, ch, 1);
        if (r_s<0){
            cout << "Reading error.\n";
            exit(-1);
        }
    }
    cout << "Sucessfully copied source code!\n";
    if((close(r_fd)!=0) || (close(w_fd)!=0)){
        cout << "Can't close file/files.\n";
    }
    return 0;
}
