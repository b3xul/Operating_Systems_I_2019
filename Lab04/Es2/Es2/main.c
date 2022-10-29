#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {
    int i, n, x;
    char str[50];
    pid_t pid;

    n = atoi (argv[1]);
    x = atoi (argv[2]);
    printf("EXEC di %d, figlio di %d: ",getpid(),getppid());
    printf ("run with n=%d\n", n);
    fflush (stdout);
    for (i=0; i<n; i++) {
        if ((pid=fork ()) > 0) {
            printf ("PADRE: io sono %d, figlio di %d, padre di %d, questo e' il mio (n-1)=%d\nORA DORMO\n",getpid(),getppid(), pid, n-1);
            sleep(x);
        }
        else{
            printf ("FIGLIO: io sono %d, figlio di %d, padre di %d, eseguo EXEC con n=%d\n",getpid(),getppid(), pid, n-1);
            sprintf (str, "%s %d %s", argv[0], n-1, argv[2]);
            system (str);
        }
    }
    if(pid==0)
        printf("PADRE %d :MI SONO SVEGLIATO E TERMINO\n",getpid());
    else
        printf("FIGLIO %d :TERMINO\n",getpid());
    exit (0);
}
