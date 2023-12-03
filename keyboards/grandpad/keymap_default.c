/* keymap_default.c - grandpad - (c) a dinosaur 2017, 2023 */

#include "keymap_common.h"
#include "config.h"


/////////////////////
/// Layer definitions
enum layer_id
{
	LAYER_BASE,  // Layer 0: Base layer

	NUM_LAYERS
};

const uint8_t keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] KEYMAP_SECTION =
{
	[LAYER_BASE] = KEYMAP(
		ESC, TAB, PEQL,BSPC,
		NLCK,PSLS,PAST,PMNS,
		P7,  P8,  P9,  PPLS,
		P4,  P5,  P6,  LBRC,
		P1,  P2,  P3,  RBRC,
		P0,  FN0, PDOT,PENT)
};


////////////////////
/// Macro defintions
enum macro_id
{
	MACRO_DOUBLEZERO
};

const macro_t* action_get_macro(keyrecord_t* record, uint8_t id, uint8_t opt)
{
	switch (id)
	{
	case MACRO_DOUBLEZERO: return record->event.pressed ? MACRO(T(P0), T(P0), END) : MACRO_NONE;
	default: return MACRO_NONE;
	}
}


/////////////////////////////////
/// Function & action definitions
enum function_id
{
	FN0_MACRO_DOUBLEZERO,

	NUM_FUNCTIONS
};

const action_t fn_actions[NUM_FUNCTIONS] ACTION_SECTION =
{
	[FN0_MACRO_DOUBLEZERO] = ACTION_MACRO(FN0_MACRO_DOUBLEZERO)
};
