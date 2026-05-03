#include "file_searcher.h"
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
const int VARIABLES = 4;
const int MAX_PATH_LENGHT = 256;
const char* PATH_VARIABLES[] = {
    "static/%s",
    "user_static/%s",
    "static/%s/index.html",
    "user_static/%s/index.html"
};
FILE* search_file(char* filename){
    struct stat filestat;
    FILE* f = NULL;
    for(int index = 0; index < VARIABLES; index++){
        char fullpath[MAX_PATH_LENGHT];
        snprintf(fullpath, 256, PATH_VARIABLES[index], filename);
        fprintf(stderr, "%s\n", fullpath);

        stat(fullpath, &filestat);

        if(S_ISREG(filestat.st_mode)){
            f = fopen(fullpath, "rb");
        }

        if(f != NULL) return f;
    }
    return NULL;
}
