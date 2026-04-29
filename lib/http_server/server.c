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
