/* keymap_filco.c - grandpad - (C) a dinosaur 2023 */
/* Replicates FILCO Majestouch TenKeyPad 2 Professional behaviour */

#include "keymap_common.h"
#include "light_ws2812.h"
#include "led.h"


/////////////////////
/// Layer definitions
enum layer_id
{
	LAYER_BASE,  // Layer 0: Base layer

	NUM_LAYERS
};

const uint8_t keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] KEYMAP_SECTION =
{
	[LAYER_BASE] = KEYMAP(
		ESC, TAB, FN13,BSPC,
		FN12,PSLS,PAST,PMNS,
		FN7, FN8, FN9, PPLS,
		FN4, FN5, FN6, NO,
		FN1, FN2, FN3, NO,
		FN0, FN10,FN11,PENT)
};


//////////////////
/// Advanced logic
enum action_id
{
	ACTION_VIRTUAL_NUMLOCK,
	ACTION_DOUBLEZERO,

	ACTION_ZERO_INSERT,
	ACTION_ONE_END,
	ACTION_TWO_DOWN,
	ACTION_THREE_PGDN,
	ACTION_FOUR_LEFT,
	ACTION_FIVE,
	ACTION_SIX_RIGHT,
	ACTION_SEVEN_HOME,
	ACTION_EIGHT_UP,
	ACTION_NINE_PGUP,
	ACTION_PERIOD_DEL,

	FIRST_KP_ACTION = ACTION_ZERO_INSERT,
	LAST_KP_ACTION = ACTION_PERIOD_DEL,
	KP_ACTIONS_LENGTH = LAST_KP_ACTION + 1 - FIRST_KP_ACTION
};

static volatile bool real_numlock = false, virt_numlock = true;
static volatile uint8_t numlock_toggle_held = 0;
static volatile uint8_t kp_pressed[KP_ACTIONS_LENGTH];
void led_rgb_update(void);

void hook_late_init(void)
{
	for (uint8_t i = 0; i < KP_ACTIONS_LENGTH; ++i)
		kp_pressed[i] = KC_NO;
	led_rgb_update();
}


////////////////////
/// Macro defintions
enum macro_id
{
	MACRO_EQUALS,
	MACRO_DOUBLEZERO
};

//TODO: fold this stuff into actions
const macro_t* action_get_macro(keyrecord_t* record, uint8_t id, uint8_t opt)
{
	if (id == MACRO_EQUALS || id == MACRO_DOUBLEZERO)
	{
		if (id == MACRO_DOUBLEZERO && !virt_numlock) return MACRO_NONE;
		if (record->event.pressed)
		{
			const macro_t* macro;
			if (numlock_toggle_held || real_numlock)
				macro = id == MACRO_EQUALS
					? MACRO(D(LALT), T(KP_6), T(KP_1), U(LALT), END)
					: MACRO(T(P0), T(P0), END);
			else
				macro = id == MACRO_EQUALS
					? MACRO(T(NUMLOCK), D(LALT), T(KP_6), T(KP_1), U(LALT), END)
					: MACRO(T(NUMLOCK), T(KP_0), T(KP_0), END);
			if (!real_numlock || numlock_toggle_held)
				++numlock_toggle_held;
			return macro;
		}
		else if (numlock_toggle_held && --numlock_toggle_held == 0)
		{
			return MACRO(T(NUMLOCK), END);
		}
	}

	return MACRO_NONE;
}


/////////////////////////////////
/// Function & action definitions
enum function_id
{
	FN0_ZERO_INSERT,
	FN1_ONE_END,
	FN2_TWO_DOWN,
	FN3_THREE_PGDN,
	FN4_FOUR_LEFT,
	FN5_FIVE,
	FN6_SIX_RIGHT,
	FN7_SEVEN_HOME,
	FN8_EIGHT_UP,
	FN9_NINE_PGUP,
	FN10_DOUBLEZERO,
	FN11_PERIOD_DEL,
	FN12_VIRTUAL_NUMLOCK,
	FN13_EQUALS,

	NUM_FUNCTIONS
};

