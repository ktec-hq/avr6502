#include "mos6502_controller.h"

// Implements input for emulator
uint8_t read6502(uint16_t address) {
    if(address >= TEXT_SEGMENT) {
        return text_read_handler(address - TEXT_SEGMENT);
    } else if(address >= KEY_SEGMENT) {
        return key_read_handler(address - KEY_SEGMENT);
    } else if(address >= LED_SEGMENT) {
        return led_read_handler(address - LED_SEGMENT);
    } else if(address >= BLANK1_SEGMENT) {
        return blank1_read_handler(address - BLANK1_SEGMENT);
    } else if(address >= RAM_SEGMENT) {
        return ram_read_handler(address - RAM_SEGMENT);
    } else if(address >= STACK_SEGMENT) {
        return stack_read_handler(address - STACK_SEGMENT);
    } else if(address >= RESERVED_SEGMENT) {
        return reserved_read_handler(address - RESERVED_SEGMENT);
    }

    fprintf(stderr, "Invalid read on address: 0x%x\n", address);
    exit(1);
}

// Implemnets output for emulator
void write6502(uint16_t address, uint8_t value) {
    if(address >= TEXT_SEGMENT) {
        return text_write_handler(address - TEXT_SEGMENT, value);
    } else if(address >= KEY_SEGMENT) {
        return key_write_handler(address - KEY_SEGMENT, value);
    } else if(address >= LED_SEGMENT) {
        return led_write_handler(address - LED_SEGMENT, value);
    } else if(address >= BLANK1_SEGMENT) {
        return blank1_write_handler(address - BLANK1_SEGMENT, value);
    } else if(address >= RAM_SEGMENT) {
        return ram_write_handler(address - RAM_SEGMENT, value);
    } else if(address >= STACK_SEGMENT) {
        return stack_write_handler(address - STACK_SEGMENT, value);
    } else if(address >= RESERVED_SEGMENT) {
        return reserved_write_handler(address - RESERVED_SEGMENT, value);
    }

    fprintf(stderr, "Invalid write on address: 0x%x with value: 0x%x\n", address, value);
    exit(1);
}

void start_up() {
    // reset 6502
    reset6502();

    // run loaded image
    while(1) {
        step6502();
    }
}

