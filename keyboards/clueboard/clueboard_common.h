#ifndef CLUEBOARD_COMMON_H
#define CLUEBOARD_COMMON_H

#include <stdint.h>

enum
{
	CLUE_LED_ESCAPE = 1,
	CLUE_LED_INSERT = 2,
	CLUE_LED_ARROWS = 3
};

typedef uint8_t clue_led_state;

#define CLUE_LED_MASK(ID) (1 << (ID))

void clue_led_set(clue_led_state state);

#endif//CLUEBOARD_COMMON_H
