#ifndef HTTP_PARSER_H
#define HTTP_PARSER_H
typedef enum{
    HTTP_GET, 
    HTTP_POST,
    HTTP_UNKOWN
} HTTP_METHOD;

typedef enum{
    JPG,
    HTML,
    CSS,
    JS,
    ICO,
    UNKOWN
} FILE_EXTENSION;
typedef struct{
    HTTP_METHOD method;
    char filename[64];
    int filename_size;
    FILE_EXTENSION extens;

} http_parser_result;

http_parser_result http_parse_request(char* req_head, int head_size);
#endif