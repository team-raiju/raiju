#include "buttons.h"
#include "gpio.h"
#include "mcu.h"

bool button_is_b1_pushed() {
    if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4) == GPIO_PIN_RESET) {
        mcu_sleep(5);

        if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4) == GPIO_PIN_RESET) {
            return true;
        }
    }

    return false;
}

bool button_is_b2_pushed() {
    if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == GPIO_PIN_RESET) {
        mcu_sleep(5);

        if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == GPIO_PIN_RESET) {
            return true;
        }
    }

    return false;
}

bool button_is_b3_pushed() {
    if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == GPIO_PIN_RESET) {
        mcu_sleep(5);

        if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1) == GPIO_PIN_RESET) {
            return true;
        }
    }

    return false;
}
