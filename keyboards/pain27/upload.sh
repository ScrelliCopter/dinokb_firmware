#!/bin/sh

HEX="pain27_${KEYMAP:=vanilla}.hex"

AVRDUDE=avrdude
DEVICE=atmega32u4
PROGRAMMER=avr109

if [ -z "$PORT" ]; then
	if [ "$(uname)" = "Darwin" ]; then
		PORT="$(find /dev -maxdepth 1 -type c -name "tty.usbmodem*" | head -n1)"
		[ ! -z "$PORT" ] && echo "Using port \"$PORT\""
	fi
	# Windows 'MINGW64_NT-10.0-blah' would look something like this: PORT=COM8
fi

if [ -z "$PORT" ]; then
	echo "Error: no port specified"
	exit 1
fi

make KEYMAP="$KEYMAP" && $AVRDUDE -p "$DEVICE" -c "$PROGRAMMER" -P "$PORT" -U flash:w:"$HEX"
