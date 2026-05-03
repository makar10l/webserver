#include "server.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "http_headers.h"
#include "parser.h"
#include "file_searcher.h"
server_t server_create(char* static_file_path, int port){
    server_t server;
    server.server_socket = socket_create(port, AF_INET, INADDR_ANY);
    if(server.server_socket.sock_fd < 0){server.return_error = server.server_socket.sock_fd; return server;}

    server.static_files_path = static_file_path;
    socket_listen(&server.server_socket, 3);
    return server;
}

int server_process(server_t* server){
    socket_accept(&(server->server_socket));
    socket_read(&(server->server_socket), 1024);
    http_parser_result parse_res = http_parse_request(server->server_socket.req_buffer, 1024);
    FILE* static_file = search_file(parse_res.filename);
    fprintf(stderr, "%s", parse_res.filename);
    char static_file_buffer[1024];
    if(static_file == NULL){ fprintf(stderr, "damn");return -1; fprintf(stderr, "damn");}
    fread(static_file_buffer, 1024, 1, static_file);
    fprintf(stderr, "%s", static_file_buffer);
    socket_send(&(server->server_socket), static_file_buffer, strlen(static_file_buffer));
    socket_client_close(&(server->server_socket));
}