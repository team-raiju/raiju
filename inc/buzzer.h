#if !defined(__BUZZER_H__)
#define __BUZZER_H__

#include <stdint.h>

void buzzer_init();

void buzzer_on();

void buzzer_off();

void buzzer_beep(uint32_t ms);

#endif // __BUZZER_H__
