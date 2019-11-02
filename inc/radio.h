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
    uint16_t           _fail_count;
} ppm_input_t;

void ppm_init(ppm_input_t* ppm);

void ppm_exti_callback(ppm_input_t* ppm);

uint16_t ppm_get_value(ppm_input_t* ppm);

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
