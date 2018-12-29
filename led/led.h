#ifndef LED_H
#define LED_H

#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef SOFTPWM_LED_FREQ
#define SOFTPWM_LED_FREQ 128
#endif

// #define SOFTPWM_LED_TIMER_TOP F_CPU / (256 * SOFTPWM_LED_FREQ)
#define SOFTPWM_LED_TIMER_TOP 0xFF

#define LED_COUNT 1

#define LED_BIT(i) (1U<<(i))

#define LED_BIT_SET(x, i) ((x) |= LED_BIT(i))
#define LED_BIT_CLEAR(x, i) ((x) &= ~LED_BIT(i))

enum {
    SOFTPWM_STATE_UNINIT = 0,
    SOFTPWM_STATE_DISABLED,
    SOFTPWM_STATE_ENABLED
};

void softpwm_init();
void softpwm_enable();
void softpwm_disable();

void softpwm_led_init();
void softpwm_led_on();
void softpwm_led_off();

void softpwm_led_enable_all();
void softpwm_led_disable_all();
void softpwm_led_set_all(uint8_t value);

#endif
