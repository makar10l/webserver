#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H
#define HTTP_METHODS_COUNT 3
#define HTTP_METHOD_SIZE 16
#define HTTP_MAX_HEAD_SIZE 64
typedef enum{
    HTTP_GET, 
    HTTP_POST,
    HTTP_UNKOWN
} HTTP_METHOD;
extern const char* HTTP_METHODS_STRING[HTTP_METHODS_COUNT];
extern const HTTP_METHOD HTTP_METHODS_LIST[HTTP_METHODS_COUNT];
typedef struct{
    HTTP_METHOD method;
    char filename[64];
    int filename_size; 
} http_parser_result;

http_parser_result http_parse_request(char* req_head, int head_size);
#endif