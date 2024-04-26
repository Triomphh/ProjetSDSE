#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

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
                char * username = strtok( cmd.command + ((cmd.command[2] == 'o') ? 9 : 3), " " );           //              Extrait le premier mot (username) apprès la commande ( en partant de l'index +commande au lieu de 0 )
                if ( username )
                {
                    // VÉRIFIER SI C'EST UN COMPTE VALIDE, SI OUI : 
                    // write( response_pipe_fd, username, strlen(username) );
                    printf( "Utilisateur %s connecté\n", username );
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