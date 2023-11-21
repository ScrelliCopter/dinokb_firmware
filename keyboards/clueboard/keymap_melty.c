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
		FN1, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, GRV, BSPC,     INS,  \
		TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,          DEL,  \
		FN0, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,NUHS,ENT,                 \
		LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM, DOT,SLSH,RO,  RSFT,     UP,        \
		LCTL,LGUI,LALT,MHEN,     SPC, SPC,                HENK,FN0, RGUI,RCTL,LEFT,DOWN,RGHT  ),
	[LAYER_FUNCTION] = KEYMAP(
		TRNS,F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, NO,  DEL,      FN2,  \
		CAPS,PSCR,NO,  NO,  NO,  NO,  NO,  PGUP,HOME,NO,  NO,  UP,  NO,  NO,            NO,   \
		TRNS,FN6, FN7, FN8, NO,  NO,  NO,  PGDN,END, NO,  LEFT,RGHT,NO,  NO,                  \
		TRNS,NO,  FN3, FN4, FN5, NO,  NO,  NO,  NO,  NO,  NO,  DOWN,NO,  TRNS,     VOLU,      \
		TRNS,TRNS,TRNS,TRNS,     NO,  NO,                 TRNS,TRNS,TRNS,TRNS,NO,  VOLD,NO    )
};


////////////////////
/// Macro defintions
enum macro_id
{
	MACRO_FOOBAR_PREVIOUS,
	MACRO_FOOBAR_PLAY,
	MACRO_FOOBAR_NEXT,
	MACRO_FOOBAR_VOLUMEDOWN,
	MACRO_FOOBAR_STOP,
	MACRO_FOOBAR_VOLUMEUP
};

const macro_t* action_get_macro(keyrecord_t* record, uint8_t id, uint8_t opt)
{
	switch (id)
	{
	case (MACRO_FOOBAR_PREVIOUS): return record->event.pressed
		? MACRO(D(RCTL), D(DEL), END)
		: MACRO(U(DEL), U(RCTL), END);
	case (MACRO_FOOBAR_PLAY): return record->event.pressed
		? MACRO(D(RCTL), D(END), END)
		: MACRO(U(END), U(RCTL), END);
	case (MACRO_FOOBAR_NEXT): return record->event.pressed
		? MACRO(D(RCTL), D(PGDN), END)
		: MACRO(U(PGDN), U(RCTL), END);
	case (MACRO_FOOBAR_VOLUMEDOWN): return record->event.pressed
		? MACRO(D(RCTL), D(INS), END)
		: MACRO(U(INS), U(RCTL), END);
	case (MACRO_FOOBAR_STOP): return record->event.pressed
		? MACRO(D(RCTL), D(HOME), END)
		: MACRO(U(HOME), U(RCTL), END);
	case (MACRO_FOOBAR_VOLUMEUP): return record->event.pressed
		? MACRO(D(RCTL), D(PGUP), END)
		: MACRO(U(PGUP), U(RCTL), END);
	default: return MACRO_NONE;
	}
}


/////////////////////////////////
/// Function & action definitions
enum function_id
{
	FN0_FUNCTION_LAYER,

	FN1_ESCAPE_GRAVE,
	FN2_TOGGLE_GRAVE,

	FN3_FOOBAR_PREVIOUS,
	FN4_FOOBAR_PLAY,
	FN5_FOOBAR_NEXT,
	FN6_FOOBAR_VOLUMEDOWN,
	FN7_FOOBAR_STOP,
	FN8_FOOBAR_VOLUMEUP,

	NUM_FUNCTIONS
};

enum action_id
{
	ACTION_ESCAPE_GRAVE,
	ACTION_TOGGLE_GRAVE
};

const action_t PROGMEM fn_actions[] =
{
	[FN0_FUNCTION_LAYER] = ACTION_LAYER_MOMENTARY(LAYER_FUNCTION),

	[FN1_ESCAPE_GRAVE] = ACTION_FUNCTION(ACTION_ESCAPE_GRAVE),
	[FN2_TOGGLE_GRAVE] = ACTION_FUNCTION(ACTION_TOGGLE_GRAVE),

	[FN3_FOOBAR_PREVIOUS]   = ACTION_MACRO(MACRO_FOOBAR_PREVIOUS),
	[FN4_FOOBAR_PLAY]       = ACTION_MACRO(MACRO_FOOBAR_PLAY),
	[FN5_FOOBAR_NEXT]       = ACTION_MACRO(MACRO_FOOBAR_NEXT),
	[FN6_FOOBAR_VOLUMEDOWN] = ACTION_MACRO(MACRO_FOOBAR_VOLUMEDOWN),
	[FN7_FOOBAR_STOP]       = ACTION_MACRO(MACRO_FOOBAR_STOP),
	[FN8_FOOBAR_VOLUMEUP]   = ACTION_MACRO(MACRO_FOOBAR_VOLUMEUP)
};

void action_function(keyrecord_t* record, uint8_t id, uint8_t opt)
{
	static uint8_t toggleGrv = 0;

	// Grave toggle off:
	//  Escape by default, grave when FN layer is active
	//  Grave whenever shift is held except for when control is also held
	// Grave toggle on:
	//  Grave by default, escape when FN layer is active

	if (id == ACTION_ESCAPE_GRAVE)
	{
		static uint8_t keyPressed = KC_NO;

		if (record->event.pressed)
		{
			if (layer_state & (1 << LAYER_FUNCTION))
			{
				keyPressed = toggleGrv ? KC_ESCAPE : KC_GRAVE;
			}
			else
			{
				if (toggleGrv)
				{
					keyPressed = toggleGrv ? KC_GRAVE : KC_ESCAPE;
				}
				else
				{
					const uint8_t modState = get_mods();
					const uint8_t shiftState =
						 (modState & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))) &&
						!(modState & (MOD_BIT(KC_LCTRL)  | MOD_BIT(KC_RCTRL)));
					keyPressed = shiftState ? KC_GRAVE : KC_ESCAPE;
				}
			}

			register_code(keyPressed);
		}
		else
		{
			unregister_code(keyPressed);
			keyPressed = KC_NO;
		}

		send_keyboard_report();
	}
	else if (id == ACTION_TOGGLE_GRAVE)
	{
		if (record->event.pressed)
		{
			toggleGrv = !toggleGrv;
			clue_led_set(toggleGrv ? CLUE_LED_MASK(CLUE_LED_INSERT) : 0);
		}
	}
}
