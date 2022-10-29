#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
/*PER OTTIMIZZARE SERVIREBBE UN SISTEMA CHE PERMETTA A PROCESSI SU RAMI DIVERSI DI COMUNICARE TRA LORO PER AVVISARE QUANDO UNO HA TERMINATO, SEGNALI E SEMAFORI (PIPE)*/

int main()
{
    pid_t branch1,branch11,branch2,branch3;  //Concettualmente divido in branch e aspetto che finisca

    printf("S1: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
    branch1=fork();
    if (!branch1){  //Dentro branch1
        sleep(1);
        printf("S3: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
        branch11=fork();

        if(!branch11){
            sleep(3);
            printf("S6: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
            exit(0);
        }
        else{
            while(wait((int *)0)!=branch11);
            sleep(3);
            printf("S9: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());

            sleep(2);
            printf("S11: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
            exit(0);
        }
    }

    else{
        printf("S2: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
        branch2=fork();
        if(!branch2){
            sleep(3);
            printf("S5: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
            sleep(4);
            exit(0);
        }

        sleep(2);
        printf("S4: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
        branch3=fork();
        if(!branch3){
            sleep(4);
            printf("S8: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
            exit(0);
        }

        sleep(3);
        printf("S7: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
        while(wait((int *)0)!=branch3);
        while(wait((int *)0)!=branch2);

        sleep(2);
        printf("S10: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
        while(wait((int *)0)!=branch1);

        printf("S12: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
    }

    return 0;
}
