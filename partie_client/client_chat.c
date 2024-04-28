/*
    cmd compilation : 
        clear; gcc -o afficheur_message afficheur_message.c; gcc -o client client_chat.c ../fonctions/creerSocketTCP.c; ./client localhost 4006

    Ressources : 
        PIPES : 
            - http://unixwiz.net/techtips/remap-pipe-fds.html
            - https://tldp.org/LDP/lpg/node11.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <wait.h> 
#include <pthread.h>

#include "common.h"
#include "../fonctions/creerSocketTCP.h"



volatile sig_atomic_t arret = 0;

void arret_client()
{
    arret = 1;
    printf( "\nInterruption. Fermeture propre du client.\n" );
}


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
    if ( send(sock, msg, strlen(msg), 0) < 0 )
    {
        perror( "Erreur lors de l'envoi du message client->serveur" );
        // close( sock );
        // exit( EXIT_FAILURE );
    }
}
// void transfererMessage( int sock, int pipe_fd_end ) 
// {
//     char buffer[ TAILLEBUF ];
//     ssize_t nbytes;

//     while ( !arret )
//     {
//         memset( buffer, 0, TAILLEBUF );  // Vider le buffer
//         nbytes = recv( sock, buffer, TAILLEBUF - 1, 0 );                                  //      On attend un message du client ( TAILLEBUF - 1 pour stocker le '\0' )

//         if ( nbytes > 0 )                                                                 //      On regarde si le client a envoyé quelque chose
//         {
//             buffer[ nbytes ] = '\0';    // On "termine"/"coupe" la chaîne de char.
//             write( pipe_fd_end, buffer, nbytes );
//         }
//     }
// }
void * transfererMessage( void * args ) 
{
    int sock = *(int *)args;                                                            // Récupère le premier paramètre (socket) (déréférence/valeur du pointeur vers le premier élément de args, casté en pointeur vers un entier)
    int pipe_fd_in = *( (int *)args + 1 );                                              // Récupère le deuxième paramètre (fd du côté écriture du pipe) (déréférence/valeur du pointeur vers le premier élément de args, casté en pointeur vers un entier)
    char buffer[ TAILLEBUF ];
    ssize_t nbytes;

    while ( !arret )
    {
        memset( buffer, 0, TAILLEBUF );                                                 //    Vider le buffer
        nbytes = recv( sock, buffer, TAILLEBUF - 1, 0 );                                //    On attend un message du serveur ( TAILLEBUF - 1 pour stocker le '\0' )
        if ( nbytes > 0 )
        {
            buffer[ nbytes ] = '\0';                                                    // On "termine"/"coupe" la chaîne de char.
            write( pipe_fd_in, buffer, nbytes );
        }
    }
    return NULL;
}


void deconnexion()
{
    printf( "Vous avez été déconnecté.\n" );
}
void leave( int sock )
{
    deconnexion();
    close(sock);
    printf( "Vous avez quitté le client.\n" );
    arret = 1;
}




int main( int argc, char **argv )
{
    // Vérification si le nombre de paramètres est valide
    if ( argc < 3 ) 
    {
        fprintf( stderr, "Nombre d'arguments insuffisants: %s <server_name> <port>\n", argv[0] );
        exit( EXIT_FAILURE );
    }

    
    /* Gestionnaire de signaux */
    signal( SIGINT, arret_client );

    
    printf( "%s    %d\n", argv[1], atoi(argv[2]) );
    int sock = connexion( argv[1], atoi(argv[2]) );                                 //      Il se connecte au serveur ( TCP avec communication.c )
    if ( sock < 0 )
    {
        fprintf( stderr, "Erreur lors de la connexion au serveur.\n" );
        return EXIT_FAILURE;
    }

    // Création du pipe client_chat |> afficheur_message
    int pipe_fd[ 2 ] = { -1, -1 };
    if ( pipe(pipe_fd) < 0 )
    {
        perror( "Erreur lors de la création du tube anonyme : " );
        exit( EXIT_FAILURE );
    }

    // Création d'un processus pour gérer le lancement de l'afficheur message    ET    un autre pour gérér la réception des messages via un thread, sinon l'envoi
    pid_t pid = fork();
    if ( pid < 0 )
    {
        perror( "Échec de création du processus afficheur_message : " );
        exit( EXIT_FAILURE );
    }
    else if ( pid == 0 )                                                            // Processus FILS: Réception des messages serveurs et transfert dans |> afficheur_message
    {
        close( pipe_fd[1] );                                                        //      Ferme le 'File Descriptor' côté écriture (1) du fils
    
        char str_fd[4];
        sprintf( str_fd, "%d", pipe_fd[0] );

        execl( "/usr/bin/xterm", "xterm", "-e", "./afficheur_message", str_fd, NULL );
        perror( "Erreur d'exécution du terminal 'Afficheur Message' : " );
        exit( EXIT_FAILURE );
    }
    else
    {
        close( pipe_fd[0] );


        pthread_t recv_thread;
        int recv_thread_args[ 2 ] = { sock, pipe_fd[1] };
        if ( pthread_create(&recv_thread, NULL, transfererMessage, recv_thread_args) != 0 )
        {
            perror( "Erreur création thread receveur message" );
        }


        char message[ TAILLEBUF ];
        while( !arret && (fgets( message, TAILLEBUF, stdin ) != NULL)  )
        {
            envoyerMessage( sock, message );                                            //      Envoi du message ( ou de la commande )                          

            if ( (strcmp(message, "/e\n") == 0) || strcmp(message, "/exit\n") == 0 )    //      Gestion de la commande "/e" ou "/exit" côté client
            {
                leave( sock );
                break;
            }

            memset( (char *)message, 0, sizeof(message) );                              //      On vide le buffer (message)
            system( "clear" );
        }

        pthread_join( recv_thread, NULL );

        close( pipe_fd[1] );                                                            //      Ferme le 'File Descriptor' côté écriture (1) du père après utilisation
        wait( NULL );                                                                   //      Attend que le processus fils termine
    }


    if ( pipe_fd[0] != -1 ) close( pipe_fd[0] );                                        // Fermeture des FD du pipe
    if ( pipe_fd[1] != -1 ) close( pipe_fd[1] );
    close( sock );                                                                      // Fermeture de la socket

    return 0;
}