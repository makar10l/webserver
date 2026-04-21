#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>

typedef struct{
    int sock_fd;
    int client_fd;

    char* req_buffer;

    struct sockaddr_in sock_rules;
    struct sockaddr client_rules;

    socklen_t rules_size;
    socklen_t client_rules_size;
} socket_t;

/* @ socket_create() 
parameters : port(1024 to 65535), 
             domain(means IPv4 or IPv6), 
             input_addr(addresses from which socket reads data)

return values :
            socket_t sock with field sock_fd > 0 everything good, socket opens sucessfully
            with sock_fd == -2 port is busy
            with sock_fd == -1 OS doesnt allow open socket
*/
socket_t socket_create(int port, int domain, in_addr_t input_addr);

/* @ socket_close()
parameters: pointer to socket struct

return values :
            0 everything is good
            -1 OS doesnt allow close socket
*/
int socket_close(socket_t* sock);
/* @ socket_client_close()
parameters: pointer to socket struct

return values :
            0 everything is good
            -1 OS doesnt allow close socket
*/
int socket_client_close(socket_t* sock);
/* @ socket_listen()
parameters : sock - pointer to  socket struct
            backlog - max clients queue
return values : 
                0 everything is good
                -1 OS error*/
int socket_listen(socket_t* sock, int backlog);

/* @ socket_accept()
parameters : sock - pointer to  socket struct
return values : 
                0 everything is good
                -1 OS error*/
int socket_accept(socket_t* sock);

/* @ socket_read()
parameters : sock - pointer to  socket struct
            data_len - size of data which you want to read
return values : 
                0 everything is good
                -1 OS error
                -5 client fd error
                -2 cannot alocate memory*/
int socket_read(socket_t* sock, int data_len);
/* @ socket_send()
parameters : sock - pointer to  socket struct
            data_len - size of data which you want to read
            send_data - data to send
return values : 
                0 everything is good
                -1 OS error
                -5 client fd error
                -2 cannot alocate memory*/
int socket_send(socket_t* sock, char* send_data, int data_len);
#endif