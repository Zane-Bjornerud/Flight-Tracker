#include "../include/error_handler.h"
#include <stdio.h>

void handle_error(ErrorCode code, const char *message)
{
    fprintf(stderr, "Error: (%s): %s\n", error_to_string(code), message);
}

const char *error_to_string(ErrorCode code)
{
    switch (code)
    {
    case ERROR_NONE:
        return "No error";
    case ERROR_NETWORK:
        return "Network error";
    case ERROR_MEMORY:
        return "Memory error";
    case ERROR_API:
        return "API error";
    case ERROR_PARSE:
        return "Parse error";
    default:
        return "Unknown error";
    }
}