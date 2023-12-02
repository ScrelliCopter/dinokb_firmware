#include "grandpad.h"

// Layers
#define L_BS 0
#define L_TK 1
#define L_ML 2
#define L_FN 3

// Function keys
#define F_FN 0
#define F_D0 1

// Macros
#define M_D0 0

// Keycodes
enum tk_keycodes {
	CK_TK = SAFE_RANGE,
	CK_BOOT,
	CK_ML
};

// Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// Base layer
	[L_BS] = KEYMAP ( \
		KC_ESC, F(F_FN),KC_TAB, KC_BSPC, \
		KC_NLCK,KC_PSLS,KC_PAST,KC_PMNS, \
		KC_P7,  KC_P8,  KC_P9,  KC_PPLS, \
		KC_P4,  KC_P5,  KC_P6,  KC_NO,   \
		KC_P1,  KC_P2,  KC_P3,  KC_NO,   \
		KC_P0,  F(F_D0),KC_PDOT,KC_PENT  ),

	// TenKey layer
	[L_TK] = KEYMAP ( \
		KC_ESC, KC_TRNS,KC_NO,  KC_NO,   \
		KC_PSCR,KC_SLCK,KC_PAUS,KC_NO,   \
		KC_INS, KC_HOME,KC_PGUP,KC_NO,   \
		KC_DEL, KC_END, KC_PGDN,KC_NO,   \
		KC_NO,  KC_UP,  KC_NO,  KC_NO,   \
		KC_LEFT,KC_DOWN,KC_RGHT,CK_ML    ),

	// Mouse layer
	[L_ML] = KEYMAP ( \
		KC_NO,     KC_NO,     KC_NO,      KC_NO,   \
		KC_NO,     KC_NO,     KC_NO,      KC_NO,   \
		KC_NO,     KC_MS_UP,  KC_NO,      KC_NO,   \
		KC_MS_LEFT,KC_MS_BTN1,KC_MS_RIGHT,KC_NO,   \
		KC_NO,     KC_MS_DOWN,KC_NO,      KC_NO,   \
		KC_MS_BTN2,KC_NO,     KC_NO,      KC_TRNS  ),

	// Function layer
	[L_FN] = KEYMAP ( \
		CK_BOOT,KC_TRNS,KC_NO,  KC_NO,   \
		CK_TK,  KC_NO,  KC_NO,  KC_NO,   \
		KC_NO,  KC_NO,  KC_NO,  KC_NO,   \
		KC_NO,  KC_NO,  KC_NO,  KC_NO,   \
		KC_NO,  KC_NO,  KC_NO,  KC_NO,   \
		KC_NO,  KC_NO,  KC_NO,  KC_NO    ),
};

const uint16_t PROGMEM fn_actions[] = {
	[F_FN] = ACTION_LAYER_MOMENTARY(L_FN),
	[F_D0] = ACTION_MACRO(M_D0)
};

const macro_t* action_get_macro(keyrecord_t* record, uint8_t id, uint8_t opt)
{
	if (record->event.pressed) {
		switch (id) {
			case M_D0:
				return MACRO(T(P0), T(P0), END);
				
			default:
				break;
		}
	}
	
	return MACRO_NONE;
}

static LED_TYPE colNorm = { 0x0F, 0x0F, 0x0F };
static LED_TYPE colNlck = { 0x3F, 0x17, 0x0F };
static LED_TYPE colTenk = { 0x0F, 0x3F, 0x0F };
static LED_TYPE colSlck = { 0x0F, 0x2F, 0x2F };
static LED_TYPE colMous = { 0x0F, 0x17, 0x3F };

uint8_t ledState;

void updateLed(void)
{
	if (IS_LAYER_ON(L_TK)) {
		if (IS_LAYER_ON(L_ML)) {
			ws2812_setleds(&colMous, 1);
		} else {
			ws2812_setleds((ledState & (1 << USB_LED_SCROLL_LOCK))
				? &colSlck
				: &colTenk, 1);
		}
	} else {
		ws2812_setleds((ledState & (1 << USB_LED_NUM_LOCK)) ?
			&colNlck :
			&colNorm, 1);
	}
}

bool process_record_user(uint16_t keycode, keyrecord_t* record)
{
	if (keycode == CK_TK ) {
		if (record->event.pressed) {
			if (IS_LAYER_ON(L_TK)) {
				layer_state &= ~(1UL << L_TK);
				updateLed();
			} else {
				layer_state |= 1UL << L_TK;
				updateLed();
			}

			return false;
		}
	} else if (keycode == CK_ML) {
		if (record->event.pressed) {
			layer_state |= 1UL << L_ML;
			clear_keyboard();
			updateLed();
		} else {
			layer_state &= ~(1UL << L_ML);
			clear_keyboard();
			updateLed();
		}
	} else if (keycode == CK_BOOT) {
		// Stop pressing keys.
		clear_keyboard();

		// Fade out led for shits and giggles.
		for (int i = 256; i > 0x00; i -= 2) {
			uint8_t val = i - 1;
			uint8_t rgbDat[] = { val, val, val };
			ws2812_setleds((LED_TYPE*)&rgbDat, 1);
			_delay_ms(5);
		}

		// Disable led.
		uint8_t rgbDat[] = { 0x00, 0x00, 0x00 };
		ws2812_setleds((LED_TYPE*)&rgbDat, 1);

		reset_keyboard();
	}

	return true;
}

void led_set_user(uint8_t usb_led)
{
	ledState = usb_led;
	updateLed();
}
