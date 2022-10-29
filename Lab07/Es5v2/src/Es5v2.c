/*
 ============================================================================
 Name        : Es5v2.c
 Author      : Bexul
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

void sig_H(int sig){
	printf("%d ha ricevuto  %s\n",getpid(),strsignal(sig));
	return;
}
int main(void) {

	pid_t p1,p2;
	printf("P pid: %d\n",getpid());

	signal(SIGUSR2,sig_H);	//P e F1

	switch(p1=fork()){
		case -1:
			fprintf(stderr,"Errore nella prima fork\n");
			exit(-1);
			break;
		case 0:
			printf("Figlio 1 attende...\n");
			pause();	//pause finchè padre non ha fatto signal SIGUSR1

			printf("Figlio 1 invia SIGUSR1 al padre:\n");
			kill(getppid(),SIGUSR1);

			printf("Figlio 1 attende...\n");
			pause();

			exit(EXIT_SUCCESS);
			break;
		default:
			printf("F1 pid: %d\n",p1);

			signal(SIGUSR1,sig_H);	//P e F2

			switch(p2=fork()){
				case -1:
					fprintf(stderr,"Errore nella seconda fork\n");
					exit(-2);
					break;
				case 0:
					printf("Figlio 2 attende...\n");
					pause();			//(3)

					printf("Figlio 2 invia SIGUSR2 al padre:\n");
					kill(getppid(),SIGUSR2);	//(4)

					exit(EXIT_SUCCESS);
					break;
				default:
					printf("F2 pid: %d\n",p2);
					break;
			}
			printf("Padre invia SIGUSR2 al figlio 1:\n");
			kill(SIGUSR2,p1);	//sblocca F1

			printf("Padre attende segnale di avvio SIGUSR1...\n");
			pause();

			printf("Padre invia SIGUSR1 al figlio 2:\n");
			kill(p2,SIGUSR1);			//(2)

			printf("Padre attende segnale di risposta SIGUSR2...\n");
			pause();

			printf("Padre invia SIGUSR2 al figlio 1:\n");
			kill(p1,SIGUSR2);

			break;
	}
	return EXIT_SUCCESS;
}
