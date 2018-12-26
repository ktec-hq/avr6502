#include <stdio.h>
#include "mos6502_controller.h"

#define LED_ROWS 1
#define LED_COLS 2

// #define MAPPING_DEBUG
#define LED_DEBUG

uint8_t image[TEXT_SIZE];
uint8_t key[TEXT_SEGMENT - KEY_SEGMENT];
uint8_t led[KEY_SEGMENT - LED_SEGMENT];
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
#ifdef MAPPING_DEBUG
    printf("read text with address: 0x%x\n", address);
#endif

    return image[address];
}

void text_write_handler(uint16_t address, uint8_t value) {
#ifdef MAPPING_DEBUG
    printf("write on text with address: 0x%x and value: 0x%x\n", address, value);
#endif

    exit(1);
}

uint8_t key_read_handler(uint16_t address) {
#ifdef MAPPING_DEBUG
    // TODO: We shouldn't have an actual KEY matrix, this is only for testing
    printf("read led with address: 0x%x\n", address);
#endif

    return key[address];
}

void key_write_handler(uint16_t address, uint8_t value) {
#ifdef MAPPING_DEBUG
    // TODO: We shouldn't have an actual KEY matrix, this is only for testing
    printf("write on led with address: 0x%x and value: 0x%x\n", address, value);
#endif

    key[address] = value;
}

// TODO: Needs reimplementation on Arduino
uint8_t led_read_manipulator(uint16_t status_address, uint8_t element) {
    char* tmp = NULL;

    switch(element) {
        case STATUS:
            tmp = "status";
            break;
        case R:
            tmp = "R";
            break;
        case G:
            tmp = "G";
            break;
        case B:
            tmp = "B";
            break;
        case HL:
            tmp = "HL";
            break;
        case HI:
            tmp = "HI";
            break;
        case S:
            tmp = "S";
            break;
        case V:
            tmp = "V";
            break;
        default:
            tmp = "UNKOWN";
            break;
    }

    uint8_t row = status_address / LED_ROWS;
    uint8_t col = status_address % LED_ROWS;

#ifdef LED_DEBUG
    printf("read led %s on row: %d col: %d\n", tmp, row, col);
#endif

    return led[status_address * 8 + element];
}

uint8_t led_read_handler(uint16_t address) {
    uint16_t status_address = address / 8;
    uint8_t element = address % 8;

    return led_read_manipulator(status_address, element);
}

// TODO: Needs reimplementation on Arduino
void led_write_manipulator(uint16_t status_address, uint8_t element, uint8_t value) {
    char* tmp = NULL;

    switch(element) {
        case STATUS:
            tmp = "status";
            break;
        case R:
            tmp = "R";
            break;
        case G:
            tmp = "G";
            break;
        case B:
            tmp = "B";
            break;
        case HL:
            tmp = "HL";
            break;
        case HI:
            tmp = "HI";
            break;
        case S:
            tmp = "S";
            break;
        case V:
            tmp = "V";
            break;
        default:
            tmp = "UNKOWN";
            break;
    }

    uint8_t row = status_address / LED_ROWS;
    uint8_t col = status_address % LED_ROWS;

#ifdef LED_DEBUG
    printf("write led %s on row: %d col: %d with value: %x\n", tmp, row, col, value);
#endif

    led[status_address * 8 + element] = value;
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

void load_code(char* filepath) {
    FILE* fileptr = fopen(filepath, "rb");
    if(fileptr == NULL) {
        fprintf(stderr, "Fail to load code\n");

        exit(1);
    }

    size_t n = fread(image, sizeof(uint8_t), 0x2000, fileptr);
    printf("0x%lx bytes has been loaded\n", n);

    fclose(fileptr);
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Please provide image path\n");

        exit(1);
    }
    char* filepath = argv[1];
    load_code(filepath);

    start_up();
}
