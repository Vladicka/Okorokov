#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(){
    int *array;
    int shmid;
    int new1 = 1;
    char pathname[] = "temp7";
    key_t key;
    if((key = ftok(pathname,0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }
    if((shmid = shmget(key, 3*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0){
        if(errno != EEXIST){
            printf("Can\'t create shared memory\n");
            exit(-1);
        }
        else {
            if((shmid = shmget(key, 3*sizeof(int), 0)) < 0){
                printf("Can\'t find shared memory\n");
                exit(-1);
            }
            new1 = 0;
        }
    }
    if((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)){
        printf("Can't attach shared memory\n");
        exit(-1);
    }
    if(new1){
        array[3] = 0;
        array[4] = 1;
        array[5] = 1;
    }
    else {
        array[1]=1;
        array[2]=0;
        while (array[0] && array[2]==0);
        array[4] += 1;
        for(int i=0; i<1000000000; i++);
        array[5] += 1;
        array[1]=0;
    }
    printf("Program 1 was spawn %d times, program 2 - %d times, total - %d times\n",
    array[3], array[4], array[5]);
    if(shmdt(array) < 0){
        printf("Can't detach shared memory\n");
        exit(-1);
    }
    return 0;
}
