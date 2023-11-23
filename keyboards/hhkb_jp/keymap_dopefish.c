/* 
 * HHKB JP Layout
 */
#include "keymap_common.h"


#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Layer 0: Default Layer */
    KEYMAP_JP(ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, GRV, BSPC, \
              TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC, \
              FN0, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,BSLS,ENT, \
              LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RSFT,UP,  FN0, \
              LCTL,CAPS,LGUI,LALT,FN1,      SPC,      CALC,FN2, RALT,FN0, LEFT,DOWN,RGHT),

    /* Layer 1: HHKB mode (HHKB Fn)` */
    KEYMAP_JP(ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, INS, DEL, \
              CAPS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  PSCR,SLCK,PAUS,UP,  NO, \
              TRNS,VOLD,VOLU,MUTE,NO,  NO,  PAST,PSLS,HOME,PGUP,LEFT,RGHT,NO,  PENT, \
              TRNS,MPRV,MPLY,MNXT,MSTP,NO,  PPLS,PMNS,END, PGDN,DOWN,TRNS,NO,  TRNS, \
              TRNS,BTLD,TRNS,TRNS,TRNS,     NO,       NO,  TRNS,TRNS,TRNS,NO,  NO,  NO),
	/* Layer 2: numpad */
	KEYMAP_JP(ESC, NO,  NO,  NO,  NO,  NO,  NO,  NLCK,PSLS,PAST,PMNS,  NO,  NO,  NO,BSPC, \
              NO,  NO,  NO,  NO,  NO,  NO,  NO,  P7,  P8,  P9,  PPLS,  NO,  NO, \
              TRNS,FN9, FN10,FN8, NO,  NO,  NO,  P4,  P5,  P6,  NO,  NO,  NO,  NO, \
              TRNS,FN5, FN7, FN6, NO,  NO,  NO,  P1,  P2,  P3,  PENT,TRNS,NO,  TRNS, \
              NO,  TRNS,TRNS,TRNS,TRNS,     NO,       CALC,P0,  PDOT,FN3, NO,  NO,  NO),
	/* Layer 3: macros */
	KEYMAP_JP(NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO, \
              NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO, \
              TRNS,NO,  NO,  NO,  NO,  FN11,NO,  NO,  FN12,FN13,FN14,NO,  NO,  NO, \
              TRNS,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  TRNS,NO,  TRNS, \
              NO,  TRNS,TRNS,TRNS,TRNS,     NO,       NO,  TRNS,TRNS,TRNS,NO,  NO,  NO),
};

enum macro_id {
	DOUBLEZERO,
	FBPREV,
	FBNEXT,
	FBPLAY,
	FBVOLUP,
	FBVOLDN,
	FBSTOP,
	
	// memes
	GREGGO,
	LIKE,
	THIS,
	THAT,
};

/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION_ENABLE
const action_t fn_actions[] __attribute__ ((section (".keymap.fn_actions"))) = {
#else
const action_t fn_actions[] PROGMEM = {
#endif
    [0] = ACTION_LAYER_MOMENTARY(1),
	[1] = ACTION_LAYER_MOMENTARY(2),
	[2] = ACTION_LAYER_MOMENTARY(3),
	[3] = ACTION_MACRO(DOUBLEZERO),
	[5] = ACTION_MACRO(FBPREV),
	[6] = ACTION_MACRO(FBNEXT),
	[7] = ACTION_MACRO(FBPLAY),
	[8] = ACTION_MACRO(FBVOLUP),
	[9] = ACTION_MACRO(FBVOLDN),
	[10] = ACTION_MACRO(FBSTOP),
	
	[11] = ACTION_MACRO(GREGGO),
	[12] = ACTION_MACRO(LIKE),
	[13] = ACTION_MACRO(THIS),
	[14] = ACTION_MACRO(THAT),
};

//fukken macros cunt
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	switch (id) {
        case DOUBLEZERO:
			return (record->event.pressed ?
					MACRO ( T(P0), T(P0), END ) :
					MACRO_NONE );
		case FBPREV:
			return (record->event.pressed ?
					MACRO ( D(RCTL), T(DEL), U(RCTL), END ) :
					MACRO_NONE );
		case FBNEXT:
			return (record->event.pressed ?
					MACRO ( D(RCTL), T(PGDN), U(RCTL), END ) :
					MACRO_NONE );
		case FBPLAY:
			return (record->event.pressed ?
					MACRO ( D(RCTL), T(END), U(RCTL), END ) :
					MACRO_NONE );
		case FBVOLUP:
			return (record->event.pressed ?
					MACRO ( D(RCTL), T(PGUP), U(RCTL), END ) :
					MACRO_NONE );
		case FBVOLDN:
			return (record->event.pressed ?
					MACRO ( D(RCTL), T(INS), U(RCTL), END ) :
					MACRO_NONE );
		case FBSTOP:
			return (record->event.pressed ?
					MACRO ( D(RCTL), T(HOME), U(RCTL), END ) :
					MACRO_NONE );
					
		case GREGGO:
            return (record->event.pressed ?
					MACRO( D(LSFT), T(SCLN), U(LSFT), T(G), T(R), T(E), T(G), T(G), T(O), D(LSFT), T(SCLN), END ) :
					MACRO_NONE );
		case LIKE:
            return (record->event.pressed ?
					MACRO( D(LSFT), T(L), U(LSFT), T(I), T(K), T(E), T(ENT), END ) :
					MACRO_NONE );
		case THIS:
            return (record->event.pressed ?
					MACRO( D(LSFT), T(T), U(LSFT), T(H), T(I), T(S), T(ENT), END ) :
					MACRO_NONE );
		case THAT:
            return (record->event.pressed ?
					MACRO( D(LSFT), T(T), U(LSFT), T(H), T(A), T(T), T(ENT), END ) :
					MACRO_NONE );
	}
	return MACRO_NONE;
}
