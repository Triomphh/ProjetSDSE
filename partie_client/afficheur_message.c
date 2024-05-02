/*
	Afficheur message du client

	cmd compilation : 
        clear; ./afficheur_message
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "common.h"


volatile sig_atomic_t arret = 0;


/*  
    ================== 
    Version pipe nommé 
    ================== 
*/
int main( int argc, char **argv ) 
{
    printf( "%s\n", argv[1] );
    int pipe_fd = open( argv[1], O_RDONLY );
    if ( pipe_fd == -1 )
        perror( "Erreur lors de l'ouverture du tube nommé côté lecture ( client_chat.c |> afficheur_message.c ) " );
    char message[TAILLEBUF];

	printf("Prêt à lire les messages...\n");
    while ( !arret )    // Quand on détecte une arrivée sur le flux du FD
	{
        if ( read(pipe_fd, message, TAILLEBUF) > 0 )
        {
            printf("%s", message);                                  //      On affiche le message
            memset( (char *)message, 0, sizeof(message) );          //      On clear le buffer pour ne pas créer des "résidus" sur les messages suivants
        }
        else
        {
            perror( "Erreur read(), lecture pipe afficheur_message" );
            break;
        }

    }

    printf("Fin de l'affichage des messages.\n");
    close( pipe_fd );
    return 0;
}





/*  
    ================================================== 
    Version pipe anonyme, marche uniquement avec xterm 
    ================================================== 
*/

// int main( int argc, char **argv ) 
// {
//     int fd = atoi(argv[1]);                                     // Récupère le descripteur de fichier de la sortie (lecture) du pipe
//     char message[TAILLEBUF];

// 	printf("Prêt à lire les messages...\n");
//     while ( !arret )    // Quand on détecte une arrivée sur le flux du FD
// 	{
//         if ( read(fd, message, TAILLEBUF) > 0 )
//         {
//             printf("%s", message);                                  //      On affiche le message
//             memset( (char *)message, 0, sizeof(message) );          //      On clear le buffer pour ne pas créer des "résidus" sur les messages suivants
//         }
//         else
//         {
//             perror( "Erreur read(), lecture pipe afficheur_message" );
//             break;
//         }

//     }

//     printf("Fin de l'affichage des messages.\n");
//     close( fd );
//     return 0;
// }
