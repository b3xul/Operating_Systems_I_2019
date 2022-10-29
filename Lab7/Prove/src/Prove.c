/*
 ============================================================================
 Name        : Prove.c
 Author      : Bexul
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <omp.h>

void SH(int signo){
	printf("Ricevuto SIGALARM\n");
}

#define SIZE 524288
int fd[2];

int main () {
	setbuf (stdout, 0);

	/*int i, n, nR, nW;
		char c = '1';


		pipe(fd);
		n = 0;
		if (fork()) {
			fprintf (stdout, "\nFather PID=%d\n", getpid());
			sleep (1);
			for (i=0; i<SIZE; i++) {
				nW = write (fd[1], &c, 1);
				* Se nessuno legge la write continua a scrivere fin quando non riempie la pipe (65535 Bytes), poi si blocca e attende
				 * Quando qualcuno inizia leggere, man mano che svuota la pipe la write ricomincia a scrivere (quando si liberano size bytes li scrive) finchè non esaurisce ciò che ha da scrivere
				 * La pipe quindi rimane sempre in stato PIENA/PIENA-1 ELEMENTO finchè entrambi leggono e scrivono (SE IL READER È PARTITO DOPO IL WRITER)
				 *
				n = n + nW;
				fprintf (stdout, "W %d\r", n);
			}
		}
		else {
			fprintf (stdout, "Child PID=%d\n", getpid());
			sleep (10);
			for (i=0; i<SIZE; i++) {
				//Il figlio legge altrettanto
				nR = read (fd[0], &c, 1);
				n = n + nR;
				fprintf (stdout, "\t\t\t\tR %d\r", n);
			}
		}

		int a,b;
		signal(SIGALRM,SH);

		a=alarm(5);
		printf("%d\n",a);
		sleep(1);
		b=alarm(3);
		printf("%d\n",b);
		pause();
		printf("I woke up");*/

	int i,j,a,n,pid;
	a=2;
	n=3;
	for(i=0;i<a;i++){
		for(j=0;j<n;j++){
			pid=fork();
			if(pid>0)
				break;
			else{
				if(j==n-1)
					exit(0);
			}
		}
	}

	printf("pid=%d\n",getpid());

	return 0;
}
