#include "mcu.h"
#include "utils.h"
#include "motors.h"
#include "leds.h"
#include "debug.h"
#include "radio.h"

extern ppm_input_t ppms[];

void test_ppm_reading() {
    debug_println("[PPM] PPM reading, this will hang...");

    for (;;) {
        coordinate_t coords = radio_get_coordinates();
        debug_printf("[PPM] coords.x = % 04d | coords.y = % 04d", coords.x, coords.y);
        debug_printf("[PPM] ppm0     = %04ld | ppm1     = %04ld", ppms[0].value, ppms[1].value);

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

        mcu_sleep(100);
    }

    debug_println("[PPM] done");
}

void test_radio() {
    test_ppm_reading();
}
