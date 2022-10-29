#include<stdio.h>
#include<stdlib.h>
#include<mylib.h>

#define BUF 1024

int main(int argc, char* argv[]){
	FILE* fi;
	FILE* fo;

	fi=fopen(argv[1],"r");
	if(fi==NULL){
		fprintf(stderr,"File input non trovato\n");
		exit(-1);
	}
	
	fo=fopen(argv[2],"w");
	if(fo==NULL){
		fprintf(stderr,"File output non trovato\n");
		exit(-2);
	}
	char content[BUF];
	
	while(fgets(content,BUF,fi)!=NULL){
		fputs(content,fo);
	}
	
	printf("Prova lib: %d",sum(40,2));
	
	fclose(fi);
	fclose(fo);
	return 0;
}
