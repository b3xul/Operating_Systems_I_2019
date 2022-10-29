/*
 ============================================================================
 Name        : Es3.c
 Author      : Bexul
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <malloc.h>
#include <errno.h>
#include <string.h>

#define BUFF_SIZE 512

int main(void) {

	FILE* f1;
	pid_t pid;
	int pipe_descriptors[2];	//file descriptors della pipe
	char* buffer=NULL;			//stringhe da passare	N.B. Non deve essere puntatore a null, al massimo malloc (0)!
//	int buf_length=0;
	char* buffer_Parent=NULL;
	unsigned long int line_length=0;	//lunghezza delle stringhe da passare
	int n=0;

	/*int i;
	unsigned long int numero;
	char stringa[125];*/

	setbuf(stdout,NULL);

	int status = pipe(pipe_descriptors);	//creazione pipe

	if (status == -1 ) {
		fprintf(stderr,"Errore nell'apertura della pipe\n");
		exit(-1);
	}
	switch(pid=fork()){
		case -1:
			fprintf(stderr,"Errore nella fork\n");
			exit(-2);
			break;
		case 0:	//Figlio scrive sulla pipe (PD[0] CHIUSO, PD[1] APERTO)

			if((f1=fopen("test_1.txt","r"))==NULL){
				kill(getppid(),SIGSTOP);	//avvisare il padre di morire perchè tanto non riceverà nulla oppure chiudere la pipe
				fprintf(stderr,"Errore nell'apertura del primo file\n");
				exit(-2);
			}

			close(pipe_descriptors[0]);

			//while((fgets(buffer,300,f1))!=NULL){
			while((getline(&buffer,&line_length,f1))!=-1){	//finchè ci sono linee da leggere dal file continua a piazzarle in buffer e mandarle al parent
				line_length=strlen(buffer);

				n = write (pipe_descriptors[1], &line_length, sizeof(unsigned long int));	//Se inverto l'ordine stack smashing ???
				printf ("FIGLIO: Ho scritto %d bytes. La linea successiva avrà dimensione: %ld\t", n,line_length);

				n = write (pipe_descriptors[1], &buffer, BUFF_SIZE);	//scrive in pipe_descriptors[1] fino a line_length byte presi da buffer
				if(n==-1){
					fprintf(stderr,"%s",strerror(errno));
				}

				printf ("FIGLIO: Linea di lunghezza: %ld : [%s]", line_length, buffer);

				//printf ("FIGLIO: Scritti %d bytes sulla pipe: [%s]", n, buffer);		//N.B. n si duplica e viene usato come nW in scrittura e come nR in lettura
			}

			/*numero=5;
			strcpy(stringa,"Robe");

			for(i=0;i<2;i++){
				n=write(pipe_descriptors[1],&numero,sizeof(unsigned long int));
				n=write(pipe_descriptors[1],&stringa,numero);

				printf("FIGLIO:numero:%ld \t %s\t\t",numero,stringa);
			}*/
			sleep(13);
			close(pipe_descriptors[1]);		//Fine scrittura: stacca ingresso pipe
			exit(EXIT_SUCCESS);
			break;
		default: //Padre legge dalla pipe (PD[0] APERTO, PD[1] CHIUSO)

			buffer_Parent=(char*)malloc(300*sizeof(char));
			close(pipe_descriptors[1]);
			while((n = read (pipe_descriptors[0], &line_length, sizeof(unsigned long int)))>0){

				n = read (pipe_descriptors[0], &buffer, BUFF_SIZE);	//finchè legge dalla pipe almeno 1 byte (zero byte =EOF) continua a leggere
				printf ("PADRE: Ho letto %d bytes. La linea successiva avrà dimensione: %ld\t", n,line_length);
				/*if(line_length>buf_length){
					buffer=(char*)realloc(buffer,line_length*sizeof(char));
					buf_length=line_length;
				}*/

				printf ("PADRE: Letti %d bytes dalla pipe: [%s]", n, buffer);
			}


			/*numero=0;

			for(i=0;i<2;i++){
				n=read(pipe_descriptors[0],&numero,sizeof(unsigned long int));
				n=read(pipe_descriptors[0],&stringa,numero);
				printf("PADRE:numero:%ld \t %s\t\t",numero,stringa);
			}*/
			close(pipe_descriptors[0]);		//Fine lettura: stacca uscita pipe
	}

	return EXIT_SUCCESS;
}
/*
	#include <stdio.h>
    #include <stdlib.h>

    int main(int argc, char *argv[]){
    	FILE *f1;
        char *line = NULL;
        int len = 0;
        int nread;

        f1 = fopen("test_1.txt", "r");

        if (f1 == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }

        while ((nread = getline(&line, &len, f1)) != -1) {
            printf("Retrieved line of length %d:\n", nread);
            fwrite(line, nread, 1, );

        }

        free(line);
        fclose(f1);
        exit(EXIT_SUCCESS);
     }
*/
