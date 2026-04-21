#include <stdio.h>
#include <stdlib.h>
#include "socket.h"
#include "server.h"
#define PORT 8001

int main(){
	server_t server = server_create("index.html", PORT);
    
	while(1){
		server_process(&server);
	}
}