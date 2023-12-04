/* keymap_filco.c - grandpad - (C) a dinosaur 2023 */
/* Replicates FILCO Majestouch TenKeyPad 2 Professional behaviour */

//FIXME: Replace incomplete macro based implementation

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


////////////////////
/// Macro defintions
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

static bool real_numlock = false, virt_numlock = true;
void led_rgb_update(void);

void hook_late_init(void)
{
	led_rgb_update();
}

const macro_t* action_get_macro(keyrecord_t* record, uint8_t id, uint8_t opt)
{
	if (id == FN13_EQUALS)
	{
		if (real_numlock)
			return record->event.pressed ? MACRO(D(LALT), T(KP_6), T(KP_1), U(LALT)) : MACRO_NONE;
		else
			return record->event.pressed ? MACRO(T(NUMLOCK), D(LALT), T(KP_6), T(KP_1), U(LALT), END) : MACRO(T(NUMLOCK), END);
	}
	if (id == FN12_VIRTUAL_NUMLOCK)
	{
		if (record->event.pressed)
		{
			virt_numlock = !virt_numlock;
			led_rgb_update();
		}
		return MACRO_NONE;
	}

	const bool p = record->event.pressed;
	if (virt_numlock)
	{
		if (real_numlock)
		{
			switch(id)
			{
			case (FN0_ZERO_INSERT): return p ? MACRO(D(P0), END) : MACRO(U(P0), END);
			case (FN1_ONE_END):     return p ? MACRO(D(P1), END) : MACRO(U(P1), END);
			case (FN2_TWO_DOWN):    return p ? MACRO(D(P2), END) : MACRO(U(P2), END);
			case (FN3_THREE_PGDN):  return p ? MACRO(D(P3), END) : MACRO(U(P3), END);
			case (FN4_FOUR_LEFT):   return p ? MACRO(D(P4), END) : MACRO(U(P4), END);
			case (FN5_FIVE):        return p ? MACRO(D(P5), END) : MACRO(U(P5), END);
			case (FN6_SIX_RIGHT):   return p ? MACRO(D(P6), END) : MACRO(U(P6), END);
			case (FN7_SEVEN_HOME):  return p ? MACRO(D(P7), END) : MACRO(U(P7), END);
			case (FN8_EIGHT_UP):    return p ? MACRO(D(P8), END) : MACRO(U(P8), END);
			case (FN9_NINE_PGUP):   return p ? MACRO(D(P9), END) : MACRO(U(P9), END);
			case (FN10_DOUBLEZERO): return p ? MACRO(T(P0), T(P0), END) : MACRO_NONE;
			case (FN11_PERIOD_DEL): return p ? MACRO(D(PDOT), END) : MACRO(U(PDOT), END);
			default: return MACRO_NONE;
			}
		}
		else
		{
			switch(id)
			{
			case (FN0_ZERO_INSERT): return p ? MACRO(T(NUMLOCK), D(P0), END) : MACRO(T(NUMLOCK), U(P0), END);
			case (FN1_ONE_END):     return p ? MACRO(T(NUMLOCK), D(P1), END) : MACRO(T(NUMLOCK), U(P1), END);
			case (FN2_TWO_DOWN):    return p ? MACRO(T(NUMLOCK), D(P2), END) : MACRO(T(NUMLOCK), U(P2), END);
			case (FN3_THREE_PGDN):  return p ? MACRO(T(NUMLOCK), D(P3), END) : MACRO(T(NUMLOCK), U(P3), END);
			case (FN4_FOUR_LEFT):   return p ? MACRO(T(NUMLOCK), D(P4), END) : MACRO(T(NUMLOCK), U(P4), END);
			case (FN5_FIVE):        return p ? MACRO(T(NUMLOCK), D(P5), END) : MACRO(T(NUMLOCK), U(P5), END);
			case (FN6_SIX_RIGHT):   return p ? MACRO(T(NUMLOCK), D(P6), END) : MACRO(T(NUMLOCK), U(P6), END);
			case (FN7_SEVEN_HOME):  return p ? MACRO(T(NUMLOCK), D(P7), END) : MACRO(T(NUMLOCK), U(P7), END);
			case (FN8_EIGHT_UP):    return p ? MACRO(T(NUMLOCK), D(P8), END) : MACRO(T(NUMLOCK), U(P8), END);
			case (FN9_NINE_PGUP):   return p ? MACRO(T(NUMLOCK), D(P9), END) : MACRO(T(NUMLOCK), U(P9), END);
			case (FN10_DOUBLEZERO): return p ? MACRO(T(NUMLOCK), T(P0), T(P0), END) : MACRO(T(NUMLOCK), END);
			case (FN11_PERIOD_DEL): return p ? MACRO(T(NUMLOCK), D(PDOT), END) : MACRO(T(NUMLOCK), U(PDOT), END);
			default: return MACRO_NONE;
			}
		}
	}
	else
	{
		if (!real_numlock)
		{
			switch(id)
			{
			case (FN0_ZERO_INSERT): return p ? MACRO(D(P0), END) : MACRO(U(P0), END);
			case (FN1_ONE_END):     return p ? MACRO(D(P1), END) : MACRO(U(P1), END);
			case (FN2_TWO_DOWN):    return p ? MACRO(D(P2), END) : MACRO(U(P2), END);
			case (FN3_THREE_PGDN):  return p ? MACRO(D(P3), END) : MACRO(U(P3), END);
			case (FN4_FOUR_LEFT):   return p ? MACRO(D(P4), END) : MACRO(U(P4), END);
			case (FN5_FIVE):        return p ? MACRO(D(P5), END) : MACRO(U(P5), END);
			case (FN6_SIX_RIGHT):   return p ? MACRO(D(P6), END) : MACRO(U(P6), END);
			case (FN7_SEVEN_HOME):  return p ? MACRO(D(P7), END) : MACRO(U(P7), END);
			case (FN8_EIGHT_UP):    return p ? MACRO(D(P8), END) : MACRO(U(P8), END);
			case (FN9_NINE_PGUP):   return p ? MACRO(D(P9), END) : MACRO(U(P9), END);
			case (FN11_PERIOD_DEL): return p ? MACRO(D(PDOT), END) : MACRO(U(PDOT), END);
			default: return MACRO_NONE;
			}
		}
		else
		{
			switch(id)
			{
			case (FN0_ZERO_INSERT): return p ? MACRO(D(INSERT), END) : MACRO(U(INSERT), END);
			case (FN1_ONE_END):     return p ? MACRO(D(END), END) : MACRO(U(END), END);
			case (FN2_TWO_DOWN):    return p ? MACRO(D(DOWN), END) : MACRO(U(DOWN), END);
			case (FN3_THREE_PGDN):  return p ? MACRO(D(PGDOWN), END) : MACRO(U(PGDOWN), END);
			case (FN4_FOUR_LEFT):   return p ? MACRO(D(LEFT), END) : MACRO(U(LEFT), END);
			case (FN6_SIX_RIGHT):   return p ? MACRO(D(RIGHT), END) : MACRO(U(RIGHT), END);
			case (FN7_SEVEN_HOME):  return p ? MACRO(D(HOME), END) : MACRO(U(HOME), END);
			case (FN8_EIGHT_UP):    return p ? MACRO(D(UP), END) : MACRO(U(UP), END);
			case (FN9_NINE_PGUP):   return p ? MACRO(D(PGUP), END) : MACRO(U(PGUP), END);
			case (FN11_PERIOD_DEL): return p ? MACRO(D(DELETE), END) : MACRO(U(DELETE), END);
			default: return MACRO_NONE;
			}
		}
	}
}


