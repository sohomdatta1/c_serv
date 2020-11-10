#include "common.h"

void c_serv_error_out( int err_no, const char * err_message, ... ) {
    if ( C_SERV_UNIX_OKAY( err_no ) ) {
        /**
         * These functions return 0 for success and other numbers for error.
         */ 
        return;
    }

    va_list args_list;
    va_start(args_list, err_message);
    vfprintf(stderr, err_message, args_list);
    va_end(args_list);
    fprintf(stderr, "\n FATAL ERROR, ABORTING...\n");
    fprintf( stderr, "Error value = %s\n", strerror(errno) );

    exit(EXIT_FAILURE);
}