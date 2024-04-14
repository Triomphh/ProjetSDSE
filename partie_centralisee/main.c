/* 
    Processus principal qui exécute tous les éléments de la partie centralisée 
*/

#include <stdio.h>
#include <stdlib.h>

#include "communication.h"



int main( int argc, char **argv )
{
    printf( "%d\n", atoi(argv[1]) );
    init( atoi(argv[1]) );

    return 0;
}