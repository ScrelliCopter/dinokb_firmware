#include "keymap_common.h"

enum layerId
{
	L_BASE,
	L_FUNC
};

enum funcId
{
	F_ESC
};

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{
	// 0: qwerty
	[L_BASE] = KEYMAP (
		FN1, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, GRV, BSPC,     INS,  \
		TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,          DEL,  \
		FN0, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,NUHS,ENT,                 \
		LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM, DOT,SLSH,RO,  RSFT,     UP,        \
		LCTL,LGUI,LALT,MHEN,     SPC, SPC,                HENK,FN0, RGUI,RCTL,LEFT,DOWN,RGHT  ),

	// 1: fn
	[L_FUNC] = KEYMAP (
		GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, NO,  DEL,      NO,   \
		CAPS,PSCR,NO,  NO,  NO,  NO,  NO,  PGUP,HOME,NO,  NO,  UP,  NO,  NO,            NO,   \
		TRNS,NO,  NO,  NO,  NO,  NO,  NO,  PGDN,END, NO,  LEFT,RGHT,NO,  NO,                  \
		TRNS,NO,  MPRV,MPLY,MNXT,NO,  NO,  NO,  NO,  NO,  NO,  DOWN,NO,  TRNS,     VOLU,      \
		TRNS,TRNS,TRNS,TRNS,     NO,  NO,                 TRNS,TRNS,TRNS,TRNS,NO,  VOLD,NO    ),
};

// Fn action definition
const action_t PROGMEM fn_actions[] =
{
	[0] = ACTION_LAYER_MOMENTARY(L_FUNC),
	[1] = ACTION_FUNCTION(F_ESC)
};

void action_function(keyrecord_t* record, uint8_t id, uint8_t opt)
{
	if (id == F_ESC)
	{
		static uint8_t shiftState;
		
		if (record->event.pressed)
		{
			shiftState = get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));
			register_code(shiftState ? KC_GRV : KC_ESC);
			//send_keyboard_report();
		}
		else
		{
			unregister_code(shiftState ? KC_GRV : KC_ESC);
		}
	}
}
