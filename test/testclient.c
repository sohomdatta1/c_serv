#include "../common.h"
#include <time.h>

void get_help() {
    fprintf(stdout, "\n USAGE: ./client [PORT NUMBER]\n" );
}

void do_everything( int port_number, char * payload ) {
    struct sockaddr_in socket_addr;
    int socketfd, n;

    printf( "Payload: %s\n", payload );

    c_serv_error_out( socketfd = socket( AF_INET, SOCK_STREAM, 0 ), "Unable to intialize socket" );

    memset( &socket_addr, 0, sizeof( socket_addr ) );
    socket_addr.sin_port = htons( port_number );
    socket_addr.sin_family = AF_INET;
    socket_addr.sin_addr.s_addr = inet_addr( "127.0.0.1" );

    c_serv_error_out( connect( socketfd, ( struct sockaddr * )&socket_addr, sizeof( struct sockaddr ) ), "Unable to connect" );

    char buffer[BUF_MAX_LEN];

    memset( &buffer, 0, sizeof( buffer ) );

    c_serv_error_out( n = write( socketfd, payload, strlen( payload ) ), "Unable to send" );

    c_serv_error_out( n =  read( socketfd, &buffer, BUF_MAX_LEN ), "Unable to recieve" );

    close(socketfd);
}

int main( int argc, char ** argv ) {
    if ( argc < 3 || argc > 3 ) {
        get_help();
        return EXIT_FAILURE;
    }
    do_everything( atoi( argv[argc - 2] ), argv[argc - 1] );
    return EXIT_SUCCESS;
}