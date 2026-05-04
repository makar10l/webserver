#include <stdio.h>
#include <stdlib.h>
#include "socket.h"
#include "server.h"
#include "file_searcher.h"
const int PORT = 8000;
int main(){
	server_t server = server_create(PORT);
	while(1){
	 server_process(&server);
	}
}   