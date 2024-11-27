#include "../include/http_client.h"
#include "../include/error_handler.h"
#include "../include/flight_data.h"
#include <stdio.h>

#define INITIAL_CAPACITY 100

int main(void)
{
    // initialize HTTP client
    if (http_client_init() != 0)
    {
        return 1;
    }

    FlightList *flights = flight_list_create(INITIAL_CAPACITY);
    if (!flights)
    {
        http_client_cleanup();
        return 1;
    }

    // API URL
    const char *url = "";

    // get data from API
    Response *resp = http_get(url);
    if (resp)
    {
        printf("Reeived data: %zu bytes\n", resp->size);
        // TODO: parse data and add to flight list
        free_response(resp);
    }

    flight_list_free(flights);
    http_client_cleanup();
    return 0;
}