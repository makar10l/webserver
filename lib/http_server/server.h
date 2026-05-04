#ifndef SERVER_H
#define SERVER_H
#include "socket.h"
/* 
    @struct server_t
    @brief server struct wnich used in server functions like creating and closing 
*/
typedef struct{
    socket_t server_socket;
    int return_error;
} server_t;
/*
    @func server_create
    @brief creates server, opening sockets
    @param port on which server opens
    @retval server_t struct setted up server structure
    @note returnal struct contains return error field. ALWAYS check this field 
*/
server_t server_create(int port);
/*
    @func server_process
    @brief main server fucntion, accepts connection, searchs static files, sends file
    @param server server_t struct
    @todo retvals
*/
int server_process(server_t* server);
#endif