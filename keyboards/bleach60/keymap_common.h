#ifndef KEYMAP_COMMON_H
#define KEYMAP_COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"

// Full layout
#define KEYMAP( \
	K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11, K12, K13, K14, K15, \
	K16, K17, K18, K19, K20, K21, K22, K23, K24, K25, K26, K27, K28,      K29, \
	K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K40, K41,           K42, \
	K43, K64, K44, K45, K46, K47, K48, K49, K50, K51, K52, K53,      K54, K55, \
	K56, K57, K58,                K59,                     K60, K61, K62, K63  \
) { \
	{ KC_##K01, KC_##K16, KC_##K30, KC_##K43, KC_##K56 }, \
	{ KC_##K02, KC_##K17, KC_##K31, KC_##K44, KC_##K57 }, \
	{ KC_##K03, KC_##K18, KC_##K32, KC_##K45, KC_##K58 }, \
	{ KC_##K04, KC_##K19, KC_##K33, KC_##K46, KC_NO    }, \
	{ KC_##K05, KC_##K20, KC_##K34, KC_##K47, KC_NO    }, \
	{ KC_##K06, KC_##K21, KC_##K35, KC_##K48, KC_##K59 }, \
	{ KC_##K07, KC_##K22, KC_##K36, KC_##K49, KC_NO    }, \
	{ KC_##K08, KC_##K23, KC_##K37, KC_##K50, KC_NO    }, \
	{ KC_##K09, KC_##K24, KC_##K38, KC_##K51, KC_NO    }, \
	{ KC_##K10, KC_##K25, KC_##K39, KC_##K52, KC_##K60 }, \
	{ KC_##K11, KC_##K26, KC_##K40, KC_##K53, KC_##K61 }, \
	{ KC_##K12, KC_##K27, KC_##K41, KC_##K64, KC_NO    }, \
	{ KC_##K13, KC_##K28, KC_NO,    KC_##K54, KC_##K62 }, \
	{ KC_##K14, KC_NO,    KC_##K42, KC_NO,    KC_NO    }, \
	{ KC_##K15, KC_##K29, KC_NO,    KC_##K55, KC_##K63 }  \
}

// Standard ANSI layout
#define KEYMAP_ANSI( \
	K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11, K12, K13, K15, \
	K16, K17, K18, K19, K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, \
	K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K40, K41,      K42, \
	K43, K44, K45, K46, K47, K48, K49, K50, K51, K52, K53,           K54, \
	K56, K57, K58,                K59,                K60, K61, K62, K63  \
) { \
	{ KC_##K01, KC_##K16, KC_##K30, KC_##K43, KC_##K56 }, \
	{ KC_##K02, KC_##K17, KC_##K31, KC_##K44, KC_##K57 }, \
	{ KC_##K03, KC_##K18, KC_##K32, KC_##K45, KC_##K58 }, \
	{ KC_##K04, KC_##K19, KC_##K33, KC_##K46, KC_NO    }, \
	{ KC_##K05, KC_##K20, KC_##K34, KC_##K47, KC_NO    }, \
	{ KC_##K06, KC_##K21, KC_##K35, KC_##K48, KC_##K59 }, \
	{ KC_##K07, KC_##K22, KC_##K36, KC_##K49, KC_NO    }, \
	{ KC_##K08, KC_##K23, KC_##K37, KC_##K50, KC_NO    }, \
	{ KC_##K09, KC_##K24, KC_##K38, KC_##K51, KC_NO    }, \
	{ KC_##K10, KC_##K25, KC_##K39, KC_##K52, KC_##K60 }, \
	{ KC_##K11, KC_##K26, KC_##K40, KC_##K53, KC_##K61 }, \
	{ KC_##K12, KC_##K27, KC_##K41, KC_NO,    KC_NO    }, \
	{ KC_##K13, KC_##K28, KC_NO,    KC_##K54, KC_##K62 }, \
	{ KC_NO,    KC_NO,    KC_##K42, KC_NO,    KC_NO    }, \
	{ KC_##K15, KC_##K29, KC_NO,    KC_NO,    KC_##K63 }  \
}

// Standard ISO layout
#define KEYMAP_ISO( \
	K01, K02, K03, K04, K05, K06, K07, K08, K09, K10, K11, K12, K13, K15, \
	K16, K17, K18, K19, K20, K21, K22, K23, K24, K25, K26, K27, K28,      \
	K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K40, K41, K29, K42, \
	K43, K64, K44, K45, K46, K47, K48, K49, K50, K51, K52, K53,      K54, \
	K56, K57, K58,                K59,                K60, K61, K62, K63  \
) { \
	{ KC_##K01, KC_##K16, KC_##K30, KC_##K43, KC_##K56 }, \
	{ KC_##K02, KC_##K17, KC_##K31, KC_##K44, KC_##K57 }, \
	{ KC_##K03, KC_##K18, KC_##K32, KC_##K45, KC_##K58 }, \
	{ KC_##K04, KC_##K19, KC_##K33, KC_##K46, KC_NO    }, \
	{ KC_##K05, KC_##K20, KC_##K34, KC_##K47, KC_NO    }, \
	{ KC_##K06, KC_##K21, KC_##K35, KC_##K48, KC_##K59 }, \
	{ KC_##K07, KC_##K22, KC_##K36, KC_##K49, KC_NO    }, \
	{ KC_##K08, KC_##K23, KC_##K37, KC_##K50, KC_NO    }, \
	{ KC_##K09, KC_##K24, KC_##K38, KC_##K51, KC_NO    }, \
	{ KC_##K10, KC_##K25, KC_##K39, KC_##K52, KC_##K60 }, \
	{ KC_##K11, KC_##K26, KC_##K40, KC_##K53, KC_##K61 }, \
	{ KC_##K12, KC_##K27, KC_##K41, KC_##K64, KC_NO    }, \
	{ KC_##K13, KC_##K28, KC_NO,    KC_##K54, KC_##K62 }, \
	{ KC_NO,    KC_NO,    KC_##K42, KC_NO,    KC_NO    }, \
	{ KC_##K15, KC_##K29, KC_NO,    KC_NO,    KC_##K63 }  \
}

#endif//KEYMAP_COMMON_H
