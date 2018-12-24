# avr6502
6502 emulator on ATmega328P

## Note

Program should start at 0x8000, and its size shouldn't exceed 0x2000 bytes.

## Current Memory Mapping

| Segment  | Start Address | Size   |
| -------- | ------------- | ------ |
| TEXT     | 0x8000        | 0x2000 |
| BLANK1   | 0x800         | 0x7800 |
| RAM      | 0x200         | 0x600  |
| STACK    | 0x100         | 0x100  |
| RESERVED | 0x0           | 0x100  |

## Resources

6502 cpu implementation: [fake6502](http://rubbermallet.org/fake6502.c)

Online assembler: [ASM80](https://www.asm80.com)
