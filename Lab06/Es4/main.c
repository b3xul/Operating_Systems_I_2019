#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <wait.h>
#include <errno.h>
#include <time.h>
/*Follow child: set follow-fork-mode child*/

void sig_handler_father(int sig){
    printf("[PADRE] Ricevuto il segnale %d (%s)\n",sig,strsignal(sig));
}
void sig_handler_son(int sig){
    printf("[FIGLIO] Ricevuto il segnale %d (%s)\n",sig,strsignal(sig));

    if(sig==SIGUSR1){
        printf("[FIGLIO] Invio segnale SIGUSR2\n");
        kill(getppid(),SIGUSR2);
    }
    else if(sig==SIGUSR2){
        printf("[FIGLIO] Invio segnale SIGUSR1\n");
        kill(getppid(),SIGUSR1);
    }
    else{
        printf("[FIGLIO] Invio segnale SIGINT\n");
        kill(getppid(),SIGINT);
    }
}

int my_system(const char* cmd);

int main(int argc, char* argv[])
{

    int i;
    if(argc<2){
        fprintf(stderr,"Numero di argomenti <2, inserire come argomenti i segnali da inviare:\n");
        /*for (i = 1; i < NSIG; i++)
            printf("%2d -> SIG%s\n", i, sys_siglist[i]);*/
        /*system("kill -l");*/  //SH
        my_system("kill -l");   //BASH
        exit(-1);
    }


    pid_t pid=fork();

    switch(pid){
        case -1:
            fprintf(stderr,"Fork fallita\n");
            exit(-1);
            break;
        case 0:
            for(i=1;i<argc;i++){
                if(atoi(argv[i])==10){
                    printf("[FIGLIO] Associo signal handler al segnale SIGUSR1\n");
                    signal(SIGUSR1,sig_handler_son);
                }
                else if(atoi(argv[i])==12){
                    printf("[FIGLIO] Associo signal handler al segnale SIGUSR2\n");
                    signal(SIGUSR2,sig_handler_son);
                }
                else if(atoi(argv[i])==2){
                    printf("[FIGLIO] Associo signal handler al segnale SIGINT\n");
                    signal(SIGINT,sig_handler_son);
                }
                else{
                    printf("[FIGLIO] Blocco il segnale %s (%s)\n",argv[i],strsignal(atoi(argv[i])));
                    signal(atoi(argv[i]),SIG_IGN);  //stringa "SIGUSR1"->CODICE SEGNALE ASSOCIATO A SIGUSR1??? sys_sigName[]
                }
            }

            while(1)
                pause();
            break;
        default:
            sleep(5);
            printf("[PADRE] Associo signal handler al segnale SIGUSR1\n");
            signal(SIGUSR1,sig_handler_father);
            printf("[PADRE] Associo signal handler al segnale SIGUSR2\n");
            signal(SIGUSR2,sig_handler_father);
            printf("[PADRE] Associo signal handler al segnale SIGINT\n");
            signal(SIGINT,SIG_DFL);


            srandom(time(NULL));
            while(1){
                i=random()%(argc-1)+1;  //3 segnali->argc=4->i=random tra 0,1,2->+1->random tra 1,2,3->argv[1,2,3]
                printf("[PADRE] Invio segnale %s (%s):\n",argv[i],strsignal(atoi(argv[i])));
                kill(pid,atoi(argv[i]));
                sleep(4);
            }
            break;
    }

    return 0;
}

int my_system(const char* cmd){
    pid_t pid;
    int status;

    if(cmd==NULL)
        return 1;
    if((pid=fork())<0)
        status=-1;
    else if(pid==0){
        execl("/bin/bash","bash","-c",cmd,(char*)0);    //-c:execute commands as provided within the quotes
        exit(-1);
    }
    else{
        while(waitpid(pid,&status,0)<0){
            if(errno!=EINTR){   //interrupted function
                status=-1;
                break;
            }
        }

    }
    return (status);
}
