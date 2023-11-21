#include "clueboard.h"
#include "led.h"
#include <stdint.h>
#include <avr/io.h>

static void led_init_ports(void);

void hook_early_init(void)
{
	// JTAG disable for PORT F
	// write JTD bit twice within four cycles
	MCUCR |= 1 << JTD;
	MCUCR |= 1 << JTD;

	led_init_ports();
}


#define USB_LED_CAPS_LOCK_ON  (PORTB |=  (1 << 4))
#define USB_LED_CAPS_LOCK_OFF (PORTB &= ~(1 << 4))

#define CAPSLOCK_BIT CLUE_LED_MASK(USB_LED_CAPS_LOCK)

void led_set(uint8_t state)
{
	state & CAPSLOCK_BIT ? USB_LED_CAPS_LOCK_ON : USB_LED_CAPS_LOCK_OFF;
}

#define ESCAPE_BIT CLUE_LED_MASK(CLUE_LED_ESCAPE)
#define INSERT_BIT CLUE_LED_MASK(CLUE_LED_INSERT)
#define ARROWS_BIT CLUE_LED_MASK(CLUE_LED_ARROWS)

#define CLUE_LED_ESCAPE_ON  (PORTD |=  (1 << 6))
#define CLUE_LED_ESCAPE_OFF (PORTD &= ~(1 << 6))
#define CLUE_LED_INSERT_ON  (PORTB |=  (1 << 7))
#define CLUE_LED_INSERT_OFF (PORTB &= ~(1 << 7))
#define CLUE_LED_ARROWS_ON  (PORTD |=  (1 << 4))
#define CLUE_LED_ARROWS_OFF (PORTD &= ~(1 << 4))

void clue_led_set(clue_led_state state)
{
	state & ESCAPE_BIT ? CLUE_LED_ESCAPE_ON : CLUE_LED_ESCAPE_OFF;
	state & INSERT_BIT ? CLUE_LED_INSERT_ON : CLUE_LED_INSERT_OFF;
	state & ARROWS_BIT ? CLUE_LED_ARROWS_ON : CLUE_LED_ARROWS_OFF;
}

void led_init_ports(void)
{
	// Setup LED pins as outputs
	DDRB |= (1 << 4) | (1 << 7); // Caps lock, Insert
	DDRD |= (1 << 6) | (1 << 4); // Escape, Arrow cluster

	// Set LED pins low
	USB_LED_CAPS_LOCK_OFF;
	CLUE_LED_ESCAPE_OFF;
	CLUE_LED_INSERT_OFF;
	CLUE_LED_ARROWS_OFF;
}


#ifdef BACKLIGHT_ENABLE
__attribute__((weak)) void backlight_set(uint8_t level) {}
#endif
