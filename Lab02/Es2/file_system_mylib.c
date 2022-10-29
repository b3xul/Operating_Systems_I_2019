/*
 * main.c
 *
 *  Created on: 08 nov 2018
 *      Author: Bexul
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include "file_system_mylib.c"
#define BUFFSIZE 4096

int main(int argc,char* argv[]){

	if(argc!=3){
		fprintf(stderr,"Numero di argomenti non ammesso.\n");
		exit(-1);
	}

	my_cp(argv[1],argv[2]);
	
	printf("Fine!\n");
	return 0;
}

void my_cp(char* path1,char* path2){

	DIR* dir1=opendir(path1);
	if(dir1==NULL)
			fprintf(stderr,"Path sorgente non trovato\n");

	printf("Creo la cartella: %s\n",path2);
	if(mkdir(path2,0777)==-1){
		fprintf(stderr,"Impossibile creare la cartella, aborted.\n%s\n",strerror(errno));
	   	exit(-2);
	}
	DIR* dir2=opendir(path2);
	if(dir2==NULL)
		fprintf(stderr,"Path destinazione non trovato\n");

	struct dirent* dir1P;
	char* next_path1;
	char* next_path2;
	
	while((dir1P=readdir(dir1))!=NULL){
		if(strcmp(dir1P->d_name,".")!=0&&strcmp(dir1P->d_name,"..")!=0){
			next_path1=(char*)malloc((strlen(path1)+strlen(dir1P->d_name)+2)*sizeof(char));
			next_path1=strcpy(next_path1,path1);
			next_path1=strcat(next_path1,"/");
			next_path1=strcat(next_path1,dir1P->d_name);

			next_path2=(char*)malloc((strlen(path2)+strlen(dir1P->d_name)+2)*sizeof(char));
			next_path2=strcpy(next_path2,path2);
			next_path2=strcat(next_path2,"/");
			next_path2=strcat(next_path2,dir1P->d_name);
			
			if(dir1P->d_type==DT_DIR){
				my_cp(next_path1, next_path2);
			}
			else{
				copia_file(next_path1,next_path2);	
			}
			free(next_path1);
			free(next_path2);
		}
	}

	return;
}

void copia_file(char* path1,char* path2){
	int nR, nW, fdR, fdW;
	char buf[BUFFSIZE];

	fdR = open (path1, O_RDONLY);
	fdW = open (path2, O_WRONLY | O_CREAT , S_IRUSR | S_IWUSR);
	if (fdR==(-1) || fdW==(-1)) {
		fprintf (stdout, "Errore nell'apertura di un file.\n");
		exit (-4);
	}
	printf("Copio file %s in %s\n",path1,path2);
	while ((nR = read (fdR, buf, BUFFSIZE)) > 0) {
		nW = write (fdW, buf, nR);
		if (nR != nW)
			fprintf (stderr,"Error: Read %d, Write %d).\n", nR, nW);
	}
	if (nR < -1)
		fprintf (stderr, "Write Error.\n");
	close (fdR);
	close (fdW);

	return;
}
