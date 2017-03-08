Skip to content
This repository
Search
Pull requests
Issues
Gist
 @Vladicka
 Sign out
 Watch 0
  Star 0
  Fork 0 Vladicka/Okorokov
 Code  Issues 0  Pull requests 0  Projects 0  Wiki  Pulse  Graphs  Settings
Branch: master Find file Copy pathOkorokov/Lab3/task_3_2.c
ab8e17a  5 minutes ago
@Vladicka Vladicka Create task_3_2.c
1 contributor
RawBlameHistory    
44 lines (41 sloc)  1.01 KB
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main(){
    char *shm_buf;
    int shmid;
    char pathname[] = "temp3";
    key_t key;
    if((key = ftok(pathname,1)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }
    if((shmid = shmget(key, 1024, 0666|IPC_CREAT|IPC_EXCL)) < 0){
        if(errno != EEXIST){
            printf("Can\'t create shared memory\n");
            exit(-1);
        }
        else {
            if((shmid = shmget(key, 1024, 0)) < 0){
                printf("Can\'t find shared memory\n");
                exit(-1);
            }
        }
    }
    if((shm_buf = (char *)shmat(shmid, NULL, 0)) == (char *)(-1)){
        printf("Can't attach shared memory\n");
        exit(-1);
    }
    printf("%s\n", shm_buf);
    if(shmdt(shm_buf) < 0){
        printf("Can't detach shared memory\n");
        exit(-1);
    }
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
Contact GitHub API Training Shop Blog About
© 2017 GitHub, Inc. Terms Privacy Security Status Help
