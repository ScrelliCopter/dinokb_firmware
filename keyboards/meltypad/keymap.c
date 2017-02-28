#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"

// Numpad shizzles, standard 17 key layout.
#define KEYMAP( \
    K00, K01, K02, K03, \
    K04, K05, K06, K07, \
    K08, K09, K0A,      \
    K0C, K0D, K0E,      \
    K10,      K12, K13  \
) { \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03 }, \
    { KC_##K04, KC_##K05, KC_##K06, KC_##K07 }, \
    { KC_##K08, KC_##K09, KC_##K0A, KC_NO    }, \
    { KC_##K0C, KC_##K0D, KC_##K0E, KC_NO    }, \
    { KC_##K10, KC_NO   , KC_##K12, KC_##K13 }  \
}

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{
	// 0 - Base layer.
	KEYMAP ( \
		FN0,	PSLS,	PAST,	PMNS,	\
		P7,		P8,		P9,		PPLS,	\
		P4,		P5,		P6,		/**/	\
		P1,		P2,		P3,		/**/	\
		P0,		/**/	PDOT,	PENT ),
	// 1 - 
	KEYMAP ( \
		TRNS,	ESC,	TAB,	BSPC,	\
		BTLD,	NO,		NO,		NO,		\
		NO,		NO,		NO,		/**/	\
		NO,		NO,		NO,		/**/	\
		NO,		/**/	NO,		NO ),
};

const action_t PROGMEM fn_actions[] =
{
	[0] = ACTION_LAYER_TAP_KEY(1, KC_NLCK)
};

// Translates key to keycode.
uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
    return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
}

// Translates Fn keycode to action.
action_t keymap_fn_to_action(uint8_t keycode)
{
    return (action_t){ .code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]) };
}
