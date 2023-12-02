/* grandpad - (c) a dinosaur 2017 */

#include "grandpad.h"

#define BASE 0
#define HOLD 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{
	[BASE] = KEYMAP_K17 ( \
		KC_FN0, KC_PSLS,KC_PAST,KC_PMNS, \
		KC_P7,  KC_P8,  KC_P9,  KC_PPLS, \
		KC_P4,  KC_P5,  KC_P6,  /**/     \
		KC_P1,  KC_P2,  KC_P3,  /**/     \
		KC_P0,  /**/    KC_PDOT,KC_PENT  ),
		
	[HOLD] = KEYMAP_K17 ( \
		KC_TRNS,KC_ESC, KC_TAB, KC_BSPC, \
		RESET,  KC_NO,  KC_NO,  KC_NO,   \
		KC_NO,  KC_NO,  KC_NO,  /**/     \
		KC_NO,  KC_NO,  KC_NO,  /**/     \
		KC_NO,  /**/    KC_NO,  KC_NO    ),
};

const uint16_t PROGMEM fn_actions[] =
{
	[0] = ACTION_LAYER_TAP_KEY(1, KC_NLCK)
};

void led_set_user(uint8_t usb_led)
{
	ledState = usb_led;

	uint8_t dat[] =
	{
		( usb_led & ( 1 << USB_LED_CAPS_LOCK ) )
			? 0x2F : 0x00,
		( usb_led & ( 1 << USB_LED_NUM_LOCK ) )
			? 0x2F : 0x00,
		(usb_led & ( 1 << USB_LED_SCROLL_LOCK ) )
			? 0x2F : 0x00
	};
	ws2812_setleds ( (LED_TYPE*)&dat, 1 );
}
