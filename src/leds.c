#include "gpio.h"
#include "leds.h"

void led1_on(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
}

void led1_off(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
}

void led1_toggle(void) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
}

void led2_on(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
}

void led2_off(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
}

void led2_toggle(void) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
}

void led3_on(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
}

void led3_off(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
}

void led3_toggle(void) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
}

void led4_on(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
}

void led4_off(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
}

void led4_toggle(void) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);
}
