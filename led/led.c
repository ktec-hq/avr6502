#include "led.h"

static uint8_t softpwm_state = SOFTPWM_STATE_UNINIT;
uint8_t softpwm_led_state = 0;
static uint8_t softpwm_led_ocr[LED_COUNT] = { 0 };
static uint8_t softpwm_led_ocr_buff[LED_COUNT] = { 0 };

void softpwm_led_init() {
    DDRE  |=  (1 << PE6 | 1 << PE6);
}

void softpwm_led_on() {
    PORTE |=  (1 << PE6 | 1 << PE6);
}

void softpwm_led_off() {
    PORTE &= ~(1 << PE6 | 1<<PE6);
}

void softpwm_init() {
    /* Timer1 setup */
    /* CTC mode */
    TCCR1B |= (1 << WGM12);
    /* Clock selelct: clk/8 */
    TCCR1B |= (1 << CS10);
    /* Set TOP value */
    uint8_t sreg = SREG;
    cli();
    OCR1AH = (SOFTPWM_LED_TIMER_TOP >> 8) & 0xff;
    OCR1AL = SOFTPWM_LED_TIMER_TOP & 0xff;
    SREG = sreg;

    softpwm_led_init();
    softpwm_state = SOFTPWM_STATE_DISABLED;
}

void softpwm_enable() {
    if (softpwm_state == SOFTPWM_STATE_UNINIT) return;

    /* Enable Compare Match Interrupt */
    if (OCR1A) {
        TIMSK1 |= (1 << OCIE1A);
        softpwm_state = SOFTPWM_STATE_ENABLED;
    }
}

void softpwm_disable() {
    if (softpwm_state == SOFTPWM_STATE_UNINIT) return;

    /* Disable Compare Match Interrupt */
    if (OCR1A) {
        TIMSK1 &= ~(1<<OCIE1A);
        softpwm_state = SOFTPWM_STATE_DISABLED;
        for (uint8_t i = 0; i < LED_COUNT; i++) {
            softpwm_led_off();
        }
    }
}

void softpwm_led_disable_all() {
    softpwm_led_state = 0;
    if (softpwm_state != SOFTPWM_STATE_UNINIT) {
        for (uint8_t i = 0; i < LED_COUNT; i++) {
            softpwm_led_off(i);
        }
    }
}

void softpwm_led_enable_all() {
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        LED_BIT_SET(softpwm_led_state, i);
    }
}

void softpwm_led_set_all(uint8_t val) {
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        softpwm_led_ocr_buff[i] = val;
    }
}

ISR(TIMER1_COMPA_vect) {
    static uint8_t pwm = 0;
    pwm++;
    for (uint8_t i = 0; i < LED_COUNT; i++) {
        if (softpwm_led_state & LED_BIT(i)) {
            /* LED on */
            if (pwm == 0) {
                if (softpwm_led_ocr[i]) softpwm_led_on();
                softpwm_led_ocr[i] = softpwm_led_ocr_buff[i];
            }
            /* LED off */
            if (pwm == softpwm_led_ocr[i]) {
                softpwm_led_off();
            }
        }
    }
}
