#include "keymap_common.h"


////////////////////
/// Layer defintions
enum layer_id
{
	LAYER_BASE,      // Layer 0: QWERTY base
	LAYER_FUNCTION,  // Layer 1: Function layer
	NUM_LAYERS
};

const uint8_t PROGMEM keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] =
{
	[LAYER_BASE] = KEYMAP(
		ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, GRV, BSPC, \
		TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,/**/ BSLS, \
		CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,/**/ /**/ ENT,  \
		LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,/**/ RSFT,FN0,  \
		LCTL,LGUI,LALT,/**/ /**/ SPC, /**/ /**/ /**/ /**/ /**/ FN0, RGUI,APP, RCTL  ),
	[LAYER_FUNCTION] = KEYMAP(
		GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL,  \
		NO,  NO,  UP,  NO,  BTLD,NO,  NO,  NO,  PSCR,INS, HOME,PGUP,NO,  /**/ NO,   \
		NO,  LEFT,DOWN,RGHT,NO,  NO,  NO,  NO,  SLCK,DEL, END, PGDN,/**/ /**/ NO,   \
		TRNS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  PAUS,NO,  NO,  /**/ TRNS,TRNS, \
		TRNS,TRNS,TRNS,/**/ /**/ NO,  /**/ /**/ /**/ /**/ /**/ TRNS,TRNS,TRNS,TRNS  )
};


/////////////////////////
/// Fn action definitions
enum function_id
{
	FN0_FUNCTION_LAYER,
	NUM_FUNCTIONS
};

const action_t PROGMEM fn_actions[NUM_FUNCTIONS] =
{
	[FN0_FUNCTION_LAYER] = ACTION_LAYER_MOMENTARY(LAYER_FUNCTION)
};
