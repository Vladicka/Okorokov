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
