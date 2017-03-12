#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(){
    int *array;
    int shmid, semid;
    int new1 = 1;
    char pathname[] = "temp3";
    key_t key_shm, key_sem;
    struct sembuf mysem;
    if((key_shm = ftok(pathname,0)) < 0){
        printf("Can\'t generate shared memory key\n");
        exit(-1);
    }
    if((shmid = shmget(key_shm, 3*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0){
        if(errno != EEXIST){
            printf("Can\'t create shared memory\n");
            exit(-1);
        }
        else {
            if((shmid = shmget(key_shm, 3*sizeof(int), 0)) < 0){
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
    if((key_sem = ftok(pathname,0)) < 0){
        printf("Can\'t generate sem key\n");
        exit(-1);
    }
    if((semid = semget(key_sem, 1, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get semid\n");
        exit(-1);
    }
    mysem.sem_op=0;
    mysem.sem_flg=0;
    mysem.sem_num=0;
    if(new1){
        array[0] = 0;
        array[1] = 1;
        array[2] = 1;
    }
    else {
        semop(semid, &mysem, 1);
        mysem.sem_op=1;
        semop(semid, &mysem, 1);
        array[1] += 1;
	for(int i=0; i<1000000000; i++);
        array[2] += 1;
        mysem.sem_op=-1;
        semop(semid, &mysem, 1);
    }
    printf("Program 1 was spawn %d times, program 2 - %d times, total - %d times\n",
    array[0], array[1], array[2]);
    if(shmdt(array) < 0){
        printf("Can't detach shared memory\n");
        exit(-1);
    }
    return 0;
}
