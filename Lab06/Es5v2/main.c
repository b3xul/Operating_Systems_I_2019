#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_handler(int sig){
    printf("[FIGLIO] PID Padre: %d, PID Figlio: %d, Segnale ricevuto: %d\n",getppid(),getpid(),sig);
    return;
}

int main(int argc, char* argv[])
{
    if(argc!=2){
        fprintf(stderr,"Errore nel numero di argomenti.\n");
        exit(-1);
    }
    int i,sig,n=atoi(argv[1]);
    pid_t pid,pid_son;

    for(i=0;i<n;i++){
        pid=getpid();
        pid_son=fork();
        switch(pid_son){
            case -1:
                printf("Errore nella generazione del processo figlio.\n");
                exit(-2);
                break;
            case 0:
                for(i=1;i<NSIG;i++)
                    signal(i,sig_handler);
                pause();
                exit (0);
                break;
            default:
                sleep(2);
                printf("[PADRE] PID Padre: %d, PID Figlio: %d\n",pid,pid_son);
                //kill(pid_son,SIGUSR1);
                sig=random()%(NSIG-1)+1;
                kill(pid_son,sig);
                break;
        }

    }
    return 0;
}
