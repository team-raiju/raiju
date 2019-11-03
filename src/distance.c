#include "distance.h"

#include "gpio.h"

/****************************************************************
 * Sensoring Service
 ****************************************************************/

bool distance_is_front_seeing() {
    return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_SET;
}

bool distance_is_left_seeing() {
    return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6) == GPIO_PIN_SET;
}

bool distance_is_right_seeing() {
    return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10) == GPIO_PIN_SET;
}
