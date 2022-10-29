#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int i;

    /*A
    for (i=1; i<=2; i++){
        if (!fork ())
            printf ("%d\n", i);
    }
    printf ("%d\n", i);
    */

    /*B
    for(i=3; i>1; i--){
        if (fork ())
            printf ("%d\n", i);
    }
    printf ("%d\n", i);
    */

    /*C
    for (i=0; i<2; i++){
        if (fork ())
            fork ();
    }
    printf ("%d\n", i);
    */

    for (i=2; i>=1; i--){
        if (!fork ())
            printf ("%d\n", -i);
        else
            printf ("%d\n", i);
    }
    return 0;
}
