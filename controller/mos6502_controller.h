#ifndef MOS6502_CONTROLLER_H
#define MOS6502_CONTROLLER_H

#define RESERVED_SEGMENT        0x0
#define STACK_SEGMENT           0x100
#define RAM_SEGMENT             0x200
#define BLANK1_SEGMENT          0x800
#define LED_SEGMENT             0x2000
#define KEY_SEGMENT             0x4000
#define HOST_FUNCTIONS_SEGMENT  0x5000
#define TEXT_SEGMENT            0x8000

#define TEXT_SIZE               0x2000

#include <stdint.h>
#include <stdlib.h>
#include "mos6502.h"

extern uint8_t reserved_read_handler(uint16_t address);
extern void    reserved_write_handler(uint16_t address, uint8_t value);

extern uint8_t stack_read_handler(uint16_t address);
extern void    stack_write_handler(uint16_t address, uint8_t value);

extern uint8_t ram_read_handler(uint16_t address);
extern void    ram_write_handler(uint16_t address, uint8_t value);

extern uint8_t blank1_read_handler(uint16_t address);
extern void    blank1_write_handler(uint16_t address, uint8_t value);

extern uint8_t led_read_handler(uint16_t address);
extern void    led_write_handler(uint16_t address, uint8_t value);

extern uint8_t key_read_handler(uint16_t address);
extern void    key_write_handler(uint16_t address, uint8_t value);

extern uint8_t host_functions_read_handler(uint16_t address);
extern void    host_functions_write_handler(uint16_t address, uint8_t value);

extern uint8_t text_read_handler(uint16_t address);
extern void    text_write_handler(uint16_t address, uint8_t value);

void start_up();

#endif
