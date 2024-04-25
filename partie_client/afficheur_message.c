/*
	Afficheur message du client

	cmd compilation : 
        clear; ./afficheur_message
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "common.h"


volatile sig_atomic_t arret = 0;


int main( int argc, char **argv ) 
{
    int fd = atoi(argv[1]);                                     // Récupère le descripteur de fichier de la sortie (lecture) du pipe
    char message[TAILLEBUF];

	printf("Prêt à lire les messages...\n");
    while ( (read( fd, message, TAILLEBUF ) > 0) && !arret )    // Quand on détecte une arrivée sur le flux du FD
	{
        printf("%s", message);                                  //      On affiche le message
        memset( (char *)message, 0, sizeof(message) );          //      On clear le buffer pour ne pas créer des "résidus" sur les messages suivants
    }

    printf("Fin de l'affichage des messages.\n");
    close( fd );
    return 0;
}
