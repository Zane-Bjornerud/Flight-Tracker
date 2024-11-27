#include "../include/http_client.h"
#include "../include/error_handler.h"
#include <stdlib.h>
#include <string.h>

static size_t write_callback(void *data, size_t size, size_t numElms, void *userp)
{
    size_t realsize = size * numElms;
    Response *resp = (Response *)userp;

    // dynamically resize buffer to fit new data
    char *ptr = realloc(resp->data, resp->size + realsize + 1);
    if (!ptr)
    {
        handle_error(ERROR_MEMORY, "Failed to allocate memory for response data");
        return 0;
    }

    // copy new data to end of buffer
    resp->data = ptr;
    memcpy(&(resp->data[resp->size]), data, realsize);
    resp->size += realsize;     // update size
    resp->data[resp->size] = 0; // null-terminate the string

    return realsize; // return nmber of bytes processed
}

int http_client_init(void)
{
    if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK)
    {
        handle_error(ERROR_NETWORK, "Failed to initialize libcurl");
        return 1;
    }
    return 0;
}

void http_client_cleanup(void)
{
    curl_global_cleanup();
}

Response *http_get(const char *url)
{
    CURL *curl = curl_easy_init();
    if (!curl)
    {
        handle_error(ERROR_NETWORK, "Failed to initialize libcurl easy handle");
        return NULL;
    }

    Response *resp = malloc(sizeof(Response));
    if (!resp)
    {
        handle_error(ERROR_MEMORY, "Failed to allocate memory for response object");
        curl_easy_cleanup(curl);
        return NULL;
    }

    // tells CURL where to fetch data from
    curl_easy_setopt(curl, CURLOPT_URL, url);
    // tells CURL to call write_callback() for each chunk of data received
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    // passes the Response object to write_callback()
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, resp);
    // sets the user-agent header
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "FlightTracker/1.0");

    CURLcode res = curl_easy_perform(curl); // performs actual request
    if (res != CURLE_OK)
    {
        handle_error(ERROR_NETWORK, curl_easy_strerror(res));
        free_response(resp);
        curl_easy_cleanup(curl);
        return NULL;
    }

    curl_easy_cleanup(curl);
    return resp;
}

void free_response(Response *resp)
{
    if (resp)
    {
        free(resp->data);
        free(resp);
    }
}
