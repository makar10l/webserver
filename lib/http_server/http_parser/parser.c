#include <stdlib.h>
#include <string.h>
#include "parser.h"
const char* HTTP_METHODS_STRING[HTTP_METHODS_COUNT] = {"GET", "POST", "UNKOWN"};
const HTTP_METHOD HTTP_METHODS_LIST[HTTP_METHODS_COUNT] = {HTTP_GET, HTTP_POST, HTTP_UNKOWN};
http_parser_result http_parse_request(char* header, int header_size){
    int head_size = 0;
    char* head = NULL;
    //calctulating fisrt string(in http header) lenght
    for(int i = 0; i < header_size; i++){
        if(header[i] == '\r' && header[i + 1] == '\n'){
            head_size = i;
            break;
        }
    }

    if(head_size = 0) ;// write some return TODO!

    head = malloc(head_size);
    memcpy(head, header, head_size);
    head[head_size] = '\0';
    http_parser_result res;
    res.method = HTTP_UNKOWN;
    res.filename_size = 0;
    int head_pos = 0;

    //method parsing
    char http_method[HTTP_METHOD_SIZE];       
    for(int i = 0; i < HTTP_METHOD_SIZE; i++){
        if(head[i] == ' '){
            head_pos = i + 1; //because head[i] = ' ' but we need head[head_pos] != ' ' 
            http_method[i] = '\0';
            break;
        }
        http_method[i] = head[i];
    }
    for(int i = 0; i < HTTP_METHODS_COUNT; i++){
        if(strcmp(http_method, HTTP_METHODS_STRING[i]) == 0) res.method = HTTP_METHODS_LIST[i];
    }

    //filename parsing
    if(res.method == HTTP_UNKOWN) return res;

    for(int i = head_pos; i < HTTP_MAX_HEAD_SIZE; i++){
        if(head[i] == ' '){
            res.filename[i - head_pos] = '\0';
            res.filename_size = i - head_pos;
            break;
        }
        res.filename[i - head_pos] = head[i]; // normalizing index in [i - head_pos]
    }

    return res;
}