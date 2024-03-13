#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

int creerSocketTCP ( int port ) {
	static struct sockaddr_in addr_local; // Adresse de la socket côté locale
	int sock; // Descripteur de la socket locale

	// Création de la socket
	sock = socket( AF_INET, SOCK_STREAM, 0 );
	if ( sock == -1 )
	{
		perror( "Erreur lors de la création de la socket." );
		exit( 1 );
	}

	// Liaison de la socket sur le port local
	bzero( (char * )&addr_local, sizeof( addr_local ) );
	addr_local.sin_family = AF_INET;
	addr_local.sin_port = htons( port );
	if ( bind( sock, (struct sockaddr *)&addr_local, sizeof( addr_local ) ) == -1 )
	{
		perror( "Erreur lors de la liaison de la socket." );
		exit( 1 );
	}

	return sock;
}