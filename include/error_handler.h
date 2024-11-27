#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

typedef enum
{
    ERROR_NONE = 0,
    ERROR_NETWORK,
    ERROR_MEMORY,
    ERROR_API,
    ERROR_PARSE
} ErrorCode;

void handle_error(ErrorCode code, const char *message);
const char *error_to_string(ErrorCode code);

#endif