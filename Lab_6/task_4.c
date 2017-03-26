#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main(void) {
    int fd;
    size_t length;
    int i;
    double sum=0;
    struct A {
        double f;
        double f2;
    } *ptr, *tmpptr;
    fd = open("mapped.dat", O_RDWR, 0666);
    if( fd == -1){
        printf("File open failed!\n");
        exit(1);
    }
    length = 100000*sizeof(struct A);
    ftruncate(fd,length);
    ptr = (struct A *)mmap(NULL, length, PROT_WRITE | PROT_READ,
    MAP_SHARED, fd, 0);
    close(fd);
    if( ptr == MAP_FAILED ){
        printf("Mapping failed!\n");
        exit(2);
    }
    tmpptr = ptr;
    for(i = 1; i <=100000; i++){
        sum+=tmpptr->f2;
        tmpptr++;
    }
    cout << sum << "\n";
    munmap((void *)ptr, length);
    return 0;
}
