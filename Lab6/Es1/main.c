#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


int a,b;    //Senza usare variabili globali?? Non si può
void sig_handler(int sig){
    switch(sig){
        case SIGUSR1: printf("%d\n",a-b);
            break;
        case SIGUSR2: printf("%d\n",a+b);
            break;
        default:
            exit(-4);
    }
}

int main()
{
    printf("PID: %d Inserire valori di a e b: ",getpid());
    scanf("%d %d",&a,&b);

    if(signal(SIGUSR1, sig_handler) == SIG_ERR) {
        fprintf(stderr, "SignalHandlerError.\n");
        return(-1);
    }
    if(signal(SIGUSR2, sig_handler) == SIG_ERR) {
        fprintf(stderr, "SignalHandlerError.\n");
        return(-2);
    }
    if(signal(SIGINT,SIG_DFL) == SIG_ERR) {
        fprintf(stderr, "SignalHandlerError.\n");
        return(-3);
    }

    while(1){
        printf("Waiting for signal... ");
        pause();
    }
    return 0;
}
