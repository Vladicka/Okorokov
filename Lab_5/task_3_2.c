#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <iostream>

using namespace std;

int main() {
    int msqid;
    char pathname[] = "temp3";
    key_t key;
    int len, maxlen, i;
    struct mymsgbuf{
        long mtype;
        struct{
            int i;
            char text[28];
        }content;
    } mybuf;
    if((key = ftok(pathname,0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }
    if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get msqid\n");
        exit(-1);
    }
    for (i = 1; i <= 5; i++){
        mybuf.mtype = 2;
        mybuf.content.i=i;
        strcpy(mybuf.content.text, "Message from programm 2 №");
        len=36;
        if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
    }
    mybuf.mtype = 2;
    mybuf.content.i=-1;
    len=8;
    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }
    while(1){
        maxlen=36;
        if (len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 1, 0) < 0){
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }
        if (mybuf.content.i==-1){
            exit(0);
        }
        cout << mybuf.content.text << " " << mybuf.content.i << "\n";
    }
    return 0;
}
