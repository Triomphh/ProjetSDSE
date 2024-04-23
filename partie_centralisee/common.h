#ifndef COMMON_H
#define COMMON_H


/*
    Fichier regroupant des objets utilisés par plusieurs programmes
*/

#include <signal.h>


#define TAILLEBUF 1024
#define REQUEST_PIPE "/tmp/request_pipe"


extern volatile sig_atomic_t arret;


typedef struct 
{
    char username[ 128 ];
    char command[ TAILLEBUF ];
} Command;




#endif // COMMON_H