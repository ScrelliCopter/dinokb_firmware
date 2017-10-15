#include "keymap_common.h"

const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: qwerty */
    KEYMAP_ANSI(
		GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC, \
		TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS, \
		FN0, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,  \
		LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RSFT, \
		LCTL,LGUI,LALT,          SPC,                     FN0, RGUI,APP, RCTL),
	/* 1: v60 arrows */
	KEYMAP_ANSI(
		TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
		TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS, \
		TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS, \
		TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          UP, \
		TRNS,TRNS,TRNS,          TRNS,                    TRNS,LEFT,DOWN,RGHT),
	/* 2: fn */
	KEYMAP_ANSI(
		ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL, \
		CAPS,PSCR,INS, HOME,PGUP,PAUS,SLCK,PGUP,UP,  PGDN,PEQL,UP,  INS, BTLD, \
		TRNS,NO,  DEL, END, PGDN,NO,  NLCK,LEFT,DOWN,RGHT,LEFT,RGHT,     FN1, \
		TRNS,MPRV,MPLY,MNXT,VOLD,VOLU,MUTE,PAST,PMNS,PPLS,DOWN,          TRNS, \
		TRNS,TRNS,TRNS,          NO,                      TRNS,TRNS,TRNS,TRNS),
};

// FN action definition.
const action_t PROGMEM fn_actions[] =
{
    [0] = ACTION_LAYER_MOMENTARY(2),
	[1] = ACTION_LAYER_TOGGLE(1),
};
