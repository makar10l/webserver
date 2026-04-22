#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H
#define HTTP_METHODS_COUNT 3
#define HTTP_METHOD_SIZE 16
typedef enum HTTP_METHOD{
    HTTP_GET, 
    HTTP_POST,
    HTTP_UNKOWN
};
const char* HTTP_METHODS_STRING[HTTP_METHOD_COUNT] = {"GET", "POST", "UNKOWN"};
const HTTP_METHOD HTTP_METHODS_LIST[HTTP_METHOD_COUNT] = {HTTP_GET, HTTP_POST, HTTP_UNKOWN};
typedef struct{
    HTTP_METHOD method;
    char filename[64];
    int filename_size; 
} http_parser_result;

char* http_get_request_head(char* header, int lenght);
http_parser_result http_parse_request(char* req_head, int head_size);
//idk
#endif