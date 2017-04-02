#include <unistd.h>
#include <iostream>
#include <signal.h>

pid_t ppid, chpid;
int fd[2], i=0, j=0;

using namespace std;

void p_handler(int nsig){
    char msg[24];
    int res;
    string num, prnt_msg;
    switch (nsig) {
        case 10: {
            num=i+1+'0';
            prnt_msg="Message from parent №" + num;
            res=write(fd[1], prnt_msg.c_str() , 24);
            if (res!=24){
                cout << "Can't send message\n";
                exit(1);
            }
            kill(chpid, SIGUSR2);
            break;
        }
        case 12: {
            res=read(fd[0], msg, 24);
            cout << "Message №" << i+1 << " received from child!\nMessage content: " << msg << "\n\n";
            i++;
            kill(getpid(), SIGUSR1);
            break;
        }
    }
    if (i==7) exit(0);
}

void ch_handler(int nsig){
    char msg[24];
    string num, ch_msg;
    int res;
    switch (nsig){
        case 10: {
            num=j+1+'0';
            ch_msg="Message from child №" + num;
            res=write(fd[1], ch_msg.c_str() , 24);
            if (res!=24){
                cout << "Can't send message\n";
                exit(1);
            }
            j++;
            kill(ppid, SIGUSR2);
            break;
        }
        case 12: {
            res=read(fd[0], msg, 24);
            cout << "Message №" << j+1 << " received from parent!\nMessage content: " << msg << "\n\n";
            kill(getpid(), SIGUSR1);
            break;
        }
    }
    if (j==7) exit(0);
}

int main(){
    if(pipe(fd) < 0){
        cout << "Can't create pipe\n";
        exit(-1);
    }
    ppid=getpid();
    chpid = fork();
    if(chpid < 0){
        cout << "Can't fork child\n";
        exit(-1);
    }
    else if (chpid > 0) {
        (void)signal(SIGUSR1, p_handler);
        (void)signal(SIGUSR2, p_handler);
        while(1);
    }
    else {
        (void)signal(SIGUSR1, ch_handler);
        (void)signal(SIGUSR2, ch_handler);
        kill(ppid, SIGUSR1);
        while(1);
    }
    return 0;
}
