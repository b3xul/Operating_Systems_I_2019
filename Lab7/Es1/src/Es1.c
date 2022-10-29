/*
 ============================================================================
 Name        : Es1.c
 Author      : Bexul
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>



void sig_handler(int sig){
	return;
}

int main(void) {
	pid_t figlio1,figlio2;
	FILE *f1,*f2;
	long unsigned int line_length=0;
	char* buffer=NULL;

	switch(figlio1=fork()){
		case -1:
			fprintf(stderr,"Prima fork fallita\n");
			exit(-1);
			break;
		case 0:
			signal(SIGUSR1,sig_handler);
			pause();
			if((f1=fopen("test_1.txt","r"))==NULL){
				fprintf(stderr,"Errore nell'apertura del primo file\n");
				exit(-2);
			}
			//fgets(s,LINE_LENGTH,f1);
			/*Come fgets ma piu' secura perche' nel caso la linea contenga piu' caratteri di LINE_LENGTH
            viene riallocata s per far si' che possa contenerli. A differenza di fgets non salva il null a fine stringa
            consentendo di rilevare eventuali null all'interno della stringa
            N.B. Alternativa: char* buffer=NULL;unsigned long int line_length=0; Automaticamente*/
			while((getline(&buffer,&line_length,f1))!=-1){
                printf("(dimensione %ld): %s",line_length,buffer);
			}
			//kill(SIGCHLD,getppid()); ridondante, lo fa già la exit!
			exit(0);
			break;
		default:
            switch(figlio2=fork()){
                case -1:
                    fprintf(stderr,"Seconda fork fallita\n");
                    exit(-1);
                    break;
                case 0:
                	signal(SIGUSR2,sig_handler);
                	pause();
                    if((f2=fopen("test_2.txt","r"))==NULL){
                        fprintf(stderr,"Errore nell'apertura del secondo file\n");
                        exit(-2);
                    }
                    while((getline(&buffer,&line_length,f2))!=-1){
                        printf("(dimensione %ld): %s",line_length,buffer);
                    }
                    exit(0);
                    break;
                default:
                    /*wait((int*)0);	2 modi possibili: doppia wait più semplice
                    wait((int*)0);*/
                	signal(SIGCHLD,sig_handler);
                	kill(figlio1,SIGUSR1);
                	pause();
                	kill(figlio2,SIGUSR2);
                	pause();
                    printf("Figli terminati\n");
                    break;
            }
	}
	return EXIT_SUCCESS;
}
