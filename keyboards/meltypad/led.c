#include <avr/io.h>
#include "stdint.h"
#include "led.h"

void led_set ( uint8_t usb_led )
{
	if ( usb_led & ( 1 << USB_LED_NUM_LOCK ) )
	{
		DDRD	|=  ( 1 << 5 );
		PORTD	&= ~( 1 << 5 );
	}
	else
	{
		DDRD	&= ~( 1 << 5 );
		PORTD	&= ~( 1 << 5 );
	}
}