const action_t PROGMEM fn_actions[NUM_FUNCTIONS] ACTION_SECTION =
{
	[FN0_ZERO_INSERT]      = ACTION_FUNCTION(ACTION_ZERO_INSERT),
	[FN1_ONE_END]          = ACTION_FUNCTION(ACTION_ONE_END),
	[FN2_TWO_DOWN]         = ACTION_FUNCTION(ACTION_TWO_DOWN),
	[FN3_THREE_PGDN]       = ACTION_FUNCTION(ACTION_THREE_PGDN),
	[FN4_FOUR_LEFT]        = ACTION_FUNCTION(ACTION_FOUR_LEFT),
	[FN5_FIVE]             = ACTION_FUNCTION(ACTION_FIVE),
	[FN6_SIX_RIGHT]        = ACTION_FUNCTION(ACTION_SIX_RIGHT),
	[FN7_SEVEN_HOME]       = ACTION_FUNCTION(ACTION_SEVEN_HOME),
	[FN8_EIGHT_UP]         = ACTION_FUNCTION(ACTION_EIGHT_UP),
	[FN9_NINE_PGUP]        = ACTION_FUNCTION(ACTION_NINE_PGUP),
	[FN10_DOUBLEZERO]      = ACTION_MACRO(MACRO_DOUBLEZERO),
	[FN11_PERIOD_DEL]      = ACTION_FUNCTION(ACTION_PERIOD_DEL),
	[FN12_VIRTUAL_NUMLOCK] = ACTION_FUNCTION(ACTION_VIRTUAL_NUMLOCK),
	[FN13_EQUALS]          = ACTION_MACRO(MACRO_EQUALS)
};

void action_function(keyrecord_t* record, uint8_t id, uint8_t opt)
{
	static const uint8_t numpad_key_lut[KP_ACTIONS_LENGTH][2] =
	{
		{ KC_KP_0, KC_INSERT },
		{ KC_KP_1, KC_END },
		{ KC_KP_2, KC_DOWN },
		{ KC_KP_3, KC_PGDOWN },
		{ KC_KP_4, KC_LEFT },
		{ KC_KP_5, KC_NO },
		{ KC_KP_6, KC_RIGHT },
		{ KC_KP_7, KC_HOME },
		{ KC_KP_8, KC_UP },
		{ KC_KP_9, KC_PGUP },
		{ KC_KP_DOT, KC_DELETE }
	};

	if (id == ACTION_VIRTUAL_NUMLOCK)
	{
		if (record->event.pressed)
		{
			virt_numlock = !virt_numlock;
			led_rgb_update();
		}
	}
	else if (id >= FIRST_KP_ACTION && id <= LAST_KP_ACTION)
	{
		const uint8_t key_id = id - FIRST_KP_ACTION;
		if (record->event.pressed)
		{
			const uint8_t pressed = numpad_key_lut[key_id][!virt_numlock && real_numlock];
			if (IS_KEY(pressed))
			{
				if (numlock_toggle_held || (!real_numlock && virt_numlock))
				{
					if (numlock_toggle_held++ == 0)
					{
						register_code(KC_NUMLOCK);
						unregister_code(KC_NUMLOCK);
					}
				}
				register_code(pressed);
				kp_pressed[key_id] = pressed;
			}
		}
		else if (IS_KEY(kp_pressed[key_id]))
		{
			const uint8_t release_key = kp_pressed[key_id];
			kp_pressed[key_id] = KC_NO;
			if (numlock_toggle_held && --numlock_toggle_held == 0)
			{
				register_code(KC_NUMLOCK);
				unregister_code(KC_NUMLOCK);
			}
			unregister_code(release_key);
			send_keyboard_report();
		}
	}
}


////////////////////
/// RGB LED handling
void led_rgb_update(void)
{
	//FIXME: why is this RBG?
	struct cRGB colour = { 0x00, virt_numlock ? 0x2F : 0x00, 0x00 };
	ws2812_setleds(&colour, 1);
}

void led_set_user(uint8_t state)
{
	const bool new_state = (state & _BV(USB_LED_NUM_LOCK)) == _BV(USB_LED_NUM_LOCK);
	if (new_state != real_numlock)
		real_numlock = new_state;
}
