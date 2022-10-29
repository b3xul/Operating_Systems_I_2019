/*
 ============================================================================
 Name        : Es3v3.c
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
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 512

int main() {
	int pipefd[2];	//N.B. Scrivo su pipefd[1] e leggo da pipefd[0]
	char *buffer=NULL;
	char received[BUF_SIZE];
	int n;
	unsigned long int line_length=0;
	int dim_getline;

	setbuf(stdout,NULL);
	int i,j;
	FILE *fOut=fopen("fOut.txt","w");
	setbuf(fOut,NULL);
	for(i=0;i<1000;i++){
		for(j=0;j<100;j++){
			fprintf(fOut,"%d",i);
		}
		fprintf(fOut,"\n");
	}

	pipe(pipefd);

	pid_t child_p = fork();
	switch(child_p) {
		case -1:
			printf("error: Could not fork.\n");
			exit(1);
			break;
		case 0:

			// Figlio legge file linea per linea e manda le stringhe al padre

			close(pipefd[0]);
			FILE *f1 = fopen("fOut.txt", "r");
			while((dim_getline=getline(&buffer,&line_length,f1))!=-1){
				printf("[LINE]: %s[LINE_LENGTH]: %ld\t[LUNGHEZZA EFFETTIVA]: %d", buffer,line_length,dim_getline);

				if((n=write(pipefd[1], buffer, BUF_SIZE))==-1)
					printf("Oh dear, something went wrong with write()! %s\n", strerror(errno));

				printf("\n[N_WRITE]:%d\n\n", n);

				//n=write(pipefd[1], buffer, dim_getline );

			}
			//sleep(10);
			fclose(f1);
			exit(EXIT_SUCCESS);
			break;
		default:

			close(pipefd[1]);
			while((n=read(pipefd[0], received, BUF_SIZE))>0){
				//sleep(1);
				printf("\n[RECEIVED] %s[N_READ]:%d\n\n", received,n);
			}
			printf("\nSono uscito!\n");
			if(n!=0)
				printf("Oh dear, something went wrong with read()! %d:%s\n", errno,strerror(errno));
			break;
	}

	return 0;
}
