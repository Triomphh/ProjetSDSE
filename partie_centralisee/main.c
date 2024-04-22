/* 
    Processus principal qui exécute tous les éléments de la partie centralisée 

    cmd compilation : 
        clear; gcc -o serveur main.c communication.c gestion_requete.c ../fonctions/creerSocketTCP.c; ./serveur 4006
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "communication.h"
#include "gestion_requete.h"





int main( int argc, char **argv )
{
    if ( argc < 2 )
    {
        fprintf( stderr, "Nombre d'arguments insuffisants: %s <port>\n", argv[0] );
        exit( EXIT_FAILURE );
    }
    
    printf( "%d\n", atoi(argv[1]) );


    pid_t pid;
    /* Gestionnaire de signal */
    // signal( SIGINT, arret_serveur );

    

    /* Processus Communication */
    pid = fork();
    if ( pid == -1 ) 
    {
        perror( "Erreur lors de la création du processus de communication " );
        exit( EXIT_FAILURE );
    } 
    else if (pid == 0) 
    {
        init_communication( atoi(argv[1]) );                                            
        exit(EXIT_SUCCESS);                                                             // Termine le processus enfant après l'exécution
    }

    /* Processus Gestion Requête */
    pid = fork();
    if ( pid == -1 ) 
    {
        perror( "Erreur lors de la création du processus de gestion des requêtes " );
        exit( EXIT_FAILURE );
    } 
    else if ( pid == 0 ) 
    {
        init_gestion_requete();
        exit( EXIT_SUCCESS );                                                           // Termine le processus enfant après l'exécution
    }

    while (wait(NULL) > 0);




    // /* Processus Communication */
    // init_communication( atoi(argv[1]) );

    // /* Processus Gestion Requête */
    // init_gestion_requete();




    return 0;
}