/**
 * @file main.c
 *
 * @brief Main function
 */

#include <stdio.h>
#include <stdbool.h>

#include "mcu.h"
#include "utils.h"
#include "motors.h"
#include "distance.h"
#include "leds.h"
#include "debug.h"
#include "buzzer.h"
#include "buttons.h"
#include "radio.h"

/*****************************************
 * Private Constant Definitions
 *****************************************/

static bool is_auto = false;

/*****************************************
 * Main Function
 *****************************************/

void rc() {
    coordinate_t coords = radio_get_coordinates();

    motors_drive(coords.x, coords.y);
    mcu_sleep(3);
}

const int speed = 20;

void strategy() {
    if (distance_is_front_seeing()) {
        motors_drive(speed, speed);
    } else if (distance_is_left_seeing() && !distance_is_right_seeing()) {
        motors_drive(-speed * 2, speed * 2);
    } else if (!distance_is_left_seeing() && distance_is_right_seeing()) {
        motors_drive(speed * 2, -speed * 2);
    } else if (distance_is_left_seeing() && distance_is_right_seeing()) {
        motors_drive(speed, speed);
    } else {
        motors_drive(0, 0);
    }
}

void auton() {
    if (radio_get_coordinates().x >= -50) {
        return;
    }

    for (uint8_t i = 0; i < 5; i++) {
        mcu_sleep(675);
        led_gauge(i);
        buzzer_beep(300);
    }

    while (radio_get_coordinates().x <= 50) {
        strategy();
    }

    motors_drive(0, 0);
}

int main(void) {
    mcu_init();
    debug_init();
    debug_println("Initializing");

    debug_println("Initializing motors");
    motors_init();

    debug_println("Initializing radio");
    radio_init();

    buzzer_init();

    motors_drive(0, 0);
    mcu_sleep(1000);

    for (int i = 0; i < 5; i++) {
        led4_toggle();
        mcu_sleep(50);
    }

    for (;;) {
        motors_drive(0, 0);

        while (!is_auto) {
            led_gauge(0);
            led2_on();
            rc();

            if (button_is_b1_pushed()) {
                is_auto = true;
            }
        }

        while (is_auto) {
            led_gauge(0);
            led1_on();

            auton();

            if (button_is_b2_pushed()) {
                is_auto = false;
            }
        }
    }
}
