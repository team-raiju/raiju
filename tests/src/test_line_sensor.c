#include "mcu.h"
#include "utils.h"
#include "leds.h"
#include "debug.h"
#include "line.h"

void test_print_values() {
    debug_println("[LINE] Printing what sensors are seeing, this will hang...");

    for (;;) {
        debug_printf("[LINE] FR = % 04lu | FL = % 04lu | RR = % 04lu | RL = % 04lu",
                     line_sensor_get(FRONT_RIGHT),
                     line_sensor_get(FRONT_LEFT),
                     line_sensor_get(REAR_RIGHT),
                     line_sensor_get(REAR_LEFT));
        mcu_sleep(200);
    }

    debug_println("[LINE] done");
}

void test_line_sensors() {
    test_print_values();
}
