#include "file_searcher.h"
#include <string.h>
#include <stdio.h>
#define VARIABLES 4
#define MAX_PATH_LENGHT 256
const char* PATH_VARIABLES[] = {
    "static/%s",
    "user_static/%s",
    "static/%s/index.html",
    "user_static/%s/index.html"
};
FILE* search_file(char* filename){
    for(int index = 0; index < VARIABLES; index++){
        char fullpath[MAX_PATH_LENGHT];
        snprintf(fullpath, 256, PATH_VARIABLES[index], filename);
        FILE* f = fopen(fullpath, "rb");
        if(f != NULL) return f;
    }
    return NULL;
}
