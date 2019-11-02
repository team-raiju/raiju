#include <stdint.h>

#include "tim.h"
#include "radio.h"
#include "utils.h"

/****************************************************************
 * PPM Handler
 ****************************************************************/

void ppm_exti_callback(ppm_input_t* ppm) {
    if (HAL_GPIO_ReadPin(ppm->gpio_port, ppm->gpio_pin) == GPIO_PIN_SET) {
        ppm->_tmp_count = __HAL_TIM_GET_COUNTER(ppm->timer);
    } else {
        ppm->value = __HAL_TIM_GET_COUNTER(ppm->timer) - ppm->_tmp_count;
        ppm->_fail_count = 0;
    }
}

uint16_t ppm_get_value(ppm_input_t* ppm) {
    return ppm->value;
}

/****************************************************************
 * Radio Adapter
 ****************************************************************/

static ppm_input_t ppms[] = {
    {
        .gpio_port = GPIOA,
        .gpio_pin = GPIO_PIN_2,

        .timer = &htim16,
    },
    {
        .gpio_port = GPIOA,
        .gpio_pin = GPIO_PIN_3,

        .timer = &htim16,
    },
};

void radio_init() {
    MX_TIM16_Init();

    HAL_TIM_Base_Start(&htim16);
}

uint16_t radio_get_channel1() {
    return ppm_get_value(&ppms[0]);
}

uint16_t radio_get_channel2() {
    return ppm_get_value(&ppms[1]);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    for (size_t i = 0; i < len(ppms); i++) {
        if (GPIO_Pin == ppms[i].gpio_pin) {
            ppm_exti_callback(&ppms[i]);
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim) {
    for (size_t i = 0; i < len(ppms); i++) {
        if (htim->Instance == ppms[i].timer->Instance) {
            ppms[i]._fail_count++;

            if (ppms[i]._fail_count > 10) {
                ppms[i].value = 0;
            }
        }
    }
}

/****************************************************************
 * Radio Service
 ****************************************************************/

coordinate_t radio_get_coordinates() {
    coordinate_t coords = {0, 0};

    uint16_t ppm_x = constrain(radio_get_channel1(), 1000, 2000);
    uint16_t ppm_y = constrain(radio_get_channel2(), 1000, 2000);

    coords.x = map(ppm_x, 1000, 2000, -100, 100);
    coords.y = map(ppm_y, 1000, 2000, -100, 100);

    return coords;
}
