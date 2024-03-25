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


// Fonction qui permet de connecter le client au serveur choisit 
int connexion( char *nom_serveur, int port )
{
	struct hostent *serveur_host;           // Identifiant de la machine serveur
	static struct sockaddr_in addr_serveur; // Adresse de la socket côté serveur
	int sock;                               // Descripteur de la socket
	socklen_t addrlen;                      // Taille de l'adresse de la socket
	

	// Création d'une socket TCP
	sock = creerSocketTCP( port );																				// Création d'une socket


	// Récupération identifiant du serveur
	serveur_host = gethostbyname( nom_serveur );
	if ( serveur_host == NULL )
	{
		perror( "Erreur lors de la récupération de l'identifiant serveur." );
		exit( EXIT_FAILURE );
	}

	
	// Copie de l'@ IP du serveur (serveur_host) dans la structure de l'adresse de la socket (addr_serveur)
	memcpy( &addr_serveur.sin_addr.s_addr, serveur_host->h_addr, serveur_host->h_length );

	// Connexion de la socket client locale à la socket côté serveur
	if ( connect(sock, (struct sockaddr *)&addr_serveur, sizeof(struct sockaddr_in)) == -1 )					// Connexion de la socket à la partie serveur (socket serveur)
	{
		perror( "Erreur lors de la connection au serveur. " );
		close( sock );
		exit( EXIT_FAILURE );
	}


	// ...fermer la socket
	

	return sock;
}


// Fonction permettant d'envoyer un message sur le serveur connecté
void envoyerMessage( char* msg )																				// Une fois connecté on communique avec le serveur, grâce à la socket
{

}
