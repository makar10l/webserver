#include "server.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "http_headers.h"
#include "parser.h"
#include "file_searcher.h"
server_t server_create(int port){
    server_t server;
    server.server_socket = socket_create(port, AF_INET, INADDR_ANY);
    if(server.server_socket.sock_fd < 0){server.return_error = server.server_socket.sock_fd; return server;}
    socket_listen(&server.server_socket, 3);
    return server;
}

int server_process(server_t* server){
    socket_accept(&(server->server_socket));
    socket_read(&(server->server_socket), 1024);

    http_parser_result parse_res = http_parse_request(server->server_socket.req_buffer, 1024);
    fprintf(stderr, "FILE REQUEST:%s\n\n", parse_res.filename);

    FILE* static_file = search_file(parse_res.filename);
    if(static_file == NULL) return -1;

    switch(parse_res.extens){
        case HTML:
            socket_send(&(server->server_socket), HTML_HEADER, strlen(HTML_HEADER));
            break;
        case CSS:
            socket_send(&(server->server_socket), CSS_HEADER, strlen(CSS_HEADER)); 
            break;
        case JS:
            socket_send(&(server->server_socket), JAVASCRIPT_HEADER, strlen(JAVASCRIPT_HEADER)); 
            break;
        case ICO:
            socket_send(&(server->server_socket), ICON_HEADER, strlen(ICON_HEADER)); 
            break;
        default:
            socket_send(&(server->server_socket), HTML_HEADER, strlen(HTML_HEADER));
    }
    
    char static_file_buffer[128 * 1024];
    memset(static_file_buffer, 0, (128 * 1024));
    size_t file_size = fread(static_file_buffer, 1, (128 * 1024), static_file);
    socket_send(&(server->server_socket), static_file_buffer, file_size);
    socket_client_close(&(server->server_socket));
}