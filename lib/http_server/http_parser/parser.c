#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include <stdio.h>
const int HTTP_METHODS_COUNT = 3;
const int HTTP_METHOD_SIZE = 16;
const int HTTP_MAX_HEAD_SIZE = 64;
const char* HTTP_METHODS_STRING[HTTP_METHODS_COUNT] = {"GET", "POST", "UNKOWN"};
const HTTP_METHOD HTTP_METHODS_LIST[HTTP_METHODS_COUNT] = {HTTP_GET, HTTP_POST, HTTP_UNKOWN};

const int EXTENSIONS_COUNT = 5; 
const char* FILE_EXTENSIONS_STRING[EXTENSIONS_COUNT] = {"html", "css", "js", "jpg", "ico"};
const FILE_EXTENSION FILE_EXTENSIONS_LIST[EXTENSIONS_COUNT] = {HTML, CSS, JS, JPG, ICO};

http_parser_result http_parse_request(char* header, int header_size){
    http_parser_result res;
    res.method = HTTP_UNKOWN;
    res.filename_size = 0;

    char* head = NULL;

    //calctulating fisrt string(in http header) lenght
    int head_size = 0;
    for(int i = 0; i < header_size; i++){
        if(header[i] == '\r' && header[i + 1] == '\n'){
            head_size = i;
            break;
        }
    }

    if(head_size == 0) return res;

    head = malloc(head_size + 1);
    if(!head) return res;
    memcpy(head, header, head_size);
    head[head_size] = '\0';

    //method parsing
    char http_method[HTTP_METHOD_SIZE]; 
    int head_pos = 0;      
    for(; head_pos < HTTP_METHOD_SIZE; head_pos++){
        if(head[head_pos] == ' '){
            http_method[head_pos] = '\0';
            head_pos++; //because head[head_pos] = ' ' but we need head[head_pos] != ' ' 
            break;
        }
        http_method[head_pos] = head[head_pos];
    }
    for(int i = 0; i < HTTP_METHODS_COUNT; i++){
        if(strcmp(http_method, HTTP_METHODS_STRING[i]) == 0) res.method = HTTP_METHODS_LIST[i];
    }

    //filename parsing
    if(res.method == HTTP_UNKOWN){
        free(head);
        return res;
    }

    for(int i = head_pos; i < HTTP_MAX_HEAD_SIZE; i++){
        if(head[i] == ' '){
            res.filename[i - head_pos] = '\0';
            res.filename_size = i - head_pos;
            break;
        }
        res.filename[i - head_pos] = head[i]; // normalizing index in [i - head_pos]
    }
    free(head);

    //getting file extension
    char* filename_pos = res.filename;
    for(; (*filename_pos) != '\0'; filename_pos++) if(*filename_pos == '.') break;
    if(*filename_pos == '\0') res.extens = UNKOWN;
    filename_pos++;

    fprintf(stderr, "FIRST : %s\n",filename_pos);
    for(int i = 0; i < EXTENSIONS_COUNT; i++){
        fprintf(stderr, "\n%d : %s\n", i, FILE_EXTENSIONS_STRING[i]);
        if(strcmp(filename_pos, FILE_EXTENSIONS_STRING[i]) == 0) {res.extens = FILE_EXTENSIONS_LIST[i]; break;}
    }
    
    return res;
}

