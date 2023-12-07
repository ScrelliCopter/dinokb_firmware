#ifndef CONFIG_H
#define CONFIG_H

// USB Device descriptor
#define VENDOR_ID     0xDEAD
#define PRODUCT_ID    0xDEAD
#define DEVICE_VER    0xDEAD
#define MANUFACTURER  uuupah
#define PRODUCT       pain27 keyboard
#define DESCRIPTION   t.m.k. keyboard firmware for pain27

// Key matrix size
#define MATRIX_COLS 9
#define MATRIX_ROWS 3

// Debounce time in ms, Set to 0 if debouncing isn't needed
#define DEBOUNCE 5

// Pro Micro LED pins
#define TXLED_PORT D
#define TXLED_PIN  5
#define RXLED_PORT B
#define RXLED_PIN  0

// Backlight pins
#ifdef BACKLIGHT_ENABLE
#define BACKLIGHT_LED_1_PORT D
#define BACKLIGHT_LED_1_PIN  0
#define BACKLIGHT_LED_2_PORT B
#define BACKLIGHT_LED_2_PIN  5
#define BACKLIGHT_LED_3_PORT B
#define BACKLIGHT_LED_3_PIN  6
#define BACKLIGHT_LEVELS 3
#endif

// RGB underlighting
#ifdef UNDERGLOW_ENABLE
#define RGB_DI_PORT B
#define RGB_DI_PIN  2
#define RGBLED_NUM  9
#endif

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

#endif//CONFIG_H
