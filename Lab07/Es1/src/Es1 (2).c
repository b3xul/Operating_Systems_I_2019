/*
 ============================================================================
 Name        : es1.c
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

int main (int argc, char **argv)
{
	int res=wait(NULL);
    printf("wait=%d\n",res);
	pid_t pid=fork();

    if(!pid){

    	fprintf (stdout, "pidSon=%d \nMIO PADRE E': %d\n", getpid(),getppid());
    	sleep(5);
    	fprintf(stdout,"Ora il mio nuovo padre e': %d\n",getppid());
    	execl ("/bin/ls", "myls", (char *) 0);
    }
    else{
    	sleep(2);
    	printf("pidFather=%d\n",pid);
    	//while(wait(NULL)!=pid);
    	fprintf (stdout, "End program\n");
    }
    return (1);
}
