/**
 * @file main.c
 *
 * @brief Main function
 */

#include <stdio.h>
#include <stdbool.h>

#include "mcu.h"
#include "fsm.h"

#include "motors.h"
#include "buttons.h"
#include "radio.h"
#include "mcu.h"
#include "buzzer.h"
#include "leds.h"
#include "distance.h"
#include "line.h"
#include "debug.h"
#include "utils.h"
#include "strategies.h"

/*****************************************
 * Private Constant Definitions
 *****************************************/

/*****************************************
 * Main Function
 *****************************************/

// fsm_t main_fsm;

int main(void) {
    // fsm_init(&main_fsm);

    // for (;;) {
    // fsm_cycle(&main_fsm);
    // }

    //// RC
    mcu_init();

    // debug_init();
    motors_init();
    radio_init();
    buzzer_init();

    motors_drive(0, 0);
    mcu_sleep(1000);

    for (int i = 0; i < 5; i++) {
        led4_toggle();
        mcu_sleep(50);
    }

    for (;;) {
        coordinate_t coords = radio_get_coordinates();

        motors_drive(coords.x, coords.y);
        mcu_sleep(5);
    }
}
