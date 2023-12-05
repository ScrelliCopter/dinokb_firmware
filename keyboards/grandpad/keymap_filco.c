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


////////////////
/// Action setup
enum action_id
{
	ACTION_VIRTUAL_NUMLOCK,

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
	ACTION_DOUBLEZERO,
	ACTION_EQUALS,

	FIRST_KP_ACTION = ACTION_ZERO_INSERT,
	LAST_KP_ACTION = ACTION_EQUALS,
	KP_ACTIONS_LENGTH = LAST_KP_ACTION + 1 - FIRST_KP_ACTION
};

static volatile uint8_t kp_action_down[KP_ACTIONS_LENGTH];

void led_rgb_update(void);

void hook_late_init(void)
{
	for (uint8_t i = 0; i < KP_ACTIONS_LENGTH; ++i)
		kp_action_down[i] = KC_NO;
	led_rgb_update();
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
	[FN10_DOUBLEZERO]      = ACTION_FUNCTION(ACTION_DOUBLEZERO),
	[FN11_PERIOD_DEL]      = ACTION_FUNCTION(ACTION_PERIOD_DEL),
	[FN12_VIRTUAL_NUMLOCK] = ACTION_FUNCTION(ACTION_VIRTUAL_NUMLOCK),
	[FN13_EQUALS]          = ACTION_FUNCTION(ACTION_EQUALS)
};

static volatile bool real_numlock = false, virt_numlock = true;

void keypad_function(keyrecord_t* record, uint8_t id)
{
	volatile static uint16_t kp_action_nlcktoggle = 0ul;

	const uint8_t kpid = id - FIRST_KP_ACTION;
	const uint16_t kpid_bit = 1ul << kpid;

	if (record->event.pressed)
	{
		const bool use_nav = !virt_numlock && real_numlock;

		uint8_t key = KC_NO;
		const macro_t* macro = MACRO_NONE;
		switch (id)
		{
		case ACTION_ZERO_INSERT: key = use_nav ? KC_INSERT : KC_KP_0; break;
		case ACTION_ONE_END:     key = use_nav ? KC_END : KC_KP_1; break;
		case ACTION_TWO_DOWN:    key = use_nav ? KC_DOWN : KC_KP_2; break;
		case ACTION_THREE_PGDN:  key = use_nav ? KC_PGDOWN : KC_KP_3; break;
		case ACTION_FOUR_LEFT:   key = use_nav ? KC_LEFT : KC_KP_4; break;
		case ACTION_FIVE:        key = use_nav ? KC_NO : KC_KP_5; break;
		case ACTION_SIX_RIGHT:   key = use_nav ? KC_RIGHT : KC_KP_6; break;
		case ACTION_SEVEN_HOME:  key = use_nav ? KC_HOME : KC_KP_7; break;
		case ACTION_EIGHT_UP:    key = use_nav ? KC_UP : KC_KP_8; break;
		case ACTION_NINE_PGUP:   key = use_nav ? KC_PGUP : KC_KP_9; break;
		case ACTION_PERIOD_DEL:  key = use_nav ? KC_DELETE : KC_KP_DOT; break;
		case ACTION_DOUBLEZERO:  macro = virt_numlock ? MACRO(T(P0), T(P0), END) : MACRO_NONE; break;
		case ACTION_EQUALS:      macro = MACRO(D(LALT), T(KP_6), T(KP_1), U(LALT), END); break;
		default: break;
		}

		if (IS_KEY(key) || macro != MACRO_NONE)
		{
			if (kp_action_nlcktoggle || (!real_numlock && virt_numlock))
			{
				if (!kp_action_nlcktoggle)
				{
					register_code(KC_NUMLOCK);
					unregister_code(KC_NUMLOCK);
					//FIXME: do we need a delay after this?
				}
				kp_action_nlcktoggle |= kpid_bit;
			}

			if (IS_KEY(key))
				register_code(kp_action_down[kpid] = key);
			if (macro != MACRO_NONE)
				action_macro_play(macro);
		}
	}
	else
	{
		if (kp_action_nlcktoggle)
		{
			kp_action_nlcktoggle &= ~kpid_bit;
			if (!kp_action_nlcktoggle)
			{
				register_code(KC_NUMLOCK);
				unregister_code(KC_NUMLOCK);
			}
		}

		if (IS_KEY(kp_action_down[kpid]))
		{
			unregister_code(kp_action_down[kpid]);
			kp_action_down[kpid] = KC_NO;
		}
	}
}

void action_function(keyrecord_t* record, uint8_t id, uint8_t opt)
{
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
		keypad_function(record, id);
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
	//TODO: check if host toggling real numlock off should clear kp_action_nlcktoggle
}
