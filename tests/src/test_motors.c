#include "mcu.h"
#include "utils.h"
#include "motors.h"
#include "leds.h"
#include "debug.h"
#include "radio.h"

void test_ppm_to_motors() {
    debug_println("[MOTORS] PPM to motors, this will hang...");

    for (;;) {
        coordinate_t coords = radio_get_coordinates();

        // debug_printf("[MOTORS] ppm.x = % 04d | ppm.y = % 04d", coords.x, coords.y);

        if (coords.x > 0) {
            led1_on();
        } else {
            led1_off();
        }

        if (coords.y > 0) {
            led3_on();
        } else {
            led3_off();
        }

        motors_drive(coords.x, coords.y);
        mcu_sleep(5);
    }

    debug_println("[MOTORS] done");
}

void test_motors_back_and_forth() {
    debug_println("[MOTORS] both backwards");

    for (int i = 0; i > -100; i--) {
        motors_drive(i, i);
        mcu_sleep(5);
    }

    debug_println("[MOTORS] both forward");
    led3_on();

    for (int i = -100; i < 100; i++) {
        motors_drive(i, i);
        mcu_sleep(5);
    }

    mcu_sleep(20000);

    debug_println("[MOTORS] both backwards");
    led3_off();

    for (int i = 100; i > -100; i--) {
        motors_drive(i, i);
        mcu_sleep(5);
    }

    mcu_sleep(20000);

    debug_println("[MOTORS] stop");
    motors_drive(0, 0);
    debug_println("[MOTORS] done");
}

void test_motors() {
    test_ppm_to_motors();

#if 0
    test_motors_back_and_forth();
#endif
}
