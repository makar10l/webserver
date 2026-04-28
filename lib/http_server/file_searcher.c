#include "file_searcher.h"
#include <string.h>
#include <stdio.h>
#define VARIABLES 4
const char* PATH_VARIABLES[] = {
    "static/%s",
    "usr_static/%s",
    "static/%s/index.html",
    "usr_static/%s/index.html"
};
FILE* search_file(char* filename){
    for(int index = 0; index < VARIABLES; index++){
        char fullpath[256];
        snprintf(fullpath, 256, PATH_VARIABLES[index], filename);
        FILE* f = fopen(fullpath, "rb");
        if(f != NULL) return f;
    }
    return NULL;
}
