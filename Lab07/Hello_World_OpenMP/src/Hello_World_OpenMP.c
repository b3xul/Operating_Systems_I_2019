/*
 ============================================================================
 Name        : Hello_World_OpenMP.c
 Author      : Bexul
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

//To activate the OpenMP extensions for C/C++ and Fortran, the compile-time flag -fopenmp must be specified
//file->properties->C Build->Settings->Miscellaneous->aggiungere flag -fopenmp
int main(void) {

#pragma omp parallel
{
	printf("Mi sto parallelizzando tuttoooo (CPU %d):Q__\n",omp_get_thread_num());
}

	return EXIT_SUCCESS;
}
