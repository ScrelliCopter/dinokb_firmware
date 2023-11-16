#include "keymap_common.h"

#define KEYMAPS_SIZE 3
const uint8_t keymaps_size = KEYMAPS_SIZE;
const uint8_t PROGMEM keymaps[KEYMAPS_SIZE][MATRIX_ROWS][MATRIX_COLS] =
{
  /* Layer 0: Standard ANSI layer */
  KEYMAP_ANSI_ISO_JIS( \
    ESC,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,    PSCR,SLCK,PAUS,                         \
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,   INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS, \
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,   DEL, END, PGDN,    P7,  P8,  P9,  PPLS, \
    CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,                       P4,  P5,  P6,        \
    LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     RSFT,        UP,           P1,  P2,  P3,  PENT, \
    LCTL,LGUI,LALT,               SPC,                RALT,RGUI, FN0,RCTL,   LEFT,DOWN,RGHT,    P0,  PDOT),          \
  /* Layer 1: Colemak */
  KEYMAP_ANSI_ISO_JIS( \
    ESC,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,    PSCR,SLCK,PAUS,                         \
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,   INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS, \
    TAB, Q,   W,   F,   P,   G,   J,   L,   U,   Y,   SCLN,LBRC,RBRC,BSLS,   DEL, END, PGDN,    P7,  P8,  P9,  PPLS, \
    CAPS,A,   R,   S,   T,   D,   H,   N,   E,   I,   O,   QUOT,     ENT,                       P4,  P5,  P6,        \
    LSFT,NUBS,Z,   X,   C,   V,   B,   K,   M,   COMM,DOT, SLSH,     RSFT,        UP,           P1,  P2,  P3,  PENT, \
    LCTL,LGUI,LALT,               SPC,                RALT,RGUI, FN0,RCTL,   LEFT,DOWN,RGHT,    P0,  PDOT),          \
  /* Layer 2: Function layer */
  KEYMAP_ANSI_ISO_JIS( \
    BTLD,     NO  ,NO,  NO,  NO,  FN3, FN4, NO,  NO,  NO,  NO,  NO,  NO,     NO,  FN2, NO,                           \
    NLCK,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,     VOLD,MUTE,VOLU,    NO,  NO,  NO,  NO,   \
    CALC,NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,     MPRV,MPLY,MNXT,    NO,  NO,  NO,  NO,   \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,       NO,                        NO,  NO,  NO,        \
    NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,  NO,       NO,          NO,           NO,  NO,  NO,  NO,   \
    NO,  NO,  NO,                 NO,                 NO,  NO,  TRNS,NO,     NO,  NO,  NO,      NO,  NO)
};


enum macro_id
{
  DOUBLE_ZERO,
  GREGGO,
};

#define FN_ACTIONS_SIZE 5
const uint8_t fn_actions_size = FN_ACTIONS_SIZE;
const action_t PROGMEM fn_actions[FN_ACTIONS_SIZE] =
{
  [0] = ACTION_LAYER_MOMENTARY(2),
  [1] = ACTION_MACRO(DOUBLE_ZERO),
  [2] = ACTION_MACRO(GREGGO),
  [3] = ACTION_DEFAULT_LAYER_SET(0),
  [4] = ACTION_DEFAULT_LAYER_SET(1)
};

const macro_t* action_get_macro(keyrecord_t* record, uint8_t id, uint8_t opt)
{
  switch (id)
  {
  case DOUBLE_ZERO: return record->event.pressed
    ? MACRO(T(0), T(0), END)
    : MACRO_NONE;
  case GREGGO: return record->event.pressed
    ? MACRO( D(LSFT), T(SCLN), T(G), U(LSFT), T(R), T(E), T(G), T(G), T(O), D(LSFT), T(SCLN), END )
    : MACRO_NONE;
  default: return MACRO_NONE;
  }
}
