#ifndef C_SERV_DEF_H

#define C_SERV_DEF_H

#include "common.h"
#include "work_queue.h"

#define MAX_CONNECTIONS 1000
#define SERVER_DEFAULT_PORT 5001
#define BUF_MAX_LEN 1000

typedef struct c_serv_header_data header_data;

char * route( c_serv_expanded_request_data * );

void c_serv_error_out_internal( int, const char * , ... );

void c_serv_handle_connections_internal();

void c_serv_create_server_with_portno(int);

void c_serv_create_server();

void c_serv_generic_serve( char *, char *);

void c_serv_close_server();

#endif