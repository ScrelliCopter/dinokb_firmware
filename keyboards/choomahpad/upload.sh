#!/bin/bash
avrdude -p atmega32u4 -c avr109 -P COM3 -U flash:w:choomahpad.hex
