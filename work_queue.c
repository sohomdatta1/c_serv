#include "work_queue.h"

static pthread_mutex_t thread_lock;

void c_serv_work_queue_push( c_serv_connection_data request, c_serv_work_queue * queue ) {
    pthread_mutex_lock(&thread_lock);
    c_serv_work_node * node = ( c_serv_work_node * )malloc( sizeof( c_serv_work_node ) );
    node->request = request;
    node->next = queue->rear;
    node->prev = NULL;
    queue->rear = node;

    if ( !queue->front )
        queue->front = node;
    else
        node->next->prev = node;
    pthread_mutex_unlock(&thread_lock);
}

c_serv_connection_data c_serv_work_queue_pop( c_serv_work_queue * queue ) {
    pthread_mutex_lock(&thread_lock);
    if ( queue->front == NULL ) {
        pthread_mutex_unlock(&thread_lock);
        c_serv_connection_data empty = {
            .connectionfd = -1,
            .request_txt = NULL
        };
        return empty;
    }
    c_serv_connection_data request = queue->front->request;
    if ( queue->front == queue->rear ) {
        free( queue->front );
        queue->front = NULL;
        queue->rear = NULL;
    } else {
        queue->front = queue->front->prev;
        free( queue->front->next );
        queue->front->next = NULL;
    }

    pthread_mutex_unlock(&thread_lock);
    return request;
}

c_serv_work_queue * c_serv_work_queue_init_queue() {
    c_serv_work_queue * queue = ( c_serv_work_queue * )malloc( sizeof( c_serv_work_queue ) );
    queue->front = NULL;
    queue->rear = NULL;
    pthread_mutex_init(&thread_lock, NULL);
    return queue;
}