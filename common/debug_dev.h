#ifndef DEBUG_DEV_H
#define DEBUG_DEV_H

#include "hal.h"
#include <string.h>
#include <stdio.h>

#define MAX_STR_SIZE 100

// Fetch the len of a constant char in C
__attribute__((unused))
static size_t __str_len(const char * str) {
    const char * ptr = str;
    while(*ptr != '\0') {
        ptr++;
    }
    return ptr - str;
}

#define DEBUG_PRINT(...) do { ; } while(0)/*\
    char buf[MAX_STR_SIZE]; \
    const char * prefix = "[DEBUG] "; \
    memcpy(buf, prefix, __str_len(prefix)); \
    sprintf(buf + __str_len(prefix), __VA_ARGS__); hal_send_str(buf); \
} while (0)*/

#endif // DEBUG_DEV_H

