#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
/*PER OTTIMIZZARE SERVIREBBE UN SISTEMA CHE PERMETTA A PROCESSI SU RAMI DIVERSI DI COMUNICARE TRA LORO PER AVVISARE QUANDO UNO HA TERMINATO, SEGNALI E SEMAFORI (PIPE)*/

int main()
{
    pid_t pid_f3,pid_f5,pid_f8,pid_f6;

    printf("S1: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
    if((pid_f3=fork())>0){
        printf("S2: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
        if((pid_f5=fork())>0){
            sleep(2);
            printf("S4: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
            if((pid_f8=fork())>0){
                sleep(3);
                printf("S7: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
                wait((int *)0);
            }
            else if(pid_f8==0){
                sleep(4);
                printf("S8: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
                exit(0);
            }
            wait((int *)0);
        }
        else if(pid_f5==0){
            sleep(3);
            printf("S5: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
            exit(0);
        }
        sleep(2);

        printf("S10: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
        wait((int *)0);
        printf("S12: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());

    }
    else if (pid_f3==0){
        sleep(1);
        printf("S3: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
        if((pid_f6=fork())>0){
            sleep(6);
            printf("S9: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
            wait((int *)0);
        }
        else if(pid_f6==0){
            sleep(3);
            printf("S6: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
            exit(0);
        }
        sleep(2);
        printf("S11: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
        exit(0);
    }
    return 0;
}
