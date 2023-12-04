/* keymap_npkc.c - grandpad - (c) a dinosaur 2017, 2023 */

#include "keymap_common.h"
#include "light_ws2812.h"


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
		NO,  NO,  NO,  NO,
		NO,  NO,  NO,  /**/
		NO,  NO,  NO,  /**/
		NO,  /**/ BTLD,NO  )
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
struct cRGB led_rgb_numlock_on = { 6, 38, 21 };
