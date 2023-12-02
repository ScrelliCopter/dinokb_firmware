#include "grandpad.h"

#define L_BS 0
#define L_FN 1

#define M_D0 0
#define M_T0 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[L_BS] = KEYMAP ( \
		KC_ESC, KC_TAB, KC_PEQL,KC_BSPC, \
		KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS, \
		KC_P7,  KC_P8,  KC_P9,  KC_PPLS, \
		KC_P4,  KC_P5,  KC_P6,  KC_FN0,  \
		KC_P1,  KC_P2,  KC_P3,  KC_PEQL, \
		KC_P0,  KC_FN1, KC_PDOT,KC_PENT  ),

	[L_FN] = KEYMAP ( \
		KC_NO,  KC_NO,  KC_NO,  KC_NO,   \
		RESET,  KC_NO,  KC_NO,  KC_NO,   \
		KC_LBRC,KC_RBRC,KC_NO,  KC_NO,   \
		KC_NO,  KC_NO,  KC_NO,  KC_TRNS, \
		KC_NO,  KC_NO,  KC_NO,  KC_NO,   \
		KC_NO,  KC_FN2, KC_NO,  KC_NO    ),
};

const uint16_t PROGMEM fn_actions[] = {
	[0] = ACTION_LAYER_MOMENTARY(L_FN),
	[1] = ACTION_MACRO(M_D0),
	[2] = ACTION_MACRO(M_T0)
};

const macro_t* action_get_macro(keyrecord_t* record, uint8_t id, uint8_t opt)
{
	if (record->event.pressed) {
		switch (id) {
			case M_D0:
				return MACRO(T(P0), T(P0), END);
			case M_T0:
				return MACRO(T(P0), T(P0), T(P0), END);
				
			default:
				break;
		}
	}
	
	return MACRO_NONE;
}

void led_set_user(uint8_t usb_led)
{
	uint8_t dat[] = {
		(usb_led & (1 << USB_LED_CAPS_LOCK))   ? 0x2F : 0x00,
		(usb_led & (1 << USB_LED_NUM_LOCK))    ? 0x2F : 0x00,
		(usb_led & (1 << USB_LED_SCROLL_LOCK)) ? 0x2F : 0x00
	};
	ws2812_setleds((LED_TYPE*)&dat, 1);
}
