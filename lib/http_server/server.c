#include "server.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "http_headers.h"
#include "parser.h"
server_t server_create(char* static_file_path, int port){
    FILE* index = fopen(static_file_path,"rb");
    fseek(index, 0, SEEK_END);   
    long file_size = ftell(index);
    fseek(index, 0, SEEK_SET);
    
    server_t server;
    server.server_socket = socket_create(port, AF_INET, INADDR_ANY);
    server.static_index_file = malloc(file_size);
    server.static_index_file_size = file_size;
    if(server.server_socket.sock_fd < 0){server.return_error = server.server_socket.sock_fd; return server;}

    fread(server.static_index_file, file_size, 1, index);
    socket_listen(&server.server_socket, 3);
    return server;
}
//парсер долежн возвращать статус и стркоу файла(имя) 
// сервак ОБЯЗАН сам найти файл у себя и если не находит скинуть на клиента 404 no found 
int server_process(server_t* server){
    socket_accept(&(server->server_socket));
    socket_read(&(server->server_socket), 1024);
    socket_send(&(server->server_socket), server->static_index_file, server->static_index_file_size);
    server->server_socket.req_buffer[1024] = '\0';
    printf("%s\n", server->server_socket.req_buffer);
    return 0;
}