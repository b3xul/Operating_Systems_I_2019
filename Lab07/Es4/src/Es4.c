/*
 ============================================================================
 Name        : Es4.c
 Author      : Bexul
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char*argv[]) {

	if(argc<2){
		fprintf(stderr,"Errore nel numero di argomenti");
		exit(-1);
	}
	if(execl("/bin/echo","Programma1",argv[1],NULL)==-1)
		fprintf(stderr,"Errore exec.");

	return EXIT_SUCCESS;
}
