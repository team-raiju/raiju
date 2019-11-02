#include <string.h>

#include "debug.h"
#include "usart.h"

#ifdef DEBUG

char __debug_buffer[128];

void debug_init() {
    MX_USART1_UART_Init();
}

void debug_println(char* msg) {
    HAL_UART_Transmit(&huart1, (uint8_t*) msg, strlen(msg), 100);
    HAL_UART_Transmit(&huart1, (uint8_t*) "\r\n", 2, 10);
}

#else

void debug_init() {
}

void debug_println(char* msg) {
    (void) msg;
}

#endif
