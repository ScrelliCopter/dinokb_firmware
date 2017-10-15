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

// Keymap
const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =
{
	{{KC_FN0}},
};

// Functions
const action_t PROGMEM fn_actions[] =
{
	[0] = ACTION_MACRO(0)
};

// Macros
const macro_t *action_get_macro (keyrecord_t *record, uint8_t id, uint8_t opt)
{
    switch (id)
	{
        case (0):
            return (record->event.pressed ?
                    MACRO( D(LSFT), T(SCLN), U(LSFT), T(C), T(H), T(O), T(O), T(M), T(A), T(H), D(LSFT), T(SCLN), U(LSFT), END ) : 0);
    }
    return MACRO_NONE;
}