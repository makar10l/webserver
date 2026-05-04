#ifndef FILE_SEARCHER
#define FILE_SEARCHER

#include <stdio.h>
/*
    @brief function that searches file in directories (user_static/ and static/)
    @param filename a pointer to the file name to search
    @retval FILE-type pointer to searched file
    @retval NULL pointer if file does not exist
*/
FILE* search_file(char* filename);

#endif