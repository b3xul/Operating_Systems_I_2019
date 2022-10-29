#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include <sys/types.h>
/*Perchè ordine diverso? Implementazione di ls -R usa sempre le librerie C nostre ma sfruttando la concorrenza, per cui il risultato potrebbe essere ogni volta diverso come ordine! (di solito ls -R home | sort)*/


void my_ls(const char* fullPath);

int main(int argc,char* argv[]){

	if(argc!=2){
		fprintf(stderr,"Errore nel numero di argomenti\n");
		exit(-1);
	}
	
	my_ls(argv[1]);

	
	return 0;
}
void my_ls(const char* fullPath){

	DIR* dir=opendir(fullPath);
	struct dirent* directoryP;
	char* nextPath;

	if(dir==NULL)
		fprintf(stderr,"Path non trovato\n");
	else{
		printf("%s:\n",fullPath);
		while((directoryP=readdir(dir))!=NULL){
			if(strcmp(directoryP->d_name,".")!=0&&strcmp(directoryP->d_name,"..")!=0){
				if(directoryP->d_type==DT_DIR)	/*N.B. link non ha d_type==dt_dir*/
					printf("[D]");
				printf("%s   ",directoryP->d_name);
			}
		}
		printf("\n\n");

		if(closedir(dir)==-1)
			fprintf(stderr,"Errore chiusura lettura\n");

		dir=opendir(fullPath);

		while((directoryP=readdir(dir))!=NULL){
			if(strcmp(directoryP->d_name,".")!=0&&strcmp(directoryP->d_name,"..")!=0){
				if(directoryP->d_type==DT_DIR){
					nextPath=(char*)malloc((strlen(fullPath)+strlen(directoryP->d_name)+2)*sizeof(char));
					nextPath=strcpy(nextPath,fullPath);					
					nextPath=strcat(nextPath,"/");
					nextPath=strcat(nextPath,directoryP->d_name);
					my_ls(nextPath);
					free(nextPath);
				}
			}
		}

		if(closedir(dir)==-1)
			fprintf(stderr,"Errore chiusura lettura\n");


	}
		
	return;
}

