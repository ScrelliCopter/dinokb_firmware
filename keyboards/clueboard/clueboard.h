#ifndef CLUEBOARD_H
#define CLUEBOARD_H

#include <stdint.h>

enum
{
	CLUE_LED_ESCAPE,
	CLUE_LED_INSERT,
	CLUE_LED_ARROWS
};

typedef uint8_t clue_led_state;

#define CLUE_LED_MASK(ID) (1 << (ID))

void clue_led_set(clue_led_state state);

#endif//CLUEBOARD_H
