#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <time.h>

using namespace std;

int main() {
    int msqid;
    char pathname[] = "temp4";
    char *curr_time;
    key_t key;
    pid_t chpid;
    int len, maxlen, pid;
    time_t rawtime;
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
    if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
        cout << "Cant get msgid\n";
        exit(-1);
    }
    pid=(int)getpid();
    cout << "Server " << pid << " is runnging.\n";
    while(1){
        if (len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 1, 0) < 0){
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }
        time(&rawtime);
        curr_time=asctime(localtime(&rawtime));
        curr_time[strlen(curr_time)-1] = '\0';
        cout << curr_time << "  Message from " << mybuf.content.source_pid << " recieved.\n";
        switch (mybuf.content.query_type){
            case 1:{
                chpid=fork();
                if (chpid==0){
                    len=116;
                    mybuf.mtype=mybuf.content.source_pid;
                    mybuf.content.source_pid=pid;
                    strcpy(mybuf.content.text, "Server is here!");
                    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
                        printf("Can\'t send message to queue\n");
                        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
                        exit(-1);
                    }
                    exit(0);
                }
                break;
            }
            case 2:{
                chpid=fork();
                if (chpid==0){
                    len=116;
                    mybuf.mtype=mybuf.content.source_pid;
                    mybuf.content.source_pid=pid;
                    strcpy(mybuf.content.text, "Baka!");
                    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
                        printf("Can\'t send message to queue\n");
                        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
                        exit(-1);
                    }
                    exit(0);
                }
                break;
            }
            case 3:{
                chpid=fork();
                if (chpid==0){
                    len=116;
                    mybuf.mtype=mybuf.content.source_pid;
                    mybuf.content.source_pid=pid;
                    strcpy(mybuf.content.text, "This is for her, war!");
                    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
                        printf("Can\'t send message to queue\n");
                        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
                        exit(-1);
                    }
                    execlp("sh", "sh", "/home/vladicka/war");
                }
                break;
            }
            case 0:{
                len=116;
                mybuf.mtype=mybuf.content.source_pid;
                mybuf.content.source_pid=pid;
                strcpy(mybuf.content.text, "I'll be back!");
                if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0){
                    printf("Can\'t send message to queue\n");
                    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
                    exit(-1);
                }
                cout << "Terminating server\n";
                msgctl(msqid, IPC_RMID, NULL);
                exit(0);
            }
            default: continue;
        }
    }
    return 0;
}
