#include "distance.h"

#include "gpio.h"

/****************************************************************
 * Sensoring Service
 ****************************************************************/

bool distance_is_front_seeing() {
    return HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10);
}

bool distance_is_left_seeing() {
    return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6);
}

bool distance_is_right_seeing() {
    return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10);
}
