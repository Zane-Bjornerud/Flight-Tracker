#ifndef FLIGHT_DATA_H
#define FLIGHT_DATA_H

#include <time.h>

typedef struct
{
    char flight_id[8];
    char callsign[8];
    double latitude;
    double longitude;
    double altitude;
    double ground_speed;
    double heading;
    time_t last_update;
} Flight;

typedef struct
{
    Flight *flights;
    size_t count;    // number of flights in list
    size_t capacity; // capacity of array
} FlightList;

FlightList *flight_list_create(size_t initial_capacity);
int flight_list_add(FlightList *list, Flight flight);
void flight_list_free(FlightList *list);

#endif