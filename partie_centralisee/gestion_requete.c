#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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
            printf( "GESTION_REQUETE :    Commande reçue de %s : %s", cmd.username, cmd.command );
        }
    }

    close( request_pipe_fd );
    return 0;
}