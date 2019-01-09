# avr6502
6502 emulator on ATmega328P

## TODO

1. LED Matrix Support

2. I2C Support

## Note

Program should start at 0x8000, and its size shouldn't exceed 0x2000 bytes.

## Current Memory Mapping

| Segment             | Start Address | Size   |
| --------------------| ------------- | ------ |
| TEXT                | 0x8000        | 0x2000 |
| HOST FUNCTIONS      | 0x5000        | 0x3000 |
| KEY                 | 0x4000        | 0x1000 |
| LED                 | 0x2000        | 0x2000 |
| BLANK1              | 0x800         | 0x1800 |
| RAM                 | 0x200         | 0x600  |
| STACK               | 0x100         | 0x100  |
| RESERVED            | 0x0           | 0x100  |

### LED Segment

each LED has 8 bytes: STATUS R G B HL HI V

Note: Each hue has two bytes with lower 8 bits first.

## Host Functions Segment

This segment contains useful functions for subsystem to use

### Delay Register

0x5000 DELAY_DATA_CTRL
0x5001 DELAY_DATA_LSB
0x5002 DELAY_DATA_MSB

Set DELAY_DATA_CTRL to 1 to pause subsystem
After the pause, host will set DELAY_DATA_CTRL to 0

## Resources

6502 cpu implementation: [fake6502](http://rubbermallet.org/fake6502.c)

Online assembler: [ASM80](https://www.asm80.com)
