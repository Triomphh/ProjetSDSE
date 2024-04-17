/*
    À faire :
        - ouvrir une connexion TCP
            * créer socket TCP ( serveur )                X
            * Configurer le nbr de connexions pendantes   X
            * attendre les connexions                     .
                . 1 processus par client                  . 
            * 

*/

/*
    cmd compilation : clear; gcc -o communication main.c communication.c ../fonctions/creerSocketTCP.c; ./communication 4006
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

#include "../fonctions/creerSocketTCP.h"

#define TAILLEBUF 1024




void traiter( int socket_service )
{
    char buffer[ TAILLEBUF ];
    ssize_t nbytes; // ssize_t compteur de bytes, signed pour pouvoir stocker une potentielle erreur avec la valeur -1 ( recv donne un ssize_t )

    while ( 1 )
    {
        memset( buffer, 0, TAILLEBUF );  // Vider le buffer
        nbytes = recv( socket_service, buffer, TAILLEBUF - 1, 0 );                                  //      On attend un message du client ( TAILLEBUF - 1 pour stocker le '\0' )

        if ( nbytes > 0 )                                                                           //      On regarde si le client a envoyé quelque chose
        {
            buffer[ nbytes ] = '\0';    // On "termine"/"coupe" la chaîne de char.
            printf( "CLIENT : %s\n", buffer );

            // TEST renvoit du message au client
            send( socket_service, buffer, nbytes, 0 );
        }
        else if ( nbytes == 0 )                                                                     //      Si le client renvoit 0, c'est qu'il s'est déconnecté
        {
            printf( "Client déconnecté.\n" );
            break;
        }
        else                                                                                        //      Sinon, il y a eu une erreur...
        {
            perror( "ERROR recv." );
            break;
        }
    }

    close( socket_service );                                                                        // On ferme la socket associée au client
}




int init( int port )
{
    static struct sockaddr_in addr_serveur;
    static struct sockaddr_in addr_client;
    socklen_t addrlen;
    int socket_ecoute, socket_service;


    // Création socket TCP d'écoute (serveur)
    socket_ecoute = creerSocketTCP( &addr_serveur, port );
    if ( bind( socket_ecoute, (struct sockaddr *)&addr_serveur, sizeof( addr_serveur ) ) == -1 )
	{
		perror( "Erreur lors de la liaison de la socket." );
		exit( EXIT_FAILURE );
	}

    // Configurer le nombre maximum de connexions pendantes
    if ( listen( socket_ecoute, 10 ) == -1 )
    {
        perror( "ERREUR listen()" );
        return -1;
    }

    // Attente de connexion client
    addrlen = sizeof( addr_client ); // ?
    while( 1 )																						// Attente de connexion du client sur la socket serveur
    {
        socket_service = accept( socket_ecoute, (struct sockaddr *)&addr_client, &addrlen );		// La connexion du client renvoit une socket de service pour le client
        if ( fork() == 0 ) // Création d'un processus par client
        {                                                                                           // Processus fils :
            close( socket_ecoute ); 
			traiter( socket_service );                                                              //      On traite la communication avec le client
			exit( 0 );
        }
		close( socket_service );
    }

    return 0;
}
