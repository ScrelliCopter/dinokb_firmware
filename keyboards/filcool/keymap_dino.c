#include "keymap_common.h"

enum layer_id
{
  LAYER_BASE,      // Layer 0: Standard ANSI layer
  LAYER_FUNCTION,  // Layer 1: Function layer
  NUM_LAYERS
};

const uint8_t keymaps_size = NUM_LAYERS;
const uint8_t PROGMEM keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] =
{
  [LAYER_BASE] = KEYMAP_ANSI_ISO_JIS( \
    ESC,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,    PSCR,SLCK,PAUS,                         \
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,   INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS, \
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,   DEL, END, PGDN,    P7,  P8,  P9,  PPLS, \
    FN0, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,                       P4,  P5,  P6,        \
    LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     RSFT,        UP,           P1,  P2,  P3,  PENT, \
    LCTL,LGUI,LALT,               SPC,                RALT,RGUI, FN0,RCTL,   LEFT,DOWN,RGHT,    P0,  PDOT),
  [LAYER_FUNCTION] = KEYMAP_ANSI_ISO_JIS( \
    BTLD,     NO  ,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,     NO,  NO,  NO,                           \
    NO,  NO,  NO,  NO,  NO,  NO,  NLCK,PSLS,PAST,PMNS,NO,  NO,  NO,  BSPC,   VOLD,MUTE,VOLU,    NO,  NO,  NO,  NO,   \
    CAPS,NO,  NO,  NO,  NO,  CALC,P7,  P8,  P9,  PPLS,NO,  NO,  NO,  NO,     MPRV,MPLY,MNXT,    NO,  NO,  NO,  NO,   \
    TRNS,NO,  NO,  NO,  NO,  FN1, P4,  P5,  P6,  PENT,NO,  NO,       NO,                        NO,  NO,  NO,        \
    NO,  NO,  NO,  NO,  NO,  NO,  P0,  P1,  P2,  P3,  PDOT,NO,       NO,          NO,           NO,  NO,  NO,  NO,   \
    NO,  NO,  NO,                 NO,                 NO,  NO,  TRNS,NO,     NO,  NO,  NO,      NO,  NO)
};


enum macro_id
{
  MACRO_DOUBLE_ZERO
};

const macro_t* action_get_macro(keyrecord_t* record, uint8_t id, uint8_t opt)
{
  switch (id)
  {
  case MACRO_DOUBLE_ZERO: return record->event.pressed
    ? MACRO(T(0), T(0), END)
    : MACRO_NONE;
  default: return MACRO_NONE;
  }
}


enum function_id
{
  FN0_FUNCTION,     // FN0: Hold for function layer
  FN1_DOUBLE_ZERO,  // FN1: Numpad double zeros
  NUM_FUNCTIONS
};

const uint8_t fn_actions_size = NUM_FUNCTIONS;
const action_t PROGMEM fn_actions[NUM_FUNCTIONS] =
{
  [FN0_FUNCTION]    = ACTION_LAYER_MOMENTARY(LAYER_FUNCTION),
  [FN1_DOUBLE_ZERO] = ACTION_MACRO(MACRO_DOUBLE_ZERO)
};


extern bool swap_num_scroll;
extern void update_leds(void);

void hook_layer_change(uint32_t layer_state)
{
  const bool function = (1 << LAYER_FUNCTION) == layer_state;
  if (function != swap_num_scroll)
  {
    swap_num_scroll = function;
    update_leds();
  }
}
