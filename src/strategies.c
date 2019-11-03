#include "strategies.h"

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

static uint32_t time = 0;

#define reset_timer() time = HAL_GetTick()
#define get_timer() (HAL_GetTick() - time)

void strategy_one() {
    if (distance_is_front_seeing()) {
        motors_drive(100, 100);
    } else if (distance_is_left_seeing() && !distance_is_right_seeing()) {
        motors_drive(50, -50);
    } else if (!distance_is_left_seeing() && distance_is_right_seeing()) {
        motors_drive(-50, 50);
    } else if (distance_is_left_seeing() && distance_is_right_seeing()) {
        motors_drive(100, 100);
    } else {
        motors_drive(50, 50);
    }

    if (line_sensor_get(FRONT_LEFT) < 2000) {
        motors_drive(-100, -100);
        mcu_sleep(200);
        motors_drive(50, -50);
        mcu_sleep(200);
    } else if (line_sensor_get(FRONT_RIGHT) < 2000) {
        motors_drive(-100, -100);
        mcu_sleep(200);
        motors_drive(-50, 50);
        mcu_sleep(200);
    }
}

void strategy_two() {
    if (distance_is_front_seeing()) {
        motors_drive(100, 100);
        reset_timer();
    } else if (distance_is_left_seeing() && !distance_is_right_seeing()) {
        motors_drive(50, -50);
        reset_timer();
    } else if (!distance_is_left_seeing() && distance_is_right_seeing()) {
        motors_drive(-50, 50);
        reset_timer();
    } else if (distance_is_left_seeing() && distance_is_right_seeing()) {
        motors_drive(100, 100);
        reset_timer();
    } else {
        motors_drive(0, 0);
    }

    if (get_timer() > 2000) {
        motors_drive(60, 60);
        mcu_sleep(100);
        reset_timer();
    }

    if (line_sensor_get(FRONT_LEFT) < 2000) {
        motors_drive(-100, -100);
        mcu_sleep(200);
        motors_drive(50, -50);
        mcu_sleep(200);
    } else if (line_sensor_get(FRONT_RIGHT) < 2000) {
        motors_drive(-100, -100);
        mcu_sleep(200);
        motors_drive(-50, 50);
        mcu_sleep(200);
    }
}
