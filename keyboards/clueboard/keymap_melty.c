#include "keymap_common.h"

enum layerId
{
	L_BASE,
	L_FUNC
};

enum macroId
{
	M_FOO_PREV,
	M_FOO_PLAY,
	M_FOO_NEXT,
	M_FOO_VLDN,
	M_FOO_STOP,
	M_FOO_VLUP
};

enum funcId
{
	F_ESC_GRV,
	F_TOGGLE_GRV
};


// Layer definition.
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{
	// 0: Base layer
	[L_BASE] = KEYMAP (
		FN1, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, GRV, BSPC,     INS,  \
		TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,          DEL,  \
		FN0, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,NUHS,ENT,                 \
		LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM, DOT,SLSH,RO,  RSFT,     UP,        \
		LCTL,LGUI,LALT,MHEN,     SPC, SPC,                HENK,FN0, RGUI,RCTL,LEFT,DOWN,RGHT  ),

	// 1: Function layer
	[L_FUNC] = KEYMAP (
		TRNS,F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, NO,  DEL,      FN2,  \
		CAPS,PSCR,NO,  NO,  NO,  NO,  NO,  PGUP,HOME,NO,  NO,  UP,  NO,  NO,            NO,   \
		TRNS,FN6, FN7, FN8, NO,  NO,  NO,  PGDN,END, NO,  LEFT,RGHT,NO,  NO,                  \
		TRNS,NO,  FN3, FN4, FN5, NO,  NO,  NO,  NO,  NO,  NO,  DOWN,NO,  TRNS,     VOLU,      \
		TRNS,TRNS,TRNS,TRNS,     NO,  NO,                 TRNS,TRNS,TRNS,TRNS,NO,  VOLD,NO    )
};

// FN action definition.
const action_t PROGMEM fn_actions[] =
{
	[0] = ACTION_LAYER_MOMENTARY(L_FUNC),
	
	[1] = ACTION_FUNCTION(F_ESC_GRV),
	[2] = ACTION_FUNCTION(F_TOGGLE_GRV),
	
	[3] = ACTION_MACRO(M_FOO_PREV),
	[4] = ACTION_MACRO(M_FOO_PLAY),
	[5] = ACTION_MACRO(M_FOO_NEXT),
	[6] = ACTION_MACRO(M_FOO_VLDN),
	[7] = ACTION_MACRO(M_FOO_STOP),
	[8] = ACTION_MACRO(M_FOO_VLUP)
};

// Macro actions.
const macro_t* action_get_macro(keyrecord_t* record, uint8_t id, uint8_t opt)
{
	switch (id)
	{
	case (M_FOO_PREV):
		return record->event.pressed ?
			MACRO( D(RCTL), D(DEL), END ) :
			MACRO( U(DEL), U(RCTL), END );
			
	case (M_FOO_PLAY):
		return record->event.pressed ?
			MACRO( D(RCTL), D(END), END ) :
			MACRO( U(END), U(RCTL), END );
			
	case (M_FOO_NEXT):
		return record->event.pressed ?
			MACRO( D(RCTL), D(PGDN), END ) :
			MACRO( U(PGDN), U(RCTL), END );
			
	case (M_FOO_VLDN):
		return record->event.pressed ?
			MACRO( D(RCTL), D(INS), END ) :
			MACRO( U(INS), U(RCTL), END );
			
	case (M_FOO_STOP):
		return record->event.pressed ?
			MACRO( D(RCTL), D(HOME), END ) :
			MACRO( U(HOME), U(RCTL), END );
			
	case (M_FOO_VLUP):
		return record->event.pressed ?
			MACRO( D(RCTL), D(PGUP), END ) :
			MACRO( U(PGUP), U(RCTL), END );
		
	default:
		return MACRO_NONE;
	}
}

// Function actions.
void action_function(keyrecord_t* record, uint8_t id, uint8_t opt)
{
	static uint8_t toggleGrv = 0;
	
	// Grave toggle off:
	//  Escape by default, grave when FN layer is active.
	//  Grave whenever shift is held except for when control is also held.
	// Grave toggle on:
	//  Grave by default, escape when FN layer is active.
	
	if (id == F_ESC_GRV)
	{
		static uint8_t keyPressed = KC_NO;
		
		if (record->event.pressed)
		{
			if (layer_state & (1 << L_FUNC))
			{
				keyPressed = toggleGrv ? KC_ESC : KC_GRV;
			}
			else
			{
				if (toggleGrv)
				{
					keyPressed = toggleGrv ? KC_GRV : KC_ESC;
				}
				else
				{
					uint8_t modState = get_mods();
					uint8_t shiftState =
						 (modState & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT))) &&
						!(modState & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)));
					keyPressed = shiftState ? KC_GRV : KC_ESC;
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
	else
	if (id == F_TOGGLE_GRV)
	{
		if (record->event.pressed)
		{
			toggleGrv = !toggleGrv;
			DDRB |= (1<<7);
			if (toggleGrv)
			{
				PORTB |= (1<<7);
			}
			else
			{
				PORTB &= ~(1<<7);
			}
		}
	}
}
