#include "mcu.h"
#include "utils.h"
#include "leds.h"
#include "debug.h"
#include "buzzer.h"

void test_beeping() {
    debug_println("[BUZZER] Beeping 5 times");

    for (uint8_t i = 0; i < 5; i++) {
        debug_println("[BUZZER] Beeping");
        mcu_sleep(700);
        buzzer_beep(300);
    }

    debug_println("[BUZZER] done");
}

void test_buzzer() {
    test_beeping();
}
