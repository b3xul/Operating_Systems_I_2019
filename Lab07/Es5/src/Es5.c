/*
 ============================================================================
 Name        : Es5.c
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

void sig_H_parent(int sig){
	printf("Padre riceve %s\n",strsignal(sig));
	return;
}
void sig_H_child(int sig){
	printf("Figlio riceve %s\n",strsignal(sig));
	return;
}
int main(void) {

	pid_t p1,p2;

	switch(p1=fork()){
		case -1:
			fprintf(stderr,"Errore nella prima fork\n");
			exit(-1);
			break;
		case 0:
			signal(SIGUSR2,sig_H_child);
			printf("Figlio 1 invia SIGUSR1 al padre:\n");
			kill(getppid(),SIGUSR1);	//(1)
			printf("Figlio 1 attende...\n");
			pause();
			exit(EXIT_SUCCESS);
			break;
		default:
			signal(SIGUSR1,sig_H_parent);	//Sia parent che p2
			switch(p2=fork()){
				case -1:
					fprintf(stderr,"Errore nella seconda fork\n");
					exit(-2);
					break;
				case 0:
					signal(SIGUSR1,sig_H_child);
					printf("Figlio 2 attende...\n");
					pause();			//(3)
					printf("Figlio 2 invia SIGUSR2 al padre:\n");
					kill(getppid(),SIGUSR2);	//(4)
					exit(EXIT_SUCCESS);
					break;
				default:
					signal(SIGUSR2,sig_H_parent);
					break;
			}

			printf("Padre attende...\n");
			pause();
			printf("Padre invia SIGUSR1 al figlio 2:\n");
			kill(p2,SIGUSR1);			//(2)
			printf("Padre attende...\n");
			pause();
			printf("Padre invia SIGUSR2 al figlio 1:\n");
			kill(p1,SIGUSR2);

			break;
	}
	return EXIT_SUCCESS;
}
