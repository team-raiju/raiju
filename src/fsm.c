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

void init_enter(fsm_t* fsm);

void init_cycle(fsm_t* fsm);

void init_exit(fsm_t* fsm);

void idle_enter(fsm_t* fsm);

void idle_cycle(fsm_t* fsm);

void idle_exit(fsm_t* fsm);

void rc_enter(fsm_t* fsm);

void rc_cycle(fsm_t* fsm);

void rc_exit(fsm_t* fsm);

void auto_enter(fsm_t* fsm);

void auto_cycle(fsm_t* fsm);

void auto_exit(fsm_t* fsm);

void strategy_enter(fsm_t* fsm);

void strategy_cycle(fsm_t* fsm);

void strategy_exit(fsm_t* fsm);

void fsm_init(fsm_t* fsm) {
    init_enter(fsm);
}

static uint32_t time = 0;

#define reset_timer() time = HAL_GetTick()
#define get_timer() (HAL_GetTick() - time)

void fsm_cycle(fsm_t* fsm) {
    switch (fsm->current_state) {
        case INIT: {
            init_cycle(fsm);

            init_exit(fsm);
            idle_enter(fsm);
            break;
        }

        case IDLE: {
            idle_cycle(fsm);

            if (button_is_b1_pushed()) {
                idle_exit(fsm);
                auto_enter(fsm);
            }

            break;
        }

        case RC: {
            rc_cycle(fsm);

            if (button_is_b2_pushed()) {
                rc_exit(fsm);
                idle_enter(fsm);
            }

            break;
        }

        case AUTO: {
            auto_cycle(fsm);

            coordinate_t coords = radio_get_coordinates();

            if ((coords.x < -80) && (coords.y < -80)) {
                auto_exit(fsm);
                strategy_enter(fsm);
            }

            break;
        }

        case STRATEGY: {
            strategy_cycle(fsm);

            coordinate_t coords = radio_get_coordinates();

            if ((coords.x > 80) && (coords.y > 80)) {
                strategy_exit(fsm);
                idle_enter(fsm);
            }

            break;
        }
    }
}

void init_enter(fsm_t* fsm) {
    fsm->current_state = INIT;
    mcu_init();
    debug_init();
    motors_init();
    radio_init();
    buzzer_init();

    line_sensors_init();

    motors_drive(0, 0);
    mcu_sleep(1000);
}

void init_cycle(fsm_t* fsm) {
    (void) fsm;
    motors_drive(0, 0);
}

void init_exit(fsm_t* fsm) {
    (void) fsm;

    for (int i = 0; i < 5; i++) {
        led4_toggle();
        mcu_sleep(50);
    }
}

void idle_enter(fsm_t* fsm) {
    fsm->current_state = IDLE;
    led4_on();
}

void idle_cycle(fsm_t* fsm) {
    motors_drive(0, 0);
}

void idle_exit(fsm_t* fsm) {
    (void) fsm;
    led4_off();
}

void rc_enter(fsm_t* fsm) {
    fsm->current_state = RC;
    led1_on();
}

void rc_cycle(fsm_t* fsm) {
    (void) fsm;

    coordinate_t coords = radio_get_coordinates();

    motors_drive(coords.x, coords.y);
    mcu_sleep(3);
}

void rc_exit(fsm_t* fsm) {
    (void) fsm;

    led1_off();
}

void auto_enter(fsm_t* fsm) {
    fsm->current_state = AUTO;
    led2_on();
}

extern ppm_input_t ppms[];

void auto_cycle(fsm_t* fsm) {
    if (button_is_b2_pushed()) {
        while (button_is_b2_pushed())
            ;

        fsm->selected_strategy = (fsm->selected_strategy + 1) % 4;
    }

    led_n((uint8_t) fsm->selected_strategy);
}

void auto_exit(fsm_t* fsm) {
    (void) fsm;

    led2_off();
}

void strategy_enter(fsm_t* fsm) {
    fsm->current_state = STRATEGY;

    for (uint8_t i = 0; i < 5; i++) {
        mcu_sleep(675);
        led_gauge(i);
        buzzer_beep(300);
    }
}

void strategy_cycle(fsm_t* fsm) {
    switch (fsm->selected_strategy) {
        case ONE: {
            strategy_one();
            break;
        }

        case TWO: {
            strategy_two();
            break;
        }

        case THREE: {
            strategy_two();
            break;
        }

        case FOUR: {
            strategy_two();
            break;
        }
    }
}

void strategy_exit(fsm_t* fsm) {
    (void) fsm;
    led_gauge(0);
}
