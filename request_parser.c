#include "request_parser.h"

char * string_trim ( char * str ) {
    if ( !str )
        NULL;

    char * str_pointer = str; 
    while ( *str_pointer == '\r' || *str_pointer == '\n' ) {
        str_pointer++;
    }

    char * pt_back_of_string = str_pointer + strlen( str_pointer );
    while ( *pt_back_of_string == '\r' || *pt_back_of_string == '\n' ) {
        *pt_back_of_string = NULL_CHAR;
        pt_back_of_string--;
    }

    return str_pointer;
}

c_serv_expanded_request_data * c_serv_request_parse( const c_serv_request_data data ) {
    if ( !data )
        return NULL;
    
    int size;    
    c_serv_expanded_request_data * request_data = ( c_serv_expanded_request_data * )malloc(sizeof(c_serv_expanded_request_data));
    char * data_pointer = data;

    if ( strncmp( data, "GET", 3 ) == 0 ) {
        request_data->method = GET;
        data_pointer = data_pointer + 3;
    } else if ( strncmp( data, "POST", 4 ) == 0 ) {
        request_data->method = POST;
        data_pointer = data_pointer + 4;
    } else {
        request_data->method = UNDEF;
        data_pointer = strchr( data, ' ' );
    }
    
    data_pointer += 1;

    size = strcspn( data_pointer, " " );
    if ( size == 0 ) {
        return NULL;
    }
    request_data->url = ( char * )calloc( size + 1, sizeof( char ) );
    strncpy( request_data->url, data_pointer, size );
    request_data->url[size] = NULL_CHAR;

    // skip the version part thingy
    data_pointer = strchr( data_pointer, '\n' );
    data_pointer = data_pointer + 1;

    request_data->header = NULL;

    while ( True ) {
        if ( strncmp( data_pointer, "\r\n", 2 ) || strncmp( data_pointer, "\n", 1 ) ) {
            break;
        }

        c_serv_tuple * temp = ( c_serv_tuple * )malloc( sizeof( c_serv_tuple ) );
        size = strcspn( data_pointer, ":" );
        temp->name = (char *)calloc( size + 1, sizeof( char ) );
        strncpy( temp->name, data_pointer, size );
        temp->name = NULL_CHAR;

        data_pointer = strchr( data_pointer, ':' ) + 1;

        size = strcspn( data_pointer, "\r\n" );
        temp->value = (char *)calloc( size + 1, sizeof( char ) );
        strncpy( temp->value, data_pointer, size );
        data_pointer = strchr( data_pointer, '\n' ) + 1;
        temp->prev = request_data->header;
        request_data->header = temp;
    }

    request_data->payload = string_trim( data_pointer );

    return request_data;
}

c_serv_boolean c_serv_free_request_data ( c_serv_expanded_request_data * data ) {
    if ( !data ) {
        return False;
    }

    c_serv_tuple * temp = data->header;
    while ( temp != NULL ) {
        free( temp->name );
        free( temp->value );
        c_serv_tuple * destroyable = temp;
        temp = temp->prev;
        free( destroyable );
    }

    free( data->url );
    free( data->payload );

    free( data );
    return True;
}