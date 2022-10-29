#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUFFSIZE 50

void copia_file(char* path1,int fdW);

void handler(int sig){
    if(sig==SIGUSR1){
        printf("Ricevuto sigusr1\n");
        return;
    }
}
void father_handler(int sig){
    if(sig==SIGCHLD){
        printf("Ricevuto sigchld\n");
        return;
    }
}
int main()
{
    pid_t pid1,pid2;

    switch(pid1=fork()){
        case -1:
            fprintf(stderr,"Errore nel primo fork()\n");
            return (-1);
            break;
        case 0:
            signal(SIGUSR1,handler);
            pause();
            copia_file("son1.txt",STDOUT_FILENO);
            printf("Termino pid1\n");
            exit(0);
            break;
        default:
            signal(SIGCHLD,father_handler);
            switch(pid2=fork()){
                case -1:
                    fprintf(stderr,"Errore nel secondo fork()\n");
                    return (-2);
                    break;
                case 0:
                    copia_file("son2.txt",STDOUT_FILENO);
                    sleep(5);
                    kill(pid1,SIGUSR1);
                    printf("Termino pid2\n");
                    exit(0);
                    break;
                default:
                    printf("Figlio1:%d\nFiglio2:%d\n",pid1,pid2);
                    pause();
                    pause();
                    break;
            };
            break;
    };

    return 0;
}
void copia_file(char* path1,int fdW){
	int nR, nW, fdR;
	char buf[BUFFSIZE];

	fdR = open (path1, O_RDONLY);
	if (fdR==(-1) || fdW==(-1)) {
		fprintf (stdout, "Errore nell'apertura di un file: %s\n",strerror(errno));
		exit (-3);
	}
	printf("Copio primi 50 byte di %s\n\n",path1);
	if((nR = read (fdR, buf, BUFFSIZE)) > 0) {
		nW = write (fdW, buf, nR);
		if (nR != nW)
			fprintf (stderr,"Error: Read %d, Write %d).\n", nR, nW);
	}
	if (nR < -1)
		fprintf (stderr, "Write Error.\n");
    fprintf(stdout,"\n\nFine copia.\n");
	close (fdR);

	return;
}
