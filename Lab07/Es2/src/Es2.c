/*
 ============================================================================
 Name        : Es2.c
 Author      : Bexul
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
#include <unistd.h>

void sig_handler(int sig){
	return;
}

int main(void) {

	pid_t pid;

	switch(pid=fork()){
		case -1:
			fprintf(stderr,"Fork fallita\n");
			exit(-1);
		case 0:
			signal(SIGINT,sig_handler);	//Non c'è concorrenza perchè invio sigint al pid del padre quindi sicuramente sarà lui a gestirlo
			pause();
			printf("\n%d\n",getpid());
			exit(0);
		default:
			signal(SIGINT,sig_handler);
			pause();
			kill(pid,SIGINT);
			while(wait((int*)0)!=pid);
	}
	return EXIT_SUCCESS;
}
