#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
/*PER OTTIMIZZARE SERVIREBBE UN SISTEMA CHE PERMETTA A PROCESSI SU RAMI DIVERSI DI COMUNICARE TRA LORO PER AVVISARE QUANDO UNO HA TERMINATO, SEGNALI E SEMAFORI (PIPE)*/

int main()
{
    pid_t pid_f3,pid_f5,pid_f8,pid_f6;  //IN realtà basta un unico PID perchè in questo caso sono io che sincronizzo a mano i vari rami sapendo i tempi di terminazione usando le sleep

    printf("S1: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
    if((pid_f3=fork())>0){
        //Attesa 0
        printf("S2: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
        if((pid_f5=fork())>0){
            sleep(2);   //Attendere il 3
            printf("S4: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
            if((pid_f8=fork())>0){
                sleep(3);
                printf("S7: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
                while(wait((int *)0)!=pid_f8);
                //wait((int *)0);     //Basta wait di qualunque processo per finire tutti i processi, per l'ordine posso usare le sleep, per sfruttare "waitpid" bisogna per forza che l'ordine sia quello voluto, per cui c'è bisogno delle sleep!
            }
            else if(pid_f8==0){
                sleep(4);
                printf("S8: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
                exit(0);
            }
            while(wait((int *)0)!=pid_f5);  //SE F5 TERMINA DURANTE L'ATTESA PER F8 QUESTA WAIT ASPETTERA' PER SEMPRE!
            //wait((int *)0);
        }
        else if(pid_f5==0){
            sleep(3);   //Attendere 3 e 4
            printf("S5: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
            sleep(4);   //Calcolare a che tempo dovrebbe terminare per evitare di mandare la wait in loop!!
            exit(0);
        }

        printf("S10: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
        while(wait((int *)0)!=pid_f3);
        //wait((int *)0);
        printf("S12: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());

    }
    else if (pid_f3==0){
        sleep(1);   //FORK 2-3
        printf("S3: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
        if((pid_f6=fork())>0){
            /*MODO 1
            sleep(6);
            printf("S9: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());
            wait((int *)0);
            */

            /*MODO2*/
            while(wait((int *)0)!=pid_f6);
            sleep(3);
            printf("S9: IO SONO %d, FIGLIO DI %d, DELLA TRIBU' DI %d\n",getpid(),getppid(),getgid());

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
