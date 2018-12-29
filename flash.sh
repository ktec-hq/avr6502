#!/bin/bash
if [ -z "$1" ]
then
  make && dfu-programmer atmega32u4 erase && dfu-programmer atmega32u4 flash avr6502.hex && make clean
else
  make && dfu-programmer atmega32u4 erase && dfu-programmer atmega32u4 flash --eeprom $1 && dfu-programmer atmega32u4 flash avr6502.hex && make clean
fi

