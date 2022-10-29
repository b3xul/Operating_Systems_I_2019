/*
 ============================================================================
 Name        : TutorialSemaforiPipe.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void semaphoreInit(int* S){		//Crea la pipe-semaforo inizializza con vettore di pipe descriptors S
	if(pipe(S)==-1){
		fprintf(stderr,"Error Init");
		exit(-1);
	}
	return;
}

void semaphoreSignal(int* S){	//Scrive sulla pipe-semaforo un carattere, dando il via libera a entrare nella SC
	char start='a';
	if(write(S[1],&start,sizeof(char))!=1){	//N.B. Si assume di non riempire mai la pipe completamente, altrimenti controllo aggiuntivo invece di errore e terminazione
		fprintf(stderr,"Error Signal");
		exit(-1);
	}
	return;
}

void semaphoreWait(int* S){		//Legge dalla pipe-semagoforo un carattere, entrando nella SC e acquisendone il lock
	char ok;
	if(read(S[0],&ok,sizeof(char))!=1){		//N.B. La read è bloccante: se pipe vuota read si blocca, svolgendo la funzione di wait
		fprintf(stderr,"Error Wait");
		exit(-1);
	}
}

int main(void) {
	int S[2];	//pipe-semaforo descriptors
	pid_t pid;
	semaphoreInit(S);	//N.B. Inizializzo i semafori PRIMA della fork!

	pid=fork();
	if(!pid){	//figlio
		semaphoreWait(S);
		printf("Wait done!\n");
	}
	else{
		printf("Going to sleep...\n");
		sleep(3);
		semaphoreSignal(S);
		printf("Signal done!\n");
	}
	return EXIT_SUCCESS;
}

