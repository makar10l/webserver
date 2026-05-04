#include "file_searcher.h"
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
/* 
    @var MAX_PATH_LENGHT
    @brief maximal path lenght
    @note path means static_directory + filename
*/
static const int MAX_PATH_LENGHT = 256; 
/*
    @var PATH_VARIABLES[]
    @brief contains all static path variants (path to directories)
    @note %s means filename
*/
static const char* PATH_VARIABLES[] = {
    "static/%s",
    "user_static/%s",
    "static/%s/index.html",
    "user_static/%s/index.html"
};
/*
    @var PATH_VARIABLES_COUNT
    @brief count of path variables
    @note do not touch it, it calculates automaticly
*/
static const int PATH_VARIABLES_COUNT = sizeof(PATH_VARIABLES) / sizeof(char*);
/*
    @see file_searcher.h
*/
FILE* search_file(char* filename){
    struct stat filestat;
    char fullpath[MAX_PATH_LENGHT] = {0};
    FILE* searchable_file = NULL; /* output file */
    for(int index = 0; index < PATH_VARIABLES_COUNT; index++){
        memset(fullpath, 0, MAX_PATH_LENGHT ); /* clear fullpath array */
        snprintf(fullpath, MAX_PATH_LENGHT, PATH_VARIABLES[index], filename); /* generating fullpath from PATH_VARIABLE and filename*/
        fprintf(stderr, "%s\n", fullpath);

        stat(fullpath, &filestat); 
        
        if(S_ISREG(filestat.st_mode)){
            searchable_file = fopen(fullpath, "rb"); //checking that searched file is FILE, not DIRECTORY
        }

        if(searchable_file != NULL) return searchable_file;
    }
    return NULL;
}
