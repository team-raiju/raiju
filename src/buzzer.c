#include "buzzer.h"

#include "mcu.h"
#include "tim.h"

// The buzzer is sharing motors TIM2, won't initialize it here
void buzzer_init() {
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);
}

void buzzer_on() {
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 500);
}

void buzzer_off() {
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);
}

void buzzer_beep(uint32_t ms) {
    buzzer_on();
    mcu_sleep(ms);
    buzzer_off();
}
