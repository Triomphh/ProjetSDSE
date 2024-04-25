#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "common.h"



int init_gestion_requete()
{
    Command cmd;

    int request_pipe_fd = open( REQUEST_PIPE, O_RDONLY );
    if ( request_pipe_fd == -1 )
    {
        perror( "Erreur lors de l'ouverture du tube de communication en lecture ( communication.c |> gestionRequete.c ) " );
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
                char * username = strtok( cmd.command + ((cmd.command[2] == 'o') ? 9 : 3), " " );               //              Extrait le premier mot (username) apprès la commande ( en partant de l'index +commande au lieu de 0 )
                if ( username )
                {
                    strncpy( cmd.user->username, username, sizeof(cmd.user->username) - 1 );
                    cmd.user->username[ sizeof(cmd.user->username) - 1 ] = '\0';
                    // printf( "Utilisateur %s connecté\n", cmd.user->username );
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
    return 0;
}