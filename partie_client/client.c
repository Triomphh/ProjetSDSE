/*
 	Questionnements:
		- Une fonction envoyerMessage( msg ) + une fonction connexion( serveur )     ou     les deux en même temps dans la même fonction      ?
		- 

	À faire:
		- envoyerMessage()
		- recevoirMessages() ou afficherMessage()
		- connexion( serveur ) ?
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


int communication( char *nom_serveur, int port )
{
	struct hostent *serveur_host;           // Identifiant de la machine serveur
	static struct sockaddr_in addr_serveur; // Adresse de la socket côté serveur
	int sock;                               // Descripteur de la socket
	socklen_t addrlen;                      // Taille de l'adresse de la socket
	char *msg; 								// Message à envoyer
	
	// Création d'une socket TCP
	sock = creerSocketTCP( port );

	// Récupération identifiant du serveur
	serveur_host = gethostbyname( nom_serveur );
	if ( serveur_host == NULL )
	{
		perror( "Erreur lors de la récupération de l'identifiant serveur." );
		exit( 1 );
	}
	
	// Création de l'identifiant de la socket d'écoute du serveur
	memcpy( &addr_serveur.sin_addr.s_addr, serveur_host->h_addr, serveur_host->h_length );

	// Envoi du message ?


	// ...fermer la socket
	return 0;
}
