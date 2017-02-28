#!/bin/bash
avrdude -p atmega32u4 -c avr109 -P COM8 -U flash:w:meltypad.hex
