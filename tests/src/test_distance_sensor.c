#include "mcu.h"
#include "utils.h"
#include "leds.h"
#include "debug.h"
#include "distance.h"

void test_print_seeing() {
    debug_println("[DISTANCE] Printing what sensors are seeing, this will hang...");

    for (;;) {
        debug_printf("[DISTANCE] left = %d | center = %d | right = %d",
                     distance_is_left_seeing() ? 1 : 0,
                     distance_is_front_seeing() ? 1 : 0,
                     distance_is_right_seeing() ? 1 : 0);
        mcu_sleep(200);
    }

    debug_println("[DISTANCE] done");
}

void test_distance_sensors() {
    test_print_seeing();
}
