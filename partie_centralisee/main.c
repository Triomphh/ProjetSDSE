/* 
    Processus principal qui exécute tous les éléments de la partie centralisée 

    cmd compilation : 
        clear; gcc -o serveur main.c communication.c ../fonctions/creerSocketTCP.c; ./serveur 4006
*/

#include <stdio.h>
#include <stdlib.h>

#include "communication.h"



int main( int argc, char **argv )
{
    printf( "%d\n", atoi(argv[1]) );

    /* Processus Communication */
    init( atoi(argv[1]) );

    return 0;
}