/*
 ============================================================================
 Name        : Es2_pipe.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
/*https://beej.us/guide/bgc/html/multi/setvbuf.html*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void semaphoreInit(int* S){		//Crea la pipe-semaforo inizializza con vettore di pipe descriptors S
	if(pipe(S)==-1){
	fprintf(stderr,"Error Init");
	exit(-1);
	}
	return;
}

void semaphoreSignal(int* S){	//Scrive sulla pipe-semaforo un carattere, dando il via libera a entrare nella SC
	char start='a';
	if(write(S[1],&start,sizeof(char))!=1){	//N.B. Si assume di non riempire mai la pipe completamente, altrimenti controllo aggiuntivo invece di errore e terminazione
	fprintf(stderr,"Error Signal");
	exit(-1);
	}
	return;
}

void semaphoreWait(int* S){		//Legge dalla pipe-semagoforo un carattere, entrando nella SC e acquisendone il lock
	char ok;
	if(read(S[0],&ok,sizeof(char))!=1){		//N.B. La read è bloccante: se pipe vuota read si blocca, svolgendo la funzione di wait
	fprintf(stderr,"Error Wait");
	exit(-1);
	}
}

int semA[2],semB[2],semC[2],semD[2],semE[2],semF[2],semG[2],semH[2], semI[2];	//pipe-semaforo descriptors

int main(void) {
	pid_t pidB,pidC,pidD,pidE,pidF,pidG,pidH,pidI;

	/*Disattivo il buffering su stdout (uno dei 2*/
	setbuf(stdout, NULL);
	//setvbuf(stdout, NULL, _IONBF, BUFSIZ);

	/*Inizializzo i semafori PRIMA della fork!*/
	semaphoreInit(semA);
	semaphoreInit(semB);
	semaphoreInit(semC);
	semaphoreInit(semD);
	semaphoreInit(semE);
	semaphoreInit(semF);
	semaphoreInit(semG);
	semaphoreInit(semH);
	semaphoreInit(semI);

	semaphoreSignal(semA);

	//while(1){
		switch(pidB=fork()){
			case -1:
				fprintf(stderr,"Error Fork");
				exit(-1);
				break;

			case 0:
				/*PROCESSO B*/

				while(1){
					semaphoreWait(semB);
					sleep(1);
					printf("B ");
					//fflush(stdout);
					semaphoreSignal(semI);
				}
				break;

			default:
				switch(pidC=fork()){
					case -1:
						fprintf(stderr,"Error Fork");
						exit(-1);
						break;

					case 0:
						/*PROCESSO C*/

						while(1){
							semaphoreWait(semC);
							sleep(2);
							printf("C ");
							//fflush(stdout);
							semaphoreSignal(semE);
							semaphoreSignal(semF);
						}
						break;

					default:
						switch(pidD=fork()){
							case -1:
								fprintf(stderr,"Error Fork");
								exit(-1);
								break;

							case 0:
								/*PROCESSO D*/

								while(1){
									semaphoreWait(semD);
									sleep(3);
									printf("D\n");
									semaphoreSignal(semH);
								}
								break;

							default:
								switch(pidE=fork()){
									case -1:
										fprintf(stderr,"Error Fork");
										exit(-1);
										break;

									case 0:
										/*PROCESSO E*/
										while(1){
											semaphoreWait(semE);
											sleep(1);
											printf(" E ");
											//fflush(stdout);
											semaphoreSignal(semG);
										}
										break;
									default:
										switch(pidF=fork()){
											case -1:
												fprintf(stderr,"Error Fork");
												exit(-1);
												break;

											case 0:
												/*PROCESSO F*/
												while(1){
													semaphoreWait(semF);
													sleep(2);
													printf("F\n");
													semaphoreSignal(semG);
												}
												break;
											default:
												switch(pidG=fork()){
													case -1:
														fprintf(stderr,"Error Fork");
														exit(-1);
														break;

													case 0:
														/*PROCESSO G*/
														while(1){
															semaphoreWait(semG);
															semaphoreWait(semG);
															sleep(1);
															printf("  G");
															//fflush(stdout);
															semaphoreSignal(semI);
														}
														break;
													default:
														switch(pidH=fork()){
															case -1:
																fprintf(stderr,"Error Fork");
																exit(-1);
																break;

															case 0:
																/*PROCESSO H*/
																while(1){
																	semaphoreWait(semH);
																	sleep(3);
																	printf(" H\n");
																	semaphoreSignal(semI);
																}
																break;
															default:
																switch(pidI=fork()){
																	case -1:
																		fprintf(stderr,"Error Fork");
																		exit(-1);
																		break;

																	case 0:
																		/*PROCESSO I*/
																		while(1){
																			semaphoreWait(semI);
																			semaphoreWait(semI);
																			semaphoreWait(semI);
																			sleep(1);
																			printf("  I\n");
																			semaphoreSignal(semA);
																		}
																		break;
																	default:
																		while(1){	//padre A
																			semaphoreWait(semA);
																			printf("  A\n");
																			semaphoreSignal(semB);
																			semaphoreSignal(semC);
																			semaphoreSignal(semD);
																		}
																}
														}
												}
										}
								}
						}

					}
				}
	//}

	return EXIT_SUCCESS;
}
