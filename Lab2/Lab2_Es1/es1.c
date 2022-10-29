#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include <sys/types.h>
/*Perchè ordine diverso?*/


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

	//printf("(full path= %s)\n",fullPath);
	if(dir==NULL)
		fprintf(stderr,"Path non trovato\n");
	else{
		printf("\n%s:\n",fullPath);
		while((directoryP=readdir(dir))!=NULL){
			if(strcmp(directoryP->d_name,".")!=0&&strcmp(directoryP->d_name,"..")!=0){
				if(directoryP->d_type==DT_DIR)	/*N.B. link non ha d_type==dt_dir*/
					printf("[D]");
				printf("%s\t",directoryP->d_name);
			}
		}

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
					printf("\n");
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

