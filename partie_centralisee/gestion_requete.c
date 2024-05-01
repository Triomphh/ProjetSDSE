#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#include "common.h"



int init_gestion_requete()
{
    Command cmd;

    if ( mkfifo( RESPONSE_PIPE, 0666 ) == -1 )                                                              // Création du tube de communication pour gérer les réponses aux requêtes utilisateur
        perror( "Erreur lors de la création du tube de communication de réponse entre gestionRequete.c et communication.c " );


    int request_pipe_fd = open( REQUEST_PIPE, O_RDONLY );
    // int response_pipe_fd = open( RESPONSE_PIPE, O_WRONLY | O_NONBLOCK );
    if ( request_pipe_fd == -1  /*||  response_pipe_fd == -1*/ )
    {
        perror( "Erreur lors de l'ouverture du tube de communication ( communication.c | gestionRequete.c ) " );
        exit( EXIT_FAILURE ); // On quitte cette partie     À VÉRIFIER
    }

    while ( !arret )
    {
        ssize_t nbytes = read(request_pipe_fd, &cmd, sizeof(cmd));
        if ( nbytes > 0 )
        {
            printf( "GESTION_REQUETE :    Commande reçue : %s", cmd.command );

            // === Gestion des commandes "/..." ===
            //      Connexion                           : /c  ,        , /connect   { nom, mdp }
            if ( strncmp(cmd.command, "/c ", 3) == 0 || strncmp(cmd.command, "/connect ", 9) == 0 )
            {
                printf("on est bien dans /c %s", cmd.command);
                char * username = strtok( cmd.command + ((cmd.command[2] == 'o') ? 9 : 3), " " );           //              Extrait le premier mot (username) apprès la commande ( en partant de l'index +commande au lieu de 0 )
                if ( username )
                {
                    // VÉRIFIER SI C'EST UN COMPTE VALIDE, SI OUI : 
                    // write( response_pipe_fd, username, strlen(username) );
                    printf( "Utilisateur %s connecté\n", username );
                    ///////// AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAH ////////////////////////////////////////////////////////////
                     struct hostent *serveur_host;
                    // adresse de la socket coté serveur
                    static struct sockaddr_in addr_serveur;
                    // taille de l'addresse socket
                    socklen_t lg;
                    // descripteur de la socket locale
                    int sock;
                    // chaine à envoyer
                    char*msg= cmd.command;
                    // buffer de réception
                    char buffer[TAILLEBUF];
                    // chaine reçue en réponse
                    char*reponse;
                    // nombre d'octets lus ou envoyés
                    int nb_octets;
                    // création d'une socket UDP
                    sock= socket(AF_INET, SOCK_DGRAM,0);
                    if (sock ==-1) {
                        perror("erreur création socket");
                        exit(1);
                    }
                    // récupération identifiant du serveur
                    serveur_host= gethostbyname("localhost");
                    if (serveur_host==NULL) {
                        perror("erreur adresse serveur");
                        exit(1);
                    }
                    // création adresse socket destinatrice
                    bzero(&addr_serveur, sizeof(struct sockaddr_in));
                    addr_serveur.sin_family= AF_INET;
                    addr_serveur.sin_port=htons(7777);
                    memcpy(&addr_serveur.sin_addr.s_addr,serveur_host -> h_addr, serveur_host -> h_length);
                    // on envoie le message "bonjour" au serveur
                    lg= sizeof(struct sockaddr_in);
                    nb_octets= sendto(sock, msg, strlen(msg)+1,0,(struct sockaddr*)&addr_serveur, lg);
                    if (nb_octets ==-1) {
                    perror("erreur envoi message");
                    exit(1); 
                    }
                    printf("paquet envoyé, nb_octets = %d\n",nb_octets);
                    // on attend la réponse du serveur
                    nb_octets = recvfrom(sock, buffer, TAILLEBUF, 0,(struct sockaddr*)&addr_serveur, &lg);
                    if (nb_octets == -1) {
                    perror("erreur réponse serveur");
                    exit(1);
                    }
                    reponse = (char *)malloc(nb_octets * sizeof(char));
                    memcpy(reponse, buffer, nb_octets);
                    printf("reponse recue du serveur : %s\n",reponse);
                    // on ferme la socket
                    close(sock);
                    /////////////// FIN AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA ////////////////////////////////////////////
                }
            }
            //      Déconnexion
            //      Afficher la liste des utilisateurs  : /l  , /list , /liste
            //      Créer un compte                     : /cr ,       , /create     { nom, mdp }
            //      Supprimer un compte                 : /d  , /del  , /delete     { nom, mdp }

            else
            {
                printf( "Commande non valide...\n" );
            }


            
        }
    }

    close( request_pipe_fd );
    // close( response_pipe_fd );
    return 0;
}