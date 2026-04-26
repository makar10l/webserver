#include <stdio.h>
#include <stdlib.h>
#include "socket.h"
#include "server.h"
#define PORT 8000

int main(){
	fprintf(stderr, "DEBUG: Checkpoint 1");
	server_t server = server_create("static/index.html", PORT);
	server_process(&server);
}