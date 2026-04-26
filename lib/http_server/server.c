#include "server.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "http_headers.h"
#include "parser.h"
server_t server_create(char* static_file_path, int port){
    server_t server;
    server.server_socket = socket_create(port, AF_INET, INADDR_ANY);
    if(server.server_socket.sock_fd < 0){server.return_error = server.server_socket.sock_fd; return server;}

    server.static_files_path = static_file_path;
    socket_listen(&server.server_socket, 3);
    return server;
}

int server_process(server_t* server){
    FILE* file;
    char* static_file;
    int static_file_size;
    socket_accept(&(server->server_socket));
    socket_read(&(server->server_socket), 1024);
    server->server_socket.req_buffer[1024] = '\0';
    http_parser_result hh = http_parse_request(server->server_socket.req_buffer, 1024);
    char fullpath[256];
    snprintf(fullpath, sizeof(fullpath), "static%s", hh.filename);
    file = fopen(fullpath, "rb");
    if(file == NULL) file = fopen("static/404.html", "rb");
    fseek(file, 0, SEEK_END);
    static_file_size = ftell(file);
    static_file = malloc(static_file_size);
    fseek(file, 0, SEEK_SET);

    fread(static_file, 1, static_file_size, file);
    printf("%s", fullpath);
    socket_send(&(server->server_socket), static_file, static_file_size);
    return 0;
}