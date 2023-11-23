// HHKB JP Layout
#include "keymap_common.h"

#ifdef KEYMAP_SECTION_ENABLE
#  define KEYMAP_SECTION __attribute__((section(".keymap.keymaps")))
#  define ACTION_SECTION __attribute__((section(".keymap.fn_actions")))
#else
#  define KEYMAP_SECTION PROGMEM
#  define ACTION_SECTION PROGMEM
#endif


/////////////////////
/// Layer definitions
enum
{
	LAYER_BASE,     // Layer 0: Default Layer
	LAYER_FUNCTION, // Layer 1: HHKB mode (HHKB Fn)
	LAYER_NUMPAD,   // Layer 2: foobar + numpad

	NUM_LAYERS
};

const uint8_t keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] KEYMAP_SECTION =
{
	[LAYER_BASE] = KEYMAP_JP(
		ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, GRV, BSPC, \
		TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,           \
		FN0, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,BSLS,ENT,       \
		LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,UP,  FN0,       \
		LCTL,CAPS,LGUI,LALT,FN1,      SPC,      CALC,FN2, RALT,FN0, LEFT,DOWN,RGHT  ),
	[LAYER_FUNCTION] = KEYMAP_JP(
		ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL,  \
		CAPS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  PSCR,SLCK,PAUS,UP,  NO,             \
		TRNS,VOLD,VOLU,MUTE,NO,  NO,  PAST,PSLS,HOME,PGUP,LEFT,RGHT,NO,  PENT,      \
		TRNS,MPRV,MPLY,MNXT,MSTP,NO,  PPLS,PMNS,END, PGDN,DOWN,TRNS,NO,  TRNS,      \
		TRNS,BTLD,TRNS,TRNS,TRNS,     NO,       NO,  TRNS,TRNS,TRNS,NO,  NO,  NO    ),
	[LAYER_NUMPAD] = KEYMAP_JP(
		ESC, NO,  NO,  NO,  NO,  NO,  NO,  NLCK,PSLS,PAST,PMNS,  NO,  NO,  NO,BSPC, \
		NO,  NO,  NO,  NO,  NO,  NO,  NO,  P7,  P8,  P9,  PPLS,  NO,  NO,           \
		TRNS,FN9, FN10,FN8, NO,  NO,  NO,  P4,  P5,  P6,  NO,  NO,  NO,  NO,        \
		TRNS,FN5, FN7, FN6, NO,  NO,  NO,  P1,  P2,  P3,  PENT,TRNS,NO,  TRNS,      \
		NO,  TRNS,TRNS,TRNS,TRNS,     NO,       CALC,P0,  PDOT,FN3, NO,  NO,  NO    )
};


////////////////////
/// Macro defintions
enum macro_id
{
	MACRO_DOUBLEZERO,

	MACRO_FOOBAR_PREVIOUS,
	MACRO_FOOBAR_NEXT,
	MACRO_FOOBAR_PLAY,
	MACRO_FOOBAR_VOLUMEUP,
	MACRO_FOOBAR_VOLUMEDOWN,
	MACRO_FOOBAR_STOP
};

const macro_t* action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	switch (id)
	{
	case MACRO_DOUBLEZERO: return record->event.pressed ? MACRO(T(P0), T(P0), END) : MACRO_NONE;

	case MACRO_FOOBAR_PREVIOUS:   return record->event.pressed ? MACRO(D(RCTL), T(DEL),  U(RCTL), END) : MACRO_NONE;
	case MACRO_FOOBAR_NEXT:       return record->event.pressed ? MACRO(D(RCTL), T(PGDN), U(RCTL), END) : MACRO_NONE;
	case MACRO_FOOBAR_PLAY:       return record->event.pressed ? MACRO(D(RCTL), T(END),  U(RCTL), END) : MACRO_NONE;
	case MACRO_FOOBAR_VOLUMEUP:   return record->event.pressed ? MACRO(D(RCTL), T(PGUP), U(RCTL), END) : MACRO_NONE;
	case MACRO_FOOBAR_VOLUMEDOWN: return record->event.pressed ? MACRO(D(RCTL), T(INS),  U(RCTL), END) : MACRO_NONE;
	case MACRO_FOOBAR_STOP:       return record->event.pressed ? MACRO(D(RCTL), T(HOME), U(RCTL), END) : MACRO_NONE;

	default: return MACRO_NONE;
	}
}


/////////////////////////////////
/// Function & action definitions
enum function_id
{
	FN0_LAYER_FUNCTION = 0,
	FN1_LAYER_NUMPAD   = 1,

	FN3_MACRO_DOUBLEZERO = 3,

	FN5_FOOBAR_PREVIOUS   = 5,
	FN6_FOOBAR_NEXT       = 6,
	FN7_FOOBAR_PLAY       = 7,
	FN8_FOOBAR_VOLUMEUP   = 8,
	FN9_FOOBAR_VOLUMEDOWN = 9,
	FN10_FOOBAR_STOP      = 10,

	NUM_FUNCTIONS
};

const action_t fn_actions[NUM_FUNCTIONS] ACTION_SECTION =
{
	[FN0_LAYER_FUNCTION] = ACTION_LAYER_MOMENTARY(LAYER_FUNCTION),
	[FN1_LAYER_NUMPAD]   = ACTION_LAYER_MOMENTARY(LAYER_NUMPAD),

	[FN3_MACRO_DOUBLEZERO] = ACTION_MACRO(MACRO_DOUBLEZERO),

	[FN5_FOOBAR_PREVIOUS]   = ACTION_MACRO(MACRO_FOOBAR_PREVIOUS),
	[FN6_FOOBAR_NEXT]       = ACTION_MACRO(MACRO_FOOBAR_NEXT),
	[FN7_FOOBAR_PLAY]       = ACTION_MACRO(MACRO_FOOBAR_PLAY),
	[FN8_FOOBAR_VOLUMEUP]   = ACTION_MACRO(MACRO_FOOBAR_VOLUMEUP),
	[FN9_FOOBAR_VOLUMEDOWN] = ACTION_MACRO(MACRO_FOOBAR_VOLUMEDOWN),
	[FN10_FOOBAR_STOP]      = ACTION_MACRO(MACRO_FOOBAR_STOP)
};
