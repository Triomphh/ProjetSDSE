// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/types.h>
// #include <sys/ipc.h>
// #include <sys/shm.h>

// #include "memoire_partagee.h"

// #define IPC_RESULT_ERROR (-1)


// static int get_bloc_memoire( char * filename, int size )
// {
//     key_t key = ftok( filename, 0 );
//     if ( key == IPC_RESULT_ERROR )
//         return IPC_RESULT_ERROR;

//     return shmget( key, size, 0644 | IPC_CREAT );
// }


// char * attacher_bloc_memoire( char * filename, int size )
// {
//     int id_bloc_memoire = get_bloc_memoire( filename, size );
//     if ( id_bloc_memoire == IPC_RESULT_ERROR )
//         return NULL;

//     char * result = shmat( id_bloc_memoire, NULL, 0 );
//     if ( result == (char *)IPC_RESULT_ERROR )
//         return NULL;

//     return result;
// }


// bool detacher_bloc_memoire( char * block )
// {
//     return ( shmdt(block) != IPC_RESULT_ERROR );
// }


// bool detruire_bloc_memoire( char * filename )
// {
//     int id_bloc_memoire = get_bloc_memoire( filename, 0 );

//     if ( id_bloc_memoire == IPC_RESULT_ERROR )
//         return NULL;

//     return ( shmctl(id_bloc_memoire, IPC_RMID, NULL) != IPC_RESULT_ERROR );
// }