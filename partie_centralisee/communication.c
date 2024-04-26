#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

#include "common.h"
#include "../fonctions/creerSocketTCP.h"

// https://www.youtube.com/watch?v=WgVSq-sgHOc
// https://www.tutorialspoint.com/inter_process_communication/inter_process_communication_shared_memory.htm

void traiter( int socket_service )
{
    char buffer[ TAILLEBUF ];
    User user = {0};                                                                                // Initialise la structure User à vide, en attendant une connexion valide
    ssize_t nbytes;                                                                                 // Compteur de bytes reçus (pour recv)



    int request_pipe_fd = open( REQUEST_PIPE, O_WRONLY | O_NONBLOCK );                              // Ouverture du pipe en lecture et O_NONBLOCK car il s'ouvre plus tard que dans gestion_requete.c
    // int response_pipe_fd = open( RESPONSE_PIPE, O_RDONLY );
    if ( request_pipe_fd == -1  /*||  response_pipe_fd == -1*/ )
        perror( "Erreur lors de l'ouverture du tube de communication ( communication.c | gestionRequete.c ) " );


    while ( !arret )
    {
        memset( buffer, 0, TAILLEBUF );  // Vider le buffer
        nbytes = recv( socket_service, buffer, TAILLEBUF - 1, 0 );                                  //      On attend un message du client ( TAILLEBUF - 1 pour stocker le '\0' )

        if ( nbytes > 0 )                                                                           //      On regarde si le client a envoyé quelque chose
        {
            buffer[ nbytes ] = '\0';    // On "termine"/"coupe" la chaîne de char.
            printf( "%s : %s", user.username, buffer );

            if ( buffer[0] == '/' )                                                                 //      Tous les clients (même non connectés peuvent envoyer des commandes)
            {
                Command cmd;                                                                        //          On stocke sa commande et son pseudo (même vide) dans une structure propre comprise par le processus gestion_requete
                cmd.user = &user;
                strncpy( cmd.command, buffer, sizeof(cmd.command) - 1 );

                printf( "COMMUNICATION   :    Commande reçue de %s : %s", user.username, buffer );
                write( request_pipe_fd, &cmd, sizeof(cmd) );                                        //          On transmet l'adresse mémoire de la commande à gestion_requete

                // char response[ TAILLEBUF ];
                // if ( read(response_pipe_fd, response, sizeof(response)) > 0 )
                // {
                //     printf( "Réponse de la requête : %s\n", response );
                //     strncpy( user.username, response, sizeof(user.username) );                      //          On modifie user.username avec la réponse retournée par gestion_requete
                //     user.username[ sizeof(user.username) - 1 ] = '\0';                              //          On coupe la chaîne de caractères
                // }
            }
            else if ( user.username[0] != '\0' )                                                    //      Mais seul les clients connectés peuvent envoyer des messages
            {
                // TEST renvoit du message au client À REMPLACER PAR UN BROADCAST À TOUS LES CLIENTS (récupérer la liste des connectés et itérer)
                send( socket_service, buffer, nbytes, 0 ); 
            }

        }
        else
        {
            printf( "%s a quitté.\n", (user.username[0] != '\0') ? user.username : "L'utilisateur non connecté" );
            break;
        }

    }


    close( request_pipe_fd );
    // close( response_pipe_fd );
    close( socket_service );                                                                        // On ferme la socket associée au client
}




int init_communication( int port )
{
    static struct sockaddr_in addr_serveur;
    static struct sockaddr_in addr_client;
    socklen_t addrlen;
    int socket_ecoute, socket_service;


    if ( mkfifo( REQUEST_PIPE, 0666 ) == -1 )                                                       // Création du tube de communication pour gérer les requêtes utilisateur
        perror( "Erreur lors de la création du tube de communication entre communication.c et gestionRequete.c " );


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
    addrlen = sizeof( addr_client );
    while( !arret )																					// Attente de connexion du client sur la socket serveur
    {
        socket_service = accept( socket_ecoute, (struct sockaddr *)&addr_client, &addrlen );		// La connexion du client renvoit une socket de service pour le client
        if ( socket_service == -1 )
        {
            perror( "Erreur accept : " );
            continue;
        }

        if ( fork() == 0 ) // Création d'un processus par client
        {                                                                                           // Processus fils :
            close( socket_ecoute ); 
			traiter( socket_service );                                                              //      On traite la communication avec le client
			exit( EXIT_SUCCESS );
        }
		close( socket_service );
    }

    return 0;
}
