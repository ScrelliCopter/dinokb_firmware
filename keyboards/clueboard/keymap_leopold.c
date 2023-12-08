#include "clueboard.h"
#include "keymap_common.h"


/////////////////////
/// Layer definitions
enum layer_id
{
	LAYER_BASE,     // 0: Base layer
	LAYER_FUNCTION, // 1: Function layer
	NUM_LAYERS
};

const uint8_t KEYMAP_SECTION keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] =
{
	[LAYER_BASE] = KEYMAP(
		FN1, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,     INS,  \
		TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,          DEL,  \
		CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,NUHS,ENT,                 \
		LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RO,  RSFT,     UP,        \
		LCTL,LGUI,LALT,MHEN,     SPC, SPC,                HENK,RALT,RCTL,FN0, LEFT,DOWN,RGHT  ),
	[LAYER_FUNCTION] = KEYMAP(
		TRNS,F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,TRNS,     TRNS, \
		TRNS,FN2, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,PSCR,SLCK,PAUS,TRNS,TRNS,TRNS,          TRNS, \
		TRNS,TRNS,FN1, TRNS,TRNS,TRNS,TRNS,TRNS,HOME,PGUP,TRNS,TRNS,TRNS,TRNS,                \
		TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,END, PGDN,TRNS,TRNS,TRNS,     PGUP,      \
		TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,               TRNS,TRNS,APP, TRNS,HOME,PGDN,END   )
};


/////////////////////////////////
/// Function & action definitions
enum function_id
{
	FN0_FUNCTION_LAYER,
	FN1_ESCAPE_GRAVE,
	FN2_GRAVE_TOGGLE,
	NUM_FUNCTIONS
};

enum action_id
{
	ACTION_ESCAPE_GRAVE,
	ACTION_GRAVE_TOGGLE
};

const action_t PROGMEM fn_actions[] =
{
	[FN0_FUNCTION_LAYER] = ACTION_LAYER_MOMENTARY(LAYER_FUNCTION),
	[FN1_ESCAPE_GRAVE]   = ACTION_FUNCTION(ACTION_ESCAPE_GRAVE),
	[FN2_GRAVE_TOGGLE]   = ACTION_FUNCTION(ACTION_GRAVE_TOGGLE)
};

void action_function(keyrecord_t* record, uint8_t id, uint8_t opt)
{
	static bool toggleGrv = false;

	if (id == ACTION_ESCAPE_GRAVE)
	{
		static uint8_t keyPressed = KC_NO;
		if (record->event.pressed)
		{
			// Leopold FC660M escape/grave works as follows:
			// Grave toggle off: Default escape, grave if shift or fn, escape if both.
			// Grave toggle on: Default grave, escape if fn.
			const bool fn = (layer_state & (1 << LAYER_FUNCTION)) == 1 << LAYER_FUNCTION;
			const uint8_t shift = get_mods() & (MOD_LSFT | MOD_RSFT);
			keyPressed = (toggleGrv || shift) == fn ? KC_ESCAPE : KC_GRAVE;
			register_code(keyPressed);
		}
		else
		{
			unregister_code(keyPressed);
			keyPressed = KC_NO;
		}
		send_keyboard_report();
	}
	else if (id == ACTION_GRAVE_TOGGLE)
	{
		if (record->event.pressed)
			clue_led_set((toggleGrv = !toggleGrv) ? _BV(CLUE_LED_INSERT) : 0);
	}
}
