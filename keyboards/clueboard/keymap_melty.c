#include <bootloader.h>
#include <wait.h>

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
	[LAYER_BASE] = KEYMAP_ANSI(
		FN1, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,          INS,  \
		TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,          DEL,  \
		FN0, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,ENT,                      \
		LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM, DOT,SLSH,     RSFT,          UP,        \
		LCTL,LGUI,LALT,          SPC, SPC,                     RGUI,RCTL,FN0, LEFT,DOWN,RGHT  ),
	[LAYER_FUNCTION] = KEYMAP_ANSI(
		TRNS,F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,           VOLU, \
		CAPS,FN2, UP,  MYCM,FN3, P7,  P8,  P9,  PSCR,SLCK,PAUS,MPRV,MNXT,MUTE,          VOLD, \
		TRNS,LEFT,DOWN,RGHT,CALC,P4,  P5,  P6,  HOME,PGUP,NO,  MSTP,MPLY,                     \
		TRNS,FN4, FN5, FN6, FN7, P1,  P2,  P3,  END, PGDN,NO,       TRNS,          PGUP,      \
		TRNS,TRNS,TRNS,          P0,  P0,                      PDOT,APP, TRNS,HOME,PGDN,END   )
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
		? MACRO(D(RCTL), D(DEL),  END)
		: MACRO(U(DEL),  U(RCTL), END);
	case (MACRO_FOOBAR_PLAY): return record->event.pressed
		? MACRO(D(RCTL), D(END),  END)
		: MACRO(U(END),  U(RCTL), END);
	case (MACRO_FOOBAR_NEXT): return record->event.pressed
		? MACRO(D(RCTL), D(PGDN), END)
		: MACRO(U(PGDN), U(RCTL), END);
	case (MACRO_FOOBAR_STOP): return record->event.pressed
		? MACRO(D(RCTL), D(HOME), END)
		: MACRO(U(HOME), U(RCTL), END);
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

	FN3_NUMLCK_BOOTLOADER,

	FN4_FOOBAR_PREVIOUS,
	FN5_FOOBAR_PLAY,
	FN6_FOOBAR_NEXT,
	FN7_FOOBAR_STOP,

	NUM_FUNCTIONS
};

enum action_id
{
	ACTION_ESCAPE_GRAVE,
	ACTION_TOGGLE_GRAVE,
	ACTION_NUMLCK_BOOTLOADER
};

const action_t PROGMEM fn_actions[] =
{
	[FN0_FUNCTION_LAYER] = ACTION_LAYER_MOMENTARY(LAYER_FUNCTION),

	[FN1_ESCAPE_GRAVE] = ACTION_FUNCTION(ACTION_ESCAPE_GRAVE),
	[FN2_TOGGLE_GRAVE] = ACTION_FUNCTION(ACTION_TOGGLE_GRAVE),

	[FN3_NUMLCK_BOOTLOADER] = ACTION_FUNCTION(ACTION_NUMLCK_BOOTLOADER),

	[FN4_FOOBAR_PREVIOUS]   = ACTION_MACRO(MACRO_FOOBAR_PREVIOUS),
	[FN5_FOOBAR_PLAY]       = ACTION_MACRO(MACRO_FOOBAR_PLAY),
	[FN6_FOOBAR_NEXT]       = ACTION_MACRO(MACRO_FOOBAR_NEXT),
	[FN7_FOOBAR_STOP]       = ACTION_MACRO(MACRO_FOOBAR_STOP)
};

void action_function(keyrecord_t* record, uint8_t id, uint8_t opt)
{
	static bool toggleGrv = false;
	static uint8_t escKeyPressed = KC_NO;

	switch (id)
	{
	case ACTION_ESCAPE_GRAVE:
		// Grave toggle off: Default Esc, Tilde if Shift & not Ctrl, FN swaps behaviour
		// Grave toggle on: Grave by default, Esc if FN
		if (record->event.pressed)
		{
			const bool fn = (layer_state & (1 << LAYER_FUNCTION)) == 1 << LAYER_FUNCTION;
			const uint8_t shiftState = get_mods() & (MOD_LSFT | MOD_RSFT);
			if (toggleGrv || (fn && !shiftState))
			{
				escKeyPressed = fn == toggleGrv ? KC_ESCAPE : KC_GRAVE;
			}
			else
			{
				const uint8_t ctrlSate = get_mods() & (MOD_LCTL | MOD_RCTL);
				escKeyPressed = fn == (shiftState && !ctrlSate) ? KC_ESCAPE : KC_GRAVE;
			}
			register_code(escKeyPressed);
		}
		else
		{
			unregister_code(escKeyPressed);
			escKeyPressed = KC_NO;
		}
		send_keyboard_report();
		break;

	case ACTION_TOGGLE_GRAVE:
		if (record->event.pressed)
		{
			toggleGrv = !toggleGrv;
			clue_led_set(toggleGrv ? CLUE_LED_MASK(CLUE_LED_INSERT) : 0);
		}
		break;

	case ACTION_NUMLCK_BOOTLOADER:
		// Jump to DFU on FN + Shift + Alt/Opt, otherwise Num Lock
		if (get_mods() & (MOD_LSFT | MOD_RSFT) && get_mods() & (MOD_LALT | MOD_RALT))
		{
			if (record->event.pressed)
			{
				clear_keyboard();
				wait_ms(50);
				bootloader_jump(); // No return
			}
		}
		else
		{
			record->event.pressed ? register_code(KC_NUMLOCK) : unregister_code(KC_NUMLOCK);
			send_keyboard_report();
		}
		break;

	default: break;
	}
}
