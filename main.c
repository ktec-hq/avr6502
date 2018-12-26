#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>

#include "mos6502_controller.h"

#define LED_ROWS 1
#define LED_COLS 2

// #define MAPPING_DEBUG
#define LED_DEBUG

// uint8_t image[TEXT_SIZE];
// uint8_t key[TEXT_SEGMENT - KEY_SEGMENT];
// uint8_t led[KEY_SEGMENT - LED_SEGMENT];

const uint8_t PROGMEM image[] = { 0xa9, 0xff, 0x8d, 0x00, 0x20, 0xa9, 0xff, 0x8d, 0x01, 0x20, 0xa9, 0x00, 0x8d, 0x02, 0x20, 0x4c, 0x00, 0x80 };
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
    return pgm_read_byte(&image[address]);
}

void text_write_handler(uint16_t address, uint8_t value) {
    exit(1);
}

uint8_t key_read_handler(uint16_t address) {
    // TODO: Unimplemented
    return 0x00;
}

void key_write_handler(uint16_t address, uint8_t value) {

    // TODO: Unimplemented
}

// TODO: Needs reimplementation on Arduino
uint8_t led_read_manipulator(uint16_t status_address, uint8_t element) {
//    Unimplemented
    return 0x00;
}

uint8_t led_read_handler(uint16_t address) {
    uint16_t status_address = address / 8;
    uint8_t element = address % 8;

    return led_read_manipulator(status_address, element);
}

// TODO: Needs reimplementation on Arduino
void led_write_manipulator(uint16_t status_address, uint8_t element, uint8_t value) {
    uint8_t row = status_address / LED_COLS;
    uint8_t col = status_address % LED_COLS;

#ifdef LED_DEBUG
    if(row == 0x0 && col == 0) {
        PORTB |= (1 << PORTB4);
        _delay_ms(200);
        PORTB &= ~(1 << PORTB4);
        _delay_ms(200);
    }
#endif
}


void led_write_handler(uint16_t address, uint8_t value) {
    uint16_t status_address = address / 8;
    uint8_t element = address % 8;

    led_write_manipulator(status_address, element, value);
}

uint8_t blank1_read_handler(uint16_t address) {
#ifndef MAPPING_DEBUG
    printf("read blank1 with address: 0x%x\n", address);
#endif

    exit(1);
}

void blank1_write_handler(uint16_t address, uint8_t value) {
#ifndef MAPPING_DEBUG
    printf("write on blank1 with address: 0x%x and value: 0x%x\n", address, value);
#endif

    exit(1);
}

uint8_t ram_read_handler(uint16_t address) {
#ifndef MAPPING_DEBUG
    printf("read ram with address: 0x%x\n", address);
#endif

    return ram[address];
}

void ram_write_handler(uint16_t address, uint8_t value) {
#ifndef MAPPING_DEBUG
    printf("write on ram with address: 0x%x and value: 0x%x\n", address, value);
#endif

    ram[address] = value;
}

uint8_t stack_read_handler(uint16_t address) {
#ifndef MAPPING_DEBUG
    printf("read stack with address: 0x%x\n", address);
#endif

    return stack[address];
}

void stack_write_handler(uint16_t address, uint8_t value) {
#ifndef MAPPING_DEBUG
    printf("write on stack with address: 0x%x and value: 0x%x\n", address, value);
#endif

    stack[address] = value;
}

uint8_t reserved_read_handler(uint16_t address) {
#ifndef MAPPING_DEBUG
    printf("read reserved with address: 0x%x\n", address);
#endif

    exit(1);
}

void reserved_write_handler(uint16_t address, uint8_t value) {
#ifndef MAPPING_DEBUG
    printf("write on reserved with address: 0x%x and value: 0x%x\n", address, value);
#endif

    exit(1);
}

int main() {
    DDRB |= (1<<DDB4);

    start_up();
}
