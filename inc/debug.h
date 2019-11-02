/**
 * @file debug.h
 *
 * @brief USART debugging using ST-Link serial converter
 *
 * @author Daniel Nery <danielnso97@gmail.com>
 */

#if !defined(__DEBUG_H__)
#define __DEBUG_H__

#ifdef DEBUG

#include <stdio.h>

extern char __debug_buffer[128];

#define debug_printf(...) do {                                         \
        snprintf(__debug_buffer, sizeof(__debug_buffer), __VA_ARGS__); \
        debug_println(__debug_buffer);                                 \
} while (0)                                                            \

#else
#define debug_printf(...)
#endif

void debug_init();

void debug_println(char* msg);

#endif // __DEBUG_H__
