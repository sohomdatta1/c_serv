#include "thread_group.h"
#define MAX_THREAD_NO 1000

pthread_t thread_group[MAX_THREAD_NO];

char * route( c_serv_expanded_request_data * data  ) {
    return "";
}

char * c_serv_respond_internal( c_serv_request_data data ) {
    return "HTTP/1.0 200 OK\n\rHello\r\n\r\n";
    // parse the data
    // route( data );
}

void * run( void * queue ) {
    while(True) {
        if ( !c_serv_work_queue_is_empty( queue ) ) {
            c_serv_connection_data * temp = c_serv_work_queue_pop( queue );
            int connectionfd = temp->connectionfd;

            char * response = c_serv_respond_internal( temp->request_txt );

            send( connectionfd, response, sizeof( response ), 0 );
            
            close( connectionfd );
        }
    }
    return NULL;
}

void c_serv_init_thread_group( c_serv_work_queue * queue ) {
    int i;
    
    for ( i = 0; i < MAX_THREAD_NO; i++ ) {
        pthread_create( &( thread_group[i] ), NULL, &run, (void *)queue );
    }
}