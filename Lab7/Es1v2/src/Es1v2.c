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



void sig_handler_v2(int sig){
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
			signal(SIGUSR1,sig_handler_v2);
			if((f1=fopen("test_1.txt","r"))==NULL){
				fprintf(stderr,"Errore nell'apertura del primo file\n");
				exit(-2);
			}

			while((getline(&buffer,&line_length,f1))!=-1){
                printf("%s",buffer);
			}
			/*for(i=0;i<5000;i++){
				printf("file1 file1file1\n");
			}*/
			//kill(SIGCHLD,getppid());
			exit(0);
			break;
		default:
            switch(figlio2=fork()){
                case -1:
                    fprintf(stderr,"Seconda fork fallita\n");
                    exit(-1);
                    break;
                case 0:
                	signal(SIGUSR2,sig_handler_v2);
                    if((f2=fopen("test_2.txt","r"))==NULL){
                        fprintf(stderr,"Errore nell'apertura del secondo file\n");
                        exit(-2);
                    }
                    while((getline(&buffer,&line_length,f2))!=-1){
                        printf("%s",buffer);
                    }
        			/*for(i=0;i<5000;i++){
        				printf("file2 file2file\n");
        			}*/
                    //kill(SIGCHLD,getppid());
                    exit(0);
                    break;
                default:
                    wait((int*)0);
                    wait((int*)0);
                	/*signal(SIGCHLD,sig_handler_v2);
                	pause();
                	pause();*/
                    printf("Figli terminati\n");
                    break;
            }
	}
	return EXIT_SUCCESS;
}
