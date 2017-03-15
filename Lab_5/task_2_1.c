#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define LAST_MESSAGE 255

int main() {
    int msqid;
    char pathname[] = "temp2";
    key_t key;
    int i,len;
    struct mymsgbuf{
        long mtype;
        struct{
            int i_info;
            double d_info;
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
    len=sizeof(mybuf.content);
    for (i = 1; i <= 5; i++){
        mybuf.mtype = 1;
        mybuf.content.i_info=i*5;
        mybuf.content.d_info=3.1415*i;
        if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
    }
    mybuf.mtype = LAST_MESSAGE;
    len = 0;
    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }
    return 0;
}
