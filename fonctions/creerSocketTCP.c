#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>



int creerSocketTCP ( struct sockaddr_in *addr_local, int port ) 
{
	// static struct sockaddr_in addr_local; // Adresse de la socket côté locale
	int sock; // Descripteur de la socket locale

	// Création de la socket
	sock = socket( AF_INET, SOCK_STREAM, 0 );
	if ( sock == -1 )
	{
		perror( "Erreur lors de la création de la socket." );
		exit( EXIT_FAILURE );
	}

	// Liaison de la socket sur le port local
	// bzero( (char * )&addr_local, sizeof( addr_local ) );
	memset( (char *)addr_local, 0, sizeof( struct sockaddr_in ) ); // memset au lieu de bzero
	addr_local->sin_family = AF_INET;
	addr_local->sin_port = htons( port );
	

	return sock;
}
