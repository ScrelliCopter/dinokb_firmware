#include "clueboard.h"
#include "keymap_common.h"


//#define GRAVE_ESC_ALT_OVERRIDE
//#define GRAVE_ESC_CTRL_OVERRIDE
//#define GRAVE_ESC_GUI_OVERRIDE
//#define GRAVE_ESC_SHIFT_OVERRIDE


/////////////////////
/// Layer definitions
enum layer_id
{
	LAYER_BASE,     // 0: Base layer
	LAYER_FUNCTION, // 1: Function layer
	LAYER_CONTROL,  // 2: Control layer
	NUM_LAYERS
};

//FIXME: Control layer sticks when FN is released first
const uint8_t KEYMAP_SECTION keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] =
{
	[LAYER_BASE] = KEYMAP(
		FN2, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, GRV, BSPC,     PGUP, \
		TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,          PGDN, \
		CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,NUHS,ENT,                 \
		LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RO,  RSFT,     UP,        \
		LCTL,LGUI,LALT,MHEN,     SPC, SPC,                HENK,RALT,FN0, RCTL,LEFT,DOWN,RGHT  ),
	[LAYER_FUNCTION] = KEYMAP(
		GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, TRNS,DEL,      VOLU, \
		TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,MPRV,MPLY,MNXT,TRNS,MUTE,          VOLD, \
		TRNS,TRNS,FN1, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,                \
		TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,FN0,      PGUP,      \
		TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,               TRNS,TRNS,TRNS,TRNS,HOME,PGDN,END   ),
	[LAYER_CONTROL] = KEYMAP(
		FN3, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     FN4,  \
		TRNS,TRNS,TRNS,TRNS,BTLD,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,          TRNS, \
		TRNS,TRNS,FN1, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,                \
		FN0, TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,TRNS,     TRNS,      \
		TRNS,TRNS,TRNS,TRNS,     TRNS,TRNS,               TRNS,TRNS,FN0, TRNS,TRNS,TRNS,TRNS  )
};


/////////////////////////////////
/// Function & action definitions
enum function_id
{
	FN0_FUNCTION_LAYER,
	FN1_CONTROL_LAYER,

	FN2_ESCAPE_GRAVE,

	FN3_BACKLIGHT_STEP,
	FN4_BACKLIGHT_TOGGLE,
	NUM_FUNCTIONS
};

enum action_id
{
	ACTION_ESCAPE_GRAVE
};

const action_t PROGMEM fn_actions[] =
{
	[FN0_FUNCTION_LAYER] = ACTION_LAYER_MOMENTARY(LAYER_FUNCTION),
	[FN1_CONTROL_LAYER]  = ACTION_LAYER_MOMENTARY(LAYER_CONTROL),

	[FN2_ESCAPE_GRAVE] = ACTION_FUNCTION(ACTION_ESCAPE_GRAVE),

	[FN3_BACKLIGHT_STEP]   = ACTION_BACKLIGHT_STEP(),
	[FN4_BACKLIGHT_TOGGLE] = ACTION_BACKLIGHT_TOGGLE()
};

void action_function(keyrecord_t* record, uint8_t id, uint8_t opt)
{
	if (id == ACTION_ESCAPE_GRAVE)
	{
		static uint8_t keyPressed = KC_NO;
		if (record->event.pressed)
		{
			uint8_t escMod = 0;
#ifdef GRAVE_ESC_ALT_OVERRIDE
			escMod |= MOD_LALT | MOD_RALT;
#endif
#ifdef GRAVE_ESC_CTRL_OVERRIDE
			escMod |= MOD_LCTL | MOD_RCTL;
#endif
#ifdef GRAVE_ESC_GUI_OVERRIDE
			escMod |= MOD_LGUI | MOD_RGUI;
#endif
#ifdef GRAVE_ESC_SHIFT_OVERRIDE
			escMod |= MOD_LSFT | MOD_RSFT;
#endif
			const uint8_t graveMod = MOD_LSFT | MOD_RSFT | MOD_LGUI | MOD_RGUI;
			const uint8_t modState = get_mods();
			keyPressed = (modState & graveMod) && !(modState & escMod) ? KC_GRAVE : KC_ESCAPE;
			register_code(keyPressed);
		}
		else
		{
			unregister_code(keyPressed);
			keyPressed = KC_NO;
		}
		send_keyboard_report();
	}
}


/////////////
/// backlight
#ifdef BACKLIGHT_ENABLE
void backlight_set(uint8_t level)
{
	//TODO: test arrow & escape patterns
	static const clue_led_state patterns[] =
	{
		0,
		CLUE_LED_MASK(CLUE_LED_ESCAPE) | CLUE_LED_MASK(CLUE_LED_INSERT) | CLUE_LED_MASK(CLUE_LED_ARROWS),
		CLUE_LED_MASK(CLUE_LED_ARROWS),
		CLUE_LED_MASK(CLUE_LED_INSERT),
		CLUE_LED_MASK(CLUE_LED_ESCAPE),
		CLUE_LED_MASK(CLUE_LED_ARROWS) | CLUE_LED_MASK(CLUE_LED_INSERT),
		CLUE_LED_MASK(CLUE_LED_INSERT) | CLUE_LED_MASK(CLUE_LED_ESCAPE),
		CLUE_LED_MASK(CLUE_LED_ESCAPE) | CLUE_LED_MASK(CLUE_LED_ARROWS)
	};
	if (level < sizeof(patterns) / sizeof(clue_led_state))
		clue_led_set(patterns[level]);
}
#endif
