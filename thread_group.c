#include "thread_group.h"
#define MAX_THREAD_NO 20

static pthread_t thread_group[MAX_THREAD_NO];

static c_serv_work_queue * queue;

char * route( c_serv_expanded_request_data * data  ) {
    return "";
}

/*
char * c_serv_respond_internal( c_serv_request_data data ) {
    char abc[] = "HTTP/1.0 200 OK\n\rHello\r\n\r\n";
    return abc;
    // parse the data
    // route( data );
} */

void * run( void * args ) {
    while(True) {
        c_serv_connection_data temp;
        if ( ( temp = c_serv_work_queue_pop( queue ) ).request_txt != NULL ) {
            fprintf(stdout, "Processing...\n" );
            char *response = temp.request_txt;
            //sleep(1);
            c_serv_error_out( send( temp.connectionfd, response, strlen( response ), 0 ), "Unable to send" );
            close( temp.connectionfd );
        }
    }
    return NULL;
}

void c_serv_init_thread_group( c_serv_work_queue * input_queue ) {
    int i;

    queue = input_queue;
    
    for ( i = 0; i < MAX_THREAD_NO; i++ ) {
        pthread_create( &( thread_group[i] ), NULL, &run, NULL );
    }
}