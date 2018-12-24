#ifndef MOS6502_EMU_H
#define MOS6502_EMU_H

#include <stdio.h>
#include <stdint.h>

// I/O needs to be implemented outside emulator
extern uint8_t read6502(uint16_t address);
extern void write6502(uint16_t address, uint8_t value);

// CPU controller
void reset6502();
void exec6502(uint32_t tickcount);
void step6502();
void hookexternal(void *funcptr);

// currently not used
void nmi6502();
void irq6502();

#endif
