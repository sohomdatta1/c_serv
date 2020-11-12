#include <linux/limits.h>
#include "common.h"

char * c_serv_generic_serve( char * directory, char * request ) {
    
}

c_serv_boolean is_out_of_dir( char * directory, char * request ) {
    if ( !request || !directory )
        return NULL;
    else if ( strchr( directory, '~' ) != NULL ) {
        c_serv_error_out( -1, "Given directory name contains tilde, please provide actual path." );
    }

    char * filepath = (char *)calloc( strlen( directory ) + strlen( request ) + 1, sizeof( char ) );
    filepath[0] = '\0';
    strcat( filepath, directory );
    strcat( filepath, request );


}
