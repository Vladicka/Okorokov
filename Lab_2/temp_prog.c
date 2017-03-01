#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[], char *envp[]){
    size_t size;
    char resstring[14];
    int des;
    stringstream strvalue;
    strvalue << argv[1];
    strvalue >> des;
    cout << "Child process\n";
    size = read(des, resstring, 14);
    printf("%s\n",resstring);
    close(des);
}
