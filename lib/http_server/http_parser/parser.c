#include <stdlib.h>
#include "parser.h"
char* http_get_head(char* header, int lenght){
    int head_size = 0;
    char* head = NULL;

    for(int i = 0; i < lenght; i++){
        if(header[i] == '\r' && header[i + 1] == '\n'){
            head_size = i;
            break;
        }
    }
    if(head_size == 0) return NULL;

    head = malloc(head_size);
    if(head == NULL) return NULL;

    memcpy(head, header, head_size);
    head[head_size] = '\0';
    return head;
}

http_parser_result http_parse_request(char* req_head, int head_size){
    http_parser_result res;
    res.method = HTTP_UNKOWN;
    res.filename_size = 0;
    int head_pos = 0;

    //method parsing
    char http_method[HTTP_METHOD_SIZE];       
    for(int i = 0; i < HTTP_METHOD_SIZE; i++){
        if(req_head[i] == ' '){
            head_pos = i;
            http_method[i] = '\0';
            break;
        }
        http_method[i] = req_head[i];
    }
    for(int i = 0; i < HTTP_METHODS_COUNT; i++){
        if(strcmp(http_method, HTTP_METHODS_STRING[i]) == 0) res.method = HTTP_METHODS_LIST[i];
    }

    //filename parsing
    if(res.method == HTTP_UNKOWN) return res;

    for(int i = head_pos + 1; i < head_size; i++){
        if(req_head[i] == ' '){
            res.filename[i - head_pos - 1] = '\0';
            res.filename_size = i - head_pos - 1;
            break;
        }
        res.filename[i - head_pos - 1] = req_head[i];
    }

    return res;
}