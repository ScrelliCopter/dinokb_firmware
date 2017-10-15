#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{
	// 0: qwerty
	KEYMAP (
		ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, GRV, BSPC,     INS,  \
		TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,          DEL,  \
		CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,NUHS,ENT,                 \
		LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM, DOT,SLSH,RO,  RSFT,     UP,        \
		LCTL,LGUI,LALT,MHEN,     SPC, SPC,                HENK,FN0, RGUI,RCTL,LEFT,DOWN,RGHT  ),

	// 1: fn
	KEYMAP (
		GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, NO,  DEL,      FN1,  \
		NO,  PSCR,NO,  HOME,PGUP,NO,  NO,  NO,  NO,  NO,  NO,  UP,  NO,  NO,            NO,   \
		NO,  NO,  NO,  END, PGDN,NO,  NO,  NO,  NO,  NO,  LEFT,RGHT,NO,  NO,                  \
		TRNS,NO,  MPRV,MPLY,MNXT,NO,  NO,  NO,  NO,  NO,  NO,  DOWN,NO,  TRNS,     VOLU,      \
		TRNS,TRNS,TRNS,TRNS,     NO,  NO,                 TRNS,TRNS,TRNS,TRNS,NO,  VOLD,NO    ),
};

// Fn action definition
const action_t PROGMEM fn_actions[] =
{
	[0] = ACTION_LAYER_MOMENTARY(1),
};
