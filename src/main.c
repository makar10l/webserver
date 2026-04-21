#include <stdio.h>
#include <stdlib.h>
#include "socket.h"
#include "server.h"
#define PORT 8000

int main(){
	server_t server = server_create("static/index.html", PORT);
    
	while(1){
		server_process(&server);
	}
}