/*
 ============================================================================
 Name        : Es2_thread.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

/*
 ============================================================================
 Name        : TutorialSemafori.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
//#include <sys/types.h> già incluso da semaphore.h
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

//N.B.  project -> properties -> C/C++ Build -> Settings -> Tool Settings tab -> GCC C Linker -> Miscellaneous -> add -pthread nel campo Linker flags
sem_t semA,semB,semC,semD,semE,semF,semG,semH, semI;

void *tfA (void *arg) {
	while(1){
		sem_wait(&semA);
		sleep(1);
		printf("  A\n");
		/*N.B. Qua non si può fare un unico semaforo perchè rischierei starvation... o no?*/
		sem_post(&semB);
		sem_post(&semC);
		sem_post(&semD);
	}
}

void *tfB (void *arg) {
	while(1){
		sem_wait(&semB);
		sleep(2);
		printf("B ");
		sem_post(&semI);
	}
}

void *tfC (void *arg) {
	while(1){
		sem_wait(&semC);
		sleep(3);
		printf("C ");
		sem_post(&semE);
		sem_post(&semF);
	}
}

void *tfD (void *arg) {
	while(1){
		sem_wait(&semD);
		sleep(4);
		printf("D\n");
		sem_post(&semH);
		//sem_post(&semI);	RIDONDANTE, dato che se H ha finito sicuramente anche D ha già finito, per cui basta quello a dire ad H di partire!
	}
}

void *tfE (void *arg) {
	while(1){
		sem_wait(&semE);
		sleep(1);
		printf(" E ");
		sem_post(&semG);
	}
}

void *tfF (void *arg) {
	while(1){
		sem_wait(&semF);
		sleep(2);
		printf("F\n");
		sem_post(&semG);
	}
}

void *tfG (void *arg) {
	while(1){
		sem_wait(&semG);
		sem_wait(&semG);
		sleep(1);
		printf("  G");
		sem_post(&semI);
	}
}

void *tfH (void *arg) {
	while(1){
		sem_wait(&semH);
		sleep(5);
		printf(" H\n");
		sem_post(&semI);
	}
}

void *tfI (void *arg) {
	while(1){
		//sem_wait(&semI);
		sem_wait(&semI);
		sem_wait(&semI);
		sem_wait(&semI);
		sleep(1);
		printf("  I\n");
		sem_post(&semA);
	}
}

int main (int argc, char **argv) {

	pthread_t thIDA,thIDB,thIDC,thIDD, thIDE,thIDF,thIDG,thIDH,thIDI;

	/* 1.studio il grafo di precedenza "a mano"
	 * 2.stabilisco il numero di semafori minimo da usare tenendo in considerazione statement sequenziali e concorrenti
	 * 3.stabilisco le routine che ogni thread dovrà svolgere, con sleep se voglio garantire ordinamento, altrimenti senza se voglio sfruttare concorrenza
	 * 4.dichiaro i semafori come globali
	 * 5.inizializzo i semafori
	 * 6.creo e avvio i thread
	 * 7.attendo la terminazione di tutti i thread
	 */
	sem_init(&semA,0,1);
	sem_init(&semB,0,0);
	sem_init(&semC,0,0);
	sem_init(&semD,0,0);
	sem_init(&semE,0,0);
	sem_init(&semF,0,0);
	sem_init(&semG,0,0);
	sem_init(&semH,0,0);
	sem_init(&semI,0,0);

	pthread_create(&thIDA,NULL,tfA,(void*)NULL);
	pthread_create(&thIDB,NULL,tfB,(void*)NULL);
	pthread_create(&thIDC,NULL,tfC,(void*)NULL);
	pthread_create(&thIDD,NULL,tfD,(void*)NULL);
	pthread_create(&thIDE,NULL,tfE,(void*)NULL);
	pthread_create(&thIDF,NULL,tfF,(void*)NULL);
	pthread_create(&thIDG,NULL,tfG,(void*)NULL);
	pthread_create(&thIDH,NULL,tfH,(void*)NULL);
	pthread_create(&thIDI,NULL,tfI,(void*)NULL);

	(void*)pthread_join(thIDA,(void*)NULL);
	(void*)pthread_join(thIDB,(void*)NULL);
	(void*)pthread_join(thIDC,(void*)NULL);
	(void*)pthread_join(thIDD,(void*)NULL);
	(void*)pthread_join(thIDE,(void*)NULL);
	(void*)pthread_join(thIDF,(void*)NULL);
	(void*)pthread_join(thIDG,(void*)NULL);
	(void*)pthread_join(thIDH,(void*)NULL);
	(void*)pthread_join(thIDI,(void*)NULL);

	sem_destroy(&semB);
	sem_destroy(&semC);
	sem_destroy(&semD);
	sem_destroy(&semE);
	sem_destroy(&semF);
	sem_destroy(&semG);
	sem_destroy(&semH);
	sem_destroy(&semI);

return 0;
}
