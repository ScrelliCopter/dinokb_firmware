/* keymap_tk.c - grandpad - (c) a dinosaur 2017, 2023 */

#include "keymap_common.h"
#include "light_ws2812.h"
#include "bootloader.h"
#include "led.h"
#include "wait.h"


/////////////////////
/// Layer definitions
enum layer_id
{
	LAYER_BASE,      // Layer 0: Base layer
	LAYER_TK,        // Layer 1: Tenkey layer
	LAYER_MOUSE,     // Layer 2: Mouse layer
	LAYER_FUNCTION,  // Layer 3: Function layer

	NUM_LAYERS
};

const uint8_t keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] KEYMAP_SECTION =
{
	[LAYER_BASE] = KEYMAP(
		ESC, FN0, TAB, BSPC,
		NLCK,PSLS,PAST,PMNS,
		P7,  P8,  P9,  PPLS,
		P4,  P5,  P6,  NO,
		P1,  P2,  P3,  NO,
		P0,  FN4, PDOT,PENT),
	[LAYER_TK] = KEYMAP(
		ESC, TRNS,NO,  NO,
		PSCR,SLCK,PAUS,NO,
		INS, HOME,PGUP,NO,
		DEL, END, PGDN,NO,
		NO,  UP,  NO,  NO,
		LEFT,DOWN,RGHT,FN2 ),
	[LAYER_MOUSE] = KEYMAP(
		NO,  NO,  NO,  NO,
		NO,  NO,  NO,  NO,
		NO,  MS_U,NO,  NO,
		MS_L,BTN1,MS_R,NO,
		NO,  MS_D,NO,  NO,
		BTN2,NO,  NO,  TRNS),
	[LAYER_FUNCTION] = KEYMAP(
		FN3, TRNS,NO,  NO,
		FN1, NO,  NO,  NO,
		NO,  NO,  NO,  NO,
		NO,  NO,  NO,  NO,
		NO,  NO,  NO,  NO,
		NO,  NO,  NO,  NO  ),
};


////////////////////
/// Macro defintions
enum macro_id
{
	MACRO_DOUBLEZERO
};

const macro_t* action_get_macro(keyrecord_t* record, uint8_t id, uint8_t opt)
{
	switch (id)
	{
	case MACRO_DOUBLEZERO: return record->event.pressed ? MACRO(T(P0), T(P0), END) : MACRO_NONE;
	default: return MACRO_NONE;
	}
}


/////////////////////////////////
/// Function & action definitions
enum function_id
{
	FN0_LAYER_FUNCTION,
	FN1_LAYER_TK,
	FN2_LAYER_MOUSE,
	FN3_FUNCTION_BOOTLOADER,
	FN4_MACRO_DOUBLEZERO,

	NUM_FUNCTIONS
};

enum action_id
{
	ACTION_BOOTLOADER
};

const action_t fn_actions[NUM_FUNCTIONS] ACTION_SECTION =
{
	[FN0_LAYER_FUNCTION] = ACTION_LAYER_MOMENTARY(LAYER_FUNCTION),
	[FN1_LAYER_TK]       = ACTION_LAYER_TOGGLE(LAYER_TK),
	[FN2_LAYER_MOUSE]    = ACTION_LAYER_MOMENTARY(LAYER_MOUSE),

	[FN3_FUNCTION_BOOTLOADER] = ACTION_FUNCTION(ACTION_BOOTLOADER),

	[FN4_MACRO_DOUBLEZERO] = ACTION_MACRO(MACRO_DOUBLEZERO)
};

void action_function(keyrecord_t* record, uint8_t id, uint8_t opt)
{
	if (id == ACTION_BOOTLOADER)
	{
		clear_keyboard();  // Stop pressing keys
		// LED fadeout animation (for shits and giggles)
		for (int i = 256; i > 0x00; i -= 2)
		{
			const uint8_t val = i - 1;
			ws2812_setleds(&(struct cRGB){ val, val, val }, 1);
			wait_ms(5);
		}
		ws2812_setleds(&(struct cRGB){ 0x00, 0x00, 0x00 }, RGBLED_NUM);  // Disable led(s)
		//wait_ms(50);
		bootloader_jump();  // Reset
	}
}


////////////////////
/// RGB LED handling
static struct cRGB led_rgb_normal  = { 0x0F, 0x0F, 0x0F };
static struct cRGB led_rgb_nlck    = { 0x3F, 0x17, 0x0F };
static struct cRGB led_rgb_tk      = { 0x0F, 0x3F, 0x0F };
static struct cRGB led_rgb_tk_slck = { 0x0F, 0x2F, 0x2F };
static struct cRGB led_rgb_mouse   = { 0x0F, 0x17, 0x3F };

static uint32_t rgb_layerstate = 0;
static uint8_t rgb_ledstate = 0xFF;

static void led_rgb_update(void)
{
	if (rgb_layerstate & (1UL << LAYER_TK))
	{
		if (rgb_layerstate & (1UL << LAYER_MOUSE))
			ws2812_setleds(&led_rgb_mouse, 1);
		else
			ws2812_setleds(rgb_ledstate & _BV(USB_LED_SCROLL_LOCK)
				? &led_rgb_tk_slck
				: &led_rgb_tk, 1);
	}
	else
	{
		ws2812_setleds(rgb_ledstate & _BV(USB_LED_NUM_LOCK) ?
			&led_rgb_nlck :
			&led_rgb_normal, 1);
	}
}

void hook_layer_change(uint32_t layer_state)
{
	if (layer_state != rgb_layerstate)
	{
		rgb_layerstate = layer_state;
		led_rgb_update();
	}
}

void led_set_user(uint8_t state)
{
	if (state != rgb_ledstate)
	{
		rgb_ledstate = state;
		led_rgb_update();
	}
}
