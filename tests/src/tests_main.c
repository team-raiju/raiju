/**
 * @file test_main.c
 *
 * @brief Main function for tests.
 */

#include <stdio.h>
#include "mcu.h"
#include "leds.h"
#include "radio.h"
#include "line.h"
#include "buzzer.h"
#include "motors.h"
#include "debug.h"

#ifndef DEBUG
#warning DEBUG is not defined, st-link print statements wont work
#endif

int main(void) {
    mcu_init();
    debug_init();
    debug_println("[INIT] Initializing tests");

    debug_println("[INIT] Initializing motors");
    motors_init();

    debug_println("[INIT] Initializing radio");
    radio_init();

#if 1
    debug_println("[INIT] Initializing line sensors");
    line_sensors_init();
#endif

    debug_println("[INIT] Initializing buzzer");
    buzzer_init();

#if 0
    test_buzzer();
    test_motors();
    test_radio();
    test_line_sensors();
#endif
    test_distance_sensors();

    led1_off();
    led2_off();
    led3_off();
    led4_off();

    for (;;) {
        led1_toggle();
        led2_toggle();
        led3_toggle();
        led4_toggle();
        mcu_sleep(1000);
    }
}
