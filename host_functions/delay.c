#include "host_functions.h"

uint8_t DELAY_DATA_CTRL = 0x00;
uint8_t DELAY_DATA_LSB = 0x00;
uint8_t DELAY_DATA_MSB = 0x00;
uint8_t is_delay_initialized = 0x00;

volatile static uint16_t delay_time = 0x00;
volatile static uint16_t counter = 0x00;

void delay_init() {
    // Enable timer 0
    TCCR0A = (1 << WGM01);
    TCCR0B = (1 << CS01) | (1 << CS00); // 64 prescaler


    uint8_t sreg = SREG;
    cli();
    OCR0A = 125; // 1 ms
    is_delay_initialized = 0x01;
    SREG = sreg;
}

void delay_enable() {
    if(!is_delay_initialized)
        return;

    // set delay time
    delay_time = (DELAY_DATA_MSB << 8) + DELAY_DATA_LSB;
    // reset counter
    counter = 0x00;

    if(OCR0A) {
        // enable interrupt
        TIMSK0 |= (1 << OCIE0A);
        is_paused = 0x01;
    }

}

void delay_disable() {
    if(!is_delay_initialized)
        return;

    if(OCR0A) {
        TIMSK0 &= ~(1 << OCIE0A);
    }

    // reset counter
    is_paused = 0x00;
}

ISR(TIMER0_COMPA_vect) {
    counter++;

    if(counter == delay_time) {
        // disable delay when count hit delay_time
        DELAY_DATA_CTRL = 0;

        delay_disable();
    }
}

uint8_t get_delay_data_ctrl() {
    return DELAY_DATA_CTRL;
}

void set_delay_data_ctrl(uint8_t value) {
    DELAY_DATA_CTRL = value;

    if(DELAY_DATA_CTRL == 1) {
        // turn off ctrl
        delay_enable();
    }
}

uint8_t get_delay_data_lsb() {
    return DELAY_DATA_LSB;
}

void set_delay_data_lsb(uint8_t value) {
    DELAY_DATA_LSB = value;
}

uint8_t get_delay_data_msb() {
    return DELAY_DATA_MSB;
}

void set_delay_data_msb(uint8_t value) {
    DELAY_DATA_MSB = value;
}

