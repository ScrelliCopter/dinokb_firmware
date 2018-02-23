#include <avr/io.h>
#include "stdint.h"
#include "led.h"

void led_set(uint8_t usb_led)
{
	DDRB |= (1<<4);
	
	if ( usb_led & ( 1 << USB_LED_CAPS_LOCK ) )
	{
		PORTB |= (1<<4);
	}
	else
	{
		PORTB &= ~(1<<4);
	}
}
