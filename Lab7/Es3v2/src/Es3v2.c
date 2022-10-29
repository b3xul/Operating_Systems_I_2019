/*
 ============================================================================
 Name        : Es3v2.c
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
#include <fcntl.h>

#define BUFFSIZE 15	//4096

int main () {

	int f1;
	pid_t pid;
	int pipe_descriptors[2];	//file descriptors della pipe
	char buffer[BUFFSIZE];		//buffer da passare
	int n=0;

	/*creazione pipe*/
	int status = pipe(pipe_descriptors);
	if (status == -1 ) {
		fprintf(stderr,"Errore nell'apertura della pipe\n");
		exit(-1);
	}

	switch(pid=fork()){
		case -1:
		fprintf(stderr,"Errore nella fork\n");
			exit(-2);
			break;
		case 0:	//Figlio scrive sulla pipe (PD[0] CHIUSO, PD[1] APERTO)

			/*apertura file*/
			if((f1=open("test_1.txt",O_RDONLY ))==-1){
				kill(getppid(),SIGSTOP);	//avvisare il padre di morire perchè tanto non riceverà nulla oppure chiudere la pipe
				fprintf(stderr,"Errore nell'apertura del primo file\n");
				exit(-2);
			}
			close(pipe_descriptors[0]);

			/*lettura del file per BUFFSIZE e invio in pipe del buffer letto*/
			while ((n = read(f1, buffer, BUFFSIZE)) > 0){
				if (write(pipe_descriptors[1], buffer, n) != n){
					fprintf(stderr,"write error");
					exit(-1);
				}
				if (n < 0){
					fprintf(stderr,"CHILD: read error");
					exit(-2);
				}
				printf("SENT STRING:\t\t%s\n", buffer);
			}
			/*lettura del file per righe e invio in pipe della stringa letta
			while(fgets(buffer,line_length,f1)!=NULL){	//finchè ci sono linee da leggere dal file continua a piazzarle in buffer e mandarle al parent
				n = write (pipe_descriptors[1], &line_length, sizeof( int));	//Se inverto l'ordine stack smashing ???
				printf ("FIGLIO: Ho scritto %d bytes. La linea successiva avrà dimensione: %ld\t", n,line_length);
				n = write (pipe_descriptors[1], &buffer, line_length*sizeof(char));	//scrive in pipe_descriptors[1] fino a line_length byte presi da buffer
				printf ("FIGLIO: Scritti %d bytes sulla pipe: [%s]", n, buffer);		//N.B. n si duplica e viene usato come nW in scrittura e come nR in lettura
			}*/
			sleep(13);
			close(pipe_descriptors[1]);		//Fine scrittura: stacca ingresso pipe
			exit(EXIT_SUCCESS);
			break;
		default: //Padre legge dalla pipe (PD[0] APERTO, PD[1] CHIUSO)
			close(pipe_descriptors[1]);

			while((n = read(pipe_descriptors[0], buffer, BUFFSIZE))>0){
				if (n < 0){
					fprintf(stderr,"PARENT: read error");
					exit(-2);
				}
				printf("RECEIVED STRING:\t%s\n", buffer);
			}
			/*lettura della pipe
			while((n = read(pipe_descriptors[0],&line_length,sizeof( int)))>0){	//finchè legge dalla pipe almeno 1 byte (zero byte=EOF) continua a leggere
				printf ("PADRE: Ho letto %d bytes. La linea successiva avrà dimensione: %ld\t", n,line_length);
				n = read (pipe_descriptors[0], &buffer, line_length*sizeof(char));
				printf ("PADRE: Letti %d bytes dalla pipe: [%s]", n, buffer);
			}*/

			close(pipe_descriptors[0]);		//Fine lettura: stacca uscita pipe
	}

	return EXIT_SUCCESS;
}
