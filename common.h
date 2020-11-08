#ifndef C_SERV_COMMON_H

#define C_SERV_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <signal.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdarg.h>

#define C_SERV_UNIX_OKAY(a) !(a < 0)

// Syntactical sugar to be able to use boolen 
enum c_serv_boolean { False, True };
typedef enum c_serv_boolean c_serv_boolean;

struct c_serv_tuple {
    char * name;
    char * value;
};

typedef struct c_serv_tuple c_serv_tuple;

typedef char * c_serv_request_data;

typedef int c_serv_err_code;

struct c_serv_expanded_request_data {
    char * method;
    char * page;
    c_serv_tuple header;
    c_serv_tuple query;
    char * payload;
};

typedef struct c_serv_expanded_request_data c_serv_expanded_request_data;

#endif