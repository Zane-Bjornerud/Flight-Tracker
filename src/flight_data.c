#include "../include/flight_data.h"
#include "../include/error_handler.h"
#include <stdlib.h>
#include <string.h>

FlightList *flight_list_create(size_t initial_capacity)
{
    // allocate memory for struct
    FlightList *list = malloc(sizeof(FlightList));
    if (!list)
    {
        handle_error(ERROR_MEMORY, "Failed to allocate memory for flight list");
        return NULL;
    }

    // allocate the array of flight structs
    list->flights = malloc(sizeof(Flight) * initial_capacity);
    if (!list->flights)
    {
        handle_error(ERROR_MEMORY, "Failed to allocate memory for flight list");
        free(list);
        return NULL;
    }

    list->count = 0;
    list->capacity = initial_capacity;
    return list;
}

int flight_list_add(FlightList *list, Flight flight)
{
    // check if list is full, if full resize to double the capacity
    if (list->count == list->capacity)
    {
        size_t new_capacity = list->capacity * 2;
        Flight *new_flights = realloc(list->flights, sizeof(Flight) * new_capacity);
        if (!new_flights)
        {
            handle_error(ERROR_MEMORY, "Failed to reallocate memory for flight list");
            return -1;
        }
        list->flights = new_flights;
        list->capacity = new_capacity;
    }

    list->flights[list->count++] = flight;
    return 0;
}

void flight_list_free(FlightList *list)
{
    if (list)
    {
        free(list->flights);
        free(list);
    }
}