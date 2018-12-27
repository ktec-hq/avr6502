#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>

#include "mos6502_controller.h"

#define LED_ROWS 1
#define LED_COLS 2

// #define MAPPING_DEBUG
#define LED_DEBUG

// Host functions segment
// Delay control addresses
#define DELAY_DATA_CTRL_ADDR 0x0000
#define DELAY_DATA_LSB_ADDR 0x0001
#define DELAY_DATA_MSB_ADDR 0x0002
// Delay control registers
uint8_t DELAY_DATA_CTRL = 0x00;
uint8_t DELAY_DATA_LSB = 0x00;
uint8_t DELAY_DATA_MSB = 0x00;

const uint8_t PROGMEM image[] = {
    0x20, 0x0f, 0x80, 0x20, 0x15, 0x80, 0x20, 0x25, 0x80, 0x20, 0x15, 0x80, 0x4c, 0x00, 0x80, 0xa9,
    0xff, 0x8d, 0x00, 0x20, 0x60, 0xa9, 0xc8, 0x8d, 0x01, 0x50, 0xa9, 0x00, 0x8d, 0x02, 0x50, 0xa9,
    0x01, 0x8d, 0x00, 0x50, 0x60, 0xa9, 0x00, 0x8d, 0x00, 0x20, 0x60,
};

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

static inline void delay_ms(uint16_t count) {
  while(count--) {
    _delay_ms(1);
  }
}

uint8_t text_read_handler(uint16_t address) {
    return pgm_read_byte(&image[address]);
}

void text_write_handler(uint16_t address, uint8_t value) {
    exit(1);
}

uint8_t host_functions_read_handler(uint16_t address) {
    switch(address) {
        case DELAY_DATA_CTRL_ADDR:
            return DELAY_DATA_CTRL;
        case DELAY_DATA_LSB_ADDR:
            return DELAY_DATA_LSB;
        case DELAY_DATA_MSB_ADDR:
            return DELAY_DATA_MSB;
        default:
            return 0x00;
    }
}

void host_functions_write_handler(uint16_t address, uint8_t value) {
    switch(address) {
        case DELAY_DATA_CTRL_ADDR:
            DELAY_DATA_CTRL = value;
            break;
        case DELAY_DATA_LSB_ADDR:
            DELAY_DATA_LSB = value;
            break;
        case DELAY_DATA_MSB_ADDR:
            DELAY_DATA_MSB = value;
            break;
        default:
            return;
    }

    if(DELAY_DATA_CTRL == 1) {
        delay_ms((DELAY_DATA_MSB << 8) + DELAY_DATA_LSB);
        // turn off ctrl
        DELAY_DATA_CTRL = 0;
    }
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
    // uint8_t row = status_address / LED_COLS;
    // uint8_t col = status_address % LED_COLS;

    if(value == 0xFF) {
        PORTE |= (1 << PORTE6);
    } else if(value == 0x00) {
        PORTE &= ~(1 << PORTE6);
    }
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
    DDRE |= (1 << DDE6);

    start_up();
}
