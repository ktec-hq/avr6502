#include <stdio.h>
#include "mos6502_controller.h"

uint8_t image[TEXT_SIZE];
uint8_t key[TEXT_SEGMENT - KEY_SEGMENT];
uint8_t led[KEY_SEGMENT - LED_SEGMENT];
uint8_t ram[BLANK1_SEGMENT - RAM_SEGMENT];
uint8_t stack[RAM_SEGMENT - STACK_SEGMENT];

uint8_t text_read_handler(uint16_t address) {
    printf("read text with address: 0x%x\n", address);

    return image[address];
}

void text_write_handler(uint16_t address, uint8_t value) {
    printf("write on text with address: 0x%x and value: 0x%x\n", address, value);

    exit(1);
}

uint8_t key_read_handler(uint16_t address) {
    // TODO: We shouldn't have an actual KEY matrix, this is only for testing
    printf("read led with address: 0x%x\n", address);

    return key[address];
}

void key_write_handler(uint16_t address, uint8_t value) {
    // TODO: We shouldn't have an actual KEY matrix, this is only for testing
    printf("write on led with address: 0x%x and value: 0x%x\n", address, value);

    key[address] = value;
}

uint8_t led_read_handler(uint16_t address) {
    // TODO: We shouldn't have an actual LED matrix, this is only for testing
    printf("read led with address: 0x%x\n", address);

    return led[address];
}

void led_write_handler(uint16_t address, uint8_t value) {
    // TODO: We shouldn't have an actual LED matrix, this is only for testing
    printf("write on led with address: 0x%x and value: 0x%x\n", address, value);

    led[address] = value;
}

uint8_t blank1_read_handler(uint16_t address) {
    printf("read blank1 with address: 0x%x\n", address);

    exit(1);
}

void blank1_write_handler(uint16_t address, uint8_t value) {
    printf("write on blank1 with address: 0x%x and value: 0x%x\n", address, value);

    exit(1);
}

uint8_t ram_read_handler(uint16_t address) {
    printf("read ram with address: 0x%x\n", address);

    return ram[address];
}

void ram_write_handler(uint16_t address, uint8_t value) {
    printf("write on ram with address: 0x%x and value: 0x%x\n", address, value);

    ram[address] = value;
}

uint8_t stack_read_handler(uint16_t address) {
    printf("read stack with address: 0x%x\n", address);

    return stack[address];
}

void stack_write_handler(uint16_t address, uint8_t value) {
    printf("write on stack with address: 0x%x and value: 0x%x\n", address, value);

    stack[address] = value;
}

uint8_t reserved_read_handler(uint16_t address) {
    printf("read reserved with address: 0x%x\n", address);

    exit(1);
}

void reserved_write_handler(uint16_t address, uint8_t value) {
    printf("write on reserved with address: 0x%x and value: 0x%x\n", address, value);

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
