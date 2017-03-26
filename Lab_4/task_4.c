#include <unistd.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <iostream>

using namespace std;

int main(){
    int fd[2], result, res, semid, i;
    char msg[24];
    char pathname[] = "temp4";
    string prnt_msg, ch_msg, num;
    key_t sem_key;
    struct sembuf mysem;
    if(pipe(fd) < 0){
        cout << "Can't create pipe\n";
        exit(-1);
    }
    if((sem_key = ftok(pathname,0)) < 0){
        cout << "Can't generate sem key\n";
        exit(-1);
    }
    if((semid = semget(sem_key, 1, 0666 | IPC_CREAT)) < 0){
        cout << "Can't get semid\n";
        exit(-1);
    }
    mysem.sem_flg=0;
    mysem.sem_num=0;
    result = fork();
    if(result <0){
        cout << "Can't fork child\n";
        exit(-1);
    }
    else if (result > 0) {
        for (i=0;i<7;i++){
            num=i+1+'0';
            prnt_msg="Message from parent №" + num;
            res=write(fd[1], prnt_msg.c_str() , 24);
            if (res!=24){
                cout << "Can't send message\n";
                exit(1);
            }
            mysem.sem_op=2;
            semop(semid, &mysem, 1);
            mysem.sem_op=0;
            semop(semid, &mysem, 1);
            res=read(fd[0], msg, 23);
            cout << "Message №" << i+1 << " received from child!\nMessage content: " << msg << "\n\n";
        }
    }
    else {
        for (i=0; i<7; i++){
            mysem.sem_op=-1;
            semop(semid, &mysem, 1);
            res=read(fd[0], msg, 24);
            cout << "Message №" << i+1 << " received from parent!\nMessage content: " << msg << "\n\n";
            num=i+1+'0';
            ch_msg="Message from child №" + num;
            res=write(fd[1], ch_msg.c_str(), 23);
            if (res!=23){
                cout << "Can't send message\n";
                exit(1);
            }
            mysem.sem_op=-1;
            semop(semid, &mysem, 1);
        }
    }
    semctl(semid, IPC_RMID, 0);
    return 0;
}
