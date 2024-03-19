/*
    À faire :
        - ouvrir une connexion TCP
            * créer socket TCP ( serveur )                X
            * Configurer le nbr de connexions pendantes   X
            * attendre les connexions                     .
                . 1 processus par client                  . 
            * 

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

#include "creerSocketTCP.h"

#define TAILLEBUF 20


int init( int port )
{
    static struct sockaddr_in addr_serveur;
    static struct sockaddr_in addr_client;
    socklen_t addrlen;
    int socket_ecoute, socket_service;

    // Création socket TCP d'écoute (serveur)
    socket_ecoute = creerSocketTCP( port );

    // Configurer le nombre maximum de connexions pendantes
    if ( listen( socket_ecoute, 5 ) == -1 )
    {
        perror( "ERREUR listen()" );
        return -1;
    }

    // Attente de connexion client
    addrlen = sizeof( addr_client ); // ?
    while( 1 )
    {
        socket_service = accept( socket_ecoute, (struct sockaddr *)&addr_client, &addrlen );
        if ( fork() == 0 ) // Création d'un processus par client
        {
            close( socket_ecoute ); // Pour éviter les duplicatas ?
            // ...fonction qui traite la communication avec le client
			// traiter();
			exit( 0 );
        }
		close( socket_service );
    }

    return 0;
}
