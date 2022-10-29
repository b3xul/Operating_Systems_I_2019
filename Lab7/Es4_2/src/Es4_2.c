/*
 ============================================================================
 Name        : Es4_2.c
 Author      : Bexul
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc,char *argv[]) {

	/*if(argc<2){
		fprintf(stderr,"Errore nel numero di argomenti\n");
		exit(-1);
	}*/
	int i,length;
	char stringa[100];

	fscanf(stdin,"%s",stringa);
	length=strlen(stringa);
	for(i=0;i<length;i++)
		stringa[i]=toupper(stringa[i]);

	fprintf(stdout,"%s",stringa);
	/*char* p=argv[1];

	while(*p!='\0'){
		*p=toupper(*p);
		p++;
	}
	fprintf(stdout,"%s",argv[1]);*/

	return EXIT_SUCCESS;
}
