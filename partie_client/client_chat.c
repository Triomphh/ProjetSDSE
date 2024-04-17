/*
    cmd compilation : clear; gcc -o client client_chat.c ../fonctions/creerSocketTCP.c; ./client localhost 4006
*/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

#include "../fonctions/creerSocketTCP.h"

#define TAILLEBUF 1024




// Fonction qui permet de connecter le client au serveur choisi
int connexion( char *nom_serveur, int port )
{
	struct hostent *serveur_host;           // Identifiant de la machine serveur
	static struct sockaddr_in addr_serveur; // Adresse de la socket côté serveur
	int sock;                               // Descripteur de la socket
	socklen_t addrlen;                      // Taille de l'adresse de la socket
	

	// Création d'une socket TCP
	sock = creerSocketTCP( &addr_serveur, port );

	// Récupération identifiant du serveur
	serveur_host = gethostbyname( nom_serveur );
	if ( serveur_host == NULL )
	{
		perror( "Erreur lors de la récupération de l'identifiant serveur." );
		exit( EXIT_FAILURE );
	}

	// Copie de l'@ IP du serveur (serveur_host) dans la structure de l'adresse de la socket (addr_serveur)
	memcpy( &addr_serveur.sin_addr.s_addr, serveur_host->h_addr_list[0], serveur_host->h_length );

	// Connexion de la socket client locale à la socket côté serveur
	if ( connect(sock, (struct sockaddr *)&addr_serveur, sizeof(addr_serveur)) == -1 )					// Connexion de la socket à la partie serveur (socket serveur)
	{
		perror( "Erreur lors de la connection au serveur. " );
		close( sock );
		exit( EXIT_FAILURE );
	}
	

	return sock;
}



// Fonction permettant d'envoyer un message sur le serveur connecté
void envoyerMessage( int sock, char* msg )                                                                      // Une fois connecté on communique avec le serveur, grâce à la socket
{
    if ( send( sock, msg, strlen(msg), 0 ) < 0 )
    {
        perror( "Erreur lors de l'envoi du message client->serveur" );
        close( sock );
        exit( EXIT_FAILURE );
    }
}




int main( int argc, char **argv )
{
    if ( argc < 3 ) 
    {
        fprintf(stderr, "Nombre d'arguments insuffisants: %s <server_name> <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf( "%s    %d\n", argv[1], atoi(argv[2]) );
    int sock = connexion( argv[1], atoi(argv[2]) );

    if ( sock < 0 )
    {
        fprintf( stderr, "Erreur lors de la connexion au serveur.\n" );
        return EXIT_FAILURE;
    }

    char message[ TAILLEBUF ];
    while( fgets( message, TAILLEBUF, stdin ) != NULL )
    {
        envoyerMessage( sock, message );
        memset( (char *)message, 0, sizeof(message) );
    }

    close( sock );


    return 0;
}