#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <iostream>
#include <dirent.h>

using namespace std;

int main(){
    DIR *curr_dir;
    struct dirent *curr_file;
    if((curr_dir = opendir("/root")) < 0){
        cout << "Can't open directory.\n";
        exit(-1);
    }
    curr_file=readdir(curr_dir);
    if (curr_file==NULL){
        cout << "Can't get info about file in directory.\n";
        exit(-1);
    }
    while(curr_file!=NULL){
        cout << curr_file->d_name << "\n";
        curr_file=readdir(curr_dir);
    }
    if (closedir(curr_dir)<0){
        cout << "Can't close directory.\n";
    }
    return 0;
}
