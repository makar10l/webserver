#include <socket.h> //connects with -I compiler flag 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
socket_t socket_create(int port, int domain, in_addr_t input_addr){
    socket_t sock;
    sock.client_fd = 0;
    sock.sock_fd = socket(domain, SOCK_STREAM, 0); //getting socket fd from os
    if(sock.sock_fd == -1) {
        sock.sock_fd = -1;
        return sock;
    }

    sock.sock_rules.sin_family = domain;            //AF_INET(IPv4) or AF_INET6(IPv6)
    sock.sock_rules.sin_addr.s_addr = input_addr;  // Input IP address
    sock.sock_rules.sin_port = htons(port);        //port + converting little-endian to big

    sock.rules_size = sizeof(sock.sock_rules);
    sock.client_rules_size = sizeof(sock.client_rules);

    sock.req_buffer = NULL;
    int opt = 1;
    setsockopt(sock.sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    int sock_bind = bind(sock.sock_fd, (struct sockaddr*)&sock.sock_rules, sock.rules_size);
    if(sock_bind == -1) {
        close(sock.sock_fd);
        sock.sock_fd = -2;
    }

    return sock;
}

int socket_close(socket_t* sock){
    int sock_close = close(sock->sock_fd);

    if(sock_close == -1){
        return -1;
    }
    free(sock->req_buffer);
    return 0;
}

int socket_client_close(socket_t* sock){
     int sock_close = close(sock->client_fd);

    if(sock_close == -1){
        return -1;
    }
    return 0;
}

int socket_listen(socket_t* sock, int backlog){
    int sock_listen = listen(sock->sock_fd, backlog);
    if(sock_listen < 0) return sock_listen;
    return 0;
}

int socket_accept(socket_t* sock){
    int client_socket = accept(sock->sock_fd, (struct sockaddr*)&sock->client_rules, &(sock->client_rules_size));
    if(client_socket < 0) return client_socket;
    sock->client_fd = client_socket;
    return 0;
}

int socket_read(socket_t* sock, int data_len){
    if(sock->client_fd <= 0) return -5;
    if(data_len < 1) return -6;
    free(sock->req_buffer);
    sock->req_buffer = malloc(data_len); // риллок добавить надо
    if(sock->req_buffer == NULL) return -2;

    int sock_read = read(sock->client_fd, sock->req_buffer, data_len);
    if(sock_read < 0) return sock_read;
    return 0;
}

int socket_send(socket_t* sock, const char* send_data, int data_len){
    if(sock->client_fd <= 0) return -5;

    int sock_send = send(sock->client_fd, send_data, data_len, 0);
    if(sock_send < 0) return sock_send;
    return 0;
}