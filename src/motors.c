/**
 * @file motors.c
 *
 * @brief Functions used to control motors
 */

#include "motors.h"
#include "tim.h"
#include "utils.h"

/***********************************************************************
 * PWM Adapter
 ***********************************************************************/

void pwm_init(pwm_t* pwm) {
    if (pwm->init_f != NULL) {
        pwm->init_f();
    }

    HAL_TIM_PWM_Start(pwm->htim, pwm->channel);
    __HAL_TIM_SET_COMPARE(pwm->htim, pwm->channel, 0);
}

void pwm_set(pwm_t* pwm, uint32_t value) {
    __HAL_TIM_SET_COMPARE(pwm->htim, pwm->channel, value);
}

/***********************************************************************
 * Motor Adapter
 ***********************************************************************/

void motor_init(motor_t* motor) {
    pwm_init(&motor->red_pwm);
    pwm_init(&motor->black_pwm);
}

void motor_stop(motor_t* motor) {
    pwm_set(&motor->red_pwm, 0);
    pwm_set(&motor->black_pwm, 0);
}

void motor_drive(motor_t* motor, int32_t speed) {
    if (speed < 0) {
        pwm_set(&motor->red_pwm, -speed);
        pwm_set(&motor->black_pwm, 0);
    } else {
        pwm_set(&motor->red_pwm, 0);
        pwm_set(&motor->black_pwm, speed);
    }
}

/***********************************************************************
 * Driving Service
 ***********************************************************************/

static motor_t left_motor = {
    .black_pwm = {
        .init_f = MX_TIM1_Init,
        .htim = &htim1,
        .channel = TIM_CHANNEL_1,
    },
    .red_pwm = {
        .init_f = MX_TIM2_Init,
        .htim = &htim2,
        .channel = TIM_CHANNEL_1,
    },
};

static motor_t right_motor = {
    .black_pwm = {
        .init_f = MX_TIM17_Init,
        .htim = &htim17,
        .channel = TIM_CHANNEL_1,
    },

    // MX_TIM1_Init is already called on the left_motor
    // It should only be called once
    .red_pwm = {
        .init_f = NULL,
        .htim = &htim1,
        .channel = TIM_CHANNEL_2,
    },
};

void motors_init() {
    motor_init(&left_motor);
    motor_init(&right_motor);
}

void motors_drive(int16_t left, int16_t right) {
    left = constrain(left, -99, 99);
    right = constrain(right, -99, 99);

    // deadzone
    if (abs(left) < 10) {
        left = 0;
    }

    if (abs(right) < 10) {
        right = 0;
    }

    left = map(left, -100, 100, -1000, 1000);
    right = map(right, -100, 100, -1000, 1000);

    motor_drive(&left_motor, left);
    motor_drive(&right_motor, right);
}
