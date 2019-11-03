/**
 * @file debug.h
 *
 * @brief Single timer implementation of a multi channel PPM receiver
 *
 * @author Daniel Nery <danielnso97@gmail.com>
 */

#if !defined(__RADIO_H__)
#define __RADIO_H__

#include "gpio.h"
#include "tim.h"

#define PPM_MIN_VALUE_MS 1000
#define PPM_STOPPED_VALUE_MS 1500
#define PPM_MAX_VALUE_MS 2000

#define MIN_COORDINATE -100
#define MAX_COORDINATE 100

#define RADIO_FAILSAFE_MAX_TIMER_OVERFLOW 10

/****************************************************************
 * External Interrupt Handler
 ****************************************************************/

/****************************************************************
 * PPM Adapter
 ****************************************************************/

typedef struct ppm_input {
    GPIO_TypeDef*      gpio_port;
    uint16_t           gpio_pin;

    TIM_HandleTypeDef* timer;

    uint16_t           value;
    uint16_t           _tmp_count;
    uint32_t           _fail_count;
} ppm_input_t;

void ppm_init(ppm_input_t* ppm);

void ppm_exti_callback(ppm_input_t* ppm);

uint16_t ppm_get_value(ppm_input_t* ppm);

uint16_t radio_get_channel1();

uint16_t radio_get_channel2();

/****************************************************************
 * Radio Service
 ****************************************************************/

typedef struct coordinate {
    int8_t x;
    int8_t y;
} coordinate_t;

void radio_init();

coordinate_t radio_get_coordinates();

#endif // __RADIO_H__
