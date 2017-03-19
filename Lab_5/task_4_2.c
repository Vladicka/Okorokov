#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main() {
    int msqid;
    char pathname[] = "temp4";
    key_t key;
    int len, maxlen, item, pid;
    struct mymsgbuf{
        long mtype;
        struct{
            int source_pid;
            int query_type;
            char text[100];
        }content;
    } mybuf;
    if((key = ftok(pathname,0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }
    if((msqid = msgget(key, 0666)) < 0){
        cout << "Server is not running. Launch it and try again.\n";
        exit(-1);
    }
    pid=(int)getpid();
    while(item!=4){
        cout << "1. Ping\n2. Cirno..?\n3. Burzum\n4. Exit\n0. Terminate server\n>";
        cin >> item;
        cout << "\n";
        switch (item){
            case 1:{
                len=116;
                mybuf.mtype=1;
                mybuf.content.source_pid=pid;
                mybuf.content.query_type=1;
                if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
                    printf("Can\'t send message to queue\n");
                    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
                    exit(-1);
                }
                break;
            }
            case 2:{
                len=116;
                mybuf.mtype=1;
                mybuf.content.source_pid=pid;
                mybuf.content.query_type=2;
                if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
                    printf("Can\'t send message to queue\n");
                    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
                    exit(-1);
                }
                break;
            }
            case 3:{
                len=116;
                mybuf.mtype=1;
                mybuf.content.source_pid=pid;
                mybuf.content.query_type=3;
                if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
                    printf("Can\'t send message to queue\n");
                    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
                    exit(-1);
                }
                break;
            }
            case 4: exit(1);
            case 0:{
                len=116;
                mybuf.mtype=1;
                mybuf.content.source_pid=pid;
                mybuf.content.query_type=0;
                if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
                    printf("Can\'t send message to queue\n");
                    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
                    exit(-1);
                }
                break;
            }
            default: continue;
        }
        maxlen=116;
        if (len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, pid, 0) < 0){
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }
        cout << "Message from server: " << mybuf.content.text << "\n\n";
    }
    return 0;
}
