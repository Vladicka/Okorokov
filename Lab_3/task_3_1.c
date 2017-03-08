#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define STR "int main(){\n\
    string *str;\n\
    int shmid;\n\
    int new1 = 1;\n\
    char pathname[] = \"03_1a.c\";\n\
    key_t key;\n\
    if((key = ftok(pathname,0)) < 0){\n\
        printf(\"Can't generate key\n\");\n\
        exit(-1);\n\
    }\
    if((shmid = shmget(key, 1024, 0666|IPC_CREAT|IPC_EXCL)) < 0){\n\
        if(errno != EEXIST){\n\
            printf(\"Can\'t create shared memory\n\");\n\
            exit(-1);\n\
        }\n\
        else {\n\
            if((shmid = shmget(key, 1024, 0)) < 0){\n\
                printf(\"Can\'t find shared memory\n\");\n\
                exit(-1);\n\
            }\n\
            new1 = 0;\n\
        }\n\
    }\n\
    if((str = (string *)shmat(shmid, NULL, 0)) == (string *)(-1)){\n\
        printf(\"Can't attach shared memory\n\");\n\
        exit(-1);\n\
    }\n\
    if(shmdt(str) < 0){\n\
        printf(\"Can't detach shared memory\n\");\n\
        exit(-1);\n\
    }\n\
    return 0;\n\
}\n"

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
    strcpy(shm_buf, STR);
    printf("Copied source code to shared memory\n");
    if(shmdt(shm_buf) < 0){
        printf("Can't detach shared memory\n");
        exit(-1);
    }
    return 0;
}
