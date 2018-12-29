#ifndef HOST_FUNCTIONS_H
#define HOST_FUNCTIONS_H

#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "mos6502_controller.h"

// Host functions segment
// Delay control segment
#define DELAY_DATA_CTRL_ADDR 0x0000
uint8_t get_delay_data_ctrl();
void set_delay_data_ctrl(uint8_t value);

#define DELAY_DATA_LSB_ADDR 0x0001
uint8_t get_delay_data_lsb();
void set_delay_data_lsb(uint8_t value);

#define DELAY_DATA_MSB_ADDR 0x0002
uint8_t get_delay_data_msb();
void set_delay_data_msb(uint8_t value);

void delay_init();

#endif
