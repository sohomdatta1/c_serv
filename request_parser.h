#ifndef R_PARSER_H
#define R_PARSER_H

#include "common.h"

char * string_trim ( char * );
c_serv_expanded_request_data * c_serv_request_parse( const c_serv_request_data );
c_serv_boolean c_serv_free_request_data ( c_serv_expanded_request_data * );

#endif
