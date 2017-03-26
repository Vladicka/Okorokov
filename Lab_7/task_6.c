#include <signal.h>
#include <stdio.h>

void my_handler(int nsig){
    switch (nsig){
        case 2: printf("Receive signal %d, CTRL-C pressed\n"); break;
        case 3: printf("Receive signal %d, CTRL-4 pressed\n");
    }
}
int main(void){
    (void) signal (SIGINT, my_handler);
    (void) signal (SIGQUIT, my_handler);
    while(1);
    return 0;
}
