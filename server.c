#include "c_serv.h"

int main () {
    fprintf(stdout, "Started server\n" );
    c_serv_create_server();
    exit( EXIT_FAILURE );
}