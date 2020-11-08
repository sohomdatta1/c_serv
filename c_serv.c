#include "c_serv.h"

static c_serv_work_queue * queue;

static int socketfd;

char * route( c_serv_expanded_request_data * request_data );

void c_serv_handle_connections_internal() {
    int connectionfd;
    char request[ ( BUF_MAX_LEN + 1 ) ];
    while( True ) {
        struct sockaddr address;
        socklen_t address_len = sizeof( struct sockaddr );
        fprintf(stdout, "Waiting for connections\n");
        c_serv_error_out_internal( connectionfd = accept( socketfd, &address, &address_len), "Unable to accept connections");

        memset( &request, 0, sizeof( request ) );
        c_serv_error_out_internal( recv( connectionfd, request, sizeof( request ), 0 ), "Unable to receive data." );

        c_serv_connection_data request_data;
        request_data.connectionfd = connectionfd;
        request_data.request_txt = request;
        
        fprintf(stdout, "Recieved request:\n---REQUEST----\n%s\n---END_REQUEST---\n",request);
        c_serv_work_queue_push( &request_data, queue );
    }
}

void c_serv_create_server_with_portno(int port_number) {
    // starting server
    struct sockaddr_in server_addr;
    queue = c_serv_work_queue_init_queue();
    c_serv_init_thread_group( queue );
    c_serv_error_out_internal(socketfd = socket( AF_INET, SOCK_STREAM, 0 ), "Unable to initialize socket");

    memset(&server_addr, (int)'\0', sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl( INADDR_ANY );
    server_addr.sin_port = htons( port_number );

    c_serv_error_out_internal( bind( socketfd, (struct sockaddr *) &server_addr, sizeof( struct sockaddr ) ), "Bind failed for port number %d!", port_number );

    c_serv_error_out_internal( listen( socketfd, 20 ), "Failed to listen" );

    fprintf( stdout, "Starting server at port %d\n", port_number);
    fprintf( stdout, "Go to http://127.0.0.1:%d to interact with server\n", port_number);

    c_serv_handle_connections_internal();
}

void c_serv_create_server() {
    c_serv_create_server_with_portno( SERVER_DEFAULT_PORT );
}

void c_serv_generic_serve( char * directory, char * request ) {
    // serve files in the directory
}

void c_serv_close_server() {
    // closing server
}

void c_serv_error_out_internal( int err_no, const char * err_message, ... ) {
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
    fprintf(stderr, "\n");
    fprintf( stderr, "Error value = %d\n", err_no );

    exit(EXIT_FAILURE);
}