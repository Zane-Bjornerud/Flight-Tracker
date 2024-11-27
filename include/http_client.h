#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <curl/curl.h>

typedef struct
{
    char *data;
    size_t size;
} Response;

int http_client_init(void);
void http_client_cleanup(void);
Response *http_get(const char *url);
void free_response(Response *response);

#endif