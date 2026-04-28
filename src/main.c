#include <stdio.h>
#include <stdlib.h>
#include "socket.h"
#include "server.h"
#include "file_searcher.h"
#define PORT 8000

int main(){
	FILE* hh =search_file("porn/");
	if(hh == NULL){
		printf("Hello");
	}
	// fprintf(stderr, "DEBUG: Checkpoint 1");
	// server_t server = server_create("static/index.html", PORT);
	// while(1){
	// server_process(&server);
	// }
}