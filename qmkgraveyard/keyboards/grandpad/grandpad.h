#ifndef GRANDPAD_H
#define GRANDPAD_H

#include "quantum.h"

// Full grid layout
#define KEYMAP( \
	K01, K02, K03, K04, \
	K05, K06, K07, K08, \
	K09, K10, K11, K12, \
	K13, K14, K15, K16, \
	K17, K18, K19, K20, \
	K21, K22, K23, K24  \
) { \
	{ K01,   K02,   K03,   K04   }, \
	{ K05,   K06,   K07,   K08   }, \
	{ K09,   K10,   K11,   K12   }, \
	{ K13,   K14,   K15,   K16   }, \
	{ K17,   K18,   K19,   K20   }, \
	{ K21,   K22,   K23,   K24   }  \
}

// 21-key numpad layout with extra top row
#define KEYMAP_K21( \
	K01, K02, K03, K04, \
	K05, K06, K07, K08, \
	K09, K10, K11, K12, \
	K13, K14, K15,      \
	K17, K18, K19,      \
	K21,      K23, K24  \
) { \
	{ K01,   K02,   K03,   K04   }, \
	{ K05,   K06,   K07,   K08   }, \
	{ K09,   K10,   K11,   K12   }, \
	{ K13,   K14,   K15,   KC_NO }, \
	{ K17,   K18,   K19,   KC_NO }, \
	{ K21,   KC_NO, K23,   K24   }  \
}

// Standard 17-key numpad layout
#define KEYMAP_K17( \
	K05, K06, K07, K08, \
	K09, K10, K11, K12, \
	K13, K14, K15,      \
	K17, K18, K19,      \
	K21,      K23, K24  \
) { \
	{ KC_NO, KC_NO, KC_NO, KC_NO }, \
	{ K05,   K06,   K07,   K08   }, \
	{ K09,   K10,   K11,   K12   }, \
	{ K13,   K14,   K15,   KC_NO }, \
	{ K17,   K18,   K19,   KC_NO }, \
	{ K21,   KC_NO, K23,   K24   }  \
}

#endif
