#include "gpio.h"
#include "leds.h"

void led1_on(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
}

void led1_off(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
}

void led1_toggle(void) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
}

void led2_on(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
}

void led2_off(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
}

void led2_toggle(void) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
}

void led3_on(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
}

void led3_off(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
}

void led3_toggle(void) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
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

void led_gauge(uint32_t level) {
    if (level == 0) {
        led1_off();
        led2_off();
        led3_off();
        led4_off();
    } else if (level == 1) {
        led1_on();
        led2_off();
        led3_off();
        led4_off();
    } else if (level == 2) {
        led1_on();
        led2_on();
        led3_off();
        led4_off();
    } else if (level == 3) {
        led1_on();
        led2_on();
        led3_on();
        led4_off();
    } else if (level == 4) {
        led1_on();
        led2_on();
        led3_on();
        led4_on();
    }
}

void led_n(uint8_t n) {
    n++;

    if (n == 1) {
        led1_on();
        led2_off();
        led3_off();
    }

    if (n == 2) {
        led1_off();
        led2_on();
        led3_off();
    }

    if (n == 3) {
        led1_off();
        led2_off();
        led3_on();
    }

    if (n == 4) {
        led1_on();
        led2_off();
        led3_on();
    }

    if (n == 5) {
        led1_off();
        led2_on();
        led3_on();
    }

    if (n == 6) {
        led1_on();
        led2_on();
        led3_on();
    }

    if (n >= 7) {
        led1_off();
        led2_off();
        led3_off();
    }
}
