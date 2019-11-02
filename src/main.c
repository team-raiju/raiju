/**
 * @file main.c
 *
 * @brief Main function
 */

#include <stdio.h>

#include "mcu.h"
#include "utils.h"
#include "motors.h"
#include "leds.h"
#include "debug.h"
#include "radio.h"

/*****************************************
 * Private Constant Definitions
 *****************************************/

static char debug_buffer[128];

/*****************************************
 * Main Function
 *****************************************/

int main(void) {
    mcu_init();
    debug_init();
    debug_println("Initializing");

    debug_println("Initializing motors");
    motors_init();

    debug_println("Initializing radio");
    radio_init();

    led4_on();

    mcu_sleep(5000);

    debug_println("Starting...");
    led2_on();

    for (;;) {
    }
}
