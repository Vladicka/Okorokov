#include <signal.h>
#include <stdio.h>

int i=0, j=0;
void (*p1)(int);
void (*p2)(int);

void my_handler(int nsig){
    switch (nsig){
        case 2: {
            printf("Receive signal %d, CTRL-C pressed\n");
            i++;
            break;
        }
        case 3: {
            printf("Receive signal %d, CTRL-4 pressed\n");
            j++;
        }
    }
    if(i == 5) (void)signal(SIGINT, p1);
    if (j==2) (void)signal(SIGQUIT, p2);
}
int main(void){
    p1 = signal(SIGINT, my_handler);
    p2 = signal(SIGQUIT, my_handler);
    while(1);
    return 0;
}
