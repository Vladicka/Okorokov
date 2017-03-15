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
    int len, maxlen;
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
    while(1){
        maxlen = 16;
        if (len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 0, 0) < 0){
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }
        if (mybuf.mtype == LAST_MESSAGE){
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(0);
        }
        printf("message type = %ld, i_info = %d, d_info= %f\n", mybuf.mtype, mybuf.content.i_info, mybuf.content.d_info);
    }
    return 0;
}