/////////////////////////////////
/// Function & action definitions
const action_t PROGMEM fn_actions[NUM_FUNCTIONS] ACTION_SECTION =
{
	[FN0_ZERO_INSERT]      = ACTION_MACRO(FN0_ZERO_INSERT),
	[FN1_ONE_END]          = ACTION_MACRO(FN1_ONE_END),
	[FN2_TWO_DOWN]         = ACTION_MACRO(FN2_TWO_DOWN),
	[FN3_THREE_PGDN]       = ACTION_MACRO(FN3_THREE_PGDN),
	[FN4_FOUR_LEFT]        = ACTION_MACRO(FN4_FOUR_LEFT),
	[FN5_FIVE]             = ACTION_MACRO(FN5_FIVE),
	[FN6_SIX_RIGHT]        = ACTION_MACRO(FN6_SIX_RIGHT),
	[FN7_SEVEN_HOME]       = ACTION_MACRO(FN7_SEVEN_HOME),
	[FN8_EIGHT_UP]         = ACTION_MACRO(FN8_EIGHT_UP),
	[FN9_NINE_PGUP]        = ACTION_MACRO(FN9_NINE_PGUP),
	[FN10_DOUBLEZERO]      = ACTION_MACRO(FN10_DOUBLEZERO),
	[FN11_PERIOD_DEL]      = ACTION_MACRO(FN11_PERIOD_DEL),
	[FN12_VIRTUAL_NUMLOCK] = ACTION_MACRO(FN12_VIRTUAL_NUMLOCK),
	[FN13_EQUALS]          = ACTION_MACRO(FN13_EQUALS)
};


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
