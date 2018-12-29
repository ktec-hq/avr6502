#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>

#include "mos6502_controller.h"
#include "host_functions.h"
#include "led.h"

#define LED_ROWS 1
#define LED_COLS 2
#define F_CPU 16000000

uint8_t ram[BLANK1_SEGMENT - RAM_SEGMENT];
uint8_t stack[RAM_SEGMENT - STACK_SEGMENT];

enum LED_ELEMENT {
    STATUS = 0,    // Current LED status
    R,             // Red
    G,             // Green
    B,             // Blue
    HL,            // Hue lower 8 bits
    HI,            // Hue higher 8 bits
    S,             // Saturation
    V              // Vue
};

uint8_t text_read_handler(uint16_t address) {
    return eeprom_read_byte((uint8_t*)address);
}

void text_write_handler(uint16_t address, uint8_t value) {
    exit(1);
}

uint8_t host_functions_read_handler(uint16_t address) {
    switch(address) {
        case DELAY_DATA_CTRL_ADDR:
            return get_delay_data_ctrl();
        case DELAY_DATA_LSB_ADDR:
            return get_delay_data_lsb();
        case DELAY_DATA_MSB_ADDR:
            return get_delay_data_msb();
        default:
            return 0x00;
    }
}

void host_functions_write_handler(uint16_t address, uint8_t value) {
    switch(address) {
        case DELAY_DATA_CTRL_ADDR:
            set_delay_data_ctrl(value);
            break;
        case DELAY_DATA_LSB_ADDR:
            set_delay_data_lsb(value);
            break;
        case DELAY_DATA_MSB_ADDR:
            set_delay_data_msb(value);
            break;
        default:
            break;
    }
}

uint8_t key_read_handler(uint16_t address) {
    // TODO: Unimplemented
    return 0x00;
}

void key_write_handler(uint16_t address, uint8_t value) {
    // TODO: Unimplemented
}

uint8_t led_read_manipulator(uint16_t status_address, uint8_t element) {
    //TODO: Unimplemented
    return 0x00;
}

uint8_t led_read_handler(uint16_t address) {
    uint16_t status_address = address / 8;
    uint8_t element = address % 8;

    return led_read_manipulator(status_address, element);
}

void led_write_manipulator(uint16_t status_address, uint8_t element, uint8_t value) {
    switch(element) {
        case STATUS:
            if(value == 1) {
                softpwm_led_enable_all();
            } else if(value == 0) {
                softpwm_led_disable_all();
            }
            break;
        case R:
            softpwm_led_set_all(value);
            break;
    }
}

void led_write_handler(uint16_t address, uint8_t value) {
    uint16_t status_address = address / 8;
    uint8_t element = address % 8;

    led_write_manipulator(status_address, element, value);
}

uint8_t blank1_read_handler(uint16_t address) {
    exit(1);
}

void blank1_write_handler(uint16_t address, uint8_t value) {
    exit(1);
}

uint8_t ram_read_handler(uint16_t address) {
    return ram[address];
}

void ram_write_handler(uint16_t address, uint8_t value) {
    ram[address] = value;
}

uint8_t stack_read_handler(uint16_t address) {
    return stack[address];
}

void stack_write_handler(uint16_t address, uint8_t value) {
    stack[address] = value;
}

uint8_t reserved_read_handler(uint16_t address) {
    exit(1);
}

void reserved_write_handler(uint16_t address, uint8_t value) {
    exit(1);
}

void init() {
    softpwm_init();
    softpwm_enable();
    delay_init();

    sei();
}

int main() {
    init();

    start_up();
}
