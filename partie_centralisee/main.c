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

#include "common.h"
#include "communication.h"
#include "gestion_requete.h"


volatile sig_atomic_t arret = 0;                                                        // Variable globale permettant d'arrêter le serveur (sortir des boucles infinies de lecture)                    

void arret_serveur()                                                                    // Fonction d'arrêt propre du serveur déclenchée par un signal
{
    arret = 1;                                                                          //      Sortie des boucles de lecture ( la fermeture propre de chaque processus est géré par lui-même (le processus) )
    unlink( REQUEST_PIPE );                                                             //      Suppression du pipe nommé ( communication |> gestion_requete )
    printf( "\nNettoyage effectué. Fermeture du serveur.\n" );
}


int main( int argc, char **argv )
{
    if ( argc < 2 )
    {
        fprintf( stderr, "Nombre d'arguments insuffisants: %s <port>\n", argv[0] );
        exit( EXIT_FAILURE );
    }
    
    printf( "%d\n", atoi(argv[1]) );


    
    /* Processus Communication */
    pid_t pid = fork();
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


    /* Gestionnaire de signaux */
    signal( SIGINT, arret_serveur );

    while ( !arret && wait(NULL) > 0);                                                  // Boucle principale du serveur qui attend la fin des processus fils ( wait() retourne -1 si aucun fils n'est en cours d'exécution ) ou l'arret forcé ( par SIGINT )




    return 0;
}