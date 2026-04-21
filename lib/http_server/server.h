#ifndef SERVER_H
#define SERVER_H
#include "socket.h"
typedef struct{
    socket_t server_socket;
    //some http entity like parser;
    char* static_index_file;
    int static_index_file_size;
    int return_error;
} server_t;

server_t server_create(char* static_file_path, int port);
int server_process(server_t* server);
int server_close();
#endif