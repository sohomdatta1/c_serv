#include "work_queue.h"

static pthread_mutex_t lock;
c_serv_err_code c_serv_work_queue_get_size( c_serv_work_queue * queue ) {
    return queue->size;
}

c_serv_err_code c_serv_work_queue_is_empty( c_serv_work_queue * queue ) {
    return queue->size == 0;
}

void c_serv_work_queue_push( c_serv_connection_data * request, c_serv_work_queue * queue ) {
    pthread_mutex_lock(&lock);
    c_serv_work_node * node = ( c_serv_work_node * )malloc( sizeof( c_serv_work_node ) );
    node->request = request;
    node->next = queue->rear;
    node->prev = NULL;
    queue->rear = node;
    (queue->size)++;

    if ( !queue->front )
        queue->front = node;
    else
        node->next->prev = node;
    pthread_mutex_unlock(&lock);
}

c_serv_connection_data * c_serv_work_queue_pop( c_serv_work_queue * queue ) {
    pthread_mutex_lock(&lock);
    if ( c_serv_work_queue_is_empty( queue ) )
        return NULL;
    c_serv_connection_data * request = queue->front->request;
    if ( queue->front == queue->rear ) {
        free( queue->front );
        queue->front = queue->rear = NULL;
    } else {
        queue->front = queue->front->prev;
        free( queue->front->next );
        queue->front->next = NULL;
    }
    
    (queue->size)--;
    pthread_mutex_unlock(&lock);
    return request;
}

c_serv_work_queue * c_serv_work_queue_init_queue() {
    c_serv_work_queue * queue = ( c_serv_work_queue * )malloc( sizeof( c_serv_work_queue ) );
    queue->front = queue->rear = NULL;
    queue->size = 0;
    pthread_mutex_init(&lock, NULL);
    return queue;
}