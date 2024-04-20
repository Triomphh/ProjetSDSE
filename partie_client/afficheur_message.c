/*
	Afficheur message du client

	cmd compilation : 
        clear; ./afficheur_message
*/

#include <stdio.h>
#include <stdlib.h>

#define TAILLEBUF 1024


int main() 
{
    char message[TAILLEBUF];

	printf("Prêt à lire les messages...\n");
    while ( fgets(message, TAILLEBUF, stdin) != NULL ) 
	{
        printf("Message reçu: %s", message);
    }

    printf("Fin de l'affichage des messages.\n");
    return 0;
}
