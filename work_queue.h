#ifndef C_SERV_WORK_QUEUE_H

#define C_SERV_WORK_QUEUE_H

#include "common.h"

struct c_serv_connection_data{
    c_serv_request_data request_txt;
    int connectionfd;
};

typedef struct c_serv_connection_data c_serv_connection_data;

typedef int c_serv_err_code;

/**
 * Queue node
 */
struct c_serv_work_node {
    c_serv_connection_data * request;
    struct c_serv_work_node * next;
    struct c_serv_work_node * prev;
};

struct c_serv_work_queue {
    struct c_serv_work_node * front;
    struct c_serv_work_node * rear;
    int size;
};

typedef struct c_serv_work_node c_serv_work_node;
typedef struct c_serv_work_queue c_serv_work_queue;

c_serv_err_code c_serv_work_queue_get_size( c_serv_work_queue * );
c_serv_err_code c_serv_work_queue_is_empty( c_serv_work_queue * );
void c_serv_work_queue_push( c_serv_connection_data *, c_serv_work_queue * );
c_serv_connection_data * c_serv_work_queue_pop( c_serv_work_queue * );
c_serv_work_queue * c_serv_work_queue_init_queue();

#endif