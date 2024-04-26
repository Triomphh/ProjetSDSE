#ifndef COMMON_H
#define COMMON_H


/*
    Fichier regroupant des objets utilisés par plusieurs programmes

    Ressources :
        + sig_atomic_t et volatile :
            http://shtroumbiniouf.free.fr/CoursInfo/Systeme2/TP/CoursSignaux/Volatile.html
*/

#include <signal.h>


#define TAILLEBUF 1024
#define REQUEST_PIPE "/tmp/request_pipe"
#define RESPONSE_PIPE "/tmp/response_pipe"


extern volatile sig_atomic_t arret;


typedef struct 
{
    char username[ 128 ];
} User;

typedef struct 
{
    User * user;
    char command[ TAILLEBUF ];
} Command;




#endif // COMMON_H