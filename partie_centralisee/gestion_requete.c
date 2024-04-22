#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


#define REQUEST_PIPE "/tmp/request_pipe"
#define TAILLEBUF 1024



int init_gestion_requete()
{
    char buffer[ TAILLEBUF ];

    int request_pipe_fd = open( REQUEST_PIPE, O_RDONLY );
    if ( request_pipe_fd == -1 )
    {
        perror( "Erreur lors de l'ouverture du tube de communication en lecture ( communication.c |> gestionRequete.c ) " );
        exit( EXIT_FAILURE ); // On quitte cette partie     À VÉRIFIER
    }

    while ( 1 )
    {
        ssize_t nbytes = read( request_pipe_fd, buffer, sizeof(buffer) - 1 );
        if ( nbytes > 0 )
        {
            buffer[ nbytes ] = '\0';
            printf( "GESTION_REQUETE :    Commande reçue :             %s\n", buffer );
        }
    }

    close( request_pipe_fd );
    return 0;
}