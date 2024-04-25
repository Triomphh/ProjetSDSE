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


extern volatile sig_atomic_t arret;







#endif // COMMON_H