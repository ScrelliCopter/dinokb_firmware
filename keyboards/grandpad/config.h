#ifndef CONFIG_H
#define CONFIG_H

// USB Device descriptor
#define VENDOR_ID       0xDEAD
#define PRODUCT_ID      0xDEAD
#define DEVICE_VER      0xDEAD
#define MANUFACTURER	Youbantoo
#define PRODUCT			Grand Pad
#define DESCRIPTION		https://youbantoo.club/

// Key matrix size
#define MATRIX_ROWS 6
#define MATRIX_COLS 4

// Debounce time in ms, Set to 0 if debouncing isn't needed
#define DEBOUNCE 5

// Key combination for command
#define IS_COMMAND() ( \
	keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)


// Feature disable options
// These options are also useful to firmware size reduction.

// Disable debug print
//#define NO_DEBUG

// Disable print
//#define NO_PRINT

// Disable action features
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION


// WS2812B RGB Underglow LED IO pin
#define RGB_DI_PORT B
#define RGB_DI_PIN  4

#define RGBLED_NUM 1

#endif//CONFIG_H
