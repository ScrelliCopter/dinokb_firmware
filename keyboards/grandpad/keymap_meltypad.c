/* keymap_meltypad.c - grandpad - (c) a dinosaur 2017, 2023 */

#include "keymap_common.h"
#include "light_ws2812.h"
#include "led.h"


/////////////////////
/// Layer definitions
enum layer_id
{
	LAYER_BASE,      // Layer 0: Base layer
	LAYER_FUNCTION,  // Layer 1: Function layer

	NUM_LAYERS
};

const uint8_t keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] KEYMAP_SECTION =
{
	[LAYER_BASE] = KEYMAP_K17(
		FN0, PSLS,PAST,PMNS,
		P7,  P8,  P9,  PPLS,
		P4,  P5,  P6,  /**/
		P1,  P2,  P3,  /**/
		P0,  /**/ PDOT,PENT),
		
	[LAYER_FUNCTION] = KEYMAP_K17(
		TRNS,ESC, TAB, BSPC,
		BTLD,NO,  NO,  NO,
		NO,  NO,  NO,  /**/
		NO,  NO,  NO,  /**/
		NO,  /**/ NO,  NO  )
};


/////////////////////////////////
/// Function & action definitions
enum function_id
{
	FN0_LAYER_FUNCTION,

	NUM_FUNCTIONS
};

const action_t PROGMEM fn_actions[NUM_FUNCTIONS] ACTION_SECTION =
{
	[FN0_LAYER_FUNCTION] = ACTION_LAYER_TAP_KEY(LAYER_FUNCTION, KC_NUMLOCK)
};


////////////////////
/// RGB LED handling
void led_set_user(uint8_t state)
{
	ws2812_setleds(&(struct cRGB){
		.r = state & (1 << USB_LED_CAPS_LOCK)   ? 0x2F : 0x00,
		.g = state & (1 << USB_LED_NUM_LOCK)    ? 0x2F : 0x00,
		.b = state & (1 << USB_LED_SCROLL_LOCK) ? 0x2F : 0x00
	}, 1);
}
