#include "keymap.h"

extern const uint8_t keymaps_size;
extern const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS];

extern const uint8_t fn_actions_size;
extern const action_t fn_actions[];

uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
	return pgm_read_byte(layer < keymaps_size
		? &keymaps[layer][key.row][key.col]
		: &keymaps[0][key.row][key.col]);
}

action_t keymap_fn_to_action(uint8_t keycode)
{
	uint8_t func = FN_INDEX(keycode);
	return func < fn_actions_size
		? (action_t){ .code = pgm_read_word(&fn_actions[func]) }
		: (action_t)ACTION_NO;
}
