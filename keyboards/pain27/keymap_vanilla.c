/* keymap_vanilla.c - pain27 - (C) 2023 a dinosaur */

#include "keymap_common.h"


const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] KEYMAP_SECTION =
{
	[0] = KEYMAP(
		Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,
		A,   S,   D,   F,   G,   H,   J,   K,   L,   /**/
		Z,   X,   C,   V,   B,   N,   M,   /**/ /**/ /**/
		/**/ /**/ /**/ /**/ SPC  /**/ /**/ /**/ /**/ /**/)
};

const action_t fn_actions[] ACTION_SECTION = {};
