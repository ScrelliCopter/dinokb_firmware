#include "clueboard.h"
#include "led.h"
#include <stdint.h>
#include <avr/io.h>

static void led_init_ports(void);

void hook_early_init(void)
{
	// JTAG disable for PORT F
	// write JTD bit twice within four cycles
	MCUCR |= _BV(JTD);
	MCUCR |= _BV(JTD);

	led_init_ports();
}


#define USB_LED_CAPS_LOCK_ON  (PORTB |=  _BV(4))
#define USB_LED_CAPS_LOCK_OFF (PORTB &= ~_BV(4))

void led_set(uint8_t state)
{
	state & _BV(USB_LED_CAPS_LOCK) ? USB_LED_CAPS_LOCK_ON : USB_LED_CAPS_LOCK_OFF;
}

#define CLUE_LED_ESCAPE_ON  (PORTD |=  _BV(6))
#define CLUE_LED_ESCAPE_OFF (PORTD &= ~_BV(6))
#define CLUE_LED_INSERT_ON  (PORTB |=  _BV(7))
#define CLUE_LED_INSERT_OFF (PORTB &= ~_BV(7))
#define CLUE_LED_ARROWS_ON  (PORTD |=  _BV(4))
#define CLUE_LED_ARROWS_OFF (PORTD &= ~_BV(4))

void clue_led_set(clue_led_state state)
{
	state & _BV(CLUE_LED_ESCAPE) ? CLUE_LED_ESCAPE_ON : CLUE_LED_ESCAPE_OFF;
	state & _BV(CLUE_LED_INSERT) ? CLUE_LED_INSERT_ON : CLUE_LED_INSERT_OFF;
	state & _BV(CLUE_LED_ARROWS) ? CLUE_LED_ARROWS_ON : CLUE_LED_ARROWS_OFF;
}

void led_init_ports(void)
{
	// Setup LED pins as outputs
	DDRB |= _BV(4) | _BV(7); // Caps lock, Insert
	DDRD |= _BV(6) | _BV(4); // Escape, Arrow cluster

	// Set LED pins low
	USB_LED_CAPS_LOCK_OFF;
	CLUE_LED_ESCAPE_OFF;
	CLUE_LED_INSERT_OFF;
	CLUE_LED_ARROWS_OFF;
}


#ifdef BACKLIGHT_ENABLE
__attribute__((weak)) void backlight_set(uint8_t level) {}
#endif
