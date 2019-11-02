/**
 * @file motors.h
 *
 * @brief Functions used to control motors
 */

#if !defined(__MOTORS_H__)
#define __MOTORS_H__

#include <stdint.h>

#include "tim.h"

/***********************************************************************
 * PWM Adapter
 ***********************************************************************/

typedef void (* timer_init_function_t)(void);

typedef struct pwm {
    TIM_HandleTypeDef*    htim;
    uint32_t              channel;
    timer_init_function_t init_f;
} pwm_t;

void pwm_init(pwm_t* pwm);

void pwm_set(pwm_t* pwm, uint32_t value);

/***********************************************************************
 * Motor Adapter
 ***********************************************************************/

typedef struct motor {
    pwm_t red_pwm;
    pwm_t black_pwm;
} motor_t;

void motor_init(motor_t* motor);

void motor_drive(motor_t* motor, int32_t speed);

/***********************************************************************
 * Driving Service
 ***********************************************************************/

void motors_init();

void motors_drive(int16_t left, int16_t right);

#endif // __MOTORS_H__
