/* keymap_prime.c - pain27 - (C) 2023 a dinosaur */

#include "keymap_common.h"


/////////////////////
/// Layer definitions
enum layer_id
{
	LAYER_BASE,      // 0: Base layer
	LAYER_FUNCTION1, // 1: Function layer 1
	LAYER_FUNCTION2, // 2: Function layer 2

	NUM_LAYERS
};

const uint8_t keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] KEYMAP_SECTION =
{
	[LAYER_BASE] = KEYMAP(
		Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,
		FN4, S,   D,   F,   G,   H,   J,   K,   FN1, /**/
		FN3, X,   C,   V,   B,   N,   FN2, /**/ /**/ /**/
		/**/ /**/ /**/ /**/ FN0  /**/ /**/ /**/ /**/ /**/),
	[LAYER_FUNCTION1] = KEYMAP(
		ESC, 1,   2,   3,   EQL, TRNS,TRNS,UP,  TRNS,BSPC,
		TRNS,4,   5,   6,   MINS,SLSH,LEFT,RGHT,ENT, /**/
		FN5, 7,   8,   9,   FN6, FN7, DOWN,/**/ /**/ /**/
		/**/ /**/ /**/ /**/ TRNS /**/ /**/ /**/ /**/ /**/),
	[LAYER_FUNCTION2] = KEYMAP(
		F1,  F2,  F3,  F4,  F5,  F6,  TRNS,PGUP,TRNS,DEL,
		F7,  F8,  F9,  F10, F11, F12, HOME,END, TRNS,/**/
		DOT, COMM,QUOT,FN8, FN9, FN10,PGDN,/**/ /**/ /**/
		/**/ /**/ /**/ /**/ NO   /**/ /**/ /**/ /**/ /**/)
};


/////////////////////////
/// Fn action definitions
enum function_id
{
	FN0_SPACE_FL1,
	FN1_L_HOLD_FL2,
	FN2_M_HOLD_RSHIFT,
	FN3_Z_HOLD_LSHIFT,
	FN4_A_HOLD_CONTROL,
	FN5_0_HOLD_LSHIFT,

	FN6_KC_PLUS,
	FN7_KC_ASTR,
	FN8_KC_DQUO,
	FN9_KC_LPRN,
	FN10_KC_RPRN,

	NUM_FUNCTIONS
};

const action_t fn_actions[NUM_FUNCTIONS] ACTION_SECTION =
{
	[FN0_SPACE_FL1]      = ACTION_LAYER_TAP(LAYER_FUNCTION1, KC_SPACE),
	[FN1_L_HOLD_FL2]     = ACTION_LAYER_TAP(LAYER_FUNCTION2, KC_L),
	[FN2_M_HOLD_RSHIFT]  = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_M),
	[FN3_Z_HOLD_LSHIFT]  = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_Z),
	[FN4_A_HOLD_CONTROL] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_A),
	[FN5_0_HOLD_LSHIFT]  = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_0),

	[FN6_KC_PLUS]  = ACTION_MODS_KEY(MOD_LSFT, KC_EQUAL),
	[FN7_KC_ASTR]  = ACTION_MODS_KEY(MOD_LSFT, KC_8),
	[FN8_KC_DQUO]  = ACTION_MODS_KEY(MOD_LSFT, KC_QUOTE),
	[FN9_KC_LPRN]  = ACTION_MODS_KEY(MOD_LSFT, KC_9),
	[FN10_KC_RPRN] = ACTION_MODS_KEY(MOD_LSFT, KC_0)
};
