#include <stdlib.h>
#include "mos6502emu.h"

#define MEMORY_SIZE 0x20000

// emulator memory
uint8_t* memory = NULL;

// Implemnets input for emulator
uint8_t read6502(uint16_t address) {
    printf("CPU wants to read on %x\n", address);

    return memory[address];
}

// Implemnets output for emulator
void write6502(uint16_t address, uint8_t value) {
    printf("CPU wants to write on %x with value: %x\n", address, value);

    memory[address] = value;
}

// Load bin image into memory
void load_image(char* filepath) {
    FILE* fileptr = fopen(filepath, "rb");

    // handle invalid file
    if(fileptr == NULL) {
        fprintf(stderr, "Fail to open file: %s\n", filepath);

        exit(1);
    }

    size_t n = fread(memory, sizeof(uint8_t), MEMORY_SIZE, fileptr);

    printf("%lu bytes has been read into memory\n", n);
}

void start_up(char* filepath) {
    // alloc memory
    memory = malloc(MEMORY_SIZE * sizeof(uint8_t));

    // load image into memory
    load_image(filepath);
    // reset 6502
    reset6502();
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Please provide image path\n");

        exit(1);
    }
    char* image_path = argv[1];

    start_up(image_path);

    // run loaded image
    while(1) {
        step6502();
    }
}
