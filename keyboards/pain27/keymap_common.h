/* keymap_common.h - pain27 - (C) 2023 a dinosaur */

#ifndef KEYMAP_COMMON_H
#define KEYMAP_COMMON_H

#include <stdint.h>
#include "keycode.h"
#include "action.h"
#include "action_code.h"
#include "action_layer.h"
#include "action_macro.h"
#include "action_util.h"

#define KEYMAP( \
	K01, K02, K03, K04, K05, K06, K07, K08, K18, K09, \
	K10, K11, K12, K13, K14, K15, K16, K17, K27,      \
	K19, K20, K21, K22, K24, K25, K26,                \
	                    K23                           \
) { \
	{ KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07, KC_##K08, KC_##K09 }, \
	{ KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17, KC_##K18 }, \
	{ KC_##K19, KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27 }  \
}

#ifdef KEYMAP_SECTION_ENABLE
#  define KEYMAP_SECTION __attribute__((section(".keymap.keymaps")))
#  define ACTION_SECTION __attribute__((section(".keymap.fn_actions")))
#else
#  define KEYMAP_SECTION PROGMEM
#  define ACTION_SECTION PROGMEM
#endif

#endif//KEYMAP_COMMON_H
